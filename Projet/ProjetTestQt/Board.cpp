/**
* Gestion d'un jeu d'échec
* \file   chess.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/

// TODO : En-tête, Revoir l'update des possibilités et rechecker ce qu'il faut avoir (checker pour for)

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
#include <time.h>
#include "Board.hpp"
#include "Chess.hpp"

Case::Case(const Qt::GlobalColor color, 
					 Position position, 
					 std::string name) : color_(color), 
															 piece_(nullptr), 
															 highlighted_(false), 
															 position_(position),
															 name_(name)
{
	QGraphicsWidget::setGeometry(0, 0, CASE_SIZE, CASE_SIZE);
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
	piece_->setParentItem(this);
}

void Case::removePiece() {
	piece_ = nullptr;
}

void Case::highlight(const Qt::GlobalColor color) {
	highlighted_ = true;
	square_->setBrush(color);
}

void Case::downlight() {
	highlighted_ = false;
	square_->setBrush(color_);
}

void Case::mousePressEvent(QGraphicsSceneMouseEvent* event) {
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

bool Case::havePiece() const {
	return piece_;
}

std::string Case::getName() const { return name_; }

Piece* Case::getPiece() const { return piece_; }

Board::Board(QGraphicsLayoutItem* parent) : QGraphicsGridLayout(parent){
	srand(time(NULL));
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
Piece* Board::selected_ = nullptr;

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
		std::string tag = "";
		selected_->checkPossibility();
		for (Position it : selected->getPossibility()) {
			tag = "";
			tag += (char)('a' + it.x);
			tag += (char)('8' - it.y);
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
	std::string tag = std::string() + (char)('a' + selected_->getPosition().x) + (char)('8' - selected_->getPosition().y);
	Case* lastCase = caseDict_[tag];
	Piece* pieceEaten;
	if (selected_->move(position)) {
		QString mouvement = "";
		caseDict_[tag]->removePiece();
		tag = std::string() + (char)('a' + selected_->getPosition().x) + (char)('8' - selected_->getPosition().y);
		pieceEaten = caseDict_[tag]->getPiece();
		if (selected_->getName()[2] != 'P')
			mouvement += selected_->getName()[2];
		mouvement += QString(lastCase->getName().c_str());
		if (pieceEaten != nullptr) {
			pieceDict_.erase(pieceDict_.find(pieceEaten->getName()));
			delete pieceEaten;
			mouvement += "x";
		}
		else
			mouvement += "-";
		caseDict_[tag]->setPiece(selected_);
		mouvement += QString(caseDict_[tag]->getName().c_str());
		lastCase->update();
		while (highlighted_.size()) {
			highlighted_.front()->downlight();
			highlighted_.pop_front();
		}
		Chess::addHistoryMove(mouvement);
		selected_ = nullptr;
	}
}

void Board::setGrid() {
	std::string tag = "";
	char rowTag = 0, columnTag = 0;
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			tag = "";
			tag += (char)('a' + x);
			tag += (char)('8' - y);
			Case* square;
			if ((y + x) % 2)
				square = new Case(Qt::blue, Position(x, y), tag);
			else
				square = new Case(Qt::cyan, Position(x, y), tag);
			square->QGraphicsWidget::setMinimumHeight(CASE_SIZE);
			square->QGraphicsWidget::setMinimumWidth(CASE_SIZE);
			addItem(square, y, x);
			caseDict_[tag] = square;
		}
	}
}

void Board::addPiece(Piece* piece, Position position) {

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
					tag += "R1";
					piece = new Rook(color, Position(x, y));
					break;
				case 1: case 6:
					tag += "N1";
					piece = new Knight(color, Position(x, y));
					break;
				case 2: case 5:
					tag += "B1";
					piece = new Bishop(color, Position(x, y));
					break;
				case 3:
					tag += "Q";
					piece = new Queen(color, Position(x, y));
					break;
				case 4:
					tag += "K";
					piece = new King(color, Position(x, y));
					break;
				}
			}
			else if (y == 1 || y == 6) {
				tag += "P1";
				piece = new Pawn(color, Position(x, y));
			}
			if (y <= 1 || y == 6 || y == 7) {
				caseDict_[std::string() + (char)('a' + x) + (char)('8' - y)]->setPiece(piece);
				while (pieceDict_.find(tag) != pieceDict_.end()) {
					tag[3] = tag[3] + 1;
				}
				pieceDict_[tag] = piece;
				piece->setName(tag);
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
		while (caseDict_[std::string() + (char)('a' + position.x) + (char)('8' - position.y)]->havePiece()) {
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
		caseDict_[std::string() + (char)('a' + position.x) + (char)('8' - position.y)]->setPiece(piece);
		while (pieceDict_.find(tag) != pieceDict_.end())
			tag[3] = tag[3] + 1;
		pieceDict_[tag] = piece;
		piece->setName(tag);
		if (i > 16)
			color = white;
	}
}