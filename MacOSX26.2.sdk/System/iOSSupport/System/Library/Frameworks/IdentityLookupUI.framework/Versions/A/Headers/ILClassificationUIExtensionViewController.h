//
//  ILClassificationUIExtensionViewController.h
//  IdentityLookupUI
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class ILClassificationUIExtensionContext;
@class ILClassificationResponse;
@class ILClassificationRequest;

/// Represents a view controller to subclass for displaying classification UI
IL_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(13.0)) API_UNAVAILABLE( macos, tvos, watchos)
@interface ILClassificationUIExtensionViewController : UIViewController

/// The extension context to use for completing the classification request
@property (nonatomic, readonly, strong) ILClassificationUIExtensionContext *extensionContext;

/// Override to customize UI based on the classification request before the view is loaded
- (void)prepareForClassificationRequest:(__kindof ILClassificationRequest *)request;

/// Override to provide a classification response for the classification request
- (ILClassificationResponse *)classificationResponseForRequest:(__kindof ILClassificationRequest *)request;

@end

NS_ASSUME_NONNULL_END
