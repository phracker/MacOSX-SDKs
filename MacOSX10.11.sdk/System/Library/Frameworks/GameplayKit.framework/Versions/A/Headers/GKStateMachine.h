//
//  GKStateMachine.h
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKit.h>

NS_ASSUME_NONNULL_BEGIN

@class GKState;

/**
 * Models a finite state machine that has a single current state.
 */
GK_BASE_AVAILABILITY @interface GKStateMachine : NSObject

/**
 * The current state that the state machine is in.
 * Prior to the first called to enterState this is equal to nil.
 */
@property (nullable, nonatomic, readonly) GKState* currentState;

/**
 * Creates a state machine with an array of possible states and an initial state.
 *
 * @param states a list of possible states for this state machine.
 */
+ (instancetype)stateMachineWithStates:(NSArray<GKState *> *)states;
- (instancetype)initWithStates:(NSArray<GKState *> *)states NS_DESIGNATED_INITIALIZER;

/**
 * Updates the current state machine.
 *
 * @param sec the time, in seconds, since the last frame
 */
- (void)updateWithDeltaTime:(NSTimeInterval)sec;

/**
 * Gets the instance of the indicated state class from this state machine.
 * Returns nil if the state does not exist
 *
 * @param stateClass the class of the state to be retrieved
 */
- (nullable GKState*)stateForClass:(Class)stateClass NS_SWIFT_UNAVAILABLE("Exposed in Swift as stateForClass<StateType: GKState>(stateClass: StateType.Type) -> StateType?");

/**
 * Returns YES if the indicated class is a a valid next state or if currentState is nil
 *
 * @param stateClass the class of the state to be tested
 */
- (BOOL)canEnterState:(Class)stateClass;

/**
 * Calls canEnterState to check if we can enter the given state and then enters that state if so.
 * [GKState willExitWithNextState:] is called on the old current state.
 * [GKState didEnterWithPreviousState:] is called on the new state.
 *
 * @param stateClass the class of the state to switch to
 * @return YES if state was entered.  NO otherwise.
 */
- (BOOL)enterState:(Class)stateClass;

@end


NS_ASSUME_NONNULL_END

