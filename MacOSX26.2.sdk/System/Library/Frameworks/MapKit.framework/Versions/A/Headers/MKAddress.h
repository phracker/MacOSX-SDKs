//
//  MKAddress.h
//  MapKit
//
//  Copyright © 2024 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(26.0), visionos(26.0), macos(26.0), tvos(26.0), watchos(26.0))
@interface MKAddress : NSObject

- (nullable instancetype)initWithFullAddress:(NSString *)fullAddress shortAddress:(nullable NSString *)shortAddress;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly, copy) NSString *fullAddress;
@property (nonatomic, readonly, copy, nullable) NSString *shortAddress;

@end

NS_ASSUME_NONNULL_END
