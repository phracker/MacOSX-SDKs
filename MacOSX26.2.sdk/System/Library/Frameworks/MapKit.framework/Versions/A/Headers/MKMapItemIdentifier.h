//
//  MKMapItemIdentifier.h
//  MapKit
//
//  Copyright © 2023 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0))
NS_SWIFT_NAME(MKMapItem.Identifier)
@interface MKMapItemIdentifier : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithIdentifierString:(NSString *)string NS_SWIFT_NAME(init(rawValue:));

@property (nonatomic, readonly) NSString *identifierString NS_SWIFT_NAME(rawValue);

@end

NS_ASSUME_NONNULL_END
