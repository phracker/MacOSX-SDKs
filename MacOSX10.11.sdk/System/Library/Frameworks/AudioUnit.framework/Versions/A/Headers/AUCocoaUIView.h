/*!
	@file		AUCocoaUIView.h
 	@framework	AudioUnit.framework
 	@copyright	(c) 2003-2015 Apple, Inc. All rights reserved.
	@abstract	Protocol for Cocoa-based audio unit views.
	@discussion
	
	Audio unit hosts can call these methods to retrieve views for audio units.
*/

#if __OBJC__

#import <Cocoa/Cocoa.h>
#include <AudioUnit/AudioUnit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AUCocoaUIBase

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
- (NSView * __nullable)uiViewForAudioUnit:(AudioUnit)inAudioUnit withSize:(NSSize)inPreferredSize;

@end

NS_ASSUME_NONNULL_END

#endif
