#pragma once
/**
* Gestion du IU pour un jeu d'échec
* \file   ChessScene.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsScene>
#include <QGraphicsLinearLayout>
#include <QListWidget>
#pragma pop()
#include "Board.hpp"
//#include "History.hpp"

class Chess : public QGraphicsScene {
	Q_OBJECT

public:
	Chess();
	~Chess() override;

	static void addHistoryMove(QString mouvement);
private:
	QGraphicsWidget* gameWidget_;
	QGraphicsLinearLayout* menu_;
	Board* board_;
	static QListWidget* history_;
};
