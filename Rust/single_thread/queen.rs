fn is_legal(row: usize, col: usize, queens: & Vec<usize>) -> bool {
    for y in 0..col {
        if queens[y] == row {
            return false;
        }
        if queens[y] as isize == row as isize - col as isize + y as isize {
            return false;
        }

        if queens[y] as isize == row as isize + col as isize - y as isize {
            return false;
        }
    }
    return true;
}

fn resolve(
    col: usize,
    queens: &mut Vec<usize>,
    iterations: &mut u64,
    num_solutions: &mut u64,
    size: usize,
    no: usize,
) {
    if col == size {
        *num_solutions += 1;
        return;
    }

    for row in 0..size {
        *iterations += 1;
        queens[col] = row;
        if is_legal(row, col, queens) {
            resolve(col + 1, queens, iterations, num_solutions, size, no);
        }
    }
    queens[col] = no;
}

use std::env;
use std::time::Instant;

fn main() {
    let args: Vec<String> = env::args().collect();

    let size: usize = {
        if args.len() == 2 {
            match args[1].parse::<usize>(){
                Ok(size) => size,
                Err(_e) => {
                    println!("expecting an integer as argument");
                    std::process::exit(-1);
                }
            }
        } else {
            8
        }
    };

    println!("using size = {size}");

    let no: usize = 2 * size;

    let mut queens: Vec<usize> = vec![no; size];
    let mut num_solutions: u64 = 0;
    let mut iterations = 0;

    let start = Instant::now();
    resolve(
        0,
        &mut queens,
        &mut iterations,
        &mut num_solutions,
        size,
        no,
    );

    println!(
        "{num_solutions} solutions\n{iterations} iterations\ntook {:.2?}\n",
        start.elapsed()
    );
}
