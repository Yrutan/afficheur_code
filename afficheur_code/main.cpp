/*************************************************************************

	Fait par Antoine Latendresse, L�a Kelly et Simon Roy

*************************************************************************/
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <fstream>
#include <iostream>
#include <chrono>
#include "keywords.cpp"
#include "initialisation.cpp"
#include "sequentiel.cpp"
#include "parallele.cpp"
#include "timer.cpp"
using namespace std;
using namespace std::chrono;

const string OPTION_COULEUR_CODE = "couleur";
const string OPTION_STATISTIQUE = "stats";
const string REGEX = "[a-zA-Z0-9_]+";
const int NBFICHIERS = 1000;

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

const string CSS_BLEU = " class='bleu' ";
const string OUVERTURE_SPAN = "<span ";
const string FERMETURE_BALISE = " >";

bool compare(const pair<string, int>&i, const pair<string, int>&j)
{
	// si ils n'ont pas la m�me valeur (m�me nombre) alors on compare lequel en a le plus
	// sinon on les compare de mani�re lexicographique
	return i.second != j.second ? i.second > j.second : std::lexicographical_compare(i.first.begin(), i.first.end(), j.first.begin(), j.first.end());
}

void generer_stats(const string nom_fichier)
{
	string pattern{ "[a-zA-Z0-9]+" };
	regex expression{ pattern };

	map<string, int> donnees;
	ifstream in{ nom_fichier };

	for (string s; in >> s;)
		if(regex_match(s, expression))
			donnees[s]++;

	vector<pair<string, int>> stats;

	for (auto & p : donnees)
		stats.push_back(make_pair(p.first, p.second));

	sort(stats.begin(), stats.end(), compare);

	ofstream output(nom_fichier +"_stats.txt");

	if (output.is_open())
		for (auto & p : stats)
			output << p.first << " : " << p.second << endl;

	// pas de close(), car les flux sont des objets RAII
}

// Fonction utilis�e pour v�rifier l'existence d'un fichier
// Ouvrir le fichier et le convertir en bool�en
bool fichier_existe(const string &nom)
{
	return !!(ifstream{ nom });
}


void remplacer(const string &toAdd, const string &toRemove, string &toModified)
{
	int index = 0;
	while ((index = toModified.find(toRemove, index)) != string::npos)
	{
		toModified.replace(index, toRemove.length(), toAdd);
		index += toAdd.length();
	}
}
string keywordWithCSS(const string &keyword)
{
	return OUVERTURE_SPAN + CSS_BLEU + FERMETURE_BALISE + keyword + BALISE_FIN;
}
void ajouter_css(vector<string> &lignes)
{
	//bool open_tag = false;
	int index = 0;
	for (const string &keyword : LISTE)
	{
		for (size_t i = 0; i < lignes.size(); ++i)
		{
			// r�initialise l'index � 0 apr�s chaque ligne
			index = 0;
			while ((index = lignes[i].find(keyword + " ", index)) != string::npos)
			{
				string new_keyword = keywordWithCSS(keyword);

				lignes[i].replace(index, keyword.length(), new_keyword);
				index += new_keyword.length();
			}
		}
	}
}

void creer_fichier_web(string nom_fichier, vector<string>texte, const bool &couleur = false)
{
	if (!empty(texte))
	{
		for (string &ligne :texte)
		{
			remplacer(SPECIAL_CHAR["&"], "&", ligne);
			remplacer(SPECIAL_CHAR["<"], "<", ligne);
			remplacer(SPECIAL_CHAR[">"], ">", ligne);
		}
		if (couleur)
		{
			ajouter_css(texte);
		}
		texte[0] = "<!DOCTYPE html><head><style>.bleu{color:blue};</style><title>Afficheur de code</title></head><pre>" + texte[0];
		texte.back() += "</pre>";
	}
	ofstream ecrire_fichier;
	ecrire_fichier.open(nom_fichier + ".html");
	if (ecrire_fichier.is_open())
	{
		for (auto it_texte = begin(texte); it_texte != end(texte); it_texte++)
			ecrire_fichier << *it_texte << "<br>";
	}
	ecrire_fichier.close();
}


void sequentiel(const vector<string> &noms_fichiers, const bool couleur = true, const bool statistique = true)
{
	ifstream lire_fichier;
	vector<string> texte_fichier;
	string ligne;

	for (auto it = begin(noms_fichiers); it != end(noms_fichiers); it++)
	{
		/*for (int i = 0; i < NBFICHIERS; ++i)
		{*/
			lire_fichier.open(*it);
			if (lire_fichier.is_open())
			{
				while (getline(lire_fichier, ligne))
				{
					texte_fichier.push_back(ligne);
				}
			}
			lire_fichier.close();

			if (statistique)
				generer_stats(*it);

			creer_fichier_web(*it, texte_fichier, couleur);
		//}

	}
}


int main(int argc, char * argv[])
{
	/*********************************************
	* Zone d'initialisation du programme
	*********************************************/ 

	Initialisation init( argc, argv, std::cout);
	ofstream output("resultats_temps.txt");

	// confirmation des param�tres
	cout << std::boolalpha; // permet d'afficher true/false au lieu de 1/0
	cout << "Language de programmation recherche : " << init.language_prog << endl;
	cout << "Afficher la couleur : " << init.couleur << endl;
	cout << "Generer le fichier de statistique : " << init.statistique << endl;
	cout << "Nombre de fichiers demandes : " << init.noms_fichiers.size() << endl;
	cout << "Nombre de fichiers existants : " << init.noms_fichiers.size() << endl;

	/*********************************************
	* Fin d'initialisation du programme
	*********************************************/


	/*********************************************
	* D�but de la zone du traitement s�quentiel
	*********************************************/
	//cout << "Debut du traitement sequentiel" << endl;
	// begin timer

	auto avant_seq = high_resolution_clock::now();
	
	sequentiel(init.noms_fichiers, init.couleur, init.statistique);

	auto apres_seq = high_resolution_clock::now();

	// end time
	//cout << "Fin du traitement sequentiel" << endl;

	/*********************************************
	* Fin de la zone du traitement s�quentiel
	*********************************************/

	if (output.is_open())
		output << "Temps pris pour le traitement sequentiel : "
			   << duration_cast<milliseconds>(apres_seq - avant_seq).count() 
			   << " ms" << endl;

	// afficher le temps pris pour le traitement s�quentiel

	/*********************************************
	* D�but de la zone du traitement en parall�le
	*********************************************/
	//cout << "Debut du traitement en parallele" << endl;
	// begin timer

	auto avant_para = high_resolution_clock::now();

	// Appeler la fonction de traitement parall�le

	auto apres_para = high_resolution_clock::now();

	// end time
	//cout << "Fin du traitement en parallele" << endl;
	/*********************************************
	* Fin de la zone du traitement en parall�le
	*********************************************/

	if (output.is_open())
		output << "Temps pris pour le traitement en parallele : "
		<< duration_cast<milliseconds>(apres_para - avant_para).count()
		<< " ms" << endl;

	cout << "Fin du programme" << endl;
}