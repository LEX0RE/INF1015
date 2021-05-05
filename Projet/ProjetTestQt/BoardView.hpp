#pragma once
/**
* Déclaration pour la vue de la planche du jeu d'échec
* \file   BoardView.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   04 mai 2021
* Cree le 04 mai 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QColor>
#include <QObject>
#pragma pop()
#include "Game.hpp"
#include "PieceView.hpp"

namespace view {
	class SquareView : public QGraphicsWidget {
		Q_OBJECT
	public:
		SquareView(Qt::GlobalColor color, QPoint position, QGraphicsItem* parent = nullptr);
		void highlight(Qt::GlobalColor color);
		void lowlight();
		void addPiece(std::string name);
		void addPiece(PieceView* piece);
		PieceView* getPiece() const;
		void removePiece();
		void deletePiece();
		void mousePressEvent(QGraphicsSceneMouseEvent* event)  override;
	signals:
		void click(const model::Position& position);
	private:
		QGraphicsRectItem* square_;
		Qt::GlobalColor color_;
		PieceView* piece_;
		QPoint position_;
	};

	class BoardView : public QGraphicsWidget {
		Q_OBJECT
	public:
		BoardView(QGraphicsItem* parent = nullptr);
		std::list<SquareView*> getList() const;
	public slots:
		void reloadPiece(std::map<std::string, model::Piece*> pieceMap);
		void reloadPossibility(std::list<model::Position> possibility);
	private:
		QGraphicsGridLayout* grid_;
		std::list<SquareView*> squareList_;
		std::list<SquareView*> highlightSquareList_;

		void clearPieces();
		PieceView* searchPiece(std::string name) const;
		SquareView* squareOfPiece(PieceView* piece) const;
	};
}
