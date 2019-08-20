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

#ifndef MODPERL_SVPTR_TABLE_H
#define MODPERL_SVPTR_TABLE_H

#ifdef USE_ITHREADS

PTR_TBL_t *modperl_svptr_table_clone(pTHX_ PerlInterpreter *proto_perl,
                                     PTR_TBL_t *source);

#endif

void modperl_svptr_table_destroy(pTHX_ PTR_TBL_t *tbl);

void modperl_svptr_table_delete(pTHX_ PTR_TBL_t *tbl, void *key);

/*
 * XXX: the following are a copy of the Perl 5.8.0 Perl_ptr_table api
 * renamed s/Perl_ptr/modperl_svptr/g;
 * two reasons:
 *   these functions do not exist without -DUSE_ITHREADS
 *   the clear/free functions do not exist in 5.6.x
 */

PTR_TBL_t *
modperl_svptr_table_new(pTHX);

void *
modperl_svptr_table_fetch(pTHX_ PTR_TBL_t *tbl, void *sv);

void
modperl_svptr_table_store(pTHX_ PTR_TBL_t *tbl, void *oldv, void *newv);

void
modperl_svptr_table_split(pTHX_ PTR_TBL_t *tbl);

void
modperl_svptr_table_clear(pTHX_ PTR_TBL_t *tbl);

void
modperl_svptr_table_free(pTHX_ PTR_TBL_t *tbl);

#endif /* MODPERL_SVPTR_TABLE_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
