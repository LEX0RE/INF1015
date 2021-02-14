#pragma region "Includes"//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.

#include "structures.hpp"      // Structures de données pour la collection de films en mémoire.

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>

#include "cppitertools/range.hpp"
#include "gsl/span"

#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp" // Nos fonctions pour le rapport de fuites de mémoire.
#include "debogage_memoire.hpp"        // Ajout des numéros de ligne des "new" dans le rapport de fuites.  Doit être après les include du système, qui peuvent utiliser des "placement new" (non supporté par notre ajout de numéros de lignes).

using namespace std;
using namespace iter;
using namespace gsl;

#pragma endregion//}

typedef uint8_t UInt8;
typedef uint16_t UInt16;

#pragma region "Fonctions de base pour lire le fichier binaire"//{

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

#pragma endregion//}

Acteur* lireActeur(istream& fichier, ListeFilms &listeFilms)
{
	Acteur acteur = {};
	acteur.nom            = lireString(fichier);
	acteur.anneeNaissance = lireUint16 (fichier);
	acteur.sexe           = lireUint8  (fichier);
	Acteur* acteurTrouve  = listeFilms.trouverActeur(acteur.nom);

	if (acteurTrouve == nullptr) {
		Acteur* acteurAlloue = new Acteur(acteur);
		cout << "Création Acteur " << acteurAlloue->nom << endl;
		return acteurAlloue;
	}
	else
		delete[] acteur.joueDans.obtenirElements();
	return acteurTrouve;
}

Film* lireFilm(istream& fichier, ListeFilms& listeFilms)
{
	Film film = {};
	film.titre       = lireString(fichier);
	film.realisateur = lireString(fichier);
	film.anneeSortie = lireUint16 (fichier);
	film.recette     = lireUint16 (fichier);
	film.acteurs.nElements = lireUint8 (fichier);
	film.acteurs.capacite = film.acteurs.nElements;
	film.acteurs.elements = new Acteur * [film.acteurs.nElements];
	Film* filmAlloue = new Film(film);

	cout << "Création Film " << film.titre << endl;

	for (int i : range(filmAlloue->acteurs.nElements)) {
		filmAlloue->acteurs.elements[i] = lireActeur(fichier, listeFilms);
		filmAlloue->acteurs.elements[i]->joueDans.ajouterFilm(filmAlloue);
	}
	return filmAlloue;
}

ListeFilms creerListe(string nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	int nElements = lireUint16(fichier);

	ListeFilms listeFilms = {};

	while (listeFilms.obtenirNombreFilms() < nElements)
		listeFilms.ajouterFilm(lireFilm(fichier, listeFilms));
	
	return listeFilms;
}

void afficherActeur(const Acteur& acteur)
{
	cout << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
}

void afficherFilm(const Film* film) 
{
	cout << "Titre: " << film->titre << "\n  Réalisateur: ";
	cout << film->realisateur << "  Année :" << film->anneeSortie << endl;
	cout << "  Recette: " << film->recette << "M$" << endl;
	cout << "Acteurs:" << endl;

	for (auto a : span(film->acteurs.elements, film->acteurs.nElements))
		afficherActeur(*a);
}


void afficherFilmographieActeur(const ListeFilms& listeFilms, const string& nomActeur)
{
	const Acteur* acteur = listeFilms.trouverActeur(nomActeur);
	if (acteur == nullptr)
		cout << "Aucun acteur de ce nom" << endl;
	else
		acteur->joueDans.afficherListeFilms();
}


ListeFilms::ListeFilms()
{
	capacite_ = 0;
	nElements_ = 0;
	elements_ = new Film * [0];
}

void ListeFilms::detruireListeFilms()
{
	while (nElements_ > 0)
		detruireFilm(elements_[0]);

	delete[] elements_;
}

Acteur* ListeFilms::trouverActeur(const std::string nomActeur) const
{
	for (Film* f : gsl::span(elements_, nElements_)) {
		for (auto a : gsl::span(f->acteurs.elements, f->acteurs.nElements)) {
			if (nomActeur == a->nom)
				return a;
		}
	}
	return nullptr;
}

int ListeFilms::obtenirNombreFilms() const
{
	return nElements_;
}

void ListeFilms::ajouterFilm(Film* const film)
{
	bool estNouveau = true;

	for (Film* f : gsl::span(elements_, nElements_))
		estNouveau = estNouveau && (f != film);

	if (estNouveau)
		if (nElements_ >= capacite_)
			doublerCapacite();

	elements_[nElements_++] = film;
}

void ListeFilms::enleverFilm(const Film* film)
{
	if (nElements_ > 0) {
		for (auto i : iter::range(nElements_)) {
			if (elements_[i] == film) {
				elements_[i] = elements_[nElements_ - 1];
				elements_[nElements_-- - 1] = nullptr;
			}
		}
	}
}

void ListeFilms::detruireFilm(Film*& film) 
{
	for (Acteur* a : gsl::span(film->acteurs.elements, film->acteurs.nElements)) {
		a->joueDans.enleverFilm(film);

		if (a->joueDans.nElements_ == 0) {
			std::cout << "Destruction Acteur " << a->nom << std::endl;
			delete[] a->joueDans.elements_;
			delete a;
		}
	}

	std::cout << "Destruction Film " << film->titre << std::endl;
	delete[] film->acteurs.elements;

	Film* toDelete = film;
	film = elements_[nElements_ - 1];
	elements_[nElements_-- - 1] = nullptr;
	delete toDelete;
}

void ListeFilms::doublerCapacite()
{
	capacite_ = std::max(2 * capacite_, 1);
	Film** elements = new Film * [capacite_];

	for (auto i : iter::range(nElements_))
		elements[i] = elements_[i];

	delete[] elements_;
	elements_ = elements;
}

Film** ListeFilms::obtenirElements() const
{
	return elements_;
}


void ListeFilms::afficherListeFilms() const
{
	static const string ligneDeSeparation = "────────────────────────────────────────";
	cout << ligneDeSeparation << endl;
	for (auto f : span(obtenirElements(), obtenirNombreFilms())) {
		afficherFilm(f);
		cout << ligneDeSeparation << endl;
	}
}

int main()
{
	#ifdef VERIFICATION_ALLOCATION_INCLUS
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	#endif
	bibliotheque_cours::activerCouleursAnsi();
	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	ListeFilms listeFilms = creerListe("films.bin");

	cout << ligneDeSeparation << "Le premier film de la liste est:" << endl;
	afficherFilm(listeFilms.obtenirElements()[0]);
	cout << ligneDeSeparation << "Les films sont:" << endl;
	listeFilms.afficherListeFilms();

	listeFilms.trouverActeur("Benedict Cumberbatch")->anneeNaissance = 1976;
	cout << ligneDeSeparation << "Liste des films où Benedict Cumberbatch joue sont:" << endl;
	afficherFilmographieActeur(listeFilms, "Benedict Cumberbatch");

	listeFilms.detruireFilm(listeFilms.obtenirElements()[0]);
	cout << ligneDeSeparation << "Les films sont maintenant:" << endl;
	listeFilms.afficherListeFilms();
	afficherFilmographieActeur(listeFilms, "Acteur Impossible");

	listeFilms.detruireListeFilms();
}
