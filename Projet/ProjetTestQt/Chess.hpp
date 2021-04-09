#pragma once
/**
* Gestion du IU pour un jeu d'�chec
* \file   ChessScene.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QGraphicsScene>
#pragma pop()
#include "Board.hpp"

class Chess : public QGraphicsScene {
	Q_OBJECT

public:
	Chess();
	~Chess() override;
private:
	QGraphicsWidget* gameWidget_;
	Board* board_;
};
