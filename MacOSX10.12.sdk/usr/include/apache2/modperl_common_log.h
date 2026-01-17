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

#ifndef MODPERL_COMMON_LOG_H
#define MODPERL_COMMON_LOG_H

#define MP_STRINGIFY(n) MP_STRINGIFY_HELPER(n)
#define MP_STRINGIFY_HELPER(n) #n

#   if defined(__GNUC__)
#      if (__GNUC__ > 2)
#         define MP_FUNC __func__
#      else
#         define MP_FUNC __FUNCTION__
#      endif
#   else
#      define MP_FUNC __FILE__ ":" MP_STRINGIFY(__LINE__)
#   endif

#include "modperl_apr_includes.h"
#include "apr_lib.h"
#include "modperl_trace.h"

#ifdef _PTHREAD_H
#define modperl_thread_self() pthread_self()
#else
#define modperl_thread_self() 0
#endif

#define MP_TIDF \
(unsigned long)modperl_thread_self()

void modperl_trace_logfile_set(apr_file_t *logfile_new);

unsigned long modperl_debug_level(void);

#ifdef WIN32
#define MP_debug_level modperl_debug_level()
#else
extern unsigned long MP_debug_level;
#endif

void modperl_trace(const char *func, const char *fmt, ...);

void modperl_trace_level_set(apr_file_t *logfile, const char *level);

#endif /* MODPERL_COMMON_LOG_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
