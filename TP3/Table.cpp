/*
* Titre : Table.cpp - Travail Pratique #3
* Date : 11 F�vrier 2019
* Auteur :Fatou S. MOUNZEO
*/

#include "Table.h"


//constructeurs
Table::Table()
{
	id_ = -1;
	nbPlaces_ = 1;
	nbClientsATable_ = 0;
	clientPrincipal_ = nullptr;
}

Table::Table(int id, int nbPlaces)
{
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbClientsATable_ = 0;
	clientPrincipal_ = nullptr;
}

//getters
int Table::getId() const
{
	return id_;
}

int Table::getNbPlaces() const
{
	return nbPlaces_;
}

bool Table::estOccupee() const
{
	return nbClientsATable_!=0;
}

bool Table::estPleine() const
{
	return nbPlaces_ == 0;
}

int Table::getNbClientsATable() const
{
	return nbClientsATable_;
}

vector<Plat*> Table::getCommande() const
{
	return commande_;
}

Client* Table::getClientPrincipal() const
{
	return clientPrincipal_;
}

double Table::getChiffreAffaire() const {
	double chiffre = 0;
	for (unsigned i = 0; i < commande_.size(); ++i){
		if(commande_[i]->getType() == Regulier){
			chiffre += (commande_[i]->getPrix() - commande_[i]->getCout());
		}
		if(commande_[i]->getType() == Bio ){
			chiffre += ((( 1 + (static_cast<PlatBio*>(commande_[i]))->getEcoTaxe()) * commande_[i]->getPrix()) - commande_[i]->getCout());
		}
		if(commande_[i]->getType() == Custom){
			chiffre += ((commande_[i]->getPrix() + (static_cast<PlatCustom*>(commande_[i]))->getSupplement()) - commande_[i]->getCout());
		}
	}
	return chiffre;
}

//setters
void Table::libererTable() {
	nbPlaces_ += nbClientsATable_;
	nbClientsATable_ = 0;
	commande_.clear();
}

void Table::placerClients(int nbClient) {
	nbPlaces_ -= nbClient;
	nbClientsATable_ = nbClient;
}

void Table::setId(int id) {
	id_ = id;
}

void Table::setClientPrincipal(Client* clientPrincipal){
	if(clientPrincipal->getStatut() == Occasionnel){
		clientPrincipal_ = new Client(clientPrincipal->getNom(),
		clientPrincipal->getPrenom(), clientPrincipal->getTailleGroupe());
	}

	if(clientPrincipal->getStatut()== Fidele){
		ClientRegulier* clientR ;
		clientR = static_cast<ClientRegulier*>(clientPrincipal);

		clientPrincipal_ = new ClientRegulier( clientR->getNom(), clientR->getPrenom(), clientR->getTailleGroupe(), clientR->getNbPoints() );
	}

	if(clientPrincipal->getStatut() == Prestige){
		ClientPrestige* clientP;
	   clientP = static_cast<ClientPrestige*>(clientPrincipal);
	   clientPrincipal_ = new ClientPrestige(clientP->getNom(), clientP->getPrenom(),
		   clientP->getTailleGroupe(), clientP->getNbPoints(),clientP->getAddresseCode());
	}
	clientPrincipal_ = clientPrincipal;
}

//autres methodes
void Table::commander(Plat* plat) {
	commande_.push_back(plat);
}


//affichage

ostream& operator<<(ostream& os, const Table& table)
{

	os << "La table numero " << table.id_;
	if (table.estOccupee())
	{
		os << " est occupee. ";
		os << *(table.getClientPrincipal()) << endl << "\t"; //verifier si deja implemente

		if (!table.commande_.empty())
		{
			os << "Voici la commande passee par les clients : " << endl;
			for (unsigned i = 0; i < table.commande_.size(); ++i)
			{
				os << "\t" << *table.commande_[i];
			}
		}
		else
			os << "Mais ils n'ont rien commande pour l'instant. " << endl;
	}
	else
		os << " est vide. " << endl;

	return os;
}