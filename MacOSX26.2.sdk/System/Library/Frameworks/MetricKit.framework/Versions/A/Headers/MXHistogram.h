//
//  MXHistogram.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXHistogramBucket
 @abstract      A class that represents a bucket within an MXHistogram
 @discussion    Histogram buckets are sorted in ascending order.
 @discussion    Histogram bucket start and end values are exclusive.
 */
API_AVAILABLE(ios(13.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXHistogramBucket<UnitType: NSUnit *> : NSObject <NSSecureCoding>

/*!
 @property      bucketStart
 @abstract      An NSMeasurement representing the start of a histogram bucket.
 */
@property (readonly, strong, nonnull) NSMeasurement<UnitType> *bucketStart;

/*!
 @property      bucketEnd
 @abstract      An NSMeasurement representing the end of a histogram bucket.
 */
@property (readonly, strong, nonnull) NSMeasurement<UnitType> *bucketEnd;

/*!
 @property      bucketCount
 @abstract      An NSUInteger representing the number of samples in this histogram bucket.
 */
@property (readonly) NSUInteger bucketCount;

@end

/*!
 @class         MXHistogram
 @abstract      A class representing bucketized histogram data.
 */
API_AVAILABLE(ios(13.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXHistogram<UnitType: NSUnit *>  : NSObject <NSSecureCoding>

/*!
 @property      totalBucketCount
 @abstract      The number of buckets contained within this histogram.
 @discussion    This value can never be negative.
 */
@property (readonly) NSUInteger totalBucketCount;

/*!
 @property      bucketEnumerator
 @abstract      An NSEnumerator that can be used to enumerate the buckets of this histogram.
 */
@property (readonly, strong, nonnull) NSEnumerator<MXHistogramBucket<UnitType> *> *bucketEnumerator;

@end

NS_ASSUME_NONNULL_END
