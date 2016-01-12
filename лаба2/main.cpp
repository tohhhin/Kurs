#include <iostream>
#include<stdio.h>
#include<conio.h>
#include <cmath>  
#include <fstream> 
#include <windows.h>
#include <vector>
#include <set>

using namespace std1;


int getGlobalIndexOfLocalBasisFunction_(int indexOfFiniteElement, int indexOfLocalBasisFunction)
{
	int i = indexOfFiniteElement+1;
	int Nx = 4;//кол-во точек по x
	int K = 2 * int((i - 1) / (Nx - 1))* (2 * Nx - 1) + 2 * ((i - 1) % (Nx - 1));
	
	switch (indexOfLocalBasisFunction) {

	case 0:
		return K;
		break;

	case 1:
		return K + 1;
		break;

	case 2:
		return K + 2;
		break;

	case 3:
		return  K + 2 * Nx - 1;
		break;
	case 4:
		return  K + 2 * Nx;
		break;
	case 5:
		return K + 2 * Nx + 1;
		break;
	case 6:
		return  K + 2 * (2 * Nx - 1);
		break;
	case 7:
		return K + 2 * (2 * Nx - 1) + 1;
		break;
	case 8:
		return K + 2 * (2 * Nx - 1) + 2;
		break;
	}
}


void portret(int *ig,int *jg, int emountOfNodes, int emountOfFiniteElements)
{
//int *ig, *jg, **adjacencyList;
	int **adjacencyList;
	//int emountOfNodes = 35;//кол-во баз функций
	//int emountOfFiniteElements = 6;//кол-во элемнтов

	adjacencyList = new int*[emountOfFiniteElements];
	for (int i = 0; i < emountOfFiniteElements; i++)
		adjacencyList[i] = new int[9];

	for (int i = 0; i < emountOfFiniteElements; i++) {
		for (int j = 0; j < 9; j++) 
		{
			adjacencyList[i][j] = getGlobalIndexOfLocalBasisFunction_(i, j);
			
		}

	}


	std::vector<std::set<int>> indexesOfNonzeroElements;
	indexesOfNonzeroElements.resize(emountOfNodes);
	for (int i = 0; i < emountOfFiniteElements; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 9; k++) {
				if (adjacencyList[i][j]>adjacencyList[i][k])
					indexesOfNonzeroElements[adjacencyList[i][j]].insert(adjacencyList[i][k]);
			}
		}
	}



	//ig = new int[emountOfNodes + 1];
	ig[0] = ig[1] = 1;

	for (int i = 1; i < emountOfNodes; i++)
		ig[i + 1] = ig[i] + indexesOfNonzeroElements[i].size();


	jg = new int[ig[emountOfNodes] - 1];
	int k = 0;
	for (int i = 0; i < indexesOfNonzeroElements.size(); i++) {
		for (int j : indexesOfNonzeroElements[i]) {
			jg[k++] = j;
		}
	}
	//for (int i = 0;i < emountOfNodes + 1;i++)
	//	printf("%d ", ig[i]);

	printf(" \n");
	//for (int i = 0;i < ig[emountOfNodes]-1;i++)
	//	printf("%d ", jg[i]);

//	_getch();
}

void main() 
{
	int emountOfNodes = 35;
	int *ig;
	int *jg;
	ig = new int[emountOfNodes + 1];
	jg = new int[emountOfNodes + 1];

	
	portret(ig,jg, emountOfNodes,6);
	for (int i = 0;i < emountOfNodes + 1;i++)
		printf("%d ", ig[i]);
	for (int i = 0;i < ig[emountOfNodes]-1;i++)
		printf("%d ", jg[i]);
	
	_getch();
}
