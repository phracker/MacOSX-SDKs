//
//  MXNetworkTransferMetric.h
//  MetricKit
//
//  Copyright (c) 2018 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <MetricKit/MXUnit.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         MXNetworkTransferMetric
 @abstract      An MXMetric subclass that encapsulates network transfer metrics
 */
API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXNetworkTransferMetric : MXMetric

/*!
 @property      cumulativeWifiUpload
 @abstract      Cumulative amount of data uploaded over WiFi.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *cumulativeWifiUpload;

/*!
 @property      cumulativeWifiDownload
 @abstract      Cumulative amount of data downloaded over WiFi.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *cumulativeWifiDownload;

/*!
 @property      cumulativeCellularUpload
 @abstract      Cumulative amount of data uploaded over cellular networks.
 @discussion    This data is radio access technology agnostic.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *cumulativeCellularUpload;

/*!
 @property      cumulativeCellularDownload
 @abstract      Cumulative amount of data downloaded over cellular networks.
 @discussion    This data is radio access technology agnostic.
 @discussion    Dimensioned as NSUnitInformationStorage.
 */
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *cumulativeCellularDownload;

@end

NS_ASSUME_NONNULL_END
