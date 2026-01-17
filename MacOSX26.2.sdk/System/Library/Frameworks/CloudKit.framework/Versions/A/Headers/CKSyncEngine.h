//
//  CKSyncEngine.h
//  CloudKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDefines.h>
#import <CloudKit/CKSyncEngineRecordZoneChangeBatch.h>

@class CKDatabase, CKOperationGroup, CKRecord, CKRecordID, CKRecordZone, CKRecordZoneID;
@class CKSyncEngineConfiguration, CKSyncEngineEvent, CKSyncEngineState, CKSyncEngineStateSerialization;
@class CKSyncEngineFetchChangesContext, CKSyncEngineFetchChangesOptions, CKSyncEngineFetchChangesScope;
@class CKSyncEngineSendChangesContext, CKSyncEngineSendChangesOptions, CKSyncEngineSendChangesScope, CKSyncEnginePendingRecordZoneChange;

@protocol CKSyncEngineDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// `CKSyncEngine` encapsulates the logic of syncing data with a CloudKit database.
///
/// Syncing with CloudKit involves many moving pieces.
/// Apps need to schedule syncs, create and batch operations, subscribe to database changes,
/// listen for push notifications, store sync state, handle a multitude of errors, and more.
/// `CKSyncEngine` is designed to encapsulate this logic in a higher-level API.
///
/// # Start Your Sync Engine
///
/// Generally, you should initialize your `CKSyncEngine` soon after your process launches.
/// The sync engine will perform work in the background on your behalf, and it needs to be initialized
/// so that it can properly listen for push notifications and handle scheduled sync tasks.
///
/// When initializing your sync engine, you need to provide an object conforming to the `CKSyncEngineDelegate` protocol.
/// This protocol is the main method of communication between the sync engine and your app.
/// You also need to provide your last known version of the ``CKSyncEngine/State/Serialization``.
/// See ``CKSyncEngine/State`` and ``CKSyncEngine/Event/StateUpdate`` for more details on the sync engine state.
///
/// Note that before using `CKSyncEngine` in your app, you need to add the CloudKit and remote notification capabilities.
///
/// # Sending Changes to the Server
///
/// In order to send changes to the server, you first need to tell the sync engine you have pending changes to send.
/// You can do this by adding pending changes to the sync engine's ``CKSyncEngine/state`` property.
///
/// When you add pending changes to the state, the sync engine will schedule a task to sync.
/// When the sync task runs, the sync engine will start sending changes to the server.
/// The sync engine will automatically send database changes from ``CKSyncEngine/State/pendingDatabaseChanges``, but you need to provide the record zone changes yourself.
/// In order to send record zone changes, you need to return them from `-[CKSyncEngineDelegate syncEngine:nextRecordZoneChangeBatchForContext:]`.
///
/// When the sync engine finishes sending a batch of changes to the server,
/// your `CKSyncEngineDelegate` will receive ``CKSyncEngine/Event/sentDatabaseChanges(_:)`` and ``CKSyncEngine/Event/sentRecordZoneChanges(_:)`` events.
/// These events will notify you of the success or failure of the changes you tried to send.
///
/// At a high level, sending changes to the server happens with the following order of operations:
///
/// 1. You add pending changes to ``CKSyncEngine/state``.
/// 2. You receive ``CKSyncEngine/Event/willSendChanges(_:)`` in `-[CKSyncEngineDelegate syncEngine:handleEvent:]`
/// 3. If there are pending database changes, the sync engine sends the next batch.
/// 4. If any database changes were sent, your delegate receives``CKSyncEngine/Event/sentDatabaseChanges(_:)``.
/// 5. Repeat from step 3 until all pending database changes are sent, then move on to record zone changes in step 6.
/// 6. The sync engine asks for the next batch of record zone changes by calling `-[CKSyncEngineDelegate syncEngine:nextRecordZoneChangeBatchForContext:]`.
/// 7. The sync engine sends the next record zone change batch to the server.
/// 8. If any record zone changes were sent, your delegate receives ``CKSyncEngine/Event/sentRecordZoneChanges(_:)``.
/// 9. If you added any pending database changes during steps 6-8, the sync engine repeats from step 3. Otherwise, it repeats from step 6.
/// 10. When all pending changes are sent, your delegate receives ``CKSyncEngine/Event/didSendChanges(_:)``.
///
/// # Fetching Changes from the Server
///
/// The sync engine will automatically listen for remote notifications, and it will fetch changes from the server when necessary.
/// Generally, you'll receive events in this order:
///
/// 1. Your delegate receives ``CKSyncEngine/Event/willFetchChanges(_:)``.
/// 2. If there are new database changes to fetch, you receive batches of them in ``CKSyncEngine/Event/fetchedDatabaseChanges(_:)`` events.
/// 3. If there are new record zone changes to fetch, you will receive ``CKSyncEngine/Event/willFetchRecordZoneChanges(_:)`` for each zone that has new changes.
/// 4. The sync engine fetches record zone changes and gives you batches of them in ``CKSyncEngine/Event/fetchedRecordZoneChanges(_:)`` events.
/// 5. Your delegate receives ``CKSyncEngine/Event/didFetchRecordZoneChanges(_:)`` for each zone that had changes to fetch.
/// 6. Your delegate receives ``CKSyncEngine/Event/didFetchChanges(_:)``, indicating that sync engine has finished fetching changes.
///
/// # Sync Scheduling
///
/// ## Automatic sync
///
/// By default, the sync engine will automatically schedule sync tasks on your behalf.
/// If the user is signed in, the device has a network connection, and the system is generally in a good state, these scheduled syncs will happen relatively quickly.
/// However, if the device has no network, is low on power, or is otherwise under a heavy load, these automatic syncs might be delayed.
/// Similarly, if the user isn't signed in to an account, the sync engine won't perform any sync tasks at all.
///
/// ## Manual sync
///
/// Generally, you should rely on this automatic sync behavior, but there may be some cases where you want to manually trigger a sync.
/// For example, if you have a pull-to-refresh UI, you can call ``CKSyncEngine/fetchChanges(_:)`` to tell the sync engine to fetch immediately.
/// Or if you want to provide some sort of "backup now" button, you can call ``CKSyncEngine/sendChanges(_:)`` to send to the server immediately.
///
/// ### Testing
///
/// These manual sync functions might also be useful during automated testing.
/// When writing automated tests, you can turn off automatic sync via ``CKSyncEngine/Configuration/automaticallySync``.
/// Then, you'll have complete control over the ordering of sync events.
/// This allows you to interject behavior in the sync flow and simulate specific sequences of events.
///
/// # Error Handling
///
/// There are some transient errors that the sync engine will handle automatically behind the scenes.
/// The sync engine will retry the operations for these transient errors automatically when it makes sense to do so.
/// Specifically, the sync engine will handle the following errors on your behalf:
///
/// * ``CKError/notAuthenticated``
/// * ``CKError/accountTemporarilyUnavailable``
/// * ``CKError/networkFailure``
/// * ``CKError/networkUnavailable``
/// * ``CKError/requestRateLimited``
/// * ``CKError/serviceUnavailable``
/// * ``CKError/zoneBusy``
///
/// When the sync engine encounters one of these errors, it will wait for the system to be in a good state and try again.
/// For example, if the server sends back a `.requestRateLimited` error, the sync engine will respect this throttle and try again after the retry-after time.
///
/// `CKSyncEngine` will _not_ handle errors that require application-specific logic.
/// For example, if you try to save a record and get a ``CKError/serverRecordChanged``, you need to handle that error yourself.
/// There are plenty of errors that the sync engine cannot handle on your behalf, see ``CKError`` for a list of all the possible errors.
///
/// # Accounts
///
/// `CKSyncEngine` monitors for account status, and it will only sync if there's an account signed in.
/// Because of this, you can initialize your `CKSyncEngine` at any time, regardless of account status.
/// If there is no account, or if the user disabled sync in settings, the sync engine will stay dormant in the background.
/// Once an account is available, the sync engine will start syncing automatically.
///
/// It will also listen for when the user signs in or out of their account.
/// When it notices an account change, it will send an ``CKSyncEngine/Event/accountChange(_:)`` to your delegate.
/// It's your responsibility to react appropriately to this change and update your local persistence.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngine : NSObject

/// Initializes a `CKSyncEngine` with the given configuration.
/// See properties on ``CKSyncEngineConfiguration`` for more details on all the options.
- (instancetype)initWithConfiguration:(CKSyncEngineConfiguration *)configuration NS_SWIFT_NAME(init(_:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The database this sync engine will sync with.
@property (readonly, strong) CKDatabase *database;

/// A collection of state properties used to efficiently manage sync engine operation.
/// See ``CKSyncEngineState`` for more details.
@property (readonly, strong) CKSyncEngineState *state;

#pragma mark - Fetching and Sending

/// Fetches changes from the server immediately, bypassing the system scheduler.
///
/// By default, the sync engine will automatically fetch changes from the server for you, and you should not have to call this function.
/// However, you can call this if for some reason you need to ensure all changes have been fetched from the server before proceeding.
/// For example, you might use this in your tests to simulate specific sync scenarios.
///
/// Fetching changes from the server might result in some events being posted to your delegate via `handleEvent`.
/// For example, you might receive a `CKSyncEngineWillFetchChangesEvent` or `CKSyncEngineDidFetchChangesEvent`.
/// This will not complete until all the relevant events have been handled by your delegate.
- (void)fetchChangesWithCompletionHandler:(nullable void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler;

/// Fetches changes from the server with the specified options.
/// See ``fetchChangesWithCompletionHandler:`` for more information.
- (void)fetchChangesWithOptions:(CKSyncEngineFetchChangesOptions *)options completionHandler:(nullable void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(fetchChanges(_:)) NS_SWIFT_NAME(fetchChanges(_:completionHandler:));

/// Sends any pending changes to the server immediately, bypassing the system scheduler.
///
/// By default, the sync engine will automatically send changes to the server for you, and you should not have to call this function.
/// However, you can call this if for some reason you need to ensure all changes have been sent to the server before proceeding.
/// For example, you might consider using this in your tests to simulate specific sync scenarios.
///
/// Sending changes to the server might result in some events being posted to your delegate via `handleEvent`.
/// For example, you might receive a `CKSyncEngineWillSendChangesEvent` or `CKSyncEngineDidSendChangesEvent`.
/// This function will not return until all the relevant events have been handled by your delegate.
- (void)sendChangesWithCompletionHandler:(nullable void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler;

/// Sends pending changes to the server with the specified options.
/// See discussion in ``sendChangesWithCompletionHandler:`` for more information.
- (void)sendChangesWithOptions:(CKSyncEngineSendChangesOptions *)options completionHandler:(nullable void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(sendChanges(_:)) NS_SWIFT_NAME(sendChanges(_:completionHandler:));

/// Cancels any currently executing or pending sync operations.
///
/// Note that cancellation does not happen synchronously, and it's possible some in-flight operations will succeed.
- (void)cancelOperationsWithCompletionHandler:(nullable void (NS_SWIFT_SENDABLE ^)(void))completionHandler;

@end

#pragma mark - Delegate

/// An interface by which `CKSyncEngine` communicates with your application.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
@protocol CKSyncEngineDelegate <NSObject>

/// Called when an event occurs during the sync engine's operation.
///
/// This is how you receive updates about local state changes, fetched changes, sent changes, and more.
/// See ``CKSyncEngineEventType`` and ``CKSyncEngineEvent`` for all the possible events that might be posted.
///
/// ## Event ordering
///
/// Events will be given to your delegate serially.
/// You will not receive the next event until you have returned from this function for the previous event.
- (void)syncEngine:(CKSyncEngine *)syncEngine handleEvent:(CKSyncEngineEvent *)event NS_SWIFT_NAME(syncEngine(_:handleEvent:));

/// Called to get the next batch of record zone changes to send to the server.
///
/// The sync engine will call this function when it's about to to send changes to the server.
/// This might happen during an automatically scheduled sync or as a result of you calling `sendChanges`.
/// Provide the next batch of record zone changes to send by returning them from this function.
///
/// Once the sync engine starts sending changes, it will continue until there are no more pending changes to send.
/// You can return `nil` to indicate that you have no more pending changes for now.
/// The next time the sync engine tries to sync, it will call this again to get any new pending changes.
///
/// ## Sending changes for specific zones
///
/// When you call ``CKSyncEngine/sendChanges(_:)`` for a specific set of zone IDs, you should make sure to only send changes for those zones.
/// You can do this by checking the `zoneIDs` property on ``CKSyncEngineSendChangesContext/options``.
///
/// For example, you might have some code like this:
///
/// ```objc
/// - (CKSyncEngineRecordZoneChangeBatch *)syncEngine:(CKSyncEngine *)syncEngine nextRecordZoneChangeBatchForContext:(CKSyncEngineSendChangesContext *)context {
///     CKSyncEngineSendChangesScope *scope = context.options.scope;
///
///     NSMutableArray<CKSyncEnginePendingRecordZoneChange *> *pendingChanges = [NSMutableArray new];
///     for (CKSyncEnginePendingRecordZoneChange *pendingChange in syncEngine.state.pendingRecordZoneChanges) {
///         if ([scope containsPendingRecordZoneChange:pendingChange]) {
///             [filteredChanges addObject:pendingChange];
///         }
///     }
///
///     CKSyncEngineRecordZoneChangeBatch *batch = [[CKSyncEngineRecordZoneChangeBatch alloc] initWithPendingChanges:pendingChangesToSave recordProvider:^CKRecord * _Nullable(CKRecordID *recordID) {
///         return [self recordToSaveForRecordID:recordID];
///     }];
///
///     return batch;
/// }
/// ```
- (nullable CKSyncEngineRecordZoneChangeBatch *)syncEngine:(CKSyncEngine *)syncEngine nextRecordZoneChangeBatchForContext:(CKSyncEngineSendChangesContext *)context NS_SWIFT_NAME(syncEngine(_:nextRecordZoneChangeBatch:));

@optional

/// Returns a custom set of options for `CKSyncEngine` to use while fetching changes.
///
/// While `CKSyncEngine` fetches changes from the server, it calls this function to determine priority and other options for fetching changes.
/// This allows you to configure your fetches dynamically while the state changes in your app.
///
/// For example, you can use this to prioritize fetching the object currently showing in the UI.
/// You can also use this to prioritize specific zones during initial sync.
///
/// By default, `CKSyncEngine` will use whatever options are in the context.
/// You can return `context.options` if you don't want to perform any customization.
///
/// This callback will be called in between each server request while fetching changes.
/// This allows the fetching mechanism to react dynamically while your app state changes.
///
/// An example implementation might look something like this:
/// ```objc
/// - (CKSyncEngineFetchChangesOptions *)syncEngine:(CKSyncEngine *)syncEngine nextFetchChangesOptionsForContext:(CKSyncEngineFetchChangesContext *)context {
///
///      // Start with the options from the context.
///     CKSyncEngineFetchChangesOptions *options = context.options;
///
///     // By default, the sync engine will automatically fetch changes for all zones.
///     // If you know that you only want to sync a specific set of zones, you can override that here.
///     options.scope = [[CKSyncEngineFetchChangesScope alloc] initWithZoneIDs:@[...]];
///
///     // You can prioritize specific zones to be fetched first by putting them in order.
///     NSMutableArray<CKRecordZoneID *> *prioritizedZoneIDs = [[NSMutableArray alloc] init];
///
///     // If you're showing some data in the UI, you might want to prioritize that zone first.
///     CKRecordZoneID *onScreenZoneID = uiController.currentlyViewedItem.zoneID;
///     if (onScreenZoneID != nil) {
///         [prioritizedZoneIDs addObject:onScreenZoneID];
///     }
///
///     // You could also prioritize special, well-known zones if that makes sense for your app.
///     // For example, if you have a top-level metadata zone that you'd like to sync first, you can prioritize that here.
///     CKRecordZoneID *topLevelZoneID = [[CKRecordZoneID alloc] initWithZoneName:@"MyImportantMetadata"];
///     [prioritizedZoneIDs addObject:topLevelZoneID];
///
///     options.prioritizedZoneIDs = prioritizedZoneIDs;
///     return options
/// }
/// ```
- (CKSyncEngineFetchChangesOptions *)syncEngine:(CKSyncEngine *)syncEngine nextFetchChangesOptionsForContext:(CKSyncEngineFetchChangesContext *)context NS_SWIFT_NAME(syncEngine(_:fetchChangesOptions:));

@end

#pragma mark - Misc

/// A set of options to use when fetching changes from the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchChangesOptions : NSObject <NSCopying>

/// The scope in which to fetch changes from the server.
@property (copy) CKSyncEngineFetchChangesScope *scope;

/// The operation group to use for the underlying operations when fetching changes.
///
/// You might set an operation group with a particular name in order to help you analyze telemetry in the CloudKit Console.
/// If you don't provide an operation group, a default one will be created for you.
@property (strong) CKOperationGroup *operationGroup;

/// A list of zones that should be prioritized over others while fetching changes.
///
/// `CKSyncEngine` will fetch changes for the zones in this list first before any other zones.
/// You might use this to prioritize a specific set of zones for initial sync.
/// You could also prioritize the object currently showing in the UI by putting it first in this list.
///
/// Any zones not included in this list will be prioritized in a default manner.
/// If a zone in this list has no changes to fetch, then that zone will be ignored.
@property (copy) NSArray<CKRecordZoneID *> *prioritizedZoneIDs;

/// Initializes a set of options with the specific scope.
/// If no scope is provided, the default scope will include everything.
- (instancetype)initWithScope:(nullable CKSyncEngineFetchChangesScope *)scope;

@end

/// A scope in which the sync engine will fetch changes from the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchChangesScope : NSObject <NSCopying>

/// A specific set of zone IDs to include in the scope.
/// For example, if you want to fetch changes for a specific set of zones, you can specify them here.
/// If `nil`, this scope includes all zones except those in `excludedZoneIDs`.
@property (nullable, readonly, copy) NSSet<CKRecordZoneID *> *zoneIDs;

/// A specific set of zone IDs to exclude from this scope.
/// If you know that you don't want to fetch changes for a particular set of zones, you can set those zones here.
@property (readonly, copy) NSSet<CKRecordZoneID *> *excludedZoneIDs;

/// Creates a scope that includes only the specified set of zones.
- (instancetype)initWithZoneIDs:(nullable NSSet<CKRecordZoneID *> *)zoneIDs;

/// Creates a scope that includes all zones except the specified excluded zones.
- (instancetype)initWithExcludedZoneIDs:(NSSet<CKRecordZoneID *> *)zoneIDs;

/// Returns true if the specified zone ID is included in this scope.
- (BOOL)containsZoneID:(CKRecordZoneID *)zoneID API_AVAILABLE(macos(14.2), macCatalyst(17.2), ios(17.2), tvos(17.2), watchos(10.2));

@end

/// A set of options to use when sending changes to the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineSendChangesOptions : NSObject <NSCopying>

/// The scope in which to send changes to the server.
@property (copy) CKSyncEngineSendChangesScope *scope;

/// The operation group to use for the underlying operations when sending changes.
///
/// You might set an operation group with a particular name in order to help you analyze telemetry in the CloudKit Console.
/// If you don't provide an operation group, a default one will be created for you.
@property (strong) CKOperationGroup *operationGroup;

/// Initializes a set of options with the specific scope.
/// If no scope is provided, the default scope will include everything.
- (instancetype)initWithScope:(nullable CKSyncEngineSendChangesScope *)scope;

@end

/// A scope in which the sync engine will send changes to  the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineSendChangesScope : NSObject <NSCopying>

/// The scope of zone IDs in which to send changes.
///
/// If you only want to send changes for a particular set of zones, you can initialize your scope with those zone IDs.
/// When creating the next batch of changes to send to the server, consult this and only send changes within these zones.
/// If this and `recordIDs` are `nil`, then you should send all changes.
@property (nullable, readonly, copy) NSSet<CKRecordZoneID *> *zoneIDs;

/// A specific set of zone IDs to exclude from this scope.
/// If you know that you don't want to send changes for a particular set of zones, you can set those zones here.
///
/// Note that if `zoneIDs` is set, then  `excludedZoneIDs` will always be empty.
@property (readonly, copy) NSSet<CKRecordZoneID *> *excludedZoneIDs;

/// The scope of record IDs in which to send changes.
///
/// If you only want to send changes for a particular set of records, you can initialize your scope with those records IDs.
/// When creating the next batch of changes to send to the server, consult this property and only send changes for these record IDs.
/// If this and `zoneIDs` are `nil`, then you should send all changes.
@property (nullable, readonly, copy) NSSet<CKRecordID *> *recordIDs;

/// Creates a scope that contains only the given zone IDs.
/// If `zoneIDs` is nil, then this scope contains all zones.
- (instancetype)initWithZoneIDs:(nullable NSSet<CKRecordZoneID *> *)zoneIDs;

/// Creates a scope that contains all zones except for the given zone IDs.
- (instancetype)initWithExcludedZoneIDs:(NSSet<CKRecordZoneID *> *)excludedZoneIDs;

/// Creates a scope that includes only the given record IDs.
/// If `recordIDs` is nil, this scope contains all records.
- (instancetype)initWithRecordIDs:(nullable NSSet<CKRecordID *> *)recordIDs;

/// Returns true if this scope includes the given record ID.
- (BOOL)containsRecordID:(CKRecordID *)recordID;

/// Returns true if this scope includes the given pending change.
- (BOOL)containsPendingRecordZoneChange:(CKSyncEnginePendingRecordZoneChange *)pendingRecordZoneChange;

@end

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEngineSyncReason) {

    /// This sync was scheduled automatically by the sync engine.
    CKSyncEngineSyncReasonScheduled,

    /// This sync was requested manually by calling ``CKSyncEngine/fetchChanges(_:)`` or ``CKSyncEngine/sendChanges(_:)``.
    CKSyncEngineSyncReasonManual,
};

/// The context of an attempt to fetch changes from the server.
///
/// The sync engine might attempt to fetch changes to the server for many reasons.
/// For example, if you call ``CKSyncEngine/fetchChanges(_:)``, it'll try to fetch changes immediately.
/// Or if it receives a push notification, it'll schedule a sync and fetch changes when the scheduler task runs.
/// This object represents one of those attempts to fetch changes.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchChangesContext : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The reason why the sync engine is attempting to fetch changes.
@property (readonly, assign) CKSyncEngineSyncReason reason;

/// The options being used for this attempt to fetch changes.
@property (readonly, copy) CKSyncEngineFetchChangesOptions *options;

@end

/// The context of an attempt to send changes to the server.
///
/// The sync engine might attempt to send changes to the server for many reasons.
/// For example, if you call ``CKSyncEngine/sendChanges(_:)``, it'll try to send changes immediately.
/// Or if you add pending changes to the state, it'll schedule a sync and send changes when the scheduler task runs.
/// This object represents one of those attempts to send changes.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineSendChangesContext : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The reason why the sync engine is attempting to send changes.
@property (readonly, assign) CKSyncEngineSyncReason reason;

/// The options being used for this attempt to send changes.
@property (readonly, copy) CKSyncEngineSendChangesOptions *options;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
