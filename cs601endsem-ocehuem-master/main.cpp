//Acknowledgements:
//CS601 Endsem: Part 2. DO NOT MODIFY THIS FILE
#include<iostream>
#include"mycontainer.h"
#include<cassert>
using namespace std;
extern int numLinesOfCodeAdded;
extern string me;
int main(){
	//Q1: Modify mycontainer.h to add support to the following operation
	MyContainer<string> u(6);
	//Q2: Modify mycontainer.cpp and other files if required to add support to the following operations
	u[0]="clt";
	u[1]="cif";
	u[2]="wec";
	u[3]="cil";
	u[4]="cac";
	u[5]="ess";
	
	//Q3: Modify mycontainer.cpp and other files if required to add support to the following operations
	u = u + "iit"; 
	assert(u[5]=="ess_iit");

	//Q4: This is about academic honesty: how many lines of code did you add to answer Q1 to Q3? In case you received help from someone, add their name(s) on the first line in front of ':'
	cout<<"Declaration: "<<me<<" added "<<numLinesOfCodeAdded<<" lines of code to this assignment"<<endl;
}
