#pragma once
/**
* Déclaration pour la scène d'un jeu d'échec
* \file   Chess.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsScene>
#include <QGraphicsLinearLayout>
#include <QListWidget>
#pragma pop()
#include "Board.hpp"

class Chess : public QGraphicsScene {
	Q_OBJECT

public:
	Chess();
	~Chess() override = default;

	static void addHistoryMove(QString mouvement);
private:
	QGraphicsWidget* mainWidget_;
	QGraphicsLinearLayout* mainLayout_;
	Board* board_;
	static QListWidget* history_;
};
