/**
 * @file GridFn.h
 * @brief Definition of GridFn class for grid function calculations
 * 
 * This file defines the GridFn class which handles grid functions for
 * finite element calculations. It manages discretized values over a grid
 * with specified length and spacing.
 */

#ifndef GRIDFN_H
#define GRIDFN_H

#include <vector>

/**
 * @class GridFn
 * @brief Class for managing grid functions and their values
 * 
 * GridFn handles the discretization and evolution of functions on a grid.
 * It maintains a vector of values at grid points and provides methods for
 * initialization and updating these values.
 */
class GridFn {
private:
    double length;    ///< Total length of the grid domain
    double deltaX;    ///< Grid spacing (distance between grid points)
    std::vector<double> values;  ///< Vector storing function values at grid points

public:
    /**
     * @brief Construct a grid function with specified domain and spacing
     * 
     * @param len Total length of the domain
     * @param dx Grid spacing (distance between grid points)
     */
    GridFn(double len, double dx);

    /**
     * @brief Initialize the grid function values
     * 
     * Sets initial values for the grid function according to
     * problem-specific requirements.
     */
    void Initialize();

    /**
     * @brief Update grid function values
     * 
     * Updates the function values based on given parameters,
     * typically used in time-stepping schemes.
     * 
     * @param alpha Coefficient for the update calculation
     * @param deltaT Time step size
     */
    void Update(double alpha, double deltaT);

    /**
     * @brief Get the current grid function values
     * 
     * @return const std::vector<double>& Reference to the vector of values
     */
    const std::vector<double>& GetValues() const;
};

#endif // GRIDFN_H
