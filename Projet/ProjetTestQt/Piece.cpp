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

#include "Piece.hpp"
#include "Board.hpp"

using iter::range;

Position::Position(unsigned char x, unsigned char y) {
	this->x = x;
	this->y = y;
}

Position::Position(std::string name) {
	if (name.size() >= 2) {
		x = name[0];
		y = name[1];
	}
}

std::string Position::name(){
	return (std::string() + (char)x + (char)y);
}

bool Position::operator==(Position autre) const { return x == autre.x && y == autre.y; }

bool Position::operator<(Position autre) const {
	if (x == autre.x)
		return y < autre.y;
	return x < autre.x;
}

Piece::Piece(const PieceColor& color, 
						 const Position& position,
						 const unsigned char& type,
						 QGraphicsItem* parent) : QGraphicsWidget(parent),
																		  color_(color),
																			position_(position),
																			lastPosition_(position),
																			possibility_({}) {
	Square* square = dynamic_cast<Square*>(parentItem());
	Board* board = dynamic_cast<Board*>(square->parentLayoutItem());
	allPieces_ = &(board->getPieceMap());
	if (color == white)
		name_ = "W";
	else
		name_ = "B";
	name_ += type;
	name_ += "1";
	while (allPieces_->find(name_) != allPieces_->end()) {
		name_[2] = name_[2] + 1;
	}
}

std::string Piece::getName() const { return name_; }

void Piece::setPicture(const QRect& pictureRect) {
	QImage image("pieces.png");
	QTransform trans;
	image = image.copy(pictureRect).transformed(trans.translate(-pictureRect.x(), -pictureRect.y()));
	picture_ = new QGraphicsPixmapItem(QPixmap::fromImage(image), this);
}

PieceColor Piece::getColor() const { return color_; }

Position Piece::getPosition() const { return position_; }

void Piece::clearPossibility() {
	while (possibility_.size() != 0)
		possibility_.pop_back();
}

std::list<Position> Piece::getPossibility() {
	if(possibility_.size() == 0)
		checkPossibility();
	return possibility_;
}

bool Piece::move(Position position) {
	for (auto it : getPossibility()) {
		if (it == position) {
			lastPosition_ = position_;
			position_ = position;
			update();
			return true;
		}
	}
	return false;
}

AddMoveState Piece::addMove(Position position) {
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

void Piece::addDirection(int iterateX, int iterateY, iter::impl::Range<int> range) {
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

void Piece::cancelMove() {
	position_ = lastPosition_;
}

bool Piece::atAlly(Position position) const {
	for (auto& [key, value] : *allPieces_) {
		if (value->getPosition() == position && value->getColor() == color_)
			return true;
	}
	return false;
}

bool Piece::atEnemy(Position position) const {
	for (auto& [key, value] : *allPieces_) {
		if (value->getPosition() == position && value->getColor() != color_)
			return true;
	}
	return false;
}

void Piece::click()
{
	update();
	Square* square = dynamic_cast<Square*>(parentItem());
	Board* board = dynamic_cast<Board*>(square->parentLayoutItem());
	board->selectPiece(this);
}

King::King(const PieceColor& color, 
					 const Position& position, 
					 QGraphicsItem* parent) : Piece(color, position, 'K', parent)
{
	if (color == black)
		setPicture(QRect(-15, 148, CASE_SIZE, CASE_SIZE));
	else
		setPicture(QRect(-13, 349, CASE_SIZE, CASE_SIZE));
}

void King::checkPossibility() {
	possibility_.clear();
	std::list<Position> possibility;
	for (int x : iter::range(-1, 2)) {
		for (int y : iter::range(-1, 2)) {
			Position test(position_.x + x, position_.y + y);
			addMove(test);
		}
	}
}

Queen::Queen(const PieceColor& color, 
						 const Position& position, 
						 QGraphicsItem* parent) : Piece(color, position, 'Q', parent) {
	if (color == black)
		setPicture(QRect(221, 149, CASE_SIZE, CASE_SIZE));
	else
		setPicture(QRect(223, 350, CASE_SIZE, CASE_SIZE));
}

void Queen::checkPossibility() {
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

Knight::Knight(const PieceColor& color, 
							 const Position& position, 
							 QGraphicsItem* parent) : Piece(color, position, 'N', parent) {
	if (color == black)
		setPicture(QRect(932, 154, CASE_SIZE, CASE_SIZE));
	else
		setPicture(QRect(932, 355, CASE_SIZE, CASE_SIZE));
}

void Knight::checkPossibility() {
	possibility_.clear();
	std::list<Position> possibility;
	for (int x : iter::range(-2, 3)) {
		for (int y : iter::range(-2, 3)) {
			if ((x != 0) && (y != 0) && (x != y) && (-x != y)) {
				Position test(position_.x + x, position_.y + y);
				addMove(test);
			}
		}
	}
}

Bishop::Bishop(const PieceColor& color, 
							 const Position& position, 
							 QGraphicsItem* parent) : Piece(color, position, 'B', parent) {
	if (color == black)
		setPicture(QRect(695, 149, CASE_SIZE, CASE_SIZE));
	else
		setPicture(QRect(697, 349, CASE_SIZE, CASE_SIZE));
}

void Bishop::checkPossibility() {
	possibility_.clear();
	addDirection(1, 1, iter::range(1, 8));
	addDirection(-1, 1, iter::range(1, 8));
	addDirection(1, -1, iter::range(1, 8));
	addDirection(-1, -1, iter::range(1, 8));
}

Rook::Rook(const PieceColor& color, 
					 const Position& position, 
					 QGraphicsItem* parent) : Piece(color, position, 'R', parent) {
	if (color == black)
		setPicture(QRect(459, 154, CASE_SIZE, CASE_SIZE));
	else
		setPicture(QRect(460, 355, CASE_SIZE, CASE_SIZE));
}

void Rook::checkPossibility() {
	possibility_.clear();
	addDirection(1, 0, iter::range(1, 8));
	addDirection(-1, 0, iter::range(1, 8));
	addDirection(0, 1, iter::range(1, 8));
	addDirection(0, -1, iter::range(1, 8));
}

Pawn::Pawn(const PieceColor& color, 
					 const Position& position, 
					 QGraphicsItem* parent) : Piece(color, position, 'P', parent) {
	if (color == black)
		setPicture(QRect(1168, 154, CASE_SIZE, CASE_SIZE));
	else
		setPicture(QRect(1170, 355, CASE_SIZE, CASE_SIZE));
}

void Pawn::checkPossibility() {
	possibility_.clear();
	Position test;
	char direction = 1;
	int maxMove = 1;
	bool valid = true;

	if (color_ == black)
		direction = -1;
	if ((color_ == black && position_.y == '7') || (color_ == white && position_.y == '2')) // TODO : À revoir
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

