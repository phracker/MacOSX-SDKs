//
//  INRideOption.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INPriceRange;
@class INRidePartySizeOption;
@class INRideFareLineItem;
@class INImage;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.0))
API_UNAVAILABLE(macos, tvos)
@interface INRideOption : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithName:(NSString *)name
         estimatedPickupDate:(NSDate *)estimatedPickupDate NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)decoder NS_DESIGNATED_INITIALIZER;

@property (readwrite, copy, NS_NONATOMIC_IOSONLY) NSString *name; // a name for the ride option.

@property (readwrite, copy, NS_NONATOMIC_IOSONLY) NSDate *estimatedPickupDate; // used for providing an ETA to the user.

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INPriceRange *priceRange; // The indicative range of prices for this option.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *usesMeteredFare NS_REFINED_FOR_SWIFT; // If true, the fare will be metered by the driver, and price range information will be noted as unavailable.

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *disclaimerMessage; // A message that includes warnings or disclaimers shown to the user before they confirm the request. For example: "This ride may make multiple stops", or "This ride may be shared with other passengers".

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INRidePartySizeOption *> *availablePartySizeOptions; // Possible party size options for this ride. An empty array indicates selecting a party size is not required.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *availablePartySizeOptionsSelectionPrompt; // A message that is shown besides the available party sizes for the user.

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *specialPricing; // eg "47.5x Surge" or "Sale"
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *specialPricingBadgeImage; // a vendor-specific badge image that represents special pricing.

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INRideFareLineItem *> *fareLineItems; // A set of line items for fare pricing.
@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *userActivityForBookingInApplication; // If set, the user will be asked to open the ride booking application to book for this ride option. (When the user selects this option, the system will open your application and continue this NSUserActivity in it.) Leave this set to nil to allow an Apple client (e.g. Siri, Maps) to instead book the ride on your app's behalf, which is preferred where possible.

@end

#pragma mark - Deprecated

@interface INRideOption (Deprecated)

@property (nonatomic, copy, nullable) NSString *identifier; // a unique identifier for this ride.

@end

NS_ASSUME_NONNULL_END
