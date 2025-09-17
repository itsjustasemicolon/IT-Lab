# Avoiding Deadlocks using Thread Programming

## Description
This C program avoids deadlock using Pthreads, by manipulating three global variables (`Total_1`, `Total_2`, `Total_3`) with four threads (`Th1`, `Th2`, `Th3`, `Th4`). The threads perform random transfers between the totals, and the order of locking mutexes is carefully controlled to avoid deadlocks. However, for testing purposes, the code can also be modified to introduce a deadlock scenario by changing the mutex lock order.

The program runs indefinitely, printing the values of `Total_1`, `Total_2`, and `Total_3`, as well as the grand total, at regular intervals.

## Program Overview
The four threads perform the following tasks:

- **Thread 1 (Th1)**: Subtracts a random amount (1-10) from `Total_1` and adds it to either `Total_2` or `Total_3`.
- **Thread 2 (Th2)**: Subtracts a random amount (1-20) from `Total_2` and adds it to either `Total_1` or `Total_3`.
- **Thread 3 (Th3)**: Subtracts a random amount (1-30) from `Total_3` and adds it to either `Total_1` or `Total_2`.
- **Thread 4 (Th4)**: Prints the current values of `Total_1`, `Total_2`, `Total_3`, and the grand total at regular intervals.

## Compilation and Execution

### Compilation Command

```shell
gcc A3_09_7.c -o A3_09_7 -pthread
```

### Execution Command
```shell
./A3_09_7
```

### Input:
- No input is required during execution. The program will run indefinitely and print the totals.

### Output:
- The program prints the values of `Total_1`, `Total_2`, `Total_3`, and the grand total to the console at regular intervals.

Example output:

```markdown
Total_1: 99993, Total_2: 100017, Total_3: 99990, Grand Total: 300000
Total_1: 100409, Total_2: 99893, Total_3: 99698, Grand Total: 300000
Total_1: 100866, Total_2: 99846, Total_3: 99288, Grand Total: 300000
Total_1: 101377, Total_2: 99823, Total_3: 98800, Grand Total: 300000
Total_1: 101558, Total_2: 99963, Total_3: 98479, Grand Total: 300000
Total_1: 101924, Total_2: 100004, Total_3: 98072, Grand Total: 300000
Total_1: 102242, Total_2: 100003, Total_3: 97755, Grand Total: 300000
Total_1: 102599, Total_2: 100185, Total_3: 97216, Grand Total: 300000
...
```

## Code Explanation

### Locking Mechanism
The program uses `pthread_mutex_t` to protect the shared global variables (`Total_1`, `Total_2`, `Total_3`). The locking order is crucial to prevent deadlocks. The `lock_in_order` and `unlock_in_order` functions ensure that the mutexes are locked and unlocked in a consistent order based on their memory addresses.

### Deadlock Scenario
By modifying the lock order in **Thread 1** (`lock_in_order(&mutex2, &mutex1)`), a circular wait condition is introduced:

1. **Thread 1** locks `mutex2` and then `mutex1`.
2. **Thread 2** locks `mutex3` and then `mutex2`.
3. **Thread 3** locks `mutex1` and then `mutex3`.

This causes the threads to wait for each other indefinitely, resulting in deadlock.

## Requirements
- C Compiler (GCC recommended)
- Pthreads library (`-pthread` flag during compilation)
- Standard Linux environment for testing (can be run on other Unix-like systems)

## Troubleshooting
- If the program freezes, it is likely due to the intentional deadlock.
- Ensure that the mutex initialization and the threading system are correctly configured.

## License
This program is provided for educational purposes and is free to use and modify.
