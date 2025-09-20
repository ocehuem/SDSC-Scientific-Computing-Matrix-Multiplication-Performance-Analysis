CS601: Scientific Computing – Grid-Based PDE Solver

Developed generalized software for computations on grids, implementing RDomain, GridFn, and Solution classes to model 1D heat diffusion using three-point stencils.

Applied object-oriented design, file I/O (binary output), and numerical methods for PDE approximation over arbitrary rectangular and 1D domains.

Tools & Frameworks: C++, Makefile, Doxygen, Bash scripting, Git/GitHub.

Concepts: Grid-based numerical computation, PDE solving, modular software design, time-stepping, boundary conditions.

# CS601 PA2: Software Development for Computation on Grids

## 📌 Overview
This assignment focuses on **grid-based numerical computation**. The goal is to design a modular software solution for solving PDEs over grids, including **rectangular and 1D domains**, with file-based output and visualization-ready data.

## 📌 Project Components

### Part I – Documentation and Code Comments
- Modified **FEMain.cpp** and provided starter files in `inc/` and `src/`.  
- Added **code comments** and generated documentation using **Doxygen**.  
- Ensured all functions, classes, and methods are clearly documented for maintainability.

### Part II – Grid-Based Numerical Software
1. **RDomain Class**
   - Subclass of `Domain`, generates **1D and rectangular grids**.  
   - Implements `PrintGrid` for writing **binary output** of X/Y coordinates.  
   - Supports user-defined **space-step(s)** for grid discretization.

2. **GridFn Class**
   - Implements **grid function modeling 1D heat diffusion** using **three-point stencil**.  
   - Handles initial conditions: \( f(x) = x^p (l - x) \) and constant boundary temperatures.

3. **Solution Class**
   - Numerically approximates PDE solutions using `RDomain` and `GridFn`.  
   - Supports **time-stepping** as a separate parameter, with iterative computation until convergence or max steps.  
   - Configurable **boundary conditions** and thermal diffusivity.

### Automation
- **Makefile** commands:  
  - `make team` – Prints team info  
  - `make part2` – Builds Part II source code  
  - `make doc` – Builds Doxygen documentation  
- **Shell script (`runme`)** automates execution with arguments: `length l`, `time-step δt`, and `space-step δx`.

## 📌 Tools & Frameworks
- **Programming:** C++  
- **Build & Automation:** Make, Makefile  
- **Documentation:** Doxygen  
- **Scripting:** Bash  
- **Version Control:** Git, GitHub  

## 📌 Concepts Covered
- Grid-based numerical computation  
- PDE solving (1D heat diffusion)  
- Object-oriented software design  
- Time-stepping and boundary condition management  
- File I/O with binary output  
- Modular and maintainable software architecture  

## 📌 Usage
1. Clone the repository:
```bash
git clone git@github.com:IITDhCSE/CS601PA2-<your-username>.git
cd CS601PA2
