//
//  CNContactVCardSerialization.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CNKeyDescriptor;

/*!
 * @abstract Contact vCard support.
 *
 * @discussion This converts between a contact and its vCard representation.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactVCardSerialization : NSObject

/*!
 *  @abstract Descriptor for all contact keys required by vCard serialization
 *
 *  @discussion This descriptor must be passed to the fetch request if the returned
 *              contacts are to be serialized with dataWithContacts:error:.
 */
+ (id<CNKeyDescriptor>)descriptorForRequiredKeys;

+ (nullable NSData *)dataWithContacts:(NSArray *)contacts error:(NSError *__nullable *__nullable)error;
+ (nullable NSArray *)contactsWithData:(NSData *)data error:(NSError *__nullable *__nullable)error;

@end

NS_ASSUME_NONNULL_END
