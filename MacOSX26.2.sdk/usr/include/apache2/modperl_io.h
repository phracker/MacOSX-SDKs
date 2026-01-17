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

#ifndef MODPERL_IO_H
#define MODPERL_IO_H

#include "modperl_io_apache.h"

/*
 * bleedperl change #11639 switch tied handle magic
 * from living in the gv to the GvIOp(gv), so we have to deal
 * with both to support 5.6.x
 */
#if MP_PERL_VERSION_AT_LEAST(5, 7, 0)
#   define TIEHANDLE_SV(handle) (SV*)GvIOp((SV*)handle)
#else
#   define TIEHANDLE_SV(handle) (SV*)handle
#endif

#define dHANDLE(name) GV *handle = gv_fetchpv(name, TRUE, SVt_PVIO)

#define IoFLUSH_off(gv) \
IoFLAGS(GvIOp((gv))) &= ~IOf_FLUSH

#define IoFLUSH_on(gv) \
IoFLAGS(GvIOp((gv))) |= IOf_FLUSH

#define IoFLUSH(gv) \
(IoFLAGS(GvIOp((gv))) & IOf_FLUSH)

MP_INLINE void modperl_io_handle_tie(pTHX_ GV *handle,
                                     char *classname, void *ptr);
MP_INLINE GV *modperl_io_tie_stdout(pTHX_ request_rec *r);

MP_INLINE GV *modperl_io_tie_stdin(pTHX_ request_rec *r);

MP_INLINE int modperl_io_handle_tied(pTHX_ GV *handle, char *classname);

MP_INLINE void modperl_io_handle_untie(pTHX_ GV *handle);

MP_INLINE GV *modperl_io_perlio_override_stdin(pTHX_ request_rec *r);

MP_INLINE GV *modperl_io_perlio_override_stdout(pTHX_ request_rec *r);

MP_INLINE void modperl_io_perlio_restore_stdin(pTHX_ GV *handle);

MP_INLINE void modperl_io_perlio_restore_stdout(pTHX_ GV *handle);

#if defined(MP_IO_TIE_SFIO)
    /* XXX */
#elif defined(MP_IO_TIE_PERLIO)
#define modperl_io_override_stdin  modperl_io_perlio_override_stdin
#define modperl_io_override_stdout modperl_io_perlio_override_stdout
#define modperl_io_restore_stdin   modperl_io_perlio_restore_stdin
#define modperl_io_restore_stdout  modperl_io_perlio_restore_stdout
#else
#define modperl_io_override_stdin  modperl_io_tie_stdin
#define modperl_io_override_stdout modperl_io_tie_stdout
#define modperl_io_restore_stdin   modperl_io_handle_untie
#define modperl_io_restore_stdout  modperl_io_handle_untie
#endif


#endif /* MODPERL_IO_H */

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
