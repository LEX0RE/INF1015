#pragma once
/**
* Gestion du IU pour un jeu d'échec
* \file   View.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsView>
#include <QGraphicsScene>
#pragma pop()

class View : public QGraphicsView {
	Q_OBJECT

public:
	View();
	~View() override;

	void setNextScene(QGraphicsScene* nextScene);
	void switchScene();
private:
	QGraphicsScene* nextScene_ = nullptr;
};
