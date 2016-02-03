/*************************************************************************

	Fait par Antoine Latendresse, L�a Kelly et Simon Roy

*************************************************************************/


#include <string>
#include <vector>
#include <map>

#include <algorithm>


#include<fstream>
#include <iostream>
using namespace std;




const string COULEUR_CODE = "-couleur";
const string STATISTIQUE = "-stats";

const string DEFAULT_FILE = "default.cpp";





int main( int argc, char * argv[] )
{
	bool couleur_code = false;
	bool fichier_statistique = false;

	// le premier param�tre est le nom de l'ex�cutable
	string nom_programme = argv[0];

	vector<string> noms_fichiers;
	vector<string> textes_fichiers;

	if ( argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			string arg = argv[i];
			if ( arg[0] == '-' || arg[0] == '/' ) // c'est une option
			{
				if ( arg.compare(COULEUR_CODE) )
				{
					couleur_code = true;
				}
				else if ( arg.compare(STATISTIQUE) )
				{
					fichier_statistique = true;
				}
			}
			else // c'est un fichier
			{
				/*
					� faire avant ou apr�s :
					- v�rifier si tous les fichiers existent 
				*/
				noms_fichiers.push_back(arg);
			}
		}
	}
	/*
		 pour les fichiers qui existent : 
		 - ouvrir le fichier et lire le contenu
		 - faire les statistiques si n�cessaire (en premier pour ne pas avoir le html dans le chemin)
		 - ajouter du css si n�cessaire 
		 - ensuite, ajout� le html pour faire du texte un document html valide (doctype, head, body, ect ...)
		 - confirmer la fin de l'op�ration avec un message pour chaque fichier (op�ration termin�e ou fichier introuvable)
	*/

	ifstream lire_fichier;
	vector<string> texte_fichier;
	string ligne;

	for (auto it = begin(noms_fichiers); it != end(noms_fichiers); it++)
	{
		lire_fichier.open(*it);
		if ( lire_fichier.is_open() )
		{
			while (getline(lire_fichier, ligne))
			{
				texte_fichier.push_back(ligne);
			}
		}
		lire_fichier.close();
	}

	if (fichier_statistique)
	{
		// compter / utiliser des maps pour compter le nombre de fois que les mots cl� se r�p�te
	}

	if (couleur_code)
	{
		// ajouter le css au texte (� chaque ligne ?)
	}


	
	// �crire dans le fichier html (et le cr�er)
	ofstream ecrire_fichier;
	for (auto it = begin(noms_fichiers); it != end(noms_fichiers); it++)
	{
		ecrire_fichier.open(*it);
		if (ecrire_fichier.is_open())
		{
			// �crit le texte dans le fichier, endl indique la fin d'une ligne
			ecrire_fichier << "output" << endl;
		}
		ecrire_fichier.close();
	}

}