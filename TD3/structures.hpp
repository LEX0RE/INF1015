/**
* Structure pour la gestion de film pour le TD3 de INF1015.
* \file   structures.hpp
* \author Ioana Daria Danciu et Alexandre G�linas
* \date   17 février 2021
* Cree le 16 janvier 2021
*/

#pragma once
// Structures mémoires pour une collection de films.

#include <string>
#include <memory>
#include <sstream>
#include <cppitertools/range.hpp>
#include "gsl/span"
using gsl::span;
using namespace std;
using namespace iter;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

class ListeFilms {
public:
	ListeFilms() = default;
	void ajouterFilm(Film* film);
	void enleverFilm(const Film* film);
	std::shared_ptr<Acteur> trouverActeur(const std::string& nomActeur) const;
	span<Film*> enSpan() const;
	int size() const { return nElements; }
	void detruire(bool possedeLesFilms = false);
	Film* operator[](const int& index);

private:
	void changeDimension(int nouvelleCapacite);

	int capacite = 0, nElements = 0;
	Film** elements = nullptr; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
};

class ListeActeurs {
public:
	ListeActeurs() = default;

	ListeActeurs(const int taille) : capacite(taille), 
																	 nElements(0), 
																	 elements(make_unique<shared_ptr<Acteur>[]>(taille)) {}

	ListeActeurs(const ListeActeurs& autre) : capacite(autre.capacite), 
																						nElements(autre.nElements), 
																						elements(make_unique<shared_ptr<Acteur>[]>(autre.capacite)) 
	{
		for (int i : range(autre.nElements))
			elements[i] = autre.elements[i];
	}
	
	void operator=(const ListeActeurs& autre)
	{
		capacite = autre.capacite;
		nElements = autre.nElements;
		elements = make_unique<shared_ptr<Acteur>[]>(autre.capacite);
		for (int i : range(autre.nElements))
			elements[i] = autre.elements[i];
	}
	
	span<std::shared_ptr<Acteur>> enSpan() const;

	void ajouterActeur(std::shared_ptr<Acteur> acteur) {
		if (nElements == capacite) // Devrait pas avoir à le faire car la capacité est lu dans le fichier
			changeDimension(max(1, capacite * 2));

		elements[nElements++] = acteur;
	}

	void changeDimension(int nouvelleCapacite)
	{
		unique_ptr<shared_ptr<Acteur>[]> nouvelleListe = make_unique<shared_ptr<Acteur>[]>(nouvelleCapacite);
		nElements = min(nouvelleCapacite, nElements);

		for (int i : range(nElements))
			nouvelleListe[i] = elements[i];

		elements = move(nouvelleListe);
		capacite = nouvelleCapacite;
	}

private:
	int capacite = 0, nElements = 0;
	std::unique_ptr<std::shared_ptr<Acteur>[]> elements; // unique_ptr vers un tableau de Acteur*, chaque Acteur* pointant vers un Film.
};

struct Film
{
	std::string titre = "", realisateur = ""; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie = 0, recette = 0; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;
};

struct Acteur
{
	std::string nom = ""; int anneeNaissance = 0; char sexe = '\0';
	//ListeFilms joueDans;
};

