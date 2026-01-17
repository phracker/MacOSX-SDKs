//
//  CNContactVCardSerialization.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CNKeyDescriptor;
@class CNContact;

/*!
 * @abstract    Contact vCard support.
 *
 * @discussion  This converts between a contact and its vCard representation.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactVCardSerialization : NSObject

/*!
 * @abstract    Descriptor for all contact keys required by vCard serialization
 *
 * @discussion  This descriptor must be passed to the fetch request if the returned
 *              contacts are to be serialized with dataWithContacts:error:.
 */
+ (id<CNKeyDescriptor>)descriptorForRequiredKeys;

/*!
 * @abstract    Serialize contacts to data.
 *
 * @discussion  The contacts to be serialized must have been fetched with
 *              @c +descriptorForRequiredKeys.
 *
 * @param       contacts
 *              The contacts to serialize.
 *
 * @param       error
 *              An optional outparameter. If the serialization fails, this will be set.
 *
 * @returns     The encoded data. If the serialization fails, this will be @c nil.
 */
+ (nullable NSData *)dataWithContacts:(NSArray<CNContact *>*)contacts error:(NSError **)error;

/*!
 * @abstract    Parse data into contacts.
 *
 * @param       data
 *              The data to parse.
 *
 * @param       error
 *              An optional outparameter. If the parsing fails, this will be set.
 *
 * @returns     The parsed contacts. If the parsing fails, this will be @c nil.
 */
+ (nullable NSArray<CNContact *>*)contactsWithData:(NSData *)data error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
