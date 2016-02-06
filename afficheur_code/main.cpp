/*************************************************************************

	Fait par Antoine Latendresse, L�a Kelly et Simon Roy

*************************************************************************/

#include "keywords.cpp"
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

const map<string, string> sanitizer{ 
	{ "<", PLUS_PETIT },
	{ ">" , PLUS_GRAND },
	{ "&" , ESPERLUETTE } 
};

/*
void sanitizeString(string &ligne)
{
	int index = 0;
	while(index != string::npos)
	{
		
		index = ligne.find(chaine, index);
		if (index != string::npos)
		{
			ligne.replace(index, chaine.length(), sanitizer[chaine]);
			index += sanitizer[chaine].length;
		}
	}
}
*/

const string COULEUR_CODE = "couleur";
const string STATISTIQUE = "stats";
const string REGEX = "[a-zA-Z0-9_]+";

// Pas eu le temps de finir
/*template <class It>
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
*/

bool compare(const pair<string, int>&i, const pair<string, int>&j)
{
	return i.second > j.second;
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
	//ordre_lexico(begin(stats), end(stats));

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

void creer_fichier_web(string nom_fichier, vector<string>texte)
{
	if (!empty(texte))
	{
		texte[0] = "<!DOCTYPE html> <title>Afficheur de code</title><pre>" + texte[0];
		texte[texte.size() - 1] += "</pre>";
	}
	ofstream ecrire_fichier;
	ecrire_fichier.open(nom_fichier + ".html");
	if (ecrire_fichier.is_open())
	{
		for (auto it_lecture = begin(texte); it_lecture != end(texte); it_lecture++)
			ecrire_fichier << *it_lecture << "<br />";
	}
	ecrire_fichier.close();
}

void ajouter_css(vector<string> &lignes)
{
	int index;
	for each (string keyword in liste)
	{
		for (int i = 0; i < lignes.size(); i++)
		{
			index = 0;
			while (index == string::npos)
			{
				index = lignes[i].find(keyword, index);
				if (index != string::npos)
				{
					/*
					string ligne = texte_fichier[i];
					texte_fichier[i] = ligne.substr(0, index - 1)
					+ OUVERTURE_BALISE + STYLE_BLEU + FERMETURE_BALISE
					+ ligne.substr(index, index + keyword.length() ) + BALISE_FIN
					+ ligne.substr(index + keyword.length(), ligne.length() );
					*/

					lignes[i].replace(index, keyword.length(), OUVERTURE_BALISE + STYLE_BLEU + FERMETURE_BALISE + keyword + BALISE_FIN);
					index += OUVERTURE_BALISE.length() + STYLE_BLEU.length() + FERMETURE_BALISE.length() + keyword.length() + BALISE_FIN.length();
				}
			}
		}
	}
}


int main(int argc, char * argv[])
{
	bool couleur_code = false;
	bool fichier_statistique = false;

	vector<string> noms_fichiers;

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			string arg = argv[i];
			if (arg[0] == '-' || arg[0] == '/') // c'est une option
			{
				if (arg.substr(1) == COULEUR_CODE)
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
		// J'ai essay� de mettre la lecture dans une fonction � part, mais quand on lui
		// envoyait une variable ifstream par param�tre, cela g�n�rait une erreur
		// que je ne comprenais pas
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
			ajouter_css(texte_fichier);
		}

		creer_fichier_web(*it, texte_fichier);
	}
}


