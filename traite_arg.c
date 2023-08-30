#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>

// GLOB VAR

extern int mask_ip;
extern char file_to_ano[255];
extern char dico[255];

// END OF GLOB VAR


void print_version () {
        printf ("fano version 2.0-1\n");
        printf ("quentin.bouyer@gmail.com\n");
}

void print_help () {
        printf ("Usage :\n"
                "-f file\t\t: mask a file , base on dictionary /etc/dic and white list /etc/dic.wl\n"
		"-d dic\t\t: specify an other dictionary to use ( instead of /etc/dic )\n"
		"-n \t\t: don't mask IP address\n"
                "-h\t\t: display help\n"
                "-v\t\t: display the version\n");
}

void parse_args (int argc, char **argv)
{
        int i;

        time_t datec;

        /* Au moins un argument */
	if (argc < 2) {
		print_help ();
		exit (EXIT_SUCCESS);
    	}

	/* Boucle d’analyse de la ligne de commande. */
        for (i = 1; i < argc; i++) {

		if (!strcmp (argv[i], "-n")) {
                        mask_ip = 0;
                }

		else if (!strcmp (argv[i], "-f")) {
			i++;
			if (i < argc) {
				strcpy (file_to_ano, argv[i]);
			}
		}

		else if (!strcmp (argv[i], "-d")) {
			i++;
                        if (i < argc) {
                                strcpy (dico, argv[i]);
                        }
		}

                else if (!strcmp (argv[i], "-v")) {
                        print_version ();
                        exit (EXIT_SUCCESS);
                }

                else if (!strcmp (argv[i], "-h")) {
                        print_help ();
                        exit (EXIT_SUCCESS);
                }

                /* Argument non reconnu. */
                else {
                        printf ("%s: Arg unknown\n",argv[i]);
                        printf ("-h for help\n");
                        exit (EXIT_FAILURE);
                }
        }
	
	if(strlen(file_to_ano) == 0) {
        	print_help();
        	exit (EXIT_FAILURE);
    	}

	if ( strlen(dico) == 0 ) {
        	strcpy(dico,"/etc/dic");
    	}

}
