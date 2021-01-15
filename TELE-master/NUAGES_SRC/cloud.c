//cloud.c

#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "pixel.h"


struct point_vec {
    vec v;
    struct pos p; 
};


struct point_vec * add_pv(struct point_vec *pv, struct point_vec pv_add, size_t *size)
{
    pv = realloc(pv, (*size + 1) * sizeof(struct point_vec));
    pv[*size] = pv_add;
    *size += 1;
    return pv;
}


static int cmp_pv(const void *pv0, const void *pv1)
{
    vec v0 = ((struct point_vec *)pv0)->v;
    vec v1 = ((struct point_vec *)pv1)->v;
    return (v0[0] + v0[1] + v0[2] + v0[3] + v0[4]) 
         - (v1[0] + v1[1] + v1[2] + v1[3] + v1[4]);
}


vec median(struct point_vec *pv, size_t size)
{
    qsort(pv, size, sizeof(struct point_vec), cmp_pv);
    return pv[size / 2].v;
}


double cloud(unsigned char *img, size_t width, size_t height)
{
    vec class_cloud_mass = create_vec_same(255);
    vec class_other_mass = create_vec_same(180);
    vec class_trois_mass = create_vec_same(110);
    vec class_quatre_mass = create_vec_same(40);
    vec tmp_class_cloud_mass = NULL;
    vec tmp_class_other_mass = NULL;
    vec tmp_class_trois_mass = NULL;
    vec tmp_class_quatre_mass = NULL;
    struct point_vec *cloud_pv = NULL;
    struct point_vec *other_pv = NULL;
    struct point_vec *trois_pv = NULL;
    struct point_vec *quatre_pv = NULL;
    size_t class_cloud_size = 0;
    size_t class_other_size = 0; 
    size_t class_trois_size = 0; 
    size_t class_quatre_size = 0; 

    int loop = 0;

    struct pixel magenta_pixel = {255, 0, 255};
    struct pixel red_pixel = {255,0, 0};
    struct pixel cyan_pixel = {0, 255, 255};
    struct pixel blue_pixel = {0,0, 255};

    do 
    {
        free(tmp_class_cloud_mass);
        free(tmp_class_other_mass);
        free(tmp_class_trois_mass);
        free(tmp_class_quatre_mass);
        
        class_cloud_size = 0;
        class_other_size = 0;
        class_trois_size = 0;
        class_quatre_size = 0;

        
        for (size_t x = 0; x < width; x++)
        {
            for (size_t y = 0; y < height; y++)
            {
                struct pos p = {x, y};
                struct point_vec pv = {init_vec(img, width, height, p), p};
                
                double euclidean_cloud = get_euclidean_dist(class_cloud_mass, pv.v);
                double euclidean_other = get_euclidean_dist(class_other_mass, pv.v);
                double euclidean_trois = get_euclidean_dist(class_trois_mass, pv.v);
                double euclidean_quatre = get_euclidean_dist(class_quatre_mass, pv.v);

                if (euclidean_cloud <= euclidean_other)
                {
                    if (euclidean_cloud <= euclidean_trois && euclidean_trois
                        <= euclidean_quatre);
                        cloud_pv = add_pv(cloud_pv, pv, &class_cloud_size);
                   
                }
                else if (euclidean_other <= euclidean_trois && euclidean_other
                    <= euclidean_quatre)
                    other_pv = add_pv(other_pv, pv, &class_other_size);
                else if (euclidean_trois <= euclidean_quatre) 
                    trois_pv = add_pv(trois_pv, pv, &class_trois_size);
                else 
                    quatre_pv = add_pv(quatre_pv, pv, &class_quatre_size);
            }
        }

        
        tmp_class_cloud_mass = copy_vec(class_cloud_mass);
        tmp_class_other_mass = copy_vec(class_other_mass);
        tmp_class_trois_mass = copy_vec(class_trois_mass);
        tmp_class_quatre_mass = copy_vec(class_quatre_mass);
       

        if (class_cloud_size)
        {
            free(class_cloud_mass);
            class_cloud_mass = copy_vec(median(cloud_pv, class_cloud_size));
        }
        if (class_other_size)
        {
            free(class_other_mass);
            class_other_mass = copy_vec(median(other_pv, class_other_size));
        }
        if (class_trois_size)
        {
            free(class_trois_mass);
            class_trois_mass = copy_vec(median(trois_pv, class_trois_size));
        }
        
        if (class_quatre_size)
        {
            free(class_quatre_mass);
            class_quatre_mass = copy_vec(median(quatre_pv, class_quatre_size));
        }

        loop++;
        if (loop >= 20)
            break;


    } while (get_euclidean_dist(class_cloud_mass, tmp_class_cloud_mass) >= 3
          && get_euclidean_dist(class_other_mass, tmp_class_other_mass) >= 3
          && get_euclidean_dist(class_quatre_mass, tmp_class_other_mass) >= 3
          && get_euclidean_dist(class_trois_mass, tmp_class_trois_mass) >= 3);

    
    for (size_t i = 0; i < class_cloud_size; i++)
        set_pixel(img, width, height, cloud_pv[i].p, red_pixel);
    for (size_t i = 0; i < class_other_size; i++)
        set_pixel(img, width, height, other_pv[i].p, magenta_pixel);
    for (size_t i = 0; i < class_trois_size; i++)
        set_pixel(img, width, height, trois_pv[i].p, cyan_pixel);
    for (size_t i = 0; i < class_quatre_size; i++)
        set_pixel(img, width, height, quatre_pv[i].p, blue_pixel);


    free(class_cloud_mass);
    free(class_other_mass);
    free(class_trois_mass);
    free(class_quatre_mass);
    free(tmp_class_cloud_mass);
    free(tmp_class_other_mass);
    free(tmp_class_trois_mass);
    free(tmp_class_quatre_mass);
    free(cloud_pv);
    free(other_pv);
    free(trois_pv);
    free(quatre_pv);

    return (double)(class_cloud_size + class_other_size) / (double)(class_cloud_size +
    class_other_size + class_trois_size + class_quatre_size);
}
