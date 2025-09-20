//This is CS601: PA2. The questions are indicated in lines having comments bearing the question number. Fill in your answers in place. 
//When you are done filling in your answers, the code must be compilable. Code with syntax errors receive Zero. Do not change any other lines other than what is indicated in the question.
#include "FEGrid.h"
#include<vector>
#include<string>
#include<cmath>
#include <iostream>
#include<iomanip>
#include<fstream>
#define K 30


using namespace std;
/**
 * @brief Main function for assembling global stiffness matrix from finite element data.
 *
 * This function reads node and element files specified by the user, calculates local stiffness matrices 
 * for each element, and assembles them into a global stiffness matrix. The program also calculates 
 * properties of the matrix, such as its structure and bandwidth.
 *
 * @param argc Number of command-line arguments (must be 2).
 * @param argv Array of command-line arguments. The second argument is the file prefix for input data.
 *
 * @return Returns 0 on successful execution, or 1 if incorrect arguments are provided.
 *
 * @debug Outputs intermediate matrices to files when DEBUG is defined. Writes kijpartial in binary format
 *        and outputs the global stiffness matrix for visualization.
 *
 * @note Requires node and element data files with specific naming conventions (prefix.node, prefix.elem).
 */
int main(int argc, char** argv) {
  if(argc != 2)
    {
      cout << "this program takes just one argument that is the common name prefix of .node and .elem files. (Note: do not give the file extension) ";
      return 1;
    }
  string prefix(argv[1]);
  string nodeFile = prefix+".node";
  string eleFile  = prefix+".elem";
  string q3Answer, q4AnswerA, q4AnswerB;

  FEGrid grid(nodeFile, eleFile);

  //get the total number of nodes and interior nodes 
  int numInteriorNodes = grid.getNumInteriorNodes();
  int numNodes = grid.getNumNodes();

  //Global stiffness matrix stores the Kij values of all interior nodes.
  //The globalMatrixIndex array stores the index of the interior node in the global matrix
  int* globalMatrixIndex = (int*)malloc(sizeof(int)*numNodes);
  int interiorNodeIndex=0;
  for(int i=0;i<numNodes;i++) {
  	const Node& n = grid.node(i);
	if(n.isInterior())
		globalMatrixIndex[i]=interiorNodeIndex++;
	else
		globalMatrixIndex[i]=-1;
  }
  double *globalK=(double *)malloc(sizeof(double)*numInteriorNodes*numInteriorNodes);
  memset(globalK, 0, sizeof(double)*numInteriorNodes*numInteriorNodes);
  double kij[VERTICES*VERTICES]; //for storing B^T * C * B
  double kijpartial[VERTICES*VERTICES]; //for storing B^T * C
  double cMatrix[DIM*2]={K, 0, 0, K};

  //Poisson operator over the grid elements
  for(int i=0;i<grid.getNumElts();i++) {
	Element e=grid.element(i);
	//first count the number of interior nodes in the element e.
	  /**
	 * @brief Identifies and stores interior nodes for the current element.
	 *
	 * Creates a vector of indices for interior nodes in the current element
	 * and calculates gradients of the shape functions for further computations.
	 */
	std::vector<int> elementInteriorNodeID;
	for(int j=0;j<VERTICES;j++) {
		const Node& n= grid.getNode(i, j);
		if(n.isInterior()) {
			//storing nodeLocal number of the interior node of the element.
			elementInteriorNodeID.push_back(j); 
		}
	}
	int numInteriorNodesOfElement = elementInteriorNodeID.size();

	//allocate storage for gradient of shape functions for each interior node/vertex of the element 
	double* bMatrixTrans=(double *)malloc(sizeof(double)*numInteriorNodesOfElement*DIM);
	//get gradient of the shape functions for all interior nodes of the element.
	for(int j=0;j<numInteriorNodesOfElement;j++)		
			grid.gradient(bMatrixTrans+j*DIM, i, elementInteriorNodeID[j]);
#ifndef CBLAS_DGEMM
	//compute B^T * C (3x2 * 2x2) OR (2x2 * 2x2) or (1x2 * 2x2)
	/**
	 * @brief Computes B^T * C manually without BLAS library.
	 *
	 * This block computes the intermediate matrix multiplication B^T * C, 
	 * where B^T is the transposed gradient matrix and C is the material matrix.
	 */
	for(int m=0;m<numInteriorNodesOfElement;m++) {
		for(int n=0;n<DIM;n++) {
  			kijpartial[m*DIM+n]=0.;
			for(int r=0;r<DIM;r++)
				kijpartial[m*DIM+n] = kijpartial[m*DIM+n]+bMatrixTrans[m*DIM+r] * cMatrix[r*DIM+n];
		}
	}
#else
	//https://www.intel.com/content/www/us/en/develop/documentation/mkl-tutorial-c/top/multiplying-matrices-using-dgemm.html
	/*Q1: if you had access to the CBLAS library routine cblas_dgemm, you can rewrite lines 70-76 by a single line that calls the cblas_dgemm routine. 
	 *Write how you would achieve the equivalentof 70-76 using cblas_dgemm routine. Make sure that you do not have syntax errors. You must make a call to the BLAS routine (i.e. not write your answer in double quotes).
	 */
	/**
	 * @brief Uses cblas_dgemm for matrix multiplication.
	 *
	 * Calls the cblas_dgemm routine from the BLAS library to perform 
	 * the equivalent of B^T * C computation.
	 */
	  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, numInteriorNodesOfElement, DIM, DIM, 1.0, bMatrixTrans, DIM, cMatrix, DIM, 0.0, kijpartial, DIM);
#endif
	//Q2: Write routine to dump kijpartial in a file called kijdump.bin here (in binary format)
	/**
	 * @brief Writes kijpartial matrix to a binary file for debugging purposes.
	 *
	 * This block writes the kijpartial matrix to `kijdump.bin` for debugging or analysis.
	 */
	ofstream kijDump("kijdump.bin", ios::binary);
	kijDump.write(reinterpret_cast<const char*>(kijpartial), sizeof(double) * numInteriorNodesOfElement * DIM);
	kijDump.close();
	//creating B from B^T	
	
	/**
	 * @brief Constructs the B matrix from its transpose (B^T).
	 *
	 * Converts the B^T matrix to its original form for further computations.
	 */
	double *bMatrix=(double *)malloc(sizeof(double)*DIM*numInteriorNodesOfElement);
	for(int m=0;m<DIM;m++)
		for(int n=0;n<numInteriorNodesOfElement;n++)
			bMatrix[m*numInteriorNodesOfElement+n]=bMatrixTrans[n*DIM+m];
			
	free(bMatrixTrans);

	//multiplying with B.
	/**
	 * @brief Multiplies B^T * C * B to form the local stiffness matrix.
	 *
	 * Computes kij = B^T * C * B, where kij is the local stiffness matrix for the current element.
	 */
	for(int m=0;m<numInteriorNodesOfElement;m++) {
		for(int n=0;n<numInteriorNodesOfElement;n++) {
  			kij[m*numInteriorNodesOfElement+n]=0.;
			for(int r=0;r<DIM;r++)
				kij[m*numInteriorNodesOfElement+n] = kij[m*numInteriorNodesOfElement+n] + kijpartial[m*DIM+r] * bMatrix[r*numInteriorNodesOfElement+n];
		}
  	}

	free(bMatrix);


  	//Insert element matrix contents into global Matrix
	/**
	 * @brief Assembles the local stiffness matrix into the global matrix.
	 *
	 * Inserts the values of the local stiffness matrix (kij) into the global matrix (globalK)
	 * using the indices of the interior nodes.
	 */
	for(int m=0;m<numInteriorNodesOfElement;m++) {
			int nodeGlobalNumber = e[elementInteriorNodeID[m]];
			assert(globalMatrixIndex[nodeGlobalNumber] !=-1);
			int rowNumber = globalMatrixIndex[nodeGlobalNumber];
			for(int n=0;n<numInteriorNodesOfElement;n++) {
				int colNumber = globalMatrixIndex[e[elementInteriorNodeID[n]]];
				globalK[rowNumber*numInteriorNodes+colNumber] +=kij[m*numInteriorNodesOfElement+n];
		}
	}	
  }

	/*Q3: What is the structure of the global matrix globalK? Choose your option from: 1) Tridiagonal 2) Diagonal 3) BiDiagonal 4) Banded 5) Upper Hessenberg 6) Lower Hessenberg
	 * Write your answer (as a string that exactly matches one of the options above.) in the space provided below.*/
	/**
	 * @brief Specifies the structure and bandwidth properties of the global stiffness matrix.
	 *
	 * Q3: Identifies the structure of the global matrix (e.g., Banded).
	 * Q4: Determines the lower and upper bandwidth of the global matrix.
	 */
  	q3Answer="Banded";
	  

	/*Q4: What is the lower bandwidth (PART A) and upper bandwidth (PART B) of the matrix represented in globalK when this program is run as: ./pa4 fine ?*/
  	q4AnswerA="9";
  	q4AnswerB="9";

	cout<<q3Answer<<endl;
	cout<<"Lower Bandwidth: "<<q4AnswerA<<endl;
	cout<<"Upper Bandwidth: "<<q4AnswerB<<endl;

#ifdef DEBUG
			
  	//write the global matrix into a file for visualization.
	/**
	 * @brief Writes the global stiffness matrix to a file for visualization.
	 *
	 * Outputs the matrix to `GlobalKMatrixFile.txt` for debugging purposes.
	 */
	ofstream myoutputfile;
	myoutputfile.open("GlobalKMatrixFile.txt");
	for(int m=0;m<numInteriorNodes;m++) {
		for(int n=0;n<numInteriorNodes;n++){
				myoutputfile<<globalK[m*numInteriorNodes+n];
				if(n!=numInteriorNodes-1)
					myoutputfile<<" ";
				else
					myoutputfile<<"\n";
		}
	}
#endif
	
	//Jacobi solver goes here.

  
  return 0;
  
}
