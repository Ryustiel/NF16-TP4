#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tp4.h"

Patient* CreerPatient(char* nm, char* pr) {
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


Consultation* CreerConsult(char* date, char* motif, int nivu) {
    // creation d'objet
    Consultation* c = malloc(sizeof(Consultation));

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
    /*int i = 0;
    char test;
    while (nm[i] != '\0') {
        if (nm[i] >= 'a') {
            //printf("%c %c\n", nm[i], nm[i] - 'a' + 'A');
            test = nm[i] - 'a' + 'A'; // minuscule to majuscule
            printf("%c", test);
        }
        i++;
    }*/

    // arbre vide : insertion en tete
    if (*abr == NULL) { // patient as root node
        *abr = CreerPatient(nm, pr);
    }

    else {

        Patient* ptr = *abr;
        Patient* ptr_prec;
        int comparison;
        char last_fils; // sert a indiquer l'etat de terminaison du while -- apparemment les char prennent moins de place en memoire

        while (ptr != NULL) { // en fin de boucle ptr vaut soit un sous arbre de ptr_prec (distingue par last_fils) soit ne change pas
            comparison = strcmp(nm, ptr->nom);
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

        } // else last_fils == 0 (node correspondante existe deja)

        // comportement suivant la derniere action du while
        if (last_fils == 1) { // insertion a gauche
            ptr_prec->fils_gauche = CreerPatient(nm, pr);
        }
        else if (last_fils == 2) { // insertion a droite
            ptr_prec->fils_droit = CreerPatient(nm, pr);
        }

    }
}


/*
// DEFINIR DATECMPR (lettre par lettre) 78-56-1234 (0 1 - 3 4 - 6 7 8 9)
int consultcmp(char* date) { // returns an unique int proportional to the date for comparison
    return date[1] + date[0]*10 + date[4]*100 + date[3]*1000 + date[9]*10000 + date[8]*100000 + date[7]*1000000 + date[6]*10000000; // utiliser la valeur du code ascii des characters pour le produit revient au meme car ils sont consecutifs dans la table
}
*/

int consultcmp(Consultation* relative, Consultation* nouvelle) { // compare les caracteristiques de nouvelle et relative consultation, et renvoie 1 si la nouvelle consultation devrait etre placee avant la relative (c'est a dire date inferieure, niveau d'urgence inferieur si date egale), 0 sinon

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

    if (p != NULL) { // valeur par defaut de rechercher_patient, cas patient non trouve

        p->nbrconsult += 1;

        if (p->ListeConsult == NULL) { // patient as root node
            p->ListeConsult = CreerConsult(date, motif, nivu);
        }

        else { // recherche de la premiere date superieure ou egale (ptr) et

            Consultation* ptr = p->ListeConsult;
            Consultation* ptr_prec;
            Consultation* nouvelle = CreerConsult(date, motif, nivu);
            int position_avant = consultcmp(p->ListeConsult, nouvelle); // position relative de la nouvelle consultation par rapport a celle passee en premier argument

            if (position_avant) { // checking the root node
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
    if (p != NULL) {
        printf("Nom : %s\nPrenom : %s\nNombre de consultations : %d\n", p->nom, p->prenom, p->nbrconsult);

        Consultation* consult = p->ListeConsult;
        while (consult != NULL) {
            printf("\nDate de la consultation : %s\nMotif : %s\nNiveau d'urgence : %d\n", consult->date, consult->motif, consult->niveauUrg);
            consult = consult->suivant;
        }
    } else {
        printf("Le patient %s n'est pas enregistre.\n", nm);
    }
}


void afficher_patients(Parbre* abr) {
    if (*abr == NULL) {
        printf("-");
    } else {
        printf("(%s ", (*abr)->nom);
        afficher_patients(&((*abr)->fils_gauche));
        afficher_patients(&((*abr)->fils_droit));
        printf(") ");
    }
}


void free_patient(Patient* p) {
    // suppression de l'attribut ListeConsult (liste chainee)
    //supprimer_consultations(p);

    free(p);
}


void supprimer_patient(Parbre* abr, char* nm) {
    int comparison;
    Patient* ptr = *abr;
    Patient* ptr_prec = NULL;

    while (ptr != NULL) { // recherche le patient dans l'arbre
      comparison = strcmp(ptr->nom, nm);
      if (comparison < 0) {
        ptr_prec = ptr;
        ptr = ptr->fils_droit;
      }
      else if (comparison > 0) {
        ptr_prec = ptr;
        ptr = ptr->fils_gauche;
      }
      else { // noeud patient trouve

          // detachement du noeud patient (ptr->)
        if (ptr->fils_droit == NULL) { // le noeud a detacher a au plus un fils gauche
            if (ptr_prec == NULL) { // ptr est la racine de l'arbre
                *abr = ptr->fils_gauche;
            }
            else if (ptr_prec->fils_droit == ptr) { // ptr est un fils droit
                ptr_prec->fils_droit = ptr->fils_gauche;
            }
            else { // ptr est un fils gauche
                ptr_prec->fils_gauche = ptr->fils_gauche;
            }
        }
        else if (ptr->fils_gauche == NULL) { // le noeud a detacher a au plus un fils droit
            if (ptr_prec == NULL) { // ptr est la racine de l'arbre
                *abr = ptr->fils_droit;
            }
            else if (ptr_prec->fils_droit == ptr) {
                ptr_prec->fils_droit = ptr->fils_droit;
            }
            else {
                ptr_prec->fils_gauche = ptr->fils_droit;
            }
        }
        else { // le noeud a detacher a 2 fils

            // le noeud a forcement un successeur a droite
            Patient* succ = ptr->fils_droit;
            Patient* succ_prec = ptr;
            while (succ->fils_gauche != NULL) { // le successeur est le minimum du sous arbre gauche (tous noeuds->nom > ptr->nom)
                succ_prec = succ;
                succ = succ->fils_gauche;
            }

            // detacher succ
            // succ ne peut pas avoir de fils gauche (voir boucle precedente)
            if (succ_prec == ptr) { // succ est un fils droit de ptr
                succ_prec->fils_droit =  succ->fils_droit;
            }
            else { // succ est un fils gauche
                succ_prec->fils_gauche = succ->fils_droit;
            }

            // copie des attributs de succ non lies a la structure d'arbre dans le noeud a detacher (ptr->)
            ptr->nom = succ->nom;
            ptr->prenom = succ->prenom;
            ptr->ListeConsult = succ->ListeConsult;
            ptr->nbrconsult = succ->nbrconsult;

            ptr = succ; // ptr pointe toujours vers le noeud a detruire en fin de boucle
        }

        // suppression des attributs pointes (ptr->->)
        free_patient(ptr);
        }
    }
}


void free_all_patients(Patient* p) {
    if (p != NULL) {
        free_all_patients(p->fils_gauche);
        free_all_patients(p->fils_droit);
        free_patient(p);
    }
}


void supprimer_consultations(Patient* p) {
    // suppression de l'attribut ListeConsult (liste chainee)
    Consultation* ptrc = p->ListeConsult;
    Consultation* temp;
    while (ptrc != NULL) {
        temp = ptrc;
        ptrc = ptrc->suivant;
        free(temp);
    }
}


int consultation_egale(Consultation* c1, Consultation* c2) { // verifie si les deux consultations sont egales
    if (c1 == NULL && c2 == NULL) {return 1;}
    else if (c1 == NULL || c2 == NULL) {return 0;}
    else if (c1->date != c2->date) {return 0;}
    else if (c1->motif != c2->motif) {return 0;}
    else if (c1->niveauUrg != c2->niveauUrg) {return 0;}
    return 1;
}


void maj_consultations(Consultation* reference, Patient* patient_modifier) {
    // parcours les noeuds et test si similaires. Si un noeud est different remplace ses valeurs par les nouvelles.

    if (consultation_egale(patient_modifier->ListeConsult, reference) == 0) {
        patient_modifier->ListeConsult = CreerConsult(reference->date, reference->motif, reference->niveauUrg);
    } // desormais patient_modifier->ListeConsult = reference
    Consultation* ref_ptr = reference->suivant;
    Consultation* modifier_ptr_prec = patient_modifier->ListeConsult;
    Consultation* modifier_ptr = modifier_ptr_prec->suivant;
    while (ref_ptr != NULL) {
        if (consultation_egale(ref_ptr, modifier_ptr) == 0) { // le noeud doit etre mis a jour
            if (modifier_ptr == NULL) { // cree un nouveau noeud
                modifier_ptr_prec->suivant = CreerConsult(ref_ptr->date, ref_ptr->motif, ref_ptr->niveauUrg);
            }
            else { // met simplement a jour le noeud existant
                modifier_ptr->date = ref_ptr->date;
                modifier_ptr->motif = ref_ptr->motif;
                modifier_ptr->niveauUrg = ref_ptr->niveauUrg;
            }
        }
        modifier_ptr_prec = modifier_ptr_prec->suivant;
        modifier_ptr = modifier_ptr_prec->suivant;
    }
    while (modifier_ptr != NULL) { // ref_ptr est NULL donc la chaine a partir de cette addresse pour modifier devrait etre NULL aussi
        modifier_ptr_prec = modifier_ptr; // utilise modifier_ptr_prec comme variable temporaire pour free
        modifier_ptr = modifier_ptr->suivant;
        free(modifier_ptr_prec); // supprime chaque consultation superflue
    }
}


void maj(Parbre* abr, Parbre* abr2) {
    // le parcours le plus bete du monde : parcourir, modifier si different -- abr2 copie basiquement abr, c'est un ABR a la fin


    if (*abr == NULL) {
        free_all_patients(*abr2); // supprime le noeud superflu dans abr2
        *abr2 = NULL; // ce pointeur sur patient est desormais NULL
    }
    else {
        if (*abr2 == NULL || (*abr2)->nom != (*abr)->nom) { // on suppose que les noms sont uniques
            if (*abr2 == NULL) {
                *abr2 = CreerPatient((*abr)->nom, (*abr)->prenom);
            }
            else { // changement du patient associe a ce noeud de l'arbre
                (*abr2)->nom = (*abr)->nom;
                (*abr2)->prenom = (*abr)->prenom;
                supprimer_consultations((*abr2)->ListeConsult); // suppression des consultations enregistrees pour eviter les conflits d'attributs (consultations aux memes dates, niveaux d'urgence pour deux patients differents pour des motifs differents)
            }



            (*abr2)->ListeConsult = (*abr)->ListeConsult;
            (*abr2)->nbrconsult = (*abr)->nbrconsult;

        }
        maj(&((*abr)->fils_droit), &((*abr2)->fils_droit));
        maj(&((*abr)->fils_gauche), &((*abr2)->fils_gauche));
    }
}



void interface() {
    //allocation d'un espace pour la liste des matrices
    Parbre liste_patients = NULL;
    Parbre liste_backup = NULL;

    int continuer = 1, reponse, urgence; // variables utilisees pour stocker les informations saisies
    char* nom, prenom, date, motif;
    while (continuer) {
        //affichage du menu et attente d'une reponse
        printf("Que voulez-vous faire ?\n1. Ajouter un patient\n2. Ajouter une consultation à un patient\n3. Afficher une fiche medicale\n4. Afficher la liste des patients\n5. Supprimer un patient\n6. Copier la liste des patients depuis la derniere sauvegarde\n7. Mettre a jour la sauvegarde de la liste des patients\n8. Quitter\n\n");
        scanf("%d", &reponse);
        printf("\n");

        switch (reponse) {

            case 1: // ajouter un patient

                printf("\nSaisir un nom > ");
                scanf("%s", nom); // demande nom et prenom du patient
                printf("\nSaisir un prenom > ");
                scanf("%s", prenom);
                inserer_patient(&liste_patients, nom, prenom);
                printf("\nPatient ajoute!");
                printf("\n");
                break;

            case 2: // ajouter une consultation a un patient

                printf("\nSaisir un nom > ");
                scanf("%s", nom); // demande nom du patient
                if (rechercher_patient(&liste_patients, nom) == NULL) { // verifie si il existe
                    printf("ce patient n'existe pas");
                }
                else { // le patient existe dans l'arbre
                    printf("\nSaisissez la date de la consultation (JJ/MM/AAAA) > ");
                    scanf("%s", date);
                    printf("\nSaisissez le motif de la consultation > ");
                    scanf("%s", motif);
                    printf("\nSaisissez le niveau d'urgence de la consultation (entier) > ");
                    scanf("%d", &urgence);
                    ajouter_consultation(&liste_patients, nom, date, motif, urgence);
                    printf("\nConsultation ajoute!");
                }
                printf("\n");
                break;

            case 3: // afficher une fiche medicale

                printf("\nSaisir un nom > ");
                scanf("%s", nom);
                if (rechercher_patient(&liste_patients, nom) == NULL) {
                    printf("ce patient n'existe pas");
                }
                else {
                    afficher_fiche(&liste_patients, nom);
                }
                printf("\n");
                break;

            case 4: // afficher la liste des patients

                afficher_patients(&liste_patients);
                printf("\n");
                break;

            case 5: // supprimer un patient

                printf("\nSaisir un nom > ");
                scanf("%s", nom);
                if (rechercher_patient(&liste_patients, nom) == NULL) {
                    printf("ce patient n'existe pas");
                }
                else {
                    supprimer_patient(&liste_patients, nom);
                    printf("\nLe patient a ete supprime");
                }
                printf("\n");
                break;

            case 6: // copier la liste des patients depuis la derniere sauvegarde

                maj(&liste_backup, &liste_patients);
                printf("Patients importes");
                printf("\n");
                break;

            case 7: // mettre a jour la sauvegarde de la liste des patients
                
                maj(liste_patients, liste_backup);
                printf("Patients sauvegardes");
                printf("\n");
                break;

            case 8: { //quitter

                free_all_patients(liste_patients); // suppression de tous les patients
                free_all_patients(liste_backup);
                continuer = 0; //sortie de la boucle
                break;
            }
        }
    }
}
