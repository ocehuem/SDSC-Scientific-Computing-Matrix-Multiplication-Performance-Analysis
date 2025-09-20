/**
* @file sumdiagonal.cpp
* @brief Calculation of the sum of diagonal elements of a square matrix.
* @author Choudari Harshitha Reddy (220010015)
*
* CS601: Midsem - PartII Question 1 - GDB, Valgrind, Doxygen
** Acknowledgements: Marcus Holm
** Adapted by: Nikhil Hegde
** This erroneous program is supposed to initialize a square matrix of given dimensions with numbers ranging from -10 to 9 and print the sum of the diagonal elements of the matrix.
*/

/**
 * @bug Fixed the following issues:
 * - Changed the return type of sumdiagonal to double instead of double*.
 * - Corrected the return statement in sumdiagonal to return sum directly.
 * - Changed the return type of fill_vectors to return vec directly.
 * - Fixed matrix allocation in initialization to allocate proper array sizes.
 * - Adjusted the loop to start from 0 in main and sumdiagonal.
 */

#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

/** DO NOT CHANGE THE BELOW 4 LINES **/
double** initialization(int);
double* fill_vectors(double*, int);
void print_matrix(double**, int);
double* sumdiagonal(double**, int);
/************************************/

/* The main program. */
int main()
{/**
*@bug removed unused variable j
*/
    int i, n;
    double **matrix;
    double sum;

    cout << endl << "Enter the Dimension for a square matrix: " << flush;
    cin >> n;
    matrix = initialization(n);
    for (i = 0; i < n; i++)
        fill_vectors(matrix[i], n); // Fixed loop index to start from 0
    sum = *sumdiagonal(matrix, n); // Dereference the pointer to get the sum
    print_matrix(matrix, n);
    cout << endl << "Sum of the diagonal elements are: " << sum << endl;

    /**
    * @bug Free the allocated memory
    */
    for (i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}

/**
 * @brief Initializes an n x n matrix by allocating dynamic memory.
 * @param n The dimension of the square matrix.
 * @return A pointer to the allocated matrix.
 */
double** initialization(int n) {
    int i;
    double** matrix;
    matrix = new double*[n]; // Changed to single pointer allocation
    for (i = 0; i < n; ++i)
        matrix[i] = new double[n];
    return (matrix);
}

/**
 * @brief Fills a vector with random numbers in the range [-10, 9].
 * @param vec Pointer to the vector to be filled.
 * @param n The number of elements in the vector.
 * @return Pointer to the filled vector.
 */
double* fill_vectors(double* vec, int n) { // Fixed function name to match declaration
    int i;
    for (i = 0; i < n; i++)
        vec[i] = rand() % 20 - 10;
    return vec; // Return pointer to the filled vector
}

/**
 * @brief Prints the elements of a square matrix.
 * @param matrix Pointer to the matrix.
 * @param n The dimension of the matrix.
 */
void print_matrix(double** matrix, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            cout << matrix[i][j] << ", ";
        cout << endl;
    }
}

/**
 * @brief Returns the sum of the diagonal elements of a given matrix.
 * @param matrix Pointer to the matrix.
 * @param n The dimension of the matrix.
 * @return A pointer to the sum of the diagonal elements.
 * @bug Fixed the indexing in the for loop and return type to match the function signature.
 */
double* sumdiagonal(double** matrix, int n) {
    int i;
    static double sum = 0.0; // Use static to return the address safely
    sum = 0.0; // Reset sum to zero
    for (i = 0; i < n; i++) // Start loop from 0 to n-1
        sum += matrix[i][i];
    return &sum; // Return address of sum
}

