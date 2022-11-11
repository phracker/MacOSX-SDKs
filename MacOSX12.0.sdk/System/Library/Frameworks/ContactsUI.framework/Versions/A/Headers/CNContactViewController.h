//
//  Copyright (c) 2015 Apple, Inc. All rights reserved.
//

#import <AppKit/AppKit.h>

NS_ASSUME_NONNULL_BEGIN

@class CNContact;
@protocol CNKeyDescriptor;

/*!
 * @abstract A view controller to display and edit a @c CNContact.
 */

NS_AVAILABLE_MAC(10_11)
@interface CNContactViewController : NSViewController

/*!
 * @abstract Descriptor for all keys that must be fetched on a contact before setting it on the view controller.
 * @discussion Pass this descriptor to the keysToFetch of the @c CNContactFetchRequest if you want to display the contact in a @c CNContactViewController.
 */
+ (id<CNKeyDescriptor>)descriptorForRequiredKeys;

/*!
 * @abstract A @c contact to display.
 * @discussion When @c contact is nil, displays an empty selection state.
 */
@property (readwrite, copy, nullable) CNContact *contact;

@end

NS_ASSUME_NONNULL_END
