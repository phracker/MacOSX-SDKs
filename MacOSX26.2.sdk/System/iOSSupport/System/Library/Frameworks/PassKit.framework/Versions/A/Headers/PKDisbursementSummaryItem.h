#if !__has_include(<PassKitCore/PKDisbursementSummaryItem.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKDisbursementSummaryItem.h
//    PassKit
//  Copyright © 2023 Apple, Inc. All rights reserved.
//

#import <PassKit/PKPaymentSummaryItem.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKDisbursementSummaryItem : PKPaymentSummaryItem

@end

NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKDisbursementSummaryItem.h>
#endif