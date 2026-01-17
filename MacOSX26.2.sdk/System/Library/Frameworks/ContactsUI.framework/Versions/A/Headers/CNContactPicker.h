//
//  Copyright (c) 2012-2015 Apple, Inc. All rights reserved.
//

#import <AppKit/AppKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CNContactPickerDelegate;

/*!
 * @abstract CNContactPicker is a popover-based contact picker for choosing a contact or a contact's value, such as a phone number or email address.
 */
NS_AVAILABLE_MAC(10_11)
@interface CNContactPicker : NSObject

/*!
 * @abstract The CNContact keys to display when a contact is expanded.
 * @discussion If no keys are provided, the picker will select contacts instead of values.
 */
@property (copy) NSArray<NSString *> * displayedKeys;

/*!
 * @abstract The picker delegate to be notified when the user chooses a contact or value.
 */
@property (weak) id<CNContactPickerDelegate> delegate;

/*!
 * @abstract Shows the picker popover relative to a positioning rect for a view with a preferred edge. See NSPopover for more information.
 */
- (void)showRelativeToRect:(NSRect)positioningRect ofView:(NSView *)positioningView preferredEdge:(NSRectEdge)preferredEdge;

/*!
 * @abstract Closes the popover.
 */
- (void)close;

@end

NS_ASSUME_NONNULL_END
