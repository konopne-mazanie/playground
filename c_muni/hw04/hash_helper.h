/**
 * File: hash_helper.h
 * Author: Milan Fabian <milan.fabian@mail.muni.cz>
 * Date: 2.1.2015
 */

#ifndef HASH_HELPER_H
#define HASH_HELPER_H

/**
 * Struct for holding current CRC-16 result. After finishing, value of
 * crc16_context.crc is valid CRC-16 hash.
 */

typedef struct
{
	unsigned char xor;
} xor_context;

typedef struct
{
	unsigned short crc;
} crc16_context;

typedef struct
{
	unsigned int crc;
} crc32_context;

void xor_Init(xor_context *xcon, unsigned char byte);
void xor_Update(xor_context *xcon, unsigned char *byte, int size);

void crc32_init(crc32_context *context);
void crc32_update(crc32_context *context, unsigned char data);
/**
 * Initialize crc16_context, must be called before calling crc16_update.
 */
void crc16_init(crc16_context *context);

/**
 * Updates crc16_context with one byte of data.
 */
void crc16_update(crc16_context *context, unsigned char data);

typedef unsigned int MD5_u32plus;

/**
 * Struct for holding current MD5 context.
 */
typedef struct
{
	MD5_u32plus lo, hi;
	MD5_u32plus a, b, c, d;
	unsigned char buffer[64];
	MD5_u32plus block[16];
} MD5_CTX;

/**
 * Initialize MD5_CTX, must be called before calling MD5_Update.
 */
void MD5_Init(MD5_CTX *ctx);

/**
 *  Updates MD5_CTX with one data of length size.
 */
void MD5_Update(MD5_CTX *ctx, const void *data, unsigned long size);

/**
 * Calculates result of MD5 and stores it into result array of length 16.
 */
void MD5_Final(unsigned char *result, MD5_CTX *ctx);

#endif
