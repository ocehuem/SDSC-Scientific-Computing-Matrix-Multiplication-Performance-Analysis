/**
 * @file RDomain.h
 * @brief Defines the RDomain class for managing a rectangular computational domain
 */
#ifndef RDOMAIN_H
#define RDOMAIN_H

#include <string>
#include <vector>

/**
 * @class Domain
 * @brief Abstract base class representing a computational domain.
 */
class Domain {
public:
    /**
     * @brief Pure virtual function to print the grid to a file.
     * @param outputFileName Name of the output file.
     */
    virtual void PrintGrid(const std::string &outputFileName) const = 0;
    
    // Virtual destructor for proper cleanup of derived classes.
    virtual ~Domain() = default;
};

/**
 * @class RDomain
 * @brief Rectangular domain class for generating and managing grids.
 * 
 * This class provides functionalities to:
 * - Generate simple 1D or rectangular grids.
 * - Print grid coordinates to a binary file using `fopen`, `fwrite`, and `fclose`.
 */
class RDomain : public Domain {
private:
    double length;            ///< Length of the domain (assumed square domain: length x length)
    double delta;             ///< Grid spacing (uniform in both x and y directions)
    std::vector<double> gridX; ///< Vector storing x-coordinates of grid points
    std::vector<double> gridY; ///< Vector storing y-coordinates of grid points

public:
    /**
     * @brief Constructs a rectangular domain with specified dimensions
     * 
     * @param len The length of the domain (creates a len x len square domain)
     * @param dx The grid spacing (uniform in both directions)
     * @throws std::invalid_argument If len <= 0 or dx <= 0
     */
    RDomain(double len, double dx);

    /**
     * @brief Generates the computational grid
     * 
     * Creates a uniform grid of points based on the domain length and
     * specified grid spacing. Points are stored in gridX and gridY vectors.
     * 
     * @note This should be called after any changes to domain parameters
     */
    void GenerateGrid();

    /**
     * @brief Outputs the grid coordinates to a file
     * 
     * @param outputFileName Name of the file where grid coordinates will be written
     * @throws std::runtime_error If file cannot be opened or written to
     */
    void PrintGrid(const std::string &outputFileName) const;

    /**
     * @brief Updates the grid spacing
     * 
     * @param dx New grid spacing value to use
     * @throws std::invalid_argument If dx <= 0
     * @note GenerateGrid() should be called after changing the step size
     *       to update the grid coordinates
     */
    void SetStepSize(double dx);

    /**
     * @brief Getter for the grid spacing (delta)
     * 
     * This method returns the current grid spacing (delta) used in both x and y directions.
     * It is useful for checking or adjusting the step size in the simulation.
     * 
     * @return The grid spacing (delta)
     */
    double GetDelta() const { return delta; }  // Added this method to retrieve the grid spacing value
};

#endif // RDOMAIN_H
