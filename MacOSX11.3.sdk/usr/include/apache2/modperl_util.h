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

#ifndef MODPERL_UTIL_H
#define MODPERL_UTIL_H

#include "modperl_common_util.h"

/* check whether the response phase has been initialized already */
#define MP_CHECK_WBUCKET_INIT(func) \
    if (!rcfg->wbucket) { \
        Perl_croak(aTHX_ "%s: " func " can't be called "  \
                   "before the response phase", MP_FUNC); \
    }

/* turn off cgi header parsing. in case we are already inside
 *     modperl_callback_per_dir(MP_RESPONSE_HANDLER, r, MP_HOOK_RUN_FIRST);
 * but haven't sent any data yet, it's too late to change
 * MpReqPARSE_HEADERS, so change the wbucket's private flag directly
 */
#define MP_CGI_HEADER_PARSER_OFF(rcfg) \
    MpReqPARSE_HEADERS_Off(rcfg); \
    if (rcfg->wbucket) { \
        rcfg->wbucket->header_parse = 0; \
    }

MP_INLINE server_rec *modperl_sv2server_rec(pTHX_ SV *sv);
MP_INLINE request_rec *modperl_sv2request_rec(pTHX_ SV *sv);

request_rec *modperl_xs_sv2request_rec(pTHX_ SV *sv, char *classname, CV *cv);

MP_INLINE SV *modperl_newSVsv_obj(pTHX_ SV *stashsv, SV *obj);

MP_INLINE SV *modperl_ptr2obj(pTHX_ char *classname, void *ptr);

int modperl_errsv(pTHX_ int status, request_rec *r, server_rec *s);

void modperl_errsv_prepend(pTHX_ const char *pat, ...);

int modperl_require_module(pTHX_ const char *pv, int logfailure);
int modperl_require_file(pTHX_ const char *pv, int logfailure);

void modperl_xs_dl_handles_clear(pTHX);

void **modperl_xs_dl_handles_get(pTHX);

void modperl_xs_dl_handles_close(void **handles);

modperl_cleanup_data_t *modperl_cleanup_data_new(apr_pool_t *p, void *data);

MP_INLINE void modperl_perl_av_push_elts_ref(pTHX_ AV *dst, AV *src);

HE *modperl_perl_hv_fetch_he(pTHX_ HV *hv,
                             register char *key,
                             register I32 klen,
                             register U32 hash);

#define hv_fetch_he(hv,k,l,h) \
    modperl_perl_hv_fetch_he(aTHX_ hv, k, l, h)

void modperl_str_toupper(char *str);

void modperl_perl_do_sprintf(pTHX_ SV *sv, I32 len, SV **sarg);

void modperl_perl_call_list(pTHX_ AV *subs, const char *name);

void modperl_perl_exit(pTHX_ int status);

MP_INLINE SV *modperl_dir_config(pTHX_ request_rec *r, server_rec *s,
                                 char *key, SV *sv_val);

SV *modperl_table_get_set(pTHX_ apr_table_t *table, char *key,
                          SV *sv_val, int do_taint);

MP_INLINE int modperl_perl_module_loaded(pTHX_ const char *name);

/**
 * slurp the contents of r->filename and return them as a scalar
 * @param r       request record
 * @param tainted whether the SV should be marked tainted or not
 * @return a PV scalar with the contents of the file
 */
SV *modperl_slurp_filename(pTHX_ request_rec *r, int tainted);

char *modperl_file2package(apr_pool_t *p, const char *file);

SV *modperl_apr_array_header2avrv(pTHX_ apr_array_header_t *array);
apr_array_header_t *modperl_avrv2apr_array_header(pTHX_ apr_pool_t *p,
                                                  SV *avrv);
void modperl_package_unload(pTHX_ const char *package);
#if defined(MP_TRACE) && defined(USE_ITHREADS)
#define MP_TRACEf_PERLID   "perl id 0x%lx"
#define MP_TRACEv_PERLID   (unsigned long)my_perl
#define MP_TRACEv_PERLID_  MP_TRACEv_PERLID,
#define MP_TRACEv__PERLID  ,MP_TRACEv_PERLID
#else
#define MP_TRACEf_PERLID
#define MP_TRACEv_PERLID
#define MP_TRACEv_PERLID_
#define MP_TRACEv__PERLID
#endif /* USE_ITHREADS */

/* dumping hundreds of lines in the trace, makes it less useful. Get a
 * string chunk of MP_TRACE_STR_LEN bytes or less. Not too long so it
 * won't wrap when posted in email. Notice that we copy 'count' bytes
 * of the string even if count < MP_TRACE_STR_LEN, because the 'str'
 * buffer doesn't necessarily have \0 terminator at 'count'. As this
 * is for debug tracing, not to be used in production, it doesn't make
 * any difference if it's not efficient.
 */
#define MP_TRACE_STR_LEN 35
#define MP_TRACE_STR_TRUNC(p, str, count)                                \
    count < MP_TRACE_STR_LEN                                             \
        ? (char *)apr_pstrmemdup(p, str, count)                          \
        : (char *)apr_psprintf(p, "%s...",                               \
                               apr_pstrmemdup(p, str, MP_TRACE_STR_LEN))

/* functions maintaining the amount of times mod_perl was restarted,
 * e.g. on Apache start, it restarts itself, so the count will be
 * first 1, and on on restart 2 */
void modperl_restart_count_inc(server_rec *base_server);
int  modperl_restart_count(void);

void modperl_pnotes_kill(void *data);

SV *modperl_pnotes(pTHX_ modperl_pnotes_t *pnotes, SV *key, SV *val,
                   apr_pool_t *pool );

U16 *modperl_code_attrs(pTHX_ CV *cv);

#if AP_SERVER_MAJORVERSION_NUMBER>2 || \
    (AP_SERVER_MAJORVERSION_NUMBER == 2 && AP_SERVER_MINORVERSION_NUMBER>=3)
apr_status_t
modperl_register_auth_provider(apr_pool_t *pool, const char *provider_group,
                               const char *provider_name,
                               const char *provider_version, SV *callback1,
                               SV *callback2, int type);

apr_status_t
modperl_register_auth_provider_name(apr_pool_t *pool,
                                    const char *provider_group,
                                    const char *provider_name,
                                    const char *provider_version,
                                    const char *callback1,
                                    const char *callback2, int type);
#endif

#endif /* MODPERL_UTIL_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
