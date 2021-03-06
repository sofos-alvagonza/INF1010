/*
* Titre : Menu.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
* Modifie par: Sofia Alvarez (1894026) et Justin de Meulemeester ( )
* Date: 08 fevrier 2019
*/

#ifndef MENU_H
#define MENU_H

#include "Plat.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

enum TypeMenu{Matin, Midi, Soir};
const int MAXPLAT = 5;
class Menu {
public:
	// constructeurs
	Menu();
	Menu(string fichier, TypeMenu type);

	//destructeur
	~Menu();

	//getters
	int getNbPlats() const;

	//affichage
	void afficher() const; //A MODIFIER

	//methodes en plus
	Plat* trouverPlat(const string& nom) const; // A MODIFIER
	Plat * trouverPlatMoinsCher() const; // Utilise les vecteurs (NE PAS MODIFIER)
	//void ajouterPlat(const Plat & plat); // A MODIFIER
	bool lireMenu(const string& fichier);
	friend ostream& operator<<(ostream& out, const Menu& menu);
	Menu& operator+=(const Plat& plat);
	Menu& operator=(const Menu& menu);

private :
	// A MODIFIER
	int capacite_;
	vector<Plat*> listePlats;
	int nbPlats_;
	TypeMenu type_;

};

#endif // !MENU_H
