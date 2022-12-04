//
//  Weight_Table.h
//  Deleter
//
//  Created by Павел on 04.07.2021.
//

#ifndef Weight_Table_h
#define Weight_Table_h

/*************************** HEADER FILES ***************************/

#include "Htab.h"
#include <stdio.h>
#include <stdlib.h>

/*************************** DATA TYPES ****************************/

static const int TABLE_COUNT = 104857600;    // 100 Mb

typedef struct Wtab
{
    struct ll* next;
} Wtab;

typedef struct ll
{
    struct Htab* Htab;
    size_t weight;
    struct ll* next;
} ll;

/*********************** FUNCTION DECLARATIONS **********************/

int WtabAdd(Wtab* T, FILE* fd, char* filepath);
Wtab* WtabCreate(size_t size);
int WtabDel(Wtab* T, size_t weight, char* path);
void DelAllWtab(Wtab* w);

#endif /* Weight_Table_h */
