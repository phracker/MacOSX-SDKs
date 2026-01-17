//
//  Copyright (c) 2012-2015 Apple, Inc. All rights reserved.
//

#import <AppKit/AppKit.h>

NS_ASSUME_NONNULL_BEGIN

@class CNContactPicker;
@class CNContact;
@class CNContactProperty;

NS_AVAILABLE_MAC(10_11)
@protocol CNContactPickerDelegate <NSObject>

@optional

/*!
 * @abstract Notifies the delegate when the user selects a contact. Only called when keysToDisplay is empty.
 */
- (void)contactPicker:(CNContactPicker *)picker didSelectContact:(CNContact *)contact;

/*!
 * @abstract Notifies the delegate when the user selects a particular value of contact. Only called when keysToDisplay is non-empty.
 */
- (void)contactPicker:(CNContactPicker *)picker didSelectContactProperty:(CNContactProperty *)contactProperty;

/*!
 * @abstract Notifies the delegate when the contact picker's popover will close.
 */
- (void)contactPickerWillClose:(CNContactPicker *)picker;

/*!
 * @abstract Notifies the delegate when the contact picker's popover has closed.
 */
- (void)contactPickerDidClose:(CNContactPicker *)picker;

@end

NS_ASSUME_NONNULL_END
