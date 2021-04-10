/**
* Gestion d'un jeu d'échec
* \file   chess.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsRectItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPalette>
#include <QObject>
#pragma pop()
#include <cppitertools/range.hpp>
#include <stdlib.h>
#include <time.h>
#include "Board.hpp"

Case::Case(const Qt::GlobalColor color) : color_(color), piece_(nullptr)
{
	setGeometry(0, 0, CASE_SIZE, CASE_SIZE);
	square_ = new QGraphicsRectItem();
	square_->setRect(0, 0, CASE_SIZE, CASE_SIZE);
	square_->setBrush(color);
	square_->setParentItem(this);
}

Case::~Case() {
	delete square_;
}

void Case::setPiece(Piece* piece) {
	piece_ = piece;
	//piece_->setParentLayoutItem(this);
	//setGraphicsItem(piece_);
}

void Case::removePiece() {
	piece_ = nullptr;
}

void Case::highlight(const Qt::GlobalColor color) {
	square_->setBrush(color);
}

void Case::downlight() {
	square_->setBrush(color_);
}

Board::Board(QGraphicsLayoutItem* parent) : QGraphicsGridLayout(parent){
	srand(time(NULL));
	QRectF rect(0, 0, CASE_SIZE, CASE_SIZE);
	setGeometry(rect);
	setHorizontalSpacing(1);
	setVerticalSpacing(1);
	setGrid();
	setPieceRandom();
	highlighted_ = {};
}

Board::~Board() {
	for (auto& [key, value] : pieceDict_) {
		removeItem(value);
		delete value;
	}
	for (auto& [key, value] : caseDict_) {
		removeItem(value);
		delete value;
	}
	pieceDict_.clear();
	caseDict_.clear();
	invalidate();
}


std::map<std::string, Case*> Board::caseDict_ = {};
std::map<std::string, Piece*> Board::pieceDict_ = {};
std::list<Case*> Board::highlighted_ = {};
Piece* Board::selected_ = nullptr;

std::map<std::string, Piece*>& Board::getPieceMap()
{
	return pieceDict_;
}

void Board::selectPiece(Piece* selected) {
	if (highlighted_.size() > 0) {
		while (highlighted_.size()) {
			highlighted_.front()->downlight();
			highlighted_.pop_front();
		}
	}
	if (selected_ != selected) {
		selected_ = selected;
		std::string tag = "";
		selected_->checkPossibility();
		for (Position it : selected->getPossibility()) {
			tag = "";
			tag += (char)('a' + it.y);
			tag += (char)('1' + it.x);
			if (caseDict_.find(tag) != caseDict_.end()) {
				highlighted_.push_back(caseDict_[tag]);
				caseDict_[tag]->highlight(Qt::green);
			}
		}
		if (highlighted_.size() == 0)
			selected_ = nullptr;
	}
	else {
		selected_ = nullptr;
	}
}

void Board::movePiece(Position position) {
	if (selected_->move(position)) {
		removeItem(selected_);
		addItem(selected_, position.x, position.y);
	}
}

void Board::setGrid() {
	std::string tag = "";
	char rowTag = 0, columnTag = 0;
	for (int row = 0; row < 8; ++row) {
		for (int column = 0; column < 8; ++column) {
			tag = "";
			tag += (char)('a' + row);
			tag += (char)('1' + column);
			Case* square;
			if ((row + column) % 2)
				square = new Case(Qt::blue);
			else
				square = new Case(Qt::cyan);
			square->setMinimumHeight(CASE_SIZE);
			square->setMinimumWidth(CASE_SIZE);
			addItem(square, row, column);
			caseDict_[tag] = square;
		}
	}
}

void Board::setPiece() {
	std::string tag = "";
	Piece* piece = nullptr;
	PieceColor color = black;
	for (int y : iter::range(8)){
		for (int x : iter::range(8)) {
			tag = "";
			if (color == white)
				tag += "W ";
			else
				tag += "B ";
			if (y == 0 || y == 7) {
				switch (x) {
				case 0: case 7:
					piece = new Rook(color, Position(x, y));
					tag += "R1";
					break;
				case 1: case 6:
					piece = new Knight(color, Position(x, y));
					tag += "N1";
					break;
				case 2: case 5:
					piece = new Bishop(color, Position(x, y));
					tag += "B1";
					break;
				case 3:
					piece = new Queen(color, Position(x, y));
					tag += "Q";
					break;
				case 4:
					piece = new King(color, Position(x, y));
					tag += "K";
					break;
				}
			}
			else if (y == 1 || y == 6) {
				piece = new Pawn(color, Position(x, y));
				tag += "P1";
			}
			if (y <= 1 || y == 6 || y == 7) {
				//caseDict_[std::string() + (char)('a' + y) + (char)('1' + x)]->setPiece(piece);
				addItem(piece, y, x);
				while (pieceDict_.find(tag) != pieceDict_.end()) {
					tag[3] = tag[3] + 1;
				}
				pieceDict_[tag] = piece;
				if (y == 1 && x == 7) {
					x = 7;
					y = 5;
					color = white;
				}
			}
		}
	}
}

void Board::setPieceRandom() {
	std::string tag = "";
	Piece* piece = nullptr;
	PieceColor color = black;
	for (int i : iter::range(32)) {
		tag = "";
		if (color == white)
			tag += "W ";
		else
			tag += "B ";
		Position position;
		position.x = rand() % 8;
		position.y = rand() % 8;
		while (dynamic_cast<Piece*>(itemAt(position.y, position.x))) {
			position.x = rand() % 8;
			position.y = rand() % 8;
		}
		switch (i % 17) {
		case 0: case 1:
			piece = new Rook(color, position);
			tag += "R1";
			break;
		case 2: case 3:
			piece = new Knight(color, position);
			tag += "N1";
			break;
		case 4: case 5:
			piece = new Bishop(color, position);
			tag += "B1";
			break;
		case 6:
			piece = new Queen(color, position);
			tag += "Q";
			break;
		case 7:
			piece = new King(color, position);
			tag += "K";
			break;
		default:
			piece = new Pawn(color, position);
			tag += "P1";
			break;
		}
		//caseDict_[std::string() + (char)('a' + position.y) + (char)('1' + position.x)]->setPiece(piece);
		addItem(piece, position.y, position.x);
		while (pieceDict_.find(tag) != pieceDict_.end())
			tag[3] = tag[3] + 1;
		pieceDict_[tag] = piece;
		if (i > 16)
			color = white;
	}
}