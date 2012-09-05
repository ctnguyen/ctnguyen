#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>

// Nécéssaire !!!
#include "GZipHelper.h"

void main()
{
	//*********************************************************************
	// Compression d'une chaîne de caractères en mémoire
	//*********************************************************************

	char plainText [] = "L'organisation de cooperation et de developpement economique (OCDE) a rendu publique, lundi 12  janvier, une version revisee des principes de gouvernance d'entreprise qu'elle avait elabores en 1999, afin de les soumettre a une consultation publique.  La premiere mouture de ces principes avait ete conçue a l'intention des pays emergents, en Asie du Sud-Est ou en Europe de l'Est. \"Nous n'avions jamais envisage de devoir discuter de ceci aux Etats-Unis et en Europe, a declare le directeur general de l'OCDE, Donald Johnston, dans un entretien au Wall Street Journal Europe lundi. Mais il y a a present une receptivite beaucoup plus grande a ce sujet dans les pays occidentaux.\"";

	printf("Chaine avant compression : %d\n", strlen(plainText));

	CA2GZIP gzip (plainText, strlen(plainText));	// Compression
	LPGZIP pgzip = gzip.pgzip;						// pgzip est le pointeur vers les données compressées, nous pouvons directement l'utiliser
	int len = gzip.Length;							// Longueur des données compressées

	printf("Chaine apres compression : %d\n", len);

	CGZIP2A plain (pgzip,len);						// Décompression
	char * pplain = plain.psz;						// psz est un pointeur vers les données décompressées
	int aLen = plain.Length;						// Longueur des données décompressées

	printf("Chaine apres decompression : %d\n\n", aLen);

	//*********************************************************************
	// Compression d'un fichier BMP
	//*********************************************************************

	// Remplacer CaptureEcran.bmp et CaptureEcran.bmp.gz par les noms de fichiers désiré sachant que CaptureEcran.bmp est le fichier à compresser
	FILE * ain = fopen("CaptureEcran.bmp","rb");

	fseek (ain, 0, SEEK_END);
	long size = ftell (ain);
	fseek (ain, 0, SEEK_SET);

	char * buffer = (char*) malloc (size);
	size_t count0 = fread (buffer, 1, size, ain);

	CA2GZIP gzip2 (buffer, size);					// Compression du buffer mémoire contenant les données du fichier BMP

	FILE * aout = fopen ("CaptureEcran.bmp.gz", "wb");
	size_t count1 = fwrite (gzip2.pgzip, 1, gzip2.Length, aout);
}
