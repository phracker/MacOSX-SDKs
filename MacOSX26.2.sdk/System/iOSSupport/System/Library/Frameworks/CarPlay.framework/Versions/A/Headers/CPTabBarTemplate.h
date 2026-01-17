//
//  CPTabBarTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CPTabBarTemplateDelegate;

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPTabBarTemplate : CPTemplate

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Initialize the tab bar with an array of templates. Each template in the array
 becomes a tab on the tab bar.
 
 The maximum number of tabs in the tab bar template is given by @c maximumTabCount.
 */
- (instancetype)initWithTemplates:(NSArray <__kindof CPTemplate *> *)templates;

/**
 The tab bar delegate is informed of tab bar events, like selecting a tab.
 */
@property (nullable, nonatomic, weak) id<CPTabBarTemplateDelegate> delegate;

/**
 The maximum number of tabs that your app may display in a @c CPTabBarTemplate,
 depending on the entitlements that your app declares.
 
 @warning The system will throw an exception if your app attempts to display more
 than this number of tabs in your tab bar template.
 */
@property (nonatomic, class, readonly) NSInteger maximumTabCount;

/**
 The currently-visible templates in the tab bar. Each template corresponds to
 a single tab on the tab bar.
 */
@property (nonatomic, strong, readonly) NSArray <__kindof CPTemplate *> *templates;

/**
 The currently-selected template in the tab bar.
 */
@property (nonatomic, strong, readonly, nullable) __kindof CPTemplate *selectedTemplate;

/**
 Update the tabs displayed in this tab bar, replacing the currently-visible tabs.
 Each template in the array becomes a tab on the tab bar.
 */
- (void)updateTemplates:(NSArray <__kindof CPTemplate *> *)newTemplates;

/**
 Update the currently-selected tab in this tab bar template, switching to the first tab
 that is currently hosting @c newTemplate.
 
 @param newTemplate The template that should become selected in the tab bar.
 */
- (void)selectTemplate:(CPTemplate *)newTemplate NS_SWIFT_NAME(select(_:)) API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos);

/**
 Update the currently-selected tab in this tab bar template, switching to the tab
 at the specified index.
 
 @param index The index of the tab to select. This must be less than the number
 of tabs in this tab bar template.
 */
- (void)selectTemplateAtIndex:(NSInteger)index NS_SWIFT_NAME(selectTemplate(at:)) API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos);

@end

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
CARPLAY_TEMPLATE_UI_ACTOR
@protocol CPTabBarTemplateDelegate <NSObject>

/**
 The user has selected one of the tabs in the tab bar template, bringing the selected template to the foreground.
 */
- (void)tabBarTemplate:(CPTabBarTemplate *)tabBarTemplate didSelectTemplate:(__kindof CPTemplate *)selectedTemplate;

@end

NS_ASSUME_NONNULL_END
