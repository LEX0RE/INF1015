#define SQUARE_SIZE 140
#include "Chess.hpp"
#include "include/cppitertools/range.hpp"
using namespace iter;

view::WindowView::WindowView() {
	setStyleSheet("background-color:black;");
	setWindowTitle("Chess");
	setScene(new ChessScene());
	QGraphicsView::fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

view::WindowView::~WindowView() {
	QGraphicsScene* toDelete = scene();
	delete toDelete;
}

void view::WindowView::setNextScene(QGraphicsScene* scene) {
	if (scene != nullptr) {
		delete nextScene_;
		nextScene_ = scene;
	}
}

void view::WindowView::changeScene() {
	if (nextScene_ != nullptr)
		setScene(nextScene_);
}

view::ChessScene::ChessScene(QGraphicsView* parent) : QGraphicsScene(parent) {
	chessBoard_ = new BoardView();
	addItem(chessBoard_);
	game_ = new model::Game();
	connect(game_, &model::Game::updatePiece, chessBoard_, &BoardView::reloadPiece);
	connect(game_, &model::Game::updatePossibility, chessBoard_, &BoardView::reloadPossibility);
	game_->setNewGame();

	for (auto it : chessBoard_->getList())
		connect(it, &SquareView::click, game_, &model::Game::action);
}

view::ChessScene::~ChessScene() {
	delete game_;
}

view::BoardView::BoardView(QGraphicsItem* parent) : QGraphicsWidget(parent) {
	highlightSquareList_ = {};
	QRectF rect(0, 0, SQUARE_SIZE * 8, SQUARE_SIZE * 8);
	setGeometry(rect);
	grid_ = new QGraphicsGridLayout();

	for (unsigned int y : range(8)) {
		for (unsigned int x : range(8)) {
			SquareView* square = nullptr;
			if ((x + y) % 2)
				square = new SquareView(Qt::blue, QPoint(x, y)), y, x;
			else
				square = new SquareView(Qt::cyan, QPoint(x, y)), y, x;
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
	else {
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

view::SquareView::SquareView(Qt::GlobalColor color, QPoint position, 
														 QGraphicsItem* parent) : QGraphicsWidget(parent) {
	color_ = color;
	position_ = position;
	piece_ = nullptr;
	QRectF rect(0, 0, SQUARE_SIZE, SQUARE_SIZE);
	square_ = new QGraphicsRectItem(rect, this);
	square_->setBrush(color_);
	square_->setParentItem(this);
	setOwnedByLayout(true);
}

void view::SquareView::addPiece(PieceView* piece) {

	if (piece_ != nullptr)
		delete piece_;
	
	piece_ = piece;
	piece_->setParentItem(this);

}

void view::SquareView::removePiece() {
	if (piece_ != nullptr)
		delete piece_;

	piece_ = nullptr;
}

void view::SquareView::highlight(Qt::GlobalColor color) {
	square_->setBrush(color);
}

void view::SquareView::lowlight() {
	square_->setBrush(color_);
}


void view::BoardView::reloadPiece(std::map<std::string, model::Piece*> pieceMap) {
	clearPieces();

	if (pieceMap.size()) {
		for (auto& [key, value] : pieceMap) {
			unsigned int x = value->getPosition().x - 'a';
			unsigned int y = '8' - value->getPosition().y;
			SquareView* square = dynamic_cast<SquareView*>(grid_->itemAt(y, x));
			if (square != nullptr) {
				bool color = key[0] == 'W';
				unsigned char type = key[1];
				switch (type) {
				case 'K':
					square->addPiece(new KingView(color));
					break;
				case 'Q':
					square->addPiece(new QueenView(color));
					break;
				case 'B':
					square->addPiece(new BishopView(color));
					break;
				case 'N':
					square->addPiece(new KnightView(color));
					break;
				case 'R':
					square->addPiece(new RookView(color));
					break;
				case 'P':
					square->addPiece(new PawnView(color));
					break;
				default:
					break;
				}
			}
		}
	}
}

void view::BoardView::clearPieces() {
	for (auto y : range(8)) {
		for (auto x : range(8)) {
			SquareView* square = dynamic_cast<SquareView*>(grid_->itemAt(y, x));
			if(square != nullptr)
				square->removePiece();
		}
	}
}

void view::SquareView::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	model::Position position = model::Position('a' + position_.x(), '8' - position_.y());
	emit click(position);
}

view::PieceView::PieceView(bool color, QGraphicsItem* parent) : QGraphicsWidget(parent) {}

void view::PieceView::setPicture(const QRect& pictureRect) {
	QImage image("pieces.png");
	QTransform trans;
	image = image.copy(pictureRect).transformed(trans.translate(-pictureRect.x(), -pictureRect.y()));
	picture_ = new QGraphicsPixmapItem(QPixmap::fromImage(image), this);
}


view::KingView::KingView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(-15, 148, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(-13, 349, SQUARE_SIZE, SQUARE_SIZE));

}

view::QueenView::QueenView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(221, 149, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(223, 350, SQUARE_SIZE, SQUARE_SIZE));

}

view::BishopView::BishopView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(695, 149, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(697, 349, SQUARE_SIZE, SQUARE_SIZE));

}

view::KnightView::KnightView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(932, 154, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(932, 355, SQUARE_SIZE, SQUARE_SIZE));

}

view::RookView::RookView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(459, 154, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(460, 355, SQUARE_SIZE, SQUARE_SIZE));

}

view::PawnView::PawnView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(1168, 154, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(1170, 355, SQUARE_SIZE, SQUARE_SIZE));

}