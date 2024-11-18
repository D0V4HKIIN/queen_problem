fn is_legal(row: usize, col: usize, queens: &Vec<usize>) -> bool {
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

fn init_resolve(
    row: usize,
    size: usize,
    no: usize,
    sum_num_solutions: Arc<Mutex<u64>>,
    sum_iterations: Arc<Mutex<u64>>,
) {
    let mut queens: Vec<usize> = vec![no; size];
    let mut num_solutions: u64 = 0;
    let mut iterations = 1;

    queens[0] = row;

    resolve(
        1,
        &mut queens,
        &mut iterations,
        &mut num_solutions,
        size,
        no,
    );

    let mut sum_sol = sum_num_solutions.lock().unwrap();
    *sum_sol += num_solutions;
    let mut sum_it = sum_iterations.lock().unwrap();
    *sum_it += iterations;
}

use rayon::prelude::*;
use std::env;
use std::sync::{Arc, Mutex};
use std::time::Instant;

fn main() {
    let args: Vec<String> = env::args().collect();

    let size: usize = {
        if args.len() == 2 {
            match args[1].parse::<usize>() {
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

    let no: usize = 2 * size;

    println!("using size = {size}");
    let sum_num_solutions: Arc<Mutex<u64>> = Arc::new(Mutex::new(0));
    let sum_iterations: Arc<Mutex<u64>> = Arc::new(Mutex::new(0));

    let start = Instant::now();
    (1..size).into_par_iter().for_each(|i| {
        init_resolve(
            i,
            size,
            no,
            Arc::clone(&sum_num_solutions),
            Arc::clone(&sum_iterations),
        )
    });

    println!(
        "{} solutions\n{} iterations\ntook {:.2?}\n",
        sum_num_solutions.lock().unwrap(),
        sum_iterations.lock().unwrap(),
        start.elapsed()
    );
}
