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

#include "Piece.hpp"
#include "Board.hpp"

using iter::range;

bool Position::operator==(Position autre) const { return autre.x == x && autre.y == y; }

Piece::Piece(const PieceColor& color, 
						 const Position& position, 
						 QGraphicsItem* parent) : QGraphicsLayoutItem(), 
																			QGraphicsItem(parent),
																			color_(color),
																			position_(position), 
																			moved_(false) {
	possibility_ = {};
}

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
	return QSizeF(100, 100);
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

std::list<Position> Piece::getPossibility() const { return possibility_; }

bool Piece::move(Position position) {
	checkPossibility();
	for (auto it : possibility_) {
		if (it == position) {
			position_ = position;
			return true;
		}
	}
	return false;
}

AddMoveState Piece::addMove(Position position) {
	if (position != position_) {
		if (position.x < 8 && position.y < 8) {
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
	Board::selectPiece(this);
}

King::King(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent)
{
	if (color == black)
		setPicture(QRect(-15, 148, 140, 140));
	else
		setPicture(QRect(-13, 349, 140, 140));
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

Queen::Queen(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent) {
	if (color == black)
		setPicture(QRect(221, 149, 140, 140));
	else
		setPicture(QRect(223, 350, 140, 140));
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

Knight::Knight(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent) {
	if (color == black)
		setPicture(QRect(932, 154, 140, 140));
	else
		setPicture(QRect(932, 355, 140, 140));
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

Bishop::Bishop(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent) {
	if (color == black)
		setPicture(QRect(695, 149, 140, 140));
	else
		setPicture(QRect(697, 349, 140, 140));
}

void Bishop::checkPossibility() {
	possibility_.clear();
	addDirection(1, 1, iter::range(1, 8));
	addDirection(-1, 1, iter::range(1, 8));
	addDirection(1, -1, iter::range(1, 8));
	addDirection(-1, -1, iter::range(1, 8));
}

Rook::Rook(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent) {
	if (color == black)
		setPicture(QRect(459, 154, 140, 140));
	else
		setPicture(QRect(460, 355, 140, 140));
}

void Rook::checkPossibility() {
	possibility_.clear();
	addDirection(1, 0, iter::range(1, 8));
	addDirection(-1, 0, iter::range(1, 8));
	addDirection(0, 1, iter::range(1, 8));
	addDirection(0, -1, iter::range(1, 8));
}

Pawn::Pawn(const PieceColor& color, const Position& position, QGraphicsItem* parent) : Piece(color, position, parent) {
	if (color == black)
		setPicture(QRect(1168, 154, 140, 140));
	else
		setPicture(QRect(1170, 355, 140, 140));
}

void Pawn::checkPossibility() {
	possibility_.clear();
	Position test;
	char direction = 1;
	int maxMove = 1;
	bool valid = true;

	if (color_ == white)
		direction = -1;
	if (moved_ == false)
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

