#if !__has_include(<PassKitCore/PKShippingMethod.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKShippingMethod.h
//    PassKit
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PassKit/PKPaymentSummaryItem.h>
#import <PassKit/PKDateComponentsRange.h>

#ifndef __PKSHIPPINGMETHOD_H__
#define __PKSHIPPINGMETHOD_H__

NS_ASSUME_NONNULL_BEGIN

// Defines a shipping method for delivering physical goods.
API_AVAILABLE(ios(8.0), watchos(3.0))
@interface PKShippingMethod : PKPaymentSummaryItem

// Application-defined unique identifier for this shipping method.  The application will receive this
// in paymentAuthorizationViewController:didAuthorizePayment:completion:.
@property (nonatomic, copy, nullable) NSString *identifier;

// Additional localized information about the shipping method, e.g. "Ships in 24 hours" or
// "Arrives Friday April 4."
@property (nonatomic, copy, nullable) NSString *detail;

// Localized date range for this shipping method e.g. "Shipping by May 12 - 19"
// Setting this results in the detail property not being displayed.
@property (nonatomic, copy, nullable) PKDateComponentsRange *dateComponentsRange API_AVAILABLE(ios(15.0), watchos(8.0));

@end

NS_ASSUME_NONNULL_END

#endif // __PKSHIPPINGMETHOD_H__

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKShippingMethod.h>
#endif