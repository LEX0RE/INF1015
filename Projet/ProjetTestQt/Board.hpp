#pragma once
/**
* Gestion d'un jeu d'échec
* \file   chess.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
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

struct Case : public QGraphicsWidget {
public:
  Case(const Qt::GlobalColor color, Position position, std::string name);
  ~Case() override;
  std::string getName() const;

  void highlight(const Qt::GlobalColor color);
  void downlight();
  void setPiece(Piece* piece);
  void removePiece();
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
  std::string name_;
};

class Board : public QGraphicsGridLayout{
public:
  Board(QGraphicsLayoutItem* parent = nullptr);
  ~Board() override;

  static void selectPiece(Piece* selected);
  void movePiece(Position position);
  void addPiece(Piece* piece, Position position);

  static std::map<std::string, Piece*>& getPieceMap();
private:
  static std::map<std::string, Case*> caseDict_;
  static std::map<std::string, Piece*> pieceDict_;
  static std::list<Case*> highlighted_;
  static Piece* selected_;
  void setGrid();
  void setPiece();
  void setPieceRandom();
};
