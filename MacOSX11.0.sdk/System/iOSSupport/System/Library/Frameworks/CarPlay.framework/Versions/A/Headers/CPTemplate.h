//
//  CPTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Abstract superclass for a template object.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPTemplate : NSObject <NSSecureCoding>

/**
 Any custom data or an object associated with this template can be stored in this property.
 */
@property (nullable, nonatomic, strong) id userInfo;

#pragma mark - Tabs

/**
 When this template is the first template displayed in a @c CPTabBarTemplate's tab, the tab will inherit
 the @c tabTitle specified in this template.
 
 @note If no @c tabTitle is specified, the tab will inherit the template's title, if any.
 
 @note Your template should specify either a @c tabSystemItem OR both a @c tabImage and @c tabTitle.
 */
@property (nullable, nonatomic, copy) NSString *tabTitle API_AVAILABLE(ios(14.0));

/**
 When this template is the first template displayed in a @c CPTabBarTemplate's tab, the tab will inherit
 the image specified in this template. If a tabSystemItem is also specified, tabImage will take precedence.
 
 @note Your template should specify either a @c tabSystemItem OR both a @c tabImage and @c tabTitle.
 */
@property (nullable, nonatomic, strong) UIImage *tabImage API_AVAILABLE(ios(14.0));

/**
 When this template is the first template displayed in a @c CPTabBarTemplate's tab, the tab will inherit
 the system image AND system title specified in this template.
 
 @note Your template should specify either a @c tabSystemItem OR both a @c tabImage and @c tabTitle.
 */
@property (nonatomic) UITabBarSystemItem tabSystemItem API_AVAILABLE(ios(14.0));

/**
 When this template is the first template displayed in a @c CPTabBarTemplate's tab, the tab may optionally
 display a badge indicator.
 
 @note This defaults to NO. Specify YES to display a badge indicator on this tab.
*/
@property (nonatomic) BOOL showsTabBadge API_AVAILABLE(ios(14.0));

@end

NS_ASSUME_NONNULL_END
