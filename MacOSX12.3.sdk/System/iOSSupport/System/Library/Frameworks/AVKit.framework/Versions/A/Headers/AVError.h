/*
	File:  AVError.h
	
	Framework:  AVKit
	
	Copyright © 2015-2016 Apple Inc. All rights reserved.
	
 */

#import <Foundation/Foundation.h>

#import <AVKit/AVKitDefines.h>


/*!
	@constant	AVKitErrorDomain
	@abstract	Domain for errors from AVKit APIs.
 */
AVKIT_EXTERN NSString * const AVKitErrorDomain API_AVAILABLE(ios(9.0));


/*!
	@constant	AVKitErrorUnknown
				Unknown error.
	@constant	AVKitErrorPictureInPictureStartFailed
				Failed to start Picture in Picture.
 */
typedef NS_ENUM(NSInteger, AVKitError) {
	AVKitErrorUnknown						= -1000,
	AVKitErrorPictureInPictureStartFailed	= -1001
} API_AVAILABLE(ios(9.0));
