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

#ifndef MODPERL_ENV_H
#define MODPERL_ENV_H

#ifndef ENVHV
#   define ENVHV GvHV(PL_envgv)
#endif

#define modperl_env_untie(mg_flags) \
    MP_magical_untie(ENVHV, mg_flags)

#define modperl_env_tie(mg_flags) \
    MP_magical_tie(ENVHV, mg_flags)

#define modperl_envelem_tie(sv, key, klen) \
    sv_magicext(sv, (SV *)NULL, PERL_MAGIC_envelem, &MP_vtbl_envelem, key, klen)

void modperl_env_hash_keys(pTHX);

void modperl_env_clear(pTHX);

void modperl_env_hv_store(pTHX_ const char *key, const char *val);

void modperl_env_sync_srv_env_hash2table(pTHX_ apr_pool_t *p,
                                         modperl_config_srv_t *scfg);

void modperl_env_sync_dir_env_hash2table(pTHX_ apr_pool_t *p,
                                         modperl_config_dir_t *dcfg);

void modperl_env_configure_server(pTHX_ apr_pool_t *p, server_rec *s);

void modperl_env_configure_request_srv(pTHX_ request_rec *r);

void modperl_env_configure_request_dir(pTHX_ request_rec *r);

void modperl_env_default_populate(pTHX);

void modperl_env_request_populate(pTHX_ request_rec *r);

void modperl_env_request_unpopulate(pTHX_ request_rec *r);

void modperl_env_request_tie(pTHX_ request_rec *r);

void modperl_env_request_untie(pTHX_ request_rec *r);

void modperl_env_init(pTHX);

void modperl_env_unload(pTHX);

extern MGVTBL MP_vtbl_env;
extern MGVTBL MP_vtbl_envelem;

#endif /* MODPERL_ENV_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
