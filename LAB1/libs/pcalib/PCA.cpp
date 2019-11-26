//==============================================================================
// Name        : PCA.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 31/07/2019
// Description : The PCA algorithm [Lever et al., 2017], [Smith, 2002]
//				 - written in C++, Ansi-style
//==============================================================================

#include "PCA.h"

void DPLKYL002::PCA::setDataPoints(string inputFileName) {

	// setup using input data stored in inputData.txt
	ifstream iFile(inputFileName);

	string input;

	while (getline(iFile, input)) {

		if (isalpha(input[0]) || input == "") {

			continue;

		}

		inputData.push_back(stof(input));

	}

	iFile.close();

}

void DPLKYL002::PCA::loadDataPoints() {

	// load vector with input data
	midpoint = inputData.size() / 2;

	for (int k = 0; k < midpoint; ++k) {

		vectPts.push_back(Vector2d(inputData[2 * k], inputData[2 * k + 1]));

	}

}
void DPLKYL002::PCA::computeCovarianceMatrix() {

	// compute mean / average
	Vector2d average(0, 0);

	for (auto p = vectPts.begin(); p != vectPts.end(); ++p) {

		average += (*p);

	}

	average = average / midpoint;

	outputFile = ofstream("answers.txt");

	outputFile << "Means: " << endl << average << endl << endl;

	// generate matrix of differences between means and samples where each column is [x - meanX] and [y - meanY]
	MatrixXd matrix(2, midpoint);

	for (int k = 0; k < midpoint; ++k) {

		matrix.col(k) = (vectPts[k] - average);

	}

	// compute covariance matrix
	outputFile << "3. Compute the values for the covariance matrix." << endl;

	covarianceMatrix = matrix * (matrix.transpose()) / (midpoint - 1);

	outputFile << "Covariance matrix: " << endl << covarianceMatrix << endl
			<< endl;
}

void DPLKYL002::PCA::computeEigenValuesVectors() {

	// compute Eigenvalues
	outputFile
			<< "1. What are the Eigenvalues for the principal components 1 and 2?"
			<< endl;

	EigenSolver<MatrixXd> es(covarianceMatrix);

	for (int k = 0; k < 2; ++k) {

		complex<double> ES = es.eigenvalues().col(0)[k];

		vectEigenValues.push_back((float) ES.real());

		outputFile << "Eigenvalue for principal component " << k + 1 << ": "
				<< vectEigenValues[k] << endl;

	}

	outputFile << endl;

	// compute Eigenvectors
	outputFile
			<< "2. What are the Eigenvectors for the principal components 1 and 2 (showing July and January component values for each)?"
			<< endl;

	for (int k = 0; k < 2; ++k) {

		auto pVect = es.eigenvectors().col(k);

		vectEigenVectors.push_back(pVect.real());

		outputFile << "Eigenvector for principal component " << k + 1 << ": "
				<< vectEigenVectors[k][0] << " " << vectEigenVectors[k][1] << endl;

	}

	outputFile << endl;

}

void DPLKYL002::PCA::computeTotalVariance() {

	// compute total variance
	outputFile << "4. What is the total variance?" << endl;

	totalVariance = covarianceMatrix(0, 0) + covarianceMatrix(1, 1);

	outputFile << "Total variance: " << totalVariance << endl << endl;

}

void DPLKYL002::PCA::computePrincipalComponentsVarianceExplained() {

	// ordered principal components
	float tempValue;

	if (vectEigenValues[0] < vectEigenValues[1]) {

		tempValue = vectEigenValues[0];

		vectEigenValues[0] = vectEigenValues[1];

		vectEigenValues[1] = tempValue;

	}

	// determine percentage of total variance that each principal component explains
	outputFile
			<< "5. What proportion (as a percentage) of total variance do principal components 1 and 2 \"explain\"?"
			<< endl;

	for (int k = 0; k < 2; ++k) {

		percentage = vectEigenValues[k] / totalVariance * 100;

		outputFile << "Percentage of total variance that principal component "
				<< k + 1 << " explains: " << percentage << "%" << endl;

	}

	outputFile.close();

	cout << "answers.txt written successfully" << endl;

}
