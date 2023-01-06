#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED
#include <stdio.h>

typedef struct { // total size of the fields of the structure "bmp_header" : 54 bytes
    unsigned char type[2];
    unsigned int file_size;
    unsigned int reserved;
    unsigned int data_offset;
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short int planes;
    unsigned short int bit_count;
    unsigned int compression;
    unsigned int image_size;
    unsigned int x_pixels_per_m;
    unsigned int y_pixels_per_m;
    unsigned int colors_used;
    unsigned int colors_important;
} bmp_header_t;

// Lecture de l'en-tête du fichier BMP (de FILE* vers bmp_header_t)
void read_bmp_header(bmp_header_t*, FILE*);

// Écriture de l'en-tête du fichier BMP (de bmp_header_t vers FILE*)
void write_bmp_header(bmp_header_t*, FILE*);

#endif // BITMAP_H_INCLUDED
