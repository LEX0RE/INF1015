#pragma once
/**
* D�claration pour les principes du jeu d'�chec
* \file   Game.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   14 avril 2021
* Cree le 14 avril 2021
*/

#define N_SQUARE 8

#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QObject>
#pragma pop()
#include <map>
#include "Piece.hpp"

namespace model {
  class Game : public QObject{
    Q_OBJECT

  public:
    Game();
    ~Game();

    bool addPiece(const std::string specification);
    void removePiece(Piece* piece);
    void setNewGame();
    void setFischerRandomGame();
    bool setGame(const std::list<std::string> specificationPiece);
    std::map<std::string, Piece*> getPieceMap() const;
  public slots:
    bool action(const Position position);
  signals:
    void updatePiece(std::map<std::string, Piece*> pieceMap);
    void updatePossibility(std::list<Position> possibility);
  private:
    PieceColor turn_;
    std::map<std::string, Piece*> pieceMap_;
    Piece* selected_;

    Piece* getPiece(const Position position) const;
    bool selectPiece(Piece* selected);
    bool movePiece(const Position position);
    bool addPiece(const PieceColor& color, const unsigned char& type, const Position& position);
    void clearAllPieces();
    void setFromBackline(std::string backline);
  };
}