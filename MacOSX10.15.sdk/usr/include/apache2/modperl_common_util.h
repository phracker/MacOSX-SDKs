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

#include "modperl_common_includes.h"

#ifndef MODPERL_COMMON_UTIL_H
#define MODPERL_COMMON_UTIL_H

#ifdef MP_DEBUG
#define MP_INLINE
#else
#define MP_INLINE APR_INLINE
#endif

#ifdef CYGWIN
#define MP_STATIC
#else
#define MP_STATIC static
#endif

#ifdef WIN32
#   define MP_FUNC_T(name)          (_stdcall *name)
#   define MP_FUNC_NONSTD_T(name)   (*name)
/* XXX: not all functions get inlined
 * so its unclear what to and not to include in the .def files
 */
#   undef MP_INLINE
#   define MP_INLINE
#else
#   define MP_FUNC_T(name)          (*name)
#   define MP_FUNC_NONSTD_T(name)   (*name)
#endif


#define MP_SSTRLEN(string) (sizeof(string)-1)

#ifndef strcaseEQ
#   define strcaseEQ(s1,s2) (!strcasecmp(s1,s2))
#endif
#ifndef strncaseEQ
#   define strncaseEQ(s1,s2,l) (!strncasecmp(s1,s2,l))
#endif

#ifndef SvCLASS
#define SvCLASS(o) HvNAME(SvSTASH(SvRV(o)))
#endif

#define SvObjIV(o) SvIV((SV*)SvRV(o))
#define MgObjIV(m) SvIV((SV*)SvRV(m->mg_obj))

#define MP_SvGROW(sv, len) \
    (void)SvUPGRADE(sv, SVt_PV); \
    SvGROW(sv, len+1)

#define MP_SvCUR_set(sv, len) \
    SvCUR_set(sv, len); \
    *SvEND(sv) = '\0'; \
    SvPOK_only(sv)

#define MP_magical_untie(sv, mg_flags) \
    mg_flags = SvMAGICAL((SV*)sv); \
    SvMAGICAL_off((SV*)sv)

#define MP_magical_tie(sv, mg_flags) \
    SvFLAGS((SV*)sv) |= mg_flags

/* some wrapper macros to detect perl versions
 * and prevent code clutter */
#define MP_PERL_VERSION_AT_LEAST(r, v, s)                                \
    (PERL_REVISION == r &&                                               \
    ((PERL_VERSION == v && PERL_SUBVERSION > s-1) || PERL_VERSION > v))

#define MP_PERL_VERSION_AT_MOST(r, v, s)                                 \
   (PERL_REVISION == r &&                                                \
   (PERL_VERSION < v || (PERL_VERSION == v && PERL_SUBVERSION < s+1)))

#define MP_PERL_VERSION(r, v, s)                                         \
  (PERL_REVISION == r && PERL_VERSION == v && PERL_SUBVERSION == s)

/* tie %hash */
MP_INLINE SV *modperl_hash_tie(pTHX_ const char *classname,
                               SV *tsv, void *p);

/* tied %hash */
MP_INLINE SV *modperl_hash_tied_object_rv(pTHX_
                                          const char *classname,
                                          SV *tsv);
/* tied %hash */
MP_INLINE void *modperl_hash_tied_object(pTHX_ const char *classname,
                                         SV *tsv);

MP_INLINE SV *modperl_perl_sv_setref_uv(pTHX_ SV *rv,
                                        const char *classname, UV uv);

MP_INLINE modperl_uri_t *modperl_uri_new(apr_pool_t *p);

SV *modperl_perl_gensym(pTHX_ char *pack);

#endif /* MODPERL_COMMON_UTIL_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
