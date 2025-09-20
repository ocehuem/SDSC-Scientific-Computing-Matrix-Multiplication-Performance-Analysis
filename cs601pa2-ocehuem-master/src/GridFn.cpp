/**
 * @file GridFn.cpp
 * @brief Implementation of the GridFn class for numerical grid functions
 * @details This class implements a grid function that discretizes a continuous function 
 *          over a uniform grid and provides methods for numerical integration and 
 *          time evolution using finite difference methods.
 */

#include "../inc/GridFn.h"
#include <cmath>
#include <cassert>

/**
 * @brief Constructs a GridFn object with specified domain length and grid spacing
 * @param len The length of the domain [0, len]
 * @param dx The grid spacing (step size)
 * @throws assertion error if len <= 0 or dx <= 0
 * @details Initializes a grid function over the domain [0, len] with uniform spacing dx.
 *          The initial condition is set to f(x) = x * sqrt((len - x)^3), which satisfies
 *          zero boundary conditions at x = 0 and x = len.
 */
GridFn::GridFn(double len, double dx) : length(len), deltaX(dx) {
    assert(len > 0 && dx > 0 && "Length and step size must be positive.");
    Initialize();
}

/**
 * @brief Initializes the grid function with the initial condition
 * @details Creates a uniform grid with spacing deltaX over [0, length] and sets
 *          the initial values according to f(x) = x * sqrt((length - x)^3).
 *          Explicitly enforces zero boundary conditions at the endpoints.
 *          The number of grid points is calculated as (length/deltaX) + 1.
 */
void GridFn::Initialize() {
    int numPoints = static_cast<int>(length / deltaX) + 2;
    values.resize(numPoints);

    for (int i = 0; i < numPoints; ++i) {
        double x = i * deltaX;
        values[i] = x * sqrt(length - x) * (length - x); // f(x) = x * sqrt((l - x)^3)
    }

    values[0] = 0.0;
    values[numPoints - 1] = 0.0;
}

/**
 * @brief Updates the grid function using an explicit finite difference scheme
 * @param alpha The diffusion coefficient
 * @param deltaT The time step size
 * @details Implements one time step of the heat equation using the explicit method:
 *          u(x,t+dt) = u(x,t) + alpha * (dt/dx^2) * [u(x-dx,t) - 2u(x,t) + u(x+dx,t)]
 *          
 *          The method maintains zero boundary conditions and uses a temporary vector
 *          to ensure all updates are based on the previous time step's values.
 *          
 *          For numerical stability, the following condition should be satisfied:
 *          alpha * deltaT / (deltaX * deltaX) <= 0.5
 */
void GridFn::Update(double alpha, double deltaT) {
    std::vector<double> newValues = values;
    for (size_t i = 1; i < values.size() - 1; ++i) {
        newValues[i] = values[i] + alpha * deltaT / (deltaX * deltaX) *
            (values[i - 1] - 2 * values[i] + values[i + 1]);
    }
    values = newValues;
}

/**
 * @brief Returns a const reference to the grid function values
 * @return Const reference to the vector containing the grid function values
 * @details Provides read-only access to the internal vector storing the
 *          discretized function values at grid points.
 */
const std::vector<double>& GridFn::GetValues() const {
    return values;
}
