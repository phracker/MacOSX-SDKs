#if !__has_include(<PassKitCore/PKConstants.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKConstants.h
//    PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef PKCONSTANTS_H
#define PKCONSTANTS_H

typedef NSString * PKEncryptionScheme NS_STRING_ENUM;
extern PKEncryptionScheme const PKEncryptionSchemeECC_V2 API_AVAILABLE(ios(9.0));
extern PKEncryptionScheme const PKEncryptionSchemeRSA_V2 API_AVAILABLE(ios(10.0));

typedef NSString * PKPaymentNetwork NS_EXTENSIBLE_STRING_ENUM;
extern PKPaymentNetwork const PKPaymentNetworkAmex API_AVAILABLE(macos(11.0), ios(8.0), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkBancomat API_DEPRECATED("Use PKPaymentNetworkPagoBancomat instead.", macos(12.0, 14.0), ios(16.0, 17.0), watchos(9.0, 10.0));
extern PKPaymentNetwork const PKPaymentNetworkPagoBancomat API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0));
extern PKPaymentNetwork const PKPaymentNetworkBancontact API_AVAILABLE(macos(12.0), ios(16.0), watchos(9.0));
extern PKPaymentNetwork const PKPaymentNetworkCarteBancaire API_DEPRECATED("Use PKPaymentNetworkCartesBancaires instead.", macos(10.13, 11.0), ios(10.3, 11.0), watchos(3.2, 4.0));
extern PKPaymentNetwork const PKPaymentNetworkCarteBancaires API_DEPRECATED("Use PKPaymentNetworkCartesBancaires instead.", macos(10.13, 11.0), ios(11.0, 11.2), watchos(4.0, 4.2));
extern PKPaymentNetwork const PKPaymentNetworkCartesBancaires API_AVAILABLE(macos(11.0), ios(11.2), watchos(4.2));
extern PKPaymentNetwork const PKPaymentNetworkChinaUnionPay API_AVAILABLE(macos(11.0), ios(9.2), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkDankort API_AVAILABLE(macos(12.1), ios(15.1), watchos(8.1));
extern PKPaymentNetwork const PKPaymentNetworkDiscover API_AVAILABLE(macos(11.0), ios(9.0), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkEftpos API_AVAILABLE(macos(11.0), ios(12.0), watchos(5.0));
extern PKPaymentNetwork const PKPaymentNetworkElectron API_AVAILABLE(macos(11.0), ios(12.0), watchos(5.0));
extern PKPaymentNetwork const PKPaymentNetworkElo API_AVAILABLE(macos(11.0), ios(12.1.1), watchos(5.1.2));
extern PKPaymentNetwork const PKPaymentNetworkIDCredit API_AVAILABLE(macos(11.0), ios(10.3), watchos(3.2));
extern PKPaymentNetwork const PKPaymentNetworkInterac API_AVAILABLE(macos(11.0), ios(9.2), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkJCB API_AVAILABLE(macos(11.0), ios(10.1), watchos(3.1));
extern PKPaymentNetwork const PKPaymentNetworkMada API_AVAILABLE(macos(11.0), ios(12.1.1), watchos(5.1.2));
extern PKPaymentNetwork const PKPaymentNetworkMaestro API_AVAILABLE(macos(11.0), ios(12.0), watchos(5.0));
extern PKPaymentNetwork const PKPaymentNetworkMasterCard API_AVAILABLE(macos(11.0), ios(8.0), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkMir API_AVAILABLE(macos(11.5), ios(14.5), watchos(7.5));
extern PKPaymentNetwork const PKPaymentNetworkPrivateLabel API_AVAILABLE(macos(11.0), ios(9.0), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkQuicPay API_AVAILABLE(macos(11.0), ios(10.3), watchos(3.2));
extern PKPaymentNetwork const PKPaymentNetworkSuica API_AVAILABLE(macos(11.0), ios(10.1), watchos(3.1));
extern PKPaymentNetwork const PKPaymentNetworkVisa API_AVAILABLE(macos(11.0), ios(8.0), watchos(3.0));
extern PKPaymentNetwork const PKPaymentNetworkVPay API_AVAILABLE(macos(11.0), ios(12.0), watchos(5.0));
extern PKPaymentNetwork const PKPaymentNetworkBarcode API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0));
extern PKPaymentNetwork const PKPaymentNetworkGirocard API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0));
extern PKPaymentNetwork const PKPaymentNetworkWaon API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0));
extern PKPaymentNetwork const PKPaymentNetworkNanaco API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0));
extern PKPaymentNetwork const PKPaymentNetworkPostFinance API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4));
extern PKPaymentNetwork const PKPaymentNetworkTmoney API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0));
extern PKPaymentNetwork const PKPaymentNetworkMeeza API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4));
extern PKPaymentNetwork const PKPaymentNetworkNAPAS API_AVAILABLE(macos(14.5), ios(17.5), watchos(10.5));
extern PKPaymentNetwork const PKPaymentNetworkBankAxept API_AVAILABLE(macos(14.5), ios(17.5), watchos(10.5));
extern PKPaymentNetwork const PKPaymentNetworkHimyan API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4));
extern PKPaymentNetwork const PKPaymentNetworkJaywan API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4));
extern PKPaymentNetwork const PKPaymentNetworkMyDebit API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0));
extern PKPaymentNetwork const PKPaymentNetworkConecs API_AVAILABLE(macos(26.2), ios(26.2), watchos(26.2));

typedef NSString * PKContactField NS_STRING_ENUM;
extern PKContactField const PKContactFieldPostalAddress API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0));
extern PKContactField const PKContactFieldEmailAddress  API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0));
extern PKContactField const PKContactFieldPhoneNumber   API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0));
extern PKContactField const PKContactFieldName          API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0));
extern PKContactField const PKContactFieldPhoneticName  API_AVAILABLE(macos(11.0), ios(11.0), watchos(4.0));

typedef NS_ENUM(NSInteger, PKPaymentAuthorizationStatus) {
    PKPaymentAuthorizationStatusSuccess, // Merchant auth'd (or expects to auth) the transaction successfully.
    PKPaymentAuthorizationStatusFailure, // Merchant failed to auth the transaction.

    PKPaymentAuthorizationStatusInvalidBillingPostalAddress API_DEPRECATED("Use PKPaymentAuthorizationResult with PKPaymentAuthorizationStatusFailure and include the result of -paymentBillingAddressInvalidErrorWithKey:localizedDescription: in the errors array.", ios(8.0, 11.0), watchos(3.0, 4.0)),  // Supplied billing address is insufficient or otherwise invalid
    PKPaymentAuthorizationStatusInvalidShippingPostalAddress API_DEPRECATED("Use PKPaymentAuthorizationResult with PKPaymentAuthorizationStatusFailure and include the result of -paymentShippingAddressInvalidErrorWithKey:localizedDescription: in the errors array.", ios(8.0, 11.0), watchos(3.0, 4.0)), // Supplied postal address is insufficient or otherwise invalid
    PKPaymentAuthorizationStatusInvalidShippingContact API_DEPRECATED("Use PKPaymentAuthorizationResult with PKPaymentAuthorizationStatusFailure and include the result of -paymentContactInvalidErrorWithContactField:localizedDescription: in the errors array.", ios(8.0, 11.0), watchos(3.0, 4.0)), // Supplied contact information is insufficient or otherwise invalid

    PKPaymentAuthorizationStatusPINRequired API_AVAILABLE(macos(11.0), ios(9.2), watchos(3.0)),  // Transaction requires PIN entry.
    PKPaymentAuthorizationStatusPINIncorrect API_AVAILABLE(macos(11.0), ios(9.2), watchos(3.0)), // PIN was not entered correctly, retry.
    PKPaymentAuthorizationStatusPINLockout API_AVAILABLE(macos(11.0), ios(9.2), watchos(3.0)),    // PIN retry limit exceeded.
} API_AVAILABLE(macos(11.0), ios(8.0), watchos(3.0));

typedef NS_ENUM(NSInteger, PKPaymentButtonStyle) {
    PKPaymentButtonStyleWhite = 0,
    PKPaymentButtonStyleWhiteOutline,
    PKPaymentButtonStyleBlack,
    PKPaymentButtonStyleAutomatic API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0)) // Automatically switches appearance based on the user interface style
} API_AVAILABLE(macos(11.0), ios(8.3), watchos(3.0));

typedef NS_ENUM(NSInteger, PKPaymentButtonType) {
    PKPaymentButtonTypePlain = 0,
    PKPaymentButtonTypeBuy,
    PKPaymentButtonTypeSetUp API_AVAILABLE(macos(11.0), ios(9.0), watchos(3.0)),
    PKPaymentButtonTypeInStore API_AVAILABLE(macos(11.0), ios(10.0), watchos(3.0)),
    PKPaymentButtonTypeDonate  API_AVAILABLE(macos(11.0), ios(10.2), watchos(3.2)),
    PKPaymentButtonTypeCheckout  API_AVAILABLE(macos(11.0), ios(12.0), watchos(5.0)),
    PKPaymentButtonTypeBook  API_AVAILABLE(macos(11.0), ios(12.0), watchos(5.0)),
    PKPaymentButtonTypeSubscribe  API_AVAILABLE(macos(11.0), ios(12.0), watchos(5.0)),
    PKPaymentButtonTypeReload  API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0)),
    PKPaymentButtonTypeAddMoney  API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0)),
    PKPaymentButtonTypeTopUp  API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0)),
    PKPaymentButtonTypeOrder  API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0)),
    PKPaymentButtonTypeRent  API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0)),
    PKPaymentButtonTypeSupport  API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0)),
    PKPaymentButtonTypeContribute  API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0)),
    PKPaymentButtonTypeTip  API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0)),
    PKPaymentButtonTypeContinue  API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0))
} API_AVAILABLE(macos(11.0), ios(8.3), watchos(3.0));

typedef NS_OPTIONS(NSUInteger, PKRadioTechnology) {
    PKRadioTechnologyNone        = 0,
    PKRadioTechnologyNFC         = 1 << 0,
    PKRadioTechnologyBluetooth   = 1 << 1,
} API_AVAILABLE(ios(14.5), watchos(7.3));

#endif // PKCONSTANTS_H

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKConstants.h>
#endif