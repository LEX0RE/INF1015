#pragma once
/**
* D�claration pour la sc�ne d'un jeu d'�chec
* \file   ChessScene.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QGraphicsScene>
#include <QGraphicsLinearLayout>
#include <QListWidget>
#pragma pop()
#include "BoardView.hpp"

class ChessScene : public QGraphicsScene {
	Q_OBJECT

public:
	ChessScene();
	~ChessScene() override = default;

	static void addHistoryMove(QString mouvement);
private:
	static QListWidget* history_;
};
