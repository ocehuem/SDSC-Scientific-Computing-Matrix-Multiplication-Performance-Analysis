/**
 * @file Solution.h
 * @brief Defines the Solution class for solving thermal diffusion problems
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include "RDomain.h"
#include "GridFn.h"

/**
 * @class Solution
 * @brief Manages the numerical solution of a 2D thermal diffusion problem
 * 
 * This class implements a solver for the 2D heat equation:
 * ∂u/∂t = α∇²u
 * where α is the thermal diffusivity coefficient.
 * The solution is computed on a rectangular domain using
 * numerical methods (likely finite differences).
 */
class Solution {
private:
    RDomain domain;      ///< Computational domain for the simulation
    GridFn gridFunction; ///< Grid function storing the temperature distribution
    double alpha;        ///< Thermal diffusivity coefficient
    double deltaT;       ///< Time step size
    int maxSteps;        ///< Maximum number of time steps to simulate

public:
    /**
     * @brief Constructs a thermal diffusion problem solver
     * 
     * @param len Domain length (creates a len x len square domain)
     * @param dx Spatial grid spacing
     * @param dt Time step size
     * @param thermalDiff Thermal diffusivity coefficient (α)
     * @param steps Maximum number of time steps to simulate
     * 
     * @throws std::invalid_argument If any of the following conditions are met:
     *         - len <= 0: Invalid domain size
     *         - dx <= 0: Invalid spatial step
     *         - dt <= 0: Invalid time step
     *         - thermalDiff <= 0: Invalid thermal diffusivity
     *         - steps <= 0: Invalid number of steps
     * 
     * @note The stability condition for the explicit scheme requires:
     *       dt <= (dx²)/(4α) in 2D
     */
    Solution(double len, double dx, double dt, double thermalDiff, int steps);

    /**
     * @brief Executes the thermal diffusion simulation
     * 
     * Performs the time integration of the heat equation for the specified
     * number of time steps or until steady state is reached (if implemented).
     * The solution is updated in the gridFunction member variable.
     * 
     * @note The simulation uses an explicit time integration scheme
     *       (likely forward Euler) with central differences for spatial derivatives.
     * 
     * @throws std::runtime_error If numerical instabilities are detected
     *         during the simulation
     */
    void Simulate();
};

#endif // SOLUTION_H
