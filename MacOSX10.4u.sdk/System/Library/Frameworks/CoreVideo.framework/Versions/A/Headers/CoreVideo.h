/*
 *  CoreVideo.h
 *  CoreVideo
 *
 *  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */
/*!
    @header CoreVideo
	@copyright 2004 Apple Computer, Inc. All rights reserved.
	@availability Mac OS X 10.4 or later
    @abstract   Umbrella header for the CoreVideo framework
    @discussion This header includes all necesssary headers for the CoreVideo API
*/

#include <TargetConditionals.h>
#include <AvailabilityMacros.h>


#include <CoreVideo/CVReturn.h>
#include <CoreVideo/CVBase.h>
#include <CoreVideo/CVHostTime.h>
#include <CoreVideo/CVDisplayLink.h>
#include <CoreVideo/CVBuffer.h>
#include <CoreVideo/CVPixelBuffer.h>
#include <CoreVideo/CVPixelBufferPool.h>
#include <CoreVideo/CVOpenGLBuffer.h>
#include <CoreVideo/CVOpenGLBufferPool.h>
#include <CoreVideo/CVOpenGLTexture.h>
#include <CoreVideo/CVOpenGLTextureCache.h>
#include <CoreVideo/CVPixelFormatDescription.h>
