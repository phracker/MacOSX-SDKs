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

@interface AUGenericView : NSView {
	void *		_reserved[32];
}

- (id)initWithAudioUnit:(AudioUnit)au;
- (id)initWithAudioUnit:(AudioUnit)inAudioUnit displayFlags:(UInt32)inFlags;

- (AudioUnit)audioUnit;

- (BOOL)showsExpertParameters;
- (void)setShowsExpertParameters:(BOOL)inShowsExpertParameters;

@end
