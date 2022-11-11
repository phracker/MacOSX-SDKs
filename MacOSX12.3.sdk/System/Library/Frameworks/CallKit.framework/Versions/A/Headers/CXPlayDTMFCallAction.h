//
//  CXPlayDTMFCallAction.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CallKit/CXCallAction.h>

typedef NS_ENUM(NSInteger, CXPlayDTMFCallActionType) {
    CXPlayDTMFCallActionTypeSingleTone = 1, // The user tapped a digit on the in-call keypad
    CXPlayDTMFCallActionTypeSoftPause = 2, // The user included digits after a soft pause in their dial string
    CXPlayDTMFCallActionTypeHardPause = 3, // The user included digits after a hard pause in their dial string
} API_AVAILABLE(ios(10.0), macCatalyst(13.0))  API_UNAVAILABLE(macos, tvos, watchos);

NS_ASSUME_NONNULL_BEGIN

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0))  API_UNAVAILABLE(macos, watchos, tvos)
@interface CXPlayDTMFCallAction : CXCallAction

- (instancetype)initWithCallUUID:(NSUUID *)callUUID digits:(NSString *)digits type:(CXPlayDTMFCallActionType)type NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCallUUID:(NSUUID *)callUUID NS_UNAVAILABLE;

// The string representation of the digits that should be played as DTMF tones
@property (nonatomic, copy) NSString *digits;

// Whether or not the string of digits represents tones following a hard or soft pause
@property (nonatomic) CXPlayDTMFCallActionType type;

@end

NS_ASSUME_NONNULL_END
