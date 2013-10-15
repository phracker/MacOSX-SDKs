/**
 * @copyright
 * ====================================================================
 * Copyright (c) 2007 CollabNet.  All rights reserved.
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
 * @file mod_authz_svn.h
 * @brief Subversion authorization extensions for mod_dav_svn
 */

#ifndef MOD_AUTHZ_SVN_H
#define MOD_AUTHZ_SVN_H

#include <httpd.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * mod_dav_svn to mod_authz_svn bypass mechanism
 */
#define AUTHZ_SVN__SUBREQ_BYPASS_PROV_GRP "dav2authz_subreq_bypass"
#define AUTHZ_SVN__SUBREQ_BYPASS_PROV_NAME "mod_authz_svn_subreq_bypass"
#define AUTHZ_SVN__SUBREQ_BYPASS_PROV_VER "00.00a"
typedef int (*authz_svn__subreq_bypass_func_t)(request_rec *r,
                                              const char *repos_path,
                                              const char *repos_name);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
