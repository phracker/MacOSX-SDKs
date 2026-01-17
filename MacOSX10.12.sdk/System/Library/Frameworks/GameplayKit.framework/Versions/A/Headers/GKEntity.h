//
//  GKEntity.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

@class GKComponent;

/**
 * An entity is the general purpose object in an entity-component system.
 * Entites have many components but components are associated with only a single entity.
 * 
 * Note: GKEntity supports NSCopying and NSCoding, but your custom GKComponent's must also support NSCopying and NSCoding
 *
 * @see GKComponent
 * @see GKComponentSystem
 */
GK_BASE_AVAILABILITY @interface GKEntity : NSObject <NSCopying, NSCoding>

/**
 * Creates a new entity ready to have components added to it.
 */
+ (instancetype)entity;

/**
 * Creates a new entity ready to have components added to it.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 * General update loop for this entity, which also updates all components in this entity that are not currently
 * in a dedicated component system.
 *
 * Per-entity component updates is a simpler and less flexible option to using per-component updates,
 * however both can not be allowed to occur at the same time for a component. Thus components that are
 * added to dedicated component systems will not be updated here as they have opted for the more powerful
 * feature of per-component systems. Update those components via their system instead.
 *
 * @see GKComponentSystem
 * @param seconds elapsed time, in seconds, since last frame
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

/**
 * Access the current set of components as an array.
 * Note: this is not the internal array of components, but rather a newly created array of the current component mapping.
 */
@property (nonatomic, readonly, retain) NSArray<GKComponent *> *components;

/**
 * Adds a component to this entity.  If a component of the same class already exists it is overwritten with the new component.
 * @param component the component to be added
 * @see GKComponent
 */
- (void)addComponent:(GKComponent *)component;

/**
 * Removes the component of the indicates class from this entity
 * @param componentClass the class of the component you want to remove
 */
#if (defined(SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH) && SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH >= 1)
- (void)removeComponentForClass:(Class)componentClass NS_REFINED_FOR_SWIFT;
#else
- (void)removeComponentForClass:(Class)componentClass;
#endif

/**
 * Gets the component of the indicated class.  Returns nil if entity does not have this component
 * @param componentClass the class of the component you want to get
 */
#if (defined(SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH) && SWIFT_SDK_OVERLAY_GAMEPLAYKIT_EPOCH >= 1)
- (nullable GKComponent *)componentForClass:(Class)componentClass NS_REFINED_FOR_SWIFT;
#else
 - (nullable GKComponent *)componentForClass:(Class)componentClass NS_SWIFT_UNAVAILABLE("Exposed in Swift as componentForClass<ComponentType: GKComponent>(componentClass: ComponentType.Type) -> ComponentType?");
#endif

@end

NS_ASSUME_NONNULL_END

