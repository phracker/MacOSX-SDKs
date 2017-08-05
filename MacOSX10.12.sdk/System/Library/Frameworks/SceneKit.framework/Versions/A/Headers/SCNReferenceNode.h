//
//  SCNReferenceNode.h
//
//  Copyright (c) 2015-2016 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNNode.h>

NS_ASSUME_NONNULL_BEGIN

/*! @enum SCNReferenceLoadingPolicy
 @abstract Controls whenever to load the reference node.
 @discussion When the load policy is set to SCNReferenceLoadingPolicyImmediately, the reference is loaded immediately when the SCNReferenceNode is unarchived.
 When the load policy is set to SCNReferenceLoadingPolicyOnDemand the reference is never loaded until "load" is explicitly invoked.
 */
typedef NS_ENUM(NSInteger, SCNReferenceLoadingPolicy) {
    SCNReferenceLoadingPolicyImmediate = 0,
    SCNReferenceLoadingPolicyOnDemand  = 1
} API_AVAILABLE(macosx(10.11), ios(9.0));

/*!
 @class SCNReferenceNode
 @abstract Node that references an external file.
 */
API_AVAILABLE(macosx(10.11), ios(9.0))
@interface SCNReferenceNode : SCNNode

/*!
 @method initWithURL:
 @abstract Creates a reference node with a url.
 */
- (nullable instancetype)initWithURL:(NSURL *)referenceURL NS_DESIGNATED_INITIALIZER;

/*!
 @method initWithCoder:
 @abstract Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/*!
 @method referenceNodeWithURL:
 @abstract Creates a reference node with a url.
 */
+ (nullable instancetype)referenceNodeWithURL:(NSURL *)referenceURL;

/*!
 @property referenceURL
 @abstract Specifies the url to resolve.
 */
@property(copy, nonatomic) NSURL *referenceURL;

/*!
 @property loadingPolicy
 @abstract Specifies when to load the reference. see SCNReferenceLoadingPolicy above. Defaults to SCNReferenceLoadingPolicyImmediately.
 */
@property(nonatomic) SCNReferenceLoadingPolicy loadingPolicy;

/*!
 @method load
 @abstract Force the reference to be loaded if it hasn't been loaded already. The resolved nodes will be added
 as child nodes of the receiver.
 */
- (void)load;

/*!
 @method unload
 @abstract Remove the child nodes and mark as unloaded.
 */
- (void)unload;

/*!
 @property loaded
 @abstract Indicates whether the referenced URL has been loaded.
 */
@property(readonly, getter=isLoaded) BOOL loaded;

@end

NS_ASSUME_NONNULL_END
