//
//  INSticker.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INStickerType.h>

NS_ASSUME_NONNULL_BEGIN

/// An object that describes a sticker someone sends in a message.
API_AVAILABLE(ios(18.0), macos(15.0), watchos(11.0))
API_UNAVAILABLE(tvos)
@interface INSticker : NSObject <NSCopying, NSSecureCoding>

/// Creates an object that represents a sticker a person sends in a message.
///
/// - Parameters:
///   - type: The type of the sticker.
///   - emoji: The single emoji character that the sticker represents.
- (instancetype)initWithType:(INStickerType)type
                       emoji:(nullable NSString *)emoji NS_DESIGNATED_INITIALIZER;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INStickerType type;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *emoji;

@end

NS_ASSUME_NONNULL_END
