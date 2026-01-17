/*
	File:      AUPannerView.h
 
	Contains:  Class definition for Generic Cocoa based view for any Panner Audio Unit
 
	Copyright: (c) 2006-2008 by Apple, Inc. All rights reserved.
 
	Bugs?:      For bug reports, consult the following page on the World Wide Web:
 
	http://developer.apple.com/bugreporter/
*/

#import <Cocoa/Cocoa.h>
#include <AudioUnit/AudioUnit.h>

/*!
@class AUPannerView
@abstract  An AUPannerView object retrieves and instantiates a generic panner view for the given panner unit
*/
@interface AUPannerView : NSView {}

/*! @method +AUPannerViewWithAudioUnit:
    @abstract Static constructor used to create the view
    @discussion This static constructor is called as follows:
		AUPannerView *mGenericPannerView = nil;
		mGenericPannerView = [[AUPannerView AUPannerViewWithAudioUnit: mCurrentAU] retain];

	Note that we retain the returned view because it is returned autoreleased. You do not to retain it if you are adding the view as a subview of an existing NSView.
    @param au  The Panner Audio Unit associated with the view
    @result  Returns the newly created view object autoreleased or nil on error
*/
+ (id) AUPannerViewWithAudioUnit: (AudioUnit) au;

/*! @method audioUnit
	@abstract Accessor method for the audio unit associated with the view
	@result   The audio unit associated with the generic panner view or nil on error
*/
- (AudioUnit) audioUnit;

@end