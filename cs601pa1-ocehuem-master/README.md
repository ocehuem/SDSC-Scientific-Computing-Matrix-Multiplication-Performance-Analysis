

CS601: Scientific Computing – Matrix Multiplication & Performance Analysis

Developed multiple matrix multiplication implementations (all loop orderings) and matrix-vector multiplication using BLAS library functions and SSE/SSE3 intrinsics.

Analyzed performance with Valgrind Cachegrind, optimizing for cache efficiency and floating-point operations.

Tools & Frameworks: C++, Makefile, BLAS, SSE/SSE3 intrinsics, Valgrind, Git/GitHub.

Concepts: Loop ordering, conditional compilation, vectorization, profiling, high-performance computing.

# CS601 PA1: Scientific Computing – Matrix Multiplication and Performance Analysis

## 📌 Overview
This assignment focuses on hands-on experience with **high-performance computing techniques**, including Makefile usage, library functions, compiler intrinsics, and memory profiling. The objective is to implement, optimize, and analyze matrix and matrix-vector operations for efficiency.

## 📌 Project Components

### 1. Matrix Multiplication (`matmul.cpp`)
- Implemented all possible **loop orderings** (ijk, ikj, jik, jki, kij, kji) for square matrices.  
- Supports **single-precision (`-DSINGLE`) and double-precision (`-DDOUBLE`)** data.  
- Integrated with **Makefile commands** for build and run (`make build_matmul_single`, `make run_matmul_single`, etc.).  
- Collected execution times and **last-layer cache read misses** using Valgrind Cachegrind.

### 2. BLAS-based Matrix Operations
- Implemented **matrix multiplication** using **BLAS dot-product** and **sgemm** functions.  
- Tabulated execution times and cache metrics for single-precision matrices.

### 3. Matrix-Vector Multiplication (`matvec.cpp`)
- Used **Intel SSE3 intrinsics** (_mm_load_ps, _mm_store_ps, etc.) for vectorized matrix-vector products.  
- Implemented **loop unrolling** for inner loops to leverage SIMD parallelism.  
- Performance analysis conducted with **Valgrind Cachegrind**.

## 📌 Tools & Frameworks
- **Programming:** C++  
- **Build & Automation:** Make, Makefile, Conditional Compilation  
- **Libraries & Intrinsics:** BLAS, SSE3, x86 intrinsics  
- **Profiling & Analysis:** Valgrind Cachegrind  
- **Version Control:** Git, GitHub

## 📌 Concepts Covered
- Loop ordering and its impact on performance  
- SIMD vectorization and compiler intrinsics  
- Cache-aware programming and profiling  
- Conditional compilation for flexible builds  
- High-performance numerical computing  

## 📌 Usage
1. Clone the repository:
```bash
git clone git@github.com:IITDhCSE/CS601PA1-<your-username>.git
cd CS601PA1
