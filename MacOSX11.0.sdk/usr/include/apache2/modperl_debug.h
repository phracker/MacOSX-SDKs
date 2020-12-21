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

#ifndef MODPERL_DEBUG_H
#define MODPERL_DEBUG_H

#include "mod_perl.h"

#ifdef MP_DEBUG
#  define MP_ASSERT(exp) ap_assert(exp)
#else
#  define MP_ASSERT(exp) ((void)0)
#endif

#ifdef USE_ITHREADS
#  define MP_ASSERT_CONTEXT(perl) MP_ASSERT((perl) == PERL_GET_CONTEXT)
#else
#  define MP_ASSERT_CONTEXT(perl) ((void)0)
#endif

char *modperl_server_desc(server_rec *s, apr_pool_t *p);

#ifdef MP_TRACE
void modperl_apr_table_dump(pTHX_ apr_table_t *table, char *name);
/* dump the contents of PL_modglobal */
void modperl_perl_modglobal_dump(pTHX);
#endif

#endif /* MODPERL_DEBUG_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
