// https://learn.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2022
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tp4.h"

void main(){

    // creation de quelques patients

    Parbre liste_patients = NULL;

    char* noms[15] = {"H", "D", "B", "A", "C", "F", "E", "G", "L", "N", "O", "M", "J", "K", "I"};

    printf("yo");
    for (int i=0; i<15; i++) {
        inserer_patient(&liste_patients, noms[i], "Luc");
    }

    afficher_patients(&liste_patients);
    //Parbre copie = NULL;
    //maj(&liste_patients, &copie);
    //afficher_patients(&copie);



    // creation de consultations

    // suppression de patients...

        // en debut d'arbre (root node)

        // au milieu de l'arbre avec 2 successeurs

        // avec un successeur

        // en tant que feuille

    // on test la detection de memory leaks



}
