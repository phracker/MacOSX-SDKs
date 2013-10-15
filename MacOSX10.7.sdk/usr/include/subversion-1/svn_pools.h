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
 * @file svn_pools.h
 * @brief APR pool management for Subversion
 */




#ifndef SVN_POOLS_H
#define SVN_POOLS_H

#include <apr_pools.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/* Wrappers around APR pools, so we get debugging. */

/** The recommended maximum amount of memory (4MB) to keep in an APR
 * allocator on the free list, conveniently defined here to share
 * between all our applications.
 */
#define SVN_ALLOCATOR_RECOMMENDED_MAX_FREE (4096 * 1024)


/** Wrapper around apr_pool_create_ex(), with a simpler interface.
 * The return pool will have an abort function set, which will call
 * abort() on OOM.
 */
apr_pool_t *
svn_pool_create_ex(apr_pool_t *parent_pool,
                   apr_allocator_t *allocator);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
apr_pool_t *
svn_pool_create_ex_debug(apr_pool_t *parent_pool,
                         apr_allocator_t *allocator,
                         const char *file_line);

#if APR_POOL_DEBUG
#define svn_pool_create_ex(pool, allocator) \
svn_pool_create_ex_debug(pool, allocator, APR_POOL__FILE_LINE__)

#endif /* APR_POOL_DEBUG */
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


/** Create a pool as a subpool of @a parent_pool */
#define svn_pool_create(parent_pool) svn_pool_create_ex(parent_pool, NULL)

/** Clear a @a pool destroying its children.
 *
 * This define for @c svn_pool_clear exists for completeness.
 */
#define svn_pool_clear apr_pool_clear


/** Destroy a @a pool and all of its children.
 *
 * This define for @c svn_pool_destroy exists for symmetry and
 * completeness.
 */
#define svn_pool_destroy apr_pool_destroy


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_POOLS_H */
