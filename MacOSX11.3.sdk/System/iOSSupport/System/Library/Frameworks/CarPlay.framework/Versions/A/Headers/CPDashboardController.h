//
//  CPDashboardController.h
//  CarPlay
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CPDashboardButton;

API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPDashboardController : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 An array of dashboard buttons to be displayed on the dashboard widget.
 @note The dashboard controller may display a maximum of 2 buttons. Setting more than 2 buttons to this
 property will only display the first 2 buttons. The system will manage hiding and showing these buttons when
 navigation is active or inactive.
 */
@property (nonatomic, copy) NSArray<CPDashboardButton *> *shortcutButtons;

@end

NS_ASSUME_NONNULL_END
