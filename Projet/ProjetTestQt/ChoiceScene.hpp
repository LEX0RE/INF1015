#pragma once
/**
* D�claration pour la sc�ne du menu pour le jeu d'�chec
* \file   ChoiceScene.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   04 mai 2021
* Cree le 04 mai 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QGraphicsScene>
#include <QPushButton>
#include <QObject>
#pragma pop()
#include "ChessScene.hpp"

namespace view {
	class ChoiceScene : public QGraphicsScene {
		Q_OBJECT

	public:
		ChoiceScene(QObject* parent = nullptr);
		~ChoiceScene() = default;
	};
}
