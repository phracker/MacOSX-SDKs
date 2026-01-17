//
//  ABUnknownPersonViewController.h
//  AddressBookUI
//
//  Copyright (c) 2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AddressBook/AddressBook.h>

@protocol ABUnknownPersonViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

AB_DEPRECATED("Use +[CNContactViewController viewControllerForUnknownContact:] from ContactsUI.framework instead")
@interface ABUnknownPersonViewController : UIViewController

// ABPersonViewController does not support subclassing in iOS 7.0 and later. A nil instance will be returned.

@property(nonatomic,assign,nullable) id<ABUnknownPersonViewControllerDelegate> unknownPersonViewDelegate;

    // The Address Book to use. Any contact returned will be from this ABAddressBook instance.
    // If not set, a new ABAddressBook will be created the first time the property is accessed.
@property(nonatomic,readwrite,nullable) ABAddressBookRef addressBook;

    // All the fields specified in displayedPerson will be displayed in the view
    // and used if the unknown person is added to Address Book or merged into an
    // existing person in Address Book.
    // If displayedPerson has been added to an ABAddressBook, then the addressBook
    // property will be updated to use the displayedPerson's ABAddressBook.
@property(nonatomic,readwrite) ABRecordRef displayedPerson;

    // An alternateName can be provided to replace the First and Last name
    // in case they are not available.
@property(nonatomic,copy,nullable) NSString *alternateName;
    // The message will be displayed below the alternateName.
@property(nonatomic,copy,nullable) NSString *message;

    // Specifies whether buttons appear to let the user perform actions such as sharing the contact,
    // initiating a FaceTime call, or sending a text message.
@property(nonatomic) BOOL allowsActions;
    // Whether options to create a contact or add to an existing contact should be
    // made available to the user.
@property(nonatomic) BOOL allowsAddingToAddressBook;

@end


@protocol ABUnknownPersonViewControllerDelegate <NSObject>

    // Called when picking has completed.  If picking was canceled, 'person' will be NULL.
    // Otherwise, person will be either a non-NULL resolved contact, or newly created and
    // saved contact, in both cases, person will be a valid contact in the Address Book.
    // It is up to the delegate to dismiss the view controller.
- (void)unknownPersonViewController:(ABUnknownPersonViewController *)unknownCardViewController didResolveToPerson:(nullable ABRecordRef)person;

@optional
    // Called when the user selects an individual value in the unknown person view, identifier will be kABMultiValueInvalidIdentifier if a single value property was selected.
    // Return NO if you do not want anything to be done or if you are handling the actions yourself.
    // Return YES if you want the ABUnknownPersonViewController to perform its default action.
- (BOOL)unknownPersonViewController:(ABUnknownPersonViewController *)personViewController shouldPerformDefaultActionForPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_3_0);

@end

NS_ASSUME_NONNULL_END
