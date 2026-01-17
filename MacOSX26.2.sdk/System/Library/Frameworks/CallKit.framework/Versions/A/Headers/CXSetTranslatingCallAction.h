//
//  CXSetTranslatingCallAction.h
//  CallKit
//
//  Created by David Evans on 2/27/25.
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <CallKit/CXBase.h>
#import <CallKit/CXCallAction.h>

NS_SWIFT_SENDABLE
typedef NS_ENUM(NSInteger, CXTranslationEngine) {
    CXTranslationEngineDefault,
    CXTranslationEngineCustom,
};

NS_ASSUME_NONNULL_BEGIN
/**
  CXSetTranslatingCallAction is supported after call is connected.
  System offered translation is only supported when using Apple's VoiceProcessor for call IO
 */
NS_SWIFT_SENDABLE
CX_EXTERN
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, macos, tvos, watchos, visionos)
@interface CXSetTranslatingCallAction : CXCallAction <NSSecureCoding>

@property (nonatomic, readonly) BOOL isTranslating;
@property (nonatomic, readonly, strong) NSString * localLanguage;
@property (nonatomic, readonly, strong) NSString * remoteLanguage;

- (instancetype)initWithCallUUID:(NSUUID *)uuid isTranslating:(BOOL)isTranslating localLanguage:(NSString *)localLanguage remoteLanguage:(NSString *)remoteLanguage NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_UNAVAILABLE;

- (void)fulfillUsingTranslationEngine:(CXTranslationEngine)translationEngine;

@end

NS_ASSUME_NONNULL_END
