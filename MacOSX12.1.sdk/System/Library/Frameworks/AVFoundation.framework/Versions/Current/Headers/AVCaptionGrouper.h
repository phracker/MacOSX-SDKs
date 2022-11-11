#if !__has_include(<AVFCore/AVCaptionGrouper.h>)
/*
	File:  AVCaptionGrouper.h
 
	Framework:  AVFoundation
 
	Copyright 2015-2021 Apple Inc. All rights reserved.
 
*/

#import <Foundation/Foundation.h>
#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVCaption.h>
#import <AVFoundation/AVCaptionGroup.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, tvos, watchos)
@interface AVCaptionGrouper : NSObject
{
@private
	NSMutableArray<AVCaption *> *_captionCollector;
	CMTime _captionGroupStartTime;
}

- (void)addCaption:(AVCaption *)input;
- (NSArray<AVCaptionGroup *> *)flushAddedCaptionsIntoGroupsUpToTime:(CMTime)upToTime;
@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVCaptionGrouper.h>
#endif
