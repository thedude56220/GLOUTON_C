/*
	Parcours en profondeur
	Philippe Rolland Balzon
	prolland at free dot fr
	01/2006
	The Dude
*/

#include <stdio.h>
#include <stdio.h>



#define ORDER_MAX 30


typedef struct t_graphe Type_G;
struct t_graphe { 
	int order;
	int matrice[ORDER_MAX][ORDER_MAX];
};


Type_G init(Type_G g){
	int i,j;
	for(i=1;i<= g.order;i++){
		for(j=1;j<= g.order;j++){
			g.matrice[i][j]=0;
			}
		}
	return (g);
}

Type_G init_rand(Type_G g){
//matrice symŽtrique
	int i,j;
	for(i=1;i<= g.order;i++){
		for(j=1;j<=(i-1);j++){
			if(rand()%2==0){
				g.matrice[i][j]=0;
				g.matrice[j][i]=0;
				}
			else	{
				g.matrice[i][j]=1;
				g.matrice[j][i]=1;
				}
			}
		}
	return (g);
}

void parcours_profondeur(Type_G g, unsigned int som_depart)
{
     int *marque,i;
     marque=malloc(sizeof(int)*(g.order));
     for(i=1;i<=g.order;i++)
        marque[i]=0;

		printf("\n\nParcours en profondeur ˆ partir du sommet=%d\n",som_depart);
     printf("\n\n\tRencontre prefixe de %d\n",som_depart);
     parcours_profondeur_rec(g,som_depart,marque);
     printf("\tRencontre suffixe de %d\n",som_depart);
     free(marque);
     printf("\n");
}


void parcours_profondeur_rec(Type_G g, unsigned int s, int *marque)
{
     unsigned int i;
     marque[s]=1;
     for (i=1;i<=g.order;i++)
     {
		if (g.matrice[s][i]!=0)		// si i est un voisin de s
            if(!marque[i])			// si i n'est pas encore visite
            {
               printf("\tRencontre prefixe de %d\n",i);
               parcours_profondeur_rec(g,i,marque);
               printf("\tRencontre suffixe de %d\n",i);
            }
     }
}


void parcours_largeur(Type_G g, unsigned int s){
// la pile fifo
     int * list;
//le juda pour memoriser les sommets par ou on est deja passŽ
	 int *marque; 
	 int i,deb,fin;
	 int sommet_a_parcourir;
	 
	 list  =(int *)malloc(sizeof(int)*(g.order+2));
	 marque=(int *)malloc(sizeof(int)*(g.order+2));
	 //init du marque
	for(i=1;i<=g.order;i++)
        marque[i]=0;
	 //on enfile le sommet de depart
	 deb=1;
	 fin=2;
	 list[deb]=s;
	 marque[s]=1;// on le marque deja passe
	 while(deb<=g.order){
		//depiler
		sommet_a_parcourir=list[deb];
		deb++;
		printf("\n sommet %d) ",sommet_a_parcourir);
		//enfiler les voisins de sommet_a_parcourir
		 for(i=1;i<=g.order;i++){
			//si voisin et non marque
			if((g.matrice[sommet_a_parcourir][i]!=0)&&(marque[i]==0)){
				list[fin]=i;
				marque[i]=1;
				fin++;
				}
			}
		}

}

int * copyYdansZ(int * destination, int *origine, Type_G g){
	int i;
	for(i=1;i<=g.order;i++)
		destination[i]=origine[i];
	return(destination);
}

int premier_sommet_de_Z (int * vecteur,  Type_G g){
	int i;
	for(i=1;i<=g.order;i++)
		if (vecteur[i]==0)
			return(i);
	return(-1);
}

int * retirer_s_et_ces_voisins (int s, int * vecteur,  Type_G g){
	int i;
	vecteur[s]=1;
	vecteur[g.order+1]++;
	for(i=1;i<=g.order;i++)
		if((g.matrice[s][i]>0)&&(vecteur[i]==0)){
			vecteur[g.order+1]++;
			vecteur[i]=1;
			}
	return(vecteur);
}


int * glouton(Type_G g){
	int i,s;
	int * Y;
	int * Z;
	int cardY=0;
	int cardZ=0;
	int color=0;
	
	Y=(int *)malloc(sizeof(int)*(g.order+2));
	Z=(int *)malloc(sizeof(int)*(g.order+2));
	Z[g.order+1]=0;//contient cardZ
	//init
	for(i=1;i<=g.order;i++){
		Y[i]=0;
		Z[i]=0;
		}
	while (cardY<g.order){
		Z=copyYdansZ(Z,Y,g);
		Z[g.order+1]=cardY;
		color++;
		printf("\n\tChangement de couleur ˆ %d",color);
		while(Z[g.order+1]<g.order){
			s=premier_sommet_de_Z(Z,g);
			printf("\ncoloration de y=%d avec color=%d",s,color);
			Y[s]=color;cardY++;
			Z=retirer_s_et_ces_voisins(s,Z,g);
		}
	}
	return (Y);
}

void display_graph(Type_G g){
	int i,j;
	printf("\n\nDISPLAY graph:\n");
	for(i=1;i<= g.order;i++){
		printf("\n");
		for(j=1;j<=(i-1);j++){
			printf(" (%d,%d)=%d ",i,j,g.matrice[i][j]);
			}
		}
}

void display_vecteur(int *vecteur, Type_G g){
	int i;
	printf("\n\nDISPLAY vecteur (i,value):\n");
	for(i=1;i<= g.order;i++){
		printf(" (%d,%d) ",i,vecteur[i]);
		}
}

int main (int argc, const char * argv[]) {
    // insert code here...
	int i;
	Type_G g;
	int * coloration;



	g.order=10;
	g=init_rand(g);
	display_graph(g);
	//parcours_profondeur(g,1);
	//parcours_largeur(g,1);
	coloration=glouton(g);
	display_vecteur(coloration,g);
	
    printf("\nFin.\n");
    return 0;
}


