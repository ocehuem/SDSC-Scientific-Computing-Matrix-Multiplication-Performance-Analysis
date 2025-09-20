/**
 * @file Node.cpp
 * @brief Implementation of the Node class for mesh discretization
 * @details This class implements a node in a computational mesh, supporting both
 *          interior and boundary nodes in DIM-dimensional space. Each node stores
 *          its spatial coordinates and classification as interior/boundary.
 */

#include <cstdio>
#include <cmath>
#include <cassert>
#include <cfloat>
#include <vector>
#include "Node.h"
using namespace std;

/**
 * @brief Default constructor
 * @details Initializes a node with:
 *          - Position coordinates set to FLT_MAX in all dimensions
 *          - Marked as interior node by default
 *          - Interior node ID set to -1
 *          This constructor creates an invalid node that should be properly initialized
 *          before use.
 */
Node::Node() {
    for (int idir = 0; idir < DIM; idir++) {
        m_position[idir] = FLT_MAX;
    }
    m_isInterior = true;
    m_interiorNodeID = -1;
}

/**
 * @brief Constructs a node with specified position and properties
 * @param a_position Array of length DIM containing spatial coordinates
 * @param a_interiorNodeID Identifier for the node if it's interior (used in matrix assembly)
 * @param a_isInterior Boolean flag indicating if node is interior (true) or boundary (false)
 * @details Creates a node with specified:
 *          - Spatial coordinates in DIM-dimensional space
 *          - Interior/boundary classification
 *          - Interior node numbering for matrix assembly
 */
Node::Node(double a_position[DIM],
           const int& a_interiorNodeID,
           const bool& a_isInterior) {
    for (int idir = 0; idir < DIM; idir++) {
        m_position[idir] = a_position[idir];
    }
    m_isInterior = a_isInterior;
    m_interiorNodeID = a_interiorNodeID;
}

/**
 * @brief Retrieves the node's spatial coordinates
 * @param[out] a_x Array of length DIM to store the coordinates
 * @details Copies the node's position coordinates into the provided array.
 *          The caller must ensure that a_x has adequate space (DIM elements).
 */
void Node::getPosition(double a_x[DIM]) const {
    for (int idir=0; idir < DIM; idir++) {
        a_x[idir] = m_position[idir];
    }
}

/**
 * @brief Gets the interior node ID
 * @return Reference to the interior node ID
 * @details Returns the node's ID used in matrix assembly for interior nodes.
 *          For boundary nodes, this ID may not be meaningful.
 */
const int& Node::getInteriorNodeID() const {
    return m_interiorNodeID;
}

/**
 * @brief Checks if the node is interior
 * @return Reference to boolean flag indicating interior (true) or boundary (false) status
 * @details A node is classified as interior if it's not on the domain boundary.
 *          This classification is important for finite element assembly and
 *          boundary condition application.
 */
const bool& Node::isInterior() const {
    return m_isInterior;
}
