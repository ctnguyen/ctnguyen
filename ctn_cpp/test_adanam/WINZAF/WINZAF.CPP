
#include <stdio.h>
#include <conio.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define ASCI_C   255
#define LENGTH  1024
#define FIN_FICHIER    0x1A
#define NBR_C        65
#define LEN_C       6
char NomSource[60];
char NomCible[60] = "";
char Nom[60];
char newname[60];
int argc =0;
char *argv[2];
char *rang,*ranj,*EXT;
char temp[60];
typedef enum { false, true} Boolean;


typedef struct S_Feuille
{
	Boolean Noeud;      /*  vrai = noeud, faux = feuille */
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
	 Paper Donnee;  /* donn‚e ou noeud pour calculer l'arbre */
	 char Code[NBR_C];     /* code trouve pour le caractere         */
	 Boolean Codifie;    /* true = codification existante         */
	 } Tab_ASCII;

int DimAscii = 0;    /* nombre de caracteres differents */
long TotalOctet = 0; /* nombre d'octets lus du fichier initial */
Noeud *PtrNoeud;   /* ptr noeud pour construire l'arbre */
Noeud *Racine;     /* racine de l'arbre */

/***********************************************************************************/
/* MAJ_TB  : mise a zero de la table servant cumuler les frequences des caracteres */
/***********************************************************************************/

void MAJ_TB( Ptr_Ascii)
Tab_ASCII * Ptr_Ascii;
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

void Change(a,b)
Tab_ASCII *a, *b;
{
   Tab_ASCII temp;
   temp = *a;
   *a = *b;
   *b = temp;
}
/*********************************************************************/
/* TriTab : Trie la table ASCII des frequences par  ordre decroissant*/
/*********************************************************************/

void TriTab( Ptr_Ascii)
Tab_ASCII *Ptr_Ascii;
{
   Boolean Permut = true;
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

void NbrFr(f, Ptr_Ascii)
FILE *f;
Tab_ASCII *Ptr_Ascii;
{
    int NbreCaract;
    int i;
    unsigned char Buffer[LENGTH];

	 MAJ_TB(Ptr_Ascii);      /* mise … 0 de la table ascii */

    do
    {
       NbreCaract = fread(Buffer, 1, LENGTH, f);
       if (NbreCaract > 0)
       {
	/* on ne tient pas compte du caract. de fin de fichier */

       /*calcul des nombres d'aparition des caractŠres */

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

void Cre_Tree(Ptr_Ascii)
Tab_ASCII * Ptr_Ascii;
{
    Tab_ASCII Temp;                /* variable temporaire */
    int i, j, ind;
    Boolean Insertion;

   /* creation de l'arbre permettant d'elaborer les codes */
    for ( i = DimAscii-1; i > 0; i--)
    {
		 PtrNoeud = ((Noeud *) malloc(sizeof(Noeud)));
       if (PtrNoeud == NULL)
       {
	  printf("Pas assez de m‚moire !!!\n");
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

void Cre_Cod(Ptr_Ascii, Ptr)
Tab_ASCII *Ptr_Ascii;
Noeud * Ptr;
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

void Wr_Tb(f, Ptr_Ascii)
FILE *f;
Tab_ASCII *Ptr_Ascii;
{
   unsigned char Bit_A_1[8] = {128, 64, 32, 16, 8, 4, 2, 1};

   int i, j;
   unsigned char *Ptr_Code;  /* table interm‚diaire avant ecriture */
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

void Cop_Data(FSource, FCible, Ptr_Ascii)
FILE *FSource, *FCible;
Tab_ASCII *Ptr_Ascii;
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
		fwrite(rang,sizeof(char [10]),1,FCible);
}

/*************************************************************************/
/* Compression : Mise en place du programme de compression*/
/*************************************************************************/

void Compression(FSource, FCible)
FILE *FSource, *FCible;
{
	 Tab_ASCII ASCII[ASCI_C+1]; /* table des fr‚q des codes ASCII lus */

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
void Cre_Tr_Dec(FSource)
FILE *FSource;
{
    unsigned char *Ptr_Code;  /* table interm‚diaire avant ecriture */
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
/* Dec_Data : Decompresse les donn‚es en parcourant l'arbre.*/
/************************************************************/

void Dec_Data(FSource, FCible)
FILE *FSource, *FCible;
{
    unsigned char Buffer_Lect[LENGTH];
    unsigned char Buffer_Ecri[LENGTH];
	 char Bit_A_1[8] = {128, 64, 32, 16, 8, 4, 2, 1};
    int NbreCaract, i, C_A_Ecrire = 0;
    char Cpt = 0;
    Noeud *Ptr;
	 Boolean FinDecomp = false;

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
		  /* ecriture des donn‚es par bloc */
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
		  /* ecrire des donn‚es par bloc */
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

void Decompression(FSource, FCible)
FILE *FSource, *FCible;
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
   /* decoder les caracteres un … un.                        */
	  Cre_Tr_Dec(FSource);

   /* decodage de chaque caractere */
	  Dec_Data(FSource, FCible);
}

/********************************************************/
/* error : Affichage de la syntaxe d'appel du programme.*/
/********************************************************/

void error(int ero)
{
textattr(132+(0 << 4));
switch (ero)
 {
case 1:
cprintf(" \r\nErreur d'ouverture!\r\n");
textattr(2+0);
cprintf("       le fichier '%s' que vous avez saisie soit:\r\n\n", NomSource);
cprintf("               * N'existe pas\r\n");
cprintf("               * Ou le chemin d'acc‚s est faux\r\n");
	break;
case 2:
cprintf(" \r\nERREUR:");
cprintf("\r\n        Vous avez depasser l'espace memoire\r\n");
	break;
case 3:
cprintf(" \r\nERREUR:");
cprintf("\r\n        Vous devez choisir une operation a effectuer\r\n");
	break;
case 4:
cprintf(" \r\nERREUR:");
cprintf("\r\n        Vous devez saisir le fichier a traiter\r\n");
	break;
}
printf(" \nPOUR CONTINUER FRAPPER UNE TOUCHE...");
 getch();
}

/*********************************************************/
/* compres : Affichage de la syntaxe d'appel du programme*/
/*********************************************************/

 int compres(char *t)
 {
 int i=0,cancel=0,j=0,x=0;
 FILE *fSource;
 textattr(15+(0 << 4));
		cprintf("ENTRER LE FICHIER A %sCOMPRESSER : \r\n", t);
		 for(i=0;i<60;i++)
		  {
		  cancel=getch();
			switch(cancel)
		  {
			 case 27:return(cancel);
			 case 8:
			 if (i==0)
			 i--;
			 else
			 {
			 NomSource[i-1]='\0';
			 (i-=2);
			 printf("%c",cancel);
			 printf("%c",32);
			 gotoxy(wherex()-1,wherey());
			 }
						break;
			 case 0: (i-=2);
						break;
			 case 13:
				  i=60;
						break;
			 default:
			 if ( ((isalnum((char)cancel)) || (ispunct((char)cancel))) && (x==0) )
			 {
				  printf("%c",cancel);
				  NomSource[i]=(char)cancel;
			 }
		  }
	if (cancel==0) x=1;
		  else x=0;
		 if(i==59)
		 {
		 error(2);
		 return(27);
		 }
		 }
		  for (i=0;i<60; i++)
		 if (NomSource[i]!= '\0') j=1;
		 if (j==0)
		 {
		  error(4);
		  return(27);
		 }
		 fSource = fopen(NomSource, "rb");       /* ouverture en lecture */

		 if (fSource == NULL)
		{
		error(1);
		  return(27);
		}
		 fclose(fSource);
		 textattr(15+0);
		 x=0;
		 cprintf("\r\nENTRER LE NOM DU FICHIER CIBLE (facultatif) : \r\n");
		 argc=0;
		 for(i=0;i<60;i++)
		  {
		  cancel=getch();
			switch(cancel)
		  {
		 case 27: return(cancel);
		 case 8:
		       if (i==0)
			 i--;
			 else
			 {
			 NomCible[i-1]='\0';
			 (i-=2);
			 printf("%c",cancel);
			 printf("%c",32);
			 gotoxy(wherex()-1,wherey());
			 }
				break;
		 case 0: (i-=2);
				break;
		 case 13:
			  i=60;
				break;
		 default:
		 if ( ((isalnum((char)cancel)) || (ispunct((char)cancel))) && (x==0) )
		 {
			  printf("%c",cancel);
			  NomCible[i]=(char)cancel;
		  }
		  }
	if (cancel==0) x=1;
		  else x=0;
		 if(i==59)
		 {
		 error(2);
		 return(27);
		 }
		 }
		 for (i=0;i<60; i++)
		 if (NomCible[i]!= '\0')
		 argc=1;
		 printf("\n");
		return(0);
  }

			  /* --------------------------------------------------- */
			  /*         P R O G R A M M E   P R I N C I P A L       */
			  /*---------------------------------------------------- */
void main(void)
{

	 FILE *fSource, *fCible;
	 char *ExtensionC = ".ZAF";
	 char *ExtensionD = ".$$$";
	 char *dec = "DE";
	 char choix,x,choi,r;
	 char ty[3];
	 int nb=0,i=0;
	 rang=(char *)malloc(10);
	 ranj=(char *)malloc(10);
	 EXT=(char *)malloc(10);
prog:

  do
{
	textcolor(WHITE);
	textbackground(BLACK);
	ranj=NULL;
	rang=NULL;
   
		strcpy(NomCible,"");
		strcpy(NomSource,"");
		strcpy(newname,"");
		strcpy(Nom,"");
		strcpy(temp,"");

	clrscr();
	textattr(2+(2 << 4));
		 cprintf("--------------------------------------------------------------------------------\r\n");
	textattr(3+0);
		 cprintf("                           |COMPRESSION DE FICHIER|\r\n");
	textattr(131+0);
		 cprintf("                           |======================|                             \r\n\n");
	textattr(14+0);
		 cprintf("*  POUR COMPRESSER TAPER        --> 'C'\r\n");
		 cprintf("*  POUR DECOMPRESSER TAPER      --> 'D'\r\n");
		 cprintf("*  POUR QUITTER TAPER           --> 'Q'\r\n\n");
	textattr(4+0);
		 cprintf("                                            *  POUR ANNULER TAPER --> 'Esc' *\r\n");
	textattr(2+(2 << 4));
		 cprintf("--------------------------------------------------------------------------------\r\n");
	textcolor(WHITE);
	textbackground(BLACK);
	printf("\nVEUILLEZ DONNER VOTRE CHOIX:");
	choix=(char)getche();
	printf("\n");
	x=toupper(choix);
	flushall();
	switch(x)
	{
		case 'C' :
		  ty[0]= '\0';
		  if (compres(ty)==27)
		  goto prog;
			break;
		case 'D' :
			strcpy(ty, dec);
			if (compres(ty)==27)
			goto prog;
			break;
		case 'Q':
				 break;
		default :
			error(3);
			goto prog;
			break;

   }
		if (x!='Q')
		{

	/* ouverture du fichier source */
	  fSource = fopen(NomSource, "rb");       /* ouverture en lecture */

	/* ouverture du fichier cible */
	 if (argc == 0)
    {


	rang = strchr(NomSource, '.');
	if ( rang == NULL)                /* recuperation sans extension */
		strcpy(NomCible, NomSource);
	else
		nb=(int)(rang-NomSource);
		strncpy(NomCible, NomSource, nb);
	if (x == 'D')
	{
		strcpy(newname,NomCible);
		strcat(NomCible, ExtensionD);
	}
	else
		strcat(NomCible, ExtensionC);
	 }


	 else
	 {
	 ranj = strchr(NomCible, '.');
	 rang = strchr(NomSource, '.');

	 if (x == 'C')
	  {
	 if  (ranj == NULL) strcat(NomCible, ExtensionC);
	 if ((ranj != ExtensionC) && (ranj != NULL))
	      {
		  nb=(int)(ranj-NomCible);
		  strncpy(Nom,NomCible,nb);
		  strcpy(NomCible, Nom);
		  strcat(NomCible, ExtensionC);
	      }
	   }
	  else
	  {
	    if  (ranj == NULL)
	    {
	     strcpy(newname,NomCible);
	     strcat(NomCible, ExtensionD);
	    }
	    if ((ranj != ExtensionD) && (ranj != NULL))
	      {
		  nb=(int)(ranj-NomCible);
		  strncpy(Nom,NomCible,nb);
		  strcpy(NomCible, Nom);
		  strcpy(newname,NomCible);
		  strcat(NomCible, ExtensionD);
	      }
	  }
	 }

	 fCible = fopen(NomCible, "wb");  /* ouverture en ecriture */
	 if (fCible == NULL)
	 {
	textattr(132+0);
       cprintf("Erreur d'ouverture pour le fichier cible: %s\r\n", NomCible);
	fclose(fSource);
	goto prog;
    }

	 textcolor(15+128);
	 cprintf("\r\nVeuillez patientez...\r\n");
	 switch (x)
	 {
	case 'C' : Compression(fSource, fCible);
			break;
	case 'D' : Decompression(fSource, fCible);
		   break;
    }
	 fclose(fSource);
	 fclose(fCible);
		 /*renomer le fichier par sa vraix extension*/
	 if (x == 'D')
	 {
	  remove(temp);
	  strcat(newname,EXT);
	  rename(NomCible, newname);
	 }
	 }
}
while((choix!='Q')&&(choix!='q'));
					 textattr(9+0);
					 cprintf("\nEtes vous sure de vouloir quitter?  (O/N):");
					 choi=(char)getche();
					 r= toupper(choi);
					 cprintf("\n");
					 flushall();
					 if (r=='O')
					 {
					 textattr(140+0);
					 cprintf("\r\n\n\n                             \t\tMERCI ET AU REVOIR\t\t                             \r");
			       cprintf("                             \t\t==================\t\t                             ");
			       exit(0);
					 }
					 else
					 goto prog;

}

