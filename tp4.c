#include<stdio.h>
#include<tp4.h>

Patient* creerPatient(char* nm, char* pr) {
    // creation d'objet 
    Patient* p = malloc(sizeof(Patient));

    // initialization des attributs
    p->nom = nm;
    p->prenom = pr;
    p->ListeConsult = NULL;
    p->nbrconsult = 0;
    p->fils_gauche = NULL;
    p->fils_droit = NULL;

    return p;
}

void inserer_patient(Parbre* abr, char* nm, char* pr) {

    // arbre vide : insertion i top
    if (abr == NULL) { // patient as root node
        *abr = CreerPatient(nm, pr);
    } 

    else {
        
        Patient* ptr = *abr;
        Patient* ptr_prec;
        int comparison;
        char last_fils; // sert a indiquer l'etat de terminaison du while -- apparemment les char prennent moins de place en memoire

        while (ptr != NULL) { // en fin de boucle ptr vaut soit un sous arbre de ptr_prec (disctingue par last_fils) soit ne change pas
            comparison = strcmp(ptr->nom, nm);
            ptr_prec = ptr;

            if (comparison < 0) { // node->nom < nm
                ptr = ptr->fils_gauche;
                last_fils = 1;
            }
            else if (comparison > 0) { // node->nom > nm
                ptr = ptr->fils_droit;
                last_fils = 2;
            }
            else {
                int success = 0;
                break; // node already exists
            }

            if (last_fils > 0) { // comportement suivant la derniere action du while
                if (last_fils == 1) {
                    ptr_prec->fils_gauche = CreerPatient(nm, pr);
                }
                else { // last_fils == 2
                    ptr_prec->fils_droit = CreerPatient(nm, pr);
                }
            }  
        }
    }
}

// trier par rapport a la date
Consultation* ajouter_consultation(Parbre* abr, char* nm, char* date, char* motif, int* nivu) {
    Patient* p = rechercher_patient(abr, nm);

    if (p->ListeConsult == NULL) { // patient as root node
        p->ListeConsult = CreerConsult(date, motif, nivu);
    } 

    else {
        
        Consultation* ptr = p->ListeConsult;
        Patient* ptr_prec;
        int comparison;

        while (ptr != NULL) { // en fin de boucle ptr vaut soit un sous arbre de ptr_prec (disctingue par last_fils) soit ne change pas
            comparison = strcmp(ptr->nom, nm);
            ptr_prec = ptr;

            if (comparison < 0) { // node->nom < nm
                ptr = ptr->fils_gauche;
                last_fils = 1;
            }
            else if (comparison > 0) { // node->nom > nm
                ptr = ptr->fils_droit;
                last_fils = 2;
            }
            else {
                int success = 0;
                break; // node already exists
            }

            if (last_fils > 0) { // comportement suivant la derniere action du while
                if (last_fils == 1) {
                    ptr_prec->fils_gauche = CreerPatient(nm, pr);
                }
                else { // last_fils == 2
                    ptr_prec->fils_droit = CreerPatient(nm, pr);
                }
            }  
        }
    }
}