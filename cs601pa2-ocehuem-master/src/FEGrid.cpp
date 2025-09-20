/**
 * @file FEGrid.cpp
 * @brief Implementation of the Finite Element Grid class
 * @author Original: cs294-73 colella@eecs.berkeley.edu
 *         Modified by: [Choudari Harshitha Reddy & Mubarakpur Keerthi]
 */

#include <cstdio>    
#include <cmath>     
#include <cstring>   
#include <cassert>   
#include <vector> 
#include <fstream> 
#include<iostream> 
#include<iomanip> 
#include<limits> 
#include "Node.h"    
#include "Element.h" 
#include "FEGrid.h"

/**
 * @brief Default constructor for FEGrid
 * @details Initializes an empty grid with zero interior nodes
 */
FEGrid::FEGrid(): m_numInteriorNodes(0) { }

/**
 * @brief Constructor that builds the grid from node and element files
 * @param a_nodeFileName File containing node coordinates and information
 * @param a_elementFileName File containing element connectivity data
 * @details Reads node positions and element connectivity from files and constructs the FE grid
 *          Identifies interior and boundary nodes based on their coordinates
 */
FEGrid::FEGrid(const std::string& a_nodeFileName, const std::string& a_elementFileName) {
  // Read nodes from file
  ifstream nodes(a_nodeFileName.c_str());
  int ncount;
  nodes>>ncount;
  
  m_nodes.resize(ncount);
  m_numInteriorNodes= 0;
  
  // Process each node
  for(int i=0; i<ncount; i++)
    {
      int vertex;
      std::string tmp[DIM];
      double x[DIM];
      bool isInterior=true;
      nodes>>vertex>>tmp[0]>>tmp[1];
      x[0]=atof(tmp[0].c_str());
      x[1]=atof(tmp[1].c_str());
      
      // Check if node is on boundary
      if(((tmp[0].compare("0.60000"))==0) || ((tmp[1].compare("0.40000"))==0) || (x[0] == 0) || (x[1] == 0)) { 
	isInterior = false; 
	} 
	else   
		m_numInteriorNodes++;
      
      vertex--;
      m_nodes[vertex] = Node(x,vertex, isInterior);
    }
    
  // Read elements from file
  ifstream elements(a_elementFileName.c_str());
  int ncell;
  elements>>ncell;
  int vert[VERTICES];
  m_elements.resize(ncell);
  
  // Process each element
  for(int i=0; i<ncell; i++)
    {
      int cellID;
      elements>>cellID>>vert[0]>>vert[1]>>vert[2];
      vert[0]--; vert[1]--; vert[2]--;
      cellID--;
      m_elements[cellID] = Element(vert);
    }
}

/**
 * @brief Computes gradient of shape functions for a given element and node
 * @param a_gradient [out] Array to store computed gradient components
 * @param a_eltNumber Element number
 * @param a_nodeNumber Local node number within the element
 * @details Calculates the gradient of shape functions N1, N2, N3 for triangular elements
 *          Warning: This calculation is valid for 2D triangular elements only
 */
void FEGrid::gradient(double a_gradient[DIM], 
		      const int& a_eltNumber,  
		      const int& a_nodeNumber) const {
  const Element& e = m_elements[a_eltNumber];
  const Node& n=m_nodes[e[a_nodeNumber]];
  
  double xbase[DIM];
  n.getPosition(xbase);
  double dx[VERTICES-1][DIM];
  
  // Calculate displacement vectors
  for (int ivert = 0;ivert < VERTICES-1; ivert++)
    {
      int otherNodeNumber = e[(a_nodeNumber + ivert+1)%VERTICES];
      m_nodes[otherNodeNumber].getPosition(dx[ivert]);
      for (int idir = 0;idir < DIM;idir++)
        {
          dx[ivert][idir] -=xbase[idir];
        }
    }
             
  // Compute gradient components using determinant method
  double det = dx[0][0]*dx[1][1] - dx[1][0]*dx[0][1];
     
  a_gradient[0] = (-(dx[1][1] - dx[0][1])/det);
  a_gradient[1] = (-(dx[1][0] - dx[0][0])/det);
}

/**
 * @brief Calculates the area of a triangular element
 * @param a_eltNumber Element number
 * @return Area of the element
 * @details Uses vector cross product method to compute triangle area
 *          Warning: This calculation is valid for 2D triangular elements only
 */
double FEGrid::elementArea(const int& a_eltNumber) const {
  const Element& e = m_elements[a_eltNumber];
  const Node& n=m_nodes[e[0]];
  double xbase[DIM];
  n.getPosition(xbase);
  double dx[VERTICES-1][DIM];
  
  // Calculate displacement vectors
  for (int ivert = 1;ivert < VERTICES; ivert++)
    {
      int otherNodeNumber = e[ivert];
      m_nodes[otherNodeNumber].getPosition(dx[ivert-1]);
      for (int idir = 0;idir < DIM;idir++)
        {
          dx[ivert-1][idir] -=xbase[idir];
        }
    }
             
  // Compute area using cross product
  double area = fabs(dx[0][0]*dx[1][1] - dx[1][0]*dx[0][1])/2;
  return area;
}

/**
 * @brief Gets a node from an element using local node number
 * @param a_eltNumber Element number
 * @param a_localNodeNumber Local node number within the element
 * @return Reference to the Node object
 */
const Node& FEGrid::getNode(const int& a_eltNumber,const int& a_localNodeNumber) const {
  return m_nodes[m_elements[a_eltNumber][a_localNodeNumber]];
}

/**
 * @brief Returns total number of elements in the grid
 * @return Number of elements
 */
int FEGrid::getNumElts() const {
  return m_elements.size();
}

/**
 * @brief Returns total number of nodes in the grid
 * @return Number of nodes
 */
int FEGrid::getNumNodes() const {
  return m_nodes.size();
}

/**
 * @brief Returns number of interior nodes in the grid
 * @return Number of interior nodes
 */
int FEGrid::getNumInteriorNodes() const {
  return m_numInteriorNodes;
}

/**
 * @brief Access an element by index
 * @param i Element index
 * @return Reference to the Element object
 */
const Element& FEGrid::element(int i) const {
  return m_elements[i];
}

/**
 * @brief Access a node by index
 * @param i Node index
 * @return Reference to the Node object
 */
const Node& FEGrid::node(int i) const {
  return m_nodes[i];
}
