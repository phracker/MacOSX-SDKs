//
//  GKState.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKit.h>

NS_ASSUME_NONNULL_BEGIN

@class GKStateMachine;

/**
 * Represents a single state in a state machine.
 * By default, states allow transitions freely to and from the states in the machine.
 *
 * If a more restricted set of valid transitions are needed in the state machine, you may override isValidNextState: where applicable.
 *
 * @see GKStateMachine
 * @see isValidNextState:
 */
GK_BASE_AVAILABILITY @interface GKState : NSObject

/**
 * The state machine that this state is associated with.
 * This is nil if this state hasn't been added to a state machine yet.
 */
@property (nullable, nonatomic, readonly, weak) GKStateMachine *stateMachine;

/**
 * Creates a new state to be used in a state machine.
 *
 * @see GKStateMachine
 */
+ (instancetype)state;
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 * Returns YES if the given class is a valid next state to enter.
 *
 * By default GKState will return YES for any class that is subclass of GKState.
 * Override this in a subclass to enforce limited edge traversals in the state machine.
 *
 * @see GKStateMachine.canEnterState:
 * @see GKStateMachine.enterState:
 *
 * @param stateClass the class to be checked
 * @return YES if the class is kind of GKState and the state transition is valid, else NO.
 */
- (BOOL)isValidNextState:(Class)stateClass;

/**
 * Called by GKStateMachine when this state is entered.
 *
 * @param previousState the state that was exited to enter this state.  This is nil if this is the state machine's first entered state.
 * @see stateMachineWithStates:initialStateClass:
 */
- (void)didEnterWithPreviousState:(nullable GKState *)previousState;

/**
 * Called by GKStateMachine when it is updated
 *
 * @param deltaTime the time, in seconds, since the last update
 */
- (void)updateWithDeltaTime:(NSTimeInterval)seconds;

/**
 * Called by GKStateMachine when this state is exited
 *
 * @param nextState the state that is being entered next
 */
- (void)willExitWithNextState:(GKState *)nextState;


@end

NS_ASSUME_NONNULL_END
