/**
 @header
 
 Node that references an external serialized node graph
 
 @copyright 2015 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKit.h>
@class SKReferenceNode;

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11)) @interface SKReferenceNode : SKNode

/** Create a reference node with a url */
- (instancetype)initWithURL:(nullable NSURL *)url NS_DESIGNATED_INITIALIZER;

/** Create a reference node with a url */
- (instancetype)initWithFileNamed:(nullable NSString *)fileName NS_DESIGNATED_INITIALIZER;

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;


/** Create a reference node with a url */
+ (instancetype)referenceNodeWithFileNamed:(NSString *)fileName;

/** Create a reference node with a url */
+ (instancetype)referenceNodeWithURL:(NSURL *)referenceURL;


/** called each time the url is loaded, after it has been added as a child */
- (void)didLoadReferenceNode:(nullable SKNode *)node;

/** Force the reference to be reloaded. The resolved node will added
 as a child of this node. If the resolved node has not yet been loaded,
 it will be automatically loaded when the resolved node is queryed or
 the refenece node is rendered. */
- (void)resolveReferenceNode;

@end

NS_ASSUME_NONNULL_END
