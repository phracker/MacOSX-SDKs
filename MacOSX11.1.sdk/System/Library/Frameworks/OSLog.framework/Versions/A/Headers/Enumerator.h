/*
 * Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef __OSLOG_ENUMERATOR_H__
#define __OSLOG_ENUMERATOR_H__

#ifndef __INDIRECT_OSLOG_HEADER_USER__
#error "Please use <OSLog/OSLog.h> instead of directly using this file."
#endif

@class OSLogPosition;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum OSLogEnumeratorOptions
 *
 * @abstract
 * Control the direction of the iteration.
 *
 * @constant OSLogEnumeratorReverse
 * Iterate backward in time. If no starting position is specified,
 * start at the latest entry.
 */
typedef NS_OPTIONS(NSUInteger, OSLogEnumeratorOptions) {
    OSLogEnumeratorReverse                                  = 0x01,
}
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
NS_SWIFT_NAME(OSLogEnumerator.Options);

/*!
 * @class OSLogEnumerator
 *
 * @abstract
 * An enumerator that views entries in the unified logging system.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
OS_EXPORT
@interface OSLogEnumerator : NSEnumerator

@end

NS_ASSUME_NONNULL_END

#endif /* __OSLOG_ENUMERATOR_H__ */
