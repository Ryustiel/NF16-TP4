// https://learn.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2022
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tp4.h"

int main(){

    // creation de quelques patients

    Parbre liste_patients = NULL;

    char* prenoms[5] = {"maggie", "ben", "charley", "iggy", "jeb"};
    char* noms[5] = {"JOW", "SITTHIE", "BJORN", "AZAZE", "GEG"};

    printf("bip");
    for (int i=0; i<5; i++) {
        inserer_patient(&liste_patients, noms[i], prenoms[i]);
    }

    Parbre copie = NULL;
    printf("hi");
    afficher_patients(&liste_patients);
    printf("yo");
    maj(&liste_patients, &copie);



    // creation de consultations

    // suppression de patients...

        // en debut d'arbre (root node)

        // au milieu de l'arbre avec 2 successeurs

        // avec un successeur

        // en tant que feuille

    // on test la detection de memory leaks



}
