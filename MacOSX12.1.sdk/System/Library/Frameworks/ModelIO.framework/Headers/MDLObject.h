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
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLObject : NSObject<MDLNamed>

/*!
 @property components
 @abstract Allows applications to introspect the components on the objects.
 */
@property (nonatomic, readonly, copy) NSArray<id<MDLComponent>> *components;

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
 @method objectForKeyedSubscript:
 @abstract Allows shorthand [key] syntax for componentConformingToProtocol:.
 @param key The protocol that the component conforms to.
 @see componentConformingToProtocol:
 */
- (nullable id<MDLComponent>)objectForKeyedSubscript:(Protocol *)key;

/*!
 @method setObject:forKeyedSubscript:
 @abstract Allows shorthand [key] syntax for setComponent:forProtocol:.
 @param key The protocol that the component conforms to.
 @see setComponent:forProtocol:
 */
- (void)setObject:(nullable id<MDLComponent>)obj forKeyedSubscript:(Protocol *)key;

/*!
 @property parent
 @abstract Parent object. Nil if no parent.
 @discussion Set to nil when you remove this from an object container inside the 
             parent object.
 */
@property (nonatomic, weak, nullable) MDLObject* parent;

/*!
 @property instance
 @abstract Instance object
 @discussion nil, unless this object refers to original data to be instanced. The
             original data object can be any MDLObject that does not have a parent.
             If an MDLAsset has been created from a data file, any original objects
             parsed from that file will be found in the originals property.
             A typical use of a original and instance might be to have one original
             chair MDLObject, and instance six chairs around a table. The
             transform of each chair would be found on the parent MDLObject, but
             the various items making up the chair would be found in the original
             object.
 */
@property (nonatomic, nullable, retain) MDLObject* instance;

/*!
 @property path
 @abstract a string representing a path to the object
 @discussion a path is of the form /path/to/object where the path is formed by
             concatenating the names of the objects up the parent chain.
             Requesting a path will force any unnamed objects to became uniquely
             named. Any characters outside of [A-Z][a-z][0-9][:-_.] will be
             forced to underscore.
 */
@property (nonatomic, readonly) NSString* path;

/*!
 @abstract Return the object at the specified path, or nil if none exists there
 */
- (MDLObject*)objectAtPath:(NSString*)path;


- (void)enumerateChildObjectsOfClass:(Class)objectClass
                                root:(MDLObject*)root
                          usingBlock:( void(^)(MDLObject* object, BOOL *stop))block
                         stopPointer:(BOOL *)stopPointer API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
 @property transform
 @abstract Short hand property for the MDLTransformComponent.
 @discussion The default value is nil
 
 @see MDLTransformComponent
 */
@property (nonatomic, nullable, retain) id<MDLTransformComponent> transform;


/*!
 @property children
 @abstract Short hand property for the MDLObjectContainerComponent.
 @discussion The default value is nil
 
 @see MDLObjectContainerComponent
 */
@property (nonatomic, retain) id<MDLObjectContainerComponent> children;

/*!
 @property hidden
 @abstract Visibility of the node
 @discussion default is NO
 */

@property (nonatomic) BOOL hidden;

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
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLObjectContainer : NSObject<MDLObjectContainerComponent>

@end

NS_ASSUME_NONNULL_END
