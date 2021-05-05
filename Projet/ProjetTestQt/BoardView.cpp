/**
* Gestion de la vue de la planche
* \file   BoardView.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   04 mai 2021
* Cree le 04 mai 2021
*/

#include "BoardView.hpp"
#include "include/cppitertools/range.hpp"
using namespace iter;

view::SquareView::SquareView(Qt::GlobalColor color, QPoint position, QGraphicsItem* parent) : QGraphicsWidget(parent) {
	color_ = color;
	position_ = position;
	piece_ = nullptr;
	QRectF rect(0, 0, SQUARE_SIZE, SQUARE_SIZE);

	square_ = new QGraphicsRectItem(rect, this);
	square_->setBrush(color_);
	square_->setParentItem(this);
	setOwnedByLayout(true);
	setGeometry(rect);
}

void view::SquareView::addPiece(std::string name) {
	if (piece_ != nullptr)
		delete piece_;

	unsigned char type = name[1];
	switch (type) {
	case 'K':
		piece_ = new KingView(name, this);
		break;
	case 'Q':
		piece_ = new QueenView(name, this);
		break;
	case 'B':
		piece_ = new BishopView(name, this);
		break;
	case 'N':
		piece_ = new KnightView(name, this);
		break;
	case 'R':
		piece_ = new RookView(name, this);
		break;
	case 'P':
		piece_ = new PawnView(name, this);
		break;
	default:
		break;
	}

	piece_->setParentItem(this);
}

void view::SquareView::addPiece(PieceView* piece) {
	if (piece_ != nullptr)
		delete piece_;

	piece_ = piece;
	piece_->setParentItem(this);
}

void view::SquareView::removePiece() { piece_ = nullptr; }

void view::SquareView::deletePiece() {
	if (piece_ != nullptr)
		delete piece_;

	removePiece();
}

void view::SquareView::highlight(Qt::GlobalColor color) {
	square_->setBrush(color);
}

void view::SquareView::lowlight() {
	square_->setBrush(color_);
}

void view::SquareView::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	model::Position position = model::Position('a' + position_.x(), '8' - position_.y());
	emit click(position);
}

view::PieceView* view::SquareView::getPiece() const { return piece_; }

view::BoardView::BoardView(QGraphicsItem* parent) : QGraphicsWidget(parent) {
	highlightSquareList_ = {};
	grid_ = new QGraphicsGridLayout(this);
	setGeometry(QRectF(0, 0, SQUARE_SIZE * N_SQUARE, SQUARE_SIZE * N_SQUARE));

	for (unsigned int y : range(8)) {
		for (unsigned int x : range(8)) {
			SquareView* square = nullptr;

			if ((x + y) % 2)
				square = new SquareView(Qt::blue, QPoint(x, y));
			else
				square = new SquareView(Qt::cyan, QPoint(x, y));

			grid_->addItem(square, y, x);
			squareList_.push_back(square);
		}
	}
	setLayout(grid_);
}

void view::BoardView::reloadPossibility(std::list<model::Position> possibility) {
	if (highlightSquareList_.size() > 0) {
		for (auto square : highlightSquareList_)
			square->lowlight();

		highlightSquareList_.clear();
	}
	else if (possibility.size() > 0) {
		for (auto position : possibility) {
			unsigned int x = position.x - 'a';
			unsigned int y = '8' - position.y;
			SquareView* square = dynamic_cast<SquareView*>(grid_->itemAt(y, x));

			if (square != nullptr)
				square->highlight(Qt::green);

			highlightSquareList_.push_back(square);
		}
	}
}

std::list<view::SquareView*> view::BoardView::getList() const { return squareList_; }

void view::BoardView::reloadPiece(std::map<std::string, model::Piece*> pieceMap) {
	if (pieceMap.size() > 0) {
		for (auto& [key, value] : pieceMap) {
			unsigned int x = value->getPosition().x - 'a';
			unsigned int y = '8' - value->getPosition().y;
			SquareView* square = dynamic_cast<SquareView*>(grid_->itemAt(y, x));
			PieceView* piece = nullptr;
			PieceView* pieceFound = nullptr;

			if (square != nullptr) {
				piece = square->getPiece();
				pieceFound = searchPiece(key);

				if (piece != nullptr) {
					if (piece->getName() != key) {
						square->deletePiece();
						squareOfPiece(pieceFound)->removePiece();

						if (pieceFound != nullptr)
							square->addPiece(pieceFound);
						else
							square->addPiece(key);
					}
				}
				else {
					squareOfPiece(pieceFound)->removePiece();

					if (pieceFound != nullptr)
						square->addPiece(pieceFound);
					else
						square->addPiece(key);
				}
			}
		}
	}
}

void view::BoardView::clearPieces() {
	for (auto y : range(N_SQUARE)) {
		for (auto x : range(N_SQUARE)) {
			SquareView* square = dynamic_cast<SquareView*>(grid_->itemAt(y, x));

			if (square != nullptr)
				square->deletePiece();
		}
	}
}

view::PieceView* view::BoardView::searchPiece(std::string name) const {
	for (auto y : range(N_SQUARE)) {
		for (auto x : range(N_SQUARE)) {
			SquareView* square = dynamic_cast<SquareView*>(grid_->itemAt(y, x));

			if (square != nullptr && square->getPiece() != nullptr) {
				if (square->getPiece()->getName() == name)
					return square->getPiece();
			}
		}
	}
	return nullptr;
}

view::SquareView* view::BoardView::squareOfPiece(PieceView* piece) const {
	for (auto y : range(N_SQUARE)) {
		for (auto x : range(N_SQUARE)) {
			SquareView* square = dynamic_cast<SquareView*>(grid_->itemAt(y, x));

			if (square != nullptr && square->getPiece() == piece)
					return square;
		}
	}
	return nullptr;
}