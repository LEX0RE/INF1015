/**
* Gestion d'une planche du jeu d'échec
* \file   Board.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsRectItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPalette>
#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#pragma pop()
#include <cppitertools/range.hpp>
#include <stdlib.h>
#include "Board.hpp"
#include "Chess.hpp"

Square::Square(const Qt::GlobalColor color,
					     Position position,
							 QGraphicsItem* parent) : color_(color),
															      piece_(nullptr), 
																	  highlighted_(false), 
																		position_(position),
																		QGraphicsWidget(parent)
{
	QGraphicsWidget::setGeometry(0, 0, CASE_SIZE, CASE_SIZE);
	square_ = new QGraphicsRectItem();
	square_->setRect(0, 0, CASE_SIZE, CASE_SIZE);
	square_->setBrush(color);
	square_->setParentItem(this);
	setOwnedByLayout(true);
}

Position Square::getPosition() const { return position_; }

void Square::setPiece(Piece* piece) {
	piece_ = piece;
	piece_->setParentItem(this);
}

void Square::removePiece() {
	piece_ = nullptr;
}

void Square::highlight(const Qt::GlobalColor color) {
	highlighted_ = true;
	square_->setBrush(color);
}

void Square::downlight() {
	highlighted_ = false;
	square_->setBrush(color_);
}

void Square::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	update();
	if (highlighted_ == true) {
		Board* parent = dynamic_cast<Board*>(parentLayoutItem());
		if (parent != nullptr)
			parent->movePiece(position_);
	}
	else if(piece_ != nullptr)
		piece_->click();
	QGraphicsWidget::mousePressEvent(event);
}

bool Square::havePiece() const { return (piece_ != nullptr); }

Piece* Square::getPiece() const { return piece_; }

Board::Board(QGraphicsLayoutItem* parent) : QGraphicsGridLayout(parent){
	squareDict_ = {};
	pieceDict_ = {};
	highlighted_ = {};
	selected_ = nullptr;
	QRectF rect(0, 0, CASE_SIZE, CASE_SIZE);
	setGeometry(rect);
	setHorizontalSpacing(1);
	setVerticalSpacing(1);
	setGrid();
}

std::map<std::string, Piece*>& Board::getPieceMap() { return pieceDict_; }

void Board::selectPiece(Piece* selected) {
	if (highlighted_.size() > 0) {
		while (highlighted_.size()) {
			highlighted_.front()->downlight();
			highlighted_.pop_front();
		}
	}
	if (selected_ != selected) {
		selected_ = selected;
		for (Position it : selected->getPossibility()) {
			if (squareDict_.find(it) != squareDict_.end()) {
				highlighted_.push_back(squareDict_[it]);
				squareDict_[it]->highlight(Qt::green);
			}
		}
		if (highlighted_.size() == 0)
			selected_ = nullptr;
	}
	else {
		selected_ = nullptr;
	}
}

bool Board::movePiece(Position position) {
	Position lastPosition = selected_->getPosition(), newPosition = {};
	Square* lastCase = squareDict_[lastPosition];
	Piece* pieceEaten = nullptr;
	if (selected_->move(position)) {
		newPosition = selected_->getPosition();
		pieceEaten = squareDict_[newPosition]->getPiece();

		Position blackKingPosition = pieceDict_["BK1"]->getPosition();
		Position whiteKingPosition = pieceDict_["WK1"]->getPosition();
		for (auto& [key, value] : pieceDict_) {
			if ((value->getColor() != selected_->getColor()) && (pieceEaten != value)) {
				value->checkPossibility();
				for (auto position : value->getPossibility()) {
					if ((selected_->getColor() == black && position == blackKingPosition) ||
						 (selected_->getColor() == white && position == whiteKingPosition)) {
						selected_->cancelMove();
						return false;
					}
				}
			}
		}
			
		QString mouvement = "";
		squareDict_[lastPosition]->removePiece();
		if (selected_->getName()[1] != 'P')
			mouvement += selected_->getName()[1];
		mouvement += lastPosition.name().c_str();
		if (pieceEaten != nullptr) {
			pieceDict_.erase(pieceDict_.find(pieceEaten->getName()));
			delete pieceEaten;
			mouvement += "x";
		}
		else
			mouvement += "-";
		squareDict_[newPosition]->setPiece(selected_);
		mouvement += newPosition.name().c_str();
		lastCase->update();
		while (highlighted_.size()) {
			highlighted_.front()->downlight();
			highlighted_.pop_front();
		}
		if(parentLayoutItem())
			Chess::addHistoryMove(mouvement);
		selected_ = nullptr;
		for (auto& [key, value] : pieceDict_)
			value->checkPossibility();
		return true;
	}
	else
		return false;
}

void Board::setGrid() {
	Position position("a1");
	for (unsigned int y : iter::range(8)) {
		for (unsigned int x: iter::range(8)) {
			position = { (unsigned char)('a' + x), (unsigned char)('8' - y) };
			if ((y + x) % 2)
				addItem(new Square(Qt::blue, position), y, x);
			else
				addItem(new Square(Qt::cyan, position), y, x);
			itemAt(y, x)->setMinimumHeight(CASE_SIZE);
			itemAt(y, x)->setMinimumWidth(CASE_SIZE);
			squareDict_[position] = dynamic_cast<Square*>(itemAt(y, x));
		}
	}
}

bool Board::setGame(std::list<std::string> specificationPiece) {
	PieceColor color = white;
	bool valid = true;
	Piece* temporary = nullptr;
	Position position = Position("a1");
	std::string name = "";

	for (auto piece : specificationPiece) {
		if (piece[0] == 'W')
			color = white;
		else
			color = black;
		position = Position(piece[2], piece[3]);
		if (squareDict_[position]->havePiece() == false) {
			switch (piece[1]) {
			case 'K':
				temporary = new King(color, position, squareDict_[position]);
				name = temporary->getName(); // Le compilateur me faisait un warning lorsque je le mettais à la fin du switch...
				break;
			case 'Q':
				temporary = new Queen(color, position, squareDict_[position]);
				name = temporary->getName();
				break;
			case 'N':
				temporary = new Knight(color, position, squareDict_[position]);
				name = temporary->getName();
				break;
			case 'B':
				temporary = new Bishop(color, position, squareDict_[position]);
				name = temporary->getName();
				break;
			case 'P':
				if (position.y == '8' || position.y == '1')
					valid = false;
				else {
					temporary = new Pawn(color, position, squareDict_[position]);
					name = temporary->getName();
				}
				break;
			case 'R':
				temporary = new Rook(color, position, squareDict_[position]);
				name = temporary->getName();
				break;
			}
			if (valid == true) {
				pieceDict_[name] = temporary;
				squareDict_[position]->setPiece(temporary);
			}
		}
		else
			valid = false;
		temporary = nullptr;
	}
	if ((pieceDict_.find("WK2") != pieceDict_.end()) || (pieceDict_.find("BK2") != pieceDict_.end()))
		valid = false;

	if (valid == false) {
		for (auto& [key, value] : squareDict_) {
			if (value->getPiece() != nullptr) {
				pieceDict_.erase(pieceDict_.find(value->getPiece()->getName()));
				delete value->getPiece();
				value->removePiece();
			}
		}
		pieceDict_.clear();
		return false;
	}
	return true;
}

void Board::setNewGame() {
	Piece* piece = nullptr;
	PieceColor color = black;
	Position position = {};
	std::string name = "";
	for (unsigned int y : iter::range(8)) {
		for (unsigned int x : iter::range(8)) {
			if (y <= 1 || y >= 6) {
				position = { (unsigned char)('a' + x), (unsigned char)('8' - y) };
				if (y == 0 || y == 7) {
					piece = nullptr;
					switch (x) {
					case 0: case 7:
						piece = new Rook(color, position, squareDict_[position]);
						name = piece->getName();
						break;
					case 1: case 6:
						piece = new Knight(color, position, squareDict_[position]);
						name = piece->getName();
						break;
					case 2: case 5:
						piece = new Bishop(color, position, squareDict_[position]);
						name = piece->getName();
						break;
					case 3:
						piece = new Queen(color, position, squareDict_[position]);
						name = piece->getName();
						break;
					case 4:
						piece = new King(color, position, squareDict_[position]);
						name = piece->getName();
						break;
					}
				}
				else {
					piece = new Pawn(color, position, squareDict_[position]);
					name = piece->getName();
				}
				pieceDict_[name] = piece;
				squareDict_[position]->setPiece(piece);
				if (y == 1 && x == 7) {
					x = 7;
					y = 5;
					color = white;
				}
			}
		}
	}
}