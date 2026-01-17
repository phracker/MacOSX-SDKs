//
//  HKHealthStore+UIKit.h
//  HealthKit
//
//  Copyright © 2023 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HealthKit.h>
#import <os/availability.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

#if __has_include(<UIKit/UIViewController.h>)
@interface HKHealthStore (UIKit)

/*!
@property      authorizationViewControllerPresenter
@abstract      The view controller from which HealthKit authorization sheets will be presented
@discussion    This property can be set before requesting authorization or running a query like HKDocumentQuery for a better user-experience. Since this property will ensure to infer the correct hosting view controller to show the authorization sheet.
*/
@property (nonatomic, weak, nullable) UIViewController *authorizationViewControllerPresenter API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos);

@end
#endif
NS_ASSUME_NONNULL_END
