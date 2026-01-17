/*
        NSTextContent.h
        Application Kit
        Copyright (c) 2020-2024, Apple Inc.
        All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/AppKitDefines.h>
#import <Availability.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

typedef NSString* NSTextContentType NS_TYPED_ENUM;

APPKIT_EXTERN API_AVAILABLE(macos(11.0)) NSTextContentType const NSTextContentTypeUsername;
APPKIT_EXTERN API_AVAILABLE(macos(11.0)) NSTextContentType const NSTextContentTypePassword;
APPKIT_EXTERN API_AVAILABLE(macos(11.0)) NSTextContentType const NSTextContentTypeOneTimeCode;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeNewPassword;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeName;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeNamePrefix;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeGivenName;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeMiddleName;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeFamilyName;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeNameSuffix;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeNickname;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeJobTitle;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeOrganizationName;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeLocation;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeFullStreetAddress;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeStreetAddressLine1;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeStreetAddressLine2;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeAddressCity;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeAddressState;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeAddressCityAndState;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeSublocality;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeCountryName;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypePostalCode;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeTelephoneNumber;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeEmailAddress;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeURL;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeCreditCardNumber;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeCreditCardName;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeCreditCardGivenName;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeCreditCardMiddleName;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeCreditCardFamilyName;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeCreditCardSecurityCode;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeCreditCardExpiration;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeCreditCardExpirationMonth;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeCreditCardExpirationYear;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeCreditCardType;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeShipmentTrackingNumber;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeFlightNumber;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeDateTime;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeBirthdate;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeBirthdateDay;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeBirthdateMonth;
APPKIT_EXTERN API_AVAILABLE(macos(14.0)) NSTextContentType const NSTextContentTypeBirthdateYear;

@protocol NSTextContent
@property (nullable, copy) NSTextContentType contentType API_AVAILABLE(macos(11.0));
@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
