#pragma once
/**
* Déclaration pour la fenêtre de l'application
* \file   Window.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   04 mai 2021
* Cree le 04 mai 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QObject>
#pragma pop()

namespace view {
	class Window : public QGraphicsView {
		Q_OBJECT
	public:
		Window();
		virtual ~Window();
		void setNextScene(QGraphicsScene* scene);
	public slots:
		void changeScene();
	private:
		QGraphicsScene* nextScene_ = nullptr;
	};
}
