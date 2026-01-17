//
//  MXDiskSpaceUsageMetric.h
//  MetricKit
//
//  Copyright (c) 2025 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXMetric.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@class         MXDiskSpaceUsageMetric
@abstract      An MXMetric subclass that encapsulates app disk space usage Metrics.
@discussion    Disk space is a shared resource on-device, and overusage of available disk space can negatively impact the customer experience.
@discussion    This Metric subclass contains properties that describe disk space usage in various locations in the apps container. Some properties also describe the number of files in common locations, and the types of files.
@discussion    The data contained in this Metric is computed as a daily snapshot, and should be used as a guide to optimize app disk space usage.
*/
API_AVAILABLE(ios(26.0), macos(26.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXDiskSpaceUsageMetric : MXMetric

/*!
@property      totalBinaryFileSize
@abstract      Total fixed size used by the app.
@discussion    Dimensioned as NSUnitInformationStorage, base unit is bytes.
*/
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *totalBinaryFileSize;

/*!
@property      totalBinaryFileCount
@abstract      Total count of fixed files owned by the app.
*/
@property (readonly) NSInteger totalBinaryFileCount;

/*!
@property      totalDataFileSize
@abstract      Total data file size used by the app.
@discussion    Dimensioned as NSUnitInformationStorage, base unit is bytes.
*/
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *totalDataFileSize;

/*!
@property      totalDataFileCount
@abstract      Total count of data files owned by the app.
*/
@property (readonly) NSInteger totalDataFileCount;

/*!
@property      totalCacheFolderSize
@abstract      Total file size contained within the apps cache folder.
@discussion    Dimensioned as NSUnitInformationStorage, base unit is bytes.
*/
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *totalCacheFolderSize;

/*!
@property      totalCloneSize
@abstract      Total clone size used by the app.
@discussion    Dimensioned as NSUnitInformationStorage, base unit is bytes.
*/
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *totalCloneSize;

/*!
@property      totalDiskSpaceUsedSize
@abstract      Total disk space used by the app.
@discussion    Dimensioned as NSUnitInformationStorage, base unit is bytes.
*/
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *totalDiskSpaceUsedSize;

/*!
@property      totalDiskSpaceCapacity
@abstract      Total disk space capacity of the device
@discussion    Dimensioned as NSUnitInformationStorage, base unit is bytes.
*/
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *totalDiskSpaceCapacity;

@end

NS_ASSUME_NONNULL_END
