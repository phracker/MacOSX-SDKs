//
//  SKError.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN NSString * const SKErrorDomain NS_AVAILABLE(10_7, 3_0);

// error codes for the SKErrorDomain
typedef NS_ENUM(NSInteger,SKErrorCode) {
    SKErrorUnknown,
    SKErrorClientInvalid,                                                     // client is not allowed to issue the request, etc.
    SKErrorPaymentCancelled,                                                  // user cancelled the request, etc.
    SKErrorPaymentInvalid,                                                    // purchase identifier was invalid, etc.
    SKErrorPaymentNotAllowed,                                                 // this device is not allowed to make the payment
    SKErrorStoreProductNotAvailable NS_ENUM_AVAILABLE(NA, 3_0),               // Product is not available in the current storefront
    SKErrorCloudServicePermissionDenied NS_ENUM_AVAILABLE(NA, 9_3),           // user has not allowed access to cloud service information
    SKErrorCloudServiceNetworkConnectionFailed NS_ENUM_AVAILABLE(NA, 9_3),    // the device could not connect to the nework
    SKErrorCloudServiceRevoked NS_ENUM_AVAILABLE(NA, 10_3),                   // user has revoked permission to use this cloud service
};

NS_ASSUME_NONNULL_END
