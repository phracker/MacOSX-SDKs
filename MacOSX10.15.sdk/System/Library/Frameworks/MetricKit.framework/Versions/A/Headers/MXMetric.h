//
//  MXMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXMetric
 @abstract      An abstract class that describes a specific metric vended by MetricKit.
 @discussion    All supported metrics are subclasses of MXMetric.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXMetric : NSObject <NSSecureCoding>

/*!
 @method        JSONRepresentation
 @abstract      Convenience method to return a JSON representation of this metric.
 @result        An NSData object containing the JSON representation
 */
- (NSData *)JSONRepresentation;

/*!
 @method        DictionaryRepresentation
 @abstract      Convenience method to return a NSDictionary representation of this metric.
 @result        An NSDictionary object containing the dictionary representation
 */
- (NSDictionary *)DictionaryRepresentation;

@end

NS_ASSUME_NONNULL_END
