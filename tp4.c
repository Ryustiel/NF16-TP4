
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

Consultation* creerConsult(char* date, char* motif, int nivu) {
    // creation d'objet 
    Consultation* c = malloc(sizeof(Patient));

    // initialization des attributs
    c->date = date;
    c->motif =  motif;
    c->niveauUrg = nivu;
    c->suivant = NULL;

    return c;
}

// CAP CONTROL (done, needs double checking)
void inserer_patient(Parbre* abr, char* nm, char* pr) { // nm (nom a inserer), pr (prenom//)

    // normalisation des caracteres du nom (defini uniquement majuscule)
    int i = 0;
    while (nm[i] != '\n') {
        if (nm[i] >= 'a') {
            nm[i] = nm[i] - ('a' - 'A'); // minuscule to majuscule
        }
        i++;
    }

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
                last_fils = 0;
                break; // node already exists
            }

            if (last_fils > 0) { // comportement suivant la derniere action du while
                if (last_fils == 1) { // (gauche)
                    ptr_prec->fils_gauche = CreerPatient(nm, pr);
                }
                else { // last_fils == 2 (droite)
                    ptr_prec->fils_droit = CreerPatient(nm, pr);
                }
            } // else last_fils == 0 (node correspondante existe deja)
        }
    }
}

/*
// DEFINIR DATECMPR (lettre par lettre) 78-56-1234 (0 1 - 3 4 - 6 7 8 9)
int consultcmp(char* date) { // returns an unique int proportional to the date for comparison
    return date[1] + date[0]*10 + date[4]*100 + date[3]*1000 + date[9]*10000 + date[8]*100000 + date[7]*1000000 + date[6]*10000000; // utiliser la valeur du code ascii des characters pour le produit revient au meme car ils sont consecutifs dans la table
}
*/

int consultcmp(Consultation* relative, Consultation* nouvelle) { // compare les caracteristiques de nouvelle et relative, et renvoie 1 si la nouvelle consultation devrait etre placee avant la relative, 0 sinon

    // comparaison de date
    int indices[8] = {6, 7, 8, 9, 3, 4, 0, 1}; // composants de la date par ordre d'importance : JJ-MM-AAAA, 78-56-1234 (0 1 - 3 4 - 6 7 8 9)

    for (int i; i<8; i++) {
        if (relative->date[indices[i]] < nouvelle->date[indices[i]]) { // les valeurs ascii des char dans les dates sont comparables car les chiffres sont consecutifs dans la table
            return 0; // le nouvel element est superieur au relatif, (composante de date superieur a celui de relative, et toutes les composantes plus importantes sonte egales)
        }
        else if (nouvelle->date[indices[i]] < relative->date[indices[i]]) {
            return 1; // pareil qu'au dessus, mais nouvel element inferieur au relatif, donc doit etre place avant
        }
        // sinon, les composantes de date sont egales, poursuivre
    }

    // comparaison de niveau
    if (nouvelle->niveauUrg <= relative->niveauUrg) { // placer la nouvelle consultation apres l'ancienne si identiques (=) ou niveau d'urgence inferieure
        return 0;
    }
    else {
        return 1;
    }


}


// trier par rapport a : date ordre croissant, niveau d'urgence ordre decroissant (priorite secondaire)
void ajouter_consultation(Parbre* abr, char* nm, char* date, char* motif, int nivu) {
    Patient* p = rechercher_patient(abr, nm);

    if (p->ListeConsult == NULL) { // patient as root node
        p->ListeConsult = CreerConsult(date, motif, nivu);
    }

    else { // recherche de la premiere date superieure ou egale (ptr) et 

        Consultation* ptr = p->ListeConsult;
        Consultation* ptr_prec;
        Consultation* nouvelle = CreerConsult(date, motif, nivu);
        int position_avant = consultcmp(p->ListeConsult, nouvelle); // position relative de la nouvelle consultation par rapport a celle passee en premier argument

        if (position_avant) { // checking the root node (might require updating Patient)
            // inserer en tant que tete de liste
            p->ListeConsult = nouvelle;
            p->ListeConsult->suivant = ptr;
        }

        else {

            while (ptr != NULL) { // en fin de boucle ptr vaut soit un sous arbre de ptr_prec (disctingue par last_fils) soit ne change pas
            position_avant = consultcmp(ptr, nouvelle);
            ptr_prec = ptr;

            ptr = ptr->suivant;
            if (position_avant) { 
                break; // le ptr a une date superieure ou egale a la nouvelle : proceder a l'insertion sur le precedent
            }
            // sinon continuer (jusqu'a ptr suivant >= ou ptr = NULL (cas de l'insertion en fin de chaine)
        }

        ptr_prec->suivant = nouvelle;
        ptr_prec->suivant->suivant = ptr; // chainage simple, pas besoin de definir un precedent

        }
    }
}


Patient* rechercher_patient(Parbre* abr, char* nm) {
    Patient* ptr = *abr; // switch du type vers pointeur sur Patient (typedef Patient* Parbre;) Patient*->nom <=> Parbre->nom <=> *(Parbre*)->nom
    while (ptr != NULL) {
        int rel = strcmp(ptr->nom, nm); //comparaison du nom du patient et du noeud
        if (rel == 0) {
            return ptr; //patient trouve
        } else if (rel > 0) {
            ptr = ptr->fils_gauche; //nom du patient inferieur au noeud actuel
        } else {
            ptr = ptr->fils_droit; //nom du patient superieur au noeud actuel
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

/*
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
*/

void supprimer_patient(Parbre* abr, char* nm) {
    int comparison;
    Patient* ptr = abr;
    while (ptr != NULL) {
        comparison = strcmp(ptr->nom, nm);
        if (comparison < 0) {
            ptr = ptr->fils_droit;
        }
        else if (comparison > 0) {
            ptr = ptr->fils_gauche;
        }
        else {
            Consultation* ptrc = ptr->ListeConsult;
            Consultation* temp;
            while (ptrc != NULL) {
                temp = ptrc;
                ptrc = ptrc->suivant;
                free(temp);
            }
            // SUPPRESSION D'ARBRE (super galere)
            free(ptr); // TESTER SI IL FAUT FREE CHAQUE COMPOSANT DU STRUCT
        }
    }
}

void maj(Parbre* abr, Parbre* abr2) {
    // 

}