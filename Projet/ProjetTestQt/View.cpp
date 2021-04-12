/**
* Gère l'utilisation de scènes pour notre jeu d'échec
* \file   View.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   11 avril 2021
* Cree le 6 avril 2021
*/

#include "View.hpp"
#include "Chess.hpp"

View::View()
{
  setStyleSheet("background-color:black;");
  setWindowTitle("Chess");
  setScene(new Chess());
  QGraphicsView::fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

View::~View() {
  QGraphicsScene* toDelete = scene();
  delete toDelete;
}

void View::setNextScene(QGraphicsScene* nextScene) {
  if (nextScene != nullptr) {
    delete nextScene_;
    nextScene_ = nextScene;
  }
}

void View::switchScene() {
  if (nextScene_ != nullptr) {
    QGraphicsScene* temporary = scene();
    setScene(nextScene_);
    nextScene_ = temporary;
  }
}