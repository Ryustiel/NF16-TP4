#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

typedef struct Consultation {
    char* date;
    char* motif;
    int niveauUrg;
    struct Consultation* suivant;
} Consultation;


typedef struct Patient {
    char* nom;
    char* prenom;
    struct Consultation* ListeConsult;
    int nbrconsult;
    struct Patient* fils_gauche;
    struct Patient* fils_droit;
} Patient;


typedef Patient* Parbre;

Patient* CreerPatient(char nm[60], char pr[30]);
void inserer_patient(Parbre* abr, char nm[30], char pr[30]);
Patient* rechercher_patient(Parbre* abr, char nm[30]);
void afficher_fiche(Parbre* abr, char nm[60]);
void afficher_patients(Parbre* abr);
Consultation* CreerConsult(char date[10], char motif[120], int nivu);
int datecmp(char date1[10], char date2[10]);
void ajouter_consultation(Parbre* abr, char nm[30], char date[10], char motif[120], int nivu);
void supprimer_patient(Parbre* abr, char nm[30]);
void maj(Parbre* abr, Parbre* abr2);

void interface();
void maj_consultations(Consultation* reference, Patient* patient_modifier);
void supprimer_consultations(Patient* p);
void free_all_patients(Patient* p);
void free_patient(Patient* p);
int datecmp(char date1[10], char date2[10]);

#endif // TP3_H_INCLUDED
