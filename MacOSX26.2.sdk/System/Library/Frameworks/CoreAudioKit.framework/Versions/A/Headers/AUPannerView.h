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
NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos)
@interface AUPannerView : NSView {}
/*! @property audioUnit
	@abstract Read-only property for the audio unit associated with the view
	@result   The audio unit associated with the generic panner view
*/
@property (readonly) AudioUnit audioUnit;

/*! @method +AUPannerViewWithAudioUnit:
    @abstract Static constructor used to create the view
    @param au  The Panner Audio Unit associated with the view
    @result  Returns the newly created view object autoreleased or nil on error
*/
+ (AUPannerView *) AUPannerViewWithAudioUnit: (AudioUnit) au;

@end
NS_ASSUME_NONNULL_END
