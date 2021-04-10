#pragma once
/**
* Librairie pour la gestion d'une pièce d'un jeu d'échec
* \file   piece.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/

#include <list>
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QPixmap>
#include <QGraphicsWidget>
#pragma pop()
#include <cppitertools/range.hpp>

// Image au lien suivant : https://pixabay.com/fr/vectors/d-%C3%A9checs-pi%C3%A8ces-ensemble-symboles-26774/

enum PieceColor{white, black};

enum AddMoveState{stop, add};

struct Position {
	unsigned int x, y;

	bool operator==(Position autre) const;
};

class Piece : public QGraphicsLayoutItem, public QGraphicsItem {
public:
	Piece(const PieceColor& color, const Position& position, QGraphicsItem* parent = nullptr);
	void setPicture(const QRect& pictureRect);
	Position getPosition() const;
	PieceColor getColor() const;
	virtual void checkPossibility() = 0;
	std::list<Position> getPossibility() const;
	AddMoveState addMove(Position position);
	void addDirection(int iterateX, int iterateY, iter::impl::Range<int> range);
	bool move(Position position);
	bool atAlly(Position position) const;
	bool atEnemy(Position position) const;

	void setGeometry(const QRectF& geom) override;
	QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;
	QRectF boundingRect() const override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
protected:
	PieceColor color_;
	Position position_;
	QPixmap picture_;
	std::list<Position> possibility_;
	bool moved_;

	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

class King : public Piece {
public:
	King(const PieceColor& color, const Position& position, QGraphicsItem* parent = nullptr);

	void checkPossibility() override;
};

class Queen : public Piece {
public:
	Queen(const PieceColor& color, const Position& position, QGraphicsItem* parent = nullptr);

	void checkPossibility() override;
};

class Knight : public Piece {
public:
	Knight(const PieceColor& color, const Position& position, QGraphicsItem* parent = nullptr);

	void checkPossibility() override;
};

class Bishop : public Piece {
public:
	Bishop(const PieceColor& color, const Position& position, QGraphicsItem* parent = nullptr);

	void checkPossibility() override;
};

class Rook : public Piece {
public:
	Rook(const PieceColor& color, const Position& position, QGraphicsItem* parent = nullptr);

	void checkPossibility() override;
};

class Pawn : public Piece {
public:
	Pawn(const PieceColor& color, const Position& position, QGraphicsItem* parent = nullptr);

	void checkPossibility() override;
};
