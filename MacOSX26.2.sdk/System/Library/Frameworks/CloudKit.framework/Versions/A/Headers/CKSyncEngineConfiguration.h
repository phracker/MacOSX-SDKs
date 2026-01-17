//
//  CKSyncEngineConfiguration.h
//  CloudKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKSubscription.h>

@class CKDatabase, CKSyncEngineStateSerialization;
@protocol CKSyncEngineDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineConfiguration : NSObject

- (instancetype)initWithDatabase:(CKDatabase *)database
              stateSerialization:(nullable CKSyncEngineStateSerialization *)stateSerialization
                        delegate:(id<CKSyncEngineDelegate>)delegate;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The database for this sync engine to sync with.
///
/// You can have multiple instances of `CKSyncEngine` in the same process, each targeting a different database.
/// For example, you might have one for your private database and one for your shared database.
///
/// It's also technically possible to have multiple instances of `CKSyncEngine` for the same ``CKDatabase``.
/// This isn't recommended for production code, but it can be helpful for testing your `CKSyncEngine` integration.
/// For example, you might make multiple `CKSyncEngine` instances to simulate multiple devices syncing back and forth.
@property (strong) CKDatabase *database;

/// The state serialization you last received in a ``CKSyncEngine/Event/StateUpdate``.
///
/// If this is the first time ever initializing your `CKSyncEngine`, you can provide `nil`.
@property (nullable, copy) CKSyncEngineStateSerialization *stateSerialization;

/// Your implementation of `CKSyncEngineDelegate`.
@property (weak) id<CKSyncEngineDelegate> delegate;

/// Whether or not the sync engine should automatically sync on your behalf.
///
/// If true, then the sync engine will automatically sync using the system scheduler. This is the default value.
/// When you add pending changes to the state, the sync engine will automatically schedule a sync task to send changes.
/// When it receives a notification about new changes on the server, it will automatically schedule a sync task to fetch changes.
/// It will also automatically re-schedule sync tasks for retryable errors such as network failures or server throttles.
///
/// If ``CKSyncEngineConfiguration/automaticallySync`` is off, then the sync engine will not perform any operations unless you tell it to do so via ``CKSyncEngine/fetchChanges(_:)`` or ``CKSyncEngine/sendChanges(_:)``.
///
/// Most applications likely want to enable automatic syncing during normal use.
/// However, you might want to disable it if you have specific requirements for when you want to sync.
/// For example, if you want to sync only once per day, you can turn off automatic sync and manually call ``CKSyncEngine/fetchChanges(_:)`` and ``CKSyncEngine/sendChanges(_:)`` once per day.
///
/// You might also disable automatic sync when writing automated tests for your integration with `CKSyncEngine`.
/// This way, you can have fine grained control over exactly when the sync engine fetches or sends changes.
/// This allows you to simulate edge cases and deterministically test your logic around scenarios like conflict resolution and error handling.
@property (assign) BOOL automaticallySync;

/// An optional override for the sync engine's default database subscription ID.
/// Use this for backward compatibility with a previous CloudKit sync implementation.
///
/// By default, `CKSyncEngine` will create its own ``CKDatabaseSubscription`` with its own subscription ID.
/// If you're migrating to `CKSyncEngine` from a custom CloudKit sync implementation, you can specify your previous subscription ID here.
/// This allows your `CKSyncEngine` integration to be backward compatible with previous versions of your app.
///
/// >Note: `CKSyncEngine` will automatically attempt to discover any previous database subscriptions,
/// but you can be more explicit by giving the subscription ID through this configuration option.
@property (nullable, copy) CKSubscriptionID subscriptionID;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
