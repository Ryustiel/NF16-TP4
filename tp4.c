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
