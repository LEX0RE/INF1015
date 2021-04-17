#pragma once
/**
* Déclaration pour la planche du jeu d'échec
* \file   BoardView.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/
/*
#define CASE_SIZE 140

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsGridLayout>
#include <QGraphicsRectItem>
#include <QGraphicsWidget>
#include <QBrush>
#pragma pop()
#include <map>
#include "PieceView.hpp"

struct SquareView : public QGraphicsWidget {
public:
  SquareView(const Qt::GlobalColor color, const Position position, QGraphicsItem* parent = nullptr); // Vue
  ~SquareView() override = default; // Vue

  void highlight(const Qt::GlobalColor color);
  void downlight();
  void setPiece(PieceView* piece);
  void removePiece();
  Position getPosition() const;
  PieceView* getPiece() const;
  bool havePiece() const;
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override; // Vue
private:
  QGraphicsRectItem* square_; // Vue
  Qt::GlobalColor color_; // Vue
  PieceView* piece_;
  bool highlighted_;
  Position position_;
};

class BoardView : public QGraphicsGridLayout{
public:
  BoardView(QGraphicsLayoutItem* parent = nullptr); // Vue
  ~BoardView() override = default; // Vue

  void selectPiece(PieceView* selected);
  bool movePiece(const Position position);
  bool setGame(const std::list<std::string> specificationPiece);
  void setNewGame();
  std::map<std::string, PieceView*>& getPieceMap();
private:
  std::map<Position, SquareView*> squareDict_;
  std::map<std::string, PieceView*> pieceDict_;
  std::list<SquareView*> highlighted_;
  PieceView* selected_;
  void setGrid();
};
*/