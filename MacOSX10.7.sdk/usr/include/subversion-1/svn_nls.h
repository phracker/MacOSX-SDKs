/**
 * @copyright
 * ====================================================================
 * Copyright (c) 2000-2005, 2008 CollabNet.  All rights reserved.
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
 * @file svn_nls.h
 * @brief Support functions for NLS programs
 */



#ifndef SVN_NLS_H
#define SVN_NLS_H

#include "svn_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Set up the NLS.
 * Return the error @c APR_EINVAL or @c APR_INCOMPLETE if an
 * error occurs.
 *
 * @note This function is for bindings. You should usually
 *       use svn_cmdline_init() instead of calling this
 *       function directly. This function should be called
 *       after initializing APR.
 *
 * @since New in 1.3.
 */
svn_error_t *
svn_nls_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_NLS_H */
