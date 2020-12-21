//
//  CPInformationTemplate.h
//  CarPlay
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <CarPlay/CPTextButton.h>
#import <CarPlay/CPTemplate.h>
#import <CarPlay/CPInformationItem.h>
#import <CarPlay/CPInformationRatingItem.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CPInformationTemplateLayout) {
    /**
     A layout that will align all items on the leading edge of the template.
     */
    CPInformationTemplateLayoutLeading = 0,
    /**
     A layout that will split each item into two columns.
     */
    CPInformationTemplateLayoutTwoColumn,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos);

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPInformationTemplate : CPTemplate

/**
 Initialize a CPInformationTemplate with a title, optional labels, and optional action buttons.

 @param layout Information template layout, either leading aligned or two columns
 @param title Information template title, appears at the top of the template
 @param items Information items that will appear in the template
 @param actions Optional actions that appear at the bottom of the template

 @note The maximum number of @c CPInformationItem is 10. If you specify more than 10 items, only the first 10 will be used.
       The maximum number of @c CPTextButton is 3. If you specify more than 3, only the first 3 will be used.
*/
- (instancetype)initWithTitle:(NSString *)title
                       layout:(CPInformationTemplateLayout)layout
                        items:(NSArray<__kindof CPInformationItem *> *)items
                      actions:(NSArray<CPTextButton *> *)actions NS_DESIGNATED_INITIALIZER;

/**
 Information template layout, either leading aligned or two columns.
 */
@property (nonatomic, readonly) CPInformationTemplateLayout layout;

/**
 Title that will appear at the top of the template.
 */
@property (nonatomic, copy) NSString *title;

/**
 An array of @c CPInformationItem.
 
 To update the items appearing in this information template, assign a new array to this property.
 
 @note The maximum number of items is 10. If you specify more than 10 items, only the first 10 will be used.
 */
@property (nonatomic, copy) NSArray<__kindof CPInformationItem *> *items;

/**
 An array of actions that appear at the bottom of the template.
 
 To update the actions appearing in this information template, assign a new array to this property.
 
 @note The maximum number of actions is 3. If you specify more than 3, only the first 3 will be used.
*/
@property (nonatomic, copy) NSArray<__kindof CPTextButton *> *actions;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
