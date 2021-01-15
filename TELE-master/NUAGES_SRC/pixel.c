//pixel.c
#include <stdlib.h>
#include <err.h>

#include "pixel.h"

unsigned char get_pixel(unsigned char *img, size_t width, size_t height, struct pos p)
{
    if (p.x < width && p.y < height)
        return img[((width * p.y) + p.x) * 3];
    errx(1, "get_pixed() failed");
}


unsigned char *get_pixel_pointer(unsigned char *img, size_t width, size_t height, struct pos p)
{
    if (p.x < width && p.y < height)
        return img + (((width * p.y) + p.x) * 3);
    return NULL;
}


void set_pixel(unsigned char *img, size_t width, size_t height, struct pos p, struct pixel pix)
{
    struct pixel *pixel = (struct pixel*) get_pixel_pointer(img, width, height, p);
    if (!pixel)
        errx(1, "Pixel not found in set_pixel()");
    pixel->red = pix.red;
    pixel->green = pix.green;
    pixel->blue = pix.blue;
    return;
}
