/*
     File:      AUGenericView.h
 
     Contains:  Class definition for Generic Cocoa based view for any Audio Unit
 
     Version:   Mac OS X
 
     Copyright: (c) 2004 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/

#import <Cocoa/Cocoa.h>
#include <AudioUnit/AudioUnit.h>

enum {
	AUViewTitleDisplayFlag			= 1 << 0,
	AUViewPropertiesDisplayFlag		= 1 << 1,
	AUViewParametersDisplayFlag		= 1 << 2
};

/*!
@class AUGenericView
@abstract  An AUGenericView object retrieves and instantiates a generic user interface view for the given audio unit
*/
@interface AUGenericView : NSView {
	__strong void *		_reserved[32];
}

/*! @method initWithAudioUnit:
@abstract initializer used to create the view for a specific audio unit
@param au  The Audio Unit associated with the view
@result  Returns the newly created view object or nil on error
*/
- (id)initWithAudioUnit:(AudioUnit)au;
/*! @method initWithAudioUnit:displayFlags:
	@abstract initializer used to create the view for a specific audio unit with a parameter for view flags
	@param au  The Audio Unit associated with the view
	@param inFlags  The flags specifying display properties (multiple flags can be combined using the or '|' operator)
	@result  Returns the newly created view object or nil on error
*/
- (id)initWithAudioUnit:(AudioUnit)inAudioUnit displayFlags:(UInt32)inFlags;

/*! @method audioUnit
@abstract Accessor method for the audio unit associated with the view
@result   The audio unit associated with the generic view or nil on error
*/
- (AudioUnit)audioUnit;

/*! @method showsExpertParameters
@abstract  Accessor method for determining whether the view is displaying expert parameters or not
@result   True if the view is displaying expert parameters for the audio unit
*/
- (BOOL)showsExpertParameters;

/*! @method setShowsExpertParameters:
@abstract  Accessor method for setting whether the view displays expert parameters or not
@param   True if the view should display expert parameters for the audio unit
*/
- (void)setShowsExpertParameters:(BOOL)inShowsExpertParameters;

@end
