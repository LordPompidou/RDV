#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <allegro.h>
#include <winalleg.h>
#define TAILLE 100

typedef struct RendezVous
{
    int date[3];// 0 : jour, 1 : l : mois, 2 : année
    int hdebut[2];// 0 : heure, 1 : minutes
    int hfin[2];// de même
    char nom[50];
    int rappel;
    int used;
}t_rdv;

int blindage(int var, int inf, int supp)
{
    if((var >= inf) && (var <= supp))
    {
        return var;
    }
    else
    {
        do{
            printf("Saisie invalide : ");
            scanf("%d", &var);
        } while((var <= inf) || (var >= supp));
        return var;
    }
}

void ajouterRdv(t_rdv tab1[TAILLE])
{
    int i,n;

    FILE* fic;
    fic = fopen("RDV.txt", "r+");

    if(fic == NULL) printf("ERREUR 2");

    for( i = 0; i < TAILLE; i++ )
    {
        if (tab1[i].used == 0)
            {
                n = i;
                i = TAILLE;
            }
    }
    fprintf(fic,"Rdv n°%d :\n",n);

    printf("Veuillez indiquer le jour du rdv : ");
    fflush(stdin);
    scanf("%d" , &tab1[n].date[0]);
    fflush(stdin);
    tab1[n].date[0] = blindage(tab1[n].date[0], 0, 31);
    printf("%d\n" , tab1[n].date[0]);//
    fprintf(fic,"%d\n", tab1[n].date[0]);

    printf("Veuillez indiquer le mois : ");
    fflush(stdin);
    scanf("%d", &tab1[n].date[1]);
    fflush(stdin);
    tab1[n].date[1] = blindage(tab1[n].date[1], 0, 12);
    printf("%d\n", tab1[n].date[1]);//
    fprintf(fic,"%d\n", tab1[n].date[1]);

    printf("annee : ");
    fflush(stdin);
    scanf("%d", &tab1[n].date[2]);
    fflush(stdin);
    tab1[n].date[2] = blindage(tab1[n].date[2], 2015, 3000);
    printf("%d\n", tab1[n].date[2]);//
    fprintf(fic,"%d\n", tab1[n].date[2]);

    printf("Veuillez indiquer le debut du rdv, l'heure et les minutes separe d'un espace : ");
    fflush(stdin);
    scanf("%d %d", &tab1[n].hdebut[0], &tab1[n].hdebut[1]);
    tab1[n].hdebut[0] = blindage(tab1[n].hdebut[0], 0, 24);
    tab1[n].hdebut[1] = blindage(tab1[n].hdebut[1], 0, 60);
    fflush(stdin);
    printf("%dh%d\n", tab1[n].hdebut[0], tab1[n].hdebut[1]);//
    fprintf(fic,"%dh%d\n", tab1[n].hdebut[0], tab1[n].hdebut[1]);

    printf("Veuillez indiquer la fin du rdv, l'heure et les minutes separe d'un espace : ");
    fflush(stdin);
    scanf("%d %d", &tab1[n].hfin[0], &tab1[n].hfin[1]);
    tab1[n].hfin[0] = blindage(tab1[n].hfin[0], 0, 24);
    tab1[n].hfin[1] = blindage(tab1[n].hfin[1], 0, 60);
    fflush(stdin);
    printf("%dh%d\n", tab1[n].hfin[0], tab1[n].hfin[1]);//
    fprintf(fic,"%dh%d\n", tab1[n].hfin[0], tab1[n].hfin[1]);

    printf("Veuillez indiquer le libelle du rdv : ");
    fgets(tab1[n].nom, 50, stdin);
    printf("%s\n", tab1[n].nom);
    fprintf(fic,"%s\n", tab1[n].nom);

    printf("Voulez un rappel ? Si oui ecrivez 1 sinon 0 : ");
    fflush(stdin);
    scanf("%d", &tab1[n].rappel);
    tab1[n].rappel = blindage(tab1[n].rappel, 0, 1);
    fflush(stdin);
    printf("%d\n", tab1[n].rappel);
    fprintf(fic,"%d", tab1[n].rappel);//

    tab1[n].used = 1;

    printf("Votre rdv a ete enregistre !\n Retour au menu...");

    fclose(fic);
}

void init(t_rdv tab[TAILLE])
{
    int i,j,k=0;

    FILE* fic;
    fic = fopen("RDV.txt", "r");

    if(fic == NULL) printf("ERREUR");

    for( i = 0; i < TAILLE; i++ )
    {
        tab[i].date[0]= 0;
        tab[i].date[1]= 0;
        tab[i].date[2]= 0;
        tab[i].hdebut[0]= 0;
        tab[i].hdebut[1]= 0;
        tab[i].hfin[0]= 0;
        tab[i].hfin[1]= 0;
        strcpy(tab[i].nom," ");
        tab[i].rappel = 0;
        tab[i].used = 0;
    }

    while ((j=fgetc(fic)) != EOF )
    {
        fscanf(fic,"%d", &k);
        fscanf(fic,"%d", &tab[k].date[0]);
        fscanf(fic,"%d", &tab[k].date[1]);
        fscanf(fic,"%d", &tab[k].date[2]);
        fscanf(fic,"%d", &tab[k].hdebut[0]);
        fscanf(fic,"%d", &tab[k].hdebut[1]);
        fscanf(fic,"%d", &tab[k].hfin[0]);
        fscanf(fic,"%d", &tab[k].hfin[1]);
        fgets(tab[k].nom,50,fic);
        fscanf(fic,"%d", &tab[k].rappel);
        tab[k].used = 1;
        k++;
    }

    fclose(fic);
}

void afficherRdv(t_rdv tab2[100])
{
    int i;

    for(i=0; i < TAILLE; i++)
    {
        if (tab2[i].used == 1)
        {
            printf("\nRdv numero %d\n", i+1);
            printf("Jour du rdv : %d/%d/%d \n", tab2[i].date[0], tab2[i].date[1], tab2[i].date[2]);
            printf("Heure du debut : %dh%d\n", tab2[i].hdebut[0], tab2[i].hdebut[1]);
            printf("Heure de fin : %dh%d\n", tab2[i].hfin[0], tab2[i].hfin[1]);
            printf("Libelle : %s\n", tab2[i].nom);
            if (tab2[i].rappel == 1 ) printf("Rappel active\n");
            else printf("Aucun rappel\n");
        }
    }
}

void rechercherRdv (t_rdv tab3[TAILLE])
{
    int i,j, choix, choix2;
    int n = 0;
    int nmax;
    int datesearch[3];
    int hdebutsearch[2];
    int hfinsearch[2];
    int found = 0;
    int search[TAILLE];
    char chaine[50];

   printf("Selon quel critere voulez-vous rechercher le rdv ?\n 1 : la date\n 2 : l'heure de debut\n 3 : l'heure de fin\n 4 : le libelle\n 5 : la presence d'un rappel\n");
   scanf("%d", &choix);
   choix = blindage(choix, 1, 5);
   switch(choix)
   {
    case 1 : printf("Veuillez indiquer la date du rdv recherché sous la forme : jour mois annee  ");
    fflush(stdin);
    scanf("%d %d %d", &datesearch[0], &datesearch[1], &datesearch[2]);
    datesearch[0] = blindage(datesearch[0], 0, 31);
    datesearch[1] = blindage(datesearch[1], 0, 12);
    datesearch[2] = blindage(datesearch[2], 2015, 3000);
    fflush(stdin);
    for(i=0; i<TAILLE; i++)
    {
        if ( (tab3[i].date[0] == datesearch[0]) && (tab3[i].date[1] == datesearch[1]) && (tab3[i].date[2] == datesearch[2]))
        {
            found = 1;
            search[n] = i;
            n++;
        }
        nmax  = n;
    }
        break;

    case 2 : printf("Veuillez indiquer l'horaire de debut du rdv sous la forme : heure minute  ");
    scanf("%d %d", &hdebutsearch[0], &hdebutsearch[1]);
    hdebutsearch[0] = blindage(hdebutsearch[0], 0, 24);
    hdebutsearch[1] = blindage(hdebutsearch[1], 0, 60);
    for(i=0; i < TAILLE; i++)
    {
        if( (tab3[i].hdebut[0] == hdebutsearch[0]) && (tab3[i].hdebut[1] == hdebutsearch[1]))
        {
            found = 1;
            search[n] = i;
            n++;
        }
        nmax  = n;
    }
        break;

    case 3 : printf("Veuillez indiquer l'horaire de fin du rdv sous la forme : heure minute  ");
    scanf("%d %d", &hfinsearch[0], &hfinsearch[1]);
    hfinsearch[0] = blindage(hfinsearch[0], 0, 24);
    hfinsearch[1] = blindage(hfinsearch[1], 0, 60);
    for(i=0; i < TAILLE; i++)
    {
        if( (tab3[i].hfin[0] == hfinsearch[0]) && (tab3[i].hfin[1] == hfinsearch[1]))
        {
            found = 1;
            search[n] = i;
            n++;
        }
        nmax  = n;
    }
        break;

    case 4 : printf("Veuillez indiquer le libelle du rdv : ");
    scanf("%s", chaine);
    for(i=0;i < TAILLE; i++)
    {
        if (strcmp(chaine,tab3[i].nom) == 0);
        {
            found = 1;
            search[n] = i;
            n++;
        }
        nmax = n;
    }
        break;

    case 5 : for(i=0; i < TAILLE; i++)
    {
        if (tab3[i].rappel == 1)
        {
            search[n] = i; // tableau de tous les rappels
            n++;
        }
    }
    nmax  = n;
    found = 1;
        break;
   }

   if (found == 1)
   {
       printf("Le/les rdv(s) a/ont ete trouve(s) ! Que voulez vous faire ?\n 1 : Afficher le/les rdv\n 2 : Supprimer un rdv\n ");
       scanf("%d", &choix2);
       choix2 = blindage(choix2, 1, 2);
       switch(choix2)
       {
        case 1 : for (n=0; n < nmax; n++);
        {
            j = search[n];
            printf("\nRdv numero %d\n", j+1);
            printf("Jour du rdv : %d/%d/%d \n", tab3[j].date[0], tab3[j].date[1], tab3[j].date[2]);
            printf("Heure du debut : %dh%d\n", tab3[j].hdebut[0], tab3[j].hdebut[1]);
            printf("Heure de fin : %dh%d\n", tab3[j].hfin[0], tab3[j].hfin[1]);
            printf("Libelle : %s\n", tab3[j].nom);
            if (tab3[j].rappel == 1 ) printf("Rappel active\n");
            else printf("Aucun rappel\n");
        }

            break;
        case 2 : printf("Quel rdv voulez vous supprime ?\n");
        fflush(stdin);
        scanf("%d",&n);
        n = blindage(n, 0, TAILLE);
        fflush(stdin);
        n = n-1;
        for(j=0; j <TAILLE; j++)
        {
            if( j == n)
            {
            tab3[n].date[0]= 0;
            tab3[n].date[1]= 0;
            tab3[n].date[2]= 0;
            tab3[n].hdebut[0]= 0;
            tab3[n].hdebut[1]= 0;
            tab3[n].hfin[0]= 0;
            tab3[n].hfin[1]= 0;
            strcpy(tab3[n].nom," ");
            tab3[n].rappel = 0;
            tab3[n].used = 0;
            }
        }
            break ;
       }
   }
   else printf("Rdv non trouve !");

   printf("Retour au menu ...");

}

void menu(t_rdv tab[TAILLE])
{
    int i,j,k,c,choix,sortie=0;
    int save;
    int today;

    struct tm* t;
    time_t tt;

    do{

    tt = time(NULL);
    t = localtime(&tt);

    c = 0;
    for(j=0;j<TAILLE;j++)
    {
        if (tab[j].used == 1) c++;
    }

    printf("Vous avez %d rdv\n Aujourd'hui vous avez : \n", c);
    for(k=0; k <TAILLE; k++)
    {
        if (tab[k].date[0] == t->tm_mday)
        {
            printf("Heure du debut : %dh%d\n", tab[k].hdebut[0], tab[k].hdebut[1]);
            printf("Heure de fin : %dh%d\n", tab[k].hfin[0], tab[k].hfin[1]);
            printf("Libelle : %s\n", tab[k].nom);
            if (tab[k].rappel == 1 ) printf("Rappel active\n");
            else printf("Aucun rappel\n");
        }
    }
    printf("Que voulez faire ?\n 1 : Ajouter un rdv\n 2 : Afficher les rdv \n 3 : Rechercher les rdv\n 4 : Supprimer tous les rdv\n 5 : Quitter\n");
    scanf("%d",&choix);
    choix = blindage(choix, 1, 5);
    switch(choix)
    {
    case 1 : ajouterRdv(tab);
        break;
    case 2 : afficherRdv(tab);
        break;
    case 3 : rechercherRdv(tab);
        break;
    case 4 : init(tab);
        break;
    case 5 :  sortie = 1;
        break;

    }
    } while(sortie != 1);

    for(i=0; i < TAILLE; i++)
    {
        if( (tab[i].date[0] == t->tm_mday) && (tab[i].date[1] == t->tm_mon +1)  && (tab[i].date[2] == t->tm_year + 1900) )
        {
            if(tab[i].hdebut[1]-15 >= 0)
            {
                if( (tab[i].hdebut[1] - 15 >= t->tm_min) && (tab[i].hdebut[0] == t->tm_hour))
                    {
                        allegro_message("\nRappel ! Rdv dans moins de 15 min\n");
                    }
            }

            else
            {
                save = tab[i].hdebut[1] - 15;
                save = fabs(save);
                tab[i].hdebut[0] = tab[i].hdebut[0] - 1;
                tab[i].hdebut[1] = 60 - save;
                if( (tab[i].hdebut[0] ==  t->tm_hour) && (tab[i].hdebut[1] == t->tm_min) )
                {
                    allegro_message("\n Rappel ! Rdv dans 15 min");
                }
            }
        }
    }
}

int main()
{
    t_rdv tab[TAILLE];

    init(tab);

    menu(tab);

    return 0;
} END_OF_MAIN();
