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

view::Window::Window() {
	setStyleSheet("background-color:black;");
	setWindowTitle("Chess");

	ChoiceScene* currentScene = new ChoiceScene(this);
	setScene(currentScene);

	QGraphicsView::fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
	setNextScene(new ChessScene(this));
}

view::Window::~Window() {
	QGraphicsScene* toDelete = scene();
	delete toDelete;
}

void view::Window::setNextScene(QGraphicsScene* scene) {
	if (scene != nullptr) {
		delete nextScene_;
		nextScene_ = scene;
	}
}

void view::Window::changeScene() {
	if (nextScene_ != nullptr) {
		setScene(nextScene_);
		QPushButton* button = dynamic_cast<QPushButton*>(sender());

		if (button != nullptr)
			dynamic_cast<ChessScene*>(nextScene_)->setGameConfiguration(button->text().toStdString());

		resize(QSize(800, 800));
		QGraphicsView::fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
	}
}