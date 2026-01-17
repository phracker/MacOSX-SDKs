//
//  ABNewPersonViewController.h
//  AddressBookUI
//
//  Copyright (c) 2010 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AddressBook/AddressBook.h>

@protocol ABNewPersonViewControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

AB_DEPRECATED("Use +[CNContactViewController viewControllerForNewContact:] from ContactsUI.framework instead")
@interface ABNewPersonViewController : UIViewController

// ABNewPersonViewController does not support subclassing in iOS 7.0 and later. A nil instance will be returned.

@property(nonatomic,assign,nullable) id<ABNewPersonViewControllerDelegate> newPersonViewDelegate;
- (id<ABNewPersonViewControllerDelegate>)newPersonViewDelegate __attribute__((objc_method_family(none)));

    // The Address Book to use. Any contact returned will be from this ABAddressBook instance.
    // If not set, a new ABAddressBook will be created the first time the property is accessed.
@property(nonatomic,readwrite,nullable) ABAddressBookRef addressBook;

    // Specify a displayedPerson to prefill some fields in the card. This is optional.
    // If displayedPerson has been added to an ABAddressBook, then the addressBook
    // property will be updated to use the displayedPerson's ABAddressBook.
@property(nonatomic,readwrite,nullable) ABRecordRef displayedPerson;
    // Specify a parentGroup the person should be added to when saved. This is optional.
@property(nonatomic,readwrite,nullable) ABRecordRef parentGroup;

@end

@protocol ABNewPersonViewControllerDelegate <NSObject>

    // Called when the user selects Save or Cancel. If the new person was saved, person will be
    // a valid person that was saved into the Address Book. Otherwise, person will be NULL.
    // It is up to the delegate to dismiss the view controller.
- (void)newPersonViewController:(ABNewPersonViewController *)newPersonView didCompleteWithNewPerson:(nullable ABRecordRef)person;

@end

NS_ASSUME_NONNULL_END
