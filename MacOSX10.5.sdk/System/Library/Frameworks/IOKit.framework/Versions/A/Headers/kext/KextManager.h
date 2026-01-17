#ifndef __KEXTMANAGER_H__
#define __KEXTMANAGER_H__

#include <CoreFoundation/CoreFoundation.h>

#include <sys/cdefs.h>

__BEGIN_DECLS

CFURLRef KextManagerCreateURLForBundleIdentifier(
    CFAllocatorRef allocator,
    CFStringRef    bundleIdentifier);

__END_DECLS

#endif __KEXTMANAGER_H__
