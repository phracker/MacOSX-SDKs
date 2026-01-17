/* Copyright 2001-2005 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MODPERL_CONST_H
#define MODPERL_CONST_H

#include "modperl_constants.h"

int modperl_const_compile(pTHX_ const char *classname,
                          const char *arg,
                          const char *name);

XS(XS_modperl_const_compile);

#define MP_newModPerlConstXS(name) \
   newXS(name "::Const::compile", \
         CvXSUB(get_cv("ModPerl::Const::compile", TRUE)), \
         __FILE__)

#endif /* MODPERL_CONST_H */
