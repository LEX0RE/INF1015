#define SQUARE_SIZE 140
#include "Chess.hpp"
#include "include/cppitertools/range.hpp"
using namespace iter;

WindowView::WindowView() {
	setStyleSheet("background-color:black;");
	setWindowTitle("Chess");
	setScene(new ChessScene());
	QGraphicsView::fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

WindowView::~WindowView() {
	QGraphicsScene* toDelete = scene();
	delete toDelete;
}

void WindowView::setNextScene(QGraphicsScene* scene) {
	if (scene != nullptr) {
		delete nextScene_;
		nextScene_ = scene;
	}
}

void WindowView::changeScene() {
	if (nextScene_ != nullptr)
		setScene(nextScene_);
	//emit sceneChanged();
}

ChessScene::ChessScene(QGraphicsView* parent) : QGraphicsScene(parent) {
	BoardView* chessBoard = new BoardView();
	addItem(chessBoard);
	game_ = new model::Game();
	connect(game_, &model::Game::updatePiece, chessBoard, &BoardView::reloadPiece);
	game_->setNewGame();
}

ChessScene::~ChessScene() {
	delete game_;
}

BoardView::BoardView(QGraphicsItem* parent) : QGraphicsWidget(parent) {
	QRectF rect(0, 0, SQUARE_SIZE * 8, SQUARE_SIZE * 8);
	setGeometry(rect);
	grid_ = new QGraphicsGridLayout();

	for (unsigned int y : range(8)) {
		for (unsigned int x : range(8)) {
			if ((x + y) % 2)
				grid_->addItem(new SquareView(Qt::cyan), y, x);
			else
				grid_->addItem(new SquareView(Qt::blue), y, x);
		}
	}
	setLayout(grid_);
}


SquareView::SquareView(Qt::GlobalColor color, QGraphicsItem* parent) : QGraphicsWidget(parent) {
	
	piece_ = nullptr;
	QRectF rect(0, 0, SQUARE_SIZE, SQUARE_SIZE);
	auto square = new QGraphicsRectItem(rect, this);
	square->setBrush(color);
	square->setParentItem(this);
	setOwnedByLayout(true);
	
}


void SquareView::addPiece(PieceView* piece) {

	if (piece_ != nullptr)
		delete piece_;
	
	piece_ = piece;
	piece_->setParentItem(this);

}

void SquareView::removePiece() {
	if (piece_ != nullptr)
		delete piece_;

	piece_ = nullptr;
}


void BoardView::reloadPiece(std::map<std::string, model::Piece*> pieceMap) {
	bool found = false;

	clearPieces();
	for (auto& [key, value] : pieceMap) {
		unsigned int x = value->getPosition().x - 'a' ;
		unsigned int y = value->getPosition().y - '1';
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

void BoardView::clearPieces() {
	for (auto y : range(8)) {
		for (auto x : range(8)) {
			SquareView* square = dynamic_cast<SquareView*>(grid_->itemAt(y, x));
			if(square != nullptr)
				square->removePiece();
		}
	}
}


void SquareView::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	//emit click(position);
}

PieceView::PieceView(bool color, QGraphicsItem* parent) : QGraphicsWidget(parent) {}

void PieceView::setPicture(const QRect& pictureRect) {
	QImage image("pieces.png");
	QTransform trans;
	image = image.copy(pictureRect).transformed(trans.translate(-pictureRect.x(), -pictureRect.y()));
	picture_ = new QGraphicsPixmapItem(QPixmap::fromImage(image), this);
}


KingView::KingView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(-15, 148, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(-13, 349, SQUARE_SIZE, SQUARE_SIZE));

}

QueenView::QueenView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(221, 149, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(223, 350, SQUARE_SIZE, SQUARE_SIZE));

}

BishopView::BishopView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(695, 149, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(697, 349, SQUARE_SIZE, SQUARE_SIZE));

}

KnightView::KnightView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(932, 154, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(932, 355, SQUARE_SIZE, SQUARE_SIZE));

}

RookView::RookView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(459, 154, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(460, 355, SQUARE_SIZE, SQUARE_SIZE));

}

PawnView::PawnView(bool color, QGraphicsItem* parent) : PieceView(color, parent) {

	if (color == false)
		setPicture(QRect(1168, 154, SQUARE_SIZE, SQUARE_SIZE));
	else
		setPicture(QRect(1170, 355, SQUARE_SIZE, SQUARE_SIZE));

}