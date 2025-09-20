/**
 * @file FEGrid.h
 * @brief Definition of FEGrid class for finite element mesh management
 * @author Original: cs294-73 colella@eecs.berkeley.edu
 * 
 * This file defines the FEGrid class which manages the complete finite element mesh,
 * including nodes and elements. It provides functionality for mesh operations and
 * calculations necessary for finite element analysis.
 */

#ifndef FEGRID_H_
#define FEGRID_H_

#include <cstdio>   
#include <cmath>    
#include <cassert>
#include <cstring> 
#include <vector> 
#include <string>
#include "Node.h"   
#include "Element.h"

using namespace std;

/**
 * @class FEGrid
 * @brief Main class for managing finite element mesh
 * 
 * FEGrid manages the complete finite element mesh structure including nodes
 * and elements. It provides methods for accessing mesh components and
 * performing calculations such as gradient computation and area calculation.
 */
class FEGrid
{
public:
    /**
     * @brief Default constructor
     * 
     * Creates an empty finite element grid.
     */
    FEGrid();

    /**
     * @brief Construct a grid from node and element files
     * 
     * @param nodeFile Path to file containing node definitions
     * @param a_elementFileName Path to file containing element definitions
     */
    FEGrid(const std::string& nodeFile, const std::string& a_elementFileName);

    /**
     * @brief Calculate gradient of shape function for a node in an element
     * 
     * @param[out] a_gradient Array to store the computed gradient (size DIM)
     * @param a_eltNumber Element number
     * @param a_localNodeNumber Local node number within the element
     */
    void gradient(double a_gradient[DIM], 
                 const int& a_eltNumber,
                 const int& a_localNodeNumber) const;

    /**
     * @brief Calculate area of a specific element
     * 
     * @param a_eltNumber Element number
     * @return double Area of the element
     */
    double elementArea(const int& a_eltNumber) const;
 
    /**
     * @brief Get node reference by element and local node number
     * 
     * @param a_eltNumber Element number
     * @param a_localNodeNumber Local node number within the element
     * @return const Node& Reference to the node
     */
    const Node& getNode(const int& a_eltNumber,
                       const int& a_localNodeNumber) const; 

    /**
     * @brief Get total number of elements in the mesh
     * @return int Number of elements
     */
    int getNumElts() const;

    /**
     * @brief Get total number of nodes in the mesh
     * @return int Number of nodes
     */
    int getNumNodes() const;

    /**
     * @brief Get number of interior nodes in the mesh
     * @return int Number of interior nodes
     */
    int getNumInteriorNodes() const;

    /**
     * @brief Get reference to specific element
     * 
     * @param i Element index
     * @return const Element& Reference to the element
     */
    const Element& element(int i) const;

    /**
     * @brief Get reference to specific node
     * 
     * @param i Node index
     * @return const Node& Reference to the node
     */
    const Node& node(int i) const;

private:                            
    vector<Node> m_nodes;            ///< Vector storing all nodes in the mesh
    vector<Element> m_elements;      ///< Vector storing all elements in the mesh
    int m_numInteriorNodes;          ///< Number of interior nodes in the mesh
};

#endif
