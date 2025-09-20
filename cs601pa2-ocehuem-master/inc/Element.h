/**
 * @file Element.h
 * @brief Definition of Element class for finite element mesh
 * @author Original: cs294-73 colella@eecs.berkeley.edu
 * 
 * This file defines the Element class which represents a triangular element
 * in a finite element mesh. Each element consists of three vertices.
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

/** @brief Number of vertices in each element (triangular elements) */
#define VERTICES 3

/**
 * @class Element
 * @brief Represents a triangular element in the finite element mesh
 * 
 * The Element class encapsulates a triangular element defined by three vertices.
 * Each vertex is represented by its index in the global node numbering system.
 */
class Element
{
public: 
    /**
     * @brief Default constructor
     * 
     * Creates an Element with uninitialized vertices.
     */
    Element();

    /**
     * @brief Construct an element with specified vertices
     * 
     * @param a_vertices Array of three vertex indices defining the element
     */
    Element(int a_vertices[VERTICES]);

    /**
     * @brief Access operator for vertex indices
     * 
     * @param a_localNodeNumber Local node number (0, 1, or 2)
     * @return const int& Reference to the vertex index
     */
    const int& operator[](const int& a_localNodeNumber) const;

    /**
     * @brief Get all vertex indices of the element
     * 
     * @param[out] a_vertices Array to store the three vertex indices
     */
    void vertices(int a_vertices[VERTICES]) const;

private:
    int m_vertices[VERTICES];  ///< Array storing the three vertex indices
};

#endif // ELEMENT_H_
