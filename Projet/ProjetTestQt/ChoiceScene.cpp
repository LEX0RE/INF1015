/**
* Gestion de la vue du menu de sélection
* \file   ChoiceScene.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   04 mai 2021
* Cree le 04 mai 2021
*/

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QVBoxLayout>
#include <QGroupBox>
#pragma pop()
#include "ChoiceScene.hpp"
#include "Window.hpp"

view::ChoiceScene::ChoiceScene(QObject* parent) : QGraphicsScene(parent) {
	QPushButton* classicButton = new QPushButton(QString("Classic"));
	QPushButton* FischerandomButton = new QPushButton(QString("Fischerandom"));

	connect(classicButton, &QPushButton::clicked, dynamic_cast<Window*>(parent), &view::Window::changeScene);
	connect(FischerandomButton, &QPushButton::clicked, dynamic_cast<Window*>(parent), &view::Window::changeScene);

	QGroupBox* choiceBox = new QGroupBox("Board setup");
	choiceBox->setAlignment(Qt::AlignCenter);

	QVBoxLayout* choiceLayout = new QVBoxLayout();
	choiceLayout->addWidget(classicButton);
	choiceLayout->addWidget(FischerandomButton);

	choiceBox->setLayout(choiceLayout);

	QGraphicsProxyWidget* ChoiceProxy = addWidget(choiceBox);
}
