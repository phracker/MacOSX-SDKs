/*
   +----------------------------------------------------------------------+
   | Suhosin Patch for PHP                                                |
   +----------------------------------------------------------------------+
   | Copyright (c) 2004-2010 Stefan Esser                                 |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.02 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available at through the world-wide-web at                           |
   | http://www.php.net/license/2_02.txt.                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Stefan Esser <stefan.esser@sektioneins.de>                   |
   +----------------------------------------------------------------------+
 */

#ifndef SUHOSIN_PATCH_H
#define SUHOSIN_PATCH_H

#if SUHOSIN_PATCH

#include "zend.h"

#define SUHOSIN_PATCH_VERSION "0.9.10"

#define SUHOSIN_LOGO_GUID "SUHO8567F54-D428-14d2-A769-00DA302A5F18"

#define SUHOSIN_CONFIG(idx) (suhosin_get_config(idx))

#define SUHOSIN_MM_USE_CANARY_PROTECTION        0
#define SUHOSIN_MM_DESTROY_FREE_MEMORY          1
#define SUHOSIN_MM_IGNORE_CANARY_VIOLATION      2
#define SUHOSIN_HT_IGNORE_INVALID_DESTRUCTOR    3
#define SUHOSIN_LL_IGNORE_INVALID_DESTRUCTOR    4

#define SUHOSIN_CONFIG_SET                      100

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#if defined(DARWIN)
#include <mach/vm_param.h>
#endif

#define SUHOSIN_MANGLE_PTR(ptr)   (ptr==NULL?NULL:((void *)((zend_intptr_t)(ptr)^SUHOSIN_POINTER_GUARD)))

#endif

#endif /* SUHOSIN_PATCH_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
