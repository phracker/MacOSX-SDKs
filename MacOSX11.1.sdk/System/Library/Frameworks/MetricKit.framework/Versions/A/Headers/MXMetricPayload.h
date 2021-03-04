//
//  MXMetricPayload.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXCPUMetric.h>
#import <MetricKit/MXGPUMetric.h>
#import <MetricKit/MXCellularConditionMetric.h>
#import <MetricKit/MXMetaData.h>
#import <MetricKit/MXAppRunTimeMetric.h>
#import <MetricKit/MXLocationActivityMetric.h>
#import <MetricKit/MXNetworkTransferMetric.h>
#import <MetricKit/MXAppLaunchMetric.h>
#import <MetricKit/MXAppResponsivenessMetric.h>
#import <MetricKit/MXDiskIOMetric.h>
#import <MetricKit/MXMemoryMetric.h>
#import <MetricKit/MXDisplayMetric.h>
#import <MetricKit/MXAnimationMetric.h>
#import <MetricKit/MXAppExitMetric.h>
#import <MetricKit/MXSignpostMetric.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXMetricPayload
 @abstract      A wrapper class which contains a metric payload and associated properties of that payload.
 @discussion    MXMetricPayload encapsulates currently supported metric types that can be vended by MetricKit. MXMetric subclasses on MXMetricPayload are nullable. If an MXMetric subclass is nil, it indicates that the data is not available for this payload.
 @discussion    MXMetricPayload exposes a convenience function, JSONRepresentation, to convert the contents of the payload to a human readable JSON. This should be used in conjunction with other APIs that accept NSData.
 @discussion    An MXMetricPayload contains data that covers a 24 hour period of application usage. The properties timeStampBegin and timeStampEnd should be used to determine which time range the payload covers.
 @discussion    It is possible for an MXMetricPayload to cover regions of time where an application was updated, and thus had multiple different app version strings. The property latestApplicationVersion will always reflect the latest appVersion at the time the metric payload was created. Use includesMultipleApplicationVersions to determine if an application changed versions during the time range the payload covers.
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXMetricPayload : NSObject <NSSecureCoding>

/*!
 @property      latestApplicationVersion
 @abstract      An NSString representation of the application version from which this payload was generated.
 @discussion    If the application version was changed during the aggregation of this data, this value will reflect the latest application version at the time of retrieval.
 */
@property (readonly, strong, nonnull) NSString *latestApplicationVersion;

/*!
 @property      includesMultipleApplicationVersions
 @abstract      A bool which indicates whether or not this payload contains data from multiple application versions.
 @discussion    A value of YES indicates that this payload's data reflects multiple application versions.
 @discussion    A value of NO indicates that this payload only reflects data from the application version specified by latestApplicationVersion.
 */

@property (readonly) BOOL includesMultipleApplicationVersions;

/*!
 @property      timeStampBegin
 @abstract      An NSDate object that indicates the time which the payload was generated.
 */
@property (readonly, strong, nonnull) NSDate *timeStampBegin;

/*!
 @property      timeStampEnd
 @abstract      An NSDate object that indicates the time which the payload was generated.
 */
@property (readonly, strong, nonnull) NSDate *timeStampEnd;

/*!
 @property      cpuMetrics
 @abstract      An object containing CPU metrics for this application.
 */
@property (readonly, strong, nullable) MXCPUMetric *cpuMetrics;

/*!
 @property      gpuMetrics
 @abstract      An object containing GPU metrics for this application.
 */
@property (readonly, strong, nullable) MXGPUMetric *gpuMetrics;

/*!
 @property      cellularConditionMetrics
 @abstract      An object containing a cellular condition metrics for this application.
 */
@property (readonly, strong, nullable) MXCellularConditionMetric *cellularConditionMetrics;

/*!
 @property      applicationTimeMetrics
 @abstract      An object containing running mode metrics for this application.
 */
@property (readonly, strong, nullable) MXAppRunTimeMetric *applicationTimeMetrics;

/*!
 @property      locationActivityMetrics
 @abstract      An object containing location activity metrics for this application.
 */
@property (readonly, strong, nullable) MXLocationActivityMetric *locationActivityMetrics;

/*!
 @property      networkTransferMetrics
 @abstract      An object containing network transfer metrics for this application.
 */
@property (readonly, strong, nullable) MXNetworkTransferMetric *networkTransferMetrics;

/*!
 @property      applicationLaunchMetrics
 @abstract      An object containing launch metrics for this application.
 */
@property (readonly, strong, nullable) MXAppLaunchMetric *applicationLaunchMetrics;

/*!
 @property      applicationResponsivenessMetrics
 @abstract      An object containing hang metrics for this application.
 */
@property (readonly, strong, nullable) MXAppResponsivenessMetric *applicationResponsivenessMetrics;

/*!
 @property      diskIOMetrics
 @abstract      An object containing disk IO metrics for this application.
 */
@property (readonly, strong, nullable) MXDiskIOMetric *diskIOMetrics;

/*!
 @property      memoryMetrics
 @abstract      An object containing memory metrics for this application.
 */
@property (readonly, strong, nullable) MXMemoryMetric *memoryMetrics;

/*!
 @property      displayMetrics
 @abstract      An object containing display metrics for this application.
 */
@property (readonly, strong, nullable) MXDisplayMetric *displayMetrics;

/*!
 @property      animationMetrics
 @abstract      An object containing animation metrics for this application.
 */
@property (readonly, strong, nullable) MXAnimationMetric *animationMetrics API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
 @property      applicationExitMetrics
 @abstract      An object containing exit metrics for this application.
 */
@property (readonly, strong, nullable) MXAppExitMetric *applicationExitMetrics API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
 @property      signpostMetrics
 @abstract      An array containing signpost metrics for this application.
 */
@property (readonly, strong, nullable) NSArray<MXSignpostMetric *> *signpostMetrics;

/*!
 @property      metaData
 @abstract      An object containing extra metadata for this payload.
 */
@property (readonly, strong, nullable) MXMetaData *metaData;

/*!
 @method        JSONRepresentation
 @abstract      Convenience method to return a JSON representation of this payload.
 @result        An NSData object containing the JSON representation
 */
- (NSData *)JSONRepresentation;

/*!
 @method        DictionaryRepresentation
 @abstract      Convenience method to return a NSDictionary representation of this payload.
 @result        An NSDictionary object containing the dictionary representation
 */
- (NSDictionary *)DictionaryRepresentation API_DEPRECATED_WITH_REPLACEMENT("Use dictionaryRepresentation", ios(13.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
@method        dictionaryRepresentation
@abstract      Convenience method to return a NSDictionary representation of this payload.
@result        An NSDictionary object containing the dictionary representation
*/
- (NSDictionary *)dictionaryRepresentation API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos) NS_REFINED_FOR_SWIFT;
@end

NS_ASSUME_NONNULL_END
