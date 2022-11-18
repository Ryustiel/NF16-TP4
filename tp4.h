struct Consultation {
    char* date;
    char* motif;
    niveauUrg
}





//test si c'est toujours la c'est bon




typedef struct Patient {
    char* nom;
    char* prenom;
    struct Consultation* ListeConsult;
    int nbrconsult; 
    struct Patient* fils_gauche;
    struct Patient* fils_droit;
} patient;
