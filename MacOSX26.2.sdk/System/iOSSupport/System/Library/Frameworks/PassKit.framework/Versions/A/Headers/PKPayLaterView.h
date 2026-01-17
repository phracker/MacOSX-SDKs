#if !__has_include(<PassKitUI/PKPayLaterView.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKPayLaterView.h
//    PassKit
//
//  Copyright © 2023 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYLATERVIEW_H
#define __PKPAYLATERVIEW_H

#import <TargetConditionals.h>

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST

#import <UIKit/UIKit.h>
#import <PassKit/PKPayLaterValidator.h>

@class PKPayLaterView;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol PKPayLaterViewDelegate <NSObject>
/// If rendering this view using manual layout, then conform to this protocol to layout the view when PKPayLaterView's height changes.
- (void)payLaterViewDidUpdateHeight:(PKPayLaterView *)view;
@end

API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface PKPayLaterView : UIView

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithFrame:(CGRect)frame NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

/// Constructs a view displaying Pay Later Merchandising information given a configuration
/// - Parameters:
///   - amount: The users bag price or item pricing
///   - currencyCode: The ISO 4217 code for the country or region of the merchant’s principle place of business.
- (instancetype)initWithAmount:(NSDecimalNumber *)amount
                  currencyCode:(NSString *)currencyCode NS_REFINED_FOR_SWIFT;

/// Delegate used to receive callbacks about size changes
@property (nonatomic, assign) id<PKPayLaterViewDelegate> delegate;

/// The users bag price or item pricing
@property (nonatomic, copy) NSDecimalNumber *amount NS_REFINED_FOR_SWIFT;

/// The ISO 4217 code for the country or region of the merchant’s principle place of business.
@property (nonatomic, copy) NSString *currencyCode NS_REFINED_FOR_SWIFT;

/// The kind of Pay Later Merchandising widget look, such as a standalone product item view. Can be badge, plain, price or checkout.
@property (nonatomic, assign) PKPayLaterDisplayStyle displayStyle;

/// The kind of Pay Later Merchandising Modal informational, such as a learnMore modal. Can be learnMore, or calculator. Default is learnMore
@property (nonatomic, assign) PKPayLaterAction action;

@end

NS_ASSUME_NONNULL_END

#endif // TARGET_OS_IOS && !TARGET_OS_MACCATALYST

#endif // __PKPAYLATERVIEW_H

#else
#if !TARGET_OS_OSX 
#import <TargetConditionals.h>
#import <PassKitUI/PKPayLaterView.h>
#endif
#endif