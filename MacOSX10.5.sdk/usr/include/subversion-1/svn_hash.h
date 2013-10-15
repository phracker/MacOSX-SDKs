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
 * @file svn_hash.h
 * @brief Dumping and reading hash tables to/from files.
 */


#ifndef SVN_HASH_H
#define SVN_HASH_H

#include <apr_pools.h>
#include <apr_hash.h>
#include <apr_file_io.h>

#include "svn_types.h"
#include "svn_io.h"
#include "svn_error.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** The longest the "K <number>" line can be in one of our hashdump files. */
#define SVN_KEYLINE_MAXLEN 100


/*----------------------------------------------------*/

/** Reading/writing hashtables to disk
 *
 * @defgroup svn_hash_read_write reading and writing hashtables to disk
 * @{
 */

/**
 * The conventional terminator for hash dumps.
 *
 * @since New in 1.1.
 */
#define SVN_HASH_TERMINATOR "END"

/**
 * Read a hash table from @a stream, storing the resultants names and
 * values in @a hash.  Use a @a pool for all allocations.  @a hash will
 * have <tt>const char *</tt> keys and <tt>svn_string_t *</tt> values.
 * If @a terminator is NULL, expect the hash to be terminated by the
 * end of the stream; otherwise, expect the hash to be terminated by a
 * line containing @a terminator.  Pass @c SVN_HASH_TERMINATOR to use
 * the conventional terminator "END".
 *
 * @since New in 1.1.
 */
svn_error_t *svn_hash_read2(apr_hash_t *hash,
                            svn_stream_t *stream,
                            const char *terminator,
                            apr_pool_t *pool);

/**
 * Dump @a hash to @a stream.  Use @a pool for all allocations.  @a
 * hash has <tt>const char *</tt> keys and <tt>svn_string_t *</tt>
 * values.  If @a terminator is not NULL, terminate the hash with a
 * line containing @a terminator.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_hash_write2(apr_hash_t *hash, 
                             svn_stream_t *stream,
                             const char *terminator,
                             apr_pool_t *pool);

/**
 * Similar to svn_hash_read2(), but allows @a stream to contain
 * deletion lines which remove entries from @a hash as well as adding
 * to it.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_hash_read_incremental(apr_hash_t *hash,
                                       svn_stream_t *stream,
                                       const char *terminator,
                                       apr_pool_t *pool);

/**
 * Similar to svn_hash_write2(), but only writes out entries for
 * keys which differ between @a hash and @a oldhash, and also writes
 * out deletion lines for keys which are present in @a oldhash but not
 * in @a hash.
 *
 * @since New in 1.1.
 */
svn_error_t *svn_hash_write_incremental(apr_hash_t *hash,
                                        apr_hash_t *oldhash,
                                        svn_stream_t *stream,
                                        const char *terminator,
                                        apr_pool_t *pool);

/**
 * This function behaves like svn_hash_read2(), but it only works
 * on an apr_file_t input, empty files are accepted, and the hash is
 * expected to be terminated with a line containing "END" or
 * "PROPS-END".
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_hash_read(apr_hash_t *hash, 
                           apr_file_t *srcfile,
                           apr_pool_t *pool);

/**
 * This function behaves like svn_hash_write2(), but it only works
 * on an apr_file_t output, and the terminator is always "END".
 *
 * @deprecated Provided for backward compatibility with the 1.0 API.
 */
svn_error_t *svn_hash_write(apr_hash_t *hash, 
                            apr_file_t *destfile,
                            apr_pool_t *pool);

/** @} */


/** Taking the "diff" of two hash tables.
 *
 * @defgroup svn_hash_diff taking the diff of two hash tables.
 * @{
 */

/** Hash key status indicator for svn_hash_diff_func_t.  */
enum svn_hash_diff_key_status
  {
    /* Key is present in both hashes. */
    svn_hash_diff_key_both,

    /* Key is present in first hash only. */
    svn_hash_diff_key_a,

    /* Key is present in second hash only. */
    svn_hash_diff_key_b
  };


/** Function type for expressing a key's status between two hash tables. */
typedef svn_error_t *(*svn_hash_diff_func_t)
  (const void *key, apr_ssize_t klen,
   enum svn_hash_diff_key_status status,
   void *baton);


/** Take the diff of two hashtables.
 *
 * For each key in the union of @a hash_a's and @a hash_b's keys, invoke
 * @a diff_func exactly once, passing the key, the key's length, an enum
 * @c svn_hash_diff_key_status indicating which table(s) the key appears
 * in, and @a diff_func_baton.
 *
 * Process all keys of @a hash_a first, then all remaining keys of @a hash_b. 
 *
 * If @a diff_func returns error, return that error immediately, without
 * applying @a diff_func to anything else.
 *
 * @a hash_a or @a hash_b or both may be null; treat a null table as though
 * empty.
 *
 * Use @a pool for temporary allocation.
 */
svn_error_t *svn_hash_diff(apr_hash_t *hash_a,
                           apr_hash_t *hash_b,
                           svn_hash_diff_func_t diff_func,
                           void *diff_func_baton,
                           apr_pool_t *pool);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_HASH_H */
