#include "headerPrgSys.h"
#define _XOPEN_SOURCE_EXTENDED 1
#define _GNU_SOURCE
#include <limits.h>
#include <sys/param.h>


void listerContenu(const char *dirNom)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(dirNom);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}

void listerOrdonne(const char *Nom)
{
    struct dirent **namelist;
    int n;
    int i = 0;

    n = scandir(Nom, &namelist,NULL,alphasort);
    while (i < n) 
    {
         printf("%s\n", namelist[i]->d_name);
         free(namelist[i]);
         i++;
    }
    free(namelist);
}

void afficherFichier(char *fichNom)
{
    FILE *ptr;
    char ch;

    ptr = fopen(fichNom, "r");

    if (ptr == NULL)
    {
        printf("Erreur ouverture fichier \n");
    }

    do
    {
        ch = fgetc(ptr);
        printf("%c", ch);

    } while (ch != EOF);

    fclose(ptr);
}

void creerRep(char *repNom)
{
    FILE *ptr1;
    FILE *ptr2;
    
    if (mkdir(repNom , 0777) == 0)
    {
        printf("repertoire cree\n");
    }
    ptr1 = fopen(join(repNom, "/fichier1.txt"), "w");
    fclose(ptr1);
    ptr2 = fopen(join(repNom, "/fichier2.txt"), "w");
    fclose(ptr2);
    if (ptr1 && ptr2)
    {
        printf("Les fichiers ont ete crees\n");
    }
}

void supprimerRep(char *Nom)
{
    if (strstr(Nom, ".txt"))
    {
        remove(Nom);
        printf("file del\n");
    }
    else
    {
    remove(join(Nom, "/fichier1.txt"));
    remove(join(Nom, "/fichier2.txt"));
    rmdir(Nom);
    }
}

char *join(char *s1, const char *s2)
{
    if (!s1)
        return strdup(s2);

    char *result = malloc(strlen(s1) + strlen(s2) + 1);

    if (result)
    {
        strcpy(result, s1);
        strcat(result, s2);
    }
    return result;
}

int Rechercher(char *fileName, personne *prs)
{
    FILE *ptr;
    char *s;
    int line;
    int i;

    line = 1;
    ptr = fopen(fileName, "r");
    if (!ptr)
        return 0;
    do
    {
        s = malloc(30);
        i = -1;
        do
        {
            i++;
            s[i] = getc(ptr);
        } while (s[i] != '\n' && s[i] != EOF);
        if (s[i] == EOF)
            break;
        s[i] = '\0';
        if (strstr(s, prs->nom) && strstr(s, prs->prenom) && strstr(s, prs->num_tel))
        {
            fclose(ptr);
            return line;
        }
        free(s);
        line++;
    } while (1);
    fclose(ptr);
    return 0;
}

void supprimer(char *fileName, personne *prs)
{
    FILE *ptr;
    FILE *temp;
    char c;
    int line;
    int currentLine = 1;

    ptr = fopen(fileName, "r");
    if (!ptr)
        return;
    temp = fopen("fileTemp.txt", "a+");
    if (!temp)
        return;
    line = Rechercher(fileName, prs);
    if (!line)
    {
        printf("element nexiste pas");
        return;
    }
    do
    {
        c = getc(ptr);
        if (line != currentLine && c != EOF)
            putc(c, temp);
        if (c == '\n')
            currentLine++;
    } while (c != EOF);
    fclose(ptr);
    fclose(temp);
    supprimerRep(fileName);
    rename("fileTemp.txt", fileName);
}

void ajouter(char *fileName, personne *prs)
{
    FILE *ptr;
    int i = 0;

    ptr = fopen(fileName, "a+");
    while (prs->nom[i])
    {
        putc(prs->nom[i], ptr);
        i++;
    }
    putc(';', ptr);
    i = 0;
    while (prs->prenom[i])
    {
        putc(prs->prenom[i], ptr);
        i++;
    }
    putc(';', ptr);
    i = 0;
    while (prs->num_tel[i])
    {
        putc(prs->num_tel[i], ptr);
        i++;
    }
    putc('\n', ptr);
    fclose(ptr);
}

void modifier(char *fileName, personne *ancien, personne *nouveau)
{
    if (Rechercher(fileName, ancien))
    {
        supprimer(fileName, ancien);
        ajouter(fileName, nouveau);
    }
}