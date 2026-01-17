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

#ifndef MODPERL_TIME_H
#define MODPERL_TIME_H

#ifdef HZ
#   define MP_HZ HZ
#else
#   define MP_HZ 100
#endif

#ifdef MP_TRACE
#define dMP_TIMES \
    struct tms start_time; \
    struct tms end_time
#else
#define dMP_TIMES dNOOP
#endif

#define MP_START_TIMES() \
    MP_TRACE_t_do((void)PerlProc_times(&start_time))

#define MP_END_TIMES() \
    MP_TRACE_t_do((void)PerlProc_times(&end_time))

#define MP_PRINT_TIMES(label) \
    MP_TRACE_t_do({ \
        double utime = \
             (double)(end_time.tms_utime - start_time.tms_utime)/MP_HZ; \
        double stime = \
             (double)(end_time.tms_stime - start_time.tms_stime)/MP_HZ; \
        if (utime || stime) { \
            MP_TRACE_t(MP_FUNC, "%s %5.2f user %5.2f sys", \
                       label, utime, stime); \
        } \
    })

#endif /* MODPERL_TIME_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
