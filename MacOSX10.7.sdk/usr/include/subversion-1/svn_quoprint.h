/**
 * @copyright
 * ====================================================================
 * Copyright (c) 2000-2004, 2008 CollabNet.  All rights reserved.
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
 * @file svn_quoprint.h
 * @brief quoted-printable encoding and decoding functions.
 */

#ifndef SVN_QUOPRINT_H
#define SVN_QUOPRINT_H

#include <apr_pools.h>

#include "svn_string.h"  /* for svn_strinbuf_t */
#include "svn_io.h"      /* for svn_stream_t */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Return a writable generic stream which will encode binary data in
 * quoted-printable format and write the encoded data to @a output.  Be
 * sure to close the stream when done writing in order to squeeze out
 * the last bit of encoded data.
 */
svn_stream_t *
svn_quoprint_encode(svn_stream_t *output,
                    apr_pool_t *pool);

/** Return a writable generic stream which will decode binary data in
 * quoted-printable format and write the decoded data to @a output.  Be
 * sure to close the stream when done writing in order to squeeze out
 * the last bit of encoded data.
 */
svn_stream_t *
svn_quoprint_decode(svn_stream_t *output,
                    apr_pool_t *pool);


/** Simpler interface for encoding quoted-printable data assuming we have all
 * of it present at once.  The returned string will be allocated from @a pool.
 */
svn_stringbuf_t *
svn_quoprint_encode_string(const svn_stringbuf_t *str,
                           apr_pool_t *pool);

/** Simpler interface for decoding quoted-printable data assuming we have all
 * of it present at once.  The returned string will be allocated from @a pool.
 */
svn_stringbuf_t *
svn_quoprint_decode_string(const svn_stringbuf_t *str,
                           apr_pool_t *pool);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_QUOPRINT_H */
