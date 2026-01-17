//
//  SHCatalog.h
//  ShazamKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An abstract base class for storing reference signatures and their associated metadata.
///
/// This is the base class of your custom catalog.
SH_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface SHCatalog : NSObject

/// The minimum duration of a query signature that you use to match reference signatures in the catalog.
@property (NS_NONATOMIC_IOSONLY, assign, readonly) NSTimeInterval minimumQuerySignatureDuration;

/// The maximum duration of a query signature that you use to match reference signatures in the catalog.
@property (NS_NONATOMIC_IOSONLY, assign, readonly) NSTimeInterval maximumQuerySignatureDuration;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
