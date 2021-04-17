#pragma once

#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QListWidget>
#include <QColor>
#include <QObject>
#pragma pop()
#include "Game.hpp"

class PieceView : public QGraphicsWidget {
	Q_OBJECT
public:
	PieceView(bool color, QGraphicsItem* parent = nullptr);
	void setPicture(const QRect& pictureRect);
	//public slots:
		//void changeLayout();
private:
	QGraphicsPixmapItem* picture_;
};

class WindowView : public QGraphicsView {
	Q_OBJECT
public:
	WindowView();
	virtual ~WindowView();
	void setNextScene(QGraphicsScene* scene);
public slots:
	void changeScene();
signals:
	void sceneChanged();
private:
	QGraphicsScene* nextScene_ = nullptr; //QGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr)
};


class ChessScene : public QGraphicsScene {
	Q_OBJECT

public:
	ChessScene(QGraphicsView* parent = nullptr);
	~ChessScene();
	//static void addHistoryMove(QString mouvement);
private:
	model::Game* game_;
	//static QListWidget* history_;
};


class BoardView : public QGraphicsWidget {
	Q_OBJECT
public:
	BoardView(QGraphicsItem* parent = nullptr);
public slots:
	void reloadPiece(std::map<std::string, model::Piece*> pieceMap);
private:
	QGraphicsGridLayout* grid_;

	void clearPieces();
};


class SquareView : public QGraphicsWidget {
	Q_OBJECT
public:
	SquareView(Qt::GlobalColor color, QGraphicsItem* parent = nullptr);
	void highlight();
	void lowlight();
	void addPiece(PieceView* piece);
	void removePiece();
	void mousePressEvent(QGraphicsSceneMouseEvent* event)  override;
signals:
	void click(const model::Position& position);
private:
	PieceView* piece_;
	//PositioN position_;		-> pourrait se faire avec les lignes et les colonnes de la grille
	Qt::GlobalColor color_;
};


class KingView : public PieceView {
public:
	KingView(bool color, QGraphicsItem* parent = nullptr);
};


class QueenView : public PieceView {
public:
	QueenView(bool color, QGraphicsItem* parent = nullptr);
};


class BishopView : public PieceView {
public:
	BishopView(bool color, QGraphicsItem* parent = nullptr);
};


class KnightView : public PieceView {
public:
	KnightView(bool color, QGraphicsItem* parent = nullptr);
};


class RookView : public PieceView {
public:
	RookView(bool color, QGraphicsItem* parent = nullptr);
};


class PawnView : public PieceView {
public:
	PawnView(bool color, QGraphicsItem* parent = nullptr);
};

