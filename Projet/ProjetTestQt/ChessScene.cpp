/**
* Gestion de la scène du jeu d'échec
* \file   ChessScene.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   04 mai 2021
* Cree le 04 mai 2021
*/

#include "ChessScene.hpp"
#include "include/cppitertools/range.hpp"
using namespace iter;

view::ChessScene::ChessScene(QObject* parent) : QGraphicsScene(parent) {
	chessBoard_ = new BoardView();
	addItem(chessBoard_);
	game_ = new model::Game();
	connect(game_, &model::Game::updatePiece, chessBoard_, &BoardView::reloadPiece);
	connect(game_, &model::Game::updatePossibility, chessBoard_, &BoardView::reloadPossibility);

	for (auto it : chessBoard_->getList())
		connect(it, &SquareView::click, game_, &model::Game::action);
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
