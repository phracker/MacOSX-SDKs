//
//  SFSafariViewControllerConfiguration.h
//  SafariServices
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>
#import <UIKit/UIKit.h>

@class SFSafariViewControllerActivityButton;

NS_ASSUME_NONNULL_BEGIN

SF_EXTERN API_AVAILABLE(ios(11.0))
NS_SWIFT_NAME(SFSafariViewController.Configuration)
@interface SFSafariViewControllerConfiguration : NSObject <NSCopying>

/*! @abstract Indicates if SFSafariViewController should automatically show the Reader version of web pages. This will only
    happen when Safari Reader is available on a web page.
 */
@property (nonatomic) BOOL entersReaderIfAvailable;

/*! @abstract Indicates if SFSafariViewController should enable collapsing of the navigation bar and hiding of the bottom toolbar
    when the user scrolls web content.
    @discussion The default value is YES.
 */
@property (nonatomic) BOOL barCollapsingEnabled;

/*! @abstract An additional button to be shown in SFSafariViewController's toolbar. See @link SFSafariViewControllerActivityButton @/link for more details.
 @discussion This allows the user to access powerful functionality from your extension without needing to first show the UIActivityViewController.
 */
@property (nonatomic, nullable, copy) SFSafariViewControllerActivityButton *activityButton API_AVAILABLE(ios(15.0));

@end

NS_ASSUME_NONNULL_END
