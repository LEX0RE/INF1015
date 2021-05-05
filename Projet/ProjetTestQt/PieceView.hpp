#pragma once
/**
* Déclaration pour la vue des pièces du jeu d'échec
* \file   PieceView.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   04 mai 2021
* Cree le 04 mai 2021
*/

#define SQUARE_SIZE 140

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsWidget>
#include <QObject>
#pragma pop()

namespace view {
	class PieceView : public QGraphicsWidget {
		Q_OBJECT
	public:
		PieceView(std::string name, QGraphicsItem* parent = nullptr);
		void setPicture(const QRect& pictureRect);
		std::string getName() const;
	private:
		QGraphicsPixmapItem* picture_;
		std::string name_;
	};

	class KingView : public PieceView {
	public:
		KingView(std::string name, QGraphicsItem* parent = nullptr);
	};

	class QueenView : public PieceView {
	public:
		QueenView(std::string name, QGraphicsItem* parent = nullptr);
	};

	class BishopView : public PieceView {
	public:
		BishopView(std::string name, QGraphicsItem* parent = nullptr);
	};

	class KnightView : public PieceView {
	public:
		KnightView(std::string name, QGraphicsItem* parent = nullptr);
	};

	class RookView : public PieceView {
	public:
		RookView(std::string name, QGraphicsItem* parent = nullptr);
	};

	class PawnView : public PieceView {
	public:
		PawnView(std::string name, QGraphicsItem* parent = nullptr);
	};
}