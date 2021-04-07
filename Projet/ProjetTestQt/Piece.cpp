/**
* Gestion d'une pièce d'un jeu d'échec
* \file   piece.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/
#include <cppitertools/range.hpp>

#include "Piece.hpp"

using iter::range;

bool Position::operator==(Position autre) const {
	return autre.x == x && autre.y == y;
}

Piece::Piece(const Color& color, const Position& position) : color_(color), position_(position) {}

Color Piece::getColor() const { return color_; }

Position Piece::getPosition() const { return position_; }

void Piece::move(Position position) {
	for (auto it : checkMove()) {
		if (*it == position)
			position_ = position;
	}
}

King::King(const Color& color, const Position& position) : Piece(color, position){}

std::list<Position*> King::checkMove() {
	std::list<Position*> possibility;
	possibility.push_back(new Position({ position_.x - 1, position_.y - 1 }));
	possibility.push_back(new Position({ position_.x - 1, position_.y }));
	possibility.push_back(new Position({ position_.x - 1, position_.y + 1 }));
	possibility.push_back(new Position({ position_.x, position_.y - 1 }));
	possibility.push_back(new Position({ position_.x, position_.y + 1 }));
	possibility.push_back(new Position({ position_.x + 1, position_.y - 1 }));
	possibility.push_back(new Position({ position_.x + 1, position_.y }));
	possibility.push_back(new Position({ position_.x + 1, position_.y + 1 }));
	return possibility;
}

Queen::Queen(const Color& color, const Position& position) : Piece(color, position) {}

std::list<Position*> Queen::checkMove() {
	std::list<Position*> possibility;
	return possibility;
}

Knight::Knight(const Color& color, const Position& position) : Piece(color, position) {}

std::list<Position*> Knight::checkMove() {
	std::list<Position*> possibility;
	return possibility;
}

Bishop::Bishop(const Color& color, const Position& position) : Piece(color, position) {}

std::list<Position*> Bishop::checkMove() {
	std::list<Position*> possibility;
	return possibility;
}

Rook::Rook(const Color& color, const Position& position) : Piece(color, position) {}

std::list<Position*> Rook::checkMove() {
	std::list<Position*> possibility;
	return possibility;
}

Pawn::Pawn(const Color& color, const Position& position) : Piece(color, position) {}

std::list<Position*> Pawn::checkMove() {
	std::list<Position*> possibility;
	return possibility;
}