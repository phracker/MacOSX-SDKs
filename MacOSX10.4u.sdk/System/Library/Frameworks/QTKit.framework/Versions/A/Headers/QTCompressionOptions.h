/*
	File:		QTCompressionOptions.h
 
	Copyright:	(c)2007 by Apple Inc., all rights reserved.
 
 */

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

/*
	Compression options identifiers:
	
	A QTCompressionOptions object can be created with any of the following identifiers, each representing a set of options that determine how media will be compressed. 
 
	These compression options are appropriate for high quality intermediate video that requires further processing.
		@"QTCompressionOptionsLosslessAppleIntermediateVideo";
		@"QTCompressionOptionsLosslessAnimationVideo";
        @"QTCompressionOptionsJPEGVideo";

	These compression options are appropriate for medium and low quality video that will be used for delivery to destinations such as the internet.
		@"QTCompressionOptions120SizeH264Video";
		@"QTCompressionOptions240SizeH264Video";
		@"QTCompressionOptionsSD480SizeH264Video";
		@"QTCompressionOptions120SizeMPEG4Video";
		@"QTCompressionOptions240SizeMPEG4Video";
		@"QTCompressionOptionsSD480SizeMPEG4Video";
	
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
#if __LP64__
	int32_t							_proxy;
#else
	QTCompressionOptionsInternal	*_internal;
#endif
	long							_reserved;
}

// This method returns all of the possible identifiers for the given media type that can be used with compressionOptionsWithIdentifier: on the user's system. Media types are defined in QTMedia.h.
+ (NSArray *)compressionOptionsIdentifiersForMediaType:(NSString *)mediaType;

// This method returns a compression options object configured for the given identifier.
+ (id)compressionOptionsWithIdentifier:(NSString *)identifier;

- (NSString *)mediaType;

- (NSString *)localizedDisplayName;
- (NSString *)localizedCompressionOptionsSummary;

- (BOOL)isEqualToCompressionOptions:(QTCompressionOptions *)compressionOptions;

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */
