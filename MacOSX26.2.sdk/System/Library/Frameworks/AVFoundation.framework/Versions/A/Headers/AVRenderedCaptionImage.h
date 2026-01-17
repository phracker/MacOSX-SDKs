#if !__has_include(<AVFCore/AVRenderedCaptionImage.h>)
/*
	File:		AVRenderedCaptionImage.h

	Framework:	AVFoundation

	Copyright 2024-2025 Apple Inc. All rights reserved.

 */

#ifndef AV_RENDERED_CAPTION_IMAGE_H
#define AV_RENDERED_CAPTION_IMAGE_H

#import <Foundation/Foundation.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <AVFoundation/AVBase.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class AVRenderedCaptionImage
 
 @abstract
	AVRenderedCaptionImage is a wrapper class vended out to the client for reading a rendered caption image (CVPixelBuffer) and its associated position (in pixels). The position is relative to the videoDisplaySize (in pixels) provided by the client during the initialization of AVPlayerItemRenderedLegibleOutput, and accordinging to the upper-left-origin coordinate system (ULO). The CVPixelBuffer will be backed by an IOSurface enabling it to be converted to MTLTexture using CVMetalTextureCache.
 
 @discussion
	Display scale is a property of the screen on which the client UI elements are displayed. This value defines the mapping between the logical coordinate space (measured in points) and the physical coordinate space (measured in pixels). Higher scale factors indicate that each point is represented by more than one pixel at render time. For example, if the display scale factor is 2.0 and the bounds of caption rectangle are 50 x 50 points, the size of the CVPixelBufferRef for the caption is 100 x 100 pixels. The client shall provide videoDisplaySize value in pixels only and the position value of the caption image shall also be returned in pixels only.

	Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */

API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(tvos, watchos, visionos)
@interface AVRenderedCaptionImage : NSObject
AV_INIT_UNAVAILABLE

/*!
	@property		pixelBuffer
	@abstract		A CVPixelBufferRef that contains pixel data for the rendered caption.
	@discussion		If the client reads a pixelBuffer and wants to use it longer than AVRenderedCaptionImage, it must retain the pixelBuffer. The pixel buffer can be converted to MTLTexture using CVMetalTextureCache. The pixel format is fixed to kCVPixelFormatType_32BGRA defined in <CoreVideo/CVPixelBuffer.h>.
 */
@property (nonatomic, readonly) CVPixelBufferRef pixelBuffer
#if __swift__
API_DEPRECATED("Use readOnlyPixelBuffer instead", macos(15.0, API_TO_BE_DEPRECATED), ios(18.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(tvos, watchos, visionos)
#endif
;

/*!
	@property		position
	@abstract		A CGPoint that defines the position (in pixels) of the rendered caption image relative to the video frame
	@discussion		To place the caption image correcly, the size of pixel buffer can be extracted from CVPixelBufferGetWidth and CVPixelBufferGetHeight. Origin is assumed at upper-left. So, a caption image is rendered to the right and bottom of the origin point.
 */
@property (nonatomic, readonly) CGPoint position;

@end

NS_ASSUME_NONNULL_END

#endif // AV_RENDERED_CAPTION_IMAGE_H

#else
#import <AVFCore/AVRenderedCaptionImage.h>
#endif
