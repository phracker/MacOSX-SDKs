//
//  GCColor.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Represents a color used by a GCDeviceLight.
 
 @see GCDeviceLight
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCColor : NSObject<NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithRed:(float)red green:(float)green blue:(float)blue;

@property (readonly) float red;
@property (readonly) float green;
@property (readonly) float blue;

@end

NS_ASSUME_NONNULL_END
