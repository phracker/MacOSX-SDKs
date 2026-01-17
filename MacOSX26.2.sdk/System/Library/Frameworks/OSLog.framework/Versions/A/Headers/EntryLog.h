/*
 * Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef __OSLOG_ENTRY_LOG_H__
#define __OSLOG_ENTRY_LOG_H__

#ifndef __INDIRECT_OSLOG_HEADER_USER__
#error "Please use <OSLog/OSLog.h> instead of directly using this file."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum OSLogEntryLogLevel
 *
 * @abstract
 * The level that this entry was generated at.
 */
typedef NS_ENUM(NSInteger, OSLogEntryLogLevel) {
    OSLogEntryLogLevelUndefined,
    OSLogEntryLogLevelDebug,
    OSLogEntryLogLevelInfo,
    OSLogEntryLogLevelNotice,
    OSLogEntryLogLevelError,
    OSLogEntryLogLevelFault,
}
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
NS_SWIFT_NAME(OSLogEntryLog.Level);

/*!
 * @class OSLogEntryLog
 *
 * @abstract
 * Entries made by the os_log API.
 */
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
OS_EXPORT
@interface OSLogEntryLog : OSLogEntry <OSLogEntryFromProcess, OSLogEntryWithPayload>

/*!
 * @property level
 *
 * @abstract
 * The level of the entry, e.g., info, debug.
 */
@property (nonatomic, readonly) OSLogEntryLogLevel level
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

@end

NS_ASSUME_NONNULL_END

#endif /* __OSLOG_ENTRY_LOG_H__ */
