//  
//  GCDevicePhysicalInputStateDiff.h
//  GameController
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameController/GCPhysicalInputElement.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, GCDevicePhysicalInputElementChange) {
    /** Indicates that a change could not be determined.  This is typically
     *  because the input state queue filled up and older input state snapshots
     *  were dropped. */
    GCDevicePhysicalInputElementUnknownChange = -1,
    /** Indicates that no value of the element changed. */
    GCDevicePhysicalInputElementNoChange = 0,
    /** Indicates that a value of the element changed. */
    GCDevicePhysicalInputElementChanged = 1,
} API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0));


/**
 An object conforming to the \c GCDevicePhysicalInputStateDiff protocol
 contains the input state differences between the current and previous
 \c GCDevicePhysicalInputState objects returned from the \c -nextInputState
 method of \c GCDevicePhysicalInput.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCDevicePhysicalInputStateDiff <NSObject>

/**
 Check if a value of \a element changed, compared the previous input state.
 
 @param element
 The element to check.  This may be a pointer to either the "live" element
 from the device's physical input, or a pointer to an element from any input
 state "snapshot" of the device's physical input.
 */
- (GCDevicePhysicalInputElementChange)changeForElement:(id<GCPhysicalInputElement>)element;

/**
 Gets an enumerator that iterates over the elements that have changed, compared
 the previous input state.
 
 This method returns \c nil if the changed elements could not be determined -
 typically because the input state queue filled up and older input state
 snapshots were dropped.
 */
- (nullable NSEnumerator<id<GCPhysicalInputElement>> *)changedElements NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
