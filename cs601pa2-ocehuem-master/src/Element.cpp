/**
 * @file Element.cpp
 * @brief Implementation of Element class methods for finite element mesh
 * @acknowledgement cs294-73 colella@eecs.berkeley.edu
 */

#include <cassert>
#include "Element.h"

/**
 * @brief Parameterized constructor for Element
 * 
 * Constructs an Element with specified vertex indices. The vertices array
 * defines the connectivity of this element with the global node numbering.
 * 
 * @param a_vertices Array containing the global indices of vertices that form this element
 * @pre a_vertices must contain VERTICES number of valid node indices
 * @post Element is initialized with the specified vertex connectivity
 */
Element::Element(int a_vertices[VERTICES]) {
    for (int ivert = 0; ivert < VERTICES; ivert++) {
        m_vertices[ivert] = a_vertices[ivert];
    }
};

/**
 * @brief Default constructor for Element
 * 
 * Initializes an Element with invalid vertex indices (-1).
 * This constructor is typically used when creating arrays of elements
 * that will be populated later.
 * 
 * @post All vertex indices are set to -1, indicating an uninitialized element
 */
Element::Element() {
    for (int ivert = 0; ivert < VERTICES; ivert++) {
        m_vertices[ivert] = -1;
    }
};

/**
 * @brief Access operator for retrieving vertex indices
 * 
 * Provides read-only access to vertex indices using local vertex numbering.
 * 
 * @param a_localNodeNumber Local index of the vertex within this element (0 to VERTICES-1)
 * @return const reference to the global index of the requested vertex
 * @throws assertion failure if a_localNodeNumber is out of bounds
 */
const int& Element::operator[](const int& a_localNodeNumber) const {
    assert(a_localNodeNumber < VERTICES);
    return m_vertices[a_localNodeNumber];
};

/**
 * @brief Retrieves all vertex indices of the element
 * 
 * Copies the global indices of all vertices that form this element
 * into the provided array.
 * 
 * @param[out] a_vertices Array where vertex indices will be stored
 * @pre a_vertices must be able to hold at least VERTICES number of integers
 * @post a_vertices contains the global indices of all vertices in this element
 */
void Element::vertices(int a_vertices[VERTICES]) const {
    for(int i=0; i<VERTICES; i++) {
        a_vertices[i] = m_vertices[i];
    }
}
