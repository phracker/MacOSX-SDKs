/*
 *  NSPointerFunctions.h
 *
 *  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
 *
 */
 

#import <Foundation/NSObject.h>

/*

  NSPointerFunctions

  This object defines callout functions appropriate for managing a pointer reference held somewhere else.

  Used by NSHashTable, NSMapTable, and NSPointerArray, this object defines the acquision and retention behavior for the pointers provided to these collection objects.

   The functions are separated into two clusters - those that define "personality", such as object or cString, and those that describe memory management issues such as a memory deallocation function.  Common personalities and memory manager selections are provided as enumerations, and further customization is provided by methods such that the composition of the actual list of functions is done opaquely such that they can be extended in the future.

  The pointer collections copy NSPointerFunctions objects on input and output, and so NSPointerFunctions is not usefully subclassed.

*/



enum {
    // Memory options are mutually exclusive
    
    // default is strong
    NSPointerFunctionsStrongMemory = (0UL << 0),       // use strong write-barrier to backing store; use GC memory on copyIn
    NSPointerFunctionsZeroingWeakMemory = (1UL << 0),  // use weak read and write barriers; use GC memory on copyIn 
    NSPointerFunctionsOpaqueMemory = (2UL << 0),
    NSPointerFunctionsMallocMemory = (3UL << 0),       // free() will be called on removal, calloc on copyIn
    NSPointerFunctionsMachVirtualMemory = (4UL << 0),
    
    // Personalities are mutually exclusive
    // default is object.  As a special case, 'strong' memory used for Objects will do retain/release under non-GC
    NSPointerFunctionsObjectPersonality = (0UL << 8),         // use -hash and -isEqual, object description
    NSPointerFunctionsOpaquePersonality = (1UL << 8),         // use shifted pointer hash and direct equality
    NSPointerFunctionsObjectPointerPersonality = (2UL << 8),  // use shifted pointer hash and direct equality, object description
    NSPointerFunctionsCStringPersonality = (3UL << 8),        // use a string hash and strcmp, description assumes UTF-8 contents; recommended for UTF-8 (or ASCII, which is a subset) only cstrings
    NSPointerFunctionsStructPersonality = (4UL << 8),         // use a memory hash and memcmp (using size function you must set)
    NSPointerFunctionsIntegerPersonality = (5UL << 8),        // use unshifted value as hash & equality

    NSPointerFunctionsCopyIn = (1UL << 16),      // the memory acquire function will be asked to allocate and copy items on input
};

typedef NSUInteger NSPointerFunctionsOptions;

NS_CLASS_AVAILABLE(10_5, 2_0)
@interface NSPointerFunctions : NSObject <NSCopying>
// construction
- (id)initWithOptions:(NSPointerFunctionsOptions)options;
+ (id)pointerFunctionsWithOptions:(NSPointerFunctionsOptions)options;

// pointer personality functions
@property NSUInteger (*hashFunction)(const void *item, NSUInteger (*size)(const void *item));
@property BOOL (*isEqualFunction)(const void *item1, const void*item2, NSUInteger (*size)(const void *item));
@property NSUInteger (*sizeFunction)(const void *item);
@property NSString *(*descriptionFunction)(const void *item);

// custom memory configuration
@property void (*relinquishFunction)(const void *item, NSUInteger (*size)(const void *item));
@property void *(*acquireFunction)(const void *src, NSUInteger (*size)(const void *item), BOOL shouldCopy);

// GC requires that read and write barrier functions be used when pointers are from GC memory
@property BOOL usesStrongWriteBarrier;             // pointers should (not) be assigned using the GC strong write barrier
@property BOOL usesWeakReadAndWriteBarriers;       // pointers should (not) use GC weak read and write barriers

@end

