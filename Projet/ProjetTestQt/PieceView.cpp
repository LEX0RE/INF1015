/**
* Gestion de la vue des pièces d'un jeu d'échec
* \file   PieceView.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   04 mai 2021
* Cree le 04 mai 2021
*/

#include "PieceView.hpp"

view::PieceView::PieceView(std::string name, QGraphicsItem* parent) : name_(name), QGraphicsWidget(parent) {}

std::string view::PieceView::getName() const { return name_; }

void view::PieceView::setPicture(const QRect& pictureRect) {
	QImage image("pieces.png");
	QTransform trans;

	image = image.copy(pictureRect).transformed(trans.translate(-pictureRect.x(), -pictureRect.y()));
	picture_ = new QGraphicsPixmapItem(QPixmap::fromImage(image), this);
}


view::KingView::KingView(std::string name, QGraphicsItem* parent) : PieceView(name, parent) {
	if (name[0] == 'B')
		setPicture(QRect(-15, 148, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(-13, 349, SQUARE_SIZE, SQUARE_SIZE));
}

view::QueenView::QueenView(std::string name, QGraphicsItem* parent) : PieceView(name, parent) {
	if (name[0] == 'B')
		setPicture(QRect(221, 149, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(223, 350, SQUARE_SIZE, SQUARE_SIZE));
}

view::BishopView::BishopView(std::string name, QGraphicsItem* parent) : PieceView(name, parent) {
	if (name[0] == 'B')
		setPicture(QRect(695, 149, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(697, 349, SQUARE_SIZE, SQUARE_SIZE));
}

view::KnightView::KnightView(std::string name, QGraphicsItem* parent) : PieceView(name, parent) {
	if (name[0] == 'B')
		setPicture(QRect(932, 154, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(932, 355, SQUARE_SIZE, SQUARE_SIZE));
}

view::RookView::RookView(std::string name, QGraphicsItem* parent) : PieceView(name, parent) {
	if (name[0] == 'B')
		setPicture(QRect(459, 154, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(460, 355, SQUARE_SIZE, SQUARE_SIZE));
}

view::PawnView::PawnView(std::string name, QGraphicsItem* parent) : PieceView(name, parent) {
	if (name[0] == 'B')
		setPicture(QRect(1168, 154, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(1170, 355, SQUARE_SIZE, SQUARE_SIZE));
}