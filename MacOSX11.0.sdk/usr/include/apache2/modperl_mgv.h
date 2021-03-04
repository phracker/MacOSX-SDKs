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

#ifndef MODPERL_MGV_H
#define MODPERL_MGV_H

modperl_mgv_t *modperl_mgv_new(apr_pool_t *p);

int modperl_mgv_equal(modperl_mgv_t *mgv1,
                      modperl_mgv_t *mgv2);

modperl_mgv_t *modperl_mgv_compile(pTHX_ apr_pool_t *p, const char *name);

GV *modperl_mgv_lookup(pTHX_ modperl_mgv_t *symbol);

GV *modperl_mgv_lookup_autoload(pTHX_ modperl_mgv_t *symbol,
                                server_rec *s, apr_pool_t *p);

int modperl_mgv_resolve(pTHX_ modperl_handler_t *handler,
                        apr_pool_t *p, const char *name, int logfailure);

void modperl_mgv_append(pTHX_ apr_pool_t *p, modperl_mgv_t *symbol,
                        const char *name);

modperl_mgv_t *modperl_mgv_last(modperl_mgv_t *symbol);

char *modperl_mgv_last_name(modperl_mgv_t *symbol);

char *modperl_mgv_as_string(pTHX_ modperl_mgv_t *symbol,
                            apr_pool_t *p, int package);

#ifdef USE_ITHREADS
int modperl_mgv_require_module(pTHX_ modperl_mgv_t *symbol,
                               server_rec *s, apr_pool_t *p);
#endif

void modperl_mgv_hash_handlers(apr_pool_t *p, server_rec *s);

#define modperl_mgv_sv(sv) \
(isGV(sv) ? GvSV(sv) : (SV*)sv)

#define modperl_mgv_cv(sv) \
GvCV(sv)

#endif /* MODPERL_MGV_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
