//==============================================================================
// Name        : PCA.h
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 31/07/2019
// Description : The PCA algorithm [Lever et al., 2017], [Smith, 2002]
//				 - written in C++, Ansi-style
//==============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

// Eigen is a C++ template library for linear algebra: matrices, vectors, numerical solvers and related algorithms
#include "Eigen/Dense"

#ifndef LIBS_PCA_H
#define LIBS_PCA_H

using namespace std;
using namespace Eigen;

namespace DPLKYL002 {

class PCA {

private:

	// private members
	vector<float> inputData;
	vector<Vector2d> vectPts;
	vector<float> vectEigenValues;
	vector<Vector2d> vectEigenVectors;
	Matrix2d covarianceMatrix;
	ofstream outputFile;
	float totalVariance, percentage;
	int midpoint;


public:

	// public members
	void setDataPoints(string inputFileName);
	void loadDataPoints();
	void computeCovarianceMatrix();
	void computeEigenValuesVectors();
	void computeTotalVariance();
	void computePrincipalComponentsVarianceExplained();

};

}

#endif
