#if !__has_include(<AVFCore/AVCaptionSettings.h>)
/*
	File:  AVCaptionSettings.h

	Framework:  AVFoundation

	Copyright 2018-2023 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#if ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )

#import <Foundation/Foundation.h>

/*!
	@header		AVCaptionSettings
	@abstract	NSDictionary keys for configuring the output caption format and validation for a caption format
*/

/*!
	@typedef	AVCaptionSettingsKey
	@abstract	Keys for the captions settings dictionary.
*/
typedef NSString * AVCaptionSettingsKey NS_TYPED_ENUM API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
	@constant	AVCaptionMediaTypeKey
	@abstract	Indicates the output media type of a caption conversion operation. For example, AVMediaTypeClosedCaption.
*/
AVF_EXPORT AVCaptionSettingsKey const AVCaptionMediaTypeKey API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
	@constant	AVCaptionMediaSubTypeKey
	@abstract	Indicates the output media subtype of a caption conversion operation. For example, [NSNumber numberWithInt:kCMClosedCaptionFormatType_CEA608].
	@discussion
		Both numeric and string forms of media subtypes are accepted for caption conversions, so you could, for example, use @"c608" instead of [NSNumber numberWithInt:kCMClosedCaptionFormatType_CEA608].
*/
AVF_EXPORT AVCaptionSettingsKey const AVCaptionMediaSubTypeKey API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
    @constant   AVCaptionTimeCodeFrameDurationKey
    @abstract	Frame duration used for the time code.
    @discussion
		Some formats, such as TTML, use time code notation to indicate the timing of a caption. Use the property to specify the frame rate of the time code. 

		For example, if the time code steps for every 1001 / 30000 seconds, the value should be CMTime(value: 1001, scale: 30000).
*/
AVF_EXPORT AVCaptionSettingsKey const AVCaptionTimeCodeFrameDurationKey API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos); // CMTime as NSValue through +[NSValue valueWithCMTime] in AVTime.h

/*!
	@constant	AVCaptionUseDropFrameTimeCodeKey
	@abstract	Indicates whether to use drop frame time code.
	@discussion
		Some formats, such as SCC, use time code notation to indicate the timing of a caption. Use the property to specify whether to use the drop frame time code or non-drop frame time code.
		When the value for this key is a NSNumber indicating the BOOL YES, the receiver will use the drop frame time code.
		When the value for this key is a NSNumber indicating the BOOL NO, the receiver will use the non-drop frame time code.
		The default is NO.
*/
AVF_EXPORT AVCaptionSettingsKey const AVCaptionUseDropFrameTimeCodeKey API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

#endif // ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )

#else
#import <AVFCore/AVCaptionSettings.h>
#endif
