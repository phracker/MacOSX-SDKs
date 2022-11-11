//
//  CPWindow.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class CPTemplateApplicationScene;

/**
 @c CPWindow is the main window for content presented on the car screen.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPWindow : UIWindow

/**
 @c mapButtonSafeAreaLayoutGuide can be used to layout content that appears above the map buttons presented on the map template.
 */
@property (nonatomic, readonly) UILayoutGuide *mapButtonSafeAreaLayoutGuide;

/**
 @c windowScene is not available for CPWindow's
 */
@property(nullable, nonatomic, weak) UIWindowScene *windowScene NS_UNAVAILABLE;

/**
 @c back-reference to the CPTemplateApplicationScene containing this CPWindow
 */
@property(nullable, nonatomic, weak) CPTemplateApplicationScene *templateApplicationScene;

@end

NS_ASSUME_NONNULL_END
