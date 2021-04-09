/**
* Gestion d'une pièce d'un jeu d'échec
* \file   piece.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QPainter>
#pragma pop()

#include <cppitertools/range.hpp>
#include "Piece.hpp"
#include "Board.hpp"

using iter::range;

bool Position::operator==(Position autre) const { return autre.x == x && autre.y == y; }

Piece::Piece(const PieceColor& color, 
						 const Position& position, 
						 QGraphicsItem* parent) : QGraphicsLayoutItem(), 
																			QGraphicsItem(parent),
																			color_(color),
																			position_(position) {}

void Piece::setPicture(const QRect& pictureRect) {
	QImage image("Resources/pieces.png");
	QTransform trans;
	image = image.copy(pictureRect).transformed(trans.translate(-pictureRect.x(), -pictureRect.y()));
	picture_ = QPixmap::fromImage(image);
	setGraphicsItem(this);
}

PieceColor Piece::getColor() const { return color_; }

Position Piece::getPosition() const { return position_; }

void Piece::setGeometry(const QRectF& geom)
{
	prepareGeometryChange();
	QGraphicsLayoutItem::setGeometry(geom);
	setPos(geom.topLeft());
}

QSizeF Piece::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
	return QSizeF(140, 140);
}

QRectF Piece::boundingRect() const
{
	return QRectF(QPointF(0, 0), geometry().size());
}
void Piece::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(widget);
	Q_UNUSED(option);
	painter->drawPixmap(QRect(0, 0, 140, 140), picture_);
}

bool Piece::move(Position position) {
	for (auto it : checkMove()) {
		if (it == position) {
			position_ = position;
			return true;
		}
	}
	return false;
}

bool Piece::validPosition(Position position) const {
	if (position.x != 0 || position.y != 0) {
		if (position.x < 8 && position.y < 8)
			return true;
	}
	return false;
}

bool Piece::atAlly(Position position) const {
	for (auto& [key, value] : Board::getPieceMap()) {
		if (value->getPosition() == position && value->getColor() == color_)
			return true;
	}
	return false;
}

bool Piece::atEnemy(Position position) const {
	for (auto& [key, value] : Board::getPieceMap()) {
		if (value->getPosition() == position && value->getColor() != color_)
			return true;
	}
	return false;
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
	Board::toggleHighlightCase(checkMove());
}

King::King(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent)
{
	if (color == black)
		setPicture(QRect(-15, 148, 140, 140));
	else
		setPicture(QRect(-13, 349, 140, 140));
}

std::list<Position> King::checkMove() {
	std::list<Position> possibility;
	for (int x : iter::range(-1, 2)) {
		for (int y : iter::range(-1, 2)) {
			if(validPosition(Position(position_.x + x, position_.y + y)) == true)
				possibility.push_back(Position(position_.x + x, position_.y + y));
		}
	}
	return possibility;
}

Queen::Queen(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent) {
	if (color == black)
		setPicture(QRect(221, 149, 140, 140));
	else
		setPicture(QRect(223, 350, 140, 140));
}

std::list<Position> Queen::checkMove() {
	std::list<Position> possibility;
	
	return possibility;
}

Knight::Knight(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent) {
	if (color == black)
		setPicture(QRect(932, 154, 140, 140));
	else
		setPicture(QRect(932, 355, 140, 140));
}

std::list<Position> Knight::checkMove() {
	std::list<Position> possibility;
	return possibility;
}

Bishop::Bishop(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent) {
	if (color == black)
		setPicture(QRect(695, 149, 140, 140));
	else
		setPicture(QRect(697, 349, 140, 140));
}

std::list<Position> Bishop::checkMove() {
	std::list<Position> possibility;
	Position test(0, 0);
	return possibility;
}

/*
	//North west
	while () {
		test.x -= 1;
		test.y += 1;
		x = position_.x - 1;
		y = position_.y + 1;
		if (x && y < 8)
			if (!grid[x][y])
			possibility.push_back(new Position({x, y}));
		else:
			enemyPiecePosition.push_back(new Position({position_.x, position_.y}))
		}
	}

	//North east
	while () {
		possibility.push_back(new Position({}));
	}

	//South west
	while () {
		possibility.push_back(new Position({}));
	}

	//South east
	while () {
		possibility.push_back(new Position({}));
	}

	return possibility;
}
*/


Rook::Rook(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent) {
	if (color == black)
		setPicture(QRect(459, 154, 140, 140));
	else
		setPicture(QRect(460, 355, 140, 140));
}

std::list<Position> Rook::checkMove() {
	std::list<Position> possibility;
	bool invalid = false;
	Position test;

	for (int x : iter::range(-1, -8, -1)) {
		if (invalid == false) {
			test = Position(position_.x + x, position_.y);

			if (validPosition(test) == true) {
				if (atAlly(test))
					invalid = true;
				else {
					if (atEnemy(test))
						invalid = true;
					possibility.push_back(test);
				}
			}
		}
	}
	invalid = false;
	for (int x : iter::range(1, 8)) {
		if (invalid == false) {
			test = Position(position_.x + x, position_.y);

			if (validPosition(test) == true) {
				if (atAlly(test))
					invalid = true;
				else {
					if (atEnemy(test))
						invalid = true;
					possibility.push_back(test);
				}
			}
		}
	}
	invalid = false;
	for (int y : iter::range(-1, -8, -1)) {
		if (invalid == false) {
			test = Position(position_.x, position_.y + y);

			if (validPosition(test) == true) {
				if (atAlly(test))
					invalid = true;
				else {
					if (atEnemy(test))
						invalid = true;
					possibility.push_back(test);
				}
			}
		}
	}
	invalid = false;
	for (int y : iter::range(1, 8)) {
		if (invalid == false) {
			test = Position(position_.x, position_.y + y);

			if (validPosition(test) == true) {
				if (atAlly(test))
					invalid = true;
				else {
					if (atEnemy(test))
						invalid = true;
					possibility.push_back(test);
				}
			}
		}
	}
	return possibility;
}

Pawn::Pawn(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent) {
	if (color == black)
		setPicture(QRect(1168, 154, 140, 140));
	else
		setPicture(QRect(1170, 355, 140, 140));
}

std::list<Position> Pawn::checkMove() { // REVOIR SI PIECE LORSQUE 2 COUPS
	std::list<Position> possibility;
	char direction = 1;
	if (color_ == white) {
		direction = -1;
	}
	if (color_ == black && position_.y == 1) {
		if (validPosition(Position(position_.x, position_.y + direction * 2)) == true)
			possibility.push_back(Position(position_.x, position_.y + direction * 2));
	}
	else if (color_ == white && position_.y == 6) {
		if (validPosition(Position(position_.x, position_.y + direction * 2)) == true)
			possibility.push_back(Position(position_.x, position_.y + direction * 2));
	}
	if (validPosition(Position(position_.x, position_.y + direction)) == true)
		possibility.push_back(Position(position_.x, position_.y + direction));
	for (int x : range(-1, 2, 2)) {
		if (x != 0 || (position_.y + direction) != 0) {
			if (position_.x + x < 8 && position_.y + direction < 8) {
				for (auto& [key, value] : Board::getPieceMap()) {
					if (value->getPosition() == Position(position_.x + x, position_.y + direction)) {
						if (value->getColor() != color_)
							possibility.push_back(Position(position_.x, position_.y + direction));
					}
				}
			}
		}
	}
	return possibility;
}

