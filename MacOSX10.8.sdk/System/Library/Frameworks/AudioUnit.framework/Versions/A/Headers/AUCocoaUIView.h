/*
     File:       AUCocoaUIView.h
 
     Contains:   Specification of Protocol for Cocoa based UI Views for AudioUnits
 
     Copyright:  (c) 2003 - 2008 by Apple, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#if __OBJC__

#import <Cocoa/Cocoa.h>
#include <AudioUnit/AudioUnit.h>

@protocol AUCocoaUIBase

/*!
	@header AUCocoaUIView
	This file specifies a protocol that cocoa-based audio unit views will implement. Audio Unit hosts will call these methods to retrieve the view for your audio unit.
 */

/*!
	@function	interfaceVersion
	@abstract	Return the version of the interface you are implementing.
	@result		An unsigned value.
	@discussion For MacOS X 10.3 or later, you should return the current version which is 0.
				NOTE: Developers are strongly encouraged to override -(NSString *)description to return the name
				of the cocoa view. This name is displayed by host applications and should be returned as a copy
				instead of a static string.
				
				For example, you could define the description method like this:
					- (NSString *) description {
						return [NSString withString: @"Filter View"];
					}
*/
- (unsigned)interfaceVersion;

/*!
	@function	uiViewForAudioUnit:withSize:
	@abstract	Return the NSView responsible for displaying the interface for the provided AudioUnit.
	@param		inAudioUnit
					The Audio Unit the view is associated with.
	@param		inPreferredSize
					The preferred size of the view to be returned.
	@result		An NSView.
	
	@discussion
				This method is a factory function: each call to it must return a unique view.
				Each view must be returned with a retain count of 1 and autoreleased.
				It is the client's responsibility to retain the returned view and to release the view when it's no longer needed.
*/
- (NSView *)uiViewForAudioUnit:(AudioUnit)inAudioUnit withSize:(NSSize)inPreferredSize;

@end

#endif
