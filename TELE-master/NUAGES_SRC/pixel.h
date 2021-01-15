//pixel.h
#ifndef PIXEL_H
#define PIXEL_H

#include <stddef.h>

struct pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct pos {
    size_t x;
    size_t y;
};

unsigned char get_pixel(unsigned char *img, size_t width, size_t height, struct pos p);
void set_pixel(unsigned char *img, size_t width, size_t height, struct pos p, struct pixel pix);

#endif
