typedef struct Consultation {
    char* date;
    char* motif;
    int niveauUrg;
    struct Consultation*;
} Consultation;





typedef struct Patient {
    char* nom;
    char* prenom;
    struct Consultation* ListeConsult;
    int nbrconsult; 
    struct Patient* fils_gauche;
    struct Patient* fils_droit;
} patient;


typedef Patient* Parbre;
