//vector.h
#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include "pixel.h"
#define size_vec sizeof(unsigned char) * 5

typedef unsigned char *vec;

int char_compare( const void* a, const void* b);
bool is_out_of_bond(size_t width, size_t height, size_t x, size_t y);
vec init_vec(unsigned char *img, size_t width, size_t height, struct pos p);
double get_euclidean_dist(vec massCenter, vec v);
vec create_vec_same(unsigned char val);
vec copy_vec(vec vector);

#endif
