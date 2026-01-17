#if !__has_include(<PassKitCore/PKContact.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKContact.h
//    PassKit
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#ifndef __PKCONTACT_H
#define __PKCONTACT_H

#import <Foundation/Foundation.h>

#if !TARGET_OS_TV
#import <Contacts/Contacts.h>
#endif

API_AVAILABLE(macos(10.12), ios(9.0), watchos(3.0))
@interface PKContact : NSObject

@property (nonatomic, strong, nullable) NSPersonNameComponents *name;

#if TARGET_OS_TV
@property (nonatomic, strong, nullable) id postalAddress;
@property (nonatomic, strong, nullable) id phoneNumber;
#else
@property (nonatomic, strong, nullable) CNPostalAddress *postalAddress;
@property (nonatomic, strong, nullable) CNPhoneNumber   *phoneNumber;
#endif

@property (nonatomic, strong, nullable) NSString        *emailAddress;


// This property is now deprecated. Use the -subLocality property on [PKContact -postalAddress] instead
@property (nonatomic, retain, nullable) NSString        *supplementarySubLocality API_DEPRECATED("Use subLocality and subAdministrativeArea on -postalAddress instead", ios(9.2, 10.3), watchos(3.0, 3.2));

@end

#endif

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKContact.h>
#endif