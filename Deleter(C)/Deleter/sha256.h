//
//  sha256.h
//  Deleter
//
//  Created by Павел on 04.07.2021.
//


#ifndef SHA256_H
#define SHA256_H

/*************************** HEADER FILES ***************************/

#include <stddef.h>

/****************************** MACROS ******************************/

#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

/*************************** DATA TYPES ****************************/

//typedef unsigned char BYTE;             // 8-bit byte
//typedef unsigned int  WORD;             // 32-bit word, change to "long" for 16-bit machines

typedef struct
{
    unsigned char data[64];
    unsigned int datalen;
    unsigned long long bitlen;
    unsigned int state[8];
} SHA256_CTX;

/*********************** FUNCTION DECLARATIONS **********************/

void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const unsigned char data[], size_t len);
void sha256_final(SHA256_CTX *ctx, unsigned char hash[]);

#endif
