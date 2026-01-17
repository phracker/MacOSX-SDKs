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

#ifndef MODPERL_ERROR_H
#define MODPERL_ERROR_H

/*** mod_perl custom errors come here ***/

/* to check whether $@ is set by ModPerl::Util::exit */
#define MODPERL_RC_EXIT        APR_OS_START_USERERR + 0
/* indicate the filter error problem */
#define MODPERL_FILTER_ERROR   APR_OS_START_USERERR + 1

/**
 * return the string representation of the error code
 * @param rc   error code
 * @return     the error string
 *
 * The return value must be immediately copied unless used only in a
 * limited visible scope where it's clear that Perl_form() is not
 * called again (which could happen indirectly). If unsure, copy.
 */
char *modperl_error_strerror(pTHX_ apr_status_t rc);

void modperl_croak(pTHX_ apr_status_t rc, const char* func);

#ifdef USE_ITHREADS
#define MP_PUTBACK_IF_USED() STMT_START                                 \
    {                                                                   \
        modperl_interp_t *interp = modperl_thx_interp_get(aTHX);        \
        if (interp && interp->refcnt > 1) {                             \
            modperl_interp_unselect(interp);                            \
        }                                                               \
    } STMT_END
#else
#define MP_PUTBACK_IF_USED() NOOP
#endif

#define MP_CROAK_PUTBACK(rc, func) STMT_START                           \
    {                                                                   \
        MP_PUTBACK_IF_USED();                                           \
        modperl_croak(aTHX_ rc, func);                                  \
    } STMT_END

#define MP_RUN_CROAK(rc_run, func) STMT_START                \
    {                                                        \
        apr_status_t rc = rc_run;                            \
        if (rc != APR_SUCCESS) {                             \
            modperl_croak(aTHX_ rc, func);                   \
        }                                                    \
    } STMT_END

#define MP_RUN_CROAK_PUTBACK(rc_run, func) STMT_START        \
    {                                                        \
        apr_status_t rc = rc_run;                            \
        if (rc != APR_SUCCESS) {                             \
            MP_PUTBACK_IF_USED();                            \
            modperl_croak(aTHX_ rc, func);                   \
        }                                                    \
    } STMT_END

#define MP_RUN_CROAK_RESET_OK(s, rc_run, func) STMT_START               \
    {                                                                   \
        apr_status_t rc = rc_run;                                       \
        if (rc != APR_SUCCESS) {                                        \
            if (APR_STATUS_IS_ECONNRESET(rc) ||                         \
                APR_STATUS_IS_ECONNABORTED(rc)) {                       \
                ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,              \
                             "%s got: %s", func,                        \
                             modperl_error_strerror(aTHX_ rc));         \
            }                                                           \
            else {                                                      \
                modperl_croak(aTHX_ rc, func);                          \
            }                                                           \
        }                                                               \
    } STMT_END

#define MP_RUN_CROAK_RESET_OK_PUTBACK(s, rc_run, func) STMT_START       \
    {                                                                   \
        apr_status_t rc = rc_run;                                       \
        if (rc != APR_SUCCESS) {                                        \
            if (APR_STATUS_IS_ECONNRESET(rc) ||                         \
                APR_STATUS_IS_ECONNABORTED(rc)) {                       \
                ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,              \
                             "%s got: %s", func,                        \
                             modperl_error_strerror(aTHX_ rc));         \
            }                                                           \
            else {                                                      \
                MP_PUTBACK_IF_USED();                                   \
                modperl_croak(aTHX_ rc, func);                          \
            }                                                           \
        }                                                               \
    } STMT_END

#endif /* MODPERL_ERROR_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
