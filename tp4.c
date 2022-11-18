Patient* rechercher_patient(Parbre* abr, char* mn) {
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
