//
//  Htab.h
//  Deleter
//
//  Created by Павел on 05.07.2021.
//

#ifndef Htab_h
#define Htab_h

/*************************** HEADER FILES ***************************/

#include <stdio.h>
#include <stdlib.h>
#include "Hash_file.h"

/*************************** DATA TYPES ****************************/

typedef struct Htab
{
    unsigned char* hash;
    char* name;
    struct Htab* next;
} Htab;

/*********************** FUNCTION DECLARATIONS **********************/

int HtabAdd(Htab* Ht, FILE* fd, char* path);
Htab* HtabCreate(void);
int HtabDel(Htab** Ht, char* path);

#endif /* Htab_h */
