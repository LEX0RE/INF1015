/**
* Résolution d'un Tic-Tac-Toe
* \file   ex5.cpp
* \author Ioana Daria Danciu et Alexandre Gélinas
* \date    7 février 2021
* Créé le 2 février 2021
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int row0 = 0, row1 = 3, row2 = 6;
const int col0 = 0, col1 = 1, col2 = 2;

void checkWinByRow(char grid[], int y, bool &player1, bool &player2) {
  const int gridY0 = grid[y + col0], gridY1 = grid[y + col1],
            gridY2 = grid[y + col2];
  bool isWin = gridY0 == gridY1 && gridY0 == gridY2;
  bool isPlayer1Winner = gridY0 == 'x';

  if (isWin) {
    if (isPlayer1Winner)
      player1 = true;
    else
      player2 = true;
  }
}

void checkWinByColumn(char grid[], int x, bool& player1, bool& player2) {
  const int grid0X = grid[row0 + x], grid1X = grid[row1 + x],
            grid2X = grid[row2 + x];
  bool isWin = grid0X == grid1X && grid0X == grid2X;
  bool isPlayer1Winner = grid0X == 'x';

  if (isWin) {
    if (isPlayer1Winner)
      player1 = true;
    else
      player2 = true;
  }
}

void checkWinByDiagonal(char grid[], bool& player1, bool& player2) {
  const int grid00 = grid[row0 + col0], grid11 = grid[row1 + col1],
            grid02 = grid[row0 + col2], grid20 = grid[row2 + col0],
            grid22 = grid[row2 + col2];
  bool isWin = (grid00 == grid11 || grid02 == grid11) &&
               (grid20 == grid11 || grid22 == grid11);
  bool isPlayer1Winner = grid11 == 'x';

  if (isWin) {
    if (isPlayer1Winner)
      player1 = true;
    else
      player2 = true;
  }
}

int solveTicTacToe(char grid[]) {
  bool isPlayer1Winner = false, isPlayer2Winner = false;
  const int win1 = 1, win2 = 2, equality = 3;

  for (unsigned int i = 0; i < 3; i++) {
    int iRow = i * 3, iColumn = i;

    checkWinByRow(grid, iRow, isPlayer1Winner, isPlayer2Winner);
    checkWinByColumn(grid, iColumn, isPlayer1Winner, isPlayer2Winner);
  }

  checkWinByDiagonal(grid, isPlayer1Winner, isPlayer2Winner);

  bool isEquality = isPlayer1Winner == isPlayer2Winner;

  if (isEquality)
    return equality;
  else if (isPlayer2Winner)
    return win2;
  else
    return win1;
}

int readGame(string file) {
  ifstream fichier(file);
  char grid[9];

  if (fichier.is_open()) {
    for(unsigned int i = 0; i < 9; i++)
      fichier >> grid[i];

    fichier.close();
    return solveTicTacToe(grid);
  }
  else
    return 0;
}

int main() {
  string message;
  int result = 0;
  const int equality = 3;
  bool isImpossible = result == 0;

  while (isImpossible) {
    cout << "Veuillez saisir un nom du ficher de votre jeu de Tic-Tac-Toe : ";
    getline(cin, message);
    result = readGame(message);
    isImpossible = result == 0;
  }

  bool isEquality = result == equality;

  if (isEquality)
    cout << "Egalite" << endl;
  else
    cout << "Le joueur " << result << " gagne." << endl;
}
