/*
     File:       DiscRecordingContent/DRBurn_ContentSupport.h
 
     Contains:   ObjC interface to Burn objects used in image creation.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2004 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#import <Foundation/Foundation.h>
#import <DiscRecordingEngine/DRBurn.h>
#include <AvailabilityMacros.h>

/* ------------------------------------------------------------------------------ */
/* Preconfigured burn types */
/*! 
	@category		DRBurn (ImageContentCreation)
	@discussion		This category on DRBurn creates a custom layout object which is set 
					up to burn an image file to disc. It implements only one method, 
					@link layoutForImageFile: layoutForImageFile: @/link which creates and 
					returns a fully configured layout object to the caller.
*/
@interface DRBurn (ImageContentCreation)

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/*!
	@method			layoutForImageFile:
	@abstract		Creates a layout capable of burning an image to disc.
 	@discussion		The layout created by this method may be any type of object. No assumptions
 					should be made as to what sort of object may be returned based on the 
 					input image type.
	@param			path	The path to the image file. This file must be one that can
							be read by DiscRecording. The supported image types include:
 							.dmg, .iso, .cue, and .toc. For .cue and .toc files the 
 							corresponding data files (.bin, .img, etc) must also be present
 							and correctly referenced in the .cue/.toc file. 
	@result			An autoreleased layout object
*/
+ (id) layoutForImageFile:(NSString*)path;
#endif

@end
