/*
 * mod_dav_svn.h: public header for the DAV/SVN Apache module
 *
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
 */


#ifndef MOD_DAV_SVN_H
#define MOD_DAV_SVN_H

#include <httpd.h>
#include <mod_dav.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Given an apache request R, a URI, and a ROOT_PATH to the svn
   location block, process URI and return many things, allocated in
   r->pool:

   * CLEANED_URI:     The uri with duplicate and trailing slashes removed.

   * TRAILING_SLASH:  Whether the uri had a trailing slash on it.

   Three special substrings of the uri are returned for convenience:

   * REPOS_NAME:      The single path component that is the directory
                      which contains the repository.

   * RELATIVE_PATH:   The remaining imaginary path components.

   * REPOS_PATH:      The actual path within the repository filesystem, or
                      NULL if no part of the uri refers to a path in
                      the repository (e.g. "!svn/vcc/default" or
                      "!svn/bln/25").


   For example, consider the uri

       /svn/repos/proj1/!svn/blah/13//A/B/alpha

   In the SVNPath case, this function would receive a ROOT_PATH of
   '/svn/repos/proj1', and in the SVNParentPath case would receive a
   ROOT_PATH of '/svn/repos'.  But either way, we would get back:

     * CLEANED_URI:    /svn/repos/proj1/!svn/blah/13/A/B/alpha
     * REPOS_NAME:     proj1
     * RELATIVE_PATH:  /!svn/blah/13/A/B/alpha
     * REPOS_PATH:     A/B/alpha
     * TRAILING_SLASH: FALSE
*/
AP_MODULE_DECLARE(dav_error *) dav_svn_split_uri(request_rec *r,
                                                 const char *uri,
                                                 const char *root_path,
                                                 const char **cleaned_uri,
                                                 int *trailing_slash,
                                                 const char **repos_name,
                                                 const char **relative_path,
                                                 const char **repos_path);


/* Given an apache request R and a ROOT_PATH to the svn location
   block sets *REPOS_PATH to the path of the repository on disk.
*/
AP_MODULE_DECLARE(dav_error *) dav_svn_get_repos_path(request_rec *r,
                                                      const char *root_path,
                                                      const char **repos_path);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MOD_DAV_SVN_H */
