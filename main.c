#include "headerPrgSys.h"

int main(int argc, char const *argv[])
{
    personne *prs1;
    personne *prs2;
    char * usms = "./USMS/";

    prs1 = malloc(sizeof(personne));
    prs2 = malloc(sizeof(personne));

    if (argc < 3)
        return -1;

    if (!strcmp(argv[1], "lister"))
    {
        if (!strcmp(argv[2],"a"))
        {
            for (int i = 3; i < argc; i++)
            {
                if(!strcmp(argv[i],"USMS"))
                    listerContenu(argv[i]);
                else
                    listerContenu(join(usms , argv[i]));
            }
        }
        else if (!strcmp(argv[2],"o"))
        {
            for (int i = 3; i < argc; i++)
            {
                if(!strcmp(argv[i],"USMS"))
                    listerOrdonne(argv[i]);
                else
                    listerOrdonne(join(usms , argv[i]));
            }
        }
    }
    if (!strcmp(argv[1], "afficher"))
    {
        for (int i = 2; i < argc; i++)
            afficherFichier(join(usms , argv[i]));
    }
    if (strcmp(argv[1], "creer") == 0)
    {
        for (int i = 2; i < argc; i++)
            creerRep(join(usms , argv[i]));
    }
    if (!strcmp(argv[1], "supprimerRep"))
    {
        for (int i = 2; i < argc; i++)
            supprimerRep(join(usms , argv[i]));
    }
    if (!strcmp(argv[1], "rechercher"))
    {
        prs1->nom = strdup(argv[2]);
        prs1->prenom = strdup(argv[3]);
        prs1->num_tel = strdup(argv[4]);
        int n = Rechercher(join(usms , argv[5]), prs1);
        if(n)
            printf("cette personne existe dans la line %d", n);
        else
            printf("cette personne n'existe pas");   
    }
    if (!strcmp(argv[1], "supprimer"))
    {
        prs1->nom = strdup(argv[2]);
        prs1->prenom = strdup(argv[3]);
        prs1->num_tel = strdup(argv[4]);
        supprimer(join(usms , argv[5]), prs1);
    }
    if (!strcmp(strdup(argv[1]), "ajouter"))
    {
        prs1->nom = strdup(argv[2]);
        prs1->prenom = strdup(argv[3]);
        prs1->num_tel = strdup(argv[4]);
        ajouter(join(usms , argv[5]), prs1);
    }
    if (!strcmp(strdup(argv[1]), "modifier"))
    {
        prs1->nom = strdup(argv[2]);
        prs1->prenom = strdup(argv[3]);
        prs1->num_tel = strdup(argv[4]);
        prs2->nom = strdup(argv[5]);
        prs2->prenom = strdup(argv[6]);
        prs2->num_tel = strdup(argv[7]);
        modifier(join(usms , argv[8]), prs1,prs2);
    }
    return 0;
}
