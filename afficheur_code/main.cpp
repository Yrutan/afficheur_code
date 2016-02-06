/*************************************************************************

	Fait par Antoine Latendresse, Léa Kelly et Simon Roy

*************************************************************************/

#include "keywords.cpp"
#include "simon.cpp"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <regex>
#include <iostream>
using namespace std;

const string STYLE_BLEU = "color='#6495ED'"; // #6495ED Cornflowerblue
const string BALISE_DEBUT = "<span >";
const string BALISE_OUVERTURE = "<span ";
const string BALISE_FERMETURE = " >";
const string BALISE_FIN = "</span>";

const string PLUS_PETIT = "&lt"; // <
const string PLUS_GRAND = "&gt"; // >
const string ESPERLUETTE = "&amp"; // &



const string COULEUR_CODE = "-couleur";
const string STATISTIQUE = "-stats";
const string REGEX = "[a-zA-Z0-9_]+";

// Non utilisé pour l'instant donc pas nécessaire ?
// const string DEFAULT_FILE = "default.cpp";

bool compare(const pair<string, int>&i, const pair<string, int>&j)
{
	return i.second > j.second;
}

void generer_stats(const string nom_fichier)
{
	// La regex n'est pas encore finie... Elle fonctionne mais ne traite pas encore toutes les conditions demandées par le prof
	// Il faut que chacune des données contienne au moins un caractère alphanumérique pour passer
	// Il faudrait aussi peut-être séparer les ; ??
	// Finalement, le prof dit qu'on n'est pas obliger de traiter les suffices comme U, UL, f
	string pattern{ "[a-zA-Z0-9]+" };
	regex expression{ pattern };

	map<string, int> donnees;
	ifstream in{ nom_fichier };

	for (string s; in >> s;)
		if(regex_match(s, expression))
			donnees[s]++;

	vector<pair<string, int>> stats;

	// Sort ne marche malheuresment pas sur une map, il faut donc transférer
	// les données dans un vector
	for (auto & p : donnees)
		stats.push_back(make_pair(p.first, p.second));

	sort(stats.begin(), stats.end(), compare);

	ofstream output;
	output.open(nom_fichier + "_stats.txt");

	if (output.is_open())
	{
		for (auto & p : stats)
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
				if (arg == COULEUR_CODE)
				{
					couleur_code = true;
				}
				else if (arg == STATISTIQUE)
				{
					fichier_statistique = true;
				}
			}
			else // c'est un fichier
			{
				if (fichier_existe(arg))
					noms_fichiers.push_back(arg);
				else
					cout << "Le fichier " << arg << " n'existe pas !" << endl;
			}
		}
	}

	// Code de test pour s'assurer que les options sont prises en compte
	cout << "couleur : " << couleur_code << endl;
	cout << "statistique : " << fichier_statistique << endl;

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
         size_t index = 0;
         for each (string keyword in liste)
         {
            //auto it = begin(texte_fichier); it != end(texte_fichier); ++it
            for (int i = 0; i < texte_fichier.size(); i++)
            {

               index = texte_fichier[i].find(keyword, index);

               if (index == string::npos)break;
               
               string css_start;
               string css_end;
               texte_fichier[i].replace(index, keyword.length(), css_start + keyword + css_end);
            }
         }
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