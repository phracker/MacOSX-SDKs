#if !__has_include(<AVFCore/AVCaptionFormatConformer.h>)
/*
	File:  AVCaptionFormatConformer.h

	Framework:  AVFoundation

	Copyright 2018-2023 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#if ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )

#import <Foundation/Foundation.h>
#import <AVFoundation/AVCaption.h>
#import <AVFoundation/AVCaptionSettings.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class AVCaptionFormatConformer
 @abstract
	Performs a conversion of canonical caption to conform to a specific format.
*/
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos)
@interface AVCaptionFormatConformer : NSObject
AV_INIT_UNAVAILABLE

/*!
 @method	captionFormatConformerWithConversionSettings:conversionSettings:
 @abstract	Returns an instance of AVCaptionFormatConformer that can convert a canonical caption to conform to a specific format.
 @param		conversionSettings
 			Describes the conversion operation for which the caption is to be conformed.
 @result	A new instance of AVCaptionFormatConformer configured to perform the specified conversion.
*/
+ (instancetype)captionFormatConformerWithConversionSettings:(NSDictionary<AVCaptionSettingsKey, id> *)conversionSettings;

/*!
 @method	initWithConversionSettings:conversionSettings:
 @abstract	Returns an instance of AVCaptionFormatConformer that can convert a canonical caption to conform to a specific format.
 @param		conversionSettings
 			Describes the conversion operation for which the caption is to be conformed.
 @result	A new instance of AVCaptionFormatConformer configured to perform the specified conversion.
 @discussion This method throws an exception if the conversion setting's AVCaptionMediaTypeKey is not equal to AVMediaTypeClosedCaption, or if its AVCaptionMediaSubTypeKey is not equal to kCMClosedCaptionFormatType_CEA608.
*/
- (instancetype)initWithConversionSettings:(NSDictionary<AVCaptionSettingsKey, id> *)conversionSettings NS_DESIGNATED_INITIALIZER;

/*!
 @property	conformsCaptionsToTimeRange
 @abstract	Specifies whether to conform the time range of a given canonical caption as well.
 @discussion
	When set to YES, conforms time range.
	When set to NO, the time range of the conformed caption will be same as a given canonical caption.
	In the case of conforming to CAE608 format, AVCaption is encoded so that each CAE608 control code (2 bytes) fits into 1 frame duration (1001/30000).
	When set to YES and if all the encoded data can not fit inside the canonical caption time range, the caption time range will be extended to fit all the data and will be returned in the conformed AVCaption.
	The default value is NO.
*/
@property (nonatomic) BOOL conformsCaptionsToTimeRange;

/*!
 @method	conformedCaptionForCaption:error:
 @abstract	Creates a format-compliant caption that conforms to a specific format by converting a given canonical caption.
 @param		caption
			Specifies a canonical caption to be converted.
 @param		outError
			A pointer where a NSError object may be returned.
 @result	A format-compliant caption that conforms to a specific format.
*/
- (nullable AVCaption *)conformedCaptionForCaption:(AVCaption *)caption error:(NSError * _Nullable * _Nullable)outError;

@end

NS_ASSUME_NONNULL_END

#endif // ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )

#else
#import <AVFCore/AVCaptionFormatConformer.h>
#endif
