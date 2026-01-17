/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MOD_PERL_H
#define MOD_PERL_H

#include "modperl_apache_includes.h"
#include "modperl_common_includes.h"
#include "modperl_apache_compat.h"

#ifdef WIN32
#define MP_THREADED 1
#else
#define MP_THREADED (defined(USE_ITHREADS) && APR_HAS_THREADS)
#endif

extern module AP_MODULE_DECLARE_DATA perl_module;

#include "modperl_error.h"
#include "modperl_flags.h"
#include "modperl_hooks.h"
#include "modperl_perl_global.h"
#include "modperl_perl_pp.h"
#include "modperl_sys.h"
#include "modperl_const.h"
#include "modperl_constants.h"

/* both perl and apr have largefile support enabled */
#if defined(USE_LARGE_FILES) && APR_HAS_LARGE_FILES
#define MP_LARGE_FILES_ENABLED
#endif

/* both perl and apr have largefile support disabled */
#if (!defined(USE_LARGE_FILES)) && !APR_HAS_LARGE_FILES
#define MP_LARGE_FILES_DISABLED
#endif

/* perl largefile support is enabled, apr support is disabled */
#if defined(USE_LARGE_FILES) && !APR_HAS_LARGE_FILES
#define MP_LARGE_FILES_PERL_ONLY
#endif

/* apr largefile support is enabled, perl support is disabled */
#if (!defined(USE_LARGE_FILES)) && APR_HAS_LARGE_FILES
#define MP_LARGE_FILES_APR_ONLY
#endif

/* conflict due to not have either both perl and apr
 * support enabled or both disabled
 */
#if defined(MP_LARGE_FILES_APR_ONLY) || defined(MP_LARGE_FILES_PERL_ONLY)
#define MP_LARGE_FILES_CONFLICT
#endif

#ifdef MP_USE_GTOP
#include "modperl_gtop.h"
#endif
#include "modperl_time.h"
#include "modperl_types.h"
#include "modperl_util.h"
#include "modperl_config.h"
#include "modperl_cmd.h"
#include "modperl_handler.h"
#include "modperl_callback.h"
#include "modperl_tipool.h"
#include "modperl_interp.h"
#include "modperl_log.h"
#include "modperl_options.h"
#include "modperl_directives.h"
#include "modperl_io.h"
#include "modperl_io_apache.h"
#include "modperl_filter.h"
#include "modperl_bucket.h"
#include "modperl_pcw.h"
#include "modperl_mgv.h"
#include "modperl_global.h"
#include "modperl_env.h"
#include "modperl_cgi.h"
#include "modperl_perl.h"
#include "modperl_svptr_table.h"
#include "modperl_module.h"
#include "modperl_debug.h"

int modperl_threads_started(void);
int modperl_threaded_mpm(void);
int modperl_post_post_config_phase(void);

#define MP_CROAK_IF_THREADS_STARTED(what)                       \
    if (modperl_threads_started()) {                            \
        Perl_croak(aTHX_ "Can't run '%s' in the threaded "      \
                   "environment after server startup", what);   \
    }

#define MP_CROAK_IF_THREADED_MPM(what)                          \
    if (modperl_threaded_mpm()) {                               \
        Perl_croak(aTHX_ "Can't run '%s' in a threaded mpm",    \
                   what);                                       \
    }

#define MP_CROAK_IF_POST_POST_CONFIG_PHASE(what)                \
    if (modperl_post_post_config_phase()) {                     \
        Perl_croak(aTHX_ "Can't run '%s' after server startup", \
                   what);                                       \
    }

int modperl_init_vhost(server_rec *s, apr_pool_t *p,
                       server_rec *base_server);
void modperl_init(server_rec *s, apr_pool_t *p);
void modperl_init_globals(server_rec *s, apr_pool_t *pconf);
int modperl_run(void);
int modperl_is_running(void);
int modperl_hook_init(apr_pool_t *pconf, apr_pool_t *plog,
                      apr_pool_t *ptemp, server_rec *s);
int modperl_hook_pre_config(apr_pool_t *p, apr_pool_t *plog,
                            apr_pool_t *ptemp);
void modperl_register_hooks(apr_pool_t *p);
apr_pool_t *modperl_server_pool(void);
apr_pool_t *modperl_server_user_pool(void);
PerlInterpreter *modperl_startup(server_rec *s, apr_pool_t *p);
int modperl_perl_destruct_level(void);
void xs_init(pTHX);

void modperl_response_init(request_rec *r);
apr_status_t modperl_response_finish(request_rec *r);
int modperl_response_handler(request_rec *r);
int modperl_response_handler_cgi(request_rec *r);

#define MgTypeExt(mg) (mg->mg_type == '~')

typedef void MP_FUNC_NONSTD_T(modperl_var_modify_t) (apr_table_t *,
                                                     apr_table_t *,
                                                     const char *,
                                                     const char *);

/* we need to hook a few internal things before APR_HOOK_REALLY_FIRST */
#define MODPERL_HOOK_REALLY_REALLY_FIRST (-20)

#ifdef USE_ITHREADS
APR_DECLARE_OPTIONAL_FN(apr_status_t,modperl_interp_unselect,(void *));
APR_DECLARE_OPTIONAL_FN(modperl_interp_t *,modperl_thx_interp_get,(PerlInterpreter *));
#endif

/*
 * perl context overriding and restoration is required when
 * PerlOptions +Parent/+Clone is used in vhosts, and perl is used to
 * at the server startup. So that <Perl> sections, PerlLoadModule,
 * PerlModule and PerlRequire are all run using the right perl context
 * and restore to the original context when they are done.
 *
 * As of perl-5.8.3 it's unfortunate that it uses PERL_GET_CONTEXT and
 * doesn't rely on the passed pTHX internally. When and if perl is
 * fixed to always use pTHX if available, this context switching mess
 * can be removed.
 */
#ifdef USE_ITHREADS

#define MP_PERL_CONTEXT_DECLARE                 \
    PerlInterpreter *orig_perl = NULL;          \
    pTHX;

#define MP_PERL_CONTEXT_STORE                   \
    orig_perl = PERL_GET_CONTEXT;

#define MP_PERL_CONTEXT_OVERRIDE(new_perl)      \
    aTHX = new_perl;                            \
    PERL_SET_CONTEXT(aTHX);

#define MP_PERL_CONTEXT_STORE_OVERRIDE(new_perl)        \
    MP_PERL_CONTEXT_STORE;                              \
    MP_PERL_CONTEXT_OVERRIDE(new_perl)

#define MP_PERL_CONTEXT_RESTORE                 \
    if (orig_perl) {                            \
        PERL_SET_CONTEXT(orig_perl);            \
    }

#else /* #ifdef USE_ITHREADS */

#define MP_PERL_CONTEXT_DECLARE
#define MP_PERL_CONTEXT_STORE
#define MP_PERL_CONTEXT_OVERRIDE(new_perl)
#define MP_PERL_CONTEXT_STORE_OVERRIDE(new_perl)
#define MP_PERL_CONTEXT_RESTORE

#endif /* end of #ifdef USE_ITHREADS */

#endif /*  MOD_PERL_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
