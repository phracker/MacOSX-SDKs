/*	CFBase.h
	Copyright 1998-2001, Apple, Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFBASE__)
#define __COREFOUNDATION_CFBASE__ 1

#if !defined(DARWIN)
    #if defined(__CF_USE_FRAMEWORK_INCLUDES__) || (defined(__MACH__) && !defined(__MWERKS__)) 
	#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/ConditionalMacros.h>
    #else
	#include <ConditionalMacros.h>
    #endif
#endif /* !DARWIN */
#if defined(DARWIN)
#include <CarbonCore/ConditionalMacros.h>
#endif /* DARWIN */

/* Have to include ConditionalMacros.h here, explicitly, because there is no
 * way to define TYPE_BOOL before it is included (it always overrides) and no
 * way to undefine true and false after MacTypes.h is included, if we don't
 * stop it here by defining TYPE_BOOL.
 */
#undef TYPE_BOOL
#define TYPE_BOOL 1

#include <stdint.h>
#include <stdbool.h>

#if !defined(DARWIN)
    #if defined(__CF_USE_FRAMEWORK_INCLUDES__) || (defined(__MACH__) && !defined(__MWERKS__)) 
	#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
    #else
	#include <MacTypes.h>
    #endif
#endif /* !DARWIN */
#if defined(DARWIN)
#include <CarbonCore/MacTypes.h>
#endif /* DARWIN */

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(NULL)
    #define NULL	0
#endif

#if !defined(TRUE)
    #define TRUE	1
#endif

#if !defined(FALSE)
    #define FALSE	0
#endif

#if defined(__WIN32__)
    #undef CF_EXPORT
    #if defined(CF_BUILDING_CF)
	#define CF_EXPORT __declspec(dllexport) extern
    #else
	#define CF_EXPORT __declspec(dllimport) extern
    #endif
#elif defined(macintosh)
    #if defined(__MWERKS__)
        #define CF_EXPORT __declspec(export) extern
    #endif
#endif

#if !defined(CF_EXPORT)
    #define CF_EXPORT extern
#endif

#if !defined(CF_INLINE)
    #if defined(__GNUC__)
	#define CF_INLINE static __inline__
    #elif defined(__MWERKS__) || defined(__cplusplus)
	#define CF_INLINE static inline
    #endif
#endif

CF_EXPORT double kCFCoreFoundationVersionNumber;

#define kCFCoreFoundationVersionNumber10_0 196.4
#define kCFCoreFoundationVersionNumber10_0_3 196.5

typedef UInt32 CFTypeID;
typedef UInt32 CFOptionFlags;
typedef UInt32 CFHashCode;
typedef SInt32 CFIndex;

typedef const struct __CFString * CFStringRef;
typedef struct __CFString * CFMutableStringRef;

/* Values returned from comparison functions */
typedef enum {
    kCFCompareLessThan = -1,
    kCFCompareEqualTo = 0,
    kCFCompareGreaterThan = 1
} CFComparisonResult;

/* A standard comparison function */
typedef CFComparisonResult (*CFComparatorFunction)(const void *val1, const void *val2, void *context);

/* Constant used by some functions to indicate failed searches. */
/* This is of type CFIndex. */
enum {
    kCFNotFound = -1
};

/* Range type */
typedef struct {
    CFIndex location;
    CFIndex length;
} CFRange;

#if defined(CF_INLINE)
CF_INLINE CFRange CFRangeMake(CFIndex loc, CFIndex len) {
    CFRange range;
    range.location = loc;
    range.length = len;
    return range;
}
#else
#define CFRangeMake(LOC, LEN) __CFRangeMake(LOC, LEN)
#endif

/* Private; do not use */
CF_EXPORT
CFRange __CFRangeMake(CFIndex loc, CFIndex len);

/* Allocator API

   Most of the time when specifying an allocator to Create functions, the NULL
   argument indicates "use the default"; this is the same as using kCFAllocatorDefault
   or the return value from CFAllocatorGetDefault().  This assures that you will use
   the allocator in effect at that time.

   You should rarely use kCFAllocatorSystemDefault, the default default allocator.
*/
typedef const struct __CFAllocator * CFAllocatorRef;

/* This is a synonym for NULL, if you'd rather use a named constant. */
CF_EXPORT
const CFAllocatorRef kCFAllocatorDefault;

/* Default system allocator; you rarely need to use this. */
CF_EXPORT
const CFAllocatorRef kCFAllocatorSystemDefault;

/* This allocator uses malloc(), realloc(), and free(). This should not be
   generally used; stick to kCFAllocatorDefault whenever possible. This
   allocator is useful as the "bytesDeallocator" in CFData or
   "contentsDeallocator" in CFString where the memory was obtained as a
   result of malloc() type functions.
*/
CF_EXPORT
const CFAllocatorRef kCFAllocatorMalloc;

/* Null allocator which does nothing and allocates no memory. This allocator
   is useful as the "bytesDeallocator" in CFData or "contentsDeallocator"
   in CFString where the memory should not be freed. 
*/
CF_EXPORT
const CFAllocatorRef kCFAllocatorNull;

/* Special allocator argument to CFAllocatorCreate() which means
   "use the functions given in the context to allocate the allocator
   itself as well". 
*/
CF_EXPORT
const CFAllocatorRef kCFAllocatorUseContext;

typedef const void *	(*CFAllocatorRetainCallBack)(const void *info);
typedef void		(*CFAllocatorReleaseCallBack)(const void *info);
typedef CFStringRef	(*CFAllocatorCopyDescriptionCallBack)(const void *info);
typedef void *		(*CFAllocatorAllocateCallBack)(CFIndex allocSize, CFOptionFlags hint, void *info);
typedef void *		(*CFAllocatorReallocateCallBack)(void *ptr, CFIndex newsize, CFOptionFlags hint, void *info);
typedef void		(*CFAllocatorDeallocateCallBack)(void *ptr, void *info);
typedef CFIndex		(*CFAllocatorPreferredSizeCallBack)(CFIndex size, CFOptionFlags hint, void *info);
typedef struct {
    CFIndex				version;
    void *				info;
    CFAllocatorRetainCallBack		retain;
    CFAllocatorReleaseCallBack		release;        
    CFAllocatorCopyDescriptionCallBack	copyDescription;
    CFAllocatorAllocateCallBack		allocate;
    CFAllocatorReallocateCallBack	reallocate;
    CFAllocatorDeallocateCallBack	deallocate;
    CFAllocatorPreferredSizeCallBack	preferredSize;
} CFAllocatorContext;

CF_EXPORT
CFTypeID	CFAllocatorGetTypeID(void);

/*
	CFAllocatorSetDefault() sets the allocator that is used in the current
	thread whenever NULL is specified as an allocator argument. This means
	that most, if not all allocations will go through this allocator. It
	also means that any allocator set as the default needs to be ready to
	deal with arbitrary memory allocation requests; in addition, the size
	and number of requests will change between releases.

	An allocator set as the default will never be released, even if later
	another allocator replaces it as the default. Not only is it impractical
	for it to be released (as there might be caches created under the covers
	that refer to the allocator), in general it's also safer and more
	efficient to keep it around.

	If you wish to use a custom allocator in a context, it's best to provide
	it as the argument to the various creation functions rather than setting
	it as the default. Setting the default allocator is not encouraged.

	If you do set an allocator as the default, either do it for all time in
	your app, or do it in a nested fashion (by restoring the previous allocator
	when you exit your context). The latter might be appropriate for plug-ins
	or libraries that wish to set the default allocator.
*/
CF_EXPORT
void CFAllocatorSetDefault(CFAllocatorRef allocator);

CF_EXPORT
CFAllocatorRef CFAllocatorGetDefault(void);

CF_EXPORT
CFAllocatorRef CFAllocatorCreate(CFAllocatorRef allocator, CFAllocatorContext *context);

CF_EXPORT
void *CFAllocatorAllocate(CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint);

CF_EXPORT
void *CFAllocatorReallocate(CFAllocatorRef allocator, void *ptr, CFIndex newsize, CFOptionFlags hint);

CF_EXPORT
void CFAllocatorDeallocate(CFAllocatorRef allocator, void *ptr);

CF_EXPORT
CFIndex CFAllocatorGetPreferredSizeForSize(CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint);

CF_EXPORT
void CFAllocatorGetContext(CFAllocatorRef allocator, CFAllocatorContext *context);

/* Base "type" of all "CF objects", and polymorphic functions on them */
typedef const void * CFTypeRef;

CF_EXPORT
CFTypeID CFGetTypeID(CFTypeRef cf);

CF_EXPORT
CFStringRef CFCopyTypeIDDescription(CFTypeID type_id);

CF_EXPORT
CFTypeRef CFRetain(CFTypeRef cf);

CF_EXPORT
void CFRelease(CFTypeRef cf);

CF_EXPORT
CFIndex CFGetRetainCount(CFTypeRef cf);

CF_EXPORT
Boolean CFEqual(CFTypeRef cf1, CFTypeRef cf2);

CF_EXPORT
CFHashCode CFHash(CFTypeRef cf);

CF_EXPORT
CFStringRef CFCopyDescription(CFTypeRef cf);

CF_EXPORT
CFAllocatorRef CFGetAllocator(CFTypeRef cf);

#if defined(__cplusplus)
}
#endif

#endif /* ! __COREFOUNDATION_CFBASE__ */

