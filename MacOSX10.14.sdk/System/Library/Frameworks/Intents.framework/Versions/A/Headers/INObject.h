//
//  INObject.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INSpeakable.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0))
API_UNAVAILABLE(macosx)
@interface INObject : NSObject <INSpeakable, NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                     displayString:(NSString *)displayString
                 pronunciationHint:(nullable NSString *)pronunciationHint NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                     displayString:(NSString *)displayString;

@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *displayString;

@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *pronunciationHint;

@end

NS_ASSUME_NONNULL_END
