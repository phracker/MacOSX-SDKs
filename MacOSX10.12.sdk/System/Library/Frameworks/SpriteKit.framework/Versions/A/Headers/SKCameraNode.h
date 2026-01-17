/**
 @header
 
 Node that controls camera movement, zoom and rotation.
 
 @copyright 2015 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SKNode.h>

NS_ASSUME_NONNULL_BEGIN

/**A Camera node is a full fledged SKNode that can have actions and physics applied to it.
 * It also uses the standard SKNode transform system so modifying the camera node's position
 * is how you translate the camera's viewport. Applying a scale to the node would zoom
 * the viewport in or out etc. As an added benefit you can now rotate the viewport by
 * applying a zRotation to the camera node, just as you would with any other SKNode.
 *
 * The camera viewport is centered on the camera's position. It uses the scene's frame
 * and scale mode along with the node transforms to determine the size, origin and
 * rotation of the viewport.
 *
 * There are some convenience functions included for testing if nodes are contained
 * within the camera viewport. It can be used to determine if objects are no longer
 * visible on the display.
 *
 * In order to use a camera; set it on the scene that contains the camera.
 * @see SKScene.camera
 */
SK_EXPORT NS_AVAILABLE(10_11, 9_0) @interface SKCameraNode : SKNode

/**Checks if the node is contained inside the viewport of the camera.
 * The camera and node must both be in the same scene and presented on a view in order
 * to determine if the node is inside the camera viewport rectangle.
 *
 * @return YES if the node is inside the viewport. NO if node is nil or the node is outside the viewport.
 */
- (BOOL)containsNode:(SKNode *)node;

/**Returns the set of nodes in the same scene as the camera that are contained within its viewport.
 * @return the set of nodes contained
 */
- (NSSet<SKNode*> *)containedNodeSet;

@end

NS_ASSUME_NONNULL_END
