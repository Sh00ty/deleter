//
//  Dir_file.c
//  Deleter
//
//  Created by Павел on 20.07.2021.
//

#include "Weight_Table.h"
#include "Dir_file.h"
#include <dirent.h>
#include <string.h>

void go_round (char* DirName, Wtab* Wtab, int count)
{
    DIR* dir = opendir (DirName);
    if ( dir == NULL )
    {
        if ( count == 0 )
        {
            printf("\n[ERROR]: Directory:: %s isn't exist\nNext time be more carefull :)", DirName);
            free(DirName);
            return;
        }
        FILE* fd = (FILE*) fopen (DirName, "r+");
        if ( fd == NULL )
        {
            printf("\ncan't open file:: %s", DirName);
            free(DirName);
            return;
        }
        printf("\n------opened %s", DirName);
        WtabAdd(Wtab, fd, DirName);
        fclose(fd);
        return;
    }
    
    struct dirent* ent;
        
    while ( (ent = readdir(dir)) != NULL )
    {
        if ( ent->d_name[0] == '.' ) continue;
        long int len = strlen(ent->d_name) + strlen(DirName);
        char* name = (char*) malloc((len + 2) * sizeof(char));
        for (int i = 0; i < len + 2; ++i) name[i] = '\0';
        strcat(name, DirName);
        strcat(name, "/");
        strcat(name, ent->d_name);
        printf("\nrd:: %s", name);
        count++;
        go_round(name, Wtab, count);
    }
    free(DirName);
    closedir (dir);
}
