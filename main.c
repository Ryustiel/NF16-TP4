// https://learn.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2022
#include <stdio.h>
#include <tp4.h>
#include <tp4.c>

int main(){
    
    // creation de quelques patients

    Patient* root = NULL;
    Parbre liste_patients = root;

    char* prenoms[5] = {"maggie", "ben", "charley", "iggy", "jeb"};
    char* noms[5] = {"JOW", "SITTHIE", "BJORN", "AZAZE", "GEG"};

    for (int i=0; i<5; i++) {
        inserer_patient(liste_patients, );
    }

    

    // creation de consultations

    // suppression de patients...

        // en debut d'arbre (root node)

        // au milieu de l'arbre avec 2 successeurs

        // avec un successeur

        // en tant que feuille
    
    // on test la detection de memory leaks



}