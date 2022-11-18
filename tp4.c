
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


Patient* rechercher_patient(Parbre* abr, char* nm) {
    while (abr != NULL) {
        int rel = strcmp(abr->nom, nm); //comparaison du nom du patient et du noeud
        if (rel == 0) {
            return abr; //patient trouve
        } else if (rel > 0) {
            abr = abr->fils_gauche; //nom du patient inferieur au noeud actuel
        } else {
            abr = abr->fils_droit; //nom du patient superieur au noeud actuel
        }
    }
    return NULL; //le patient n'a pas ete trouve
}

void afficher_fiche(Parbre* abr, char* nm) {
    Patient* p = rechercher_patient(abr, nm);
    printf("Nom : %s\nPrenom%s\nNombre de consultations : %d\n", p->nom, p->prenom, p->nbrconsult);

    Consultation* consult = p->ListeConsult;
    while (consult != NULL) {
        printf("\nDate de la consultation : %s\nMotif : %s\nNiveau d'urgence : %d\n", consult->date, consult->motif, consult->niveauUrg);
        consult = consult->suivant;
    }
}

void afficher_patients(Parbre* abr) {
    if (abr == NULL) {
        printf("-");
    } else {
        printf("(%s ", abr->nom);
        afficher_patients(abr->fils_gauche);
        afficher_patients(abr->fils_droit);
        printf(") ")
    }
}

