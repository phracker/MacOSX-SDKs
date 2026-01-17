#if !__has_include(<PassKitUI/PKAddPassesViewController.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKAddPassesViewController.h
//    PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#ifndef __PKADDPASSESVIEWCONTROLLER_H
#define __PKADDPASSESVIEWCONTROLLER_H

#import <TargetConditionals.h>

#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>

@class PKPass;
@class PKAddPassesViewController;

NS_ASSUME_NONNULL_BEGIN

@protocol PKAddPassesViewControllerDelegate <NSObject>
@optional
-(void)addPassesViewControllerDidFinish:(PKAddPassesViewController *)controller; // delegate should dismiss presentation
@end

API_AVAILABLE(ios(6.0))
@interface PKAddPassesViewController : UIViewController

/* controller should be presented with -presentViewController:animated:completion:
 pass should be a pass you want the user to add.
 */
- (nullable instancetype)initWithPass:(PKPass *)pass;
- (nullable instancetype)initWithPasses:(NSArray<PKPass *> *)passes API_AVAILABLE(ios(7.0));
- (nullable instancetype)initWithIssuerData:(NSData *)issuerData signature:(NSData *)signature error:(NSError **)error API_AVAILABLE(ios(16.4));
+ (BOOL)canAddPasses API_AVAILABLE(ios(8.0));

@property(nonatomic, weak, nullable) id <PKAddPassesViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END

#endif
#endif

#else
#if !TARGET_OS_OSX 
#import <TargetConditionals.h>
#import <PassKitUI/PKAddPassesViewController.h>
#endif
#endif