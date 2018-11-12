#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "hash_helper.h"

void error_occ(void)
{
    fprintf(stderr, "Error");
    exit(1);
}

int fxor(FILE *fobj, int size)
{
    xor_context xcon;
    unsigned char digest[12];
    fread(digest, sizeof(unsigned char), 1, fobj);
    xor_Init(&xcon, digest[0]);
    size--;
    while (true)
    {
        if (size < 12)
        {
            fread(digest, sizeof(unsigned char), size, fobj);
            xor_Update(&xcon, digest, size);
            break;
        }
        fread(digest, sizeof(unsigned char), 12, fobj);
        xor_Update(&xcon, digest, 12);
        size -= 12;
        if (size == 0)
        {
            break;
        }
    }
    return (int)xcon.xor;
}

int fc16(FILE *fobj, int size)
{
    crc16_context crc;
    unsigned char digest[1];
    crc16_init(&crc);
    while (size != 0)
    {
        fread(digest, sizeof(unsigned char), 1, fobj);
        crc16_update(&crc, digest[0]);
        size--;
    }
    int result = (int)crc.crc;
    return result;
}

int fc32(FILE *fobj, int size)
{
    crc32_context crc;
    unsigned char digest[1];
    crc32_init(&crc);
    while (size != 0)
    {
        fread(digest, sizeof(unsigned char), 1, fobj);
        crc32_update(&crc, digest[0]);
        size--;
    }
    int result = (int)~crc.crc;
    return result;
}

void fmd5(FILE *fobj, int size)
{
    MD5_CTX ctx;
    unsigned char digest[12];
    unsigned char result[16];
    MD5_Init(&ctx);
    while (true)
    {
        if (size < 12)
        {
            fread(digest, sizeof(unsigned char), size, fobj);
            MD5_Update(&ctx, digest, size);
            break;
        }
        fread(digest, sizeof(unsigned char), 12, fobj);
        MD5_Update(&ctx, digest, 12);
        size -= 12;
        if (size == 0)
        {
            break;
        }
    }


    MD5_Final(result, &ctx);

    printf("MD5: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%02x", result[i]);
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    bool c16 = false;
    bool c32 = false;
    bool md5 = false;
    bool xor = false;
    bool hex = false;
    char *file = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-c16"))
        {
            c16 = true;
        }
        else if (!strcmp(argv[i], "-c32"))
        {
            c32 = true;
        }
        else if (!strcmp(argv[i], "-md5"))
        {
            md5 = true;
        }
        else if (!strcmp(argv[i], "-xor"))
        {
            xor = true;
        }
        else if (!strcmp(argv[i], "-hex"))
        {
            hex = true;
        }
        else if (!strcmp(argv[i], "-f"))
        {
            if (i == argc-1)
            {
                error_occ();
            }
            file = malloc(strlen(argv[i + 1]) * sizeof(char) + 1);
            strcpy(file, argv[i + 1]);
            i++;
        }
        else
        {
            error_occ();
        }
    }
    FILE *fobj = NULL;
    if (file)
    {
        fobj = fopen(file, "rb");
        free(file);
        if (argc < 3 || !fobj || (argc == 3 && hex))
        {
            error_occ();
        }
    }
    else
    {
        if (argc < 2 || (argc == 2 && hex))
        {
            error_occ();
        }
    }
    if (!fobj)
    {
        fobj = stdin;
    }
    fseek(fobj, 0L, SEEK_END);
    int fsize = ftell(fobj);
    if (fsize < 1)
    {
        error_occ();
    }
    rewind(fobj);
    printf("Length: %d bytes\n", fsize);

    if (xor)
    {
        if (hex)
        {
            printf("XOR: 0x%02x\n", fxor(fobj, fsize));
        }
        else
        {
            printf("XOR: %d\n", fxor(fobj, fsize));
        }
        rewind(fobj);
    }
    if (c16)
    {
        if (hex)
        {
            printf("CRC-16: 0x%04x\n", fc16(fobj, fsize));
        }
        else
        {
            printf("CRC-16: %d\n", fc16(fobj, fsize));
        }
        rewind(fobj);
    }
    if (c32)
    {
        if (hex)
        {
            printf("CRC-32: 0x%08x\n", fc32(fobj, fsize));
        }
        else
        {
            printf("CRC-32: %d\n", fc32(fobj, fsize));
        }
        rewind(fobj);
    }
    if (md5)
    {
        fmd5(fobj, fsize);
    }
    fclose(fobj);
    return 0;
}