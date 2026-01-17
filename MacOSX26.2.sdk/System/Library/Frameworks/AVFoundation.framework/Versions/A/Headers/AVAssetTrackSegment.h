#if !__has_include(<AVFCore/AVAssetTrackSegment.h>)
/*
	File:  AVAssetTrackSegment.h

	Framework:  AVFoundation
 
	Copyright 2010-2015 Apple Inc. All rights reserved.

*/

/*!
	@class			AVAssetTrackSegment

	@abstract		AVAssetTrackSegment represents a segment of an AVAssetTrack, comprising of a
					time mapping from the source to the asset track timeline.

					Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVAssetTrackSegment : NSObject
{
@private
	CMTimeMapping	_timeMapping;
}
AV_INIT_UNAVAILABLE

/* indicates the timeRange of the track of the container file of the media presented by the AVAssetTrackSegment */
@property (nonatomic, readonly) CMTimeMapping timeMapping;

/* indicates whether the AVAssetTrackSegment is an empty segment */
@property (nonatomic, readonly, getter=isEmpty) BOOL empty;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetTrackSegment.h>
#endif
