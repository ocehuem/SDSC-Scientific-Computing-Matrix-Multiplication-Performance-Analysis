/**
 * @file simulation.cpp
 * @brief Main program for running the heat equation simulation
 * @author [Choudari Harshitha Reddy & Mubarakpur Keerthi]
 * 
 * This program implements a numerical simulation of the 1D heat equation using
 * finite difference methods. It takes command line arguments for the simulation
 * parameters and runs the simulation using the Solution class.
 */

#include "../inc/Solution.h"
#include <cstdlib>
#include <iostream>

/**
 * @brief Main entry point for the heat equation simulation program
 *
 * @param argc Number of command line arguments (expected: 4)
 * @param argv Array of command line arguments:
 *             argv[0]: Program name
 *             argv[1]: Length of the domain
 *             argv[2]: Time step size (deltaT)
 *             argv[3]: Space step size (deltaX)
 * 
 * @return int Returns 0 on successful execution, 1 if invalid arguments provided
 * 
 * @details This program simulates heat diffusion in a 1D domain using the following parameters:
 *          - length: The total length of the domain
 *          - deltaT: Time step size for the simulation
 *          - deltaX: Space discretization step size
 *          - alpha: Thermal diffusivity (set to 1.0)
 *          - maxSteps: Maximum number of simulation steps (set to 100)
 * 
 * The program checks for correct number of command line arguments and initializes
 * the Solution class with the provided parameters. It then runs the simulation
 * using the Simulate() method.
 * 
 * Example usage:
 * @code
 *     ./simulation 1.2 0.1 0.4
 * @endcode
 */
int main(int argc, char** argv) {
    // Check if correct number of command line arguments are provided
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <length> <deltaT> <deltaX>" << std::endl;
        return 1;
    }

    // Convert command line arguments to appropriate data types
    double length = atof(argv[1]);   // Domain length
    double deltaT = atof(argv[2]);   // Time step size
    double deltaX = atof(argv[3]);   // Space step size

    // Initialize the solver with simulation parameters
    // Using alpha = 1.0 (thermal diffusivity) and maxSteps = 100
    Solution solver(length, deltaX, deltaT, 1.0, 100);

    // Run the simulation
    solver.Simulate();

    return 0;
}
