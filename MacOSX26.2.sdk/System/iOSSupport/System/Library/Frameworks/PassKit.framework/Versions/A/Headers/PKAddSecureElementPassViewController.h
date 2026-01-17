#if !__has_include(<PassKitUI/PKAddSecureElementPassViewController.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKAddSecureElementPassViewController.h
//    PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <TargetConditionals.h>

#if TARGET_OS_IOS

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class PKSecureElementPass;
@class PKAddSecureElementPassConfiguration;
@class PKAddSecureElementPassViewController;

API_AVAILABLE(ios(13.4))
@protocol PKAddSecureElementPassViewControllerDelegate <NSObject>

@optional
- (void)addSecureElementPassViewController:(PKAddSecureElementPassViewController *)controller
          didFinishAddingSecureElementPass:(nullable PKSecureElementPass *)pass
                                     error:(nullable NSError *)error API_DEPRECATED("Use addSecureElementPassViewController:didFinishAddingSecureElementPasses:error: instead", ios(13.4, 14.0));

@required
- (void)addSecureElementPassViewController:(PKAddSecureElementPassViewController *)controller
        didFinishAddingSecureElementPasses:(nullable NSArray<PKSecureElementPass *> *)passes
                                     error:(nullable NSError *)error;
@end

API_AVAILABLE(ios(13.4))
@interface PKAddSecureElementPassViewController : UIViewController

+ (BOOL)canAddSecureElementPassWithConfiguration:(PKAddSecureElementPassConfiguration *)configuration NS_SWIFT_NAME(canAddSecureElementPass(configuration:));

- (nullable instancetype)initWithConfiguration:(PKAddSecureElementPassConfiguration *)configuration
                                      delegate:(nullable id<PKAddSecureElementPassViewControllerDelegate>)delegate;

@property (nonatomic, weak, nullable) id<PKAddSecureElementPassViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END

#endif // TARGET_OS_IOS

#else
#if !TARGET_OS_OSX 
#import <TargetConditionals.h>
#import <PassKitUI/PKAddSecureElementPassViewController.h>
#endif
#endif