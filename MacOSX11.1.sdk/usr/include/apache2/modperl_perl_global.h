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

#ifndef MODPERL_PERL_GLOBAL_H
#define MODPERL_PERL_GLOBAL_H

#define MP_MODGLOBAL_FETCH(gkey)                                        \
    hv_fetch_he(PL_modglobal, (char *)gkey->val, gkey->len, gkey->hash)

#define MP_MODGLOBAL_STORE_HV(gkey)                                     \
    (HV*)*hv_store(PL_modglobal, gkey->val, gkey->len,                  \
                   (SV*)newHV(), gkey->hash)

typedef struct {
    const char *name;
    const char *val;
    I32 len;
    U32 hash;
} modperl_modglobal_key_t;

typedef enum {
    MP_MODGLOBAL_END
} modperl_modglobal_key_e;

typedef struct {
    AV **av;
    modperl_modglobal_key_e key;
} modperl_perl_global_avcv_t;

typedef struct {
    GV *gv;
    AV *tmpav;
    AV *origav;
} modperl_perl_global_gvav_t;

typedef struct {
    GV *gv;
    HV *tmphv;
    HV *orighv;
} modperl_perl_global_gvhv_t;

typedef struct {
    GV *gv;
    char flags;
} modperl_perl_global_gvio_t;

typedef struct {
    SV **sv;
    char pv[256]; /* XXX: only need enough for $/ at the moment */
    I32 cur;
} modperl_perl_global_svpv_t;

typedef struct {
    modperl_perl_global_avcv_t end;
    modperl_perl_global_gvhv_t env;
    modperl_perl_global_gvav_t inc;
    modperl_perl_global_gvio_t defout;
    modperl_perl_global_svpv_t rs;
} modperl_perl_globals_t;

void modperl_modglobal_hash_keys(pTHX);

modperl_modglobal_key_t *modperl_modglobal_lookup(pTHX_ const char *name);

void modperl_perl_global_request_save(pTHX_ request_rec *r);

void modperl_perl_global_request_restore(pTHX_ request_rec *r);

void modperl_perl_global_avcv_register(pTHX_ modperl_modglobal_key_t *gkey,
                                       const char *package, I32 packlen);

void modperl_perl_global_avcv_call(pTHX_ modperl_modglobal_key_t *gkey,
                                   const char *package, I32 packlen);

void modperl_perl_global_avcv_clear(pTHX_ modperl_modglobal_key_t *gkey,
                                    const char *package, I32 packlen);

#endif

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
