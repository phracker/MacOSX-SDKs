//
//  GKComponent.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

@class GKEntity;

/**
 A component is the data and logic for one part of an object in an entity-component system.
 Entities have many components but components are associated with only a single entity.
 
 Components across entities are best arranged in ComponentSystems, which are homogeneous
 collections of components that the game logic updates in a deterministic order.
 
 @see GKComponentSystem
 */
GK_BASE_AVAILABILITY @interface GKComponent : NSObject <NSCopying, NSSecureCoding>

/**
 * The entity that this component belongs to. Defaults to nil until the component is added to an entity.
 */
@property (nullable, nonatomic, readonly, weak) GKEntity *entity;

/**
 * Updates the component with the given delta time since the last update. Each component should
 * perform its time-based logic in this method.
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

/**
 * Override this to perform game logic when this component is added to an entity
 */
-(void)didAddToEntity;

/**
 * Override this to perform game logic before this entity is removed from it's entity
 */
-(void)willRemoveFromEntity;

@end


/**
 * A component system is a homogeneous collection of components that are intended to be called at the same time.
 * The system is homogeneous, meaning it only allows members of the same class into the system.
 */
GK_BASE_AVAILABILITY @interface GKComponentSystem<ComponentType : GKComponent *> : NSObject<NSFastEnumeration>

/**
 * The collection's component class. Any selector the component supports can be called on the system and it will be forwarded
 * to each of the components in the collection.
 */
@property (nonatomic, readonly) Class componentClass;

/**
 * The array of components currently in the system.
 */
@property (nonatomic, readonly, retain) NSArray<ComponentType> *components;

/**
 * Supports getting components via a [] subscript.
 */
- (ComponentType)objectAtIndexedSubscript:(NSUInteger)idx;

/**
 * Initializes a system for the given component class. The receiver can now only accept components of the given class.
 */
- (instancetype)initWithComponentClass:(Class)cls;

/**
 * Adds a component to the system. The component must be of the same class as the system's componentClass.
 * The component is added to the tail of the collection and will be processed after components that were added before it.
 *
 * @throws NSInvalidArgumentException if the component added is not a kind of the system's componentClass.
 */
- (void)addComponent:(ComponentType)component;

/**
 * Adds the supported component from the entity's component collection.
 * This is conceptually the same as the pseudo-code:
 *
 * for (GKComponent *component in entity.components)
 *    if (component.class == system.componentClass)
 *        [system addComponent:component]
 *
 * @see GKEntity.components
 */
- (void)addComponentWithEntity:(GKEntity *)entity;

/**
 * Removes the supported component from the entity's component collection
 * This is conceptually the same as the pseudo-code:
 *
 * for (GKComponent *component in entity.components)
 *    if (component.class == system.componentClass)
 *        [system removeComponent:component]
 */
- (void)removeComponentWithEntity:(GKEntity *)entity;

/**
 * Removes a component from the system
 *
 * Does nothing if the component is not in this system
 */
- (void)removeComponent:(ComponentType)component;


#pragma mark Component message forwarding

/**
 * Updates each component with the given delta time since the last update. Each component thus performs its time
 * based logic with a single message.
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

/**
 * Returns the class of the specified generic index
 */
- (nonnull Class)classForGenericArgumentAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
