//
//  INImage.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class NSData;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INImage : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)imageNamed:(NSString *)name;
+ (instancetype)imageWithImageData:(NSData *)imageData;
+ (nullable instancetype)imageWithURL:(NSURL *)URL;
+ (nullable instancetype)imageWithURL:(NSURL *)URL width:(double)width height:(double)height API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

@end

NS_ASSUME_NONNULL_END
