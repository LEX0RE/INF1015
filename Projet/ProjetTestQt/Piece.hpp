#pragma once
/**
* Librairie pour la gestion d'une pièce d'un jeu d'échec
* \file   Piece.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
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
	unsigned char x, y;
	Position() = default;
	Position(unsigned char x, unsigned char y);
	Position(std::string name);

	std::string name();
	bool operator==(Position autre) const;
	bool operator<(Position autre) const;
};

class Piece : public QGraphicsWidget {
	Q_OBJECT

public:
	Piece(const PieceColor& color, const Position& position, const unsigned char& type, QGraphicsItem* parent = nullptr);
	~Piece() override = default;
	std::string getName() const;
	void setPicture(const QRect& pictureRect);
	Position getPosition() const;
	PieceColor getColor() const;
	virtual void checkPossibility() = 0;
	std::list<Position> getPossibility();
	void clearPossibility();
	AddMoveState addMove(const Position position);
	void addDirection(int iterateX, int iterateY, iter::impl::Range<int> range);
	void cancelMove();
	bool move(const Position position);
	bool atAlly(const Position position) const;
	bool atEnemy(const Position position) const;
	void click();

protected:
	PieceColor color_;
	Position position_, lastPosition_;
	QGraphicsPixmapItem* picture_;
	std::list<Position> possibility_;
	std::string name_;
	std::map<std::string, Piece*>* allPieces_;
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
