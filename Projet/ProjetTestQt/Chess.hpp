#pragma once
/**
* Gestion d'un jeu d'échec
* \file   chess.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/
#include "Piece.hpp"

class Board {
private:
  Piece* grid[8][8];
};