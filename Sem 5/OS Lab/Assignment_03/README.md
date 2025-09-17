# Assignment – 3  
**Total Marks:** 10 [CO4]  
**Topic:** Parallel Programming in Python  

---

## Objective  
The goal of this assignment is to write a **parallel program in Python** that performs **Matrix Multiplication** between two large square matrices with **unsigned integer elements**. Additionally, you need to measure the **time elapsed** for computation.  

---

## Requirements  

1. **Matrix Specifications**
   - Both matrices must be **square** and **large enough** (at least **3000 x 3000**).  
   - Matrices must be **dynamically allocated** to fit in available memory.  
   - Elements should be initialized with **random numbers** (using modulo operator with a given value).  

2. **Parallel Execution**
   - Use **Python multiprocessing** (not `threading`) to parallelize the multiplication.  
   - As the number of **parallel processes (threads)** increases (up to the number of CPUs), execution time should **improve**.  
   - Use a **high-resolution timer** such as `time.perf_counter()` to measure execution time.  
   - **Matrix initialization time should not be included** in the measurement.  

3. **Performance Monitoring**
   - Show CPU utilization using **`cpustat`** or **`sar`**.  
   - Attach these outputs along with the timing information in the **starting comment block** of your source file.  

---

## Command Line Arguments  

Your program should accept **four arguments** in the following order:  

1. **Matrix Dimension**  
   - Dimension `N` of the square matrix (`N x N`).  

2. **Number of Parallel Threads**  
   - Example: `1, 2, 3, 4, ...`  
   - Determines how workload will be divided among CPUs.  

3. **Modulo Value (`mod`)**  
   - Used to initialize elements of the two input matrices.  

4. **Print Switch**  
   - `1` → Print input matrices and the result matrix.  
   - `0` → Do not print matrices.  

---

## Example Usage  

```bash
python matrix_multiplication.py 3000 4 100 0
