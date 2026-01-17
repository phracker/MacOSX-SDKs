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
@interface SKReceiptRefreshRequest : SKRequest
{
    NSDictionary *_properties;
}
- (id)initWithReceiptProperties:(NSDictionary *)properties;
@property (nonatomic, readonly) NSDictionary *receiptProperties;

@end


// Receipt properties for sandbox testing:
SK_EXTERN NSString * const SKReceiptPropertyIsExpired;  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsRevoked;  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsVolumePurchase;  // NSNumber BOOL, defaults to NO
