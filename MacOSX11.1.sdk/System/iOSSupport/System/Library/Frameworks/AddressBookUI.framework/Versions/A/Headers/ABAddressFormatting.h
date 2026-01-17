//
//  ABAddressFormatting.h
//  AddressBookUI
//
//  Copyright (c) 2010 Apple Inc. All rights reserved.
//

#import <AddressBook/AddressBook.h>

#if defined(__cplusplus)
extern "C" {
#endif    

NS_ASSUME_NONNULL_BEGIN
    
    // address: an address dictionary obtained representing the address (kABPersonAddressProperty) of a person (ABRecordRef)
    // addCountryName: whether to always include the country name in the address string, regardless of whether it is specified
    //                 in the dictionary. If not specified by the user a localized country name will be added.
    // returns a formatted multi line string that contains the full address. The string is likely to contain line endings.
NSString *ABCreateStringWithAddressDictionary(NSDictionary *address, BOOL addCountryName) NS_RETURNS_RETAINED AB_DEPRECATED("Use CNPostalAddressFormatter from Contacts.framework instead");

NS_ASSUME_NONNULL_END
    
#if defined(__cplusplus)
}
#endif
