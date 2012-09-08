
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#define ASCI_C   255
#define LENGTH  1024
#define FIN_FICHIER    0x1A
#define NBR_C        65
#define LEN_C       6
char newname[60];
char *rang,*ranj,*EXT;
char temp[60];
//typedef enum { false, true} bool;

typedef struct S_Feuille
{
	bool Noeud;      /*  vrai = noeud, faux = feuille */
	union
	{
		unsigned char Data;    /* donnee d'une feuille   */
		struct S_Noeud * Ptr;  /* ptr sur un autre noeud */
	} U_Feuille;
} Paper;

/* definition d'un noeud de l'arbre */
typedef struct S_Noeud
{
	Paper FDroite;
	Paper FGauche;
	char CodeNoeud[NBR_C];        /* codage jusqu'au noeud */
} Noeud;

typedef struct  {
	long  Cumul;        /* frequence d'apparition des caracteres */
	Paper Donnee;  /* donn�e ou noeud pour calculer l'arbre */
	char Code[NBR_C];     /* code trouve pour le caractere         */
	bool Codifie;    /* true = codification existante         */
} Tab_ASCII;

int DimAscii = 0;    /* nombre de caracteres differents */
long TotalOctet = 0; /* nombre d'octets lus du fichier initial */
Noeud *PtrNoeud;   /* ptr noeud pour construire l'arbre */
Noeud *Racine;     /* racine de l'arbre */

/***********************************************************************************/
/* MAJ_TB  : mise a zero de la table servant cumuler les frequences des caracteres */
/***********************************************************************************/

void MAJ_TB( Tab_ASCII * Ptr_Ascii)
//Tab_ASCII * Ptr_Ascii;
{
	int i;
	for( i = 0; i <= ASCI_C ; i++)
	{
		(Ptr_Ascii+i)->Cumul = 0;
		(Ptr_Ascii+i)->Donnee.U_Feuille.Data = i;
		(Ptr_Ascii+i)->Codifie = false;
		(Ptr_Ascii+i)->Donnee.Noeud = false;
		strcpy ( (Ptr_Ascii+i)->Code, "");
	}

}

/**************************************************/
/* Change : Permute 2 cellules de la table ASCII. */
/**************************************************/

void Change(Tab_ASCII *a,Tab_ASCII *b)
//Tab_ASCII *a, *b;
{
	Tab_ASCII _buffer;
	_buffer = *a;
	*a = *b;
	*b = _buffer;
}
/*********************************************************************/
/* TriTab : Trie la table ASCII des frequences par  ordre decroissant*/
/*********************************************************************/

void TriTab( Tab_ASCII *Ptr_Ascii)
//Tab_ASCII *Ptr_Ascii;
{
	bool Permut = true;
	unsigned char Debut = 0;
	unsigned char LastPermut = Debut;
	short i;

	while(Permut)
	{
		for( Permut=false, i=ASCI_C; i > Debut; i--)
			if ((Ptr_Ascii+i)->Cumul > (Ptr_Ascii+i-1)->Cumul)
			{
				Change((Ptr_Ascii+i), (Ptr_Ascii+i-1));
				Permut = true;
				LastPermut = (unsigned char) i;
			}
		Debut = LastPermut;
	}
}

/******************************************************************************/
/* NbrFr : Cumul des frequences d'apparition des caracteres du fichier source */
/******************************************************************************/

void NbrFr(FILE *f, Tab_ASCII *Ptr_Ascii)
//FILE *f;
//Tab_ASCII *Ptr_Ascii;
{
	int NbreCaract;
	int i;
	unsigned char Buffer[LENGTH];

	MAJ_TB(Ptr_Ascii);      /* mise � 0 de la table ascii */

	do
	{
		NbreCaract = fread(Buffer, 1, LENGTH, f);
		if (NbreCaract > 0)
		{
			/* on ne tient pas compte du caract. de fin de fichier */

			/*calcul des nombres d'aparition des caract�res */

			for(i = 0; i < NbreCaract; i++)
			{
				if (!((Ptr_Ascii+Buffer[i])->Cumul)) DimAscii++;
				(Ptr_Ascii+Buffer[i])->Cumul ++;
			}
			TotalOctet += NbreCaract;
		}

	}
	while (NbreCaract > 0);

	/*  triage de la table ascii */

	TriTab(Ptr_Ascii);
}

/**************************************************************/
/* Cre_Tree : Construction de l'arbre pour elaborer les codes */
/**************************************************************/

void Cre_Tree(Tab_ASCII *Ptr_Ascii)
//Tab_ASCII * Ptr_Ascii;
{
	Tab_ASCII Temp;                /* variable temporaire */
	int i, j, ind;
	bool Insertion;

	/* creation de l'arbre permettant d'elaborer les codes */
	for ( i = DimAscii-1; i > 0; i--)
	{
		PtrNoeud = ((Noeud *) malloc(sizeof(Noeud)));
		if (PtrNoeud == NULL)
		{
			printf("Pas assez de m�moire !!!\n");
			exit(0);
		}

		/* mise a jour de la partie droite : cad la plus petite frequence */
		PtrNoeud->FDroite = (Ptr_Ascii+i)->Donnee;

		/* mise a jour de la partie gauche : cad la 2e frequence */
		PtrNoeud->FGauche = (Ptr_Ascii+i-1)->Donnee;

		/* calcul du cumul des donnees */
		Temp.Cumul = (Ptr_Ascii+i)->Cumul + (Ptr_Ascii+i-1)->Cumul;
		Temp.Donnee.Noeud = true;   /* c'est un noeud et non une feuille */
		Temp.Donnee.U_Feuille.Ptr = PtrNoeud;

		/* reclassement du noeud dans la table */
		for (j=i, Insertion=false; (j>0) && (!(Insertion)); j--)
			if ((Ptr_Ascii+j-1)->Cumul < Temp.Cumul)
				*(Ptr_Ascii+j) = *(Ptr_Ascii+j-1);
			else
			{
				Insertion = true;
				ind = j;
			}

		if (!(Insertion))  ind = 0;
		*(Ptr_Ascii+ind) = Temp;
	}
	Racine = PtrNoeud;
}

/***************************************************************************/
/* Cre_Cod : Parcours de l'arbre, et elaboration du codage. Module recursif*/
/***************************************************************************/

void Cre_Cod(Tab_ASCII *Ptr_Ascii, Noeud *Ptr)
//Tab_ASCII *Ptr_Ascii;
//Noeud * Ptr;
{
	char code[NBR_C];

	/* exploration de la partie droite du pointeur */
	strcpy(code,Ptr->CodeNoeud);
	strcat(code, "1");
	if ((Ptr->FDroite).Noeud)
	{
		strcpy((Ptr->FDroite).U_Feuille.Ptr->CodeNoeud,code);
		Cre_Cod(Ptr_Ascii, (Ptr->FDroite).U_Feuille.Ptr);
	}
	else
	{
		strcpy((Ptr_Ascii+(Ptr->FDroite).U_Feuille.Data)->Code, code);
		(Ptr_Ascii+(Ptr->FDroite).U_Feuille.Data)->Codifie = true;
	}

	/* exploration de la partie gauche du pointeur */
	strcpy(code,Ptr->CodeNoeud);
	strcat(code,"0");
	if ((Ptr->FGauche).Noeud)
	{
		strcpy(((Ptr->FGauche).U_Feuille.Ptr)->CodeNoeud, code);
		Cre_Cod(Ptr_Ascii, (Ptr->FGauche).U_Feuille.Ptr);
	}
	else
	{
		strcpy((Ptr_Ascii+(Ptr->FGauche).U_Feuille.Data)->Code, code);
		(Ptr_Ascii+(Ptr->FGauche).U_Feuille.Data)->Codifie = true;
	}
}

/***********************************************************************/
/* Wr_Tb : Ecriture de la table de correspondance dans le fichier cible*/
/***********************************************************************/

void Wr_Tb(FILE *f, Tab_ASCII *Ptr_Ascii)
//FILE *f;
//Tab_ASCII *Ptr_Ascii;
{
	unsigned char Bit_A_1[8] = {128, 64, 32, 16, 8, 4, 2, 1};

	int i, j;
	unsigned char *Ptr_Code;  /* table interm�diaire avant ecriture */
	int Cpt_Car = 0;          /* compteur de caracteres pour Ptr_Code */
	unsigned char Octet;
	unsigned char Cpt;               /* compteur de bits positionnes */
	char NbOctet = 0;

	/* on ecrit d'abord le nombre de caracteres */
	/* envoyer dans la table                    */
	fwrite(&DimAscii, sizeof(int), 1, f);

	/* reservation de la place memoire pour ecrire la table de codage */
	/* surdimensionnement avec 4 octets par caractere code.           */
	Ptr_Code = (unsigned char *) malloc(4 * DimAscii);

	/* envoi de chaque caractere sur 3 octets :                   */
	/*   - le 1er etant le caractere a convertir,                 */
	/*   - LEN_C bits du 2e : nombre de bits utiles pour le    */
	/*                     codage (maximum 16 bits),              */
	/*   - 8-LEN_C bits du 2e + eventuellement 3e octet+etc..  */
	/*                   : codage du caractere.                   */
	for(i = 0; i<=ASCI_C;i++)
		if ((Ptr_Ascii+i)->Codifie==true)
		{
			/* mise en table du caractere a coder */
			*(Ptr_Code+Cpt_Car) = (unsigned char) i;

			/* mise en table de la longueur du codage en DCB */
			Octet = strlen((Ptr_Ascii+i)->Code);
			Octet <<= (8-LEN_C);          /* decalage de 4 positions */
			Cpt = LEN_C;
			NbOctet = 1;       /* nombre d'octets servant a la codification */

			for (j=0; j<strlen((Ptr_Ascii+i)->Code); j++)
			{
				if (Cpt == 8)
				{
					*(Ptr_Code+Cpt_Car+NbOctet++) = Octet;
					Octet  = Cpt = 0;
				}
				if ((Ptr_Ascii+i)->Code[j] == '1')
				{
					Octet |= Bit_A_1[Cpt];
				}
				Cpt++;
			}
			*(Ptr_Code+Cpt_Car+NbOctet) = Octet;
			Cpt_Car += NbOctet+1;
		}

	/* ecriture de toute la table */
	fwrite(&Cpt_Car, sizeof(Cpt_Car), 1, f);
	fwrite(Ptr_Code, 1, Cpt_Car, f);
	free(Ptr_Code);             /* liberation de la place memoire */

	/* ecriture du nombre total d'octets */
	fwrite(&TotalOctet, sizeof(TotalOctet), 1, f);
}

/***************************************************************************/
/* Cop_Data : Ecriture des donnees caractere par caractere dans le fichier.*/
/***************************************************************************/

void Cop_Data(FILE *FSource,FILE *FCible, Tab_ASCII *Ptr_Ascii)
//FILE *FSource, *FCible;
//Tab_ASCII *Ptr_Ascii;
{
	int NbreCaract;
	int i, l;
	unsigned char Octet = 0, Cpt = 0;
	unsigned char Buffer_Lect[LENGTH];
	unsigned char Buffer_Ecri[LENGTH];
	unsigned char Bit_A_1[8] = {128, 64, 32, 16, 8, 4, 2, 1};
	int C_A_Ecrire = 0;

	fseek(FSource, 0L, SEEK_SET);/* repositionnement en debut de fichier */
	do
	{
		/* lecture en bloc des donnees */
		NbreCaract = fread(Buffer_Lect, 1, LENGTH, FSource);
		if (NbreCaract > 0)
		{

			for(i = 0; i < NbreCaract; i++)
			{
				for (l = 0; l<strlen((Ptr_Ascii+Buffer_Lect[i])->Code);l++)
				{
					if ((Ptr_Ascii+Buffer_Lect[i])->Code[l] == '1')
						Octet |= Bit_A_1[Cpt];
					Cpt++;
					if (Cpt == 8)
					{
						Buffer_Ecri[C_A_Ecrire++] = Octet;
						Octet = Cpt = 0;
						if (C_A_Ecrire == LENGTH)
						{
							fwrite(Buffer_Ecri, 1, LENGTH, FCible);
							C_A_Ecrire = 0;
						}
					}
				}
			}
		}
	}
	while (NbreCaract > 0);

	/* ecriture de la fin du buffer */
	Buffer_Ecri[C_A_Ecrire++] = Octet;    /* sauvegarde du dernier octet */
	fwrite(Buffer_Ecri, 1, C_A_Ecrire, FCible);

	/* Stokage de l'extension du fichier a compresser*/
	fseek(FCible, 0L, SEEK_END);
	std::cout<<"here 1"<<std::endl;
	fwrite(rang,sizeof(char [10]),1,FCible);
	std::cout<<"here 2"<<std::endl;
}

/*************************************************************************/
/* Compression : Mise en place du programme de compression*/
/*************************************************************************/

void Compression(FILE *FSource, FILE *FCible)
//FILE *FSource, *FCible;
{
	Tab_ASCII ASCII[ASCI_C+1]; /* table des fr�q des codes ASCII lus */

	/* lecture fichier source et calcul des frequences d'apparition */
	NbrFr(FSource, ASCII);

	/* creation de l'arbre */
	Cre_Tree(ASCII);

	/* lecture de l'arbre => creation du codage */
	strcpy(Racine->CodeNoeud,"");
	Cre_Cod(ASCII, Racine);

	/* ecriture de la table de correspondance dans le fichier */
	Wr_Tb(FCible, ASCII);

	/* ecriture des donnees dans le fichier cible */
	Cop_Data(FSource, FCible, ASCII);
}

/*******************************************************************/
/* Cre_Tr_Dec : Reconstitution de l'arbre pour decoder les donnees.*/
/*******************************************************************/
void Cre_Tr_Dec(FILE *FSource)
//FILE *FSource;
{
	unsigned char *Ptr_Code;  /* table interm�diaire avant ecriture */
	int Cpt_Car = 0;          /* compteur de caracteres pour Ptr_Code */
	int Max_Car;              /* maximum de car. dans la table        */
	char Bit_A_1[8] = {128, 64, 32, 16, 8, 4, 2, 1};
	char Code[NBR_C], Nb;
	char Cpt, l;//, n;        /* nombre de bits formant le code */
	unsigned char Octet, NbBit;
	Noeud *Ptr, *p;
	char NbOctet = 0;         /* nombre d'octets a lire pour le decodage */

	/* initialisation de la racine de l'arbre */
	Racine = (Noeud *) malloc(sizeof(Noeud));
	Racine->FDroite.U_Feuille.Ptr = NULL;
	Racine->FGauche.U_Feuille.Ptr = NULL;

	/* lecture du nombre de caracteres du fichier initial a reconstituer */
	fread(&DimAscii, sizeof(DimAscii), 1, FSource);

	/* lecture du nombre de caracteres de la table de conversion */
	fread(&Cpt_Car, sizeof(Cpt_Car), 1, FSource);
	Ptr_Code = (unsigned char *) malloc(Cpt_Car);
	fread(Ptr_Code, 1, Cpt_Car, FSource);
	Max_Car = Cpt_Car;
	Cpt_Car = 0;

	for (Nb = 0; (Nb < DimAscii) && (Cpt_Car < Max_Car); Nb++)
	{
		Octet = *(Ptr_Code+Cpt_Car+1);
		NbBit = Octet >> (8-LEN_C);               /* longueur du codage */
		Cpt = LEN_C;
		NbOctet = 1;
		strcpy(Code, "");          /* initialisation de la chaine */

		/* reconstitution de la chaine de codage */
		for(l = 0; l<NbBit; l++)
		{
			if (Cpt == 8)
			{
				Octet = *(Ptr_Code+Cpt_Car+(++NbOctet));
				Cpt = 0;
			}
			if (Octet & Bit_A_1[Cpt]) strcat(Code,"1");
			else strcat(Code,"0");
			Cpt++;
		}
		Ptr = Racine;

		for (l = 0; l < NbBit; l++)
		{
			/* creation d'une feuille droite */
			if (Code[l] == '1')
				/* dernier bit a coder, il faut y mettre la feuille */
				if (l == NbBit-1)
				{
					Ptr->FDroite.U_Feuille.Data = *(Ptr_Code+Cpt_Car);
					Ptr->FDroite.Noeud = false;
				}
				else
					/* c'est encore un noeud */
					if ((Ptr->FDroite).U_Feuille.Ptr == NULL) /* noeud inexistant */
					{
						p = (Noeud *) malloc(sizeof(Noeud));
						Ptr->FDroite.U_Feuille.Ptr = p;   /* lien avec fils droit */
						Ptr->FDroite.Noeud = true;
						p->FDroite.U_Feuille.Ptr = NULL;
						p->FGauche.U_Feuille.Ptr = NULL;
						Ptr = p;
					}
					else Ptr = Ptr->FDroite.U_Feuille.Ptr;

			/* creation d'une feuille gauche */
			else
				/* dernier bit a coder, il faut y mettre la feuille */
				if (l == NbBit-1)
				{
					Ptr->FGauche.U_Feuille.Data = *(Ptr_Code+Cpt_Car);
					Ptr->FGauche.Noeud = false;
				}
				else
					/* c'est encore un noeud */
					if ((Ptr->FGauche).U_Feuille.Ptr == NULL) /* noeud inexistant */
					{
						p = (Noeud *) malloc(sizeof(Noeud));
						Ptr->FGauche.U_Feuille.Ptr = p;   /* lien avec fils gauche */
						Ptr->FGauche.Noeud = true;
						p->FDroite.U_Feuille.Ptr = NULL;
						p->FGauche.U_Feuille.Ptr = NULL;
						Ptr = p;
					}
					else Ptr = Ptr->FGauche.U_Feuille.Ptr;

		}
		Cpt_Car += NbOctet+1;
	}
	free(Ptr_Code);     /* liberation de la place memoire */

	/* lecture du nombre total d'octets compresses */
	fread(&TotalOctet, sizeof(TotalOctet), 1, FSource);
}

/************************************************************/
/* Dec_Data : Decompresse les donn�es en parcourant l'arbre.*/
/************************************************************/

void Dec_Data(FILE *FSource, FILE *FCible)
//FILE *FSource, *FCible;
{
	unsigned char Buffer_Lect[LENGTH];
	unsigned char Buffer_Ecri[LENGTH];
	char Bit_A_1[8] = {128, 64, 32, 16, 8, 4, 2, 1};
	int NbreCaract, i, C_A_Ecrire = 0;
	char Cpt = 0;
	Noeud *Ptr;
	bool FinDecomp = false;

	Ptr = Racine;

	do
	{
		/* lecture en bloc des donnees */
		NbreCaract = fread(Buffer_Lect, 1, LENGTH, FSource);
		if (NbreCaract > 0)

			/* pour tous les caracteres du buffer */
			for(i = 0; i < NbreCaract; i++)

				/* pour tous les bits de chaque caractere */
				for(Cpt = 0; Cpt < 8; Cpt++)
				{
					/* s'il y a mathematiquement d'autres octets */
					if (FinDecomp) continue;

					/* test si feuille droite */
					if (Buffer_Lect[i] & Bit_A_1[Cpt])

						/* si c'est un pointeur sur un autre noeud */
						if ((Ptr->FDroite).Noeud) Ptr = (Ptr->FDroite).U_Feuille.Ptr;

					/* c'est une feuille terminale donc un caractere */
						else
						{
							/* ecriture des donn�es par bloc */
							Buffer_Ecri[C_A_Ecrire++] = (Ptr->FDroite).U_Feuille.Data;
							if (C_A_Ecrire == LENGTH)
							{
								fwrite(Buffer_Ecri, LENGTH, 1, FCible);
								C_A_Ecrire = 0;
							}
							if (!(--TotalOctet)) FinDecomp = true;
							Ptr = Racine;
						}

					/* test si feuille gauche */
					else
						/* si c'est un pointeur sur un autre noeud */
						if ((Ptr->FGauche).Noeud) Ptr = (Ptr->FGauche).U_Feuille.Ptr;

					/* c'est une feuille terminale donc un caractere */
						else
						{
							/* ecrire des donn�es par bloc */
							Buffer_Ecri[C_A_Ecrire++] = (Ptr->FGauche).U_Feuille.Data;
							if (C_A_Ecrire == LENGTH)
							{
								fwrite(Buffer_Ecri, 1, LENGTH, FCible);
								C_A_Ecrire = 0;
							}
							if (!(--TotalOctet)) FinDecomp = true;
							Ptr = Racine;
						}
				}
	}
	while (NbreCaract > 0);
	if (C_A_Ecrire) fwrite(Buffer_Ecri, 1, C_A_Ecrire, FCible);
}

/*******************************************************************************/
/* Decompression : Mise en place du programme de decompression   */
/*******************************************************************************/

void Decompression(FILE *FSource, FILE *FCible)
//FILE *FSource, *FCible;
{
	FILE *tmp;
	int w;
	long int pos;

	/*Prendre l'extension du fuchier et la supprimer*/
	strcpy(temp,newname);
	strcat(temp,".tmp");
	tmp=fopen(temp,"wb+");
	fseek(FSource, (0L)-10, SEEK_END);
	pos=ftell(FSource);
	fread(EXT,sizeof(char [10]),1,FSource);
	rewind(FSource);
	while(pos != ftell(FSource))
	{
		w=getc(FSource);
		putc(w,tmp);
	}
	fclose(FSource);
	fclose(tmp);
	FSource = fopen(temp, "rb");
	/* creation d'un arbre qui permettra en le parcourant de */
	/* decoder les caracteres un � un.                        */
	Cre_Tr_Dec(FSource);

	/* decodage de chaque caractere */
	Dec_Data(FSource, FCible);
}

/* --------------------------------------------------- */
/*         P R O G R A M M E   P R I N C I P A L       */
/*---------------------------------------------------- */
int main(int argc, char* argv[])
{
	std::cout<<"initialization global variables "<<std::endl;
	rang = (char *)malloc(10);
	ranj = (char *)malloc(10);
	EXT  = (char *)malloc(10);

	{
		std::cout<<"ARGC = "<<argc<<std::endl;
		for(int i=0;i<argc;++i)
		{
			std::cout<<" argv["<<i<<"] = "<<argv[i]<<std::endl;
		}
	}


	if((argc != 4) || (*(argv[1]) !='c' && *(argv[1]) !='d' ))
	{
		std::cout<<"ERROR command, try "<<std::endl;
		std::cout<<"./test_winsaf c sourcefile.txt destfile  #For compression "<<std::endl;
		std::cout<<"./test_winsaf d sourcefile destfile.txt  #For dcompression "<<std::endl;
		return 0;
	}

	FILE *fSource, *fCible;
	bool _isCompression=false;
	if(*(argv[1]) =='c') _isCompression = true;

	fSource = fopen(argv[2], "rb");
	fCible = fopen(argv[3], "wb");

	if(_isCompression)
	{
		Compression(fSource, fCible);
		fclose(fSource);fclose(fCible);
	}
	else//decompression
	{
		Decompression(fSource, fCible);
		fclose(fSource);fclose(fCible);
	}

	return 0;
}

