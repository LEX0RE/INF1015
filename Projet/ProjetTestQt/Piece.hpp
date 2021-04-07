#pragma once
/**
* Librairie pour la gestion d'une pièce d'un jeu d'échec
* \file   piece.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/
#include <list>

enum Color{white, black};

struct Position {
	unsigned int x, y;

	bool operator==(Position autre) const;
};

class Piece {
public:
	Piece(const Color& color, const Position& position);
	Color getColor() const;
	Position getPosition() const;
	virtual std::list<Position*> checkMove() = 0;
	void move(Position position);
protected:
	Color color_;
	Position position_;
};

class King : public Piece {
public:
	King(const Color& color, const Position& position);

	std::list<Position*> checkMove() override;
};

class Queen : public Piece {
public:
	Queen(const Color& color, const Position& position);

	std::list<Position*> checkMove() override;
};

class Knight : public Piece {
public:
	Knight(const Color& color, const Position& position);

	std::list<Position*> checkMove() override;
};

class Bishop : public Piece {
public:
	Bishop(const Color& color, const Position& position);

	std::list<Position*> checkMove() override;
};

class Rook : public Piece {
public:
	Rook(const Color& color, const Position& position);

	std::list<Position*> checkMove() override;
};

class Pawn : public Piece {
public:
	Pawn(const Color& color, const Position& position);

	std::list<Position*> checkMove() override;
};
