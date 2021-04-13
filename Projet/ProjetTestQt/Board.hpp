#pragma once
/**
* Déclaration pour la planche du jeu d'échec
* \file   Board.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/

#define CASE_SIZE 140

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsGridLayout>
#include <QGraphicsRectItem>
#include <QGraphicsWidget>
#include <QBrush>
#pragma pop()
#include <map>
#include "Piece.hpp"

struct Square : public QGraphicsWidget {
public:
  Square(const Qt::GlobalColor color, const Position position, QGraphicsItem* parent = nullptr);
  ~Square() override = default;

  void highlight(const Qt::GlobalColor color);
  void downlight();
  void setPiece(Piece* piece);
  void removePiece();
  Position getPosition() const;
  Piece* getPiece() const;
  bool havePiece() const;
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
private:
  QGraphicsRectItem* square_;
  Qt::GlobalColor color_;
  Piece* piece_;
  bool highlighted_;
  Position position_;
};

class Board : public QGraphicsGridLayout{
public:
  Board(QGraphicsLayoutItem* parent = nullptr);
  ~Board() override = default;

  void selectPiece(Piece* selected);
  bool movePiece(const Position position);
  bool setGame(const std::list<std::string> specificationPiece);
  void setNewGame();
  std::map<std::string, Piece*>& getPieceMap();
private:
  std::map<Position, Square*> squareDict_;
  std::map<std::string, Piece*> pieceDict_;
  std::list<Square*> highlighted_;
  Piece* selected_;
  void setGrid();
};
