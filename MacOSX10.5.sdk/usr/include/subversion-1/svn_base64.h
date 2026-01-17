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
 * @file svn_base64.h
 * @brief Base64 encoding and decoding functions
 */

#ifndef SVN_BASE64_H
#define SVN_BASE64_H

#include <apr_md5.h>

#include "svn_io.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Return a writable generic stream which will encode binary data in
 * base64 format and write the encoded data to @c output.  Be sure to
 * close the stream when done writing in order to squeeze out the last
 * bit of encoded data.  The stream is allocated in @c pool.
 */
svn_stream_t *svn_base64_encode(svn_stream_t *output, apr_pool_t *pool);

/** Return a writable generic stream which will decode base64-encoded
 * data and write the decoded data to @c output.  The stream is allocated 
 * in @c pool.
 */
svn_stream_t *svn_base64_decode(svn_stream_t *output, apr_pool_t *pool);


/** Encode an @c svn_stringbuf_t into base64.
 *
 * A simple interface for encoding base64 data assuming we have all of 
 * it present at once.  The returned string will be allocated from @c pool.
 */
const svn_string_t *svn_base64_encode_string(const svn_string_t *str,
                                             apr_pool_t *pool);

/** Decode an @c svn_stringbuf_t from base64.
 *
 * A simple interface for decoding base64 data assuming we have all of 
 * it present at once.  The returned string will be allocated from @c pool.
 */
const svn_string_t *svn_base64_decode_string(const svn_string_t *str,
                                             apr_pool_t *pool);


/** Return a base64-encoded checksum for finalized @c digest.
 *
 * @c digest contains @c APR_MD5_DIGESTSIZE bytes of finalized data.
 * Allocate the returned checksum in @c pool.
 */
svn_stringbuf_t *svn_base64_from_md5(unsigned char digest[],
                                     apr_pool_t *pool);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_BASE64_H */
