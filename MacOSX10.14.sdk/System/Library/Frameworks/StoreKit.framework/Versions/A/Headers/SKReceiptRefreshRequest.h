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

SK_EXTERN_CLASS_AVAILABLE(10_9, 7_0) @interface SKReceiptRefreshRequest : SKRequest {
@private
    NSDictionary *_properties;
}

- (instancetype)initWithReceiptProperties:(nullable NSDictionary<NSString *, id> *)properties NS_AVAILABLE(10_9, 7_0);
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *receiptProperties NS_AVAILABLE(10_9, 7_0);

@end

SK_EXTERN void SKTerminateForInvalidReceipt(void) NS_AVAILABLE(10_14, 7_1);

// Receipt properties for sandbox testing:
SK_EXTERN NSString * const SKReceiptPropertyIsExpired NS_AVAILABLE(10_9, 7_0);  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsRevoked NS_AVAILABLE(10_9, 7_0);  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsVolumePurchase NS_AVAILABLE(10_9, 7_0);  // NSNumber BOOL, defaults to NO

NS_ASSUME_NONNULL_END
