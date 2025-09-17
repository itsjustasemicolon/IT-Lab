# Shared Memory and Thread Synchronization Program

## Overview
This program demonstrates the use of shared memory and thread synchronization in C. It creates a shared memory segment to store arrays of `X` and `Y` values, along with the results of the computations `A`, `B`, and `C`. These computations are performed by three separate threads:
1. **Thread A** computes `A = X * Y`.
2. **Thread B** computes `B = 2 * X + 2 * Y + 1`.
3. **Thread C** computes `C = B / A`, ensuring that division by zero is handled.

The threads synchronize through a shared memory structure and condition variables, ensuring that each phase (A, B, C) is executed for all `X`, `Y` pairs before moving to the next phase.

### Program Features
- Uses **shared memory** (`shmget`, `shmat`) to store values of `X`, `Y`, `A`, `B`, and `C`.
- Synchronizes threads using **mutexes** and **condition variables** to ensure proper execution order.
- Allows for an arbitrary number of pairs `X` and `Y` passed via command line input.
- Computes the values in parallel using threads, then outputs the results.

## Dependencies
- POSIX threads (pthread) for thread management.
- POSIX shared memory (`shmget`, `shmat`, `shmdt`) for inter-process communication.

## Compilation
To compile the program, use the following command:

```bash
gcc A3_09_5.c -o A3_09_05 -lpthread
