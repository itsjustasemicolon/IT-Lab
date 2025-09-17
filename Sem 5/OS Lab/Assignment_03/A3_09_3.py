#!/usr/bin/env python3
""" *************************************************************************************************
"" Assignment No.: 3
"" Assignment    : Parallel Programming in Python - Matrix Multiplication using Multiprocessing
"" Date          : 12/08/2025
"" Group No.     : A3
"" Team No.      : 09
"" Roll No.      : 002311001004, 002311001011, 002311001049
"" Name          : Soham Das, Sarbo Sarcar, Arnob Bhakta
"" Details       : A Python program that multiplies two large square matrices in parallel using 
""                 the multiprocessing module. The program divides the first matrix into row 
""                 chunks, assigns each chunk to a separate process, and multiplies it with 
""                 the second matrix. The execution time is measured.
"" Input         : Command-line arguments specifying matrix dimension, number of processes, 
""                 modulus value for initialization, and a print flag.
"" Output        : Elapsed execution time and optional printing of matrices.
""
"" Execution     : python3 A3_09_3.py <dimension> <threads> <mod_val> <print_switch>
""
"" Sample Input  : python3 A3_09_3.py 3000 10 84 1
""
"" Sample Output :
"" Initializing 3000x3000 matrices...
Initialization complete.

Starting matrix multiplication with 10 processes...
Matrix multiplication complete.
Time Elapsed: 13.6681 seconds

--- Input Matrix A ---
[[51 14 71 ... 48 40 16]
 [20 50 58 ... 80  1 24]
 [12 69 66 ... 77 67 16]
 ...
 [ 4 36 74 ... 40 22 25]
 [27 39 42 ...  6 43 73]
 [64 47 57 ... 79 11 14]]

--- Input Matrix B ---
[[ 0 61 24 ... 69  8 79]
 [18 19 76 ... 64 19 17]
 [74 28 76 ... 59 18 77]
 ...
 [45 38 48 ... 25 23 74]
 [ 9  6 53 ... 68 55  2]
 [48 20 66 ... 57 46 56]]

--- Result Matrix C ---
[[5014435 5044413 4824865 ... 5047789 4979953 4976611]
 [5222614 5209517 5008655 ... 5237725 5251477 5236041]
 [5291467 5330678 5092048 ... 5205442 5316450 5292740]
 ...
 [5112472 5132064 4965631 ... 5002377 5073256 5094724]
 [5354336 5371559 5143769 ... 5267930 5305765 5345355]
 [5141079 5181697 4994877 ... 5159840 5090467 5177105]]

 === Snapshot of output using 'cpustat' for 6 seconds during program run: ===

   %CPU   %USR   %SYS     PID S  CPU    Time Task
 98.00  98.00   0.00   19300 R    7   4.50s python3
 85.00  85.00   0.00   19296 R    6   4.28s python3
 81.00  81.00   0.00   19303 R    5   4.34s python3
 79.00  79.00   0.00   19291 R    9   4.44s python3
 78.00  78.00   0.00   19304 R   10   2.90s python3
 76.00  76.00   0.00   19305 R    4   3.99s python3
 75.00  75.00   0.00   19299 R   11   3.81s python3
 74.00  74.00   0.00   19297 R   11   4.15s python3
 73.00  73.00   0.00   19306 R    9   2.90s python3
 70.00  70.00   0.00   19293 R    3   4.52s python3
 69.00  69.00   0.00   19302 R    1   3.88s python3
 68.00  68.00   0.00   19298 R    8   3.90s python3
 66.00  66.00   0.00   19292 R    2   4.73s python3
 65.00  65.00   0.00   19294 R    2   4.67s python3
 65.00  65.00   0.00   19301 R    0   4.23s python3
 64.00  64.00   0.00   19295 R    7   4.40s python3
  8.00   7.00   1.00   13251 S    0   1.28m gnome-system-monitor
  2.00   2.00   0.00    3520 S   10   2.30m /usr/bin/gnome-shell
  1.00   0.00   1.00    5655 S    2   3.57m /snap/firefox/6565/usr/lib/firefox/firefox
  1.00   1.00   0.00    8468 S    8  13.58s /usr/libexec/gnome-terminal-server

  %CPU   %USR   %SYS     PID S  CPU    Time Task
 98.00  98.00   0.00   19299 R   11   4.79s python3
 94.00  94.00   0.00   19296 R    6   5.22s python3
 87.00  87.00   0.00   19300 R    7   5.37s python3
 79.00  79.00   0.00   19306 R    9   3.69s python3
 77.00  77.00   0.00   19303 R    5   5.11s python3
 77.00  77.00   0.00   19297 R   11   4.92s python3
 77.00  77.00   0.00   19305 R    4   4.76s python3
 74.00  74.00   0.00   19301 R    0   4.97s python3
 73.00  73.00   0.00   19304 R   10   3.63s python3
 71.00  70.00   1.00   19295 R    7   5.11s python3
 67.00  66.00   1.00   19294 R    2   5.34s python3
 66.00  66.00   0.00   19292 R    2   5.39s python3
 65.00  65.00   0.00   19291 R    9   5.09s python3
 64.00  64.00   0.00   19293 R    3   5.16s python3
 63.00  63.00   0.00   19298 R    8   4.53s python3
 59.00  59.00   0.00   19302 R    1   4.47s python3
  7.00   7.00   0.00   13251 S    0   1.28m gnome-system-monitor
  4.00   4.00   0.00    3520 S   10   2.30m /usr/bin/gnome-shell
  1.00   0.00   1.00   19367 R    5   0.02s cpustat
  1.00   1.00   0.00   10812 S    4  51.00s /snap/firefox/6565/usr/lib/firefox/firefox -contentproc -isForBrowser -prefsHandle 0:42800 -prefMapHandle 1:272080 -jsInitHa

  %CPU   %USR   %SYS     PID S  CPU    Time Task
 96.00  95.00   1.00   19299 R   11   5.75s python3
 92.00  92.00   0.00   19292 R    2   6.31s python3
 89.00  89.00   0.00   19303 R    5   6.00s python3
 85.00  85.00   0.00   19293 R    3   6.01s python3
 76.00  76.00   0.00   19305 R    4   5.52s python3
 73.00  73.00   0.00   19300 R    7   6.10s python3
 72.00  72.00   0.00   19306 R    9   4.41s python3
 71.00  71.00   0.00   19295 R    7   5.82s python3
 68.00  68.00   0.00   19304 R   10   4.31s python3
 68.00  68.00   0.00   19302 R    1   5.15s python3
 66.00  66.00   0.00   19301 R    0   5.63s python3
 65.00  65.00   0.00   19294 R    2   5.99s python3
 64.00  64.00   0.00   19297 R   11   5.56s python3
 64.00  64.00   0.00   19296 R    6   5.86s python3
 61.00  61.00   0.00   19298 R    8   5.14s python3
 60.00  60.00   0.00   19291 R    9   5.69s python3
  8.00   6.00   2.00    3520 S   10   2.30m /usr/bin/gnome-shell
  7.00   7.00   0.00   13251 S    0   1.29m gnome-system-monitor
  6.00   6.00   0.00    8468 S    8  13.64s /usr/libexec/gnome-terminal-server
  1.00   0.00   1.00    7868 S    2   2.18s /snap/firefox/6565/usr/lib/firefox/firefox -contentproc -isForBrowser -prefsHandle 0:42800 -prefMapHandle 1:272080 -jsInitHa

  %CPU   %USR   %SYS     PID S  CPU    Time Task
100.00 100.00   0.00   19297 R   11   6.56s python3
100.00 100.00   0.00   19300 R    7   7.10s python3
 91.00  91.00   0.00   19303 R    5   6.91s python3
 88.00  88.00   0.00   19292 R    2   7.19s python3
 85.00  85.00   0.00   19293 R    3   6.86s python3
 75.00  75.00   0.00   19295 R    7   6.57s python3
 70.00  70.00   0.00   19304 R   10   5.01s python3
 69.00  69.00   0.00   19306 R    9   5.10s python3
 69.00  69.00   0.00   19302 R    1   5.84s python3
 68.00  68.00   0.00   19294 R    2   6.67s python3
 65.00  65.00   0.00   19299 R   11   6.40s python3
 65.00  65.00   0.00   19298 R    8   5.79s python3
 65.00  65.00   0.00   19291 R    9   6.34s python3
 63.00  63.00   0.00   19301 R    0   6.26s python3
 61.00  61.00   0.00   19305 R    4   6.13s python3
 56.00  56.00   0.00   19296 R    6   6.42s python3
  6.00   6.00   0.00   13251 S    0   1.29m gnome-system-monitor
  1.00   0.00   1.00    1113 S    5  35.14s /usr/sbin/mysqld
  1.00   1.00   0.00    3520 S   10   2.30m /usr/bin/gnome-shell

  %CPU   %USR   %SYS     PID S  CPU    Time Task
100.00 100.00   0.00   19305 R    4   7.13s python3
 92.00  92.00   0.00   19303 R    5   7.83s python3
 90.00  90.00   0.00   19297 R   11   7.46s python3
 87.00  87.00   0.00   19301 R    0   7.13s python3
 84.00  84.00   0.00   19300 R    7   7.94s python3
 77.00  77.00   0.00   19302 R    1   6.61s python3
 74.00  74.00   0.00   19291 R    9   7.08s python3
 74.00  74.00   0.00   19296 R    6   7.16s python3
 72.00  72.00   0.00   19304 R   10   5.73s python3
 69.00  68.00   1.00   19293 R    3   7.55s python3
 69.00  69.00   0.00   19292 R    2   7.88s python3
 67.00  67.00   0.00   19295 R    7   7.24s python3
 63.00  63.00   0.00   19299 R   11   7.03s python3
 61.00  61.00   0.00   19294 R    2   7.28s python3
 57.00  57.00   0.00   19306 R    9   5.67s python3
 54.00  54.00   0.00   19298 R    8   6.33s python3
  7.00   7.00   0.00   13251 S    0   1.29m gnome-system-monitor
  2.00   2.00   0.00    3520 S   10   2.30m /usr/bin/gnome-shell
  1.00   1.00   0.00    6277 S    2  48.63s /snap/firefox/6565/usr/lib/firefox/firefox -contentproc -isForBrowser -prefsHandle 0:42506 -prefMapHandle 1:272080 -jsInitHa
  1.00   1.00   0.00      14 I    5   4.21s [rcu_sched]
  1.00   1.00   0.00    3430 S   11   0.57s /usr/bin/dbus-daemon
  1.00   1.00   0.00    5655 S    2   3.57m /snap/firefox/6565/usr/lib/firefox/firefox
  1.00   0.00   1.00   19367 R    5   0.03s cpustat
  1.00   1.00   0.00    6873 S    6   2.25m /snap/firefox/6565/usr/lib/firefox/firefox -contentproc -isForBrowser -prefsHandle 0:42800 -prefMapHandle 1:272080 -jsInitHa
  1.00   0.00   1.00     981 S    8  10.44s /usr/lib/erlang/erts-12.2.1/bin/beam.smp

  %CPU   %USR   %SYS     PID S  CPU    Time Task
 98.00  98.00   0.00   19305 R    4   8.11s python3
 95.00  95.00   0.00   19301 R    0   8.08s python3
 94.00  94.00   0.00   19303 R    5   8.77s python3
 92.00  92.00   0.00   19302 R    1   7.53s python3
 76.00  76.00   0.00   19296 R    6   7.92s python3
 75.00  75.00   0.00   19291 R    9   7.83s python3
 75.00  75.00   0.00   19295 R    7   7.99s python3
 71.00  71.00   0.00   19299 R   11   7.74s python3
 71.00  71.00   0.00   19293 R    3   8.26s python3
 71.00  71.00   0.00   19294 R    2   7.99s python3
 70.00  70.00   0.00   19300 R    7   8.64s python3
 64.00  64.00   0.00   19298 R    8   6.97s python3
 62.00  62.00   0.00   19304 R   10   6.35s python3
 61.00  61.00   0.00   19306 R    9   6.28s python3
 59.00  59.00   0.00   19297 R   11   8.05s python3
 58.00  58.00   0.00   19292 R    2   8.46s python3
  7.00   7.00   0.00   13251 S    0   1.29m gnome-system-monitor
  2.00   1.00   1.00    3520 S   10   2.30m /usr/bin/gnome-shell
  1.00   1.00   0.00    6252 S   10  15.96s /snap/firefox/6565/usr/lib/firefox/firefox -contentproc -isForBrowser -prefsHandle 0:42506 -prefMapHandle 1:272080 -jsInitHa

=== Summary of Timings ===
1 thread(s): 68.1075 seconds
2 thread(s): 35.7399 seconds
3 thread(s): 24.7012 seconds
4 thread(s): 18.6546 seconds
5 thread(s): 16.0776 seconds
6 thread(s): 13.6749 seconds
7 thread(s): 13.5342 seconds
8 thread(s): 13.1743 seconds
9 thread(s): 13.0149 seconds
10 thread(s): 12.5747 seconds
************************************************************************************************* """

import sys
import time
import argparse
import numpy as np
import multiprocessing

def multiply_chunk(args):
    matrix_A_chunk, matrix_B = args
    return matrix_A_chunk @ matrix_B

def main():
    parser = argparse.ArgumentParser(
        description="Performs parallel matrix multiplication using Python's multiprocessing module.",
        epilog="""Example Usage:
        python %(prog)s 3000 12 84 0
        This will multiply two 3000x3000 matrices using 12 processes.
        Matrix elements will be random integers modulo 84.
        Matrices will not be printed to the screen.""",
        formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument('dimension', type=int, help='The dimension of the square matrices.')
    parser.add_argument('threads', type=int, help='The number of parallel processes (threads) to use.')
    parser.add_argument('mod_val', type=int, help='The modulus value for initializing matrix elements.')
    parser.add_argument('print_switch', type=int, choices=[0, 1], help='Set to 1 to print matrices, 0 to suppress.')

    args = parser.parse_args()

    print(f"Initializing {args.dimension}x{args.dimension} matrices...")
    np.random.seed(42)
    matrix_A = np.random.randint(0, args.mod_val, size=(args.dimension, args.dimension), dtype=np.uint32)
    matrix_B = np.random.randint(0, args.mod_val, size=(args.dimension, args.dimension), dtype=np.uint32)
    print("Initialization complete.")

    chunks_A = np.array_split(matrix_A, args.threads, axis=0)
    tasks = [(chunk, matrix_B) for chunk in chunks_A]

    print(f"\nStarting matrix multiplication with {args.threads} processes...")
    start_time = time.perf_counter()

    with multiprocessing.Pool(processes=args.threads) as pool:
        results_list = pool.map(multiply_chunk, tasks)

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time

    print("Matrix multiplication complete.")
    print(f"Time Elapsed: {elapsed_time:.4f} seconds")

    result_matrix = np.vstack(results_list)

    if args.print_switch == 1:
        print("\n--- Input Matrix A ---")
        print(matrix_A)
        print("\n--- Input Matrix B ---")
        print(matrix_B)
        print("\n--- Result Matrix C ---")
        print(result_matrix)
    else:
        print("\nMatrix printing is suppressed (print_switch=0).")

if __name__ == '__main__':
    main()
