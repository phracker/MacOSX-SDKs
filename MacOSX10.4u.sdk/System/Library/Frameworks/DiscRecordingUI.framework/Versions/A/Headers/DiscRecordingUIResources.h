/*
     File:       DiscRecordingUI/DiscRecordingUIResources.h
 
     Contains:   Resources provided by the DiscRecordingUI framework.
 
      Version:   Technology: Mac OS X
                 Release:    Mac OS X
 
    Copyright:   (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	DiscRecordingUIResources.h
	@abstract	Resources provided by the DiscRecordingUI framework.
	@discussion
*/

#import <Cocoa/Cocoa.h>
#import <AvailabilityMacros.h>

/*!
	@const		DRBurnIcon
	@abstract	The name of the burn icon image.
	@discussion	The icon is available to applications through the @link //apple_ref/occ/instm/NSImage/imageNamed: -[NSImage imageNamed:] @/link method.
*/
extern NSString* const DRBurnIcon		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		DREraseIcon
	@abstract	The name of the erase icon image.
	@discussion	The icon is available to applications through the @link //apple_ref/occ/instm/NSImage/imageNamed: -[NSImage imageNamed:] @/link method.
*/
extern NSString* const DREraseIcon		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
