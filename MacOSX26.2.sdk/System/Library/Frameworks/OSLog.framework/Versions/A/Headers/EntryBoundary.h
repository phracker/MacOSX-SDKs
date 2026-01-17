/*
 * Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef __OSLOG_ENTRY_BOUNDARY_H__
#define __OSLOG_ENTRY_BOUNDARY_H__

#ifndef __INDIRECT_OSLOG_HEADER_USER__
#error "Please use <OSLog/OSLog.h> instead of directly using this file."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class OSLogEntryBoundary
 *
 * @abstract
 * This entry represents metadata that partitions sequences of
 * other entries.
 *
 * @discussion
 * For example, this kind of entry is used for boot boundaries.
 * The data here are currently informational and carried in the
 * composedMessage property.
 */
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
OS_EXPORT
@interface OSLogEntryBoundary : OSLogEntry
@end

NS_ASSUME_NONNULL_END

#endif /* __OSLOG_ENTRY_BOUNDARY_H__ */
