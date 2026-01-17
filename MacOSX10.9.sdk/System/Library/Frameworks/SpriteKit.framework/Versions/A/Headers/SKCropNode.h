/**
 @header
 
 
 Node that can crop its children's contents with a mask
 
 
 @copyright 2011 Apple, Inc. All rights reserve.
 
 */

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SpriteKitBase.h>

/**
 A SpriteKit node that masks child nodes using another node's alpha component
 */
SK_EXPORT @interface SKCropNode : SKNode

/**
 SKNode to be used as the mask.
 
 The SKNode supplied as the mask must not be a child of another node, but it may have children. Anywhere the mask's output alpha component is less than 0.05 masks out that area for the SKCropNode's children. If the mask is nil, nothing is masked out.
 */
@property (SK_NONATOMIC_IOSONLY, retain) SKNode *maskNode;

@end
