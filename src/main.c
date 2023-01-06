#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "image_editing.h"
#include "bitmap.h"*

//  using MAJERLE's code style
//  https://github.com/MaJerle/c-code-style

char* path;

int main(int argc, char* argv[]) {
    FILE* f_in;
    bmp_header_t header;
    image_t img, img2;

    // i est un compteur (pour les boucles) et choice le choix de l'utilisateur pour le traitement
    short int i, choice;

    // end_path va sauvegarder la taille du chemin (chaîne de caractères) vers le répertoire où sont les images
    short int end_path;

    // Allocation dynamique de 256 octets de mémoire et assigne l'adresse de cette mémoire à la variable path
    path = malloc(256);

    // retourne -2 si l'allocation échoue, cela signifie que le fichier ne pourra pas être ouvert
    if (path == NULL) return -2;

    switch (argc) {
        case 4:
            strcpy(path, argv[1]);
            // Au cas où l'utilisateur oublie de mettre un slash pour accéder au répertoire des images
            strcat(path, "\\");
            strcat(path, argv[3]);
            f_in = fopen(path, "rb");

            // retourne -2 si l’un des fichiers fournis n’existe pas ou ne peut être ouvert
            if (f_in == NULL) {
                free(path);
                return -2;
            }

            read_bmp_header(&header, f_in);
            img = read_image(f_in, header.width, header.height);

            // argv est un tableau de chaînes de caractères, ici on transforme le troisième élément de ce tableau
            // (censé représenter une valeur entière) en une valeur numérique
            choice = atoi(argv[2]);
            break;
        case 5:
            // Chemin du premier fichier BMP
            strcpy(path, argv[1]);
            // Au cas où l'utilisateur oublie de mettre un slash pour accéder au répertoire des images
            strcat(path, "\\");
            end_path = strlen(path);
            strcat(path, argv[3]);

            f_in = fopen(path, "rb");
            // retourne -2 si l’un des fichiers fournis n’existe pas ou ne peut être ouvert
            if (f_in == NULL) {
                free(path);
                return -2;
            }

            read_bmp_header(&header, f_in);
            img = read_image(f_in, header.width, header.height);

            // Chemin du deuxième fichier BMP
            // path est une adresse, on copie argv[4] à l'adresse path+end_path pour ne pas écraser le chemin
            strcpy(path + end_path, argv[4]);

            f_in = freopen(path, "rb", f_in);
            // retourne -2 si l’un des fichiers fournis n’existe pas ou ne peut être ouvert
            if (f_in == NULL) {
                free_image(img);
                free(path);
                return -2;
            }

            // N'ayant pas lu l'entête du deuxième fichier, il faut se placer après celle-ci
            fseek(f_in, 54, SEEK_SET);
            
            img2 = read_image(f_in, header.width, header.height);

            // transforme le troisième élément de argv en une valeur numérique
            choice = atoi(argv[2]);
            break;
        default:
            printf("Bienvenue dans notre programme de traitement d'image !\n");
            printf("Voici la liste des traitements actuellement disponibles :\n");

            printf(" 1 - Image en niveaux de gris\n");
            printf(" 2 - Inversion des couleurs de l'image\n");
            printf(" 3 - Image en monochrome\n");
            printf(" 4 - Extraction des contours de l'image\n");
            printf(" 5 - Superposition de deux images\n");

            printf("\nQuel est le chemin du r%cpertoire ? ", 130);
            fgets(path, 256, stdin);
            // strcspn(path, "\n")] renvoie la position du premier saut de ligne dans la chaîne de caractère path.
            // Ainsi, on remplace ce saut de ligne par le caractère nul ayant une valeur de zéro
            path[strcspn(path, "\n")] = 0;
            // Au cas où l'utilisateur oublie de mettre un slash pour accéder au répertoire des images
            strcat(path, "\\");
            end_path = strlen(path);

            printf("Choisissez le num%cro du traitement souhait%c : ", 130, 130);
            scanf("%hd", &choice);
            getchar();

            printf("Quel est le nom du %sfichier %c traiter ? ", ((choice) == (4) ? ("1er ") : ("")), 133);
            fgets(path + end_path, 256 - end_path, stdin);
            path[strcspn(path, "\n")] = 0;
            f_in = fopen(path, "rb");

            // retourne -2 si l’un des fichiers fournis n’existe pas ou ne peut être ouvert
            if (f_in == NULL) {
                free(path);
                return -2;
            }

            read_bmp_header(&header, f_in);
            img = read_image(f_in, header.width, header.height);

            // On demande le deuxième fichier BMP si l'utilisateur souhaite une superposition d'images (5)
            if (choice == 5) {
                printf("Quel est le nom du 2%cme fichier %c traiter ? ", 138, 133);
                fgets(path + end_path, 256 - end_path, stdin);
                path[strcspn(path, "\n")] = 0;
                freopen(path, "rb", f_in);

                // retourne -2 si l’un des fichiers fournis n’existe pas ou ne peut être ouvert
                if (f_in == NULL) {
                    free_image(img);
                    free(path);
                    return -2;
                }

                // N'ayant pas lu l'entête du deuxième fichier, il faut se placer après celle-ci
                fseek(f_in, 54, SEEK_SET);

                img2 = read_image(f_in, header.width, header.height);
            }
            break;
    }

    // Effectue le traitement voulu par l'utilisateur (choice)
    switch (choice) {
        case 1:
            image_to_grayscale(img);
            break;
        case 2:
            invert_image_colors(img);
            break;
        case 3:
            image_to_monochromatic(img);
            break;
        case 4:
            get_contours(img, 100);
            break;
        case 5:
            overlay(img, img2);
            break;
        default:
            // retourne -1 si le traitement spécifié n'existe pas
            free_image(img);
            free(path);
            return -1;
            break;
    }
    // Une fois des fichiers ouverts, il est d'usage de les fermer...
    fclose(f_in);

    // Une fois les traitements effectués, on créé un fichier BMP qui sera
    // tout simplement le résultat de ces traitements
    FILE* f_out = fopen("result.bmp", "wb");

    // retourne -3 si le fichier de sortie result.bmp ne peut pas être écrit
    if (f_out == NULL) {
        free_image(img);
        if (choice == 5)
            free_image(img2);
        free(path);
        return -3;
    }

    write_bmp_header(&header, f_out);
    for (i = 0; i < img.height; ++i)
        fwrite(img.rgb[i], img.width, sizeof(color_t), f_out);
    fclose(f_out);

    // Libère la mémoire allouée tout au long du programme
    free_image(img);
    if (choice == 5)
        free_image(img2);
    free(path);

    return 0;
}
