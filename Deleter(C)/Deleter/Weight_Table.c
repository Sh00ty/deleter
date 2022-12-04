//
//  Weight_Table.c
//  Deleter
//
//  Created by Павел on 04.07.2021.
//

#include "Weight_Table.h"


size_t hash(size_t* weight, FILE* fd)
{
    fseek(fd, 0, SEEK_END);
    *weight = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    return (*weight * 37) % TABLE_COUNT;
}


Wtab* WtabCreate(size_t size)
{
    size = TABLE_COUNT * sizeof (Wtab);
    Wtab* T = (Wtab*) malloc(size);
    if ( T == NULL )
    {
        printf("\nCan't allocate Wtab");
        return NULL;
    }
    
    for (int i = 0; i < TABLE_COUNT; ++i)
        T->next = NULL;
    return T;
}

// return -1 if it can't add to Htab
// return -2 if cant allocate memory
int WtabAdd (Wtab* T, FILE* fd, char* filepath)
{
    size_t weight = 0;
    size_t h = hash(&weight, fd);

    if ( T[h].next == NULL )
    {
        T[h].next = (ll*) malloc(sizeof(ll));
        if ( T[h].next == NULL )
        {
            printf("\nCan't allocte memory for ll during adding to Wtab");
            return -2;
        }
        // here is a dangerous place with . and ->
        T[h].next->next = NULL;
        T[h].next->weight = weight;
        T[h].next->Htab = HtabCreate();
        if ( T[h].next->Htab == NULL ) return -2;
        
        if ( HtabAdd(T[h].next->Htab, fd, filepath) == -1 )
        {
            free (T[h].next->Htab);
            free(filepath);
            T[h].next->Htab = NULL;
            T[h].next->weight = -1;
            printf("\nMissed file during adding it to Hash Table:: %s", filepath);
            return -1;
        }
        return 1;
    }

    ll* g = T[h].next;
    while (1)
    {
        if ( g->weight == weight )
        {
            if ( HtabAdd(g->Htab, fd, filepath) == -1 )
            {
                printf("\nMissed file during adding it to Hash Table:: %s", filepath);
                return -1;
            }
            return 1;
        }
        else
        {
            if ( g->next == NULL ) break;
            printf("\n[DEBUG PRINT]: hash collision in Wtab");
            g = g->next;
        }
    }
    
    g->next = (ll*) malloc(sizeof(ll));
    if ( g->next == NULL )
    {
        printf("\nCan't allocte memory for ll during adding to Wtab:: %s", filepath);
        return -2;
    }
    g->next->next = NULL;
    g->next->weight = weight;
    g->next->Htab = HtabCreate();
    if ( g->next->Htab == NULL )
    {
        free(g->next);
        g->next = NULL;
        return -2;
    }
    if ( HtabAdd(g->next->Htab, fd, filepath) == -1 )
    {
        free (g->next->Htab);
        free (g->next);
        g->next = NULL;
        printf("\nMissed file during adding it to Hash Table:: %s", filepath);
        return -1;
    }
    return 1;
}


int WtabDel(Wtab* T, size_t weight, char* path)
{
    int h = (weight* 37) % TABLE_COUNT;
    ll* g = T[h].next;
    ll* prev = NULL;
    while ( g != NULL )
    {
        if ( g->weight == weight )
        {
            if ( HtabDel(&g->Htab, path) < 0 )
            {
                printf("\nCan't del:: %s", path);
                return -2;
            }
            printf("\n[DEBUG PRINT]: DELETED FROM Htab:: %s", path);
            if ( g->Htab == NULL )
            {
                if ( prev != NULL ) prev->next = g->next;
                free (g->Htab);
                free (g);
                return 1;
            }
            return 1;
        }
        prev = g;
        g = g->next;
    }
    return 0;
}


void DelAllWtab(Wtab* w)
{
    if ( w == NULL ) return;
    for (int i = 0; i < TABLE_COUNT; ++i)
    {
        ll* g = w[i].next;
        while ( g != NULL )
        {
            Htab* k = g->Htab;
            while ( k != NULL )
            {
                if ( k->name != NULL )
                {
                    free (k->name);
                    free (k->hash);
                }
                Htab* next = k->next;
                free (k);
                k = next;
            }
            ll* llnext = g->next;
            free (g);
            g = llnext;
        }
    }
    free (w);
}
