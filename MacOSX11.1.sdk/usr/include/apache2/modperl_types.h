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

#ifndef MODPERL_TYPES_H
#define MODPERL_TYPES_H

#ifndef MP_IOBUFSIZE
#   ifdef AP_IOBUFSIZE
#      define MP_IOBUFSIZE AP_IOBUFSIZE
#   else
#      define MP_IOBUFSIZE 8192
#   endif
#endif

/* aliases */

typedef request_rec subrequest_rec;
typedef apr_array_header_t MpAV;
typedef apr_table_t        MpHV;
typedef char char_len; /* see xs/typemap */

/* mod_perl structures */

typedef struct {
    request_rec *r;
    conn_rec    *c;
    server_rec  *s;
} modperl_rcs_t;

typedef struct modperl_config_con_t modperl_config_con_t;

#ifdef USE_ITHREADS

typedef struct modperl_list_t modperl_list_t;

struct modperl_list_t {
    modperl_list_t *prev, *next;
    void *data;
};

typedef struct modperl_interp_t modperl_interp_t;
typedef struct modperl_interp_pool_t modperl_interp_pool_t;
typedef struct modperl_tipool_t modperl_tipool_t;
typedef struct modperl_tipool_config_t modperl_tipool_config_t;

struct modperl_interp_t {
    modperl_interp_pool_t *mip;
    PerlInterpreter *perl;
    int num_requests;
    U8 flags;
    modperl_config_con_t *ccfg;
    int refcnt;
#ifdef MP_TRACE
    unsigned long tid;
#endif
};

typedef struct {
    /* s == startup grow
     * r == runtime grow
     */
    void * (*tipool_sgrow)(modperl_tipool_t *tipool, void *data);
    void * (*tipool_rgrow)(modperl_tipool_t *tipool, void *data);
    void (*tipool_shrink)(modperl_tipool_t *tipool, void *data,
                          void *item);
    void (*tipool_destroy)(modperl_tipool_t *tipool, void *data,
                           void *item);
    void (*tipool_dump)(modperl_tipool_t *tipool, void *data,
                        modperl_list_t *listp);
} modperl_tipool_vtbl_t;

struct modperl_tipool_config_t {
    int start; /* number of items to create at startup */
    int min_spare; /* minimum number of spare items */
    int max_spare; /* maximum number of spare items */
    int max; /* maximum number of items */
    int max_requests; /* maximum number of requests per item */
};

struct modperl_tipool_t {
    perl_mutex tiplock;
    perl_cond available;
    modperl_list_t *idle, *busy;
    int in_use; /* number of items currrently in use */
    int size; /* current number of items */
    void *data; /* user data */
    modperl_tipool_config_t *cfg;
    modperl_tipool_vtbl_t *func;
};

struct modperl_interp_pool_t {
    server_rec *server;
    modperl_tipool_t *tipool;
    modperl_interp_t *parent; /* from which to perl_clone() */
};

#endif /* USE_ITHREADS */

typedef U32 modperl_opts_t;

typedef struct {
    modperl_opts_t opts;
    modperl_opts_t opts_add;
    modperl_opts_t opts_remove;
    modperl_opts_t opts_override;
    modperl_opts_t opts_seen;
    int unset;
} modperl_options_t;

typedef struct {
    MpHV *setvars;
    MpHV *configvars;
    MpHV *SetEnv;
    MpHV *PassEnv;
    MpAV *PerlRequire, *PerlModule, *PerlPostConfigRequire;
    MpAV *handlers_per_srv[MP_HANDLER_NUM_PER_SRV];
    MpAV *handlers_files[MP_HANDLER_NUM_FILES];
    MpAV *handlers_process[MP_HANDLER_NUM_PROCESS];
    MpAV *handlers_pre_connection[MP_HANDLER_NUM_PRE_CONNECTION];
    MpAV *handlers_connection[MP_HANDLER_NUM_CONNECTION];
#ifdef USE_ITHREADS
    modperl_interp_pool_t *mip;
    modperl_tipool_config_t *interp_pool_cfg;
#else
    PerlInterpreter *perl;
#endif
#ifdef MP_USE_GTOP
    modperl_gtop_t *gtop;
#endif
    MpAV *argv;
    modperl_options_t *flags;
    apr_hash_t *modules;
    server_rec *server;
} modperl_config_srv_t;

typedef struct {
    char *location;
    char *PerlDispatchHandler;
    MpAV *handlers_per_dir[MP_HANDLER_NUM_PER_DIR];
    MpHV *SetEnv;
    MpHV *setvars;
    MpHV *configvars;
    modperl_options_t *flags;
} modperl_config_dir_t;

typedef struct {
    const char *file;
    modperl_config_dir_t *dcfg;
} modperl_require_file_t;

typedef struct modperl_mgv_t modperl_mgv_t;

struct modperl_mgv_t {
    char *name;
    int len;
    UV hash;
    modperl_mgv_t *next;
};

typedef struct modperl_handler_t modperl_handler_t;

struct modperl_handler_t {
    /* could be:
     * - the lightweight gv for named subs
     * - the lookup data in $PL_modperl{ANONSUB}
     */
    modperl_mgv_t *mgv_obj;
    modperl_mgv_t *mgv_cv;
    /* could be:
     * - a subroutine name for named subs
     * - NULL for anon subs
     */
    const char *name;
    CV *cv;
    U8 flags;
    U16 attrs;
    modperl_handler_t *next;
};

#define MP_HANDLER_TYPE_CHAR 1
#define MP_HANDLER_TYPE_SV   2

typedef struct {
    int outcnt;
    char outbuf[MP_IOBUFSIZE];
    apr_pool_t *pool;
    ap_filter_t **filters;
    int header_parse;
    request_rec *r;
} modperl_wbucket_t;

typedef enum {
    MP_INPUT_FILTER_MODE,
    MP_OUTPUT_FILTER_MODE
} modperl_filter_mode_e;

typedef struct {
    int seen_eos;
    int eos;
    int flush;
    ap_filter_t *f;
    char *leftover;
    apr_ssize_t remaining;
    modperl_wbucket_t *wbucket;
    apr_bucket *bucket;
    apr_bucket_brigade *bb_in;
    apr_bucket_brigade *bb_out;
    ap_input_mode_t input_mode;
    apr_read_type_e block;
    apr_off_t readbytes;
    apr_status_t rc;
    modperl_filter_mode_e mode;
    apr_pool_t *pool;
    apr_pool_t *temp_pool;
} modperl_filter_t;

typedef struct {
    int sent_eos;
    SV *data;
    modperl_handler_t *handler;
#ifdef USE_ITHREADS
    modperl_interp_t *interp;
#endif
} modperl_filter_ctx_t;

typedef struct {
    HV *pnotes;
    apr_pool_t *pool;
#ifdef USE_ITHREADS
    modperl_interp_t *interp;
#endif
} modperl_pnotes_t;

typedef struct {
    modperl_pnotes_t pnotes;
    SV *global_request_obj;
    U8 flags;
    int status;
    modperl_wbucket_t *wbucket;
    MpAV *handlers_per_dir[MP_HANDLER_NUM_PER_DIR];
    MpAV *handlers_per_srv[MP_HANDLER_NUM_PER_SRV];
    modperl_perl_globals_t perl_globals;
} modperl_config_req_t;

struct modperl_config_con_t {
    modperl_pnotes_t pnotes;
#ifdef USE_ITHREADS
    modperl_interp_t *interp;
#endif
};

typedef struct {
    apr_pool_t *pool;
    void *data;
} modperl_cleanup_data_t;

typedef struct {
    module *modp;
    const char *cmd_data;
    const char *func_name;
} modperl_module_cmd_data_t;

typedef enum {
    MP_HOOK_RUN_ALL,
    MP_HOOK_RUN_FIRST,
    MP_HOOK_VOID
} modperl_hook_run_mode_e;

#endif /* MODPERL_TYPES_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
