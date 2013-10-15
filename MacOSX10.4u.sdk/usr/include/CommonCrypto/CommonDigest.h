/* 
 * Copyright (c) 2004 Apple Computer, Inc. All Rights Reserved.
 * 
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 * CommonDigest.h - common digest routines: MD2, MD4, MD5, SHA1.
 */
 
#ifndef	_SECURITY_COMMON_DIGEST_H_
#define _SECURITY_COMMON_DIGEST_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * For compatibility with legacy implementations, all of the functions
 * declared here *always* return a value of 1 (one). This corresponds 
 * to "success" in the similar openssl implementations. There are no 
 * errors of any kind which can be, or are, reported here, so you can 
 * safely ignore the return values of all of these functions if you 
 * are implementing new code.
 */
 
typedef uint32_t CC_LONG;		/* 32 bit unsigned integer */
typedef uint64_t CC_LONG64;		/* 64 bit unsigned integer */

/*** MD2 ***/

#define CC_MD2_DIGEST_LENGTH	16			/* digest length in bytes */
#define CC_MD2_BLOCK_BYTES		64			/* block size in bytes */
#define CC_MD2_BLOCK_LONG       (CC_MD2_BLOCK_BYTES / sizeof(CC_LONG))

typedef struct CC_MD2state_st
{
    int num;
    unsigned char data[CC_MD2_DIGEST_LENGTH];
    CC_LONG cksm[CC_MD2_BLOCK_LONG];
	CC_LONG state[CC_MD2_BLOCK_LONG];
} CC_MD2_CTX;

extern int CC_MD2_Init(CC_MD2_CTX *c);
extern int CC_MD2_Update(CC_MD2_CTX *c, const void *data, CC_LONG len);
extern int CC_MD2_Final(unsigned char *md, CC_MD2_CTX *c);

/*** MD4 ***/

#define CC_MD4_DIGEST_LENGTH	16			/* digest length in bytes */
#define CC_MD4_BLOCK_BYTES		64			/* block size in bytes */
#define CC_MD4_BLOCK_LONG       (CC_MD4_BLOCK_BYTES / sizeof(CC_LONG))

typedef struct CC_MD4state_st
{
	CC_LONG A,B,C,D;
	CC_LONG Nl,Nh;
	CC_LONG data[CC_MD4_BLOCK_LONG];
	int num;
} CC_MD4_CTX;

extern int CC_MD4_Init(CC_MD4_CTX *c);
extern int CC_MD4_Update(CC_MD4_CTX *c, const void *data, CC_LONG len);
extern int CC_MD4_Final(unsigned char *md, CC_MD4_CTX *c);

/*** MD5 ***/

#define CC_MD5_DIGEST_LENGTH	16			/* digest length in bytes */
#define CC_MD5_BLOCK_BYTES		64			/* block size in bytes */
#define CC_MD5_BLOCK_LONG       (CC_MD5_BLOCK_BYTES / sizeof(CC_LONG))

typedef struct CC_MD5state_st
{
	CC_LONG A,B,C,D;
	CC_LONG Nl,Nh;
	CC_LONG data[CC_MD5_BLOCK_LONG];
	int num;
} CC_MD5_CTX;

extern int CC_MD5_Init(CC_MD5_CTX *c);
extern int CC_MD5_Update(CC_MD5_CTX *c, const void *data, CC_LONG len);
extern int CC_MD5_Final(unsigned char *md, CC_MD5_CTX *c);

/*** SHA1 ***/

#define CC_SHA1_DIGEST_LENGTH	20			/* digest length in bytes */
#define CC_SHA1_BLOCK_BYTES		64			/* block size in bytes */
#define CC_SHA1_BLOCK_LONG      (CC_SHA1_BLOCK_BYTES / sizeof(CC_LONG))

typedef struct CC_SHA1state_st
{
	CC_LONG h0,h1,h2,h3,h4;
	CC_LONG Nl,Nh;
	CC_LONG data[CC_SHA1_BLOCK_LONG];
	int num;
} CC_SHA1_CTX;

extern int CC_SHA1_Init(CC_SHA1_CTX *c);
extern int CC_SHA1_Update(CC_SHA1_CTX *c, const void *data, CC_LONG len);
extern int CC_SHA1_Final(unsigned char *md, CC_SHA1_CTX *c);

/*** SHA256 ***/

#define CC_SHA256_DIGEST_LENGTH		32			/* digest length in bytes */
#define CC_SHA256_BLOCK_BYTES		64			/* block size in bytes */

typedef struct CC_SHA256state_st
{   CC_LONG count[2];
    CC_LONG hash[8];
    CC_LONG wbuf[16];
} CC_SHA256_CTX;

extern int CC_SHA256_Init(CC_SHA256_CTX *c);
extern int CC_SHA256_Update(CC_SHA256_CTX *c, const void *data, CC_LONG len);
extern int CC_SHA256_Final(unsigned char *md, CC_SHA256_CTX *c);

/*** SHA384 ***/

#define CC_SHA384_DIGEST_LENGTH		48			/* digest length in bytes */
#define CC_SHA384_BLOCK_BYTES      128			/* block size in bytes */

/* same context struct is used for SHA384 and SHA512 */
typedef struct CC_SHA512state_st
{   CC_LONG64 count[2];
    CC_LONG64 hash[8];
    CC_LONG64 wbuf[16];
} CC_SHA512_CTX;

extern int CC_SHA384_Init(CC_SHA512_CTX *c);
extern int CC_SHA384_Update(CC_SHA512_CTX *c, const void *data, CC_LONG len);
extern int CC_SHA384_Final(unsigned char *md, CC_SHA512_CTX *c);

/*** SHA512 ***/

#define CC_SHA512_DIGEST_LENGTH		64			/* digest length in bytes */
#define CC_SHA512_BLOCK_BYTES      128			/* block size in bytes */

extern int CC_SHA512_Init(CC_SHA512_CTX *c);
extern int CC_SHA512_Update(CC_SHA512_CTX *c, const void *data, CC_LONG len);
extern int CC_SHA512_Final(unsigned char *md, CC_SHA512_CTX *c);

/*
 * To use the above digest functions with existing code which uses
 * the corresponding openssl functions, #define the symbol 
 * COMMON_DIGEST_FOR_OPENSSL in your client code (BEFORE including
 * this file), and simply link against Security.framework instead 
 * of libcrypto.
 *
 * You can *NOT* mix and match functions operating on a given data
 * type from the two implementations; i.e., if you do a CC_MD5_Init()
 * on a CC_MD5_CTX object, do not assume that you can do an openssl-style
 * MD5_Update() on that same context.
 */
 
#ifdef	COMMON_DIGEST_FOR_OPENSSL

#define MD2_DIGEST_LENGTH			CC_MD2_DIGEST_LENGTH
#define MD2_CTX						CC_MD2_CTX
#define MD2_Init(c)					CC_MD2_Init(c)
#define MD2_Update(c,d,l)			CC_MD2_Update(c,d,l)
#define MD2_Final(m, c)				CC_MD2_Final(m,c)

#define MD4_DIGEST_LENGTH			CC_MD4_DIGEST_LENGTH
#define MD4_CTX						CC_MD4_CTX
#define MD4_Init(c)					CC_MD4_Init(c)
#define MD4_Update(c,d,l)			CC_MD4_Update(c,d,l)
#define MD4_Final(m, c)				CC_MD4_Final(m,c)

#define MD5_DIGEST_LENGTH			CC_MD5_DIGEST_LENGTH
#define MD5_CTX						CC_MD5_CTX
#define MD5_Init(c)					CC_MD5_Init(c)
#define MD5_Update(c,d,l)			CC_MD5_Update(c,d,l)
#define MD5_Final(m, c)				CC_MD5_Final(m,c)

#define SHA_DIGEST_LENGTH			CC_SHA1_DIGEST_LENGTH
#define SHA_CTX						CC_SHA1_CTX
#define SHA1_Init(c)				CC_SHA1_Init(c)
#define SHA1_Update(c,d,l)			CC_SHA1_Update(c,d,l)
#define SHA1_Final(m, c)			CC_SHA1_Final(m,c)

#endif	/* COMMON_DIGEST_FOR_OPENSSL */

/*
 * In a manner similar to that described above for openssl 
 * compatibility, these macros can be used to provide compatiblity 
 * with legacy implementations of MD5 using the interface defined 
 * in RFC 1321.
 */
 
#ifdef	COMMON_DIGEST_FOR_RFC_1321

#define MD5_CTX						CC_MD5_CTX
#define MD5Init(c)					CC_MD5_Init(c)
#define MD5Update(c,d,l)			CC_MD5_Update(c,d,l)
#define MD5Final(m, c)				CC_MD5_Final((unsigned char *)m,c)

#endif	/* COMMON_DIGEST_FOR_RFC_1321 */

#ifdef __cplusplus
}
#endif

#endif	/* _SECURITY_COMMON_DIGEST_H_ */
