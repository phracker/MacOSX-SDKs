/*
	File:  AVError.h
	
	Framework:  AVKit
	
	Copyright © 2015-2023 Apple Inc. All rights reserved.
	
 */

#import <Foundation/Foundation.h>

#if TARGET_OS_OSX || TARGET_OS_MACCATALYST
#import <AVKit/AVKitDefines.h>
#else
#import <AVKit/AVKitDefines.h>
#endif // TARGET_OS_OSX || TARGET_OS_MACCATALYST


/*!
	@constant	AVKitErrorDomain
	@abstract	Domain for errors from AVKit APIs.
 */
AVKIT_EXTERN NSString * const AVKitErrorDomain API_AVAILABLE(ios(9.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos);


/*!
	@constant	AVKitErrorUnknown
				Unknown error.
	@constant	AVKitErrorPictureInPictureStartFailed
				Failed to start Picture in Picture.

	@constant	AVKitErrorContentRatingUnknown
				Media content rating missing or unrecognized.
 	@constant	AVKitErrorContentDisallowedByPasscode
 				Restriction settings disallow access to this content, but the user can override by entering the passcode.
 	@constant	AVKitErrorContentDisallowedByProfile
 				An installed profile sets restriction settings that disallow access to this content; the user cannot override by entering the passcode (they may be able to override in Settings).
 
 	@constant	AVKitErrorRecordingFailed
				The recording failed.
 */
typedef NS_ENUM(NSInteger, AVKitError) {
	AVKitErrorUnknown																						= -1000,
	AVKitErrorPictureInPictureStartFailed API_UNAVAILABLE(watchos)											= -1001,

	AVKitErrorContentRatingUnknown API_AVAILABLE(tvos(13.0)) API_UNAVAILABLE(ios, visionos, watchos)		= -1100,
	AVKitErrorContentDisallowedByPasscode API_AVAILABLE(tvos(13.0)) API_UNAVAILABLE(ios, visionos, watchos)	= -1101,
	AVKitErrorContentDisallowedByProfile API_AVAILABLE(tvos(13.0)) API_UNAVAILABLE(ios, visionos, watchos)	= -1102,

	AVKitErrorRecordingFailed API_UNAVAILABLE(watchos) API_UNAVAILABLE(ios, tvos, visionos)				= -1200,
} API_AVAILABLE(ios(9.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos);
