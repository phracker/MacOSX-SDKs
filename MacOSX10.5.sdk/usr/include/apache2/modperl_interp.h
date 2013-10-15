/* Copyright 2000-2005 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MODPERL_INTERP_H
#define MODPERL_INTERP_H

void modperl_interp_init(server_rec *s, apr_pool_t *p,
                         PerlInterpreter *perl);

apr_status_t modperl_interp_cleanup(void *data);

#ifdef USE_ITHREADS

/*
 * HvPMROOT will never be used by Perl with PL_modglobal.
 * so we have stolen it as a quick way to stash the interp
 * pointer.
 *
 * However in 5.9.3 HvPMROOT was completely removed, so we have moved
 * to use another struct member that's hopefully won't be used by
 * anybody else. But if we can find a better place to store the
 * pointer to the current mod_perl interpreter object it'd be a much
 * cleaner solution. of course it must be really fast.
 */
#ifndef HvPMROOT
#define MP_THX_INTERP_GET(thx)                                  \
    (modperl_interp_t *) ((XPVMG*)SvANY(*Perl_Imodglobal_ptr(thx)))->xmg_magic
#else
#define MP_THX_INTERP_GET(thx) \
    (modperl_interp_t *)HvPMROOT(*Perl_Imodglobal_ptr(thx))
#endif

#ifndef HvPMROOT
#define MP_THX_INTERP_SET(thx, interp)                          \
    ((XPVMG*)SvANY(*Perl_Imodglobal_ptr(thx)))->xmg_magic = (MAGIC*)interp
#else
#define MP_THX_INTERP_SET(thx, interp)                          \
    HvPMROOT(*Perl_Imodglobal_ptr(thx)) = (PMOP*)interp
#endif

const char *modperl_interp_scope_desc(modperl_interp_scope_e scope);

void modperl_interp_clone_init(modperl_interp_t *interp);

modperl_interp_t *modperl_interp_new(modperl_interp_pool_t *mip,
                                     PerlInterpreter *perl);

void modperl_interp_destroy(modperl_interp_t *interp);

modperl_interp_t *modperl_interp_get(server_rec *s);

apr_status_t modperl_interp_unselect(void *data);

modperl_interp_t *modperl_interp_pool_get(apr_pool_t *p);

void modperl_interp_pool_set(apr_pool_t *p,
                             modperl_interp_t *interp,
                             int cleanup);

modperl_interp_t *modperl_interp_pool_select(apr_pool_t *p,
                                             server_rec *s);

modperl_interp_t *modperl_interp_select(request_rec *r, conn_rec *c,
                                        server_rec *s);

#define MP_dINTERP_SELECT(r, c, s) \
    pTHX; \
    modperl_interp_t *interp = NULL; \
    interp = modperl_interp_select(r, c, s); \
    aTHX = interp->perl

#define MP_INTERP_PUTBACK(interp) \
    if (interp && MpInterpPUTBACK(interp)) { \
        modperl_interp_unselect(interp); \
    }

#define MP_aTHX aTHX

apr_status_t modperl_interp_pool_destroy(void *data);

typedef apr_status_t (*modperl_interp_mip_walker_t)(pTHX_ 
                                                    modperl_interp_pool_t *mip,
                                                    void *data);

void modperl_interp_mip_walk(PerlInterpreter *current_perl,
                             PerlInterpreter *parent_perl,
                             modperl_interp_pool_t *mip,
                             modperl_interp_mip_walker_t walker,
                             void *data);

void modperl_interp_mip_walk_servers(PerlInterpreter *current_perl,
                                     server_rec *base_server,
                                     modperl_interp_mip_walker_t walker,
                                     void *data);
#else

#define MP_dINTERP_SELECT(r, c, s) dNOOP

#define MP_INTERP_PUTBACK(interp) NOOP

#define MP_aTHX 0

#endif /* USE_ITHREADS */

#endif /* MODPERL_INTERP_H */
