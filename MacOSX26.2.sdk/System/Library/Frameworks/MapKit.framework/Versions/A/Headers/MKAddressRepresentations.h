//
//  MKAddressRepresentations.h
//  MapKit
//
//  Copyright © 2024 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MKAddressRepresentationsContextStyle) {
    // Includes "United States" only if device region is not the United States
    MKAddressRepresentationsContextStyleAutomatic,

    // Omits "United States"
    MKAddressRepresentationsContextStyleShort,

    // Includes "United States" even if device region is the United States
    MKAddressRepresentationsContextStyleFull
} NS_SWIFT_NAME(MKAddressRepresentations.ContextStyle) API_AVAILABLE(ios(26.0), visionos(26.0), macos(26.0), tvos(26.0), watchos(26.0));


API_AVAILABLE(ios(26.0), visionos(26.0), macos(26.0), tvos(26.0), watchos(26.0))
@interface MKAddressRepresentations : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// 1 Apple Park Way
// Cupertino, CA 95014
// United States
- (nullable NSString *)fullAddressIncludingRegion:(BOOL)includingRegion singleLine:(BOOL)singleLine NS_SWIFT_NAME(fullAddress(includingRegion:singleLine:));

// Cupertino
@property (nonatomic, readonly, copy, nullable) NSString *cityName;

// Cupertino, CA
@property (nonatomic, readonly, copy, nullable) NSString *cityWithContext;

// Cupertino, CA, United States
- (nullable NSString *)cityWithContextUsingStyle:(MKAddressRepresentationsContextStyle)style NS_SWIFT_NAME(cityWithContext(_:));

// United States
@property (nonatomic, readonly, copy, nullable) NSString *regionName;

// US
@property (nonatomic, readonly, copy, nullable) NSString *regionCode NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
