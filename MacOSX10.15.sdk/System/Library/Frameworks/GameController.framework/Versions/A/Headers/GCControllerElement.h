//
//  GCControllerElement.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Every controller element knows which collection it belongs to and whether its input value is analog or digital.
 */
API_AVAILABLE(macos(10.9), ios(7.0), tvos(7.0))
@interface GCControllerElement : NSObject

/**
 Each element can be part of a wider collection of inputs that map to a single logical element. A directional pad (dpad)
 is a logical collection of two axis inputs and thus each axis belongs to the same collection element - the dpad.
 */
@property (nonatomic, weak, readonly, nullable) GCControllerElement *collection;

/**
 Check if the element can support more than just digital values, such as decimal ranges between 0 and 1.
 Defaults to YES for most elements.
 */
@property (nonatomic, readonly, getter = isAnalog) BOOL analog;

@end

NS_ASSUME_NONNULL_END
