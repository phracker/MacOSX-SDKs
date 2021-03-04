//
//  Copyright (c) 2012 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@protocol ABPersonPickerDelegate;

/*!
 * @abstract ABPersonPicker is a popover-based person picker for choosing an ABPerson or ABPerson's value, such as a phone number or email address.
 */
OBJC_GC_UNAVAILABLE
API_AVAILABLE(macos(10.9))
API_UNAVAILABLE(macCatalyst)
@interface ABPersonPicker : NSObject

/*!
 * @abstract The ABPerson properties to display when a person is expanded.
 * @discussion If no properties are provided, the picker will select people instead of values.
 */
@property (copy) NSArray * properties;

/*!
 * @abstract The picker delegate to be notified when the user chooses a person or value.
 */
@property (assign) id<ABPersonPickerDelegate> delegate;

/*!
 * @abstract Shows the picker popover relative to a positioning rect for a view with a preferred edge. See NSPopover for more information.
 */
- (void)showRelativeToRect:(NSRect)positioningRect ofView:(NSView *)positioningView preferredEdge:(NSRectEdge)preferredEdge;

/*!
 * @abstract Closes the popover.
 */
- (void)close;

@end
