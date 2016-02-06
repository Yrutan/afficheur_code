/*************************************************************************

	Fait par Antoine Latendresse, L�a Kelly et Simon Roy

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

const string BALISE_DEBUT = "<span >";
const string BALISE_FIN = "</span>";

const string STYLE_BLEU = "style = 'color:blue'";
const string OUVERTURE_BALISE = "<span ";
const string FERMETURE_BALISE = " >";


const string PLUS_PETIT = "&lt"; // <
const string PLUS_GRAND = "&gt"; // >
const string ESPERLUETTE = "&amp"; // &



const string COULEUR_CODE = "-couleur";
const string STATISTIQUE = "-stats";
const string REGEX = "[a-zA-Z0-9_]+";

bool compare(const pair<string, int>&i, const pair<string, int>&j)
{
	return i.second > j.second;
}

// Pas eu le temps de finir
template <class It>
void ordre_lexico(It debut, It fin)
{
	auto prochain = ++debut;
	for (; debut != fin; debut++)
	{
		if (lexicographical_compare(debut->first, debut->second, prochain->first, prochain->second))
			swap(debut, prochain);
		++prochain;
	}
}

void generer_stats(const string nom_fichier)
{
	// Je sais que la regex n'est pas la bonne pour ce qui a �t� demand�,
	// cela est �galement d� � un manque de temps pour finir
	string pattern{ "[a-zA-Z0-9]+" };
	regex expression{ pattern };

	map<string, int> donnees;
	ifstream in{ nom_fichier };

	for (string s; in >> s;)
		if(regex_match(s, expression))
			donnees[s]++;

	vector<pair<string, int>> stats;

	// Sort ne marche malheuresment pas sur une map, il faut donc transf�rer
	// les donn�es dans un vector
	for (auto & p : donnees)
		stats.push_back(make_pair(p.first, p.second));

	sort(stats.begin(), stats.end(), compare);
	ordre_lexico(begin(stats), end(stats));

	ofstream output;
	output.open(nom_fichier + "_stats.txt");

	if (output.is_open())
		for (auto & p : stats)
			output << p.first << " : " << p.second << endl;

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
			size_t index;
			for each (string keyword in liste)
			{
				for each (string ligne in texte_fichier)
				{
					index = 0;
					while (index != string::npos)
					{
						index = ligne.find(keyword, index);
						if (ligne.find(keyword) != string::npos)
						{

							ligne.replace(index, keyword.length(),
								OUVERTURE_BALISE + STYLE_BLEU + FERMETURE_BALISE + keyword + BALISE_FIN);
						}
					}
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