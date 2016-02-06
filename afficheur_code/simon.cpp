

/*

const string BALISE_DEBUT = "<span >";
const string BALISE_FIN = "</span>";

const string STYLE_BLEU = "style = 'color:blue'";
const string OUVERTURE_BALISE = "<span ";
const string FERMETURE_BALISE = " >";




int index;
for each (string keyword in liste)
{
for (int i = 0; i < texte_fichier.size(); i++)
{
index = 0;
while (index == string::npos)
{
index = texte_fichier[i].find(keyword, index);
if ( index != string::npos)
{


texte_fichier[i].replace(index, keyword.length(), OUVERTURE_BALISE + STYLE_BLEU + FERMETURE_BALISE + keyword + BALISE_FIN);
index += OUVERTURE_BALISE.length() + STYLE_BLEU.length(); +FERMETURE_BALISE.length() + keyword.length() + BALISE_FIN.length();
						}
					}
				}
			}

ecrire_fichier.open(*it + ".real.html");
for each (string ligne in texte_fichier)
{
ecrire_fichier << ligne << endl;
}
ecrire_fichier.close();


*/