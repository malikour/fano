#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *fichier_entree;
    FILE *fichier_sortie;
    FILE *fichier_chaines_a_supprimer;
    char fichier_ano[100];
    char ligne[1000];
    char chaine_a_supprimer[100];
    int longueur_chaine_a_supprimer;
    long double pos;
    int i, j;

    char *resultat;

    if (argc != 2) {
        printf("Usage: %s file_to_anonymize\n", argv[0]);
        printf("/etc/dic is a text file which contains all strings to remove\n");
        return 1;
    }

    // Ouvrir le fichier d'entrée en mode lecture
    fichier_entree = fopen(argv[1], "r");
    if (fichier_entree == NULL) {
        printf("Unable to open input file %s\n",argv[1]);
        exit(1);
    }

    strcpy(fichier_ano, argv[1]);
    strcat(fichier_ano, ".ano");

    // Ouvrir le fichier de sortie en mode écriture
    fichier_sortie = fopen(fichier_ano, "w");
    if (fichier_sortie == NULL) {
        printf("Unable to open output file %s.ano\n",argv[1]);
        exit(1);
    }

    // Ouvrir le fichier contenant les chaînes à supprimer en mode lecture
    fichier_chaines_a_supprimer = fopen("/etc/dic", "r");
    if (fichier_chaines_a_supprimer == NULL) {
        printf("Unable to open dictionary file /etc/dic\n");
        exit(1);
    }


    // Parcourir chaque ligne du fichier d'entrée
    while (fgets(ligne, 1000, fichier_entree)) {

        // on supprime le caractere fin de ligne
        ligne[strcspn(ligne, "\n")] = 0;

        // Parcourir chaque ligne du fichier contenant les chaînes à supprimer
        while (fgets(chaine_a_supprimer, 100, fichier_chaines_a_supprimer)) {

                // on supprime le caractere fin de ligne
                chaine_a_supprimer[strcspn(chaine_a_supprimer, "\n")] = 0;

                longueur_chaine_a_supprimer = strlen(chaine_a_supprimer);

                if ( longueur_chaine_a_supprimer > 0 ) {

                        // on recherche la chaine a supprimer dans entree, en boucle pour supprimer toute les occurences
                        while ( ( resultat = strstr(ligne, chaine_a_supprimer) ) != NULL ) {
                                pos = resultat - ligne;
                                i = (int) pos;

                                // anonymisation
                                for (j=i; j < i + longueur_chaine_a_supprimer; j++) {
                                        ligne[j]='X';
                                }
                        }
                }

        }
        // Rembobiner le fichier d'entrée pour recommencer au début
        rewind(fichier_chaines_a_supprimer);

        // ecriture fichier ano
        fprintf(fichier_sortie,"%s\n",ligne);
    }

    // Fermer les fichiers
    fclose(fichier_entree);
    fclose(fichier_sortie);
    fclose(fichier_chaines_a_supprimer);

    return 0;
}
