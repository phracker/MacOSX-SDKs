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

#ifndef MODPERL_GLOBAL_H
#define MODPERL_GLOBAL_H

typedef struct {
#if MP_THREADED
    perl_mutex glock;
#endif
    int flags;
    void *data;
    const char *name;
} modperl_global_t;

#if MP_THREADED
typedef apr_threadkey_t modperl_tls_t;
#else
typedef modperl_global_t modperl_tls_t;
#endif

void modperl_global_request_cfg_set(request_rec *r);

request_rec *modperl_global_request(pTHX_ SV *svr);

void modperl_global_request_set(request_rec *r);

void modperl_global_request_obj_set(pTHX_ SV *svr);

void modperl_global_init(modperl_global_t *global, apr_pool_t *p,
                         void *data, const char *name);

void modperl_global_lock(modperl_global_t *global);

void modperl_global_unlock(modperl_global_t *global);

void *modperl_global_get(modperl_global_t *global);

void modperl_global_set(modperl_global_t *global, void *data);

#define MP_GLOBAL_DECL(gname, type)                                \
    void modperl_global_init_##gname(apr_pool_t *p, type gname);   \
    void modperl_global_lock_##gname(void);                        \
    void modperl_global_unlock_##gname(void);                      \
    type modperl_global_get_##gname(void);                         \
    void modperl_global_set_##gname(void *)

/* modperl_global_get_pconf returns a thread un-safe object */
MP_GLOBAL_DECL(pconf, apr_pool_t *);

/* modperl_global_get_server_rec returns a thread un-safe object */
MP_GLOBAL_DECL(server_rec, server_rec *);

void modperl_global_anon_cnt_init(apr_pool_t *p);
int modperl_global_anon_cnt_next(void);

apr_status_t modperl_tls_create(apr_pool_t *p, modperl_tls_t **key);
apr_status_t modperl_tls_get(modperl_tls_t *key, void **data);
apr_status_t modperl_tls_set(modperl_tls_t *key, void *data);
void modperl_tls_reset_cleanup(apr_pool_t *p, modperl_tls_t *key, void *data);

#define MP_TLS_DECL(gname, type) \
apr_status_t modperl_tls_create_##gname(apr_pool_t *p); \
apr_status_t modperl_tls_get_##gname(type *data); \
apr_status_t modperl_tls_set_##gname(void *data); \
void modperl_tls_reset_cleanup_##gname(apr_pool_t *p, type data)

MP_TLS_DECL(request_rec, request_rec *);

#endif /* MODPERL_GLOBAL_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
