//
//  Hash_file.c
//  Deleter
//
//  Created by Павел on 03.07.2021.
//

#include "Hash_file.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sha256.h"


void HashStringSha256(unsigned char *string,unsigned char outputBuffer[65])
{
    unsigned char hash[SHA256_BLOCK_SIZE];
    SHA256_CTX sha256;
    sha256_init(&sha256);
    // check optimization for strlen(may be we can count it from fread)
    
    sha256_update(&sha256, string, strlen((char*) string));
    sha256_final(&sha256, hash);

    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
    {
        sprintf((char*)outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = '\0';
}


int FileHash(FILE* fd, unsigned char* output)
{
    size_t bufsize = 32768;
    unsigned char* buffer = (unsigned char*) malloc(bufsize);
    if ( buffer == NULL ) return -1;
    size_t count = 0;
    
    unsigned char hash[SHA256_BLOCK_SIZE + 1];
    SHA256_CTX sha256;
    sha256_init(&sha256);
    
    while ( (count = fread(buffer, sizeof(char), bufsize, fd)) )
        sha256_update(&sha256, buffer, count);
    hash[SHA256_BLOCK_SIZE] = '\0';
    sha256_final(&sha256, hash);
    HashStringSha256(hash, output);
    free(buffer);
    return 0;
}
