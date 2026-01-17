#if !__has_include(<AVFCore/AVAssetSegmentReport.h>)
/*
	File:  AVAssetSegmentReport.h

	Framework:  AVFoundation

	Copyright 2020 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMBase.h>
#import <CoreMedia/CMTime.h>

@class AVAssetSegmentTrackReport;
@class AVAssetSegmentReportSampleInformation;

NS_ASSUME_NONNULL_BEGIN

/*!
	@enum		AVAssetSegmentType
	@abstract	Indicates the type of segment.

	@constant	AVAssetSegmentTypeInitialization
				Indicates that the segment is a initialization segment.
	@constant	AVAssetSegmentTypeSeparable
				Indicates that the segment is a separable segment.
*/
typedef NS_ENUM(NSInteger, AVAssetSegmentType) {
	AVAssetSegmentTypeInitialization	= 1,
	AVAssetSegmentTypeSeparable			= 2
} API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);


/*!
	@class		AVAssetSegmentReport
	@abstract	This class provides information on a segment data.
	@discussion	Clients may get an instance of AVAssetSegmentReport through the -assetWriter:didOutputSegmentData:segmentType:segmentReport: delegate method, which is defined in AVAssetWriter.h.
*/

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos)
@interface AVAssetSegmentReport : NSObject
AV_INIT_UNAVAILABLE

/*!
	@property	segmentType
	@abstract	A segment type of the segment data.
*/
@property (nonatomic, readonly) AVAssetSegmentType segmentType;

/*!
	@property	trackReports
	@abstract	Provides an array of AVAssetSegmentTrackReport in the segment data.
*/
@property (nonatomic, readonly) NSArray<AVAssetSegmentTrackReport *> *trackReports;

@end


/*!
	@class		AVAssetSegmentTrackReport
	@abstract	This class is vended by AVAssetSegmentReport. It will provide information on a track in a segment data.
*/

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos)
@interface AVAssetSegmentTrackReport : NSObject
AV_INIT_UNAVAILABLE

/*!
	@property	trackID
	@abstract	Indicates the persistent unique identifier for this track.
*/

@property (nonatomic, readonly) CMPersistentTrackID trackID;

/*!
	@property	mediaType
	@abstract	Indicates the media type for this track. Media types are declared in AVMediaFormat.h.
*/
@property (nonatomic, readonly) AVMediaType mediaType;

/*!
	@property	earliestPresentationTimeStamp
	@abstract	Indicates the earliest presentation timestamp (PTS) for this track. The value is kCMTimeInvalid if there is no information available.
*/
@property (nonatomic, readonly) CMTime earliestPresentationTimeStamp;

/*!
	@property	duration
	@abstract	Indicates the duration for this track. The value is kCMTimeInvalid if there is no information available.
*/
@property (nonatomic, readonly) CMTime duration;

/*!
	@property	firstVideoSampleInformation
	@abstract	Provides information on the first video sample in this track. The value is nil if this track is not video track or no information available.
*/
@property (nonatomic, readonly, nullable) AVAssetSegmentReportSampleInformation *firstVideoSampleInformation;

@end


/*!
	@class		AVAssetSegmentReportSampleInformation
	@abstract	This class is vended by AVAssetSegmentTrackReport. It will provide information on a sample in a track.
*/

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos)
@interface AVAssetSegmentReportSampleInformation : NSObject
AV_INIT_UNAVAILABLE

/*!
	@property	presentationTimeStamp
	@abstract	The presentation timestamp (PTS) of the sample.
	@discussion	This timestamp may be different from the earliestPresentationTimeStamp if the video is encoded using frame reordering.
*/
@property (nonatomic, readonly) CMTime presentationTimeStamp;

/*!
	@property	offset
	@abstract	The offset of the sample in the segment.
*/
@property (nonatomic, readonly) NSInteger offset;

/*!
	@property	length
	@abstract	The length of the sample.
*/
@property (nonatomic, readonly) NSInteger length;

/*!
	@property	isSyncSample
	@abstract	Indicates whether the sample is a sync sample.
*/
@property (nonatomic, readonly) BOOL isSyncSample;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetSegmentReport.h>
#endif
