#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>

#define size 17
#define no 2 * size


unsigned long sum_num_solutions = 0;
unsigned long sum_iterations = 0;

bool queenAt(int row, int col, int queens[size])
{
    return queens[col] == row;
}

void printBoard(int queens[size])
{
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (queenAt(x, y, queens))
            {
                putchar('Q');
            }
            else
            {
                putchar('.');
            }
        }
        putchar('\n');
    }
    puts("==============");
}

bool is_legal(int row, int col, int queens[size])
{
    // always check to the left
    // same row
    // diag up
    // diag down

    // .Q.
    // ...
    // Q..
    // row = 2
    // col = 1
    // y = 0
    for (int y = 0; y < col; y++)
    {
        if (queens[y] == row)
        {
            return false;
        }

        if (queens[y] == row - col + y)
        {
            return false;
        }

        if (queens[y] == row + col - y)
        {
            return false;
        }
    }
    return true;
}

// init to col 0
// row 1234...
// if found col++ else col-- and set to -1 (for printboard)
void resolve(int col, int queens[size], unsigned long *num_solutions, unsigned long *iterations)
{
    if (col == size)
    {
        // printBoard(queens);
        (*num_solutions)++;
        return;
    }

    for (int row = 0; row < size; row++)
    {
        (*iterations)++;
        queens[col] = row;
        if (is_legal(row, col, queens))
        {
            resolve(col + 1, queens, num_solutions, iterations);
        }
    }
    queens[col] = no;
}

void init_resolve(int row)
{

    int queens[size]; // [col] = row
    unsigned long num_solutions = 0;
    unsigned long iterations = 1;
    memset(&queens, no, size * sizeof(int));

    queens[0] = row;

    resolve(1, queens, &num_solutions, &iterations);

    #pragma omp critical
    {
        sum_num_solutions += num_solutions;
        sum_iterations += iterations;
    }
}

int main()
{
    clock_t start, end;
    double cpu_time_used;
    start = omp_get_wtime();

#pragma omp parallel for
    for (int i = 0; i < size; i++)
    {
        init_resolve(i);
    }
    end = omp_get_wtime();
    cpu_time_used = ((double)(end - start));

    printf("%lu solutions\n%lu iterations\ntook %f seconds\n", sum_num_solutions, sum_iterations, cpu_time_used);
}