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

#ifndef MODPERL_PERL_PP_H
#define MODPERL_PERL_PP_H

#define MP_PERL_BRANCH(r, v)                                             \
    (PERL_REVISION == r && PERL_VERSION == v)

#if defined(USE_ITHREADS) && MP_PERL_BRANCH(5, 6)
#   define MP_REFGEN_FIXUP
#endif

typedef enum {
#ifdef MP_REFGEN_FIXUP
    MP_OP_SREFGEN,
#endif
    MP_OP_REQUIRE,
    MP_OP_max
} modperl_perl_opcode_e;

void modperl_perl_pp_set(modperl_perl_opcode_e idx);

void modperl_perl_pp_set_all(void);

void modperl_perl_pp_unset(modperl_perl_opcode_e idx);

void modperl_perl_pp_unset_all(void);

#endif /* MODPERL_PERL_PP_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
