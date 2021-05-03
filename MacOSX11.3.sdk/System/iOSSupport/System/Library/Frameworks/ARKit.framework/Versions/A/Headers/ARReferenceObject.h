//
//  ARReferenceObject.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0))
FOUNDATION_EXTERN NSString *const ARReferenceObjectArchiveExtension NS_SWIFT_NAME(ARReferenceObject.archiveExtension);

@class ARPointCloud;

/**
 A reference object to track in the scene.
 */
API_AVAILABLE(ios(12.0))
@interface ARReferenceObject : NSObject<NSSecureCoding>

/**
 An optional name used to identify the object.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The center of the object in the object’s local coordinate space.
 */
@property (nonatomic, readonly) simd_float3 center;

/**
 The extent of the object in the object’s local coordinate space.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 The scale of the object’s local coordinate space.
 @discussion Multiplying the extent by this scale will result in the physical extent of the object, measured in meters.
 */
@property (nonatomic, readonly) simd_float3 scale;

/**
 The AR resource group name for this object.
 @discussion If this object was loaded via an AR resource group in the Xcode asset catalogue this property will have the name of the resource group,
 else be set to nil.
 */
@property (nonatomic, strong, nullable, readonly) NSString *resourceGroupName API_AVAILABLE(ios(13.0));

/**
 The feature points of the object.
 */
@property (nonatomic, strong, readonly) ARPointCloud *rawFeaturePoints;

/**
 Returns the set of ARReferenceObjects in the specified resource group and bundle.
 
 @param name The name of the resource group.
 @param bundle The bundle containing the image file or asset catalog. Specify nil to search the app’s main bundle.
 @return The set of reference objects or nil on error.
 */
+ (nullable NSSet<ARReferenceObject *> *)referenceObjectsInGroupNamed:(NSString *)name bundle:(nullable NSBundle *)bundle;

/**
 Initializes a new reference object with the contents of an archive at the specified URL.
 @param url The URL from which to read data (.arobject archive).
 @param error The error to populate if the object could not be initialized.
 */
- (nullable instancetype)initWithArchiveURL:(NSURL *)url error:(NSError **)error;

/**
 Exports the object as an archive at the given URL.
 
 @discussion The URL path should use ARReferenceObjectArchiveExtension (.arobject) for the file extension.
 If serialization across devices is desired, NSKeyedArchiver should be used instead.
 @param url The URL at which to write the exported object.
 @param previewImage An optional preview image to include in the archive.
 @param error The error to populate if the write is not successful.
 @return YES if the location is written successfully, otherwise NO.
 */
- (BOOL)exportObjectToURL:(NSURL *)url previewImage:(nullable UIImage *)previewImage error:(NSError **)error;

/**
 Returns a new reference object by applying the specified transform to the object's origin.
 @discussion This can be used to change the reference object's origin with respect to the physical object. Providing
 a transform local to the current object's coordinate space will return an object with the transform's position and orientation as the origin.
 @param transform The rotation and translation to apply to the object's origin.
 @return A reference object with updated origin.
*/
- (ARReferenceObject *)referenceObjectByApplyingTransform:(simd_float4x4)transform;

/**
 Returns a new reference object by aligning and merging the provided object with this reference.
 @discussion This can be used to combine multiple scans of the same object for detection in different conditions. The object being merged
 must share similar feature points for the merge to succeed.
 @param object The reference object to align and merge.
 @param error The error to populate if the merge is not successful.
 @return A new reference object combining features of both scans or nil if the merge was not successful.
 */
- (nullable ARReferenceObject *)referenceObjectByMergingObject:(ARReferenceObject *)object error:(NSError **)error;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
