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

#ifndef MODPERL_GTOP_H
#define MODPERL_GTOP_H

#ifndef MP_TRACE
#    undef MP_USE_GTOP
#endif

#ifdef MP_USE_GTOP
/* prevent undef symbol errors (glibtop_error_vr) */
#define __GLIBTOP_ERROR_H__
#include <glibtop.h>
#include <glibtop/open.h>
#include <glibtop/close.h>
#ifndef GTOP_2_5_PLUS
#include <glibtop/xmalloc.h>
#endif
#include <glibtop/parameter.h>
#include <glibtop/union.h>
#include <glibtop/sysdeps.h>

#define MP_GTOP_SSS 16

typedef struct {
    char size[MP_GTOP_SSS];
    char vsize[MP_GTOP_SSS];
    char resident[MP_GTOP_SSS];
    char share[MP_GTOP_SSS];
    char rss[MP_GTOP_SSS];
} modperl_gtop_proc_mem_ss;

typedef struct {
    glibtop_union before;
    glibtop_union after;
    pid_t pid;
    modperl_gtop_proc_mem_ss proc_mem_ss;
} modperl_gtop_t;

modperl_gtop_t *modperl_gtop_new(apr_pool_t *p);
void modperl_gtop_get_proc_mem_before(modperl_gtop_t *gtop);
void modperl_gtop_get_proc_mem_after(modperl_gtop_t *gtop);
void modperl_gtop_report_proc_mem(modperl_gtop_t *gtop,
                                  char *when, const char *func, char *msg);
void modperl_gtop_report_proc_mem_diff(modperl_gtop_t *gtop, const char* func, char *msg);
void modperl_gtop_report_proc_mem_before(modperl_gtop_t *gtop, const char* func, char *msg);
void modperl_gtop_report_proc_mem_after(modperl_gtop_t *gtop, const char* func, char *msg);

#define modperl_gtop_do_proc_mem_before(func, msg) \
        modperl_gtop_get_proc_mem_before(scfg->gtop); \
        modperl_gtop_report_proc_mem_before(scfg->gtop, func, msg)

#define modperl_gtop_do_proc_mem_after(func, msg) \
        modperl_gtop_get_proc_mem_after(scfg->gtop); \
        modperl_gtop_report_proc_mem_after(scfg->gtop, func, msg); \
        modperl_gtop_report_proc_mem_diff(scfg->gtop, func, msg)

#endif /* MP_USE_GTOP */

#endif /* MODPERL_GTOP_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
