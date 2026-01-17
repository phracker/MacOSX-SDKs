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

#ifndef MODPERL_FILTER_H
#define MODPERL_FILTER_H

#define MP_FILTER_CONNECTION_OUTPUT_NAME "MODPERL_CONNECTION_OUTPUT"
#define MP_FILTER_CONNECTION_INPUT_NAME  "MODPERL_CONNECTION_INPUT"

#define MP_FILTER_REQUEST_OUTPUT_NAME    "MODPERL_REQUEST_OUTPUT"
#define MP_FILTER_REQUEST_INPUT_NAME     "MODPERL_REQUEST_INPUT"

#define MP_FILTER_CONNECTION_HANDLER 0x01
#define MP_FILTER_REQUEST_HANDLER    0x02
#define MP_FILTER_HAS_INIT_HANDLER   0x04
#define MP_FILTER_INIT_HANDLER       0x08
#define MP_FILTER_HTTPD_HANDLER      0x10

typedef ap_filter_t * MP_FUNC_T(modperl_filter_add_t) (const char *, void *,
                                                       request_rec *,
                                                       conn_rec *);

/* simple buffer api */
MP_INLINE apr_status_t modperl_wbucket_pass(modperl_wbucket_t *b,
                                            const char *buf, apr_size_t len,
                                            int add_flush_bucket);

MP_INLINE apr_status_t modperl_wbucket_flush(modperl_wbucket_t *b,
                                             int add_flush_bucket);

MP_INLINE apr_status_t modperl_wbucket_write(pTHX_
                                             modperl_wbucket_t *b,
                                             const char *buf,
                                             apr_size_t *wlen);

/* generic filter routines */

modperl_filter_t *modperl_filter_new(ap_filter_t *f,
                                     apr_bucket_brigade *bb,
                                     modperl_filter_mode_e mode,
                                     ap_input_mode_t input_mode,
                                     apr_read_type_e block,
                                     apr_off_t readbytes);

modperl_filter_t *modperl_filter_mg_get(pTHX_ SV *obj);

int modperl_filter_resolve_init_handler(pTHX_ modperl_handler_t *handler,
                                        apr_pool_t *p);

int modperl_run_filter(modperl_filter_t *filter);

/* output filters */
apr_status_t modperl_output_filter_handler(ap_filter_t *f,
                                           apr_bucket_brigade *bb);

void modperl_output_filter_add_connection(conn_rec *c);

void modperl_output_filter_add_request(request_rec *r);

MP_INLINE apr_status_t modperl_output_filter_flush(modperl_filter_t *filter);
MP_INLINE apr_status_t modperl_input_filter_flush(modperl_filter_t *filter);


MP_INLINE apr_size_t modperl_output_filter_read(pTHX_
                                                modperl_filter_t *filter,
                                                SV *buffer,
                                                apr_size_t wanted);

MP_INLINE apr_status_t modperl_output_filter_write(pTHX_
                                                   modperl_filter_t *filter,
                                                   const char *buf,
                                                   apr_size_t *len);

void modperl_brigade_dump(apr_bucket_brigade *bb, apr_file_t *file);

/* input filters */
apr_status_t modperl_input_filter_handler(ap_filter_t *f,
                                          apr_bucket_brigade *bb,
                                          ap_input_mode_t input_mode,
                                          apr_read_type_e block,
                                          apr_off_t readbytes);

void modperl_input_filter_add_connection(conn_rec *c);

void modperl_input_filter_add_request(request_rec *r);

MP_INLINE apr_size_t modperl_input_filter_read(pTHX_
                                               modperl_filter_t *filter,
                                               SV *buffer,
                                               apr_size_t wanted);

MP_INLINE apr_status_t modperl_input_filter_write(pTHX_
                                                  modperl_filter_t *filter,
                                                  const char *buf,
                                                  apr_size_t *len);

void modperl_filter_runtime_add(pTHX_ request_rec *r, conn_rec *c,
                                const char *name,
                                modperl_filter_mode_e mode,
                                modperl_filter_add_t addfunc,
                                SV *callback, const char *type);

#endif /* MODPERL_FILTER_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
