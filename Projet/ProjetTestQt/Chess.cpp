/**
* Gestion du IU pour un jeu d'échec
* \file   ChessScene.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/

#include <iostream>
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsWidget>
#pragma pop()

#include "Chess.hpp"

Chess::Chess()
{
	gameWidget_ = new QGraphicsWidget();
	board_ = new Board();
	gameWidget_->setLayout(board_);
	addItem(gameWidget_);
	setSceneRect(0, 0, board_->minimumHeight(), board_->minimumWidth());
}

Chess::~Chess() {
	removeItem(gameWidget_);
	delete gameWidget_;
}
