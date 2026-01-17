//
//  SFCertificatePresentation.h
//  SecurityUI
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TargetConditionals.h>

#if TARGET_OS_IOS || TARGET_OS_TV || TARGET_OS_VISION
@class UIViewController;
#elif TARGET_OS_OSX
@class NSWindow;
#endif

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(15.4), ios(18.4), tvos(18.4), visionos(2.4)) API_UNAVAILABLE(watchos)
@interface SFCertificatePresentation : NSObject

/// Initialize the certificate presentation with a certificate trust reference.
- (instancetype)initWithTrust:(SecTrustRef)trust NS_DESIGNATED_INITIALIZER;

/// Clients should use designated initializers.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Presents the certificate sheet. A dismiss handler is invoked whent the sheet has dismissed.
#if TARGET_OS_IOS || TARGET_OS_TV || TARGET_OS_VISION
- (void)presentSheetInViewController:(UIViewController *)viewController dismissHandler:(nullable void (^)(void))dismissHandler;
#elif TARGET_OS_OSX
- (void)presentSheetInWindow:(NSWindow *)window dismissHandler:(nullable void (^)(void))dismissHandler;
#endif

/// Dismisses the certificate sheet.
- (void)dismissSheet;

/// A trust reference, previously created with SecTrustCreateWithCertificates (see <Security/SecTrust.h>).
@property (nonatomic, assign, readonly) SecTrustRef trust;

/// Title string to be displayed. If no title is provided, a default title will be used.
@property (nonatomic, copy, nullable) NSString *title;

/// Message string to be displayed. If no message is provided, a default message will be used.
@property (nonatomic, copy, nullable) NSString *message;

/// The URL that will be opened by clicking the "Learn More" button.
@property(nonatomic, copy, nullable) NSURL *helpURL;

@end

NS_ASSUME_NONNULL_END
