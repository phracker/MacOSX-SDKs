//
//  CPGridTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPBarButtonProviding.h>
#import <CarPlay/CPGridButton.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

extern NSUInteger const CPGridTemplateMaximumItems API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, watchos, tvos);

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPGridTemplate : CPTemplate <CPBarButtonProviding>

/**
 Initialize a grid template with an array of @c CPGridButton and a title.
 
 @param title Title shown in template's navigation bar.
 @param gridButtons A list of grid buttons on the template. The maximum button count is  @c CPGridTemplateMaximumItems.
 
 @note A grid template will only display the first @c CPGridTemplateMaximumItems buttons in the provided @c gridButtons array.
 */
- (instancetype)initWithTitle:(nullable NSString *)title
                  gridButtons:(NSArray<CPGridButton *> *)gridButtons;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Array of grid buttons displayed on the template
 */
@property (nonatomic, readonly) NSArray<CPGridButton *> *gridButtons;

/**
 Update the grid buttons displayed in this template, reloading
 the view displaying these buttons.
 */
- (void)updateGridButtons:(NSArray<CPGridButton *> *)gridButtons API_AVAILABLE(ios(15.0));

/**
 Title shown in template's navigation bar
 */
@property (nonatomic, readonly) NSString *title;

/**
 Update the title displayed in this template.
 */
- (void)updateTitle:(NSString *)title API_AVAILABLE(ios(15.0));

@end

NS_ASSUME_NONNULL_END
