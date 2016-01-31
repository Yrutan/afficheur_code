/*************************************************************************

	Fait par Antoine Latendresse, Léa Kelly et Simon Roy

*************************************************************************/


#include <string>
#include <vector>
#include <iostream>
using namespace std;




const string COULEUR_CODE = "-couleur";
const string STATISTIQUE = "-stats";

const string DEFAULT_FILE = "default.cpp";

int main( int argc, char * argv[] )
{
	bool couleur_code = false;
	bool fichier_statistique = false;

	// le premier paramètre est le nom de l'exécutable
	string nom_programme = argv[0];

	if ( argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			string arg = argv[i];
			if ( arg[0] == '-' )
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
				// faire un vecteur pour garder une liste des 
				// noms de fichier à copier en html ?
			}
		}


	}
}