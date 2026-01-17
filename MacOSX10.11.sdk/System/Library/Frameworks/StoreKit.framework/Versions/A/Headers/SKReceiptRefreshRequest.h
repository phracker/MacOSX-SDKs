//
//  SKReceiptRefreshRequest.h
//  StoreKit
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/SKRequest.h>
#import <StoreKit/StoreKitDefines.h>

NS_CLASS_AVAILABLE(10_9, NA)
NS_ASSUME_NONNULL_BEGIN
@interface SKReceiptRefreshRequest : SKRequest
{
    NSDictionary *_properties;
}
- (nullable id)initWithReceiptProperties:(NSDictionary<NSString *, id> *)properties;
@property (nullable, nonatomic, readonly) NSDictionary<NSString *, id> *receiptProperties;

@end


// Receipt properties for sandbox testing:
SK_EXTERN NSString * const SKReceiptPropertyIsExpired;  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsRevoked;  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsVolumePurchase;  // NSNumber BOOL, defaults to NO
NS_ASSUME_NONNULL_END
