

/*

const string BALISE_DEBUT = "<span >";
const string BALISE_FIN = "</span>";

const string STYLE_BLEU = "style = 'color:blue'";
const string OUVERTURE_BALISE = "<span ";
const string FERMETURE_BALISE = " >";





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






ecrire_fichier.open(*it + ".real.html");
for each (string ligne in texte_fichier)
{
ecrire_fichier << ligne << endl;
}
ecrire_fichier.close();


*/