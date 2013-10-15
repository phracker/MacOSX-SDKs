/*	NSDebug.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

/**************************************************************************
WARNING: Unsupported API.

This module contains material that is only partially supported -- if
at all.  Do not depend on the existance of any of these symbols in your
code in future releases of this software.  Certainly, do not depend on
the symbols in this header in production code.  The format of any data
produced by the functions in this header may also change at any time.

However, it should be noted that the features (but not necessarily the
exact implementation) in this file have been found to be generally useful,
and in some cases invaluable, and are not likely to go away anytime soon.
**************************************************************************/

#import <Foundation/NSObject.h>
#import <Foundation/NSAutoreleasePool.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSPort.h>

/* The environment component of this API

The boolean- and integer-valued variables declared in this header,
plus some values set by methods, read starting values from the
process's environment at process startup.  This is mostly a benefit
if you need to initialize these variables to some non-default value
before your program's main() routine gets control, but it also
allows you to change the value without modifying your program's
source. (Variables can be set and methods called around specific
areas within a program, too, of course.)

The initialization from the environment happens very early, but may
not have happened yet at the time of a +load method statically linked
into an application (as opposed to one in a dynamically loaded module). 
But as noted in the "Foundation Release Notes", +load methods that are
statically linked into an application are tricky to use and are not
recommended.

Here is a table of the variables/values initialized from the environment
at startup.  Some of these just set variables, others call methods to
set the values.

NAME OF ENV. VARIABLE		       DEFAULT	SET TO...
NSDebugEnabled				  NO	"YES"
NSZombieEnabled				  NO	"YES"
NSDeallocateZombies			  NO	"YES"
NSHangOnUncaughtException		  NO	"YES"

NSEnableAutoreleasePool			 YES	"NO"
NSAutoreleaseFreedObjectCheckEnabled	  NO	"YES"
NSAutoreleaseHighWaterMark		  0	non-negative integer
NSAutoreleaseHighWaterResolution	  0	non-negative integer

*/

/****************	General		****************/

FOUNDATION_EXPORT BOOL NSDebugEnabled;
	// General-purpose global boolean. Applications and frameworks
	// may choose to do some extra checking, or use different
	// algorithms, or log informational messages, or whatever, if
	// this variable is true (ex: if (NSDebugEnabled) { ... }).

FOUNDATION_EXPORT BOOL NSZombieEnabled;
	// Enable object zombies. When an object is deallocated, its isa
	// pointer is modified to be that of a "zombie" class (whether or
	// not the storage is then freed can be controlled by the
	// NSDeallocateZombies variable). Messages sent to the zombie
	// object cause logged messages and can be broken on in a debugger.
	// The default is NO.

FOUNDATION_EXPORT BOOL NSDeallocateZombies;
	// Determines whether the storage of objects that have been
	// "zombified" is then freed or not. The default value (NO)
	// is most suitable for debugging messages sent to zombie
	// objects. And since the memory is never freed, storage
	// allocated to an object will never be reused, either (which
	// is sometimes useful otherwise).

FOUNDATION_EXPORT BOOL NSHangOnUncaughtException;
	// If set to YES, causes the process to hang after logging the
	// "*** Uncaught exception:" message. A backtrace can be gotten
	// from the process with the 'sample' utility, or the process can
	// be attached to with a debugger. The default is NO.

FOUNDATION_EXPORT BOOL NSIsFreedObject(id anObject);
	// Returns YES if the value passed as the parameter is a pointer
	// to a freed object. Note that memory allocation packages will
	// eventually reuse freed memory blocks to satisfy a request.
	// NSZombieEnabled and NSDeallocateZombies can be used to prevent
	// reuse of allocated objects.

/****************	Stack processing	****************/

FOUNDATION_EXPORT void *NSFrameAddress(unsigned frame);
FOUNDATION_EXPORT void *NSReturnAddress(unsigned frame);
	// Returns the value of the frame pointer or return address,
	// respectively, of the specified frame. Frames are numbered
	// sequentially, with the "current" frame being zero, the
	// previous frame being 1, etc. The current frame is the
	// frame in which either of these functions is called. For
	// example, NSReturnAddress(0) returns an address near where
	// this function was called, NSReturnAddress(1) returns the
	// address to which control will return when current frame
	// exits, etc. If the requested frame does not exist, then
	// NULL is returned. The behavior of these functions is
	// undefined in the presence of code which has been compiled
	// without frame pointers.

FOUNDATION_EXPORT unsigned NSCountFrames(void);
	// Returns the number of call frames on the stack. The behavior
	// of this functions is undefined in the presence of code which
	// has been compiled without frame pointers.

/****************	Autorelease pool debugging	****************/

// Functions used as interesting breakpoints in a debugger
FOUNDATION_EXPORT void _NSAutoreleaseNoPool(void *object);
	// Called to log the "Object X of class Y autoreleased with no
	// pool in place - just leaking" message.

FOUNDATION_EXPORT void _NSAutoreleaseFreedObject(void *freedObject);
	// Called when a previously freed object would be released
	// by an autorelease pool. See +enableFreedObjectCheck: below.

FOUNDATION_EXPORT void _NSAutoreleaseHighWaterLog(unsigned int count);
	// Called whenever a high water mark is reached by a pool.
	// See +setPoolCountHighWaterMark: below.

@interface NSAutoreleasePool (NSAutoreleasePoolDebugging)

+ (void)enableRelease:(BOOL)enable;
	// Enables or disables autorelease pools; that is, whether or
	// not the autorelease pools send the -release message to their
	// objects when each pool is released. This message affects only
	// the pools of the autorelease pool stack of the current thread
	// (and any future pools in that thread). The "default default"
	// value can be set in the initial environment when a program
	// is launched with the NSEnableAutoreleasePool environment
	// variable (see notes at the top of this file) -- as thread
	// pool-stacks are created, they take their initial enabled
	// state from that environment variable.

+ (void)showPools;
	// Displays to stderr the state of the current thread's
	// autorelease pool stack.

+ (void)resetTotalAutoreleasedObjects;
+ (unsigned)totalAutoreleasedObjects;
	// Returns the number of objects autoreleased (in ALL threads,
	// currently) since the counter was last reset to zero with
	// +resetTotalAutoreleasedObjects.

+ (void)enableFreedObjectCheck:(BOOL)enable;
	// Enables or disables freed-object checking for the pool stack
	// of the current thread (and any future pools in that thread).
	// When enabled, an autorelease pool will call the function
	// _NSAutoreleaseFreedObject() when it is about to attempt to
	// release an object that the runtime has marked as freed (and
	// then it doesn't attempt to send -release to the freed storage).
	// The pointer to the freed storage is passed to that function.
	// The "default default" value can be set in the initial
	// environment when a program is launched with the
	// NSAutoreleaseFreedObjectCheckEnabled environment variable
	// (see notes at the top of this file) -- as thread pool-stacks
	// are created, they take their initial freed-object-check state
	// from that environment variable.

+ (unsigned int)autoreleasedObjectCount;
	// Returns the total number of autoreleased objects in all pools
	// in the current thread's pool stack.

+ (unsigned int)topAutoreleasePoolCount;
	// Returns the number of autoreleased objects in top pool of
	// the current thread's pool stack.

+ (unsigned int)poolCountHighWaterMark;
+ (void)setPoolCountHighWaterMark:(unsigned int)count;
	// Sets the pool count high water mark for the pool stack of
	// the current thread (and any future pools in that thread). When
	// 'count' objects have accumulated in the top autorelease pool,
	// the pool will call _NSAutoreleaseHighWaterLog(), which
	// generates a message to stderr. The number of objects in the
	// top pool is passed as the parameter to that function. The
	// default high water mark is 0, which disables pool count
	// monitoring. The "default default" value can be set in the
	// initial environment when a program is launched with the
	// NSAutoreleaseHighWaterMark environment variable (see notes at
	// the top of this file) -- as thread pool-stacks are created,
	// they take their initial high water mark value from that
	// environment variable. See also +setPoolCountHighWaterResolution:.

+ (unsigned int)poolCountHighWaterResolution;
+ (void)setPoolCountHighWaterResolution:(unsigned int)res;
	// Sets the pool count high water resolution for the pool stack of
	// the current thread (and any future pools in that thread). A
	// call to _NSAutoreleaseHighWaterLog() is generated every multiple
	// of 'res' objects above the high water mark. If 'res' is zero
	// (the default), only one call to _NSAutoreleaseHighWaterLog() is
	// made, when the high water mark is reached. The "default default"
	// value can be set in the initial environment when a program is
	// launched with the NSAutoreleaseHighWaterResolution environment
	// variable (see notes at the top of this file) -- as thread
	// pool-stacks are created, they take their initial high water
	// resolution value from that environment variable. See also
	// +setPoolCountHighWaterMark:.

@end

/****************	Allocation statistics	****************/

// The statistics-keeping facilities generate output on various types of
// events. Currently, output logs can be generated for use of the zone
// allocation functions (NSZoneMalloc(), etc.), and allocation and
// deallocation of objects (and other types of lifetime-related events).

// This boolean is obsolete and unused
FOUNDATION_EXPORT BOOL NSKeepAllocationStatistics;

// Object allocation event types
#define NSObjectAutoreleasedEvent		3
#define NSObjectExtraRefIncrementedEvent	4
#define NSObjectExtraRefDecrementedEvent	5
#define NSObjectInternalRefIncrementedEvent	6
#define NSObjectInternalRefDecrementedEvent	7


FOUNDATION_EXPORT void NSRecordAllocationEvent(int eventType, ...);
	// Notes an object or zone allocation event and various other
	// statistics, such as the time and current thread. The additional
	// arguments to be passed to this function vary by the type of
	// event. The behavior is undefined (and likely catastrophic) if
	// the correct arguments for 'eventType' are not provided.
	//
	// The parameter prototypes for each event type are shown below.
	//   NSRecordAllocationEvent(NSObjectAutoreleasedEvent, curObj)
	//   NSRecordAllocationEvent(NSObjectExtraRefIncrementedEvent, curObj)
	//   NSRecordAllocationEvent(NSObjectExtraRefDecrementedEvent, curObj)
	//   NSRecordAllocationEvent(NSObjectInternalRefIncrementedEvent, curObj)
	//   NSRecordAllocationEvent(NSObjectInternalRefDecrementedEvent, curObj)
	//
	// Only the Foundation should have reason to use many of these.
	// Do not call NSRecordAllocationEvent(NSZoneMallocEvent, ...)
	// after NSZoneMalloc(), for example, in your own code because
	// NSZoneMalloc() has already done this for you. The only common
	// use of this function should be with these two events:
	//	NSObjectInternalRefIncrementedEvent
	//	NSObjectInternalRefDecrementedEvent
	// when a class overrides -retain and -release to do its own
	// reference counting.
	//

