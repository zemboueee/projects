//vector.c

#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "pixel.h"
#include "vector.h"

int char_compare( const void* a, const void* b)
{
    return (*(unsigned char *)b) - (*(unsigned char *)a);   
}

bool is_out_of_bond(size_t width, size_t height, size_t x, size_t y)
{
    if (x >= width || y >= height)
    {
        return true;
    }
    return false;
}

vec init_vec(unsigned char *img, size_t width, size_t height, struct pos p)
{
    vec v = malloc(size_vec);
    int total;
    if (!is_out_of_bond(width, height, p.x, p.y))
    {
        v[0] = get_pixel(img, width, height, p);
    }
    else
    {
        v[0] = 0;
    }
    total = is_out_of_bond(width, height, p.x, p.y);
    if (!is_out_of_bond(width, height, p.x + 1, p.y))
    {
        v[1] = get_pixel(img, width, height, (struct pos){p.x + 1, p.y});
    }
    else
    {
        v[1] = 0;
    }
    total += is_out_of_bond(width, height, p.x + 1, p.y);
    if (!is_out_of_bond(width, height, p.x, p.y + 1))
    {
        v[2] = get_pixel(img, width, height, (struct pos){p.x, p.y + 1});
    }
    else
    {
        v[2] = 0;
    }
    total += is_out_of_bond(width, height, p.x, p.y + 1);
    if (!is_out_of_bond(width, height, p.x - 1, p.y))
    {
        v[3] = get_pixel(img, width, height, (struct pos){p.x - 1, p.y});
    }
    else
    {
        v[3] = 0;
    }
    total += is_out_of_bond(width, height, p.x - 1, p.y);
    if (!is_out_of_bond(width, height, p.x, p.y - 1))
    {
        v[4] = get_pixel(img, width, height, (struct pos){p.x, p.y - 1});
    }
    else
    {
        v[4] = 0;
    }
    total += is_out_of_bond(width, height, p.x, p.y - 1);
    size_t sum = v[0] + v[1] + v[2] + v[3] + v[4];
    bool check = false;
    for (size_t i = 0; i < 5; i++)
    {
        if (v[i] == 0)
        {
            check = true;
        }
        break;
    }
    unsigned char avg;
    if (check)
    {
        avg = sum / (5 - total);
    }
    for (size_t i = 0; i < 5; i++)
    {
        if (v[i] == 0)
        {
            v[i] = avg;
        }
    }
    qsort(v, 5, sizeof(unsigned char), char_compare);
    return v;
}


double get_euclidean_dist(vec massCenter, vec v)
{
    double res = 0;
    for (size_t i = 0; i < 5; i++)
    {
        res += (double)pow(massCenter[i] - v[i], 2);
    }
    return sqrt(res);
}

vec create_vec_same(unsigned char val)
{
    vec v = malloc(size_vec);
    memset(v, val, 5);
    return v;
}


vec copy_vec(vec vector)
{
    vec v = malloc(size_vec);
    memcpy(v, vector, size_vec);
    return v;
}
