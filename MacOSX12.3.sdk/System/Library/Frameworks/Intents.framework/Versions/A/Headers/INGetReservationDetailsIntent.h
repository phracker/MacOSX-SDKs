//
//  INGetReservationDetailsIntent.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INGetReservationDetailsIntent : INIntent

- (instancetype)initWithReservationContainerReference:(nullable INSpeakableString *)reservationContainerReference
                            reservationItemReferences:(nullable NSArray<INSpeakableString *> *)reservationItemReferences NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *reservationContainerReference;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INSpeakableString *> *reservationItemReferences;

@end

NS_ASSUME_NONNULL_END
