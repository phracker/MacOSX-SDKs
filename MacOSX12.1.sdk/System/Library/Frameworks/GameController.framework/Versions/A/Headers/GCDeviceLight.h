//
//  GCDeviceLight.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//


#import <GameController/GCExtern.h>
#import <GameController/GCColor.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A controller light is an abstract representation of the light-emitting capabilities of a GCController instance.
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCDeviceLight : NSObject

@property (nonatomic, copy) GCColor *color;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
