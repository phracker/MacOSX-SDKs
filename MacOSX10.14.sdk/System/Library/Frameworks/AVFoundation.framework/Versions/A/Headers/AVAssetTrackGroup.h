/*
	File:  AVAssetTrackGroup.h

	Framework:  AVFoundation

	Copyright 2010-2016 Apple Inc. All rights reserved.

 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAssetTrackGroupInternal;

/*!
 @class AVAssetTrackGroup
 @abstract
	A class whose instances describe a group of tracks in an asset.
 
 @discussion
	Instances of AVAssetTrackGroup describe a single group of related tracks in an asset. For example, a track group can
	describe a set of alternate tracks, which are tracks containing variations of the same content, such as content
	translated into different languages, out of which only one track should be played at a time.
 
	Clients can inspect the track groups contained in an AVAsset by loading and obtaining the value of its trackGroups property.
 */

NS_CLASS_AVAILABLE(10_9, 7_0)
@interface AVAssetTrackGroup : NSObject <NSCopying>
{
@private
	AVAssetTrackGroupInternal	*_assetTrackGroup;
}

/*!
 @property trackIDs
 @abstract
	The IDs of all of the tracks in the group.
 
 @discussion
	The value of this property is an NSArray of NSNumbers interpreted as CMPersistentTrackIDs, one for each track in the
	group.
 */
@property (nonatomic, readonly) NSArray<NSNumber *> *trackIDs;

@end

NS_ASSUME_NONNULL_END
