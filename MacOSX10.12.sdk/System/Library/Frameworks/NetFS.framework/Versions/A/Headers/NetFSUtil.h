/*
 *  NetFSUtil.h
 *
 *  Copyright (c) 2007-2009 Apple Inc. All rights reserved.
 */

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Get a C string from a CFStringRef.
 * The string is allocated with malloc(), and must be freed when it's
 * no longer needed.
 */
extern char *NetFSCFStringtoCString(CFStringRef);

#ifdef __cplusplus
}
#endif
