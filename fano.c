#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "traite_arg.h"

// GLOBAL VAR

int mask_ip;
char file_to_ano[255];
char dico[255];


// GLOBAL VAR


int main(int argc, char *argv[]){
    FILE *fichier_entree;
    FILE *fichier_sortie;
    FILE *fichier_chaines_a_supprimer;
    FILE *fichier_chaines_a_garder;
    FILE *fichier_prov;
    char fichier_ano[255];
    char ligne[1000];
    char chaine_a_supprimer[100];
    char chainip[50];
    char chainipprov[50];
    int longueur_chaine_a_supprimer;
    long double pos;
    int i, j, stoken;

    char cmd[255] = {0};
    static const char GR[] = "\"([0-9][0-9][0-9][0-9]|[0-9][0-9][0-9]|[0-9][0-9]|[0-9])\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\"";

    char *resultat;

    // flag whitelist
    int whl;

    //dico whitelist
    char dico_wl[255];

    // nombre de modification
    int nbmod=0;

    // on initialise le premier caractere de file_to_ano et dico a 0
    file_to_ano[0] = 0;
    dico[0] = 0;

    // on masque les IP par defaut
    mask_ip = 1;

    //lecture des arguments
    parse_args (argc, argv);

    //printf ("%s %s\n",file_to_ano,dico);

    // Ouvrir le fichier d'entrée en mode lecture
    fichier_entree = fopen(file_to_ano, "r");
    if (fichier_entree == NULL) {
        printf("Unable to open %s\n",file_to_ano);
        exit(1);
    }

    strcpy(fichier_ano, file_to_ano);
    strcat(fichier_ano, ".ano");

    // Ouvrir le fichier de sortie en mode écriture
    fichier_sortie = fopen(fichier_ano, "w");
    if (fichier_sortie == NULL) {
        printf("Unable to open %s.ano\n",file_to_ano);
        exit(1);
    }

    // Verifier si le fichier contenant les chaînes à supprimer existe (dico)
    fichier_chaines_a_supprimer = fopen(dico, "r");
    if (fichier_chaines_a_supprimer == NULL) {
        printf("Unable top open dictionary %s\n",dico);
        exit(1);
    }
    fclose(fichier_chaines_a_supprimer);

    strcpy(dico_wl, dico);
    strcat(dico_wl, ".wl");
    // Verifier si le fichier contenant les chaînes à ne pas supprimer existe (dico.wl)
    fichier_chaines_a_garder = fopen(dico_wl, "r");
    if (fichier_chaines_a_garder == NULL) {
	printf("No white list\n");
        whl=0;
    }
    else {
	whl = 1;
	printf("White List = %s\n",dico_wl);
    	fclose(fichier_chaines_a_supprimer);
    }

    // On construit le fichier dictionnaire /tmp/dic.prov qui contient tout ce qui ressemble a une ip si mask_ip > 0

    if ( mask_ip > 0 ) {

    	sprintf(cmd,"grep -E -o %s %s > /tmp/dic.tmp 2>/dev/null", GR, file_to_ano); 
    	system (cmd);

	// remise a 0 de cmd
	memset(cmd, 0, sizeof(cmd));

	if ( whl > 0 ) {
		// on cree /tmp/dic.prov en retirant la white list de /tmp/dic.prov
		sprintf(cmd,"grep -v -f %s /tmp/dic.tmp > /tmp/dic.prov 2>/dev/null", dico_wl);
		system (cmd);
	} else {
		system ("cp /tmp/dic.tmp /tmp/dic.prov >/dev/null 2>&1");
	}
	
    	// on ouvre le fichier /tmp/dic.prov pour voir si c'est une adresse IP valide
    	fichier_prov = fopen("/tmp/dic.prov", "r"); 

    	// on ouvre le fichier /tmp/dic qu'on va ecrire
    	fichier_chaines_a_supprimer = fopen("/tmp/dic", "w");
   
    	// on verifie chaque entree de /tmp/dic.prov pour voir si c'est bien un ip valide
    	while (fgets(chainip, 50, fichier_prov)) {
		struct in_addr addr;

        	// on supprime le caractere fin de ligne
        	chainip[strcspn(chainip, "\n")] = 0;

		strcpy(chainipprov, chainip);
		//printf("chainip=%s chainipprov=%s\n", chainip, chainipprov);
 		char *token = strtok(chainipprov, ".");
        	stoken = strlen (token);
        	//printf("ip=%s premier digit de l'ip = %s avec %d digits\n", chainip, token, stoken);
        
		if ( inet_aton(chainip, &addr) != 0 && stoken < 4 ) {
			fprintf(fichier_chaines_a_supprimer,"%s\n",chainip);
		}
		memset(chainip, 0, sizeof(chainip));
		memset(chainipprov, 0, sizeof(chainipprov));
    	}

    	fclose(fichier_prov);
    	fclose(fichier_chaines_a_supprimer);
    }

    // on ajoute /etc/dic a /tmp/dic
    system("cat /etc/dic >> /tmp/dic");

    // on ouvre le dic qu'on a construit /tmp/dic
    fichier_chaines_a_supprimer = fopen("/tmp/dic", "r");

    printf("Begining of anonymization ..\n");

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
				nbmod++;
                        }
			
                }

        }

        // Rembobiner le fichier d'entrée pour recommencer au début
        rewind(fichier_chaines_a_supprimer);

        // ecriture fichier ano
        fprintf(fichier_sortie,"%s\n",ligne);
    }
    if ( nbmod > 1 ) {
    	printf("%d modifications\n", nbmod);
    } else {
		printf("%d modification\n", nbmod);
    }
    printf("End of anonymization\n");
    printf("Anonymized file is %s\n", fichier_ano);
    

    // Fermer les fichiers
    fclose(fichier_entree);
    fclose(fichier_sortie);
    fclose(fichier_chaines_a_supprimer);
    system("rm -f /tmp/dic.tmp >/dev/null 2>&1");
    system("rm -f /tmp/dic.prov >/dev/null 2>&1");
    system("rm -f /tmp/dic >/dev/null 2>&1");

    return 0;
}
