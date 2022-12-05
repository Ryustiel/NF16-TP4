// https://learn.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2022
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tp4.c"

void test(){
    Parbre liste_patients = NULL;
    Parbre liste2 = NULL, liste3 = NULL;

    //Insertion et affichage
    /*
    char* noms[15] = {"H", "D", "B", "A", "C", "F", "E", "G", "L", "N", "O", "M", "J", "K", "I"};
    for (int i=0; i<15; i++) {
        inserer_patient(&liste_patients, noms[i], "Luc");
    }
    afficher_patients(&liste_patients);
    */


    //Premier test de MAJ
    /*
    maj(&liste_patients, &liste3);
    afficher_patients(&liste3);
    */


    //Comparaison de dates
    printf("\n%d", datecmp("01/01/2000", "01/01/2001"));
    printf("\n%d", datecmp("01/01/2000", "01/01/2010"));
    printf("\n%d", datecmp("01/01/2000", "01/01/2100"));
    printf("\n%d", datecmp("01/01/2000", "01/01/3000"));
    printf("\n%d", datecmp("01/01/2000", "01/02/2000"));
    printf("\n%d", datecmp("01/01/2000", "01/11/2000"));
    printf("\n%d", datecmp("01/01/2000", "02/01/2000"));
    printf("\n%d", datecmp("01/01/2000", "11/01/2000"));
    printf("\n");
    printf("\n%d", datecmp("01/01/2001", "01/01/2000"));
    printf("\n%d", datecmp("01/01/2010", "01/01/2000"));
    printf("\n%d", datecmp("01/01/2100", "01/01/2000"));
    printf("\n%d", datecmp("01/01/3000", "01/01/2000"));
    printf("\n%d", datecmp("01/02/2000", "01/01/2000"));
    printf("\n%d", datecmp("01/11/2000", "01/01/2000"));
    printf("\n%d", datecmp("02/01/2000", "01/01/2000"));
    printf("\n%d", datecmp("11/01/2000", "01/01/2000"));



    //Recherche, ajouter consultation et fiche
    /*
    ajouter_consultation(&liste_patients, "F", "01/01/2004", "vomissement", 2);
    ajouter_consultation(&liste_patients, "K", "01/01/2000", "fievre", 0);
    ajouter_consultation(&liste_patients, "K", "01/01/1999", "fievre", 0);
    ajouter_consultation(&liste_patients, "K", "01/01/2002", "douleur", 1);
    ajouter_consultation(&liste_patients, "K", "01/01/2001", "gastro", 2);
    ajouter_consultation(&liste_patients, "Z", "01/01/2000", "fievre", 0);
    ajouter_consultation(&liste_patients, "I", "01/01/2000", "bobo", 4);
    ajouter_consultation(&liste2, "K", "01/01/2000", "fievre", 0);
    */

    /*
    afficher_fiche(&liste_patients, "H");
    afficher_fiche(&liste_patients, "B");
    afficher_fiche(&liste_patients, "F");
    afficher_fiche(&liste_patients, "K");
    afficher_fiche(&liste_patients, "M");
    afficher_fiche(&liste_patients, "GO");
    afficher_fiche(&liste_patients, "EO");
    afficher_fiche(&liste_patients, "GA");
    afficher_fiche(&liste_patients, "EA");
    afficher_fiche(&liste_patients, "Z");
    afficher_fiche(&liste2, "H");
    */



    //Suppression
    supprimer_patient(&liste_patients, "C");
    supprimer_patient(&liste_patients, "E");
    supprimer_patient(&liste_patients, "B");
    supprimer_patient(&liste_patients, "F");
    supprimer_patient(&liste_patients, "J");
    supprimer_patient(&liste_patients, "L");
    supprimer_patient(&liste_patients, "H");
    supprimer_patient(&liste_patients, "Z");
    /*
    afficher_patients(&liste_patients);
    afficher_fiche(&liste_patients, "I");
    */

    /*supprimer_patient(&liste2, "E");
    inserer_patient(&liste2, "A", "Luc");
    supprimer_patient(&liste2, "A");
    afficher_patients(&liste2);*/



    //Deuxieme test de MAJ
    /*
    maj(&liste_patients, &liste3);
    afficher_patients(&liste3);

    afficher_fiche(&liste3, "K");
    ajouter_consultation(&liste_patients, "K", "01/01/2013", "accident", 3);
    maj(&liste_patients, &liste3);
    afficher_fiche(&liste_patients, "K");
    afficher_fiche(&liste3, "K");
    */



    //Test de free final
    /*
    free_all_patients(liste_patients);
    printf("bien free");
    */
}

int main(){
    test();
    //interface();
    return 0;
}
