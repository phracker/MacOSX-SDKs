//
//  INRequestRideIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INRequestRideIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INRequestRideIntent (Deprecated)

- (instancetype)initWithPickupLocation:(nullable CLPlacemark *)pickupLocation
                       dropOffLocation:(nullable CLPlacemark *)dropOffLocation
                        rideOptionName:(nullable INSpeakableString *)rideOptionName
                             partySize:(nullable NSNumber *)partySize
                         paymentMethod:(nullable INPaymentMethod *)paymentMethod NS_REFINED_FOR_SWIFT API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.3));

@end

NS_ASSUME_NONNULL_END
