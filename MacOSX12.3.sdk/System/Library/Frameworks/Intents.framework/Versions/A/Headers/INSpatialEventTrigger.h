//
//  INSpatialEventTrigger.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INSpatialEvent.h>

@class CLPlacemark;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INSpatialEventTrigger : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithPlacemark:(CLPlacemark *)placemark
                            event:(INSpatialEvent)event NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLPlacemark *placemark;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INSpatialEvent event;

@end

NS_ASSUME_NONNULL_END
