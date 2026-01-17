//
//  INMessageReaction.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INMessageReactionType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(18.0), macos(15.0), watchos(11.0))
API_UNAVAILABLE(tvos)
@interface INMessageReaction : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithReactionType:(INMessageReactionType)reactionType
                 reactionDescription:(nullable NSString *)reactionDescription
                               emoji:(nullable NSString *)emoji NS_DESIGNATED_INITIALIZER;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMessageReactionType reactionType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *reactionDescription;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *emoji;

@end

NS_ASSUME_NONNULL_END
