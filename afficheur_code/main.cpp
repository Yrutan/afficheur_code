/*************************************************************************

	Fait par Antoine Latendresse, Léa Kelly et Simon Roy

*************************************************************************/


#include <string>
#include <vector>
#include <map>

#include <algorithm>

#include <iostream>
using namespace std;




const string COULEUR_CODE = "-couleur";
const string STATISTIQUE = "-stats";

const string DEFAULT_FILE = "default.cpp";

int main( int argc, char * argv[] )
{
	bool couleur_code = false;
	bool fichier_statistique = false;

	// le premier paramètre est le nom de l'exécutable
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
					à faire avant ou après :
					- vérifier si tous les fichiers existent 
				*/
				noms_fichiers.push_back(arg);
			}
		}
	}
	/*
		 pour les fichiers qui existent : 
		 - ouvrir le fichier et lire le contenu
		 - faire les statistiques si nécessaire (en premier pour ne pas avoir le html dans le chemin)
		 - ajouter du css si nécessaire 
		 - ensuite, ajouté le html pour faire du texte un document html valide (doctype, head, body, ect ...)
		 - confirmer la fin de l'opération avec un message pour chaque fichier (opération terminée ou fichier introuvable)
	*/

	if (fichier_statistique)
	{

	}

	if (couleur_code)
	{

	}



}