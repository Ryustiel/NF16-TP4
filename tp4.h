typedef struct Consultation {
    char* date;
    char* motif;
    int niveauUrg;
    struct Consultation*;
} Consultation;

struct Patient {

}

typedef Patient* Parbre;

Patient* CreerPatient(char* nm, char* pr);
void inserer_patient(Parbre* abr, char* nm, char* pr);
Patient* rechercher_patient(Parbre* abr, char* mn);
void afficher_fiche(Parbre* abr, char* nm);
void afficher_patients(Parbre* abr);
Consultation* CreerConsult(char* date, char* motif, int nivu);
void ajouter_consultation(Parbre* abr, char* nm, char* date, char* motif, int nivu);
void supprimer_patient(Parbre* abr, char* nm);
void maj(Parbre* abr, Parbre* abr2);
