//
//  INImage.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NSData;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), macos(11.0), watchos(3.2), tvos(14.0))
@interface INImage : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)imageNamed:(NSString *)name;
+ (instancetype)systemImageNamed:(NSString *)systemImageName API_AVAILABLE(ios(14.0), watchos(7.0), tvos(14.0)) API_UNAVAILABLE(macos);
+ (instancetype)imageWithImageData:(NSData *)imageData;
+ (nullable instancetype)imageWithURL:(NSURL *)URL;
+ (nullable instancetype)imageWithURL:(NSURL *)URL width:(double)width height:(double)height API_AVAILABLE(ios(11.0), watchos(4.0));

@end

NS_ASSUME_NONNULL_END
