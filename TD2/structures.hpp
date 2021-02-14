#pragma once
// Structures mémoires pour une collection de films.

#include <string>

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

class ListeFilms {
public:
	ListeFilms();
	// Aucun destructeur car nous n'avons pas appris le move

	Acteur* trouverActeur(const std::string nomActeur) const;

	void ajouterFilm(Film* const film);
	void detruireFilm(Film*& film);
	int obtenirNombreFilms() const;
	Film** obtenirElements() const;
	void detruireListeFilms();
	void afficherListeFilms() const;

private:
	int capacite_, nElements_;
	Film** elements_;

	void doublerCapacite();
	void enleverFilm(const Film* film); // Pourrait causer des pertes de mémoire si l'utilisateur ne s'en sert pas bien
};

struct ListeActeurs {
	int capacite, nElements;
	Acteur** elements; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
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
