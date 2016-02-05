/*************************************************************************

	Fait par Antoine Latendresse, Léa Kelly et Simon Roy

*************************************************************************/


#include "CSS.cpp"
#include "keywords.cpp"
#include "simon.cpp"

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include<fstream>
#include <iostream>
using namespace std;




const string COULEUR_CODE = "-couleur";
const string STATISTIQUE = "-stats";

// Non utilisé pour l'instant donc pas nécessaire ?
const string DEFAULT_FILE = "default.cpp";

void generer_stats(const string nom_fichier)
{
	map<string, int> donnees;
	ifstream in{ nom_fichier };

	// Il faut faire une expression régulière pour filtrer ce que l'on met dans données
	for (string s; in >> s;)
		donnees[s]++;

	ofstream output;
	output.open(nom_fichier + "_stats.txt");

	if (output.is_open())
	{
		for (auto & p : donnees)
		{
			output << p.first << " : " << p.second << endl;
		}
	}

	output.close();
}

// Fonction utilisée pour vérifier l'existence d'un fichier
// Ouvrir le fichier et le convertir en booléen
bool fichier_existe(const string &nom)
{
	return !!(ifstream{ nom });
}

int main(int argc, char * argv[])
{
	bool couleur_code = false;
	bool fichier_statistique = false;

	/*On a pas besoin de les lignes suivantes je me trompe ?
	// le premier paramètre est le nom de l'exécutable
	string nom_programme = argv[0];*/

	vector<string> noms_fichiers;
	/* Non-utilisé ?
	vector<string> textes_fichiers; */

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			string arg = argv[i];
			if (arg[0] == '-' || arg[0] == '/') // c'est une option
			{
				if (arg.compare(COULEUR_CODE))
				{
					couleur_code = true;
				}
				else if (arg.compare(STATISTIQUE))
				{
					fichier_statistique = true;
				}
			}
			else // c'est un fichier
			{
				// Fonctionne !
				if (fichier_existe(arg))
					noms_fichiers.push_back(arg);
				else
					cout << "Le fichier " << arg << " n'existe pas !" << endl;
			}
		}
	}

	// Code de test pour s'assurer que les options sont prises en compte
	cout << couleur_code << endl;
	cout << fichier_statistique << endl;

	/*
		 pour les fichiers qui existent :
		 - ouvrir le fichier et lire le contenu
		 - faire les statistiques si nécessaire (en premier pour ne pas avoir le html dans le chemin)
		 - ajouter du css si nécessaire
		 - ensuite, ajouté le html pour faire du texte un document html valide (doctype, head, body, ect ...)
		 - confirmer la fin de l'opération avec un message pour chaque fichier (opération terminée ou fichier introuvable)
		 - réorganiser le main en fonctions pour éviter qu'il soit excessivement long
	*/

	ifstream lire_fichier;
	ofstream ecrire_fichier;
	vector<string> texte_fichier;
	string ligne;

	for (auto it = begin(noms_fichiers); it != end(noms_fichiers); it++)
	{
		lire_fichier.open(*it);
		if (lire_fichier.is_open())
		{
			while (getline(lire_fichier, ligne))
			{
				texte_fichier.push_back(ligne);
			}
		}
		lire_fichier.close();

		if (fichier_statistique)
			generer_stats(*it);

		if (couleur_code)
		{
			// ajouter le css au texte (à chaque ligne ?)
		}

		// ../../ ne change rien... cela écrit toujours dans le fichier courant
		ecrire_fichier.open(*it + ".html");
		if (ecrire_fichier.is_open())
		{
			for (auto it_lecture = begin(texte_fichier); it_lecture != end(texte_fichier); it_lecture++)
				ecrire_fichier << *it_lecture << "<br />";
		}
		ecrire_fichier.close();
	}

}