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
#include <functional>
#include "gsl/span"
using gsl::span;
using namespace std;
using namespace iter;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

class ListeFilms 
{
public:
	ListeFilms() = default;
	void ajouterFilm(Film* film);
	void enleverFilm(const Film* film);
	shared_ptr<Acteur> trouverActeur(const string& nomActeur) const;
	span<Film*> enSpan() const;
	int size() const { return nElements; }
	void detruire(bool possedeLesFilms = false);
	Film*& operator[](const int& index);
	Film* trouverFilm(const function<bool(Film*)>& critere) const;
	
private:
	int capacite = 0, nElements = 0;
	Film** elements = nullptr; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.

	void changeDimension(int nouvelleCapacite);
};

template <typename T>
class Liste 
{
public:
	Liste() = default;

	Liste(const int taille) : capacite_(taille), 
														nElements_(0), 
														elements_(make_unique<shared_ptr<T>[]>(taille)) {}

	Liste(const Liste<T>& autre) : capacite_(autre.capacite_), 
															   nElements_(autre.nElements_), 
															   elements_(make_unique<shared_ptr<T>[]>(autre.capacite_))
	{
		for (int i : range(autre.nElements_))
			elements_[i] = autre.elements_[i];
	}
	
	void operator=(const Liste<T>& autre) 
	{
		capacite_ = autre.capacite_;
		nElements_ = autre.nElements_;
		elements_ = make_unique<shared_ptr<T>[]>(autre.capacite_);
		for (int i : range(autre.nElements_))
			elements_[i] = autre.elements_[i];
	}

	shared_ptr<T>& operator[](const int& indice)
	{
		return elements_[indice];
	}

	span<shared_ptr<T>> enSpan() const 
	{
		return span(elements_.get(), nElements_);
	}

	void ajouter(shared_ptr<T> element) 
	{
		if (nElements_ == capacite_)
			changeDimension(max(1, capacite_ * 2));

		elements_[nElements_++] = element;
	}

private:
	int capacite_ = 0, nElements_ = 0;
	unique_ptr<shared_ptr<T>[]> elements_; // unique_ptr vers un tableau de T

	void changeDimension(int nouvelleCapacite)
	{
		unique_ptr<shared_ptr<T>[]> nouvelleListe = make_unique<shared_ptr<T>[]>(nouvelleCapacite);
		nElements_ = min(nouvelleCapacite, nElements_);

		for (int i : range(nElements_))
			nouvelleListe[i] = elements_[i];

		elements_ = move(nouvelleListe);
		capacite_ = nouvelleCapacite;
	}
};

// Pour ne pas causer de problème de définition
using ListeActeurs = Liste<Acteur>;

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

