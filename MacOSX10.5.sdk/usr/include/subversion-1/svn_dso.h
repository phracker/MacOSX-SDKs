/**
 * @copyright
 * ====================================================================
 * Copyright (c) 2006 CollabNet.  All rights reserved.
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
 * @file svn_dso.h
 * @brief DSO loading routines
 */



#ifndef SVN_DSO_H
#define SVN_DSO_H

#include <apr_dso.h>

#include "svn_error.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Initialize the DSO loading routines.
 *
 * @note This should be called prior to the creation of any pool that
 *       is passed to a function that comes from a DSO, otherwise you
 *       risk having the DSO unloaded before all pool cleanup callbacks
 *       that live in the DSO have been executed.  If it is not called
 *       prior to @c svn_dso_load being used for the first time there
 *       will be a best effort attempt made to initialize the subsystem,
 *       but it will not be entirely thread safe and it risks running
 *       into the previously mentioned problems with DSO unloading and
 *       pool cleanup callbacks.
 *
 * @since New in 1.4.0.
 */
void svn_dso_initialize(void);

#if APR_HAS_DSO
/**
 * Attempt to load @a libname, returning it in @a dso.
 *
 * If @a libname cannot be loaded set @a dso to NULL and return
 * @c SVN_NO_ERROR.
 *
 * @note Due to pool lifetime issues DSOs are all loaded into a global
 *       pool, so you must be certain that there is a bounded number of
 *       them that will ever be loaded by the system, otherwise you will
 *       leak memory.
 *
 * @since New in 1.4.0.
 */
svn_error_t *svn_dso_load(apr_dso_handle_t **dso, const char *libname);
#endif /* APR_HAS_DSO */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SVN_DSO_H */
