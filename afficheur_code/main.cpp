/*************************************************************************

	Fait par Antoine Latendresse, L�a Kelly et Simon Roy

*************************************************************************/


#include "CSS.cpp"
#include "keywords.cpp"
#include "simon.cpp"

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include<fstream>
#include <regex>
#include <iostream>
using namespace std;




const string COULEUR_CODE = "-couleur";
const string STATISTIQUE = "-stats";
const string REGEX = "[a-zA-Z0-9_]+";

// Non utilis� pour l'instant donc pas n�cessaire ?
// const string DEFAULT_FILE = "default.cpp";

void generer_stats(const string nom_fichier)
{
	string pattern{ "[a-zA-Z_]([a-zA-Z0-9_])*" };
	regex expression{ pattern };

	map<string, int> donnees;
	ifstream in{ nom_fichier };

	// Il faut faire une expression r�guli�re pour filtrer ce que l'on met dans donn�es
	for (string s; in >> s;)
		if(regex_match(s, expression))
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

// Fonction utilis�e pour v�rifier l'existence d'un fichier
// Ouvrir le fichier et le convertir en bool�en
bool fichier_existe(const string &nom)
{
	return !!(ifstream{ nom });
}

int main(int argc, char * argv[])
{
	bool couleur_code = false;
	bool fichier_statistique = false;

	/*On a pas besoin de les lignes suivantes je me trompe ?
	// le premier param�tre est le nom de l'ex�cutable
	string nom_programme = argv[0];*/

	vector<string> noms_fichiers;
	/* Non-utilis� ?
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
	cout << couleur_code << endl;
	cout << fichier_statistique << endl;

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
			// ajouter le css au texte (� chaque ligne ?)
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

		// ../../ ne change rien... cela �crit toujours dans le fichier courant
		ecrire_fichier.open(*it + ".html");
		if (ecrire_fichier.is_open())
		{
			for (auto it_lecture = begin(texte_fichier); it_lecture != end(texte_fichier); it_lecture++)
				ecrire_fichier << *it_lecture << "<br />";
		}
		ecrire_fichier.close();
	}

}