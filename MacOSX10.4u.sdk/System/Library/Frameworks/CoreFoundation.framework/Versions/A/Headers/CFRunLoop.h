/*	CFRunLoop.h
	Copyright (c) 1998-2005, Apple, Inc. All rights reserved.
*/

/*!
	@header CFRunLoop
	CFRunLoops monitor sources of input to a task and dispatch control
	when sources become ready for processing. Examples of input sources
	might include user input devices, network connections, periodic
	or time-delayed events, and asynchronous callbacks. Input sources
	are registered with a run loop, and when a run loop is "run",
	callback functions associated with each source are called when
	the sources have some activity.

	There is one run loop per thread. Each run loop has different
	sets of input sources, called modes, which are named with strings.
	A run loop is run -- in a named mode -- to have it monitor the
	sources that have been registered in that mode, and the run loop
	blocks there until something happens. Examples of modes include
	the default mode, which a process would normally spend most of
	its time in, and a modal panel mode, which might be run when
	a modal panel is up, to restrict the set of input sources that
	are allowed to "fire". This is not to the granularity of, for
	example, what type of user input events are interesting, however.
	That sort of finer-grained granularity is given by UI-level
	frameworks with "get next event matching mask" or similar
	functionality.

	The CFRunLoopSource type is an abstraction of input sources that
	can be put in a run loop. An input source type would normally
	define an API for creating and operating on instances of the type,
	as if it were a separate entity from the run loop, then provide a
	function to create a CFRunLoopSource for an instance. The
	CFRunLoopSource can then be registered with the run loop,
	represents the input source to the run loop, and acts as
	intermediary between the run loop and the actual input source
	type instance. Examples include CFMachPort and CFSocket.

	A CFRunLoopTimer is a specialization of run loop sources, a way
	to generate either a one-shot delayed action, or a recurrent
	action.

	While being run, a run loop goes through a cycle of activities.
	Input sources are checked, timers which need firing are fired,
	and then the run loop blocks, waiting for something to happen 
	(or in the case of timers, waiting for it to be time for
	something to happen). When something does happen, the run loop
	wakes up, processes the activity (usually by calling a callback
	function for an input source), checks other sources, fires timers,
	and goes back to sleep. And so on. CFRunLoopObservers can be
	used to do processing at special points in this cycle.




*/

#if !defined(__COREFOUNDATION_CFRUNLOOP__)
#define __COREFOUNDATION_CFRUNLOOP__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFString.h>
#if defined(__MACH__)
    #include <mach/port.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*!
	@typedef CFRunLoopRef
	This is the type of a reference to a run loop.
*/
typedef struct __CFRunLoop * CFRunLoopRef;

/*!
	@typedef CFRunLoopSourceRef
	This is the type of a reference to general run loop input sources.
*/
typedef struct __CFRunLoopSource * CFRunLoopSourceRef;

/*!
	@typedef CFRunLoopObserverRef
	This is the type of a reference to a run loop observer.
*/
typedef struct __CFRunLoopObserver * CFRunLoopObserverRef;

/*!
	@typedef CFRunLoopTimerRef
	This is the type of a reference to a run loop timer.
*/
typedef struct __CFRunLoopTimer * CFRunLoopTimerRef;

/* Reasons for CFRunLoopRunInMode() to Return */
enum {
    kCFRunLoopRunFinished = 1,
    kCFRunLoopRunStopped = 2,
    kCFRunLoopRunTimedOut = 3,
    kCFRunLoopRunHandledSource = 4
};

/* Run Loop Observer Activities */
typedef enum {
    kCFRunLoopEntry = (1 << 0),
    kCFRunLoopBeforeTimers = (1 << 1),
    kCFRunLoopBeforeSources = (1 << 2),
    kCFRunLoopBeforeWaiting = (1 << 5),
    kCFRunLoopAfterWaiting = (1 << 6),
    kCFRunLoopExit = (1 << 7),
    kCFRunLoopAllActivities = 0x0FFFFFFFU
} CFRunLoopActivity;

CF_EXPORT const CFStringRef kCFRunLoopDefaultMode;
CF_EXPORT const CFStringRef kCFRunLoopCommonModes;

/*!
	@function CFRunLoopGetTypeID
	Returns the type identifier of all CFRunLoop instances.
*/
CF_EXPORT CFTypeID CFRunLoopGetTypeID(void);

/*!
	@function CFRunLoopGetCurrent
	Returns the run loop for the current thread. There is exactly
	one run loop per thread.
*/
CF_EXPORT CFRunLoopRef CFRunLoopGetCurrent(void);

/*!
	@function CFRunLoopCopyCurrentMode
	Returns the name of the mode in which the run loop is running.
	NULL is returned if the run loop is not running.
	@param rl The run loop for which the current mode should be
		reported.
*/
CF_EXPORT CFStringRef CFRunLoopCopyCurrentMode(CFRunLoopRef rl);

/*!
	@function CFRunLoopCopyAllModes
	Returns an array of all the names of the modes known to the run
	loop.
	@param rl The run loop for which the mode list should be returned.
*/
CF_EXPORT CFArrayRef CFRunLoopCopyAllModes(CFRunLoopRef rl);

/*!
	@function CFRunLoopAddCommonMode
	Makes the named mode a "common mode" for the run loop. The set of
	common modes are collectively accessed with the global constant
	kCFRunLoopCommonModes. Input sources previously added to the
	common modes are added to the new common mode.
	@param rl The run loop for which the mode should be made common.
	@param mode The name of the mode to mark as a common mode.
*/
CF_EXPORT void CFRunLoopAddCommonMode(CFRunLoopRef rl, CFStringRef mode);

/*!
	@function CFRunLoopGetNextTimerFireDate
	Returns the time at which the next timer will fire.
	@param rl The run loop for which the next timer fire date should
		be reported.
	@param mode The name of the mode to query.
*/
CF_EXPORT CFAbsoluteTime CFRunLoopGetNextTimerFireDate(CFRunLoopRef rl, CFStringRef mode);





CF_EXPORT void CFRunLoopRun(void);
CF_EXPORT SInt32 CFRunLoopRunInMode(CFStringRef mode, CFTimeInterval seconds, Boolean returnAfterSourceHandled);
CF_EXPORT Boolean CFRunLoopIsWaiting(CFRunLoopRef rl);
CF_EXPORT void CFRunLoopWakeUp(CFRunLoopRef rl);
CF_EXPORT void CFRunLoopStop(CFRunLoopRef rl);

CF_EXPORT Boolean CFRunLoopContainsSource(CFRunLoopRef rl, CFRunLoopSourceRef source, CFStringRef mode);
CF_EXPORT void CFRunLoopAddSource(CFRunLoopRef rl, CFRunLoopSourceRef source, CFStringRef mode);
CF_EXPORT void CFRunLoopRemoveSource(CFRunLoopRef rl, CFRunLoopSourceRef source, CFStringRef mode);

CF_EXPORT Boolean CFRunLoopContainsObserver(CFRunLoopRef rl, CFRunLoopObserverRef observer, CFStringRef mode);
CF_EXPORT void CFRunLoopAddObserver(CFRunLoopRef rl, CFRunLoopObserverRef observer, CFStringRef mode);
CF_EXPORT void CFRunLoopRemoveObserver(CFRunLoopRef rl, CFRunLoopObserverRef observer, CFStringRef mode);

CF_EXPORT Boolean CFRunLoopContainsTimer(CFRunLoopRef rl, CFRunLoopTimerRef timer, CFStringRef mode);
CF_EXPORT void CFRunLoopAddTimer(CFRunLoopRef rl, CFRunLoopTimerRef timer, CFStringRef mode);
CF_EXPORT void CFRunLoopRemoveTimer(CFRunLoopRef rl, CFRunLoopTimerRef timer, CFStringRef mode);

/*!
	@typedef CFRunLoopSourceContext
	Structure containing the callbacks of a CFRunLoopSource.
	@field version The version number of the structure type being
		passed in as a parameter to the CFArray creation
		functions. Valid version numbers are currently 0 and 1.
		Version 0 sources are fairly generic, but may require a
		bit more implementation, or may require a separate
		thread as part of the implementation, for a complex
		source. Version 1 sources are available on Mach and Windows,
		and have performance advantages when the source type can
		be described with this style.
	@field info An arbitrary pointer to client-defined data, which
		can be associated with the source at creation time, and
		is passed to the callbacks.
	@field retain The callback used to add a retain for the source on
		the info pointer for the life of the source, and may be
		used for temporary references the source needs to take.
		This callback returns the actual info pointer to store in
		the source, almost always just the pointer passed as the
		parameter.
	@field release The callback used to remove a retain previously
		added for the source on the info pointer. 
	@field copyDescription The callback used to create a descriptive
		string representation of the info pointer (or the data
		pointed to by the info pointer) for debugging purposes.
		This is used by the CFCopyDescription() function.
	@field equal The callback used to compare the info pointers of
		two sources, to determine equality of sources.
	@field hash The callback used to compute a hash code for the info
		pointer for the source. The source uses this hash code
		information to produce its own hash code.
	@field schedule For a version 0 source, this callback is called
		whenever the source is added to a run loop mode. This
		information is often needed to implement complex sources.
	@field cancel For a version 0 source, this callback is called
		whenever the source is removed from a run loop mode. This
		information is often needed to implement complex sources.
	@field getPort Defined in version 1 sources, this function returns
		the Mach port or Windows HANDLE of a kernel object to
		represent the source to the run loop.  This function
		must return the same result every time it is called, for the
                lifetime of the source, and should be quick.
	@field perform This callback is the workhorse of a run loop source.
		It is called when the source needs to be "handled" or
		processing is needed for input or conditions relating to
		the source. For version 0 sources, this function is called
		when the source has been marked "signaled" with the
		CFRunLoopSourceSignal() function, and should do whatever
		handling is required for the source. For a version 1 source
		on Mach, this function is called when a Mach message arrives
		on the source's Mach port, with the message, its
		length, an allocator, and the source's info pointer. A
		version 1 source performs whatever processing is required
		on the Mach message, then can return a pointer to a Mach
		message (or NULL if none) to be sent (usually this is a
		"reply" message), which should be allocated with the
		allocator (and will be deallocated by the run loop after
		sending).  For a version 1 source on Windows the function
		is called when the kernel object is in the signaled state.
*/
typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
    Boolean	(*equal)(const void *info1, const void *info2);
    CFHashCode	(*hash)(const void *info);
    void	(*schedule)(void *info, CFRunLoopRef rl, CFStringRef mode);
    void	(*cancel)(void *info, CFRunLoopRef rl, CFStringRef mode);
    void	(*perform)(void *info);
} CFRunLoopSourceContext;

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
    Boolean	(*equal)(const void *info1, const void *info2);
    CFHashCode	(*hash)(const void *info);
#if defined(__MACH__)
    mach_port_t	(*getPort)(void *info);
    void *	(*perform)(void *msg, CFIndex size, CFAllocatorRef allocator, void *info);
#else
    HANDLE	(*getPort)(void *info);
    void	(*perform)(void *info);
#endif
} CFRunLoopSourceContext1;

/*!
	@function CFRunLoopSourceGetTypeID
	Returns the type identifier of all CFRunLoopSource instances.
*/
CF_EXPORT CFTypeID CFRunLoopSourceGetTypeID(void);

/*!
	@function CFRunLoopSourceCreate
	Creates a new run loop source with the given context.
	@param allocator The CFAllocator which should be used to allocate
		memory for the array and its storage for values. If this
		reference is not a valid CFAllocator, the behavior is
		undefined.
	@param order On platforms which support it, for source versions
		which support it, this parameter determines the order in
		which the sources which are ready to be processed are
		handled. A lower order number causes processing before
		higher order number sources. It is inadvisable to depend
		on the order number for any architectural or design aspect
		of code. In the absence of any reason to do otherwise,
		zero should be used.
	@param context A pointer to the context structure for the source.
*/
CF_EXPORT CFRunLoopSourceRef CFRunLoopSourceCreate(CFAllocatorRef allocator, CFIndex order, CFRunLoopSourceContext *context);

/*!
	@function CFRunLoopSourceGetOrder
	Returns the ordering parameter of the run loop source.
	@param source The run loop source for which the order number
		should be returned.
*/
CF_EXPORT CFIndex CFRunLoopSourceGetOrder(CFRunLoopSourceRef source);

/*!
	@function CFRunLoopSourceInvalidate
	Invalidates the run loop source. The run loop source is never
	performed again after it becomes invalid, and will automatically
	be removed from any run loops and modes which contain it. The
	source is not destroyed by this operation, however -- the memory
	is still valid; only the release of all references on the source
	through the reference counting system can do that. But note, that
	if the only retains on the source were held by run loops, those
	retains may all be released by the time this function returns,
	and the source may actually be destroyed through that process.
	@param source The run loop source which should be invalidated.
*/
CF_EXPORT void CFRunLoopSourceInvalidate(CFRunLoopSourceRef source);

/*!
	@function CFRunLoopSourceIsValid
	Reports whether or not the source is valid.
	@param source The run loop source for which the validity should
		be returned.
*/
CF_EXPORT Boolean CFRunLoopSourceIsValid(CFRunLoopSourceRef source);

/*!
	@function CFRunLoopSourceGetContext
	Fills the memory pointed to by the context parameter with the
	context structure of the source.
	@param source The run loop source for which the context structure
		should be returned.
	@param context A pointer to a context structure to be filled.
*/
CF_EXPORT void CFRunLoopSourceGetContext(CFRunLoopSourceRef source, CFRunLoopSourceContext *context);

/*!
	@function CFRunLoopSourceSignal
	Marks the source as signalled, ready for handling by the run loop.
	Has no effect on version 1 sources, which are automatically
	handled when Mach messages for them come in.
	@param source The run loop source which should be signalled.
*/
CF_EXPORT void CFRunLoopSourceSignal(CFRunLoopSourceRef source);

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
} CFRunLoopObserverContext;

typedef void (*CFRunLoopObserverCallBack)(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void *info);

/*!
	@function CFRunLoopObserverGetTypeID
	Returns the type identifier of all CFRunLoopObserver instances.
*/
CF_EXPORT CFTypeID CFRunLoopObserverGetTypeID(void);

CF_EXPORT CFRunLoopObserverRef CFRunLoopObserverCreate(CFAllocatorRef allocator, CFOptionFlags activities, Boolean repeats, CFIndex order, CFRunLoopObserverCallBack callout, CFRunLoopObserverContext *context);

CF_EXPORT CFOptionFlags CFRunLoopObserverGetActivities(CFRunLoopObserverRef observer);
CF_EXPORT Boolean CFRunLoopObserverDoesRepeat(CFRunLoopObserverRef observer);
CF_EXPORT CFIndex CFRunLoopObserverGetOrder(CFRunLoopObserverRef observer);
CF_EXPORT void CFRunLoopObserverInvalidate(CFRunLoopObserverRef observer);
CF_EXPORT Boolean CFRunLoopObserverIsValid(CFRunLoopObserverRef observer);
CF_EXPORT void CFRunLoopObserverGetContext(CFRunLoopObserverRef observer, CFRunLoopObserverContext *context);

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
} CFRunLoopTimerContext;

typedef void (*CFRunLoopTimerCallBack)(CFRunLoopTimerRef timer, void *info);

/*!
	@function CFRunLoopTimerGetTypeID
	Returns the type identifier of all CFRunLoopTimer instances.
*/
CF_EXPORT CFTypeID CFRunLoopTimerGetTypeID(void);

CF_EXPORT CFRunLoopTimerRef CFRunLoopTimerCreate(CFAllocatorRef allocator, CFAbsoluteTime fireDate, CFTimeInterval interval, CFOptionFlags flags, CFIndex order, CFRunLoopTimerCallBack callout, CFRunLoopTimerContext *context);
CF_EXPORT CFAbsoluteTime CFRunLoopTimerGetNextFireDate(CFRunLoopTimerRef timer);
CF_EXPORT void CFRunLoopTimerSetNextFireDate(CFRunLoopTimerRef timer, CFAbsoluteTime fireDate);
CF_EXPORT CFTimeInterval CFRunLoopTimerGetInterval(CFRunLoopTimerRef timer);
CF_EXPORT Boolean CFRunLoopTimerDoesRepeat(CFRunLoopTimerRef timer);
CF_EXPORT CFIndex CFRunLoopTimerGetOrder(CFRunLoopTimerRef timer);
CF_EXPORT void CFRunLoopTimerInvalidate(CFRunLoopTimerRef timer);
CF_EXPORT Boolean CFRunLoopTimerIsValid(CFRunLoopTimerRef timer);
CF_EXPORT void CFRunLoopTimerGetContext(CFRunLoopTimerRef timer, CFRunLoopTimerContext *context);

#if defined(__cplusplus)
}
#endif

#endif /* ! __COREFOUNDATION_CFRUNLOOP__ */

