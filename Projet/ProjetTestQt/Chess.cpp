/**
* Gestion de la scène pour le jeu d'échec
* \file   Chess.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
#pragma pop()
#include <iostream>
#include "Chess.hpp"

QListWidget* Chess::history_ = nullptr;

Chess::Chess()
{
	mainWidget_ = new QGraphicsWidget();
	mainLayout_ = new QGraphicsLinearLayout(Qt::Horizontal);
	history_ = new QListWidget();
	board_ = new Board(mainLayout_);

	mainLayout_->addItem(board_);

	QGraphicsProxyWidget* historyWidget = addWidget(history_);
	mainLayout_->setAlignment(historyWidget, Qt::AlignRight);
	history_->setMinimumWidth(400);
	mainLayout_->addItem(historyWidget);

	mainWidget_->setLayout(mainLayout_);
	addItem(mainWidget_);
	setSceneRect(0, 0, board_->minimumWidth() + history_->minimumWidth(), board_->minimumHeight() + history_->minimumHeight());
	board_->setNewGame();
}

void Chess::addHistoryMove(QString mouvement) {
	QListWidgetItem* message = new QListWidgetItem(mouvement);
	QFont font = message->font();
	font.setPixelSize(40);
	message->setFont(font);
	history_->addItem(message);
}