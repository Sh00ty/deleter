//
//  Htab.c
//  Deleter
//
//  Created by Павел on 05.07.2021.
//

#include "Htab.h"
#include <string.h>

int HtabAdd(Htab* Ht, FILE* fd, char* path)
{
    Htab* g = Ht;
    unsigned char* hash = (unsigned char *) malloc(65 * sizeof(unsigned char));
    if ( hash == NULL )
    {
        printf("\nCan't allocate memory HtabAdd");
        return -1;
    }
    if ( FileHash(fd, hash) == -1 )
    {
        free(hash);
        return -1;
    }
    
    Htab* add = HtabCreate();
    if ( add == NULL )
    {
        free(hash);
        return -1;
    }
    add->hash = hash;
    add->name = path;
    
    while ( g->next != NULL )
    {
        if ( g->hash != NULL )
        {
            if ( strcmp(g->hash, hash) == 0 )
            {
                add->next = g->next;
                g->next = add;
                return 0;
            }
        }
        g = g->next;
    }
    g->next = add;
    return 0;
}


Htab* HtabCreate(void)
{
    Htab* t = (Htab*) malloc(sizeof(Htab));
    if ( t == NULL )
    {
        printf("\nCan't create  Htab");
        return NULL;
    }
    t->hash = NULL;
    t->name = NULL;
    t->next = NULL;
    return t;
}


int HtabDel(Htab** Ht, char* path)
{
    Htab* prev = *Ht;
    Htab* g = *Ht;
    g = g->next;
    while ( g != NULL )
    {
        if ( strcmp(path, g->name) == 0 )
        {
            free (g->hash);
            prev->next = g->next;
            free (g);
            return 1;
        }
        prev = g;
        g = g->next;
    }
    printf("\nCan't find file:: %s", path);
    return 0;
}
