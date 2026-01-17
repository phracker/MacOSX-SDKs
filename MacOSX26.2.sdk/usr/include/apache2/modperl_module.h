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

#ifndef MODPERL_MODULE_H
#define MODPERL_MODULE_H

PTR_TBL_t *modperl_module_config_table_get(pTHX_ int create);

void modperl_module_config_table_set(pTHX_ PTR_TBL_t *table);

const char *modperl_module_add(apr_pool_t *p, server_rec *s,
                               const char *name, SV *mod_cmds);

SV *modperl_module_config_get_obj(pTHX_ SV *pmodule, server_rec *s,
                                  ap_conf_vector_t *v);

#endif /* MODPERL_MODULE_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
