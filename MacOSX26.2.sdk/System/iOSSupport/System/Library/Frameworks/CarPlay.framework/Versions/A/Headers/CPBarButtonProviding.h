//
//  CPBarButtonProviding.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPBarButton.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@protocol CPBarButtonProviding <NSObject>

/**
 An array of bar buttons to be displayed on the leading side of the navigation bar.

 @note The navigation bar may display a maximum of 2 buttons in the leading space.
 Setting more than 2 buttons to this property will only display the first 2 buttons.
 */
@property (nonatomic, strong) NSArray<CPBarButton *> *leadingNavigationBarButtons;

/**
 An array of bar buttons to be displayed on the trailing side of the navigation bar.

 @note The navigation bar may display a maximum of 2 buttons in the trailing space.
 Setting more than 2 buttons to this property will only display the first 2 buttons.
 */
@property (nonatomic, strong) NSArray<CPBarButton *> *trailingNavigationBarButtons;

@property (nonatomic, strong, nullable) CPBarButton *backButton;

@end

NS_ASSUME_NONNULL_END
