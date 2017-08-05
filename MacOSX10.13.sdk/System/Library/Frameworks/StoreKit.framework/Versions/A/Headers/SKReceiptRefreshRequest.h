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

SK_EXTERN_CLASS_AVAILABLE(10_9)
@interface SKReceiptRefreshRequest : SKRequest
{
    NSDictionary *_properties;
}

- (instancetype)initWithReceiptProperties:(nullable NSDictionary<NSString *, id> *)properties NS_AVAILABLE_MAC(10_9);

@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *receiptProperties NS_AVAILABLE_MAC(10_9);

@end


// Receipt properties for sandbox testing:
SK_EXTERN NSString * const SKReceiptPropertyIsExpired  NS_AVAILABLE_MAC(10_9);  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsRevoked  NS_AVAILABLE_MAC(10_9);  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsVolumePurchase  NS_AVAILABLE_MAC(10_9);  // NSNumber BOOL, defaults to NO

NS_ASSUME_NONNULL_END
