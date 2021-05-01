/*
 * Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef __OSLOG_POSITION_H__
#define __OSLOG_POSITION_H__

#ifndef __INDIRECT_OSLOG_HEADER_USER__
#error "Please use <OSLog/OSLog.h> instead of directly using this file."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class OSLogPosition
 *
 * @abstract
 * An opaque abstraction representing a point in a sequence of
 * entries in the unified logging system.
 *
 * @discussion
 * Generate positions with OSLogStore instance methods and use them
 * to start viewing entries from a particular starting point.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
OS_EXPORT
@interface OSLogPosition : NSObject
- (instancetype)init NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END

#endif /* __OSLOG_POSITION_H__ */
