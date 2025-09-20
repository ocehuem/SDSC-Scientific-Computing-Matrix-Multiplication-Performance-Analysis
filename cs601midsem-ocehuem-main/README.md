CS601: Scientific Computing – Cache Optimization & Matrix Debugging

Optimized array summation program (sum11.c → sum12.c) to achieve zero last-layer cache misses by inspecting cache hierarchy and modifying array sizes.

Debugged and corrected matrix diagonal summation program (sumdiagonal.cpp) using GDB and Valgrind, ensuring memory safety and correctness.

Added Doxygen documentation with @brief, @bug, @author, @file, @fn, @param directives for maintainable, error-free code.

Tools & Frameworks: C, C++, Valgrind, GDB, Doxygen, Makefile, Git/GitHub.

Concepts: Cache hierarchy analysis, memory optimization, debugging, numerical correctness, automated documentation generation.

# CS601 Mid-Semester Assignment: Cache Optimization & Matrix Debugging

## 📌 Overview
This assignment focuses on **cache-aware programming, memory optimization, and debugging**. It consists of two questions:

1. **Cache Optimization:** Modify `sum11.c` to reduce last-layer cache misses to zero.  
2. **Matrix Debugging:** Correct and document the `sumdiagonal.cpp` program to compute the sum of diagonal elements correctly.

## 📌 Project Components

### Question 1 – Array Summation (`sum11.c` / `sum12.c`)
- Original program `sum11.c` allocates an array of **U = 10 million** elements and sums **N = 75 million** random elements.  
- Measured **first-layer (L1) and last-layer (LL) cache misses** using **Valgrind Cachegrind**.  
- Modified program `sum12.c` to optimize for **zero last-layer cache misses** by adjusting `U` and `N` after inspecting local cache hierarchy:
```bash
lscpu | grep "L1d\|L2\|L3"    # Command to inspect cache sizes
valgrind --tool=cachegrind ./sum12
```
- Screenshots of cache misses and hierarchy are included in 1.pdf.

### Question 2 – Matrix Diagonal Summation (sumdiagonal.cpp)

- Corrected all compiler, linker, runtime, and logic errors in sumdiagonal.cpp.
- Used GDB for debugging and Valgrind to detect and fix memory errors.
- Added Doxygen comments including @brief, @bug, @author, @file, @fn, and @param directives.
- Build and execute using Makefile2 target sumdiagonal.
- Generate documentation with:
	make -f Makefile2 DOCS=1

## 📌 Deliverables

Makefile1: Targets q11 (build/run sum11.c) and q12 (build/run sum12.c with Valgrind).

sum12.c – Optimized array summation program.

1.pdf – Writeup with screenshots of cache miss results and cache sizes.

Makefile2 – Builds sumdiagonal and optionally generates documentation.

Modified source files for Question 2 (sumdiagonal.cpp and Doxygen files).

📌 Tools & Frameworks

Programming: C, C++

Build & Automation: Make, Makefile

Profiling & Debugging: Valgrind Cachegrind, GDB

Documentation: Doxygen

Version Control: Git, GitHub

📌 Concepts

Cache hierarchy analysis and optimization

Memory-safe programming and debugging

Randomized array access and performance measurement

Numerical computation and object-oriented C++ programming

Automated documentation generation using Doxygen

📌 Submission

Tag the repository for grading:

git tag -a cs601midsemsubmission -m "CS601 Mid-Semester Submission"
git push --tags
