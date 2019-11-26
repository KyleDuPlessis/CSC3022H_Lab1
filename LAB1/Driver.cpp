//==============================================================================
// Name        : Driver.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 31/07/2019
// Description : The PCA algorithm [Lever et al., 2017], [Smith, 2002]
//				 - written in C++, Ansi-style
//==============================================================================

#include "PCA.h"

// main function
int main(int argc, char * argv[]) { // argc and argv values passed into main

	DPLKYL002::PCA pca;

	pca.setDataPoints("inputData.txt");
	pca.loadDataPoints();
	pca.computeCovarianceMatrix();
	pca.computeEigenValuesVectors();
	pca.computeTotalVariance();
	pca.computePrincipalComponentsVarianceExplained();

	return 0;

}
