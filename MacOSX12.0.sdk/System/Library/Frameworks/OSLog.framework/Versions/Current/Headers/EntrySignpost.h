/*
 * Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef __OSLOG_ENTRY_SIGNPOST_H__
#define __OSLOG_ENTRY_SIGNPOST_H__

#ifndef __INDIRECT_OSLOG_HEADER_USER__
#error "Please use <OSLog/OSLog.h> instead of directly using this file."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum OSLogEntrySignpostType
 *
 * @discussion
 * The kind of of signpost emitted.
 */
typedef NS_ENUM(NSInteger, OSLogEntrySignpostType) {
    OSLogEntrySignpostTypeUndefined,
    OSLogEntrySignpostTypeIntervalBegin,
    OSLogEntrySignpostTypeIntervalEnd,
    OSLogEntrySignpostTypeEvent,
}
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
NS_SWIFT_NAME(OSLogEntrySignpost.SignpostType);

/*!
 * @class OSLogEntrySignpost
 *
 * @abstract
 * Entries made by the os_signpost API.
 */
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
OS_EXPORT
@interface OSLogEntrySignpost : OSLogEntry <OSLogEntryFromProcess, OSLogEntryWithPayload>

/*!
 * @property signpostIdentifier
 *
 * @abstract
 * The signpost ID associated with this entry.
 */
@property (nonatomic, readonly) os_signpost_id_t signpostIdentifier
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 * @property signpostName
 *
 * @abstract
 * The signpost name associated with this entry.
 */
@property (nonatomic, readonly) NSString *signpostName
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 * @property signpostType
 *
 * @abstract
 * The signpost type associated with this entry.
 */
@property (nonatomic, readonly) OSLogEntrySignpostType signpostType
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

@end

NS_ASSUME_NONNULL_END

#endif /* __OSLOG_ENTRY_SIGNPOST_H__ */
