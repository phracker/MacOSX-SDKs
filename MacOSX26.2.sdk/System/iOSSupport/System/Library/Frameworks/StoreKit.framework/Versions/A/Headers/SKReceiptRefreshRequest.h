//
//  SKReceiptRefreshRequest.h
//  StoreKit
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/SKRequest.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS
API_DEPRECATED("Use Transaction.all and AppTransaction.shared.", ios(7.0, 18.0), macos(10.9, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0))
NS_SWIFT_NONSENDABLE
@interface SKReceiptRefreshRequest : SKRequest {
@private
    NSDictionary *_properties;
}

- (instancetype)initWithReceiptProperties:(nullable NSDictionary<NSString *, id> *)properties;
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *receiptProperties;

@end

SK_EXTERN void SKTerminateForInvalidReceipt(void) API_AVAILABLE(ios(7.1), macos(10.14), watchos(6.2), visionos(1.0));

// Receipt properties for sandbox testing:
SK_EXTERN NSString * const SKReceiptPropertyIsExpired API_DEPRECATED("No longer supported.", ios(7.0, 18.0), macos(10.9, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsRevoked API_DEPRECATED("No longer supported.", ios(7.0, 18.0), macos(10.9, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsVolumePurchase API_DEPRECATED("No longer supported.", ios(7.0, 18.0), macos(10.9, 15.0), watchos(6.2, 11.0), visionos(1.0, 2.0));  // NSNumber BOOL, defaults to NO

NS_ASSUME_NONNULL_END
