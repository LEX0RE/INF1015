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
#include "Board.hpp"

Case::Case(const Qt::GlobalColor color) : color_(color)
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

void Case::highlight(const Qt::GlobalColor color) {
	square_->setBrush(color);
}

void Case::downlight() {
	square_->setBrush(color_);
}

Board::Board(QGraphicsLayoutItem* parent) : QGraphicsGridLayout(parent){
	QRectF rect(0, 0, CASE_SIZE, CASE_SIZE);
	setGeometry(rect);
	setHorizontalSpacing(1);
	setVerticalSpacing(1);
	setGrid();
	setPiece();
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

std::map<std::string, Piece*>& Board::getPieceMap()
{
	return pieceDict_;
}

void Board::toggleHighlightCase(const std::list<Position>& caseList) {
	if (highlighted_.size() > 0) {
		while (highlighted_.size()) {
			highlighted_.front()->downlight();
			highlighted_.pop_front();
		}
		return;
	}
	else {
		std::string tag = "";
		for (Position it : caseList) {
			tag = "";
			tag += (char)('a' + it.y);
			tag += (char)('1' + it.x);
			if (caseDict_.find(tag) != caseDict_.end()) {
				highlighted_.push_back(caseDict_[tag]);
				caseDict_[tag]->highlight(Qt::green);
			}
		}
	}
}

void Board::movePiece(Piece* piece, Position position) {
	if (piece->move(position)) {
		removeItem(piece);
		addItem(piece, position.x, position.y);
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
	for (unsigned int y = 0; y < 8; y++) {
		for (unsigned int x = 0; x < 8; x++) {
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
			else {
				piece = new Pawn(color, Position(x, y));
				tag += "P1";
			}
			addItem(piece, y, x);
			//connect(piece, SIGNAL(Piece::move()), this, SLOT(Board::movePiece(Piece*, Position)));
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