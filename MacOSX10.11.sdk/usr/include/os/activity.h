/*
 * Copyright (c) 2013-2015 Apple Inc. All rights reserved.
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

#ifndef __OS_ACTIVITY_H__
#define __OS_ACTIVITY_H__

#include <Availability.h>
#include <os/base.h>
#include <stdint.h>

extern void *__dso_handle;

__BEGIN_DECLS

/*!
 * @typedef os_activity_t
 * An opaque value for the activity ID.
 */
typedef uint64_t os_activity_t;
typedef uint32_t os_breadcrumb_t;

#define OS_ACTIVITY_NULL 0
// No NULL for breadcrumb or activity_code

/*!
 * @typedef os_activity_flag_t
 * Flags for activity
 */
typedef uint32_t os_activity_flag_t;

/*!
 * @constant OS_ACTIVITY_FLAG_DEFAULT
 * Use the default flags for the activity.
 */
static const os_activity_flag_t OS_ACTIVITY_FLAG_DEFAULT = 0;

/*!
 * @constant: OS_ACTIVITY_FLAG_DETACHED
 * Creates an activity that is disassociated from the current activity
 */
static const os_activity_flag_t OS_ACTIVITY_FLAG_DETACHED = 0x1;

#pragma mark - activity related

/*!
 * @function os_activity_initiate
 *
 * @abstract
 * Synchronously initiates an activity using provided block.
 *
 * @discussion
 * Synchronously initiates an activity using the provided block and creates
 * a tracing buffer as appropriate.  All new activities are created as a
 * subactivity of an existing activity on the current thread.
 *
 *		os_activity_initiate("indexing database", OS_ACTIVITY_FLAG_DEFAULT, ^(void) {
 *			// either do work directly or issue work asynchronously
 *		});
 *
 * @param description
 * A constant string describing the activity, e.g., "performClick" or
 * "menuSelection".
 *
 * @param flags
 * Flags to be used when initiating the activity, typically OS_ACTIVITY_FLAG_DEFAULT.
 *
 * @param activity_block
 * The block to execute a given activity
 */
#define os_activity_initiate(description, flags, activity_block) __extension__({                            \
    _Static_assert(__builtin_constant_p(description), "activity description must be a constant string");    \
    __attribute__((section("__TEXT,__os_activity"))) static const char _d[] = description;                  \
    _os_activity_initiate(&__dso_handle, _d, flags, activity_block);                                        \
    __asm__(""); /* avoid tailcall */                                                                       \
})

/*!
 * @function os_activity_initiate_f
 *
 * @abstract
 * Synchronously initiates an activity using the provided function.
 *
 * @discussion
 * Synchronously initiates an activity using the provided function and creates
 * a tracing buffer as appropriate.  All new activities are created as a
 * subactivity of an existing activity on the current thread.
 *
 *		os_activity_initiate_f("indexing database", OS_ACTIVITY_FLAG_DEFAULT, context, function);
 *
 * @param description
 * A constant string describing the activity, e.g., "performClick" or
 * "menuSelection".
 *
 * @param flags
 * Flags to be used when initiating the activity, typically OS_ACTIVITY_FLAG_DEFAULT.
 *
 * @param context
 * An optional context that will be supplied to the activity function.
 *
 * @param activity_func
 * The function to execute for the new activity.
 */
#define os_activity_initiate_f(description, flags, context, activity_func) __extension__({                  \
    _Static_assert(__builtin_constant_p(description), "activity description must be a constant string");    \
    __attribute__((section("__TEXT,__os_activity"))) static const char _d[] = description;                  \
    _os_activity_initiate_f(&__dso_handle, _d, flags, context, activity_func);                              \
    __asm__(""); /* avoid tailcall */                                                                       \
})

/*!
 * @function os_activity_start
 *
 * @abstract
 * Starts a new activity immediately within the current context.
 *
 * @discussion
 * Starts a new activity immediately within the current context.
 *
 *		os_activity_t activity = os_activity_start("indexing database", OS_ACTIVITY_FLAG_DEFAULT);
 *		< do some work >
 *		os_activity_end(activity);
 *
 * The os_activity_t can be stored in a context if needed and ended at a later
 * time.
 *
 * @param description
 * A constant string describing the activity, e.g., "performClick" or
 * "menuSelection".
 *
 * @param flags
 * Flags to be used when initiating the activity, typically OS_ACTIVITY_FLAG_DEFAULT.
 *
 * @result
 * Returns a valid os_activity_t or 0 on failure.
 */
#define os_activity_start(description, flags) __extension__({                                               \
    _Static_assert(__builtin_constant_p(description), "activity description must be a constant string");    \
    __attribute__((section("__TEXT,__os_activity"))) static const char _d[] = description;                  \
    os_activity_t _aid = _os_activity_start(&__dso_handle, _d, flags);                                      \
    __asm__(""); /* avoid possibility of tail call through optimization */                                  \
    _aid;                                                                                                   \
})

/*!
 * @function os_activity_end
 *
 * @abstract
 * Ends the specified activity on the current thread.
 *
 * @discussion
 * Ends the specified activity on the current thread.  Does not signify anything
 * other than the originator has received control back from the activity.  Work
 * could still be in flight related to the activity.
 *
 * @param activity_id
 * An os_activity_t returned from os_activity_start.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0)
OS_EXPORT OS_NOTHROW
void
os_activity_end(os_activity_t activity_id);

/*!
 * @function os_activity_get_active
 *
 * @abstract
 * Returns the stack of nested activities associated with the current thread.
 *
 * @discussion
 * Activities have a sense of nesting and therefore there could be more than
 * one activity involved on the current thread.  This should be used by
 * diagnostic tools only for making additional decisions about a situation.
 * 
 * @param entries
 * Pass a buffer of sufficient size to hold the the number of entries being
 * requested.
 *
 * @param count
 * Pointer to the requested number of activity identifiers.
 * On output will be filled with the number of activities that are available.
 *
 * @result
 * Number of activity identifiers written to 'entries'
 */
__OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0)
OS_EXPORT OS_NOTHROW
unsigned int
os_activity_get_active(os_activity_t *entries, unsigned int *count);

#pragma mark - application breadcrumbs

/*!
 * @function os_activity_set_breadcrumb
 *
 * @abstract
 * This flags the current activity as a "breadcrumb", i.e., an interesting event.
 *
 * @discussion
 * Not all activities are interesting events at the macro-level.  Some activities
 * can be flagged as a breadcrumb for evalutating cross activity interactions.
 * This can only be called once per activity, other requests will be ignored.
 *
 * @param name
 * A constant string that describes the breadcrumb.
 */
#define os_activity_set_breadcrumb(name) __extension__({                                            \
    _Static_assert(__builtin_constant_p(name), "breadcrumb name must be a constant string");        \
    __attribute__((section("__TEXT,__os_breadcrumb"))) static const char _m[] = name;               \
    _os_activity_set_breadcrumb(&__dso_handle, _m);                                                 \
    __asm__("");                                                                                    \
})

#pragma mark - internal routines

/*!
 * @function _os_activity_set_breadcrumb
 *
 * @abstract
 * Internal function for setting breadcrumb.  Do not use directly.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0)
OS_EXPORT OS_NOTHROW
void
_os_activity_set_breadcrumb(void *dso, const char *name);

/*!
 * @function _os_activity_start
 *
 * @abstract
 * Internal function for activity start, do not use directly will not preserve
 * description.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0)
OS_EXPORT OS_NOTHROW OS_WARN_RESULT
os_activity_t
_os_activity_start(void *dso, const char *description, os_activity_flag_t flags);

/*!
 * @function _os_activity_initiate
 *
 * @abstract
 * Do not use directly because your description will not be preserved.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0)
OS_EXPORT OS_NOTHROW
void
_os_activity_initiate(void *dso, const char *description, os_activity_flag_t flags, void (^activity_block)(void));

/*!
 * @function _os_activity_initiate_f
 *
 * @abstract
 * Do not use directly because your description will not be preserved.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0)
OS_EXPORT OS_NOTHROW
void
_os_activity_initiate_f(void *dso, const char *description, os_activity_flag_t flags, void *context, void (*activity_func)(void *context));

__END_DECLS

#endif // __OS_ACTIVITY_H__
