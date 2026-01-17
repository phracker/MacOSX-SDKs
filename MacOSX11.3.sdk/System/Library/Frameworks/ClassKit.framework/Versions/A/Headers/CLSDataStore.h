//
//  CLSDataStore.h
//  ClassKit
//
//  Copyright © 2018-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ClassKit/CLSDefines.h>
#import <ClassKit/CLSContext.h>
#import <ClassKit/CLSActivity.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos)
@protocol CLSDataStoreDelegate <NSObject>

@required

/*!
 @abstract      Implement to return a new context with the supplied identifier as a child of the parent context.
 @discussion    This method is invoked for missing contexts in: @code -[CLSDataStore contextsMatchingIdentifierPath:completion:] @endcode and @code -[CLSContext descendantMatchingIdentifierPath:completion:] @endcode
                It will be called successively for each identifier in the path that is not found. This helps centralize context creation in one place.
 @note          New contexts returned in this method are automatically saved.

 @param         identifier              Identifier for the new context.
 @param         parentContext           Parent of the new context.
 @param         parentIdentifierPath    Ordered list of identifiers leading to the parent context.

 @return        The new context for the supplied identifier. The new context is automatically saved.
 */
- (nullable __kindof CLSContext *)createContextForIdentifier:(NSString *)identifier
                                               parentContext:(__kindof CLSContext *)parentContext
                                        parentIdentifierPath:(NSArray<NSString *> *)parentIdentifierPath;

@end


/*!
 @abstract      The data store maintains and syncs your app's contexts.
 */
API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface CLSDataStore : NSObject

/*!
 @abstract      The data store provides read/write access to your app's ClassKit data.
 @discussion    Data written to the data store is automatically synced via iCloud across the user's devices.
 */
@property (class, nonatomic, strong, readonly) CLSDataStore *shared;

/*!
 @abstract      Fetch the top level context for the current app.
 @discussion    The main context is automatically created. Add child contexts to this context to persist them in the data store.
 */
@property (nonatomic, strong, readonly) CLSContext *mainAppContext;

/*!
 @abstract      Returns the context that is currently active. If no context is active, this will return nil.
 */
@property (nullable, nonatomic, strong, readonly) CLSContext *activeContext;

/*!
 @abstract      Returns the most recently started activity that is running.
 */
@property (nullable, nonatomic, strong, readonly) CLSActivity *runningActivity;

/*!
 @abstract      The data store delegate allows for easy population of the app's context hierarchy.
 */
@property (nullable, nonatomic, weak) id<CLSDataStoreDelegate> delegate;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

 /*!
  @abstract      Save changes made in the data store.
  @discussion    Save new/modified/removed contexts, activities, etc. to the local store. In case of an error -[NSError userInfo] will contain the object that caused the error under the CLSErrorObjectKey..
  */
- (void)saveWithCompletion:(nullable void(^)(NSError * _Nullable error))completion;

/*!
 @abstract      Complete all assigned actvities.
 @discussion    Marks all of the currently active assigned activities for this contextPath as complete.
 */
- (void)completeAllAssignedActivitiesMatching:(NSArray<NSString *> *)contextPath API_AVAILABLE(ios(12.2), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

@end

API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface CLSDataStore (Contexts)


 /*!
  @abstract      Fetch contexts matching a predicate.
  @discussion    For example: NSPredicate<topic == kCLSContextTopicPhysics AND parent == someContext>.  Completion block may be called on a background thread.
  */
- (void)contextsMatchingPredicate:(NSPredicate *)predicate
                       completion:(void(^)(NSArray<CLSContext *> *contexts, NSError * _Nullable error))completion;

 /*!
  @abstract      Returns contexts matching a set of identifiers where each identifier is the parent of the following identifier.
  @discussion    For example: @c@["math-game", @c"level1"] returns two contexts where @em math-game is the parent of @em level1.
                 If there are any missing contexts, they will be filled in by calling the following method on the data store's delegate:
                 @code -[CLSDataStoreDelegate createContextForIdentifier:parentContext:parentIdentifierPath:] @endcode
                 If the dataStore does not have a delegate and there are missing contexts then an incomplete list of contexts will be passed to the completion handler.  Completion block may be called on a background thread.
  */
- (void)contextsMatchingIdentifierPath:(NSArray<NSString *> *)identifierPath
                            completion:(void(^)(NSArray<CLSContext *> *contexts, NSError * _Nullable error))completion;

/*!
 @abstract      Mark a context for removal.
 @discussion    Save to commit removal. Removal cascades and deletes all descendants.
 */
- (void)removeContext:(CLSContext *)context;

/*!
@abstract Implement to fetch the current CLSActivity instance for your document to add progress to.
@discussion Gets the currently CLSActivity for the file. If no current activity exists, one will be created for you.
@param  url File url for the document.

*/
- (void)fetchActivityForURL:(NSURL *)url
                 completion:(void(^)(CLSActivity * _Nullable activity, NSError * _Nullable error))completion API_AVAILABLE(ios(14.5), macos(11.3), macCatalyst(14.5)) API_UNAVAILABLE(watchos, tvos);
@end

NS_ASSUME_NONNULL_END
