/*






const string STYLE_BLEU = "color='#6495ED'"; // #6495ED Cornflowerblue
const string BALISE_DEBUT = "<span >";
const string BALISE_OUVERTURE = "<span ";
const string BALISE_FERMETURE = " >";
const string BALISE_FIN = "</span>";


const string COULEUR_CODE = "-couleur";
const string STATISTIQUE = "-stats";

const string PLUS_PETIT = "&lt"; // <
const string PLUS_GRAND = "&gt"; // >
const string ESPERLUETTE = "&amp"; // &










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












*/