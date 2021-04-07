/**
* G�re l'interface utilisation pour le jeu d'�chec
* \file   ChessWindow.cpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/

#include "ChessWindow.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QAction>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QButtonGroup>
#include <QMenuBar>
#include <QLabel>
#include <QString>
#include <QVariant>
#include <QRect>
#pragma pop()


ChessWindow::ChessWindow(QWidget* parent) :
	QMainWindow(parent)
{
	// Si on objet n'a pas encore de parent on lui met "this" comme parent en attendant, si possible, pour s'assurer que tous les pointeurs sont g�r�s par un delete automatique en tout temps sans utiliser de unique_ptr.
	auto widgetPrincipal = new QWidget(this);
	auto layoutPrincipal = new QVBoxLayout(widgetPrincipal);  // Donner un parent � un layout est comme un setLayout.
	setStyleSheet("background-color:black;");
	setAutoFillBackground(true);
	setCentralWidget(widgetPrincipal);
	setWindowTitle("Jeu d'�chec");
	setup();
}

void ChessWindow::setMenu() {
	// On cr�e un bouton 'Exit'
	QAction* exit = new QAction(tr("E&xit"), this);
	// On ajoute un raccourci clavier qui simulera l'appui sur ce bouton (Ctrl+Q)
	exit->setShortcuts(QKeySequence::Quit);
	// On connecte le clic sur ce bouton avec l'action de clore le programme
	connect(exit, SIGNAL(triggered()), this, SLOT(close()));
	// On cr�e un nouveau menu 'File'
	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
	// Dans lequel on ajoute notre bouton 'Exit'
	fileMenu->addAction(exit);
}

void ChessWindow::setUI() {
	// Le s�lecteur pour filtrer ce que l'on souhaite dans la liste
	QComboBox* showCombobox = new QComboBox(this);
	showCombobox->addItem("Show all"); // Index 0
	showCombobox->addItem("Show only managers"); // Index 1
	showCombobox->addItem("Show only secretaries"); // Index 2
	showCombobox->addItem("Show only other employees"); // Index 3
	connect(showCombobox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(filterList(int)));
	/*
	// La liste des employ�s
	employeesList = new QListWidget(this);
	employeesList->setSortingEnabled(true);
	connect(employeesList, SIGNAL(itemClicked(QListWidgetItem*)),
		this, SLOT(selectEmployee(QListWidgetItem*)));
	*/
	// Le bouton pour cong�dier tout le monde
	QPushButton* fireEveryoneButton = new QPushButton(this);
	fireEveryoneButton->setText("Fire everyone");
	connect(fireEveryoneButton, SIGNAL(clicked()), this, SLOT(fireEveryone()));
	// Le bouton pour remettre � z�ro la vue et cr�er un nouvel employ�
	QPushButton* hireSomeoneButton = new QPushButton(this);
	hireSomeoneButton->setText("Hire someone new");
	connect(hireSomeoneButton, SIGNAL(clicked()), this, SLOT(cleanDisplay()));
}

void ChessWindow::setup() {
	// On cr�� notre menu et notre UI
	setMenu();
	setUI(); 
	QRect r1(100, 200, 11, 16);
	// On connecte les signaux de notre company aux
	// slots cr��s localement pour agir suite � ces signaux
	/*
	connect(company_, SIGNAL(employeeAdded(Employee*)),
		this, SLOT(employeeHasBeenAdded(Employee*)));
	connect(company_, SIGNAL(employeeDeleted(Employee*)),
		this, SLOT(employeeHasBeenDeleted(Employee*)));
	// On charge la liste des employ�s actuels
	loadEmployees();
	*/
}