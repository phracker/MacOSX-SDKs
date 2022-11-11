//
//  PKPass.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#ifndef __PKPASS_H
#define __PKPASS_H

#import <PassKit/PKObject.h>

typedef NS_ENUM(NSUInteger, PKPassType) {
    PKPassTypeBarcode,
    PKPassTypeSecureElement API_AVAILABLE(macos(11.0), ios(13.4), watchos(6.2)),
    PKPassTypePayment API_DEPRECATED("Use PKPassTypeSecureElement instead", macos(10.12, API_TO_BE_DEPRECATED), ios(8.0, API_TO_BE_DEPRECATED), watchos(3.0, API_TO_BE_DEPRECATED)) = PKPassTypeSecureElement,
    
    PKPassTypeAny = ~(NSUInteger)0
} API_AVAILABLE(macos(11.0), ios(8.0), watchos(3.0));

@class PKPaymentPass;
@class PKSecureElementPass;

#if TARGET_OS_IPHONE
@class UIImage;
#endif

NS_ASSUME_NONNULL_BEGIN
@interface PKPass : PKObject

- (nullable instancetype)initWithData:(NSData *)data error:(NSError **)error;

@property (nonatomic, assign, readonly) PKPassType           passType API_AVAILABLE(macos(11.0), ios(8.0), watchos(3.0));
@property (nonatomic, readonly, nullable) PKPaymentPass      *paymentPass API_DEPRECATED("Use -[PKPass secureElementPass] instead", macos(11.0, API_TO_BE_DEPRECATED), ios(8.0, API_TO_BE_DEPRECATED), watchos(3.0, API_TO_BE_DEPRECATED));
@property (nonatomic, readonly, nullable) PKSecureElementPass *secureElementPass API_AVAILABLE(macos(11.0), ios(13.4), watchos(6.2));

@property (nonatomic, copy, readonly) NSString               *serialNumber;
@property (nonatomic, copy, readonly) NSString               *passTypeIdentifier;
@property (nonatomic, copy, readonly,nullable) NSURL         *webServiceURL;
@property (nonatomic, copy, readonly,nullable) NSString      *authenticationToken;

#if TARGET_OS_IPHONE
@property (nonatomic, copy, readonly) UIImage                *icon __WATCHOS_PROHIBITED;
#endif

@property (nonatomic, copy, readonly) NSString               *localizedName; // e.g. "Boarding Pass"
@property (nonatomic, copy, readonly) NSString               *localizedDescription; // e.g. "SFO -> LHR"
@property (nonatomic, copy, readonly) NSString               *organizationName; // e.g. "Great Airways"
@property (nonatomic, copy, readonly, nullable) NSDate       *relevantDate; // may be useful for sorting
@property (nonatomic, copy, readonly, nullable) NSDictionary *userInfo API_AVAILABLE(macos(11.0), ios(7.0), watchos(3.0));

@property (nonatomic, copy, readonly, nullable) NSURL *passURL; // open to view pass in Wallet app

@property (nonatomic, assign, readonly, getter=isRemotePass)   BOOL       remotePass API_AVAILABLE(macos(11.0), ios(9.0), watchos(3.0));
@property (nonatomic, copy, readonly)                          NSString   *deviceName API_AVAILABLE(macos(11.0), ios(9.0), watchos(3.0));

- (nullable id)localizedValueForFieldKey:(NSString *)key; // IBOutlet-like; allows access to field data from pass file format

@end
NS_ASSUME_NONNULL_END

#endif // __PKPASS_H
