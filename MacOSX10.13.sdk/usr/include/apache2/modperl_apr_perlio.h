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

#ifndef MODPERL_APR_PERLIO_H
#define MODPERL_APR_PERLIO_H

#ifdef PERLIO_LAYERS
#include "perliol.h"
#else
#include "iperlsys.h"
#endif

#include "apr_portable.h"
#include "apr_file_io.h"
#include "apr_errno.h"

#ifndef MP_SOURCE_SCAN
#include "apr_optional.h"
#endif

/* 5.6.0 */
#ifndef IoTYPE_RDONLY
#define IoTYPE_RDONLY '<'
#endif
#ifndef IoTYPE_WRONLY
#define IoTYPE_WRONLY '>'
#endif

typedef enum {
    MODPERL_APR_PERLIO_HOOK_READ,
    MODPERL_APR_PERLIO_HOOK_WRITE
} modperl_apr_perlio_hook_e;

#ifndef MP_SOURCE_SCAN
void modperl_apr_perlio_init(pTHX);
#endif

/* The following functions can be used from other .so libs, they just
 * need to load APR::PerlIO perl module first
 */
#ifndef MP_SOURCE_SCAN

#ifdef PERLIO_LAYERS
PerlIO *modperl_apr_perlio_apr_file_to_PerlIO(pTHX_ apr_file_t *file,
                                              apr_pool_t *pool,
                                              modperl_apr_perlio_hook_e type);
APR_DECLARE_OPTIONAL_FN(PerlIO *,
                        modperl_apr_perlio_apr_file_to_PerlIO,
                        (pTHX_ apr_file_t *file, apr_pool_t *pool,
                         modperl_apr_perlio_hook_e type));
#endif /* PERLIO_LAYERS */


SV *modperl_apr_perlio_apr_file_to_glob(pTHX_ apr_file_t *file,
                                        apr_pool_t *pool,
                                        modperl_apr_perlio_hook_e type);
APR_DECLARE_OPTIONAL_FN(SV *,
                        modperl_apr_perlio_apr_file_to_glob,
                        (pTHX_ apr_file_t *file, apr_pool_t *pool,
                         modperl_apr_perlio_hook_e type));
#endif /* MP_SOURCE_SCAN */

#endif /* MODPERL_APR_PERLIO_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
