# ASSIGNMENT – 2
## IPC/SYNCHRONIZATION

---

### **A. SIGNAL Handling (3 Marks) [CO3]**

Catch the signal `SIGINT` and display “Ha Ha, Not Stopping”.  
Use the `signal` system call. Always use `perror` to check the return status of a library/system call.

---

### **B. IPC using Named Pipe (FIFO) (7 Marks) [CO5]**

- Using the `fork` system call, create a Child Process.
- Transfer **1GB file** from the Parent Process to Child Process using a **FIFO**.
- Now, transfer the same file from the Child Process to the Parent Process using another FIFO.
- Now, compare the two files (use `cmp` or `diff` command) to make sure that the same file has returned back.
- Also, print the time required to do this double transfer.
- Attach this output to the source file as a comment.

Additional Instructions:
- To create FIFO, you can either use a shell command or a system call.
- To create a large file, you can use the relevant command.
- Use `ls –l` command to show the FIFO and the large file. Attach this output to the source file as a comment.
- Make sure that the starting comment block has all the necessary information attached.
