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

#ifndef MODPERL_HANDLER_H
#define MODPERL_HANDLER_H

typedef enum {
    MP_HANDLER_ACTION_GET,
    MP_HANDLER_ACTION_PUSH,
    MP_HANDLER_ACTION_SET
} modperl_handler_action_e;

void modperl_handler_anon_init(pTHX_ apr_pool_t *p);
MP_INLINE modperl_mgv_t *modperl_handler_anon_next(pTHX_ apr_pool_t *p);
MP_INLINE void modperl_handler_anon_add(pTHX_ modperl_mgv_t *anon, CV *cv);
MP_INLINE CV *modperl_handler_anon_get(pTHX_ modperl_mgv_t *anon);

#define modperl_handler_array_new(p) \
apr_array_make(p, 1, sizeof(modperl_handler_t *))

#define modperl_handler_array_push(handlers, h) \
*(modperl_handler_t **)apr_array_push(handlers) = h

#define modperl_handler_array_item(handlers, idx) \
((modperl_handler_t **)(handlers)->elts)[idx]

#define modperl_handler_array_last(handlers) \
modperl_handler_array_item(handlers, ((handlers)->nelts - 1))

modperl_handler_t *modperl_handler_new(apr_pool_t *p, const char *name);

modperl_handler_t *modperl_handler_new_from_sv(pTHX_ apr_pool_t *p, SV *sv);

MP_INLINE const char *modperl_handler_name(modperl_handler_t *handler);

int modperl_handler_resolve(pTHX_ modperl_handler_t **handp,
                            apr_pool_t *p, server_rec *s);

modperl_handler_t *modperl_handler_dup(apr_pool_t *p,
                                       modperl_handler_t *h);

int modperl_handler_equal(modperl_handler_t *h1, modperl_handler_t *h2);

MpAV *modperl_handler_array_merge(apr_pool_t *p, MpAV *base_a, MpAV *add_a);

void modperl_handler_make_args(pTHX_ AV **avp, ...);

MpAV **modperl_handler_lookup_handlers(modperl_config_dir_t *dcfg,
                                       modperl_config_srv_t *scfg,
                                       modperl_config_req_t *rcfg,
                                       apr_pool_t *p,
                                       int type, int idx,
                                       modperl_handler_action_e action,
                                       const char **desc);

MpAV **modperl_handler_get_handlers(request_rec *r, conn_rec *c,server_rec *s,
                                    apr_pool_t *p, const char *name,
                                    modperl_handler_action_e action);

int modperl_handler_push_handlers(pTHX_ apr_pool_t *p,
                                  MpAV *handlers, SV *sv);

SV *modperl_handler_perl_get_handlers(pTHX_ MpAV **handp, apr_pool_t *p);

int modperl_handler_perl_add_handlers(pTHX_
                                      request_rec *r,
                                      conn_rec *c,
                                      server_rec *s,
                                      apr_pool_t *p,
                                      const char *name,
                                      SV *sv,
                                      modperl_handler_action_e action);

#endif /* MODPERL_HANDLER_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
