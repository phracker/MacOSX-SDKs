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
NS_CLASS_AVAILABLE(10_9, 7_0)
@interface GCControllerElement : NSObject

/**
 Each element can be part of a wider collection of inputs that map to a single logical element. A directional pad (dpad)
 is a logical collection of two axis inputs and thus each axis belongs to the same collection element - the dpad.
 */
#if !__has_feature(objc_arc)
@property (nonatomic, assign, readonly) GCControllerElement *collection;
#else
@property (nonatomic, weak, readonly, nullable) GCControllerElement *collection;
#endif

/**
 Check if the element can support more than just digital values, such as decimal ranges between 0 and 1.
 Defaults to YES for most elements.
 */
@property (nonatomic, readonly, getter = isAnalog) BOOL analog;

@end

NS_ASSUME_NONNULL_END
