/**
* Gestion de la scène du jeu d'échec
* \file   ChessScene.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   04 mai 2021
* Cree le 04 mai 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#pragma pop()
#include "ChessScene.hpp"
#include "include/cppitertools/range.hpp"
using namespace iter;

view::ChessScene::ChessScene(QObject* parent) : QGraphicsScene(parent) {
	chessBoard_ = new BoardView();
	addItem(chessBoard_);

	game_ = new model::Game();
	connect(game_, &model::Game::updatePiece, chessBoard_, &BoardView::reloadPiece);
	connect(game_, &model::Game::updatePossibility, chessBoard_, &BoardView::reloadPossibility);

	if (chessBoard_->getList().size() > 0) {
		for (auto it : chessBoard_->getList())
			connect(it, &SquareView::click, game_, &model::Game::action);
	}
}

view::ChessScene::~ChessScene() {
	delete game_;
}

void view::ChessScene::setGameConfiguration(std::string configuration) {
	if (configuration == "Classic")
		game_->setNewGame();
	else if (configuration == "Fischerandom")
		game_->setFischerRandomGame();
}
