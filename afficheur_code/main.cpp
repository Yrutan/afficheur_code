/*************************************************************************

	Fait par Antoine Latendresse, Léa Kelly et Simon Roy

*************************************************************************/

#include "keywords.cpp"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <fstream>
#include <iostream>
using namespace std;



const string OPTION_COULEUR_CODE = "couleur";
const string OPTION_STATISTIQUE = "stats";
const string REGEX = "[a-zA-Z0-9_]+";

const string ESPERLUETTE = "&amp"; // &
const string PLUS_PETIT = "&lt"; // <
const string PLUS_GRAND = "&gt"; // >

map<string, string> SPECIAL_CHAR{ 
	{ "&" , ESPERLUETTE },
	{ "<", PLUS_PETIT },
	{ ">" , PLUS_GRAND }
};

const string BALISE_DEBUT = "<span>";
const string BALISE_FIN = "</span>";


const string CSS_BLEU = " class='bleu'";
const string OUVERTURE_SPAN = "<span";
const string FERMETURE_SPAN = ">";


string sanitizeString(string ligne)
{
	if ( ligne.size() > 0 )
	{
		int index;
		for (auto courant = SPECIAL_CHAR.begin(), fin = SPECIAL_CHAR.end(); courant != fin; courant++)
		{
			for (size_t i = 0; i < ligne.size(); i++)
			{
				index = 0;
				while ( (index = ligne.find(courant->second, index) ) != string::npos)
				{
					if (index != string::npos)
					{
						string new_ligne = ligne.substr(0, index - 1 )
							+ courant->second
							+ ligne.substr( index + 1, ligne.size() );
						ligne = new_ligne;
						index += courant->second.size();
					}
				}
			}
		}
	}
	return ligne;
}


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
	// Je sais que la regex n'est pas la bonne pour ce qui a été demandé,
	// cela est également dû à un manque de temps pour finir
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
	//ordre_lexico(begin(stats), end(stats));

	ofstream output;
	output.open(nom_fichier + "_stats.txt");

	if (output.is_open())
		for (auto & p : stats)
			output << p.first << " : " << p.second << endl;

	output.close();
}

// Fonction utilisée pour vérifier l'existence d'un fichier
// Ouvrir le fichier et le convertir en booléen
bool fichier_existe(const string &nom)
{
	return !!(ifstream{ nom });
}

void creer_fichier_web(string nom_fichier, vector<string>texte)
{
	if (!empty(texte))
	{
		texte[0] = "<!DOCTYPE html><head><style>.bleu{color:blue};</style><title>Afficheur de code</title></head><pre>" + texte[0];
		texte[texte.size() - 1] += "</pre>";
	}
	ofstream ecrire_fichier;
	ecrire_fichier.open(nom_fichier + ".html");
	if (ecrire_fichier.is_open())
	{
		for (auto it_lecture = begin(texte); it_lecture != end(texte); it_lecture++)
			ecrire_fichier << *it_lecture << "<br>";
	}
	ecrire_fichier.close();
}




string keywordWithCSS(const string &keyword)
{
	return OUVERTURE_SPAN + CSS_BLEU + FERMETURE_SPAN + keyword + BALISE_FIN;
}

void ajouter_css(vector<string> &lignes)
{
	//bool open_tag = false;
	int index;
	for each (string keyword in liste)
	{
		for (size_t i = 0; i < lignes.size(); i++)
		{
			index = 0;
			while ( ( index = lignes[i].find(keyword + " ", index) ) != string::npos)
			{
				string new_keyword = keywordWithCSS(keyword);

				lignes[i].replace(index, keyword.length(), new_keyword);
				index += new_keyword.length();
					
				//cout << lignes[i] << endl;
			}
		}
	}
}



void remplacer(string &toAdd, const string &toRemove, string )
{

}

int main(int argc, char * argv[])
{
	bool couleur_code = false;
	bool fichier_statistique = false;

	vector<string> noms_fichiers;
	// début de la gestion des paranètres
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			string arg = argv[i];
			if (arg[0] == '-' || arg[0] == '/') // c'est une option
			{
				if (arg.substr(1) == OPTION_COULEUR_CODE)
				{
					couleur_code = true;
				}
				else if (arg.substr(1) == OPTION_STATISTIQUE)
				{
					fichier_statistique = true;
				}
				else
				{
					cout << "L'option : " << arg << "n'est pas valide pour ce programme." << endl;
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
	// fin de la gestion des paranètres

	// Code de test pour s'assurer que les options sont prises en compte
	cout << "couleur : " << couleur_code << endl;
	cout << "statistique : " << fichier_statistique << endl;

	ifstream lire_fichier;
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

		/*
		for each (string ligne in texte_fichier)
		{
			ligne = sanitizeString(ligne);
		}
		*/
		if (couleur_code)
		{
			ajouter_css(texte_fichier);
		}
		creer_fichier_web(*it, texte_fichier);
	}

	cout << "fin des operations" << endl;
}


