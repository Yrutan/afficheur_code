
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;




class Initialisation
{
	const string OPTION_COULEUR_CODE = "couleur";
	const string OPTION_STATISTIQUE = "stats";
	std::ostream &os;
public :
	string language_prog = "C++";
	bool couleur = false;
	bool statistique = false;
	int nb_fichiers = 0;

	vector<string> noms_fichiers;

	// Fonction utilis�e pour v�rifier l'existence d'un fichier
	// Ouvrir le fichier et le convertir en bool�en
	bool fichier_existe(const string &nom)
	{
		return !!(ifstream{ nom });
	}

	Initialisation( int argc, char * argv[], std::ostream &os = std::cout) noexcept : os{os}
	{
		// d�but de la gestion des paran�tres
		if (argc > 1)
		{
			// le premier param�tre est le chemin de l'ex�cutable (le param�tre � l'index 0)
			for (int i = 1; i < argc; i++)
			{
				string arg = argv[i];
				if (!std::empty(arg))
				{
					// Si le premier caract�re est '-' ou '/'
					if (arg[0] == '-' || arg[0] == '/') // Le param�tre doit �tre une option
					{
						if (arg.substr(1) == OPTION_COULEUR_CODE)
						{
							couleur = true;
						}
						else if (arg.substr(1) == OPTION_STATISTIQUE)
						{
							statistique = true;
						}
						else
						{
							os << "L'option : " << arg << " n'est pas valide pour ce programme." << endl;
						}
					}
					// Si le param�tre n'est pas une option
					else // alors c'est un nom de fichier
					{
						nb_fichiers++;
						if (fichier_existe(arg))
						{
							// Si le fichier existe alors on l'ajoute dans notre liste de fichiers � traiter.
							noms_fichiers.push_back(arg);
						}
						else
						{
							os << "Le fichier " << arg << " n'existe pas !" << endl;
						}
					}
				}
			}
		}
		// fin de la gestion des paran�tres
	}

};
