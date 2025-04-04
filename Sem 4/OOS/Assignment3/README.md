# Assignment #3

## Overview
This assignment involves working with Java generics and reflection. You will implement generic methods and classes to perform sorting, frequency counting, and duplicate detection on arrays of any data type. Additionally, you will explore Java's reflection API to dynamically inspect and manipulate class properties and methods at runtime.

## Tasks

### 1. Generic Sorting Method
- Implement a generic method in Java that accepts an array of any data type.
- Sort the array in ascending order using any sorting algorithm (e.g., Bubble Sort, QuickSort, MergeSort).

### 2. Generic Frequency Counter
- Implement a generic method in Java that accepts an array of any data type.
- Find the frequency of each unique element in the array and return the result in a suitable data structure (e.g., `Map<T, Integer>`).

### 3. Generic Duplicate Finder
- Create a generic Java class with a method that accepts an array of any data type.
- Identify and print all duplicate elements present in the array.

### 4. Java Reflection API Testing
- Explore and test different Java reflection APIs.
- Implement code to demonstrate the usage of:
  - `getClass()`
  - `getMethods()`
  - `getConstructors()`
  - `getDeclaredMethod()`
  - `getDeclaredField()`
  - `setAccessible()`

## How to Run
1. Implement the required methods and classes.
2. Create a `main` method to test each functionality.
3. Compile and run the Java program to verify correct behavior.

## Expected Output
- A sorted array for Task 1.
- A frequency map for Task 2.
- A list of duplicate elements for Task 3.
- Output showcasing Java reflection capabilities for Task 4.

## Notes
- Ensure proper use of Java Generics (`<T>`).
- Use appropriate data structures (`List`, `Map`, etc.).
- Handle edge cases (empty arrays, null values, etc.).
- Use `setAccessible(true)` cautiously when accessing private fields and methods.

## Submission Guidelines
- Submit the Java source files (`.java` files) with well-documented code.
- Include sample input and expected output in comments.
- Ensure the code is properly formatted and follows Java conventions.

Happy Coding! 🚀
