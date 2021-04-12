#pragma once
/**
* D�finition pour la gestion des sc�nes 
* \file   View.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
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
