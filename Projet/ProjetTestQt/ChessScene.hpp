#pragma once
/**
* Déclaration pour la scène du jeu d'échec
* \file   ChessScene.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   04 mai 2021
* Cree le 04 mai 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsScene>
#include <QObject>
#include <QListWidget>
#pragma pop()
#include "BoardView.hpp"
#include "Game.hpp"
#include "ChoiceScene.hpp"

namespace view {
	class ChessScene : public QGraphicsScene {
		Q_OBJECT

	public:
		ChessScene(QObject* parent = nullptr);
		~ChessScene();
		void setGameConfiguration(std::string configuration);
	private:
		model::Game* game_;
		BoardView* chessBoard_;
	};
}