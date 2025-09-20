CS601 End-Semester Assignment – Custom C++ Container
Implemented a generic container class supporting element indexing and custom concatenation operations, validated with assertions. Applied operator overloading, memory-safe programming, and structured C++17 template usage.


*This is an individual assignment. You must not discuss / share your solution with others.*

# CS601 End-Semester Assignment: Custom Container Operations

## 📌 Overview
This assignment focuses on **custom container implementation, operator overloading, and memory-safe programming in C++**. It consists of multiple operations on a template container class `MyContainer<T>`:

1. Extend `MyContainer` to support **element assignment and indexing**.  
2. Implement **custom addition operator** to concatenate a string to elements.  
3. Ensure correctness using **assertions** and track lines of code added.  

## 📌 Project Components

### Question 1 – Element Assignment (`mycontainer.h`)
- Modified the template class `MyContainer` to support **assignment and indexing**.  
- Allowed storing and accessing elements using `[]` operator.

### Question 2 – Custom Operations (`mycontainer.cpp`)
- Added support for **element concatenation via operator `+`**.  
- Ensured correct update of existing elements without memory leaks.  
- Verified behavior with **assertions** in `main.cpp`.

### Question 3 – Declaration & Academic Honesty
- Tracked **lines of code added** using `numLinesOfCodeAdded`.  
- Output includes contributor declaration for transparency.

### Execution
Build and run the program using the following commands:
```bash
g++ -std=c++17 main.cpp mycontainer.cpp -o endsem_part2
./endsem_part2
```
📌 Deliverables

mycontainer.h – Modified template class header.

mycontainer.cpp – Implementation of required operations.

main.cpp – Test driver (DO NOT MODIFY).

Output showing lines of code added and assertion validation.

📌 Tools & Frameworks

Programming: C++17

Build & Automation: g++ compiler

Debugging & Verification: Assertions, memory-safe programming

Version Control: Git, GitHub

📌 Concepts

Template classes in C++

Operator overloading ([], +)

Memory management and safe programming practices

Automated testing with assertions

- This repository contains 4 files: `main.cpp`, `mycontainer.cpp`, `mycontainer.h`, and `makefile`.
- You must not modify `main.cpp`. Doing so will fetch you a zero in this assignment.
- You must not add any additional file(s) to this repository. Doing so will fetch you a zero in this assignment.
- Open `main.cpp` to see the questions and answer accordingly.

Submission Instructions
*The submission instructions for turning in this exam is similar to what you have been following for homework/programming assignments.*
 
After you are done making edits to the files: 
1. You must save the changes by committing the files in your local repository (use `git add` and `git commit` commands for this.) 
2. You must push the saved changes to GitHub.com (use `git push` command for this)
3. You must tag the saved changes (use `git tag -a cs601endsemsubmission -m "Submitting exam"` command)
4. You must push the saved tags to GitHub.com (use `git push --tags` command)

