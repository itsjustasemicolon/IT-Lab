# Parallel Matrix Multiplication in C using Pthreads

This repository contains a C program that performs parallel matrix multiplication using the POSIX Threads (pthreads) library. The program demonstrates the performance benefits of multithreaded computation.

---

## Assignment 6: Parallel Programming Using THREAD

### Objective

The objective of this assignment is to use thread programming techniques to write a parallel program that performs matrix multiplication between two large square matrices with unsigned character elements. The program should:

- Use various `Pthread` library calls.
- Show improvement in execution time as you increase the number of threads (up to your CPU count).
- Use `gettimeofday` to measure timing (excluding matrix initialization).
- Use process listing commands (`ps`) to show that your threads are running in the system.

---

## Command-line Arguments

The program takes **four command-line arguments**:
1. `dimension` - The dimension of the square matrix.
2. `threads` - The number of threads to be created (e.g., 1, 2, 3, 4, etc.).
3. `mod_val` - The modulus value used to initialize all elements of the two input matrices.
4. `print_switch` - If `1`, input and output matrices are printed; if `0`, they are not printed.

---

## About the Program

The C program implements the assignment requirements by performing the following steps:

- Accepts four command-line arguments: matrix dimension, number of threads, modulus for random initialization, and print switch.
- Dynamically allocates memory for three square matrices (A, B, and result C).
- Initializes matrices A and B with random unsigned integer values.
- Divides the rows of matrix A among the specified number of threads.
- Each thread computes its assigned portion of the result matrix C.
- Measures execution time using `gettimeofday()`.
- Optionally prints a preview of the input and output matrices.

---

## How to Compile and Run

### Compilation

A `Makefile` is provided for convenience. To compile, simply run:
```sh
make
```
Alternatively, compile manually using gcc:
```sh
gcc -o assignment_6 assignment_6.c -pthread -O2
```
- `-pthread`: Links the POSIX threads library. (Required)
- `-O2`: Enables level 2 compiler optimizations for better performance. (Recommended)

### Execution

Run the compiled program from your terminal:
```sh
./assignment_6 <dimension> <threads> <mod_val> <print_switch>
```

#### Example

To multiply two 2000x2000 matrices using 8 threads, with elements initialized modulo 100, and suppress output printing:
```sh
./assignment_6 2000 8 100 0
```

**Sample Output:**
```
Initializing 2000x2000 matrices...
Initialization complete.

Starting matrix multiplication with 8 threads...
Matrix multiplication complete.
Time Elapsed: 2.1534 seconds

Matrix printing is suppressed (print_switch=0).
```

---

## Monitoring Thread Usage

To verify that multiple threads are running as intended, you can use the `ps` command:

1. In one terminal, run the program.
2. In a second terminal, find the Process ID (PID) of your running program:
    ```sh
    pgrep assignment_6
    ```
3. Display all threads for that PID:
    ```sh
    ps -T -p <PID>
    ```
    (Replace `<PID>` with the number from `pgrep`). You will see an entry for the main process and for each worker thread, confirming parallel execution.

---

## Source Code (`assignment_6.c`)

<details>
<summary>Click to expand full source code</summary>

```c
/**************************************************************************************************
 * Assignment No.: 6
 * Assignment    : Parallel Programming using THREAD
 * Date          : 02/09/2025
 * Group No.     : A3
 * Team No.      : 09
 * Roll No.      : 002311001004, 002311001011, 002311001049
 * Name          : Soham Das, Sarbo Sarcar, Arnob Bhakta
 * Details       : A C program that multiplies two large square matrices in parallel using
 * the pthread library. The program divides the first matrix into row chunks,
 * assigns each chunk to a separate thread for computation. The execution
 * time is measured using gettimeofday.
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

unsigned int **mat_A;
unsigned int **mat_B;
unsigned int **mat_C;
int dim;

typedef struct {
    int id;
    int start_row;
    int end_row;
} ThreadArgs;

void *multiply_chunk(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int start_row = args->start_row;
    int end_row = args->end_row;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < dim; j++) {
            mat_C[i][j] = 0;
            for (int k = 0; k < dim; k++) {
                mat_C[i][j] += mat_A[i][k] * mat_B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

void print_matrix(unsigned int **mat) {
    const int PREVIEW_SIZE = 10;
    printf("\n");

    if (dim <= PREVIEW_SIZE * 2) {
        // If the matrix is small enough (e.g., <= 20x20), print it all.
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                printf("%u ", mat[i][j]);
            }
            printf("\n");
        }
    } else {
        // Print a preview for larger matrices
        // Print top rows
        for (int i = 0; i < PREVIEW_SIZE; i++) {
            // first PREVIEW_SIZE columns
            for (int j = 0; j < PREVIEW_SIZE; j++) {
                printf("%u ", mat[i][j]);
            }
            printf("... ");
            // last PREVIEW_SIZE columns
            for (int j = dim - PREVIEW_SIZE; j < dim; j++) {
                printf("%u ", mat[i][j]);
            }
            printf("\n");
        }

        // separator for rows
        printf("...\n");

        // Print bottom rows
        for (int i = dim - PREVIEW_SIZE; i < dim; i++) {
            // first PREVIEW_SIZE columns
            for (int j = 0; j < PREVIEW_SIZE; j++) {
                printf("%u ", mat[i][j]);
            }
            printf("... ");
            // last PREVIEW_SIZE columns
            for (int j = dim - PREVIEW_SIZE; j < dim; j++) {
                printf("%u ", mat[i][j]);
            }
            printf("\n");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <dimension> <threads> <mod_val> <print_switch>\n", argv[0]);
        return 1;
    }

    dim = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    int mod_val = atoi(argv[3]);
    int print_switch = atoi(argv[4]);

    if (dim <= 0 || num_threads <= 0 || mod_val <= 0) {
        fprintf(stderr, "Error: dimension, threads, and mod_val must be positive integers.\n");
        return 1;
    }

    printf("Initializing %dx%d matrices...\n", dim, dim);

    mat_A = (unsigned int **)malloc(dim * sizeof(unsigned int *));
    mat_B = (unsigned int **)malloc(dim * sizeof(unsigned int *));
    mat_C = (unsigned int **)malloc(dim * sizeof(unsigned int *));
    for (int i = 0; i < dim; i++) {
        mat_A[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
        mat_B[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
        mat_C[i] = (unsigned int *)malloc(dim * sizeof(unsigned int));
    }

    srand(time(NULL));
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            mat_A[i][j] = rand() % mod_val;
            mat_B[i][j] = rand() % mod_val;
        }
    }
    printf("Initialization complete.\n");

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    printf("\nStarting matrix multiplication with %d threads...\n", num_threads);

    pthread_t threads[num_threads];
    ThreadArgs thread_args[num_threads];
    int rows_per_thread = dim / num_threads;

    for (int i = 0; i < num_threads; i++) {
        thread_args[i].id = i;
        thread_args[i].start_row = i * rows_per_thread;
        thread_args[i].end_row = (i == num_threads - 1) ? dim : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, multiply_chunk, &thread_args[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1e6;

    printf("Matrix multiplication complete.\n");
    printf("Time Elapsed: %.4f seconds\n", elapsed_time);

    if (print_switch == 1) {
        printf("\n--- Input Matrix A ---");
        print_matrix(mat_A);
        printf("\n--- Input Matrix B ---");
        print_matrix(mat_B);
        printf("\n--- Result Matrix C ---");
        print_matrix(mat_C);
    } else {
        printf("\nMatrix printing is suppressed (print_switch=0).\n");
    }

    for (int i = 0; i < dim; i++) {
        free(mat_A[i]);
        free(mat_B[i]);
        free(mat_C[i]);
    }
    free(mat_A);
    free(mat_B);
    free(mat_C);

    return 0;
}
```
</details>

---

**Feel free to submit issues or pull requests for improvements!**
