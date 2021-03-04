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

#ifndef MODPERL_APR_COMPAT_H
#define MODPERL_APR_COMPAT_H

/* back compat adjustements for older libapr versions */

/* BACK_COMPAT_MARKER: make back compat issues easy to find :) */

/* use the following format:
 *     #if ! AP_MODULE_MAGIC_AT_LEAST(20020903,4)
 *         [compat code]
 *     #endif
 * and don't forget to insert comments explaining exactly
 * which httpd release allows us to remove the compat code
 */

/* apr_filetype_e entries rename */

#ifndef APR_FILETYPE_NOFILE
#define APR_FILETYPE_NOFILE  APR_NOFILE
#endif
#ifndef APR_FILETYPE_REG
#define APR_FILETYPE_REG     APR_REG
#endif
#ifndef APR_FILETYPE_DIR
#define APR_FILETYPE_DIR     APR_DIR
#endif
#ifndef APR_FILETYPE_CHR
#define APR_FILETYPE_CHR     APR_CHR
#endif
#ifndef APR_FILETYPE_BLK
#define APR_FILETYPE_BLK     APR_BLK
#endif
#ifndef APR_FILETYPE_PIPE
#define APR_FILETYPE_PIPE    APR_PIPE
#endif
#ifndef APR_FILETYPE_LNK
#define APR_FILETYPE_LNK     APR_LNK
#endif
#ifndef APR_FILETYPE_SOCK
#define APR_FILETYPE_SOCK    APR_SOCK
#endif
#ifndef APR_FILETYPE_UNKFILE
#define APR_FILETYPE_UNKFILE APR_UNKFILE
#endif


/* apr file permissions group rename (has no enum) */

#if defined(APR_USETID) && !defined(APR_FPROT_USETID)
#define APR_FPROT_USETID     APR_USETID
#endif
#ifndef APR_FPROT_UREAD
#define APR_FPROT_UREAD      APR_UREAD
#endif
#ifndef APR_FPROT_UWRITE
#define APR_FPROT_UWRITE     APR_UWRITE
#endif
#ifndef APR_FPROT_UEXECUTE
#define APR_FPROT_UEXECUTE   APR_UEXECUTE
#endif
#if defined(APR_GSETID) && !defined(APR_FPROT_GSETID)
#define APR_FPROT_GSETID     APR_GSETID
#endif
#ifndef APR_FPROT_GREAD
#define APR_FPROT_GREAD      APR_GREAD
#endif
#ifndef APR_FPROT_GWRITE
#define APR_FPROT_GWRITE     APR_GWRITE
#endif
#ifndef APR_FPROT_GEXECUTE
#define APR_FPROT_GEXECUTE   APR_GEXECUTE
#endif
#if defined(APR_WSTICKY) && !defined(APR_FPROT_WSTICKY)
#define APR_FPROT_WSTICKY    APR_WSTICKY
#endif
#ifndef APR_FPROT_WREAD
#define APR_FPROT_WREAD      APR_WREAD
#endif
#ifndef APR_FPROT_WWRITE
#define APR_FPROT_WWRITE     APR_WWRITE
#endif
#ifndef APR_FPROT_WEXECUTE
#define APR_FPROT_WEXECUTE   APR_WEXECUTE
#endif
#ifndef APR_FPROT_OS_DEFAULT
#define APR_FPROT_OS_DEFAULT APR_OS_DEFAULT
#endif
/* APR_FPROT_FILE_SOURCE_PERMS seems to have only an internal apr
 * use */

/* apr_file_open flag group rename (has no enum) */

#ifndef APR_FOPEN_READ
#define APR_FOPEN_READ        APR_READ
#endif
#ifndef APR_FOPEN_WRITE
#define APR_FOPEN_WRITE       APR_WRITE
#endif
#ifndef APR_FOPEN_CREATE
#define APR_FOPEN_CREATE      APR_CREATE
#endif
#ifndef APR_FOPEN_APPEND
#define APR_FOPEN_APPEND      APR_APPEND
#endif
#ifndef APR_FOPEN_TRUNCATE
#define APR_FOPEN_TRUNCATE    APR_TRUNCATE
#endif
#ifndef APR_FOPEN_BINARY
#define APR_FOPEN_BINARY      APR_BINARY
#endif
#ifndef APR_FOPEN_EXCL
#define APR_FOPEN_EXCL        APR_EXCL
#endif
#ifndef APR_FOPEN_BUFFERED
#define APR_FOPEN_BUFFERED    APR_BUFFERED
#endif
#ifndef APR_FOPEN_DELONCLOSE
#define APR_FOPEN_DELONCLOSE  APR_DELONCLOSE
#endif
#ifndef APR_FOPEN_XTHREAD
#define APR_FOPEN_XTHREAD     APR_XTHREAD
#endif
#ifndef APR_FOPEN_SHARELOCK
#define APR_FOPEN_SHARELOCK   APR_SHARELOCK
#endif
#ifndef APR_FOPEN_NOCLEANUP
#define APR_FOPEN_NOCLEANUP   APR_FILE_NOCLEANUP
#endif
#ifndef APR_FOPEN_SENDFILE_ENABLED
#define APR_FOPEN_SENDFILE_ENABLED  APR_SENDFILE_ENABLED
#endif
#ifndef APR_FOPEN_LARGEFILE
/* added in 2.0.50 */
#ifdef APR_LARGEFILE
#define APR_FOPEN_LARGEFILE   APR_LARGEFILE
#endif
#endif

#endif /* MODPERL_APR_COMPAT_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
