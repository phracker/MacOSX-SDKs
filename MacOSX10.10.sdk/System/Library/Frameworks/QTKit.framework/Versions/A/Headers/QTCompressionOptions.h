/*
	File:		QTCompressionOptions.h
 
	Copyright:	(c)2007-2012 by Apple Inc., all rights reserved.
 
*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

/*
	Compression options identifiers:
	
	A QTCompressionOptions object can be created with any of the following identifiers, each representing a set of options that determine how media will be compressed. 
 
	These compression options are appropriate for high quality intermediate video that requires further processing.
		@"QTCompressionOptionsLosslessAnimationVideo";
		@"QTCompressionOptionsJPEGVideo";
		@"QTCompressionOptionsLosslessAppleIntermediateVideo";		// Not available in 64-bit

	These compression options are appropriate for medium and low quality video that will be used for delivery to destinations such as the internet.
		@"QTCompressionOptions120SizeH264Video";
		@"QTCompressionOptions240SizeH264Video";
		@"QTCompressionOptionsSD480SizeH264Video";
		@"QTCompressionOptionsHD720SizeH264Video";
		@"QTCompressionOptions120SizeMPEG4Video";		// Not available in 64-bit
		@"QTCompressionOptions240SizeMPEG4Video";		// Not available in 64-bit
		@"QTCompressionOptionsSD480SizeMPEG4Video";		// Not available in 64-bit
	
	This compression option is appropriate for lossless audio that requires further processing, or is intended for high fidelity destinations.
		@"QTCompressionOptionsLosslessALACAudio";
 
	These compression options are appropriate for audio delivered with lossy compression.
		@"QTCompressionOptionsHighQualityAACAudio";		// For music and other high quality audio
		@"QTCompressionOptionsVoiceQualityAACAudio";	// For voice recordings
*/

@class QTCompressionOptionsInternal;

@interface QTCompressionOptions : NSObject
{
@private
	QTCompressionOptionsInternal	*_internal;
	long							_reserved;
}

// This method returns all of the possible identifiers for the given media type that can be used with compressionOptionsWithIdentifier: on the user's system. Media types are defined in QTMedia.h.
+ (NSArray *)compressionOptionsIdentifiersForMediaType:(NSString *)mediaType AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

// This method returns a compression options object configured for the given identifier.
+ (id)compressionOptionsWithIdentifier:(NSString *)identifier AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (NSString *)mediaType AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (NSString *)localizedDisplayName AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (NSString *)localizedCompressionOptionsSummary AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (BOOL)isEqualToCompressionOptions:(QTCompressionOptions *)compressionOptions AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */
