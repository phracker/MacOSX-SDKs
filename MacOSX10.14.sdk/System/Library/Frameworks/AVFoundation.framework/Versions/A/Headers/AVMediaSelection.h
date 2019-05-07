/*
	File:  AVMediaSelection.h

	Framework:  AVFoundation

	Copyright 2015 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import	<AVFoundation/AVAsset.h>
#import <AVFoundation/AVMediaSelectionGroup.h>

NS_ASSUME_NONNULL_BEGIN

@class AVMediaSelectionInternal;
@class AVMutableMediaSelectionInternal;

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AVMediaSelection : NSObject <NSCopying, NSMutableCopying>
{
@private
	AVMediaSelectionInternal *_mediaSelection;
}

/*
 @property		asset
 @abstract		The asset associated with the receiver.
*/
@property (nonatomic, readonly, weak) AVAsset *asset;

/*!
 @method		selectedMediaOptionInMediaSelectionGroup:
 @abstract		Indicates the media selection option that's currently selected from the specified group. May be nil.
 @param 		mediaSelectionGroup
				A media selection group obtained from the receiver's asset.
 @result		An instance of AVMediaSelectionOption that describes the currently selection option in the group.
 @discussion
				If the value of the property allowsEmptySelection of the AVMediaSelectionGroup is YES, the currently selected option in the group may be nil.
*/
- (nullable AVMediaSelectionOption *)selectedMediaOptionInMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup;

/*!
 @method		mediaSelectionCriteriaCanBeAppliedAutomaticallyToMediaSelectionGroup:
 @abstract		Indicates that specified media selection group is subject to automatic media selection.
 @param 		mediaSelectionGroup
				A media selection group obtained from the receiver's asset.
 @result		YES if the group is subject to automatic media selection.
 @discussion	Automatic application of media selection criteria is suspended in any group in which a specific selection has been made via an invocation of -selectMediaOption:inMediaSelectionGroup:.
*/
- (BOOL)mediaSelectionCriteriaCanBeAppliedAutomaticallyToMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup;

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AVMutableMediaSelection : AVMediaSelection
/*!
 @method		selectMediaOption:inMediaSelectionGroup:
 @abstract		Selects the media option described by the specified instance of AVMediaSelectionOption in the specified AVMediaSelectionGroup and deselects all other options in that group.
 @param			mediaSelectionOption
				The option to select.
 @param			mediaSelectionGroup
				The media selection group, obtained from the receiver's asset, that contains the specified option.
 @discussion
				If the specified media selection option isn't a member of the specified media selection group, no change in presentation state will result.
				If the value of the property allowsEmptySelection of the AVMediaSelectionGroup is YES, you can pass nil for mediaSelectionOption to deselect all media selection options in the group.
*/
- (void)selectMediaOption:(nullable AVMediaSelectionOption *)mediaSelectionOption inMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup;

@end

NS_ASSUME_NONNULL_END
