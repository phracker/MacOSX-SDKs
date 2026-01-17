/*
 * Copyright (c) 2009-2011 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#if !defined(__ODCSTR_H)
#define __ODCSTR_H

#include <CoreFoundation/CoreFoundation.h>

/*!
    @function   od_cstr_from_cfstring
    @abstract   get a C string from a CF String as UTF8
    @discussion get a C string from a CF String as UTF8
    @param      inCFStr the CFString to extract
    @param      ioCStr must be freed if it is non-NULL
    @result     a constant C string that should not be freed as it may be internal storage from the CFString
*/
OS_EXPORT OS_NOTHROW OS_WARN_RESULT
const char *
od_cstr_from_cfstring(CFStringRef inCFStr, char **ioCStr);

/*!
    @function    od_cstr_from_cfstring_or_cfdata
    @abstract   fetches a standard C-string from a CFDataRef or CFStringRef passed to APIs
    @discussion fetches a standard C-string from a CFDataRef or CFStringRef passed to APIs
    @param      value is a CFDataRef or CFStringRef to extract the string from
    @result     a pointer to a char string that must be freed
*/
OS_EXPORT OS_NOTHROW OS_WARN_RESULT OS_MALLOC
char *
od_cstr_from_cfstring_or_cfdata(CFTypeRef value);

#endif /* !__ODCSTR_H */
