#include <dirent.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include "compute.h"

int main(void)
{

    char *name_dir;
    DIR *dir = opendir("../IMAGES");
    if (dir == NULL)
    {
        dir = opendir("../../IMAGES");
        name_dir = "../../IMAGES";
    }
    else
    {
        name_dir = "../IMAGES";
    }
    
    if (dir == NULL)
    {
        printf("No directory found\n");
        return 0;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)))
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
        {
            continue;
        }
        char path[4096] = "";
        char buf[4096] = "";
        strcat(path, name_dir);
        strcat(path, "/");
        strcat(path, entry->d_name);
        realpath(path, buf);
        printf("-------------------------------------------\n");
        printf("Processing Image %s\n", entry->d_name);

        GError *error;
        guint NbCol, NbLine;
        guchar *pucImaOrig, *pucImaRes;
        GdkPixbuf *pGdkPixbufImaOrig, *pGdkPixbufImaRes;
        pGdkPixbufImaOrig = gdk_pixbuf_new_from_file(buf, &error);
        pGdkPixbufImaRes = gdk_pixbuf_copy(pGdkPixbufImaOrig);
        NbCol = gdk_pixbuf_get_width(pGdkPixbufImaOrig);
        NbLine = gdk_pixbuf_get_height(pGdkPixbufImaOrig);
        pucImaOrig = gdk_pixbuf_get_pixels(pGdkPixbufImaOrig);
        pucImaRes = gdk_pixbuf_get_pixels(pGdkPixbufImaRes);

        ComputeImage(pucImaOrig, NbLine, NbCol, pucImaRes);
    }
    closedir(dir);
    return 0;
}