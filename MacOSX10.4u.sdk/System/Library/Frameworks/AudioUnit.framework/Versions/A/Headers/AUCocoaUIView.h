/*
     File:       AUCocoaUIView.h
 
     Contains:   Specification of Protocol for Cocoa based UI Views for AudioUnits
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#import <Cocoa/Cocoa.h>
#include <AudioUnit/AudioUnit.h>

@protocol AUCocoaUIBase

// Returns the version of the interface you are implementing
// In Mac OS X v10.3, this is 0
- (unsigned)interfaceVersion;

// Returns the NSView responsible for displaying the interface for the provided AudioUnit.
//
// This function is a factory function: each call to it must return a unique view.
// Each view must be returned with a retain count of 1 and autoreleased.
// It is the client's responsibility to retain the returned view and to release the view when it's
// no longer needed.
- (NSView *)uiViewForAudioUnit:(AudioUnit)inAudioUnit withSize:(NSSize)inPreferredSize;

@end
