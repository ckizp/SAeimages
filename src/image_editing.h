#ifndef IMAGE_EDITING_H_INCLUDED
#define IMAGE_EDITING_H_INCLUDED
#include <stdio.h>

// Structure définie par les trois composantes d'une couleur (RGB)
typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} color_t;

// Structure définie par la taille et les pixels de l'image
typedef struct {
    int width;
    int height;
    color_t** rgb;
} image_t;

// Lecture de chaque pixel de l'image (allocation dynamique) et de l'image en elle-même
image_t read_image(FILE* f, int width, int height);

// Libère la mémoire allouée lors de la lecture de l'image
void free_image(image_t img);

unsigned char grayscale(color_t);

void image_to_grayscale(image_t); //using luminosity method
void invert_image_colors(image_t); //absolute value of the RGB of the image and 255
void overlay(image_t, image_t); //average RGB of the two images
void image_to_monochromatic(image_t); //compares the average of the intensities to 127 and assigns 0 or 255
void get_contours(image_t, short int);

#endif // IMAGE_EDITING_H_INCLUDED
