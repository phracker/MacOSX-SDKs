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

#ifndef MODPERL_CMD_H
#define MODPERL_CMD_H

char *modperl_cmd_push_handlers(MpAV **handlers, const char *name,
                                apr_pool_t *p);

char *modperl_cmd_push_filter_handlers(MpAV **handlers,
                                       const char *name,
                                       apr_pool_t *p);

#define MP_CMD_SRV_DECLARE(item)                                        \
    const char *modperl_cmd_##item(cmd_parms *parms, void *mconfig,     \
                                   const char *arg)

#define MP_CMD_SRV_DECLARE2(item)                                       \
    const char *modperl_cmd_##item(cmd_parms *parms, void *mconfig,     \
                                   const char *arg1, const char *arg2)

#define MP_CMD_SRV_DECLARE_FLAG(item)                           \
    const char *modperl_cmd_##item(cmd_parms *parms,            \
                                   void *mconfig, int flag_on)

MP_CMD_SRV_DECLARE(trace);
MP_CMD_SRV_DECLARE(switches);
MP_CMD_SRV_DECLARE(modules);
MP_CMD_SRV_DECLARE(requires);
MP_CMD_SRV_DECLARE(config_requires);
MP_CMD_SRV_DECLARE(post_config_requires);
#if AP_SERVER_MAJORVERSION_NUMBER>2 || \
    (AP_SERVER_MAJORVERSION_NUMBER == 2 && AP_SERVER_MINORVERSION_NUMBER>=3)
MP_CMD_SRV_DECLARE2(authz_provider);
MP_CMD_SRV_DECLARE2(authn_provider);
#endif
MP_CMD_SRV_DECLARE2(set_var);
MP_CMD_SRV_DECLARE2(add_var);
MP_CMD_SRV_DECLARE2(set_env);
MP_CMD_SRV_DECLARE(pass_env);
MP_CMD_SRV_DECLARE(options);
MP_CMD_SRV_DECLARE(init_handlers);
MP_CMD_SRV_DECLARE(perl);
MP_CMD_SRV_DECLARE(perldo);
MP_CMD_SRV_DECLARE(pod);
MP_CMD_SRV_DECLARE(pod_cut);
MP_CMD_SRV_DECLARE(END);
MP_CMD_SRV_DECLARE(load_module);
MP_CMD_SRV_DECLARE(set_input_filter);
MP_CMD_SRV_DECLARE(set_output_filter);

#ifdef MP_COMPAT_1X

MP_CMD_SRV_DECLARE_FLAG(taint_check);
MP_CMD_SRV_DECLARE_FLAG(warn);
MP_CMD_SRV_DECLARE_FLAG(send_header);
MP_CMD_SRV_DECLARE_FLAG(setup_env);

#endif /* MP_COMPAT_1X */

#ifdef USE_ITHREADS
MP_CMD_SRV_DECLARE(interp_start);
MP_CMD_SRV_DECLARE(interp_max);
MP_CMD_SRV_DECLARE(interp_max_spare);
MP_CMD_SRV_DECLARE(interp_min_spare);
MP_CMD_SRV_DECLARE(interp_max_requests);

#endif /* USE_ITHREADS */

#define MP_CMD_SRV_RAW_ARGS(name, item, desc) \
    AP_INIT_RAW_ARGS( name, modperl_cmd_##item, NULL, \
      RSRC_CONF, desc )

#define MP_CMD_SRV_RAW_ARGS_ON_READ(name, item, desc) \
    AP_INIT_RAW_ARGS( name, modperl_cmd_##item, NULL, \
      RSRC_CONF|EXEC_ON_READ, desc )

#define MP_CMD_SRV_FLAG(name, item, desc) \
    AP_INIT_FLAG( name, modperl_cmd_##item, NULL, \
      RSRC_CONF, desc )

#define MP_CMD_SRV_TAKE1(name, item, desc) \
    AP_INIT_TAKE1( name, modperl_cmd_##item, NULL, \
      RSRC_CONF, desc )

#define MP_CMD_SRV_TAKE2(name, item, desc) \
    AP_INIT_TAKE2( name, modperl_cmd_##item, NULL, \
      RSRC_CONF, desc )

#define MP_CMD_SRV_ITERATE(name, item, desc) \
   AP_INIT_ITERATE( name, modperl_cmd_##item, NULL, \
      RSRC_CONF, desc )

#define MP_CMD_SRV_ITERATE_ON_READ(name, item, desc) \
   AP_INIT_ITERATE( name, modperl_cmd_##item, NULL, \
      RSRC_CONF|EXEC_ON_READ, desc )

#define MP_CMD_SRV_ITERATE2(name, item, desc) \
   AP_INIT_ITERATE2( name, modperl_cmd_##item, NULL, \
      RSRC_CONF, desc )

#define MP_CMD_DIR_TAKE1(name, item, desc) \
    AP_INIT_TAKE1( name, modperl_cmd_##item, NULL, \
      OR_ALL, desc )

#define MP_CMD_DIR_TAKE2(name, item, desc) \
    AP_INIT_TAKE2( name, modperl_cmd_##item, NULL, \
      OR_ALL, desc )

#define MP_CMD_DIR_ITERATE(name, item, desc) \
    AP_INIT_ITERATE( name, modperl_cmd_##item, NULL, \
      OR_ALL, desc )

#define MP_CMD_DIR_ITERATE2(name, item, desc) \
    AP_INIT_ITERATE2( name, modperl_cmd_##item, NULL, \
      OR_ALL, desc )

#define MP_CMD_DIR_FLAG(name, item, desc) \
    AP_INIT_FLAG( name, modperl_cmd_##item, NULL, \
      OR_ALL, desc )

#define MP_CMD_DIR_RAW_ARGS(name, item, desc) \
    AP_INIT_RAW_ARGS( name, modperl_cmd_##item, NULL, \
      OR_ALL, desc )

#define MP_CMD_DIR_RAW_ARGS_ON_READ(name, item, desc) \
    AP_INIT_RAW_ARGS( name, modperl_cmd_##item, NULL, \
      OR_ALL|EXEC_ON_READ, desc )

#endif /* MODPERL_CMD_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
