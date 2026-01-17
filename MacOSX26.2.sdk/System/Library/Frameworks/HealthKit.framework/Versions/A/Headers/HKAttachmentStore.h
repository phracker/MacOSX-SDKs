//
//  HKAttachmentStore.h
//  HealthKit
//
//  Copyright © 2022-2024 Apple. All rights reserved.
//

#import <HealthKit/HKAttachment.h>
#import <HealthKit/HKDefines.h>

@class HKHealthStore;
@class HKObject;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKAttachmentStore
 @discussion    The HKAttachmentStore class provides an interface for accessing and storing HKAttachment objects.
 */
HK_EXTERN
API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0))
@interface HKAttachmentStore : NSObject

/*!
 @method        initWithHealthStore:
 @abstract      The designated initializer to create an HKAttachmentStore.
 @param         healthStore     Specifies the HKHealthStore object to use.
 */
- (instancetype)initWithHealthStore:(HKHealthStore *)healthStore;

/*!
 @method        addAttachmentToObject:name:contentType:URL:metadata:completion:
 @abstract      Creates a new HKAttachment using the passed in NSURL and attaches it to the specified HKObject.
 @param         object          The object for which to add the HKAttachment.
 @param         name            The name of the attachment.
 @param         contentType     The content type of the attachment.
 @param         URL             The NSURL to use to create the attachment.
 @param         metadata        Extra information describing the attachment.
 @param         completion      Called with an HKAttachment instance once the file was successfully saved and attached,
                                otherwise called with an error.
 */
- (void)addAttachmentToObject:(HKObject *)object
                         name:(NSString *)name
                  contentType:(UTType *)contentType
                          URL:(NSURL *)URL
                     metadata:(nullable NSDictionary<NSString *, id> *)metadata
                   completion:(void (^)(HKAttachment * _Nullable attachment, NSError * _Nullable error))completion NS_REFINED_FOR_SWIFT;

/*!
 @method        removeAttachment:fromObject:completion:
 @abstract      Removes the given HKAttachment from the specified HKObject.
 @param         attachment      The HKAttachment to be removed.
 @param         object          The object from which to remove the attachment.
 @param         completion      Called once the remove operation finishes.
 */
- (void)removeAttachment:(HKAttachment *)attachment
              fromObject:(HKObject *)object
              completion:(void (^)(BOOL success, NSError * _Nullable error))completion NS_SWIFT_NAME(removeAttachment(_:from:completion:)) NS_SWIFT_ASYNC_THROWS_ON_FALSE(1);

/*!
 @method        getAttachmentsForObject:completion:
 @abstract      Retrieves a list of attachments for a given object.
 @param         object               The object for which to retrieve attachments.
 @param         completion           Called with a list of attachments or an error.
 */
- (void)getAttachmentsForObject:(HKObject *)object
                     completion:(void(^)(NSArray<HKAttachment *> * _Nullable attachments, NSError * _Nullable error))completion NS_SWIFT_NAME(getAttachments(for:completion:)) NS_SWIFT_ASYNC_NAME(attachments(for:));

/*!
 @method        getDataForAttachment:completion:
 @abstract      Retrieves the NSData for the given HKAttachment.
 @discussion    Prefer @c streamDataForAttachment:completion: for large files that support incremental reading to limit your app's peak memory usage.
                The attachment's data may not always be available locally, and could be stored in iCloud.
 @param         attachment           The attachment object to read data from.
 @param         completion           Called with an NSData or an error.
 @return        An NSProgress object to use for tracking the progress of downloading the attachment's data from iCloud.
 */
- (NSProgress *)getDataForAttachment:(HKAttachment *)attachment
                          completion:(void(^)(NSData * _Nullable attachmentData, NSError * _Nullable error))completion NS_SWIFT_NAME(getData(for:completion:));

/*!
 @method        streamDataForAttachment:dataHandler:
 @abstract      Streams the given HKAttachment's data as ordered NSData chunks.
 @discussion    The dataHandler's done parameter is set to YES when all chunks have been streamed.
                The attachment's data may not always be available locally, and could be stored in iCloud.
 @param         attachment           The attachment object to read data from.
 @param         dataHandler          Called with an NSData chunk or an error. When done is YES, the operation has completed.
 @return        An NSProgress object to use for tracking the progress of downloading the attachment's data from iCloud.
 */
- (NSProgress *)streamDataForAttachment:(HKAttachment *)attachment
                            dataHandler:(void(^)(NSData * _Nullable dataChunk, NSError * _Nullable error, BOOL done))dataHandler;

@end

NS_ASSUME_NONNULL_END
