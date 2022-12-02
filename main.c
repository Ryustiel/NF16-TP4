// https://learn.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2022
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tp4.h"

void main(){
    test();
}

//version test
void test(){
    Parbre liste_patients = NULL;
    Parbre liste2 = NULL;

    //Insertion et affichage
    char* noms[15] = {"H", "D", "B", "A", "C", "F", "E", "G", "L", "N", "O", "M", "J", "K", "I"};
    printf("yo");
    for (int i=0; i<15; i++) {
        inserer_patient(&liste_patients, noms[i], "Luc");
    }
    afficher_patients(&liste_patients);

    //Recherche, ajouter consultation et fiche
    ajouter_consultation(&liste_patients, "F", "01/01/2000", "fievre", 0);
    ajouter_consultation(&liste_patients, "K", "01/01/1999", "fievre", 0);
    ajouter_consultation(&liste_patients, "K", "01/01/2002", "douleur", 1);
    ajouter_consultation(&liste_patients, "K", "01/01/2001", "gastro", 2);
    ajouter_consultation(&liste_patients, "Z", "01/01/2000", "fievre", 0);
    ajouter_consultation(&liste2, "K", "01/01/2000", "fievre", 0);

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
}
