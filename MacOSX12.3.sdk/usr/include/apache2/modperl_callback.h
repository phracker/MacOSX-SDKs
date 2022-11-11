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

#ifndef MODPERL_CALLBACK_H
#define MODPERL_CALLBACK_H

/* alias some hook names to match Perl*Handler names */
#define ap_hook_trans  ap_hook_translate_name
#define ap_hook_access ap_hook_access_checker
#define ap_hook_authen ap_hook_check_user_id
#define ap_hook_authz  ap_hook_auth_checker
#define ap_hook_type   ap_hook_type_checker
#define ap_hook_fixup  ap_hook_fixups
#define ap_hook_log    ap_hook_log_transaction

#define modperl_callback_current_callback_sv \
    get_sv("Apache2::__CurrentCallback", TRUE)

#define modperl_callback_current_callback_set(desc) \
    sv_setpv(modperl_callback_current_callback_sv, desc)

#define modperl_callback_current_callback_get() \
    SvPVX(modperl_callback_current_callback_sv)

int modperl_callback(pTHX_ modperl_handler_t *handler, apr_pool_t *p,
                     request_rec *r, server_rec *s, AV *args);

int modperl_callback_run_handlers(int idx, int type,
                                  request_rec *r, conn_rec *c, server_rec *s,
                                  apr_pool_t *pconf,
                                  apr_pool_t *plog,
                                  apr_pool_t *ptemp,
                                  modperl_hook_run_mode_e run_mode);

int modperl_callback_per_dir(int idx, request_rec *r,
                             modperl_hook_run_mode_e run_mode);

int modperl_callback_per_srv(int idx, request_rec *r,
                             modperl_hook_run_mode_e run_mode);

int modperl_callback_connection(int idx, conn_rec *c,
                                modperl_hook_run_mode_e run_mode);

int modperl_callback_pre_connection(int idx, conn_rec *c, void *csd,
                                    modperl_hook_run_mode_e run_mode);

void modperl_callback_process(int idx, apr_pool_t *p, server_rec *s,
                              modperl_hook_run_mode_e run_mode);

int modperl_callback_files(int idx,
                           apr_pool_t *pconf, apr_pool_t *plog,
                           apr_pool_t *ptemp, server_rec *s,
                           modperl_hook_run_mode_e run_mode);

#endif /* MODPERL_CALLBACK_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
