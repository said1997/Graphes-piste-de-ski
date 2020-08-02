#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uvsqgraphics.h>
#define TAILLE 232

/*Etapes pour compiler 
 * ouvrez le terminal a l'interieur du dossier floyd puis tapez les commandes suivantes
 * gcc -c flyd.c  `sdl-config --cflags`
 * gcc flyd.o -o flyd -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf
 * ./flyd
 * si cela ne marche pas verifiez que vous avez la biblotheque uvsqgraphics installe
 * pour installer la bibliotheque uvsq entrez dans le dossier uvsqgraphics et ouvrez le terminal dedans et tapez "make"
 * */


//structure pour enregistrer le nom de chaque station et sa position dans la fenetre graphique (x,y)
typedef struct
{
  char nomStation[TAILLE][100];
  int cord_x[TAILLE];
  int cord_y[TAILLE];
} Station;
//structure qui aide a representer les arcs et leurs poids 
typedef struct
{
  int depart, destination;
  int temps;
} Ski;
//structure contenants le nombres d'arcs et de sommets et le type de chaque arc(rouge,vert.....) avec une matrice pour derouler notre algorithme
typedef struct
{
  int arcs;
  int sommets;
  char ***type;
  Ski *matrice;
} graph;
//fonction pour cherche une station donné en entré si elle existe on renvoie son numero de sommet
int Indice_station (Station S, graph G)
{

  char chaine[100];
  int i;
  while (1)
    {
      scanf ("%s", chaine);
      for (i = 1; i <= G.sommets; i++)
	{
	  if (strcasecmp (chaine, S.nomStation[i]) == 0)
	    return i;
	}
      printf ("station non trouvee\n");
    }



}

//fonction pour dessiner le chemin a prendre 
void dessin_chemin (Station S, graph G, int i, int j)
{
  POINT p1, p2;
  p1.x = S.cord_x[i];
  p1.y = S.cord_y[i];
  p2.x = S.cord_x[j];
  p2.y = S.cord_y[j];
  draw_line (p1, p2, bleu);


}

//fonction pour defenir si l'utilisateur est debutant ou professinnel
int debutant_professionnel ()
{
  char c;
  printf ("vous etes debutant ? (Y/N)\n");
  scanf (" %c", &c);
  while (c != 'y' && c != 'Y' && c != 'n' && c != 'N')
    {
      printf ("repondez par (Y/N)\n");
      scanf (" %c", &c);

    }
  if (c == 'y' || c == 'Y')
    return 1;
  else
    return 0;

}

//allocation d'un tableau 3d pour recharger les types d'arcs dedans (rouge,vert.....)
char *** allocation_tab_trois_dim (char ***ptr, int l, int c)
{

  char nom = 100;
  int i, j;

  ptr = malloc (l * sizeof (int *));

  for (i = 0; i < l; i++)
    ptr[i] = malloc (c * sizeof (int *));
  for (i = 0; i < l; i++)
    for (j = 0; j < c; j++)
      ptr[i][j] = malloc (nom * sizeof (char));

  return ptr;
}

//chargement des donnees a partir des fichiers
graph loadGraph (char *nomfichier)
{
  FILE *fp = fopen (nomfichier, "r");

  graph G;
  int i;
  fscanf (fp, "%d%d", &G.sommets, &G.arcs);	//lire le nombre d'arcs et de sommets 
  G.matrice = (Ski *) malloc (G.arcs * sizeof (Ski));	//reservation de memoire pour ma matrice
  G.type = allocation_tab_trois_dim (G.type, G.arcs, G.arcs);	//reservation de memoire pour les types de chemain entre deux arcs 
  char type[100];
  for (i = 0; i < G.arcs; i++)
    {
      fscanf (fp, "%d%d%d", &G.matrice[i].depart, &G.matrice[i].destination, &G.matrice[i].temps);	//lecture d'une ligne depart arrive temps 
      fgets (type, 50, fp);	//je lis le type d'arc
      strcpy (G.type[G.matrice[i].depart][G.matrice[i].destination], type);	//je copie le type d'arc dans type
      char *eff = strchr (G.type[G.matrice[i].depart][G.matrice[i].destination], '\n');	//si je lis un \n je l'enleve
      if (eff)
	*eff = 0;
    }
  fclose (fp);
  return G;
}

//lire chaque sommet et le nom qu'on lui a associe
Station
lire_nom_station ()
{
  Station S;
  char nom[200];
  int i, m, l;
  int test;
  FILE *p;
  p = fopen ("nom_station.txt", "r");

  while (test != EOF)
    {
      test = fscanf (p, "%d", &i);
      fscanf (p, "%s", nom);
      strcpy (S.nomStation[i], nom);

      char *eff = strchr (S.nomStation[i], '\n');
      if (eff)
	*eff = 0;

    }
  fclose (p);
  p = fopen ("x_y_sation.txt", "r");

  test = 0;
  while (test != EOF)
    {
      test = fscanf (p, "%d %d %d\n", &i, &l, &m);
      S.cord_x[i] = l;
      S.cord_y[i] = m;
    }
  return S;
}

//afficher les stations et leurs noms
void afficheLignes (Station S, graph G)
{
  init_graphics (1300, 710);
  fill_screen (blanc);
  int i;
  POINT p1;
  for (i = 1; i <= G.sommets; i++)
    {
      p1.x = S.cord_x[i];
      p1.y = S.cord_y[i];
      draw_fill_circle (p1, 1, vert);
      aff_pol (S.nomStation[i], 8, p1, rouge);
    }
// cette boucle pour afficher tout les arcs existant entre les sommets
  /* POINT p2;
     for(i=0;i<G.arcs;i++)
     {
     p1.x = S.cord_x[G.matrice[i].depart];
     p1.y = S.cord_y[G.matrice[i].depart];
     p2.x = S.cord_x[G.matrice[i].destination];
     p2.y = S.cord_y[G.matrice[i].destination];
     if (!strcmp(G.type[G.matrice[i].depart][G.matrice[i].destination]," rouge"))
     draw_line(p1,p2,rouge);
     else
     if (!strcmp(G.type[G.matrice[i].depart][G.matrice[i].destination]," vert"))
     draw_line(p1,p2,vert);
     else
     draw_line(p1,p2,noir);

     } */

}

//algorithme pour trouver le trajet le plus court
int floydWarshall (graph g, Station S)
{

  int tempsAret[g.sommets][g.sommets], sommetsTraitee[g.sommets][g.sommets];
  int i, j, k;
  for (i = 0; i < g.sommets; i++)
    for (j = 0; j < g.sommets; j++)
      {
	tempsAret[i][j] = SHRT_MAX;
	sommetsTraitee[i][j] = (i != j) ? j + 1 : 0;
      }

  for (i = 0; i < g.arcs; i++)
    tempsAret[g.matrice[i].depart - 1][g.matrice[i].destination - 1] =
      g.matrice[i].temps;

  for (i = 0; i < g.sommets; i++)
    for (j = 0; j < g.sommets; j++)
      for (k = 0; k < g.sommets; k++)
	{
	  if (tempsAret[j][i] + tempsAret[i][k] < tempsAret[j][k])
	    {
	      tempsAret[j][k] = tempsAret[j][i] + tempsAret[i][k];
	      sommetsTraitee[j][k] = sommetsTraitee[j][i];

	    }
	}

  /*afficheLignes (S,g);
     printf ("regardez la map et "); */
  printf ("entrez un point de depart\n");
  i = Indice_station (S, g);
  printf ("entrez point d'arrivee\n");
  j = Indice_station (S, g);
  j = j - 1;
  i = i - 1;
  int k2;
  if (i < g.sommets)
    if (j < g.sommets)
      {
	if (i != j)
	  {

	    if (tempsAret[i][j] > 10000)
	      {
		printf
		  ("--------------------------------------------trajet non existant---------------------------------\n");
		return 1;
	      }
	    afficheLignes (S, g);
	    int temps = tempsAret[i][j];
	    int minute = temps / 60;
	    int seconde = temps % 60;
	    printf
	      ("Vous allez partir de:%s vers :%s\n temps estimee %dM %ds \n",
	       S.nomStation[i + 1], S.nomStation[j + 1], minute, seconde);
	    POINT p;

	    p.x = S.cord_x[i + 1];
	    p.y = S.cord_y[i + 1] + 10;
	    aff_pol ("Depart", 10, p, cyan);
	    p.x = S.cord_x[j + 1];
	    p.y = S.cord_y[j + 1] + 10;
	    aff_pol ("Arrivee", 10, p, vert);
	    printf ("itenairaire:de %s ", S.nomStation[i + 1]);
	    k = i + 1;
	    k2 = k;
	    do
	      {
		k = sommetsTraitee[k - 1][j];
		printf ("prenez (%s) vers %s ", g.type[k2][k],
			S.nomStation[k]);
		if (k != j + 1)
		  printf ("\nde %s ", S.nomStation[k]);
		else
		  printf ("\n vous errivé a destination : %s ",
			  S.nomStation[k]);
		dessin_chemin (S, g, k2, k);
		k2 = k;
	      }
	    while (k != j + 1);
	    printf ("\n");
	  }
      }
  return 0;
}

int main ()
{

  Station S;
  graph G;
  int i;
  S = lire_nom_station ();

  if (debutant_professionnel ())
    G = loadGraph ("fich_D_2.txt");
  else
    G = loadGraph ("fich_P_2.txt");
  i = floydWarshall (G, S);
  while (i)
    {
      i = floydWarshall (G, S);
    }

  wait_clic ();

  return 0;
}
