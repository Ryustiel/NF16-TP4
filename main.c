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

    char* noms[15] = {"H", "D", "B", "A", "C", "F", "E", "G", "L", "N", "O", "M", "J", "K", "I"};

    printf("yo");
    for (int i=0; i<15; i++) {
        inserer_patient(&liste_patients, noms[i], "Luc");
    }

    afficher_patients(&liste_patients);
}
