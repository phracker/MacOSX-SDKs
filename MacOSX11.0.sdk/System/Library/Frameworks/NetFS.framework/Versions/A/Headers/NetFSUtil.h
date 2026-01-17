/*
 *  NetFSUtil.h
 *
 *  Copyright (c) 2007-2009 Apple Inc. All rights reserved.
 */

#include <NetFS/NetFS.h>

/*
 * Get a C string from a CFStringRef.
 * The string is allocated with malloc(), and must be freed when it's
 * no longer needed.
 */

API_UNAVAILABLE_BEGIN(ios, tvos, watchos)

NETFS_EXPORT char *NetFSCFStringtoCString(CFStringRef);

API_UNAVAILABLE_END

