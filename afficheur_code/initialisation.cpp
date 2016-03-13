
/*************************************************************************

Fait par Antoine Latendresse, Léa Kelly et Simon Roy

*************************************************************************/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Initialisation
{
	const string OPTION_COULEUR_CODE = "couleur";
	const string OPTION_STATISTIQUE = "stats";
	const string OPTION_TEST = "test";
	const int NBFICHIERS = 100;
	std::ostream &os;
public :
	string language_prog = "C++";
	bool couleur = false;
	bool statistique = false;
	bool test = false;
	int nb_fichiers = 0;

	vector<string> noms_fichiers;

	// Fonction utilisée pour vérifier l'existence d'un fichier
	// Ouvrir le fichier et le convertir en booléen
	bool fichier_existe(const string &nom)
	{
		return !!(ifstream{ nom });
	}

	Initialisation( int argc, char * argv[], std::ostream &os = std::cout) noexcept : os{os}
	{
		// début de la gestion des paramètres
		if (argc > 1)
		{
			// le premier paramètre est le chemin de l'exécutable (le paramètre à l'index 0)
			for (int i = 1; i < argc; i++)
			{
				string arg = argv[i];
				if (!std::empty(arg))
				{
					// Si le premier caractère est '-' ou '/'
					if (arg[0] == '-' || arg[0] == '/') // Le paramètre doit être une option
					{
						if (arg.substr(1) == OPTION_COULEUR_CODE)
						{
							couleur = true;
						}
						else if (arg.substr(1) == OPTION_STATISTIQUE)
						{
							statistique = true;
						}
						else if (arg.substr(1) == OPTION_TEST)
						{
							test = true;
						}
						else
						{
							os << "L'option : " << arg << " n'est pas valide pour ce programme." << endl;
						}
					}
					// Si le paramètre n'est pas une option
					else // alors c'est un nom de fichier
					{
						nb_fichiers++;
						// Si le fichier existe alors on l'ajoute dans notre liste de fichiers à traiter.
						if (fichier_existe(arg))
						{
							// Si l'option test est passée en paramètre lors de l'exécution, alors on met
							// plusieurs fois le même fichier selon le nombre de la constante
							if (test)
							{
								for (int i = 0; i < NBFICHIERS; ++i)
									noms_fichiers.push_back(arg);
							}
							// Sinon on ne le met qu'une fois
							else
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
		// fin de la gestion des paramètres
	}

};
