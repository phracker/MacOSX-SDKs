//  
//  GCDevicePhysicalInput.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameController/GCDevicePhysicalInputState.h>
#import <GameController/GCDevicePhysicalInputStateDiff.h>

@protocol GCDevice;

NS_ASSUME_NONNULL_BEGIN

/**
 An objecting conforming to \c GCDevicePhysicalInput provides properties and
 methods for accessing common physical elements - buttons, thumbsticks, dpads,
 etc - of a device.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCDevicePhysicalInput <GCDevicePhysicalInputState>

/**
 The device that this profile is mapping input from.
 */
@property (weak, readonly) id<GCDevice> device;

/**
 The dispatch queue that element value change handlers and other callbacks are
 submitted on.
 
 The default queue is the \c handlerQueue of the associated \c device.  Set
 this property if your application wants to receive input callbacks on a
 different queue.  You should set this property before configuring other
 callbacks.
 */
@property (atomic, strong, nullable) dispatch_queue_t queue API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

#pragma mark Immediate Input

/**
 Set this block to be notified when a value on a element changed.  If multiple
 elements change this block will be called for each element that changed.
 
 The block is called on the \c queue configured for the physical input.
 
 @param element
 The element that has been modified.
 */
@property (atomic, copy, nullable) void (^elementValueDidChangeHandler)(__kindof id<GCDevicePhysicalInput> physicalInput, __kindof id<GCPhysicalInputElement> element);

/**
 Polls the current state vector of the physical input and saves it to a new
 instance.
 
 If your application is heavily multithreaded this may also be useful to
 guarantee atomicity of input handling as a snapshot will not change based on
 further device input once it is taken.
 
 @return An input state with the duplicated state vector of the current input.
 */
- (__kindof id<GCDevicePhysicalInputState>)capture;

#pragma mark Buffered Input

/**
 Set this block to be notified when a new input state is available.  Your
 handler should repeatedly call \c -nextInputState until it returns \c nil to
 drain the pending input states from the queue.
 
    physicalInput.inputStateQueueDepth = 20;
    physicalInput.inputStateAvailableHandler = ^(__kindof id<GCDevicePhysicalInput> physicalInput) {
        id<GCDevicePhysicalInputState, GCDevicePhysicalInputStateDiff> nextInputState;
        while ((nextInputState = [physicalInput nextInputState])) {
 
            // You can grab the individual states of all elements that your app
            // is interested in.
            id<GCButtonElement> buttonA = nextInputState.buttons[GCInputButtonA];
            BOOL buttonAPressed = buttonA.pressedInput.pressed;
            if (buttonAPressed) {
                // Handle button A pressed
            }
 
            // Your code can first query whether an element's input value changed
            // from the prior input state.
            GCDevicePhysicalInputElementChange buttonAChange = [nextInputState changeForElement:buttonA];
            if (buttonAChange == GCDevicePhysicalInputElementChanged) {
                // Handle button A input changed
            }
 
            // Or, your code can request an enumerator of elements with input
            // values that changed from the prior input state
            for (id<GCPhysicalInputElement> changedElement in nextInputState.changedElements) {
 
            }
        }
    };
 */
@property (atomic, copy, nullable) void (^inputStateAvailableHandler)(__kindof id<GCDevicePhysicalInput> physicalInput);

/**
 The maximum number of input states to buffer.  If your application does not
 drain the pending input states in the queue before this limit is reached, older
 input states will be discarded - resulting in your application "missing" input
 state changes.
 
 The default value is \c one (no buffering).  Smaller values are ignored.  A
 value of \c 20 should be more than enough to ensure no input state changes
 are missed.
 */
@property (atomic, readwrite) NSInteger inputStateQueueDepth;

/**
 Pop the oldest pending input state from the queue.  This method returns \c nil
 when there are no more input states pending.
 */
- (nullable __kindof id<GCDevicePhysicalInputState, GCDevicePhysicalInputStateDiff>)nextInputState;



@end

NS_ASSUME_NONNULL_END
