/**
 * @file Solution.cpp
 * @brief Implementation of the Solution class for heat equation simulation
 * @author [Choudari Harshitha Reddy & Mubarakpur Keerthi]
 * 
 * This file contains the implementation of the Solution class methods which
 * handle the numerical solution of the 1D heat equation using finite difference methods.
 */

#include "../inc/Solution.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
/**
 * @brief Constructs a Solution object with specified simulation parameters
 *
 * @param len Length of the spatial domain
 * @param dx Spatial step size (delta x)
 * @param dt Temporal step size (delta t)
 * @param thermalDiff Thermal diffusivity coefficient (alpha)
 * @param steps Maximum number of time steps for simulation
 * 
 * @details This constructor initializes the simulation domain and grid function
 * with the specified parameters. It sets up:
 * - The spatial domain using RDomain
 * - The grid function for temperature values using GridFn
 * - Simulation parameters including thermal diffusivity and time step
 * 
 * The stability condition (CFL condition) should be satisfied:
 * alpha * dt / (dx * dx) <= 0.5
 */
Solution::Solution(double len, double dx, double dt, double thermalDiff, int steps)
    : domain(len, dx),         // Initialize the domain
      gridFunction(len, dx),   // Initialize the grid function
      alpha(thermalDiff),      // Set thermal diffusivity
      deltaT(dt),              // Set time step
      maxSteps(steps) {}       // Set maximum simulation steps

/**
 * @brief Executes the heat equation simulation
 * 
 * @details This method performs the following steps:
 * 1. Runs the simulation for the specified number of time steps
 * 2. Updates the grid function at each time step using the explicit scheme
 * 3. Prints the final temperature values at each spatial point
 * 
 * The simulation uses an explicit finite difference scheme:
 * u(x,t+dt) = u(x,t) + alpha * dt/dx^2 * [u(x+dx,t) - 2u(x,t) + u(x-dx,t)]
 * 
 * The results are output to standard output in the format:
 * x[i] = value
 * where i is the grid point index and value is the temperature at that point
 */


void Solution::Simulate() {
    double maxError = std::numeric_limits<double>::max(); // Initial max error
    std::vector<double> previousValues;

const auto& currentValues = gridFunction.GetValues();

    // Print the grid size
    std::cout << "Number of grid points: " << currentValues.size() << std::endl;
    // Perform time-stepping for the simulation
    for (int step = 0; step < maxSteps; ++step) {
        // Store the previous values to compute the error
        previousValues = gridFunction.GetValues();
        
        // Update the grid function (compute the next time step)
        gridFunction.Update(alpha, deltaT);
        
        // Get the current temperature values
        const auto& currentValues = gridFunction.GetValues();

        // Compute the maximum error (difference between previous and current)
        maxError = 0.0;
        for (size_t i = 0; i < currentValues.size(); ++i) {
            double error = std::abs(currentValues[i] - previousValues[i]);
            if (error > maxError) {
                maxError = error;
            }
        }

        // Output the current step's information
        std::cout << "step " << step << " max error= " << maxError;
        for (size_t i = 0; i < currentValues.size(); ++i) {
            std::cout << ", Grid[" << i << "]=" << currentValues[i];
        }
        std::cout << std::endl;

        // Check for convergence (if max error is below a certain threshold)
        if (maxError < 1e-6) {
            std::cout << "Solution converged XCoordinates= ";
            for (size_t i = 0; i < currentValues.size(); ++i) {
                // Manually compute the X-coordinate using delta
                double xCoordinate = i * domain.GetDelta();  // Use delta directly
                std::cout << xCoordinate << " ";
            }
            std::cout << ", YCoordinates= ";
            for (size_t i = 0; i < currentValues.size(); ++i) {
                std::cout << currentValues[i] << " ";
            }
            std::cout << std::endl;
            break; // Exit the loop if the solution has converged
        }
    }
}
