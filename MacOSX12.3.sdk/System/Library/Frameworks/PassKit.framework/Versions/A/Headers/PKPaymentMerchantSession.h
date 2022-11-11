//
//  PKPaymentMerchantSession.h
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef __PKPAYMENTMERCHANTSESSION_H__
#define __PKPAYMENTMERCHANTSESSION_H__

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0))
@interface PKPaymentMerchantSession : NSObject

- (instancetype)initWithDictionary:(NSDictionary *)dictionary;

@end

NS_ASSUME_NONNULL_END

#endif // __PKPAYMENTMERCHANTSESSION_H__
