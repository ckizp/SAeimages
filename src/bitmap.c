#include "bitmap.h"

void read_bmp_header(bmp_header_t* header, FILE* stream) {
    fread(header->type, sizeof(char[2]), 1, stream);
    fread(&header->file_size, 52, 1, stream);
}

void write_bmp_header(bmp_header_t* header, FILE* stream) {
    fwrite(header->type, sizeof(char[2]), 1, stream);
    fwrite(&header->file_size, 52, 1, stream);
}
