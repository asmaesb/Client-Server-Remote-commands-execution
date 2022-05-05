#ifndef HEADER_PRG_SYS_H
#define HEADER_PRG_SYS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct personne
{
    char *nom;
    char *prenom;
    char *num_tel;
} personne;


void listerContenu(const char *dirNom);
void listerOrdonne(const char *Nom);
void afficherFichier(char *fichNom);
void creerRep(char *repNom);
void supprimerRep(char *Nom);
char *join(char *s1, const char *s2);
int Rechercher(char *fileName, personne *prs);
void supprimer(char *fileName, personne *prs);
void ajouter(char *fileName, personne *prs);
void modifier(char *fileName, personne *ancien, personne *nouveau);


#endif