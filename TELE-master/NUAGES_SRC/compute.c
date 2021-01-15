//compute.c
#include <gtk/gtk.h>
#include <stdio.h>
#include <time.h>

#include "compute.h"
#include "vector.h"
#include "pixel.h"
#include "cloud.h"

/*******************************************************
  IL EST FORMELLEMENT INTERDIT DE CHANGER LE PROTOTYPE
  DES FONCTIONS
 *******************************************************/


/*---------------------------------------
Proto: 


But: 

Entrees: 
--->le tableau des valeurs des pixels de l'image d'origine
(les lignes sont mises les unes ? la suite des autres)
--->le nombre de lignes de l'image,
--->le nombre de colonnes de l'image,
--->le tableau des valeurs des pixels de l'image resultat
(les lignes sont mises les unes ? la suite des autres)


Sortie:

Rem: 

Voir aussi:

---------------------------------------*/
void ComputeImage(guchar *pucImaOrig, guint NbCol, guint NbLine, guchar *pucImaRes)
{
    clock_t begin = clock();
    int iNbPixelsTotal, iNumPix;
    int iNumChannel, iNbChannels = 3; /* on travaille sur des images couleurs*/
    guchar ucMeanPix;

    iNbPixelsTotal = NbCol*NbLine;
    for(iNumPix = 0; iNumPix < iNbPixelsTotal * iNbChannels; iNumPix += iNbChannels)
    {
        /*moyenne sur les composantes RVB */
        ucMeanPix = (unsigned char) ((*(pucImaOrig + iNumPix) 
                                    + *(pucImaOrig + iNumPix + 1) 
                                    + *(pucImaOrig + iNumPix + 2)) / 3);


        /* sauvegarde du resultat */
        for(iNumChannel = 0; iNumChannel < iNbChannels; iNumChannel++)
            *(pucImaRes + iNumPix + iNumChannel) = ucMeanPix;
    }


    double prop = cloud(pucImaRes, NbLine, NbCol);

    double time = ((clock_t)clock() - begin) / (double)(CLOCKS_PER_SEC );
    printf("Time: %lfs\nPercentage of cloud found: %lf%%\n", time, prop * 100);

}
