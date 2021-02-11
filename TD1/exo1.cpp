/**
* Statistiques sur les mots (longueur, mot le plus long/court, moyenne de lettre)
* \file   ex1.cpp
* \author Ioana Daria Danciu et Alexandre Gélinas
* \date    7 février 2021
* Créé le 26 janvier 2021
*/

#include <iostream>
#include <string>
#include <vector>

#define LENGTH_TYPE_BIGGEST 0
#define LENGTH_TYPE_SMALLEST 1

using namespace std;

void toVector(vector<string> &data, string &sentence) {
  string word = "";
  int i = 0;

  for (auto letter : sentence) {
    bool isSpace = letter == ' ', isEnd = i++ == size(sentence) - 1;

    if (isSpace || isEnd) {
      if (isEnd)
        word += letter;
      
      data.push_back(word);
      word = "";
    }
    else
      word += letter;
  }
}

string findLengthWord(vector<string> &data, bool lengthType) {
  string result = data.at(0);

  for (auto c : data) {
    bool isSmaller = size(result) > size(c),
         isBigger = size(result) < size(c);

    if ((lengthType != 0 && isSmaller) || (lengthType == 0 && isBigger))
        result = c;
  }

  return result;
}

double getAverageLetter(vector<string>& data) {
  int nWord = 0;
  double summation = 0;

  for (auto& w : data) {
    summation += int(size(w));
    nWord++;
  }

  return summation / nWord;
}

int main() {
  string sentence = "";
  vector<string> data = {};

  cout << "Saisissez une phrase : ";
  getline(cin, sentence);
  toVector(data, sentence);

  cout << "Le mot le plus court est : ";
  cout << findLengthWord(data, LENGTH_TYPE_SMALLEST) << endl;
  cout << "Le mot le plus long est : ";
  cout << findLengthWord(data, LENGTH_TYPE_BIGGEST) << endl;
  cout << "La longueur moyenne est : " << getAverageLetter(data) << " lettres";

  return 0;
}
