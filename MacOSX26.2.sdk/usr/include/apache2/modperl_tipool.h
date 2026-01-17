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

#ifndef MODPERL_TIPOOL_H
#define MODPERL_TIPOOL_H

#ifdef USE_ITHREADS

modperl_list_t *modperl_list_new(void);

modperl_list_t *modperl_list_last(modperl_list_t *list);

modperl_list_t *modperl_list_first(modperl_list_t *list);

modperl_list_t *modperl_list_append(modperl_list_t *list,
                                    modperl_list_t *new_list);

modperl_list_t *modperl_list_prepend(modperl_list_t *list,
                                     modperl_list_t *new_list);

modperl_list_t *modperl_list_remove(modperl_list_t *list,
                                    modperl_list_t *rlist);

modperl_tipool_t *modperl_tipool_new(apr_pool_t *p,
                                     modperl_tipool_config_t *cfg,
                                     modperl_tipool_vtbl_t *func,
                                     void *data);

void modperl_tipool_init(modperl_tipool_t *tipool);

void modperl_tipool_destroy(modperl_tipool_t *tipool);

void modperl_tipool_add(modperl_tipool_t *tipool, void *data);

void modperl_tipool_remove(modperl_tipool_t *tipool, modperl_list_t *listp);

modperl_list_t *modperl_list_remove_data(modperl_list_t *list,
                                         void *data,
                                         modperl_list_t **listp);

modperl_list_t *modperl_tipool_pop(modperl_tipool_t *tipool);

void modperl_tipool_putback(modperl_tipool_t *tipool,
                            modperl_list_t *listp,
                            int num_requests);

void modperl_tipool_putback_data(modperl_tipool_t *tipool, void *data,
                                 int num_requests);

#define modperl_tipool_wait(tipool) \
    while (tipool->size == tipool->in_use) { \
        MP_TRACE_i(MP_FUNC, \
                   "waiting for available tipool item in thread 0x%lx", \
                   MP_TIDF); \
        MP_TRACE_i(MP_FUNC, "(%d items in use, %d alive)", \
                   tipool->in_use, tipool->size); \
        COND_WAIT(&tipool->available, &tipool->tiplock); \
    }

#define modperl_tipool_broadcast(tipool) \
    MP_TRACE_i(MP_FUNC, "broadcast available tipool item"); \
    COND_SIGNAL(&tipool->available)

#define modperl_tipool_lock(tipool) \
    MP_TRACE_i(MP_FUNC, "about to lock tipool in thread 0x%lx", MP_TIDF); \
    MUTEX_LOCK(&tipool->tiplock); \
    MP_TRACE_i(MP_FUNC, "acquired tipool lock")

#define modperl_tipool_unlock(tipool) \
    MP_TRACE_i(MP_FUNC, "about to unlock tipool in thread 0x%lx", MP_TIDF); \
    MUTEX_UNLOCK(&tipool->tiplock); \
    MP_TRACE_i(MP_FUNC, "released tipool lock")

#endif /* USE_ITHREADS */

#endif /* MODPERL_TIPOOL_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
