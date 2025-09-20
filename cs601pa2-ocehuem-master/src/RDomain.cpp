/**
 * @file RDomain.cpp
 * @brief Implementation of the RDomain class for rectangular domain discretization
 * @details This class implements a rectangular computational domain with uniform
 *          grid spacing in both x and y directions. The domain is defined on
 *          [0, length] x [0, length] with specified grid spacing.
 */

#include "../inc/RDomain.h"
#include <cstdio>
#include <cassert>

/**
 * @brief Constructs a rectangular domain with specified length and grid spacing
 * @param len The length of the domain in both x and y directions
 * @param dx The uniform grid spacing
 * @throws assertion error if len <= 0 or dx <= 0
 * @details Creates a square/rectangular domain [0, len] x [0, len] with uniform
 *          grid spacing dx. The grid points are generated along both x and y
 *          directions, creating a structured rectangular grid.
 */
RDomain::RDomain(double len, double dx) : length(len), delta(dx) {
    assert(len > 0 && dx > 0 && "Length and step size must be positive.");
    GenerateGrid();
}

/**
 * @brief Generates the grid points for the domain
 * @details Creates uniformly spaced grid points in both x and y directions:
 *          - Clears any existing grid points
 *          - Generates points from 0 to length with spacing delta
 *          - Creates identical grids for x and y (for rectangular domains)
 *          - Number of points in each direction is floor(length/delta) + 1
 * 
 * The grid points are stored in two separate vectors:
 * - gridX: coordinates along x-direction
 * - gridY: coordinates along y-direction (identical to gridX for square domains)
 */
void RDomain::GenerateGrid() {
    gridX.clear();
    for (double x = 0; x <= length; x += delta) {
        gridX.push_back(x);
    }
    

 if (gridX.back() != length) {
        gridX.push_back(length);
    }
    gridY = gridX; // Assuming square domain, Y-coordinates identical to X-coordinates
}

/**
 * @brief Writes the grid coordinates to a binary file
 * @param outputFileName Name of the file to write the grid data
 * @throws assertion error if file cannot be opened
 * @details Writes the grid coordinates to a binary file in the following format:
 *          - First writes all x-coordinates (sizeof(double) * nx bytes)
 *          - Then writes all y-coordinates (sizeof(double) * ny bytes)
 *          where nx and ny are the number of points in x and y directions.
 * 
 * The binary format allows for efficient I/O and exact representation of
 * floating-point values.
 */
void RDomain::PrintGrid(const std::string &outputFileName) const {
    FILE *fp = fopen(outputFileName.c_str(), "wb");
    assert(fp && "Failed to open file.");
    fwrite(gridX.data(), sizeof(double), gridX.size(), fp);
    fwrite(gridY.data(), sizeof(double), gridY.size(), fp);
    fclose(fp);
}

/**
 * @brief Updates the grid spacing and regenerates the grid
 * @param dx New grid spacing value
 * @throws assertion error if dx <= 0
 * @details Changes the grid spacing and regenerates the entire grid:
 *          - Validates the new spacing value
 *          - Updates the internal delta member
 *          - Regenerates grid points with new spacing
 *          - Maintains the same domain length
 * 
 * This method can be used to refine or coarsen the grid while
 * maintaining the same physical domain size.
 */
void RDomain::SetStepSize(double dx) {
    assert(dx > 0 && "Step size must be positive.");
    delta = dx;
    GenerateGrid();
}
