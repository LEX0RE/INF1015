/**
* Évaluation d'une limite d'une fonction
* \file   ex2.cpp
* \author Ioana Daria Danciu et Alexandre Gélinas
* \date    7 février 2021
* Créé le 27 janvier 2021
*/

#include <iostream>
#include <cmath>
#include <iomanip>

const int precision = -5;

using namespace std;

inline double function(double input) {
  return double(pow(2.0 + input, 0.5));
}

double estimateRecursiveFonction(double lastResult) {
  double result = function(lastResult), decimalPrecision = pow(10, precision);
  bool isGoodPrecision = abs(lastResult - result) < decimalPrecision;

  if (isGoodPrecision)
    return result;
  else
    return estimateRecursiveFonction(result);
 }

int main() {
  double u_0 = 1.0;

  cout << "U_0 = 1\nU_n + 1 = sqrt(2 + U_n)" << endl
       << "Estimation de la limite avec " << precision
       << " decimale : " << estimateRecursiveFonction(u_0);
}

