//
//  Hash_file.h
//  Deleter
//
//  Created by Павел on 03.07.2021.
//

#ifndef Hash_file_h
#define Hash_file_h

#include <stdio.h>

/*********************** FUNCTION DECLARATIONS **********************/

int FileHash(FILE* fd, unsigned char* output);  // return -2 if file haven't opened
void HashStringSha256(unsigned char *string,unsigned char outputBuffer[65]);

#endif /* Hash_file_h */


