/**
* Gestion d'une pièce d'un jeu d'échec
* \file   Piece.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QPainter>
#pragma pop()
#include <iostream>
#include "Piece.hpp"
#include "Game.hpp"

using iter::range;
using namespace std;

class TooManyKings : public logic_error
{
public:
	using logic_error::logic_error;
};

class TwoSameColorKings : public logic_error
{
public:
	using logic_error::logic_error;
};

model::Position::Position(unsigned char x, unsigned char y) {
	this->x = x;
	this->y = y;
}

model::Position::Position(string name) {
	if (name.size() >= 2) {
		x = name[0];
		y = name[1];
	}
}

string model::Position::name(){
	return (string() + (char)x + (char)y);
}

bool model::Position::operator==(Position autre) const { return x == autre.x && y == autre.y; }

bool model::Position::operator<(Position autre) const {
	if (x == autre.x)
		return y < autre.y;
	return x < autre.x;
}

map<string, model::Piece*> model::Piece::allPieces_ = {};

model::Piece::Piece(const PieceColor& color,
						 const unsigned char& type,
						 const Position& position) : color_(color),
																				 position_(position),
																				 lastPosition_(position),
																				 possibility_({}) {
	if (color == white)
		name_ = "W";
	else
		name_ = "B";
	name_ += type;
	name_ += "1";
	while (allPieces_.find(name_) != allPieces_.end()) {
		name_[2] = name_[2] + 1;
	}
	allPieces_[name_] = this;
}

model::Piece::~Piece() {
	allPieces_.erase(name_);
}

string model::Piece::getName() const { return name_; }

model::PieceColor model::Piece::getColor() const { return color_; }

model::Position model::Piece::getPosition() const { return position_; }

void model::Piece::generatePossibility() {
	bool blackCheck = false, whiteCheck = false;
	for (auto& [key, value] : allPieces_)
		value->checkPossibility();

	for (auto& [key, value] : allPieces_)
		value->removeCheckSelfPossibility();
}

void model::Piece::removeCheckSelfPossibility() {
	list<Position> toRemove;
	if (possibility_.size() != 0) {
		for (auto position : possibility_) {
			if (isRemovingCheck(position) == false) {
				toRemove.push_back(position);
			}
		}
	}
	if (toRemove.size() != 0) {
		for (auto position : toRemove)
			possibility_.remove(position);
	}
}

list<model::Position> model::Piece::getPossibility() { return possibility_; }

bool model::Piece::movePiece(const Position& position) {
	for (auto it : getPossibility()) {
		if (it == position) {
			lastPosition_ = position_;
			position_ = position;
			return true;
		}
	}
	return false;
}

bool model::Piece::isDoingCheck() {
	if (isKingAlive()) {
		Position kingPosition;
		if (color_ == white)
			kingPosition = allPieces_["BK1"]->getPosition();
		else
			kingPosition = allPieces_["WK1"]->getPosition();

		for (auto it : possibility_) {
			if (it == kingPosition) {
				return true;
			}
		}
		return false;
	}
	return true;
}

bool model::Piece::isKingAlive() const {
	if (allPieces_["BK1"] != nullptr && allPieces_["WK1"] != nullptr)
		return true;
	return false;
}

bool model::Piece::isRemovingCheck(const Position& position) {
	if (isKingAlive()) {
		Position piecePosition = position_, kingPosition;
		Piece* pieceEaten = nullptr;
		if (allPieces_["WK1"] == this || allPieces_["BK1"] == this)
			kingPosition = position;
		else if (color_ == white)
			kingPosition = allPieces_["BK1"]->getPosition();
		else
			kingPosition = allPieces_["WK1"]->getPosition();

		for (auto& [key, value] : allPieces_) {
			if (value->getPosition() == position) {
				pieceEaten = value;
				pieceEaten->position_ = Position("z0");
			}
		}
		position_ = position;

		for (auto& [key, value] : allPieces_) {
			list<Position> savePosibility = move(value->possibility_);

			value->checkPossibility();

			if ((value->getColor() != color_) && (position != value->getPosition())) {
				if (value->isDoingCheck()) {

					if (pieceEaten != nullptr)
						pieceEaten->position_ = position;

					value->possibility_ = move(savePosibility);
					position_ = piecePosition;
					return false;
				}
			}
			value->possibility_ = move(savePosibility);
		}

		if (pieceEaten != nullptr)
			pieceEaten->position_ = position;

		position_ = piecePosition;
		return true;
	}
	return false;
}

model::AddMoveState model::Piece::addMove(const Position& position) {
	if (position != position_) {
		if (position.x >= 'a' && position.x <= 'h' && position.y <= '8' && position.y >= '1') {
			if (atAlly(position))
				return stop;
			possibility_.push_back(position);
			if (atEnemy(position))
				return stop;
			return add;
		}
	}
	return stop;
}

void model::Piece::addDirection(int iterateX, int iterateY, iter::impl::Range<int> range) {
	bool valid = true;
	Position test;

	for (int i : range) {
		if (valid) {
			Position test = Position(position_.x + (i * iterateX), position_.y + (i * iterateY));
			if (addMove(test) == stop)
				valid = false;
		}
	}
}

void model::Piece::cancelMove() {
	position_ = lastPosition_;
}

bool model::Piece::atAlly(const Position& position) const {
	for (auto& [key, value] : allPieces_) {
		if (value->getPosition() == position && value->getColor() == color_)
			return true;
	}
	return false;
}

bool model::Piece::atEnemy(const Position& position) const {
	for (auto& [key, value] : allPieces_) {
		if (value->getPosition() == position && value->getColor() != color_)
			return true;
	}
	return false;
}

list<model::King*> model::King::instanceList_ = {};

model::King* model::King::getInstance(const PieceColor& color, const Position& position) {
	King* instance = nullptr;
	try {
		if (instanceList_.size() < 2) {
			if (instanceList_.size() == 0) {
				instance = new King(color, position);
				instanceList_.push_back(instance);
			}
			else if (instanceList_.front()->color_ != color) {
				instance = new King(color, position);
				instanceList_.push_back(instance);
			}
			else {
				throw TwoSameColorKings("Two Kings of the same color have been created");
			}
		}
		else {
			throw TooManyKings("Too many Kings have been created");
		}
	}
	catch (TwoSameColorKings& e) {
		std::cout << e.what() << std::endl;
	}
	catch (TooManyKings& e) {
		std::cout << e.what() << std::endl;
	}
	return instanceList_.back();
}

model::King::~King() {
	if (instanceList_.size()) {
		King* toDelete = nullptr;

		for (auto it : instanceList_) {
			if (it == this) {
				toDelete = it;
			}
		}
		instanceList_.remove(toDelete);
	}
}

model::King::King(const PieceColor& color, const Position& position) : Piece(color, 'K', position){}

void model::King::checkPossibility() {
	possibility_.clear();
	list<Position> possibility;
	for (int x : iter::range(-1, 2)) {
		for (int y : iter::range(-1, 2)) {
			if (x != 0 || y != 0) {
				Position test(position_.x + x, position_.y + y);
				addMove(test);
			}
		}
	}
}

model::Queen::Queen(const PieceColor& color, const Position& position) : Piece(color, 'Q', position) {}

void model::Queen::checkPossibility() {
	possibility_.clear();
	addDirection(1, 1, iter::range(1, 8));
	addDirection(-1, 1, iter::range(1, 8));
	addDirection(1, -1, iter::range(1, 8));
	addDirection(-1, -1, iter::range(1, 8));
	addDirection(1, 0, iter::range(1, 8));
	addDirection(-1, 0, iter::range(1, 8));
	addDirection(0, 1, iter::range(1, 8));
	addDirection(0, -1, iter::range(1, 8));
}

model::Knight::Knight(const PieceColor& color, const Position& position) : Piece(color, 'N', position) {}

void model::Knight::checkPossibility() {
	possibility_.clear();
	list<Position> possibility;
	for (int x : iter::range(-2, 3)) {
		for (int y : iter::range(-2, 3)) {
			if ((x != 0) && (y != 0) && (x != y) && (-x != y)) {
				Position test(position_.x + x, position_.y + y);
				addMove(test);
			}
		}
	}
}

model::Bishop::Bishop(const PieceColor& color, const Position& position) : Piece(color, 'B', position) {}

void model::Bishop::checkPossibility() {
	possibility_.clear();
	addDirection(1, 1, iter::range(1, 8));
	addDirection(-1, 1, iter::range(1, 8));
	addDirection(1, -1, iter::range(1, 8));
	addDirection(-1, -1, iter::range(1, 8));
}

model::Rook::Rook(const PieceColor& color, const Position& position) : Piece(color, 'R', position) {}

void model::Rook::checkPossibility() {
	possibility_.clear();
	addDirection(1, 0, iter::range(1, 8));
	addDirection(-1, 0, iter::range(1, 8));
	addDirection(0, 1, iter::range(1, 8));
	addDirection(0, -1, iter::range(1, 8));
}

model::Pawn::Pawn(const PieceColor& color, const Position& position) : Piece(color, 'P', position) {}

void model::Pawn::checkPossibility() {
	possibility_.clear();
	Position test;
	char direction = 1;
	int maxMove = 1;
	bool valid = true;

	if (color_ == black)
		direction = -1;
	if ((color_ == black && position_.y == '7') || (color_ == white && position_.y == '2'))
		maxMove = 2;

	for (int i : iter::range(1, 1 + maxMove)) {
		if (valid) {
			Position test = Position(position_.x, position_.y + (i * direction));
			if (atEnemy(test) == false) {
				if (addMove(test) == stop)
					valid = false;
			}
			else
				valid = false;
		}
	}
	test = Position(position_.x - 1, position_.y + direction);
	if (atEnemy(test))
		addMove(test);
	test.x += 2;
	if (atEnemy(test))
		addMove(test);
}
