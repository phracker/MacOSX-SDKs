/*	NSGarbageCollector.h
	Copyright (c) 2006-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

/*
 Cocoa's Garbage Collector is a conservative generational non-stop-the-world collector.  It uses "write-barriers" to detect cross generational stores of pointers so that "young" generation objects can be collected quickly.
 Garbage Collection is enabled by using the -fobjc-gc compiler switch upon your main program file and all others used by the program, including frameworks and bundles (bundles will fail to laod if they are not gc capable).  This switch causes the generation of the write-barrier assignment primitives.
 The collector is currently configured to run only on the main thread and then only on specific request, not on allocation demand, due to locking issues in the frameworks.  Collections may be requested from any thread, however.
 The collector determines what is garbage by recursively examining all nodes starting with globals, possible nodes referenced from the thread stacks, and all nodes marked as having "external" references.  Nodes not reached by this search are deemed garbage.  Weak references to garbage nodes are then cleared.  Garbage nodes that are objects are sent the -finalize method in an arbitrary order, and after all finalize messages have been sent the memory is recovered.
 It is a runtime error to store a object being finalized into one that is not (resurrection).
 
*/


@interface NSGarbageCollector : NSObject 

// There is only one garbage collector for Cocoa within a single process.
// Returns nil if this process is not running with garbage collection
+ (id)defaultCollector;


- (BOOL)isCollecting;  // is there a collection in progress

- (void)disable;  // temporarily disable collections
- (void)enable; // reenable disabled collections (must be called once per call to disableCollector)
- (BOOL)isEnabled;

- (void)collectIfNeeded;  // collects if thresholds crossed, but subject to interruption on user input
- (void)collectExhaustively; // collects iteratively, but subject to interruption on user input

// references outside the heap, globals, and the stack, e.g. unscanned memory, malloc memory, must be tracked by the collector
- (void)disableCollectorForPointer:(void *)ptr;     // this pointer will not be collected...
- (void)enableCollectorForPointer:(void *)ptr;      // ...until this (stacking) call is made

/*
 Legacy. 
 The garbage collector provides an "NSZone" interface for legacy code that attempts zone affinity for allocations.  (The zone used by malloc(3) continues to operate in parallel). In a garbage collected progam, "NSDefaultMallocZone()" provides the same zone as this call, but with a now misleading name. (All heap objects in fact return this same zone, referred internally as the "auto" zone).
 Allocation of garbage collected memory should be done with the NSAllocateCollectable() call, introduced in 10.4.
 For legacy purposes, however, memory can be allocated using this zone via NSZoneMalloc() and returned via NSZoneFree().  This memory will be unscanned and will not be normally collected (unless enableCollectorForPointer: is called upon it).
*/
- (NSZone *)zone;
@end

#endif
