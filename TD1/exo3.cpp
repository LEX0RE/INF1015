/**
* Insertion dans un table + tri
* \file   ex3.cpp
* \author Ioana Daria Danciu et Alexandre Gélinas
* \date    7 février 2021
* Créé le 27 janvier 2021
*/

#include <iostream>
#include <string>

const int sizeOfTab = 6;

using namespace std;

struct container{
  unsigned int nElement;
  int tab[sizeOfTab];
};

bool isValidEntry(string message) {
  try {
    int result = stoi(message);
  }
  catch (...) {
    cout << "Entree non valide" << endl;
    return false;
  }

  return true;
}

void swapElementInContainer(container& table, int element1, int element2) {
  int temporary = table.tab[element1];

  table.tab[element1] = table.tab[element2];
  table.tab[element2] = temporary;
}

void sortContainer(container& table) {
  for (unsigned int i = 0; i < table.nElement; i++) {
    for (unsigned int j = i; j < table.nElement; j++) {
      bool isBefore = table.tab[i] > table.tab[j];
      
      if (isBefore)
        swapElementInContainer(table, i, j);
    }
  }
}

void insertInContainer(container& table, int element) {
  table.tab[table.nElement++] = element;

  sortContainer(table);
}

string printContainer(container& table) {
  string data = " ";

  for (auto e : table.tab) {
    bool isValid = e != -1;

    if (isValid)
      data += to_string(e) + " ";
  }

  return data;
}

int main() {
  container table = { 5, { 1, 3, 4, 7, 9, -1} };
  string message = "";
  int element = 0;

  cout << "Veuillez saisir un entier : ";
  getline(cin, message);

  while (isValidEntry(message) == 0) {
    cout << "Veuillez saisir un entier : ";
    getline(cin, message);
  }

  element = stoi(message);
  cout << "entier=" << element << "\ttable avant insertion={" 
       << printContainer(table);

  insertInContainer(table, element);

  cout << "}\ttable apres insertion={" << printContainer(table) << "}" << endl;
}

