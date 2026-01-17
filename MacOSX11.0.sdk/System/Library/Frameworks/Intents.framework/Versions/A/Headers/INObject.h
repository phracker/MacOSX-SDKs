//
//  INObject.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INSpeakable.h>
#import <Intents/INSpeakableString.h>
#import <Intents/INImage.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), macos(11.0), watchos(5.0))
API_UNAVAILABLE(tvos)
@interface INObject : NSObject <INSpeakable, NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                     displayString:(NSString *)displayString
                 pronunciationHint:(nullable NSString *)pronunciationHint NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                     displayString:(NSString *)displayString;

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                     displayString:(NSString *)displayString
                    subtitleString:(nullable NSString *)subtitleString
                      displayImage:(nullable INImage *)displayImage NS_SWIFT_NAME(init(identifier:display:subtitle:image:)) API_AVAILABLE(ios(14.0), watchos(7.0));

- (instancetype)initWithIdentifier:(nullable NSString *)identifier
                     displayString:(NSString *)displayString
                 pronunciationHint:(nullable NSString *)pronunciationHint
                    subtitleString:(nullable NSString *)subtitleString
                      displayImage:(nullable INImage *)displayImage NS_SWIFT_NAME(init(identifier:display:pronunciationHint:subtitle:image:)) API_AVAILABLE(ios(14.0), watchos(7.0));

@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *displayString;

@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *pronunciationHint;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *subtitleString API_AVAILABLE(ios(14.0), watchos(7.0));

@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) INImage *displayImage API_AVAILABLE(ios(14.0), watchos(7.0));

@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) NSArray<INSpeakableString *> *alternativeSpeakableMatches API_AVAILABLE(ios(13.0), watchos(6.0));

@end

NS_ASSUME_NONNULL_END
