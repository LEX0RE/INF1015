/**
* Gestion de la fenêtre de l'application
* \file   TestBoard.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   04 mai 2021
* Cree le 04 mai 2021
*/

#include "Window.hpp"
#include "ChessScene.hpp"
#include "ChoiceScene.hpp"

view::WindowView::WindowView() {
	setStyleSheet("background-color:black;");
	setWindowTitle("Chess");
	ChoiceScene* currentScene = new ChoiceScene(this);
	setScene(currentScene);
	QGraphicsView::fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
	setNextScene(new ChessScene(this));
}

view::WindowView::~WindowView() {
	QGraphicsScene* toDelete = scene();
	delete toDelete;
}

void view::WindowView::setNextScene(QGraphicsScene* scene) {
	if (scene != nullptr) {
		delete nextScene_;
		nextScene_ = scene;
	}
}

void view::WindowView::changeScene() {
	if (nextScene_ != nullptr) {
		setScene(nextScene_);
		QPushButton* button = dynamic_cast<QPushButton*>(sender());

		if (button != nullptr)
			dynamic_cast<ChessScene*>(nextScene_)->setGameConfiguration(button->text().toStdString());

		QRectF rect = scene()->sceneRect();
		rect.adjust(0, 0, -400, -400);
		QGraphicsView::fitInView(rect, Qt::KeepAspectRatio);
		resize(QSize(800, 800));
	}
}