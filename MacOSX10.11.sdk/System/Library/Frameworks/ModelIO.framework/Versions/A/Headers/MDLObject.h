/*!
 @header MDLObject.h
 @framework ModelIO
 @abstract Base structures for representing components of 3d assets
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLTransform.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MDLTransformComponent;

/*!
 @class MDLObject
 @abstract Base class for object in a ModelIO asset hierarchy
 @discussion Includes transformation and bounds info, links to parent and
             children in the hierachy
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLObject : NSObject<MDLNamed>

/*!
 @method setComponent:forProtocol:
 @abstract Extensible component support that allows user of ModelIO to customize 
           MDLObjects to fit their format and workflow.
 */
- (void)setComponent:(id<MDLComponent>)component forProtocol:(Protocol *)protocol;

/*!
 @method componentConformingToProtocol:
 @abstract Extensible component support that allows user of ModelIO to customize 
           MDLObjects to fit their format and workflow.
 */
- (nullable id<MDLComponent>)componentConformingToProtocol:(Protocol *)protocol;

/*!
 @property parent
 @abstract Parent object. Nil if no parent.
 @discussion Set to nil when you remove this from an object container inside the 
             parent object.
 */
@property (nonatomic, weak, nullable) MDLObject* parent;

/*!
 @property transform
 @abstract Short hand property for the MDLTransformComponent.
 @discussion 
 
 The default value is nil

 Getter is equivalent to "-[componentConformingToProtocol:@protocol(MDLTransformComponent)]"
 Setter is equivalent to "-[setComponent:forProtocol:@protocol(MDLTransformComponent)]"
 
 @see MDLTransformComponent
 */
@property (nonatomic, nullable, retain) id<MDLTransformComponent> transform;

/*!
 @property children
 @abstract Short hand property for the MDLObjectContainerComponent.
 @discussion
  The default value is nil
 
 Getter is equivalent to "-[componentConformingToProtocol:@protocol(MDLObjectContainerComponent)]"
 Setter is equivalent to "-[setComponent:forProtocol:@protocol(MDLObjectContainerComponent)]"
 
 @see MDLObjectContainerComponent
 */
@property (nonatomic, retain) id<MDLObjectContainerComponent> children;

/*!
 @method addChild:
 @abstract Short hand for adding a child to the current container component and 
           setting the parent to this object.
 @discussion  It will create a default container if none exists. If children are 
              explicitly disallowed for an object, then add a container component 
              that throws on addition.
 
 @see MDLObjectContainer
 */
- (void)addChild:(MDLObject *)child;

/*!
 @method boundingBoxAtTime:
 @abstract Bounds ob object at the specified time
 */
- (MDLAxisAlignedBoundingBox)boundingBoxAtTime:(NSTimeInterval)time;

@end

/*!
 @class MDLObjectContainer
 @abstract Default container object
 @discussion Subclass the object container to support custom containers. Such 
             custom containers might reference in memory representations, offline 
             databases, and so on.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLObjectContainer : NSObject<MDLObjectContainerComponent>

@end

NS_ASSUME_NONNULL_END
