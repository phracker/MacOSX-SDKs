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

#ifndef MODPERL_PERL_H
#define MODPERL_PERL_H

/* starting from 5.8.1 perl caches ppids, so we need to maintain our
 * own. some distros fetch fake 5.8.0 with changes from 5.8.1, so we
 * need to do that for those fake 5.8.0 as well. real 5.8.0 doesn't
 * have THREADS_HAVE_PIDS defined.
 */
#if MP_PERL_VERSION_AT_LEAST(5, 8, 0) && THREADS_HAVE_PIDS
#define MP_MAINTAIN_PPID
#endif

typedef struct {
    I32 pid;
    Uid_t uid, euid;
    Gid_t gid, egid;
#ifdef MP_MAINTAIN_PPID
    Uid_t ppid;
#endif
} modperl_perl_ids_t;

void modperl_perl_core_global_init(pTHX);

void modperl_perl_init_ids_server(server_rec *s);

void modperl_perl_destruct(PerlInterpreter *perl);

void modperl_perl_call_endav(pTHX);

void modperl_hash_seed_init(apr_pool_t *p);

void modperl_hash_seed_set(pTHX);

#ifndef GvCV_set
#    define GvCV_set(gv, cv) (GvCV(gv)=(cv))
#endif
#ifndef GvGP_set
#    define GvGP_set(gv, gp) (GvGP(gv)=(gp))
#endif

#ifndef Newx
#    define Newx(v,n,t) New(0,v,n,t)
#endif
#ifndef Newxz
#    define Newxz(v,n,t) Newz(0,v,n,t)
#endif

#endif /* MODPERL_PERL_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
