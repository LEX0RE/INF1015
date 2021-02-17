/**
* Structure pour la gestion de film pour le TD3 de INF1015. 
* \file   structures_solutionnaire_td2_3.hpp
* \author Ioana Daria Danciu et Alexandre G�linas
* \date   17 f�vrier 2021
* Cree le 16 janvier 2021
*/

#pragma once
// Structures mémoires pour une collection de films.

#include <string>
#include <memory>
#include "gsl/span"
using gsl::span;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

class ListeFilms {
public:
	ListeFilms() = default;
	void ajouterFilm(Film* film);
	void enleverFilm(const Film* film);
	Acteur* trouverActeur(const std::string& nomActeur) const;
	span<Film*> enSpan() const;
	int size() const { return nElements; }
	void detruire(bool possedeLesFilms = false);

private:
	void changeDimension(int nouvelleCapacite);

	int capacite = 0, nElements = 0;
	Film** elements = nullptr; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
};

class ListeActeurs {
public:
	ListeActeurs(int taille);
	span<Acteur*> enSpan() const;
	int capacite, nElements;
	unique_ptr<Acteur* []> elements; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Film.
};

struct Film
{
	std::string titre, realisateur; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie, recette; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;
};

struct Acteur
{
	std::string nom; int anneeNaissance; char sexe;
	ListeFilms joueDans;
};
