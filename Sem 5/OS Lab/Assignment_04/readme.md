# Assignment – 4  
**Total Marks:** 10 [CO2]  
**Topic:** `mmap` and Page Fault Observation  

---

## Objective  
The objective of this programming assignment is to **use the `mmap()` system call** and **observe page faults** using the `sar` command.  

---

## Requirements  

1. **File Creation**  
   - Create a **large file (~8GB)** using the `fallocate` command.  
   - Write a **single byte value (X)** at a specific **offset (F)** in this file.  
   - Both **X** and **F** should be generated randomly:  
     - `X` → Value between **0–255**.  
     - `F` → Offset between **0–8GB**.  

2. **Memory Mapping (`mmap`)**  
   - Map the created file into the **virtual address space** using the `mmap()` system call.  
   - Read data back from the **same offset (F)**.  

3. **Verification**  
   - Compare the written value `X` and the read value `X'`.  
   - If they **do not match**, print an **error message** and **terminate the program**.  
   - Display the offset (`F`) in **hexadecimal format**.  

4. **Continuous Execution**  
   - Perform the **write → read → verify** sequence inside an **infinite loop**.  

5. **Page Fault Observation**  
   - In a separate terminal, run the following command **before starting the program**:  
     ```bash
     sar -B 1
     ```  
   - This will display **page fault statistics**.  
   - Once the program starts execution, the **page fault count should increase**.  

---

## Output and Documentation  

- The **program output** and the **`sar` command output** must be pasted as a **comment block at the beginning of your program file** (as per the assignment guidelines).  

---

## Example Workflow  

1. **Create a large file (~8GB)**:  
   ```bash
   fallocate -l 8G bigfile.bin

---

why not use char ? 
> char in c is signed so better use unsigned char


why use time for seeding ? 
otherwise everytime we start the program it will generate the same sequence of randomness


what is this 
```
size_t rand_off = ((size_t)rand() <<31 | rand() )% FILE_SIZE;
```
rand() -> 31 bit unsigned inter 
to use full 8gb we need 64 bit unsigned int
size_t is unsigned 64 bit usually
solution :
1. (size_t)rand() -> converts `31 bit rand()` to `62 bit number` but with lower 31 bits having random values
2. (size_t)rand()<<31 -> shifting the lower 31 random bits to the upper 31 bits
3. (size_t)rand()<<31 | rand() -> unsigned 64 bit with more random lower 31 bits flipped
4. % FILE_SIZE -> puts it in the 8GB range
