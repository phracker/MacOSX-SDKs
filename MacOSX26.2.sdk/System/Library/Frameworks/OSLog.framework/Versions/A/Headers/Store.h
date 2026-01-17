/*
 * Copyright (c) 2018-2019 Apple Inc. All rights reserved.
 */

#ifndef __OSLOG_STORE_H__
#define __OSLOG_STORE_H__

#ifndef __INDIRECT_OSLOG_HEADER_USER__
#error "Please use <OSLog/OSLog.h> instead of directly using this file."
#endif

@class OSLogEnumerator;
@class OSLogPosition;

/*!
 * @enum OSLogStoreScope
 *
 * @abstract
 * Create a store to a subset of the libtrace entries.
 *
 * @constant OSLogStoreSystem
 * @constant OSLogStoreCurrentProcessIdentifier
 * "System" scope indicates the entire system; i.e., all logs. Entries can be
 * retrieved for the current calling process, i.e., matching pid.
 */
typedef NS_ENUM(NSInteger, OSLogStoreScope) {
    OSLogStoreSystem API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, tvos, watchos) = 0,
    OSLogStoreCurrentProcessIdentifier = 1,
}
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
NS_SWIFT_NAME(OSLogStore.Scope);

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class OSLogStore
 *
 * @abstract
 * A set of entries from the unified logging system. Instances
 * represent a fixed range of entries and may be backed by a
 * logarchive or the Mac's local store.
 *
 * @discussion
 * Entries in OSLogStore objects are used by OSLogEnumerator
 * instances; one store can support multiple OSLogEnumerator
 * instances concurrently.
 */
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
OS_EXPORT
@interface OSLogStore : NSObject

/*!
 * @method localStoreAndReturnError
 *
 * @abstract
 * Create an OSLogStore representing the Mac's local store.
 *
 * @param error
 * If initialization is unsuccessful --- for example, this process
 * does not have access to local logs --- return nil and set this
 * parameter to a pointer to an error object describing the reason.
 *
 * @discussion
 * This enables processing of a sequence of logs as of the particular
 * point in time when this object is created.
 *
 * Gaining access to the local unified logging system requires
 * permission from the system. The caller must be run by an admin
 * account.
 */
+ (nullable instancetype)localStoreAndReturnError:(NSError **)error
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos)
NS_SWIFT_NAME(local());

/*!
 * @method storeWithScope
 *
 * @abstract
 * Create an OSLogStore for a subset of entries in the local store.
 *
 * @param scope
 * The kind of subset the OSLogStore is for.
 *
 * @param error
 * If initialization is unsuccessful, return nil and set this parameter to a
 * pointer to an error object that describes the reason.
 */
+ (nullable instancetype)storeWithScope:(OSLogStoreScope)scope
                                  error:(NSError **)error
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 * @method storeWithURL
 *
 * @abstract
 * Create an OSLogStore based on a logarchive.
 *
 * @param url
 * The path identifying a logarchive to be read.
 *
 * @param error
 * If initialization is unsuccessful --- for example, the path is not
 * to a valid logarchive or the logarchive is not compatible because
 * it is from a newer version --- return nil and set this parameter
 * to a pointer to an error object that describes the reason.
 */
+ (nullable instancetype)storeWithURL:(NSURL *)url
                                error:(NSError **)error
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

- (instancetype)init
API_DEPRECATED("Use one of the factory methods", macos(10.15, 12.0))
API_UNAVAILABLE(ios, tvos, watchos);

/*!
 * @method entriesEnumeratorWithOptions
 *
 * @abstract
 * Return an OSLogEnumerator object based on an underlying store.
 * This object represents the sequence of entries for the store.
 * OSLogStore. Additional parameters control which entries are
 * yielded and their order.
 *
 * @param options
 * Control the direction of iteration.
 *
 * @param position
 * Where to start iteration. If nil, depend on the direction of
 * the iteration: if forwards, start with the earliest entry; if
 * reverse, start with the latest entry.
 *
 * @param predicate
 * A predicate that filters which entries are in the sequence. If
 * this is nil, yield all entries.
 *
 * @param error
 * If the enumerator cannot be set up --- for example, the
 * predicate has an unrecognized key --- return nil and set this
 * to a pointer to an error object that describes the reason.
 */
- (nullable OSLogEnumerator *)entriesEnumeratorWithOptions:(OSLogEnumeratorOptions)options
                                                  position:(nullable OSLogPosition *)position
                                                 predicate:(nullable NSPredicate *)predicate
                                                     error:(NSError **)error
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
NS_REFINED_FOR_SWIFT;

/*!
 * @method entriesEnumeratorAndReturnError
 *
 * @abstract
 * Return an OSLogEnumerator object with default options for
 * viewing the entries; all are viewed, from earliest to latest.
 *
 * @param error
 * If the enumerator cannot be set up, return nil and set this
 * to a pointer to an error object that describes the reason.
 */
- (nullable OSLogEnumerator *)entriesEnumeratorAndReturnError:(NSError **)error
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
NS_SWIFT_UNAVAILABLE("Use `entries` method");

/*!
 * @method positionWithDate
 *
 * @abstract
 * Return a position representing the time specified.
 *
 * @param date
 * The date to look for.
 *
 * @discussion
 * If there are multiple occurences of the same time --- if, for
 * example, there was a time change during the range of entries
 * --- the earliest occurrence is used.
 */
- (OSLogPosition *)positionWithDate:(NSDate *)date
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
NS_SWIFT_NAME(position(date:));

/*!
 * @method positionWithTimeIntervalSinceEnd
 *
 * @abstract
 * Return a position representing an offset since the end of the time
 * range that the entries span.
 *
 * @param seconds
 * The seconds to add to the last time point in the range of entries.
 */
- (OSLogPosition *)positionWithTimeIntervalSinceEnd:(NSTimeInterval)seconds
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
NS_SWIFT_NAME(position(timeIntervalSinceEnd:));

/*!
 * @method positionWithTimeIntervalSinceLatestBoot
 *
 * @abstract
 * Return a position representing time since the last boot in the
 * series of entries.
 *
 * @param seconds
 * The seconds to add to the boot time point in the log time range.
 *
 * @discussion
 * Negative seconds would create an ambiguous or imprecise position;
 * this function asserts that the interval is positive.
 */
- (OSLogPosition *)positionWithTimeIntervalSinceLatestBoot:(NSTimeInterval)seconds
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
NS_SWIFT_NAME(position(timeIntervalSinceLatestBoot:));

@end

NS_ASSUME_NONNULL_END

#endif /* __OSLOG_STORE_H__ */
