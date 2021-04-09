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
  Case(const Qt::GlobalColor color);
  ~Case() override;

  void highlight(const Qt::GlobalColor color);
  void downlight();
private:
  QGraphicsRectItem* square_;
  Qt::GlobalColor color_;
};

class Board : public QGraphicsGridLayout, public QObject {
public:
  Board(QGraphicsLayoutItem* parent = nullptr);
  ~Board() override;

  static void toggleHighlightCase(const std::list<Position>& caseList);
  void movePiece(Piece* piece, Position position);

  static std::map<std::string, Piece*>& getPieceMap();
private:
  static std::map<std::string, Case*> caseDict_;
  static std::map<std::string, Piece*> pieceDict_;
  static std::list<Case*> highlighted_;
  //Piece* selected_;
  void setGrid();
  void setPiece();
};
