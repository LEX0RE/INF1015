#pragma once
/**
* Déclaration pour les principes du jeu d'échec
* \file   Game.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   14 avril 2021
* Cree le 14 avril 2021
*/
#include <map>
#include "Piece.hpp"

class Game {
public:
  Game();
  ~Game();

  bool action(const Position position);
  bool addPiece(const std::string specification);
  void removePiece(Piece* piece);
  void setNewGame();
  bool setGame(const std::list<std::string> specificationPiece);
  std::map<std::string, Piece*> getPieceMap() const;
private:
  PieceColor turn_;
  std::map<std::string, Piece*> pieceMap_;
  Piece* selected_;

  Piece* getPiece(const Position position) const;
  bool selectPiece(Piece* selected);
  bool movePiece(const Position position);
  bool addPiece(const PieceColor& color, const unsigned char& type, const Position& position);
  void clearAllPieces();
};
