/*
 * Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef __OSLOG_ENTRY_H__
#define __OSLOG_ENTRY_H__

#ifndef __INDIRECT_OSLOG_HEADER_USER__
#error "Please use <OSLog/OSLog.h> instead of directly using this file."
#endif

@class OSLogMessageComponent;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum OSLogEntryStoreCategory
 *
 * @abstract
 * A classification of how the entry was to be stored and
 * rotated at the point when it was created.
 *
 * @discussion
 * The unified logging system keeps entries in one of two
 * places: a ring buffer in memory and a persisted data store.
 * Entries are rotated out of both places to free up resources.
 * This rotation is not strictly aligned with entries'
 * timestamps --- in particular, they can be rotated in bulk,
 * and they are rotated according to a series of heuristics that
 * take into account space, time, and how the entries were
 * classified.
 *
 * @constant OSLogEntryStoreCategoryMetadata
 * This entry was generated as information about the other
 * entries or about the sequence of entries as a whole.
 *
 * @constant OSLogEntryStoreCategoryShortTerm
 * This entry was not intended to be long-lived and was captured
 * in the ring buffer.
 *
 * @constant OSLogEntryStoreCategoryLongTermAuto
 * The entry was intended to be persisted in a filesystem-backed
 * data store and kept mainly based on the amount of space
 * available.
 *
 * @constant OSLogEntryStoreCategoryLongTerm1
 * @constant OSLogEntryStoreCategoryLongTerm3
 * @constant OSLogEntryStoreCategoryLongTerm7
 * @constant OSLogEntryStoreCategoryLongTerm14
 * @constant OSLogEntryStoreCategoryLongTerm30
 * The entry was tagged with a hint indicating that the system
 * should try to preserve it for a certain amount of time. It
 * was persisted in the filesystem-backed data store, and
 * rotation of these entries was based on both time and space
 * considerations.
 */
typedef NS_ENUM(NSInteger, OSLogEntryStoreCategory) {
    OSLogEntryStoreCategoryUndefined,
    OSLogEntryStoreCategoryMetadata,
    OSLogEntryStoreCategoryShortTerm,
    OSLogEntryStoreCategoryLongTermAuto,
    OSLogEntryStoreCategoryLongTerm1,
    OSLogEntryStoreCategoryLongTerm3,
    OSLogEntryStoreCategoryLongTerm7,
    OSLogEntryStoreCategoryLongTerm14,
    OSLogEntryStoreCategoryLongTerm30,
}
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
NS_SWIFT_NAME(OSLogEntry.StoreCategory);

/*!
 * @class OSLogEntry
 *
 * @abstract
 * A single entry from the unified logging system.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
OS_EXPORT
@interface OSLogEntry : NSObject

/*!
 * @property composedMessage
 *
 * @abstract
 * The fully formatted message for the entry.
 */
@property (nonatomic, readonly) NSString *composedMessage;

/*!
 * @property date
 *
 * @abstract
 * The timestamp of the entry.
 */
@property (nonatomic, readonly) NSDate *date;

/*!
 * @property storeCategory
 *
 * @abstract
 * This entry's storage tag. See OSLogEntryStoreCategory.
 */
@property (nonatomic, readonly) OSLogEntryStoreCategory storeCategory;

@end

/*!
 * @protocol OSLogEntryFromProcess
 *
 * @abstract
 * Entry subclasses conforming to this protocol represent data
 * that are generated from a process; they have metadata about
 * the originator.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
OS_EXPORT
@protocol OSLogEntryFromProcess

/*!
 * @property activityIdentifier
 *
 * @abstract
 * The activity ID associated with the entry.
 */
@property (nonatomic, readonly) os_activity_id_t activityIdentifier;

/*!
 * @property process
 *
 * @abstract
 * The name of the process that made the entry.
 */
@property (nonatomic, readonly) NSString *process;

/*!
 * @property processIdentifier
 *
 * @abstract
 * The pid of the process that made the entry.
 */
@property (nonatomic, readonly) pid_t processIdentifier;

/*!
 * @property sender
 *
 * @abstract
 * The name of the binary image that made the entry.
 */
@property (nonatomic, readonly) NSString *sender;

/*!
 * @property threadIdentifier
 *
 * @abstract
 * The tid of the thread that made the entry.
 */
@property (nonatomic, readonly) uint64_t threadIdentifier;

@end

/*!
 * @protocol OSLogEntryWithPayload
 *
 * @abstract
 * Entry subclasses conforming to this protocol represent
 * entries that were made using a handle and a format string.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
OS_EXPORT
@protocol OSLogEntryWithPayload

/*!
 * @property category
 *
 * @abstract
 * The category from the os_log_t handle used.
 */
@property (nonatomic, readonly) NSString *category;

/*!
 * @property components
 *
 * @abstract
 * An array of the various parts of the composed message.
 */
@property (nonatomic, readonly) NSArray<OSLogMessageComponent *> *components;

/*!
 * @property formatString
 *
 * @abstract
 * The format string used.
 */
@property (nonatomic, readonly) NSString *formatString;

/*!
 * @property subsystem
 *
 * @abstract
 * The subsystem of the os_log_t handle used.
 */
@property (nonatomic, readonly) NSString *subsystem;

@end

NS_ASSUME_NONNULL_END

#endif /* __OSLOG_ENTRY_H__ */
