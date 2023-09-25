#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define size 15
#define no 2 * size

int queens[size]; // [col] = row
unsigned long num_solutions = 0;
unsigned long iterations = 0;

bool queenAt(int row, int col)
{
    return queens[col] == row;
}

void printBoard()
{
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (queenAt(x, y))
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

bool is_legal(int row, int col)
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
void resolve(int col)
{
    if (col == size)
    {
        // printBoard();
        num_solutions++;
        return;
    }

    for (int row = 0; row < size; row++)
    {
        iterations++;
        queens[col] = row;
        if (is_legal(row, col))
        {
            resolve(col + 1);
        }
    }
    queens[col] = no;
}

int main()
{
    clock_t start, end;
    double cpu_time_used;
    memset(&queens, no, size * sizeof(int));
    printBoard();
    start = clock();
    resolve(0);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%lu solutions\n%lu iterations\ntook %f seconds\n", num_solutions, iterations, cpu_time_used);
}