/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
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

#ifndef _MALLOC_MALLOC_H_
#define _MALLOC_MALLOC_H_

#include <stddef.h>
#include <mach/mach_types.h>
#include <sys/cdefs.h>

__BEGIN_DECLS
/*********	Type definitions	************/

typedef struct _malloc_zone_t {
    /* Only zone implementors should depend on the layout of this structure;
    Regular callers should use the access functions below */
    unsigned	version;
    void	*reserved2;
    size_t 	(*size)(struct _malloc_zone_t *zone, const void *ptr); /* returns the size of a block or 0 if not in this zone; must be fast, especially for negative answers */
    void 	*(*malloc)(struct _malloc_zone_t *zone, size_t size);
    void 	*(*calloc)(struct _malloc_zone_t *zone, size_t num_items, size_t size); /* same as malloc, but block returned is set to zero */
    void 	*(*valloc)(struct _malloc_zone_t *zone, size_t size); /* same as malloc, but block returned is set to zero and is guaranteed to be page aligned */
    void 	(*free)(struct _malloc_zone_t *zone, void *ptr);
    void 	*(*realloc)(struct _malloc_zone_t *zone, void *ptr, size_t size);
    void 	(*destroy)(struct _malloc_zone_t *zone); /* zone is destroyed and all memory reclaimed */
    const char	*zone_name;

    /* Optional batch callbacks; these may be NULL */
    unsigned	(*batch_malloc)(struct _malloc_zone_t *zone, size_t size, void **results, unsigned num_requested); /* given a size, returns pointers capable of holding that size; returns the number of pointers allocated (maybe 0 or less than num_requested) */
    void	(*batch_free)(struct _malloc_zone_t *zone, void **to_be_freed, unsigned num_to_be_freed); /* frees all the pointers in to_be_freed; note that to_be_freed may be overwritten during the process */

    struct malloc_introspection_t	*introspect;
    void	*reserved5;
} malloc_zone_t;

/*********	Creation and destruction	************/

extern malloc_zone_t *malloc_default_zone(void);
    /* The initial zone */

extern malloc_zone_t *malloc_create_zone(vm_size_t start_size, unsigned flags);
    /* Create a new zone */

extern void malloc_destroy_zone(malloc_zone_t *zone);
    /* Destroys zone and everything it allocated */

/*********	Block creation and manipulation	************/

extern void *malloc_zone_malloc(malloc_zone_t *zone, size_t size);
    /* Allocates a new pointer of size size; zone must be non-NULL */

extern void *malloc_zone_calloc(malloc_zone_t *zone, size_t num_items, size_t size);
    /* Allocates a new pointer of size num_items * size; block is cleared; zone must be non-NULL */

extern void *malloc_zone_valloc(malloc_zone_t *zone, size_t size);
    /* Allocates a new pointer of size size; zone must be non-NULL; Pointer is guaranteed to be page-aligned and block is cleared */

extern void malloc_zone_free(malloc_zone_t *zone, void *ptr);
    /* Frees pointer in zone; zone must be non-NULL */

extern void *malloc_zone_realloc(malloc_zone_t *zone, void *ptr, size_t size);
    /* Enlarges block if necessary; zone must be non-NULL */

extern malloc_zone_t *malloc_zone_from_ptr(const void *ptr);
    /* Returns the zone for a pointer, or NULL if not in any zone.
    The ptr must have been returned from a malloc or realloc call. */

extern size_t malloc_size(const void *ptr);
    /* Returns size of given ptr */

/*********	Batch methods	************/

extern unsigned malloc_zone_batch_malloc(malloc_zone_t *zone, size_t size, void **results, unsigned num_requested);
    /* Allocates num blocks of the same size; Returns the number truly allocated (may be 0) */

extern void malloc_zone_batch_free(malloc_zone_t *zone, void **to_be_freed, unsigned num);
    /* frees all the pointers in to_be_freed; note that to_be_freed may be overwritten during the process; This function will always free even if the zone has no batch callback */

/*********	Functions for zone implementors	************/

extern void malloc_zone_register(malloc_zone_t *zone);
    /* Registers a freshly created zone;
    Should typically be called after a zone has been created */

extern void malloc_zone_unregister(malloc_zone_t *zone);
    /* De-registers a zone
    Should typically be called before calling the zone destruction routine */

extern void malloc_set_zone_name(malloc_zone_t *zone, const char *name);
    /* Sets the name of a zone */

extern const char *malloc_get_zone_name(malloc_zone_t *zone);
    /* Returns the name of a zone */

typedef struct {
    vm_address_t	address;
    vm_size_t		size;
} vm_range_t;

typedef struct malloc_statistics_t {
    unsigned	blocks_in_use;
    size_t	size_in_use;
    size_t	max_size_in_use;	/* high water mark of touched memory */
    size_t	size_allocated;		/* reserved in memory */
} malloc_statistics_t;

typedef kern_return_t memory_reader_t(task_t remote_task, vm_address_t remote_address, vm_size_t size, void **local_memory);
    /* given a task, "reads" the memory at the given address and size
local_memory: set to a contiguous chunk of memory; validity of local_memory is assumed to be limited (until next call) */

#define MALLOC_PTR_IN_USE_RANGE_TYPE	1	/* for allocated pointers */
#define MALLOC_PTR_REGION_RANGE_TYPE	2	/* for region containing pointers */
#define MALLOC_ADMIN_REGION_RANGE_TYPE	4	/* for region used internally */

typedef void vm_range_recorder_t(task_t, void *, unsigned type, vm_range_t *, unsigned);
    /* given a task and context, "records" the specified addresses */

typedef struct malloc_introspection_t {
    kern_return_t (*enumerator)(task_t task, void *, unsigned type_mask, vm_address_t zone_address, memory_reader_t reader, vm_range_recorder_t recorder); /* enumerates all the malloc pointers in use */
    size_t	(*good_size)(malloc_zone_t *zone, size_t size);
    boolean_t 	(*check)(malloc_zone_t *zone); /* Consistency checker */
    void 	(*print)(malloc_zone_t *zone, boolean_t verbose); /* Prints zone  */
    void	(*log)(malloc_zone_t *zone, void *address); /* Enables logging of activity */
    void	(*force_lock)(malloc_zone_t *zone); /* Forces locking zone */
    void	(*force_unlock)(malloc_zone_t *zone); /* Forces unlocking zone */
    void	(*statistics)(malloc_zone_t *zone, malloc_statistics_t *stats); /* Fills statistics */
} malloc_introspection_t;

extern void malloc_printf(const char *format, ...);
    /* Convenience for logging errors and warnings;
    No allocation is performed during execution of this function;
    Only understands usual %p %d %s formats, and %y that expresses a number of bytes (5b,10KB,1MB...)
    */

/*********	Functions for performance tools	************/

extern kern_return_t malloc_get_all_zones(task_t task, memory_reader_t reader, vm_address_t **addresses, unsigned *count);
    /* Fills addresses and count with the addresses of the zones in task;
    Note that the validity of the addresses returned correspond to the validity of the memory returned by reader */

/*********	Debug helpers	************/

extern void malloc_zone_print_ptr_info(void *ptr);
    /* print to stdout if this pointer is in the malloc heap, free status, and size */

extern boolean_t malloc_zone_check(malloc_zone_t *zone);
    /* Checks zone is well formed; if !zone, checks all zones */

extern void malloc_zone_print(malloc_zone_t *zone, boolean_t verbose);
    /* Prints summary on zone; if !zone, prints all zones */

extern void malloc_zone_statistics(malloc_zone_t *zone, malloc_statistics_t *stats);
    /* Fills statistics for zone; if !zone, sums up all zones */

extern void malloc_zone_log(malloc_zone_t *zone, void *address);
    /* Controls logging of all activity; if !zone, for all zones;
    If address==0 nothing is logged;
    If address==-1 all activity is logged;
    Else only the activity regarding address is logged */
__END_DECLS

#endif /* _MALLOC_MALLOC_H_ */
