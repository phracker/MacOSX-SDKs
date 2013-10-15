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
 * @file svn_user.h
 * @brief Subversion's wrapper around APR's user information interface.
 */

#ifndef SVN_USER_H
#define SVN_USER_H

#include <apr_pools.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Get the name of the current user, using @a pool for any necessary
 * allocation, returning NULL on error.
 *
 * @since New in 1.4.
 */
const char *
svn_user_get_name(apr_pool_t *pool);

/** Get the path of the current user's home directory, using @a pool for
 * any necessary allocation, returning NULL on error.
 *
 * @since New in 1.4.
 */
const char *
svn_user_get_homedir(apr_pool_t *pool);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_USER_H */
