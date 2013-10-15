/*	CFMachPort.h
	Copyright (c) 1998-2005, Apple, Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFMACHPORT__)
#define __COREFOUNDATION_CFMACHPORT__ 1

#if defined(__MACH__)

#include <CoreFoundation/CFRunLoop.h>
#include <mach/port.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct __CFMachPort * CFMachPortRef;

typedef struct {
    CFIndex	version;
    void *	info;
    const void *(*retain)(const void *info);
    void	(*release)(const void *info);
    CFStringRef	(*copyDescription)(const void *info);
} CFMachPortContext;

typedef void (*CFMachPortCallBack)(CFMachPortRef port, void *msg, CFIndex size, void *info);
typedef void (*CFMachPortInvalidationCallBack)(CFMachPortRef port, void *info);

CF_EXPORT CFTypeID	CFMachPortGetTypeID(void);

CF_EXPORT CFMachPortRef	CFMachPortCreate(CFAllocatorRef allocator, CFMachPortCallBack callout, CFMachPortContext *context, Boolean *shouldFreeInfo);
CF_EXPORT CFMachPortRef	CFMachPortCreateWithPort(CFAllocatorRef allocator, mach_port_t portNum, CFMachPortCallBack callout, CFMachPortContext *context, Boolean *shouldFreeInfo);

CF_EXPORT mach_port_t	CFMachPortGetPort(CFMachPortRef port);
CF_EXPORT void		CFMachPortGetContext(CFMachPortRef port, CFMachPortContext *context);
CF_EXPORT void		CFMachPortInvalidate(CFMachPortRef port);
CF_EXPORT Boolean	CFMachPortIsValid(CFMachPortRef port);
CF_EXPORT CFMachPortInvalidationCallBack CFMachPortGetInvalidationCallBack(CFMachPortRef port);
CF_EXPORT void		CFMachPortSetInvalidationCallBack(CFMachPortRef port, CFMachPortInvalidationCallBack callout);

CF_EXPORT CFRunLoopSourceRef	CFMachPortCreateRunLoopSource(CFAllocatorRef allocator, CFMachPortRef port, CFIndex order);

#if defined(__cplusplus)
}
#endif

#endif /* __MACH__ */

#endif /* ! __COREFOUNDATION_CFMACHPORT__ */

