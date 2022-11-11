//
//  MLModelCollection.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLModelCollectionEntry.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLModelCollection
 *
 * A collection of models managed as part of Core ML Model Deployment.
 */
API_AVAILABLE(macos(11.0), ios(14.0))
API_UNAVAILABLE(tvos, watchos)
ML_EXPORT
@interface MLModelCollection : NSObject

/// The identifier of the model collection you want to access, as configured in the Core ML Model Deployment dashboard.
@property (readonly, nonatomic, copy) NSString *identifier;

/// Information about the models downloaded in the collection, or an empty dictionary if the collection has not been downloaded.
@property (readonly, nonatomic, copy) NSDictionary<NSString *, MLModelCollectionEntry *> *entries;

/// The identifier for the currently downloaded deployment, corresponding to a recent deployment on the Core ML Model Deployment dashboard.
@property (readonly, nonatomic, copy) NSString *deploymentID;

/*!
  Request access to a model collection. If the collection is not downloaded on the device, it is requested
  from Core ML Model Deployment.

  @discussion When called, this method downloads the model collection if it is not already on the device. Once
  all models are downloaded, an MLModelCollection instance is made available for use with the completion handler.

  @param identifier The model collection identifier, as managed in Core ML Model Deployment.
  @param completionHandler The completion handler, invoked with a valid MLModelCollection instance on success or NSError on failure.
  @result NSProgress for updates during setup and download of the model collection
*/
+ (NSProgress *)beginAccessingModelCollectionWithIdentifier:(NSString *)identifier
                                          completionHandler:(void (^)(MLModelCollection *_Nullable modelCollection, NSError *_Nullable error))completionHandler NS_REFINED_FOR_SWIFT;

/*!
  End access to a model collection. This informs the system you have finished accessing the models within the collection.

  @discussion Call this method as soon as you have finished using the models in this collection.

  @param identifier The model collection identifier, as managed in Core ML Model Deployment.
  @param completionHandler The completion handler, invoked with YES on success or NSError on failure.
*/
+ (void)endAccessingModelCollectionWithIdentifier:(NSString *)identifier
                                completionHandler:(void (^)(BOOL success, NSError *_Nullable error))completionHandler NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC_NAME(endAccessing(identifier:));

- (instancetype)init NS_UNAVAILABLE;

+ (id)new NS_UNAVAILABLE;

@end

/// Notification posted when the model collection has changed.
API_AVAILABLE(macos(11.0), ios(14.0))
API_UNAVAILABLE(tvos, watchos)
ML_EXPORT
NSNotificationName const MLModelCollectionDidChangeNotification;

NS_ASSUME_NONNULL_END
