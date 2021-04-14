/**
* Gère l'utilisation de scènes pour notre jeu d'échec
* \file   Window.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/

#include "Window.hpp"
#include "ChessScene.hpp"

Window::Window()
{
  setStyleSheet("background-color:black;");
  setWindowTitle("Chess");
  setScene(new ChessScene());
  QGraphicsView::fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

Window::~Window() {
  QGraphicsScene* toDelete = scene();
  delete toDelete;
}

void Window::setNextScene(QGraphicsScene* nextScene) {
  if (nextScene != nullptr) {
    delete nextScene_;
    nextScene_ = nextScene;
  }
}

void Window::switchScene() {
  if (nextScene_ != nullptr) {
    QGraphicsScene* temporary = scene();
    setScene(nextScene_);
    nextScene_ = temporary;
  }
}