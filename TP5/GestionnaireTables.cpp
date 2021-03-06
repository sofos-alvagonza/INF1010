/********************************************
* Titre: Travail pratique #5 - gestionnaireTables.cpp
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/


#include "GestionnaireTables.h"
#include "LectureFichierEnSections.h"

Table* GestionnaireTables::getTable(int id) const{
	return *find(conteneur_.begin(), conteneur_.end(), id);

}

Table* GestionnaireTables::getMeilleureTable(int tailleGroupe) const {
	set<Table*>::iterator itr;
	set<Table*> tableSet = getConteneur();
	Table* meilleureTable = nullptr;

	for (itr = tableSet.begin(); itr != tableSet.end(); ++itr) {
		if ((!(*itr)->estOccupee()) && ((*itr)->getId() != ID_TABLE_LIVRAISON)) {
			int nPlaces = (*itr)->getNbPlaces();
			if ((nPlaces >= tailleGroupe) && (!meilleureTable || nPlaces < meilleureTable->getNbPlaces())) {
				meilleureTable = (*itr);
			}
		}
	}

	return meilleureTable;

}

void GestionnaireTables::lireTables(const string& nomFichier)
{
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection("-TABLES");
	while (!fichier.estFinSection()) {
		int id, nbPlaces;
		fichier >> id >> nbPlaces;
		ajouter(new Table(id, nbPlaces));
	}
}

void GestionnaireTables::afficherTables(ostream& os) const {
	set<Table*>::iterator itr = conteneur_.begin();
	for (itr; itr != conteneur_.end(); itr++) {
		os << **itr;
	}

}


