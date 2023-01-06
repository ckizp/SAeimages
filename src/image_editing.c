#include "image_editing.h"
#include <math.h>
#include <stdlib.h>

extern char* path;

image_t read_image(FILE* f, int width, int height) {
    short int i;
    image_t img;
    img.width = width;
    img.height = height;
    img.rgb = (color_t**) malloc(height * sizeof(void*));
    // retourne -1 si l'allocation se passe mal, de ce fait le traitement ne pourra pas bien se dérouler
    if (img.rgb == NULL) exit(-1);
    for (i = 0; i < height; ++i) {
        img.rgb[i] = (color_t*) malloc(width * sizeof(color_t));
        // Libère toute la mémoire allouée jusqu'ici si l'allocation se passe mal et retourne -1
        if (img.rgb[i] == NULL) {
            short int j;
            for (j = 0; j < i; j++)
                free(img.rgb[j]);
            free(img.rgb);
            free(path);
            exit(-1);
        }
        fread(img.rgb[i], width, sizeof(color_t), f);
    }
    return img;
}

void free_image(image_t img) {
    short int i;
    for (i = 0; i < img.height; ++i)
        free(img.rgb[i]);
    free(img.rgb);
}

unsigned char grayscale(color_t rgb) {
    return 0.3 * rgb.blue + 0.59 * rgb.green + 0.11 * rgb.red;
}

void image_to_grayscale(image_t img) {
    short int x, y;
    for (y = 0; y < img.height; ++y) {
        for (x = 0; x < img.width; ++x) {
            img.rgb[x][y].red = img.rgb[x][y].green = img.rgb[x][y].blue = grayscale(img.rgb[x][y]);
        }
    }
}

void invert_image_colors(image_t img) {
    short int x, y;
    for (y = 0; y < img.height; ++y) {
        for (x = 0; x < img.width; ++x) {
            img.rgb[x][y].red = abs(img.rgb[x][y].red - 255);
            img.rgb[x][y].green = abs(img.rgb[x][y].green - 255);
            img.rgb[x][y].blue = abs(img.rgb[x][y].blue - 255);
        }
    }
}

void overlay(image_t img1, image_t img2) {
    if(img1.width == img2.width && img1.height == img2.height) {
        short int x, y;
        for (y = 0; y < img1.height; ++y) {
            for (x = 0; x < img1.width; ++x) {
                img1.rgb[x][y].red = (img1.rgb[x][y].red + img2.rgb[x][y].red)/2;
                img1.rgb[x][y].green = (img1.rgb[x][y].green + img2.rgb[x][y].green)/2;
                img1.rgb[x][y].blue = (img1.rgb[x][y].blue + img2.rgb[x][y].blue)/2;
            }
        }
    }
}

void image_to_monochromatic(image_t img) {
    short int x, y;
    unsigned char average;
    for (y = 0; y < img.height; ++y) {
        for (x = 0; x < img.width; ++x) {
            img.rgb[x][y].red = img.rgb[x][y].green = img.rgb[x][y].blue = ((grayscale(img.rgb[x][y])) > (127) ? (255) : (0));
        }
    }
}

void get_contours(image_t img, short int threshold) {
    short int x, y;
    short int gx, gy;
    short int g[img.width][img.height];
    image_to_grayscale(img);
    // => img.rgb[y][x].red = img.rgb[y][x].green = img.rgb[y][x].blue
    for (y = 1; y < img.height-1; ++y) {
        for (x = 1; x < img.width-1; ++x) {
            gx =  abs(-(img.rgb[x-1][y-1].red + img.rgb[x][y-1].red + img.rgb[x+1][y-1].red) +
            (img.rgb[x-1][y+1].red + img.rgb[x][y+1].red + img.rgb[x+1][y+1].red));

            gy =  abs(-(img.rgb[x-1][y-1].red + img.rgb[x-1][y].red + img.rgb[x-1][y+1].red) +
            (img.rgb[x+1][y-1].red + img.rgb[x+1][y].red + img.rgb[x+1][y+1].red));

            g[x][y] = (sqrt(pow(gx, 2) + pow(gy, 2)) < (threshold) ? (255) : (0));
        }
    }
    for (y = 1; y < img.height-1; ++y) {
        for (x = 1; x < img.width-1; ++x) {
            img.rgb[x][y].red = img.rgb[x][y].green = img.rgb[x][y].blue = g[x][y];
        }
    }
}
