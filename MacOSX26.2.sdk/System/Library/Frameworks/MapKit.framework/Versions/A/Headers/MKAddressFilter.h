//
//  MKAddressFilter.h
//  MapKit
//
//  Copyright © 2024 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, MKAddressFilterOption) {
    MKAddressFilterOptionCountry = 1 << 0,
    MKAddressFilterOptionAdministrativeArea = 1 << 1,
    MKAddressFilterOptionSubAdministrativeArea = 1 << 2,
    MKAddressFilterOptionLocality = 1 << 3,
    MKAddressFilterOptionSubLocality = 1 << 4,
    MKAddressFilterOptionPostalCode = 1 << 5
} NS_SWIFT_NAME(MKAddressFilter.Options) API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0));


API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0))
@interface MKAddressFilter : NSObject <NSSecureCoding, NSCopying>

@property (nonatomic, class, readonly) MKAddressFilter *filterIncludingAll NS_SWIFT_NAME(includingAll);
@property (nonatomic, class, readonly) MKAddressFilter *filterExcludingAll NS_SWIFT_NAME(excludingAll);

- (instancetype)initIncludingOptions:(MKAddressFilterOption)options NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(including:));
- (instancetype)initExcludingOptions:(MKAddressFilterOption)options NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(excluding:));

- (BOOL)includesOptions:(MKAddressFilterOption)options NS_SWIFT_NAME(includes(_:));
- (BOOL)excludesOptions:(MKAddressFilterOption)options NS_SWIFT_NAME(excludes(_:));

@end

NS_ASSUME_NONNULL_END
