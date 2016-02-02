/*************************************************************************

	Fait par Antoine Latendresse, L�a Kelly et Simon Roy

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

	if (fichier_statistique)
	{

	}

	if (couleur_code)
	{

	}



}