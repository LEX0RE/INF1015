#pragma once
/**
* Gestion du IU pour un jeu d'�chec
* \file   ChessWindow.hpp
* \author Ioana Daria Danciu et Alexandre Gelinas
* \date   6 avril 2021
* Cree le 6 avril 2021
*/
#include "Chess.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QMainWindow>

class ChessWindow : public QMainWindow {
	Q_OBJECT

public:
	ChessWindow(QWidget* parent = nullptr);
	~ChessWindow() override = default;

public slots:
	//void changerValeurAffichee(int valeur);  // Pour la version QButtonGroup.
	//void chiffreAppuye(); //QAbstractButton* bouton);  // Pour la version setProperty.

private:
	/*
	template <typename T = decltype(nullptr)>
	QPushButton* nouveauBouton(const QString& text, const T& slot = nullptr);

	Calc calc_;  // Le Mod�le (pourrait �tre un pointeur mais pas n�cessaire dans ce cas).

	QLabel* affichage_;  // Pour la version QButtonGroup.
	*/
	Board board_;

	void setMenu();
	void setUI();
	void setup();
};
