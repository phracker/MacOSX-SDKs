//
//  SHRange.h
//  ShazamKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ShazamKit/SHDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A half-open interval from a lower bound up to, but not including, an upper bound.
SH_EXPORT NS_SWIFT_SENDABLE API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) NS_REFINED_FOR_SWIFT
@interface SHRange : NSObject <NSSecureCoding, NSCopying>

/// The lowerBound of this time range
@property (NS_NONATOMIC_IOSONLY, assign, readonly) double lowerBound;

/// The range's upper bound.
@property (NS_NONATOMIC_IOSONLY, assign, readonly) double upperBound;

/// Creates a range with the bounds you specify.
///
/// - Parameters:
///   - lowerBound: The lower bound of the range.
///   - upperBound: The upper bound of the range.
+ (instancetype)rangeWithLowerBound:(double)lowerBound upperBound:(double)upperBound;

/// Creates a range with the bounds you specify.
///
/// - Parameters:
///   - lowerBound: The lower bound of the range.
///   - upperBound: The upper bound of the range.
- (instancetype)initWithLowerBound:(double)lowerBound upperBound:(double)upperBound NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
