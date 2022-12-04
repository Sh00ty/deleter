//
//  funcs.h
//  Deleter
//
//  Created by Павел on 21.08.2021.
//

#ifndef funcs_h
#define funcs_h

/*************************** HEADER FILES ***************************/

#include <stdio.h>
#include <string.h>
#include "Hash_file.h"
#include "Weight_Table.h"
#include "Dir_file.h"

/*************************** DATA TYPES ****************************/

typedef struct point
{
    unsigned long int x;
    int y;
} point;

/*********************** FUNCTION DECLARATIONS **********************/

void print_table(Wtab* w);
void search_empty_files(Wtab* w);
void show_all_equal_files(Wtab* w, point* mas);

void show_only_eq_files(Wtab* w);

int del_equal_files(Wtab* w, size_t weight, int count, int* nums);
Htab* find_file_weight(Wtab* w, size_t weight, int place);
int* create_del_ans(char* ans, int* retsize);

void help_print(void);
void main_menu(void);
int get_int(int* a);
int get_str(char** name);
int bin_ans(void);
#endif /* funcs_h */
