/**
* Multiplication Russe + Test
* \file   ex4.cpp
* \author Ioana Daria Danciu et Alexandre Gélinas
* \date    7 février 2021
* Créé le 2 février 2021
*/

#include <iostream>
#include <string>

const int nTest = 3;

using namespace std;

int resolveWithRussianMultiplication(int nombre1, int nombre2) {
  int total = 0;
  const int divisibleBy = 2, multiplyBy = 2, divideBy = 2;
  bool isValid = nombre1 > 1;

  while (isValid) {
    nombre1 = int(nombre1 / divideBy);
    nombre2 *= multiplyBy;
    bool isDivisiblePerTwo = nombre1 % divisibleBy;

    if (isDivisiblePerTwo)
      total += nombre2;

    isValid = nombre1 > 1;
  }

  return total;
}

struct Test {
  int n1, n2, result;
};

int main() {
  Test test[nTest] = { { 2, 3, 6 }, { 4, 8, 32 }, { 12, 12, 144 } };
  int succes = 0;

  for (auto t : test) {
    bool isCorrect = resolveWithRussianMultiplication(t.n1, t.n2) == t.result;

    if (isCorrect)
      succes++;
  }
  cout << succes << "/3 tests passent";
}
