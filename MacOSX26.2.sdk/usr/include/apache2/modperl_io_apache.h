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

#ifndef MODPERL_IO_APACHE_H
#define MODPERL_IO_APACHE_H

#ifdef PERLIO_LAYERS

#include "perliol.h"
/* XXX: should this be a Makefile.PL config option? */
#define MP_IO_TIE_PERLIO

#include "apr_portable.h"
#include "apr_file_io.h"
#include "apr_errno.h"

typedef enum {
    MODPERL_IO_APACHE_HOOK_READ,
    MODPERL_IO_APACHE_HOOK_WRITE
} modperl_io_apache_hook_e;

#define PERLIO_Apache_DEBUG

MP_INLINE void modperl_io_apache_init(pTHX);

#else /* #ifdef PERLIO_LAYERS */

#define modperl_io_apache_init(pTHX)

#endif /* #ifdef PERLIO_LAYERS */

/**
 * read 'len' bytes from the request record 'r' into 'buffer'
 *
 * this call will block until all 'len' bytes are read, eof is reached
 * or will return an error otherwise
 *
 * @param r       request record
 * @param buffer  preallocated buffer of size 'len' to store the data in
 * @param len     how many bytes to read
 * @return how many bytes were read,
 *        -1 on error (in which case ERRSV ($!) is set)
 */
MP_INLINE SSize_t modperl_request_read(pTHX_ request_rec *r,
                                       char *buffer, Size_t len);

#endif /* MODPERL_IO_APACHE_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
