﻿/*************************************************************************************************************************
*Auteur : Pisani Fosso A00187566                                                                                        **
**************************************************************************************************************************
*But:	Dans cette deuxième partie du devoir, vous devez implémenter un annuaire                                        **
*		téléphonique simple en utilisant les tables de hachage.                                                         **
*		Votre annuaire peut être géré en utilisant les opérations suivantes :                                           **
*																														**
*			— a [correspondant][numérodetéléphone]. L’utilisateur demande d’ajouter une nouvelle entrée dans l’annuaire.**
*				Si le correspondant existe déjà, son numéro de téléphone doit être mis à jour.                          **
*			— s [correspondant]. L’utilisateurdemandede supprimer l’entrée de l’annuaire.                               **
*				Si aucune entrée portant le nom du correspondant n’existe,                                              **
*				la requête de l’utilisateur est simplement ignorée.                                                     **
*			— r [correspondant]. L’utilisateur demande d’obtenir le numéro de téléphone du correspondant.               **
*				Si ce dernier n’est pas trouvé, le message "non trouve" doit être afﬁché.                               **
**************************************************************************************************************************
*/


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Les coordon/es du contact seront stoqué dans une structure contenant le nom et le numéro
struct contact {
	string name;
	int number;
};

// Les numéros contenu dans notre phone book seront stoqué dans cette structure de données
struct Node {
	contact NewContact;
	Node* Next;
};

/*La class ci-dessous s'occupera de:
	- Ajouter ou modifier un contact dans la structure de données avec la fonction addphoneBook
	- Supprimeer un contact s'il se trouve dans la structure de données avec la fonction supphoneBook
	- Afficher un contat demandé s'il se trouve dans la structure avec la fonction showphoneBook
*/
class phoneBook
{
private:
	int size_table;
	int nameHashed;
public:
	int hashFunction(string);
	void addphoneBook(Node*&, contact);
	void supphoneBook(Node*&, string);
	void showphoneBook(Node*&, string);
	phoneBook(int);
	~phoneBook();
};

/*
*********************************************************************************
Nom de la fonction: hashFunction                                               **
*********************************************************************************
type de parametres: string                                                     **
*********************************************************************************
Description: Le string prit en parametre est convertis en int par la formule:  **
*																			   **
*																			   **
*				***************************************************			   **
*				**	 H(C) = somme ((C[i] * pow(R,i)) % P ) % M   **			   **
*				***************************************************			   **
*																			   **
*																			   **
*			 où C[i] est le code ASCII du i−ème caractère du correspondant C,  **
*			 T est le nombre de caractère dans C, P = 1009,                    **
*			 R = 31 et M est la taille de la table de hachage.                 **
*********************************************************************************
*/

int phoneBook::hashFunction(string contactName)
{
	int result;					//contiendra le résultat
	int somme = 0;				//contiendra la somme
	int ASCII;					//contiendra le caracter converti en ASCII
	for (int i = 0; i < contactName.length(); i++)
	{
		ASCII = contactName[i];		//Conversion en ASCII
		somme += fmod(ASCII * pow(31, i), 1009);
	}
	result = somme % size_table;
	return result;
}

/*
*********************************************************************************
Nom de la fonction: addphoneBook                                               **
*********************************************************************************
type de parametres: Node*&; contact                                            **
*********************************************************************************
Description: Le Noeud est prit en parametre par reference car il sera modifié  **
*			 le contact prit en parametre sera ajouté a la liste de contact    **
*********************************************************************************
*/
void phoneBook::addphoneBook(Node*& List, contact New)
{
	nameHashed = hashFunction(New.name);	//Hashage du nom du contact pour connaitre la position ou le sauvegarder dans l'annuaire
	Node* Save = List[nameHashed].Next;		//Sauvegarde de contact deja présenta dans l'emplacement

	//Recherche si le contact à ajouter existe déja si oui modifier juste le numéro avec le nouveau numéro
	while (List[nameHashed].Next != NULL)
	{
		if (List[nameHashed].Next->NewContact.name == New.name)		//Nom déjà existant
		{
			List[nameHashed].Next->NewContact.number = New.number;	//modification du numéro
			return;
		}

		List[nameHashed].Next = List[nameHashed].Next->Next;		//Contact suivant dans l'emplacement
	}
	Node* Newadd = new Node;		//Cree un nouveau contact
	Newadd->NewContact = New;		//ajoute coordonnées du contact
	Newadd->Next = Save;			//le nouveau contact pointe sur l'ancienne Liste de contacts
	List[nameHashed].Next = Newadd;	// Lier tout les contacts à l'emplacement
}

/*
*********************************************************************************
Nom de la fonction: supphoneBook                                               **
*********************************************************************************
type de parametres: Node*&; string                                             **
*********************************************************************************
Description: Le Noeud est prit en parametre par reference car il sera modifié  **
*			 le string prit en parametre sera utiliser pour recherche le contact*
*			 correspondant dans la liste et le supprimer                       **
*********************************************************************************
*/
void phoneBook::supphoneBook(Node*& List, string name)
{
	nameHashed = hashFunction(name);	//Hashage du nom du contact pour connaitre la position ou le sauvegarder dans l'annuaire

	//Recherche si le contact à supprimer existe si c'est pas le cas ne rien faire
	while (List[nameHashed].Next != NULL)
	{
		if (List[nameHashed].Next->NewContact.name == name)			//contact trouvé
		{
			Node* Old = List[nameHashed].Next;						//Sauvegarder l'infomation sur le contact à supprimer dans un nouveau Noeud
			List[nameHashed].Next = List[nameHashed].Next->Next;	//Changer le pointeur du contact
			delete Old;												//supprimer le contact
			return;
		}
		List[nameHashed].Next = List[nameHashed].Next->Next;
	}
	cout << "Not found" << endl;
}

/*
*********************************************************************************
Nom de la fonction: showphoneBook                                              **
*********************************************************************************
type de parametres: Node*&; string                                             **
*********************************************************************************
Description: Le Noeud est prit en parametre par reference car il sera modifié  **
*			 le string prit en parametre sera utiliser pour recherche le contact*
*			 correspondant dans la liste et afficher son numéro                **
*********************************************************************************
*/

void phoneBook::showphoneBook(Node*& List, string name)
{

	nameHashed = hashFunction(name); //Hashage du nom du contact pour connaitre la position ou le sauvegarder dans l'annuaire
	Node* Show = List[nameHashed].Next;

	//Recherche si le contact à afficher existe si c'est pas le cas afficher Non trouvé
	while (Show != NULL)
	{
		if (Show->NewContact.name == name)				//Contact trouvé
		{
			cout << Show->NewContact.number << endl;	//Afficher le numéro du contact
			return;
		}
		Show = Show->Next;
	}

	//Contact inexistant
	cout << "Non trouve (:" << endl;
}

//Constructeur initialise la taille du tableau
phoneBook::phoneBook(int size)
{
	size_table = size; 
}

//Destructeur
phoneBook::~phoneBook()
{
}

int main()
{
	
	ifstream myFile;

	myFile.open("phone_book.txt");	//Ouverture du fichier .txt
	if (myFile)
	{
		//Déclaration des variables
		int size_table;				//contiendra la taille du tableau
		int nomber_of_request;		//contiendra le nombre de requete
		char request;				//contiendra les requetes
		contact myContact;

		myFile >> size_table;					//Recuperer la taille du tableau dans le fichier

		Node *Phone = new Node[size_table];		//allouer de l'espace memoire au tableau de contact

		for (int i = 0; i < size_table; i++)
		{
			Phone[i].Next = NULL;				//Initialisation du contenu du tableau par NULL
		}

		//Instanciation de la class phoneBook
		phoneBook PhoneContain(size_table);

		//Recuperer le nombre de requetes dans le fichier
		myFile >> nomber_of_request;


		for (int i = 0; i < nomber_of_request; i++)
		{
			//Recuperer la requette dans le fichier
			myFile >> request;

			//évaluer la requette
			switch (request)
			{
					//Si la requtte est r, L’utilisateur demande d’obtenir le numéro de téléphone du correspondant. 
			case 'r': {
				myFile >> myContact.name;
				PhoneContain.showphoneBook(Phone, myContact.name);
				break;
			}

					 //Si la requette est a, L’utilisateur demande d’ajouter une nouvelle entrée dans l’annuaire.
			case 'a': {
				myFile >> myContact.name;
				myFile >> myContact.number;
				PhoneContain.addphoneBook(Phone, myContact);
				break;
			}

					  //si la requette est s, L’utilisateur demande de supprimer l’entrée de l’annuaire.
			case 's': {
				myFile >> myContact.name;
				PhoneContain.supphoneBook(Phone, myContact.name);
				break;
			}
					  //Au cas contraire ne rine faire.
			default:
				break;
			}
		}
		//Desallouer l<espace m/moire occup/ par le tableau
		delete[] Phone;
	}
	else cerr << "Erreur" << endl;

	//Fermer le fichier
	myFile.close();

	return 0;
}


//Exemple:
/*
Input file contain: 
5 
9 
r maison 
a maison 5874932 
a police 911 
r police 
s maison 
a Moi 5487896 
a Maison 5874932 
r maison 
r Maison

Output Shell: 
Non trouve (:
911
Non trouve (:
5874932

*/