#ifndef __KEXTMANAGER_H__
#define __KEXTMANAGER_H__

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

CFURLRef KextManagerCreateURLForBundleIdentifier(
    CFAllocatorRef allocator,
    CFStringRef    bundleIdentifier);

#ifdef __cplusplus
}
#endif

#endif __KEXTMANAGER_H__
