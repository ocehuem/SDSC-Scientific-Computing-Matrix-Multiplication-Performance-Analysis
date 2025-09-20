/**
 * @file Node.h
 * @brief Defines the Node class for representing points in a 2D computational grid
 * @acknowledgement cs294-73 colella@eecs.berkeley.edu
 */

#ifndef NODE_H_
#define NODE_H_

#define DIM 2  // Dimensionality of the space (2D)

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

/**
 * @class Node
 * @brief Represents a node in a 2D computational grid
 * 
 * The Node class maintains information about a point in 2D space,
 * including its position coordinates and whether it's an interior node.
 * Interior nodes are assigned unique identification numbers.
 */
class Node {
public:
    /**
     * @brief Default constructor
     * 
     * Creates a Node object with default initialization
     */
    Node();

    /**
     * @brief Parameterized constructor
     * 
     * @param a_position Array containing the (x,y) coordinates of the node
     * @param a_interiorNodeID Unique identifier for interior nodes
     * @param a_isInterior Boolean flag indicating if the node is interior
     */
    Node(double a_position[DIM],
         const int&  a_interiorNodeID,
         const bool& a_isInterior);

    /**
     * @brief Retrieves the position coordinates of the node
     * 
     * @param[out] a_position Array where the position coordinates will be stored
     */
    void getPosition(double a_position[DIM]) const;

    /**
     * @brief Gets the interior node identifier
     * 
     * @return Reference to the interior node ID
     * @note Only meaningful if the node is an interior node
     */
    const int& getInteriorNodeID() const;

    /**
     * @brief Checks if the node is an interior node
     * 
     * @return Reference to boolean indicating interior/exterior status
     */
    const bool& isInterior() const;

private:
    double m_position[DIM];    ///< Position coordinates of the node
    bool m_isInterior;         ///< Flag indicating if node is interior
    int m_interiorNodeID;      ///< Unique ID for interior nodes
};

#endif /* NODE_H_ */
