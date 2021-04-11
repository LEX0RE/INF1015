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
#include <QGraphicsProxyWidget>
#pragma pop()
#include <cppitertools/range.hpp>

#include "Chess.hpp"

QListWidget* Chess::history_ = nullptr;

Chess::Chess()
{
	menu_ = new QGraphicsLinearLayout(Qt::Horizontal);
	gameWidget_ = new QGraphicsWidget();
	history_ = new QListWidget();

	board_ = new Board(menu_);
	menu_->addItem(board_);

	QGraphicsProxyWidget* historyWidget = addWidget(history_);
	menu_->setAlignment(historyWidget, Qt::AlignRight);
	history_->setMinimumWidth(400);
	menu_->addItem(historyWidget);

	gameWidget_->setLayout(menu_);
	addItem(gameWidget_);
	setSceneRect(0, 0, board_->minimumWidth() + history_->minimumWidth(), board_->minimumHeight() + history_->minimumHeight());
}

Chess::~Chess() {
	removeItem(gameWidget_);
	delete gameWidget_;
}

void Chess::addHistoryMove(QString mouvement) {
	QListWidgetItem* message = new QListWidgetItem(mouvement);
	QFont font = message->font();
	font.setPixelSize(40);
	message->setFont(font);
	history_->addItem(message);
}