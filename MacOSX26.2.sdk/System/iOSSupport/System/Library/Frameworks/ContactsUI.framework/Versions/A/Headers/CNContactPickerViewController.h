//
//  CNContactPickerViewController.h
//  ContactsUI
//
//  Copyright (c) 2015 Apple, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Contacts/Contacts.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CNContactPickerDelegate;


/*!
 * @abstract    The CNContactPickerViewController allows the user to select one or multiple contacts or properties.
 * @discussion  The entire list of contacts will be presented to the user.
 *              The picker supports both single selection and multi-selection.
 *              The app does not need access to the user’s contacts and the user will
 *              not be prompted for access. It will only have access to the final selection of the user.
 *              Changing the predicates only takes effect before the view is presented.
 */
NS_CLASS_AVAILABLE_IOS(9_0) API_DEPRECATED("Unavailable on tvOS", tvos(1.0, 18.0))
@interface CNContactPickerViewController : UIViewController

/*!
 * @abstract    The CNContact property keys to display in the contact detail card.
 * @discussion  If not set all properties are displayed.
 */
@property (nonatomic, copy, nullable) NSArray<NSString*> *displayedPropertyKeys;

/*!
 * @abstract    The delegate to be notified when the user selects a contact or property.
 */
@property (nonatomic, weak, nullable) id <CNContactPickerDelegate> delegate;

/*!
 * @abstract    The predicate to determine if a contact is selectable in the list.
 * @discussion  If not set all contacts are selectable.
 */
@property (nonatomic, copy, nullable) NSPredicate *predicateForEnablingContact; // e.g. emailAddresses.@count > 0

/*!
 * @abstract    The predicate to control the selection of a contact.
 * @discussion  It determines whether a selected contact should be returned (predicate evaluates to TRUE)
 *              or if the contact detail card should be displayed (evaluates to FALSE).
 *              If not set the picker displays the contact detail card when the contact is selected.
 */
@property (nonatomic, copy, nullable) NSPredicate *predicateForSelectionOfContact; // e.g. emailAddresses.@count == 1

/*!
 * @abstract    The predicate to control the selection of a property.
 * @discussion  It determines whether a selected property should be returned (predicate evaluates to TRUE)
 *              or if the default action for the property should be performed (predicate evaluates to FALSE).
 *              If not set the picker returns the first selected property.
 *              The predicate is evaluated on the CNContactProperty that is being selected.
 */
@property (nonatomic, copy, nullable) NSPredicate *predicateForSelectionOfProperty; // e.g. (key == 'emailAddresses') AND (value LIKE '*@apple.com')

@end


NS_AVAILABLE_IOS(9_0) API_DEPRECATED("Unavailable on tvOS", tvos(1.0, 18.0))
@protocol CNContactPickerDelegate <NSObject>

@optional

/*!
 * @abstract    Invoked when the picker is closed.
 * @discussion  The picker will be dismissed automatically after a contact or property is picked.
 */
- (void)contactPickerDidCancel:(CNContactPickerViewController *)picker;

/*!
 * @abstract    Singular delegate methods.
 * @discussion  These delegate methods will be invoked when the user selects a single contact or property.
 */
- (void)contactPicker:(CNContactPickerViewController *)picker didSelectContact:(CNContact *)contact;
- (void)contactPicker:(CNContactPickerViewController *)picker didSelectContactProperty:(CNContactProperty *)contactProperty;

/*!
 * @abstract    Plural delegate methods.
 * @discussion  These delegate methods will be invoked when the user is done selecting multiple contacts or properties.
 *              Implementing one of these methods will configure the picker for multi-selection.
 */
- (void)contactPicker:(CNContactPickerViewController *)picker didSelectContacts:(NSArray<CNContact*> *)contacts;
- (void)contactPicker:(CNContactPickerViewController *)picker didSelectContactProperties:(NSArray<CNContactProperty*> *)contactProperties;

@end

NS_ASSUME_NONNULL_END
