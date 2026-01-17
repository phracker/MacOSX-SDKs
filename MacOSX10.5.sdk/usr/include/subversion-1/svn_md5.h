/**
 * @copyright
 * ====================================================================
 * Copyright (c) 2000-2004 CollabNet.  All rights reserved.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at http://subversion.tigris.org/license-1.html.
 * If newer versions of this license are posted there, you may use a
 * newer version instead, at your option.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://subversion.tigris.org/.
 * ====================================================================
 * @endcopyright
 *
 * @file svn_md5.h
 * @brief Converting and comparing MD5 checksums.
 */

#ifndef SVN_MD5_H
#define SVN_MD5_H

#include <apr_pools.h>
#include <apr_md5.h>
#include "svn_error.h"
#include "svn_pools.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/** The MD5 digest for the empty string. */
const unsigned char *svn_md5_empty_string_digest(void);


/** Return the hex representation of @a digest, which must be
 * @c APR_MD5_DIGESTSIZE bytes long, allocating the string in @a pool.
 */
const char *svn_md5_digest_to_cstring_display(const unsigned char digest[],
                                              apr_pool_t *pool);


/** Return the hex representation of @a digest, which must be
 * @c APR_MD5_DIGESTSIZE bytes long, allocating the string in @a pool.
 * If @a digest is all zeros, then return NULL.
 */
const char *svn_md5_digest_to_cstring(const unsigned char digest[],
                                      apr_pool_t *pool);


/** Compare digests @a d1 and @a d2, each @c APR_MD5_DIGESTSIZE bytes long.
 * If neither is all zeros, and they do not match, then return false;
 * else return true.
 */
svn_boolean_t svn_md5_digests_match(const unsigned char d1[],
                                    const unsigned char d2[]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_MD5_H */
