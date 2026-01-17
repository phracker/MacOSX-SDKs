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

#ifndef MODPERL_CONFIG_H
#define MODPERL_CONFIG_H

void *modperl_config_dir_create(apr_pool_t *p, char *dir);

void *modperl_config_dir_merge(apr_pool_t *p, void *basev, void *addv);

modperl_config_srv_t *modperl_config_srv_new(apr_pool_t *p, server_rec *s);

modperl_config_dir_t *modperl_config_dir_new(apr_pool_t *p);

modperl_config_req_t *modperl_config_req_new(request_rec *r);

modperl_config_con_t *modperl_config_con_new(conn_rec *c);

void *modperl_config_srv_create(apr_pool_t *p, server_rec *s);

void *modperl_config_srv_merge(apr_pool_t *p, void *basev, void *addv);

char **modperl_config_srv_argv_init(modperl_config_srv_t *scfg, int *argc);

#define modperl_config_srv_argv_push(arg)               \
    *(const char **)apr_array_push(scfg->argv) = (arg)

apr_status_t modperl_config_request_cleanup(pTHX_ request_rec *r);

apr_status_t modperl_config_req_cleanup(void *data);

/* use a subpool here to ensure that a PerlCleanupHandler is run before
 * any other pool cleanup - suppools are destroyed first. Particularly a
 * PerlCleanupHandler must run before request pnotes are dropped.
 */
#define modperl_config_req_cleanup_register(r, rcfg)           \
    if (r && !MpReqCLEANUP_REGISTERED(rcfg)) {                 \
        apr_pool_t *p;                           \
        apr_pool_create(&p, (r)->pool);                 \
        apr_pool_cleanup_register(p,                   \
                                  (void*)(r),                  \
                                  modperl_config_req_cleanup,  \
                                  apr_pool_cleanup_null);      \
        MpReqCLEANUP_REGISTERED_On(rcfg);                      \
    }

void *modperl_get_perl_module_config(ap_conf_vector_t *cv);
void modperl_set_perl_module_config(ap_conf_vector_t *cv, void *cfg);

#if defined(MP_IN_XS) && defined(WIN32)
#   define modperl_get_module_config(v)         \
    modperl_get_perl_module_config((v))

#   define modperl_set_module_config(v, c)      \
    modperl_set_perl_module_config((v), (c))
#else
#   define modperl_get_module_config(v)         \
    ap_get_module_config((v), &perl_module)

#   define modperl_set_module_config(v, c)      \
    ap_set_module_config((v), &perl_module, (c))
#endif

#define modperl_config_req_init(r, rcfg)                    \
    if (!(rcfg)) {                                          \
        (rcfg) = modperl_config_req_new(r);                 \
        modperl_set_module_config((r)->request_config, (rcfg)); \
    }

#define modperl_config_req_get(r)                               \
    (r ? (modperl_config_req_t *)                               \
     modperl_get_module_config((r)->request_config) : NULL)

#define MP_dRCFG \
    modperl_config_req_t *rcfg = modperl_config_req_get(r)

#define modperl_config_con_init(c, ccfg)                 \
    if (!ccfg) {                                         \
        ccfg = modperl_config_con_new(c);                \
        modperl_set_module_config((c)->conn_config, (ccfg)); \
    }

#define modperl_config_con_get(c)                               \
    (c ? (modperl_config_con_t *)                               \
     modperl_get_module_config((c)->conn_config) : NULL)

#define MP_dCCFG \
    modperl_config_con_t *ccfg = modperl_config_con_get(c)

#define modperl_config_dir_get(r)                               \
    (r ? (modperl_config_dir_t *)                               \
     modperl_get_module_config((r)->per_dir_config) : NULL)

#define modperl_config_dir_get_defaults(s)              \
    (modperl_config_dir_t *)                            \
        modperl_get_module_config((s)->lookup_defaults)

#define MP_dDCFG \
    modperl_config_dir_t *dcfg = modperl_config_dir_get(r)

#define modperl_config_srv_get(s)                       \
    (modperl_config_srv_t *)                            \
        modperl_get_module_config(s->module_config)

#define MP_dSCFG(s)                                             \
    modperl_config_srv_t *scfg = modperl_config_srv_get(s)

int modperl_config_apply_PerlModule(server_rec *s,
                                    modperl_config_srv_t *scfg,
                                    PerlInterpreter *perl, apr_pool_t *p);

int modperl_config_apply_PerlRequire(server_rec *s,
                                     modperl_config_srv_t *scfg,
                                     PerlInterpreter *perl, apr_pool_t *p);

int modperl_config_apply_PerlPostConfigRequire(server_rec *s,
                                               modperl_config_srv_t *scfg,
                                               apr_pool_t *p);

const char *modperl_config_insert(pTHX_ server_rec *s,
                                  apr_pool_t *p,
                                  apr_pool_t *ptmp,
                                  int override,
                                  char *path,
                                  int override_options,
                                  ap_conf_vector_t *conf,
                                  SV *lines);

const char *modperl_config_insert_parms(pTHX_ cmd_parms *parms,
                                        SV *lines);

const char *modperl_config_insert_server(pTHX_ server_rec *s, SV *lines);

const char *modperl_config_insert_request(pTHX_
                                          request_rec *r,
                                          SV *lines,
                                          int override,
                                          char *path,
                                          int override_options);

int modperl_config_is_perl_option_enabled(pTHX_ request_rec *r,
                                          server_rec *s, const char *name);


#endif /* MODPERL_CONFIG_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
