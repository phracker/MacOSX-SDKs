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

#ifndef MODPERL_LOG_H
#define MODPERL_LOG_H

#include "modperl_common_log.h"
#include "modperl_apache_includes.h"

#define modperl_trace_level_set_apache(s, level) \
    modperl_trace_level_set(s->error_log, level);

#define modperl_log_warn(s, msg) \
    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, "%s", msg)

#define modperl_log_error(s, msg) \
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "%s", msg)

#define modperl_log_notice(s, msg) \
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, "%s", msg)

#define modperl_log_debug(s, msg) \
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "%s", msg)

#define modperl_log_reason(r, msg, file)                            \
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,               \
                 "access to %s failed for %s, reason: %s",          \
                 file,                                              \
                 ap_get_remote_host(r->connection,                  \
                                    r->per_dir_config, REMOTE_NAME, \
                                    NULL),                          \
                 msg)

#endif /* MODPERL_LOG_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
