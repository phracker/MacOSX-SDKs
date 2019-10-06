//
//  INMediaDestination.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INMediaDestinationType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macosx)
@interface INMediaDestination : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)libraryDestination;
+ (instancetype)playlistDestinationWithName:(NSString *)playlistName;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMediaDestinationType mediaDestinationType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *playlistName;

@end

NS_ASSUME_NONNULL_END
