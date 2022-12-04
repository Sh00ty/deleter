//
//  funcs.c
//  Deleter
//
//  Created by Павел on 21.08.2021.
//

#include "funcs.h"

int cmp(const void *a, const void *b)
{
     return *(int*)a - *(int*)b;
}


void print_table(Wtab* w)
{
    int numX = -1, numY = 0, count = 0;
    for (int i = 0; i < TABLE_COUNT; ++i)
    {
        ll* g = w[i].next;
        while (g != NULL)
        {
            Htab* k = g->Htab;
            k = k->next;
            unsigned char* hash;
            if ( k->next != NULL )
            {
                numY = 0;
                hash = k->hash;
                numX++;
                printf("\n\n%d:Weight::%ld  NUMBER::%d", numX, g->weight, numY);
                while ( k != NULL )
                {
                    if ( strcmp(hash, k->hash) != 0 )
                    {
                        hash = k->hash;
                        numY++;
                        numX++;
                        printf("\n\n%d:Weight::%ld  NUMBER::%d", numX, g->weight, numY);
                    }
                    printf("\n%d:: %s  ||  hash %s", count, k->name ,k->hash);
                    count++;
                    k = k->next;
                }
                printf("\n");
            }
            else
            {
                numX++;
                printf("\n\n%d:Weight::%ld  NUMBER::%d", numX, g->weight, numY);
                printf("\n%d:: %s  ||  hash %s", count, k->name ,k->hash);
                count++;
            }
            g = g->next;
        }
    }
}


void search_empty_files(Wtab* w)
{
    ll* g = w->next;
    while ( g != NULL )
    {
        if ( g->weight == 0 )
        {
            Htab* k = g->Htab;
            if (k == NULL)
            {
                printf("\nNo empty files");
                return;
            }
            else printf("\nHERE EMPTY FILES::");
            k = k->next;
            while ( k != NULL )
            {
                printf("\n%s", k->name);
                k = k->next;
            }
            printf("\n");
            return;
        }
        g = g->next;
    }
}


void show_only_eq_files(Wtab* w)
{
    int count = 0;
    int ct = 0;
    char flag = 0;
    for (int i = 0; i < TABLE_COUNT; ++i)
    {
        ll* g = w[i].next;
        while (g != NULL)
        {
            Htab* k = g->Htab;
            k = k->next;
            unsigned char* hash = k->hash;
            while ( k != NULL)
            {
                if ( k->next != NULL )
                {
                    if ( strcmp(hash, k->next->hash) == 0 )
                    {
                        if ( !flag )
                        {
                            printf("\n%d::", count);
                            count++;
                        }
                        printf("\n%dname:: %s || hash:: %s", ct, k->name, k->hash);
                        flag = 1;
                    }
                    else if ( flag )
                    {
                        printf("\n%dname:: %s || hash:: %s", ct, k->name, k->hash);
                        hash = k->next->hash;
                        flag = 0;
                    }
                }
                else if ( flag ) printf("\n%dname:: %s || hash:: %s", ct, k->name, k->hash);
                ct++;
                k = k->next;
            }
            flag = 0;
            g = g->next;
        }
    }
}


void show_all_equal_files(Wtab* w, point* mas)
{
    int numX = -1, numY, count = 0, ct = 0;
    for (int i = 0; i < TABLE_COUNT; ++i)
    {
        ll* g = w[i].next;
        while ( g != NULL )
        {
            Htab* k = g->Htab;
            k = k->next;
            unsigned char* hash = k->hash;
            numY = 0;
            numX++;
            printf("\n\n:Weight::%ld  NUMBER::%d", g->weight, numY);
            ct = 0;
            while ( k != NULL )
            {
                if ( strcmp(hash, k->hash) != 0 )
                {
                    hash = k->hash;
                    numY++;
                    numX++;
                    printf("\n\n:Weight::%ld  NUMBER::%d", g->weight, numY);
                }
                mas[count].x = g->weight;
                mas[count].y = ct;
                printf("\n%d:: %s  ||  hash %s", count, k->name ,k->hash);
                count++;
                ct++;
                k = k->next;
            }
            printf("\n");
            g = g->next;
        }
    }
}


Htab* find_file_weight(Wtab* w, size_t weight, int place)
{
    int hash = (weight * 37) % TABLE_COUNT;
    ll* g = w[hash].next;
    while ( g->weight != weight )
    {
        if ( g == NULL ) return NULL;
        g = g->next;
    }
    Htab* k = g->Htab->next;
    unsigned char* has = k->hash;
    for (int i = 0; i < place;)
    {
        if ( k == NULL) return NULL;
        if ( strcmp(k->hash, has) != 0 )
        {
            i++;
            if ( i == place ) return k;
            has = k->hash;
        }
        k = k->next;
    }
    return k;
}


int show_file(Wtab* w, size_t weight, int count, int* nums)
{
    qsort(nums, count, sizeof(int), cmp);
    int ret = 0;
    int hash = (weight * 37) % TABLE_COUNT;
    ll* g = w[hash].next;
    while ( g->weight != weight )
    {
        if ( g == NULL ) return 0;
        g = g->next;
    }
    Htab* h = g->Htab->next;
    if (h == NULL)
    {
        printf("\nCan't find necessary file");
        return -1;
    }
    char* name = h->name;
    for (int i = 0, x = 0; i < count; ++x)
    {
        Htab* next = h->next;
        if ( nums[i] == x )
        {
            ++ret;
            char str[strlen(name) + 5];
            str[0] = 'o';
            str[0] = 'p';
            str[0] = 'e';
            str[0] = 'n';
            str[0] = ' ';
            str[0] = '\0';
            strcat(str, name);
            int status = system(str);
            ++i;
        }
        h = next;
        if ( h == NULL )
        {
            printf("\n[WARNING]: del_equal_weight:: list unexpected ended");
            return ret;
        }
        name = h->name;
    }
    return ret;
}


int del_equal_files(Wtab* w, size_t weight, int count, int* nums)
{
    qsort(nums, count, sizeof(int), cmp);
    int ret = 0;
    int hash = (weight * 37) % TABLE_COUNT;
    ll* g = w[hash].next;
    while ( g->weight != weight )
    {
        if ( g == NULL ) return 0;
        g = g->next;
    }
    Htab* h = g->Htab->next;
    if (h == NULL)
    {
        printf("\nCan't find necessary file");
        return -1;
    }
    char* name = h->name;
    for (int i = 0, x = 0; i < count; ++x)
    {
        Htab* next = h->next;
        if ( nums[i] == x )
        {
            printf("\n\n[WARNING]:: WOULD YOU LIKE TO DELETE %s???", name);
            if ( bin_ans() )
                if ( WtabDel(w, weight, h->name) > 0 )
                {
                    ++ret;
                    remove(name);
                    printf("\n----------Deleted:: %s\n", name);
                    free(name);
                }
            ++i;
        }
        h = next;
        if ( h == NULL )
        {
            printf("\n[WARNING]: del_equal_weight:: list unexpected ended");
            return ret;
        }
        name = h->name;
    }
    return ret;
}


int get_int(int* a)
{
    int n;
    do
    {
        n = scanf("%d", a);
        if ( n == 0 )
        {
            printf("Error! Erore! Atantium! Ples! put chisla:\n");
            scanf("%*s");
        }
    }
    while ( n == 0 );
    return n;
}


int get_str(char **str)
{
    int n;
    unsigned long int k,r,ret = 0;
    do
    {
        if ( *str == NULL ) k = 0;
        else k = strlen(*str);
        scanf("%*c");
        n = scanf("%100[^\n]", *str + k);
        if (n == -1) return -1;
        r = strlen(*str);
        ret = r - k;
        if (ret != 100) break;
        *str = (char *) realloc(*str, (101 + r) * sizeof(char));
    } while (n > 0);
    *str = (char *) realloc(*str, (r+1) * sizeof(char));
    (*str)[r] = '\0';
    return (int) r;
}


int bin_ans()
{
    printf("\nEnter y/n::");
    char ans[4];
    if ( scanf("%4s", ans) == -1 )
        return 0;
    if ( strcmp(ans, "yes") == 0 || strcmp(ans, "y") == 0 || strcmp(ans, "Y") == 0 || strcmp(ans, "YES") == 0) return 1;
    else return 0;
}


int* create_del_ans(char* ans, int* retsize)
{
    *retsize = 0;
    long int size = strlen(ans);
    int g = 1;
    int* ret = (int *) malloc(1000*sizeof(int));
    int start = 0;
    int fin = 0;
    int num = -1;
    char pen = 0;
    // "12 23-43" for 12 pen = 0; for 23 pen = 1
    long int i = size - 1;
    while ( i >= 0 )
    {
        if ( ans[i] <= '9' && ans[i] >= '0' )
        {
            if ( num == -1 ) num = 0;
            num += g * (ans[i] - 48);
            g *= 10;
        }
        else if ( ans[i] == ' ' )
        {
            if ( num != -1 )
            {
                if ( pen )
                {
                    start = num;
                    for (int e = fin; e >= start; --e)
                    {
                        ret[*retsize] = e;
                        (*retsize)++;
                    }
                    num = -1;
                    g = 1;
                    pen = 0;
                }
                else
                {
                    ret[*retsize] = num;
                    num = -1;
                    (*retsize)++;
                    g = 1;
                }
            }
        }
        else if ( ans[i] == '-' )
        {
            fin = num;
            num = -1;
            g = 1;
            pen = 1;
        }
        else
        {
            printf("\n[WARNING]:: your input was wrong (you used not the integers or '-' or ' ')\nIt means that data you input can be wrong");
            printf("\nYour input:: %c", ans[i]);
            num = -1;
            g = 1;
        }
        --i;
        if ( i < 0 )
        {
            if ( num != -1 )
            {
                if ( pen )
                {
                    start = num;
                    for (int e = fin; e >= start; --e)
                    {
                        ret[*retsize] = e;
                        (*retsize)++;
                    }
                }
                else
                {
                    ret[*retsize] = num;
                    (*retsize)++;
                }
            }
        }
    }
    ret = (int*) realloc(ret, *retsize * sizeof(int));
    return ret;
}


void help_print(void)
{
    printf("\n###################\n");
    printf("\nEnter -1 to exit");
    printf("\nEnter 0 to show help message");
    printf("\nEnter 1 to show Table with equal files");
    printf("\nEnter 2 to create Table with equal files");
    printf("\nEnter 3 to delete something");
    printf("\nEnter 4 to show Table with only duplicated files");
    printf("\nEnter 5 to show empty files");
    printf("\nEnter 6 to delete table");
    printf("\nEnter 7 to show only duplicated files");
    printf("\nEnter 8 to delete file by name");
    printf("\n::");
}


void main_menu()
{
    help_print();
    int input = 0;
    if ( get_int(&input) == - 1 )
    {
        printf("\n----------------  CLOSED");
        return;
    }
    Wtab* w = NULL;
    point mas[10000];
    for (int i = 0; i < 10000; ++i)
    {
        mas[i].x = 0;
        mas[i].y = 0;
    }
    while(1)
    {
        switch (input)
        {
            case -1:
            {
                DelAllWtab(w);
                return;
            }
            case 0:
            {
                help_print();
                break;
            }
            case 1:
            {
                if ( w == NULL )
                {
                    printf("\n[ERROR]:: TABLE IS EMPTY\nYou must create it before");
                    break;
                }
                print_table(w);
                break;
            }
            case 2:
            {
                if ( w != NULL )
                {
                    printf("\nYou must delete last table!!!");
                    break;
                }
                char* DirName = (char*) malloc(101 * sizeof(char));
                DirName[0] = '\0';
                printf("\nEnter full path to the directory::");
                if ( get_str(&DirName) <= 0 )
                {
                    free(DirName);
                    printf("\n----------------  CLOSED");
                    break;
                }
                w = WtabCreate(TABLE_COUNT);
                if ( w == NULL )
                {
                    free(DirName);
                    printf("\n[ERROR]: can't allocate memory for Wtab");
                    return;
                }
                go_round(DirName, w, 0);
                show_all_equal_files(w, mas);
                printf("\n[WARNING]:: There are only duplicated files (NOT ALL)");
                break;
            }
            case 3:
            {
                if ( w == NULL )
                {
                    printf("\n[ERROR]:: TABLE IS EMPTY\nYou must create it before");
                    break;
                }
                printf("\n[WARNING]:: You came to delete mode\nBe carefull before deleting something");
                while(1)
                {
                    printf("\nIf you want to continue enter 0\n::");
                    int inp = 0;
                    if ( get_int(&inp) == -1 ) return;
                    if ( inp != 0 ) break;
                    printf("\nNow chooce numbers you want to delete");
                    printf("\n(for example 1 2 5 7-10 60-90) it would be nice if you sorted your answer\n::");
                    char* ans = (char*) malloc(101 * sizeof(char));
                    int size = 0;
                    if ( get_str(&ans) <= 0 )
                    {
                        free(ans);
                        continue;
                    }
                    
                    int* nums = create_del_ans(ans, &size);
                    free(ans);
                    printf("\nIt how i understed::\n");
                    for (int i = size - 1; i >= 0; --i)
                        printf(" %d", nums[i]);
                    
                    int* OneWeight = (int*) malloc(size * sizeof(int));
                    int owSize = 0;
                    long int weight = mas[nums[size-1]].x;
                    for (int i = size - 1; i >= 0; --i)
                    {
                        if ( mas[nums[i]].x == weight )
                        {
                            OneWeight[owSize] = mas[nums[i]].y;
                            owSize++;
                        }
                        else
                        {
                            int y = del_equal_files(w, weight, owSize, OneWeight);
                            printf("\n[DEBUG]: Deleted ::%d", y);
                            weight = mas[nums[i]].x;
                            owSize = 0;
                            OneWeight[owSize] = mas[nums[i]].y;
                            owSize++;
                        }
                    }
                    int y = del_equal_files(w, weight, owSize, OneWeight);
                    printf("\n[DEBUG]: Deleted ::%d", y);
                    free (OneWeight);
                    free (nums);
                }
                break;
            }
            case 4:
            {
                if ( w == NULL )
                {
                    printf("\n[ERROR]:: TABLE IS EMPTY\nYou must create it before");
                    break;
                }
                show_all_equal_files(w, mas);
                break;
            }
            case 5:
            {
                if ( w == NULL )
                {
                    printf("\n[ERROR]:: TABLE IS EMPTY\nYou must create it before");
                    break;
                }
                search_empty_files(w);
                break;
            }
            case 6:
            {
                DelAllWtab(w);
                w = NULL;
                printf("\nTable deleted");
                break;
            }
            case 7:
            {
                if ( w == NULL )
                {
                    printf("\n[ERROR]:: TABLE IS EMPTY\nYou must create it before");
                    break;
                }
                show_only_eq_files(w);
                break;
            }
            case 8:
            {
                printf("\nBe carefull!!!\nEnter full name of the file you want to delete::");
                char* name = (char*) malloc(101 * sizeof(char));
                if ( get_str(&name) <= 0 )
                {
                    free(name);
                    break;
                }
                printf("\nWould you like to delete:: %s ???", name);
                if ( bin_ans() )
                {
                    int y = remove(name);
                    printf("\nREMOVED:: %d", y);
                }
                free(name);
                break;
            }
            case 9:
            {
                if ( w == NULL )
                {
                    printf("\n[ERROR]:: TABLE IS EMPTY\nYou must create it before");
                    break;
                }
                printf("\n[WARNING]:: You came to show mode");
                while(1)
                {
                    printf("\nIf you want to continue enter 0\n::");
                    int inp = 0;
                    if ( get_int(&inp) == -1 ) return;
                    if ( inp != 0 ) break;
                    printf("\nNow chooce numbers you want to delete");
                    printf("\n(for example 1 2 5 7-10 60-90) it would be nice if you sorted your answer\n::");
                    char* ans = (char*) malloc(101 * sizeof(char));
                    int size = 0;
                    if ( get_str(&ans) <= 0 )
                    {
                        free(ans);
                        continue;
                    }
                    
                    int* nums = create_del_ans(ans, &size);
                    free(ans);
                    printf("\nIt how i understed::\n");
                    for (int i = size - 1; i >= 0; --i)
                        printf(" %d", nums[i]);
                    
                    int* OneWeight = (int*) malloc(size * sizeof(int));
                    int owSize = 0;
                    long int weight = mas[nums[size-1]].x;
                    for (int i = size - 1; i >= 0; --i)
                    {
                        if ( mas[nums[i]].x == weight )
                        {
                            OneWeight[owSize] = mas[nums[i]].y;
                            owSize++;
                        }
                        else
                        {
                            int y = show_file(w, weight, owSize, OneWeight);
                            printf("\n[DEBUG]: Showed ::%d", y);
                            weight = mas[nums[i]].x;
                            owSize = 0;
                            OneWeight[owSize] = mas[nums[i]].y;
                            owSize++;
                        }
                    }
                    int y = show_file(w, weight, owSize, OneWeight);
                    printf("\n[DEBUG]: Showed ::%d", y);
                    free (OneWeight);
                    free (nums);
                }
            }
            default:
            {
                printf("[ERROR]\nInput failed, try again\nBe more carefull");
                break;
            }
        }
        help_print();
        if ( get_int(&input) == - 1 )
        {
            DelAllWtab(w);
            return;
        }
    }
}
