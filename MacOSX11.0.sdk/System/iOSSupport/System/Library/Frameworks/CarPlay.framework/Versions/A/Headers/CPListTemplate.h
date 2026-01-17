//
//  CPListTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPBarButtonProviding.h>
#import <CarPlay/CPListItemTypes.h>
#import <CarPlay/CPListSection.h>
#import <CarPlay/CPTemplate.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CPListTemplateDelegate;
@class CPListItem;

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPListTemplate : CPTemplate <CPBarButtonProviding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Initialize a list template with one or more sections of items and an optional title.
 */
- (instancetype)initWithTitle:(nullable NSString *)title
                     sections:(NSArray <CPListSection *> *)sections;

/**
 The list template's delegate is informed of list selection events.
 */
@property (nullable, nonatomic, weak) id<CPListTemplateDelegate> delegate API_DEPRECATED_WITH_REPLACEMENT("-[CPListItem handler]", ios(12.0, 14.0));

/**
 The maximum number of items, across all sections, that may appear in a @c CPListTemplate.
 
 @note Your list template will display the first @c maximumItemCount items, across all sections.
 Any items or sections beyond that limit will be trimmed.
 */
@property (nonatomic, class, readonly) NSUInteger maximumItemCount API_AVAILABLE(ios(14.0));

/**
 The maximum number of sections that may appear in a @c CPListTemplate.
 
 @note Your list template will display the first @c maximumSectionCount sections.
 Any sections beyond that limit will be trimmed.
 */
@property (nonatomic, class, readonly) NSUInteger maximumSectionCount API_AVAILABLE(ios(14.0));

/**
 The sections displayed in this list.
 */
@property (nonatomic, readonly, copy) NSArray <CPListSection *> *sections;

/**
 Title shown in the navigation bar while this template is visible.
 */
@property (nullable, nonatomic, readonly, copy) NSString *title;

/**
 Update the list of sections displayed in this list template, reloading
 the table view displaying this list.
 */
- (void)updateSections:(NSArray <CPListSection *> *)sections;

/**
 The number of sections currently displayed in this list template.
 */
@property (nonatomic, readonly) NSUInteger sectionCount API_AVAILABLE(ios(14.0));

/**
 The number of items currently displayed in this list template, across all sections.
 */
@property (nonatomic, readonly) NSUInteger itemCount API_AVAILABLE(ios(14.0));

#pragma mark - Item Access

/**
 Return an @c NSIndexPath for the specified item, if it exists in any section
 in this list template, or nil if not found.
 */
- (nullable NSIndexPath *)indexPathForItem:(id <CPListTemplateItem>)item API_AVAILABLE(ios(14.0));

#pragma mark - Empty View

/**
 An optional array of strings, ordered from most to least preferred.
 The variant strings should be provided as localized, displayable content.
 The system will select the first variant that fits the available space.
 
 If the list template does not contain any items (itemCount == 0), then
 the template will display an empty view with a title and subtitle to indicate
 that the template has no list items.
 
 If the list template is updated to contain items, the empty view will be automatically
 removed.
 */
@property (nonatomic, copy) NSArray<NSString *> *emptyViewTitleVariants API_AVAILABLE(ios(14.0));

/**
 An optional array of strings, ordered from most to least preferred.
 The variant strings should be provided as localized, displayable content.
 The system will select the first variant that fits the available space.
 
 If the list template does not contain any items (itemCount == 0), then
 the template will display an empty view with a title and subtitle to indicate
 that the template has no list items.

 If the list template is updated to contain items, the empty view will be automatically
 removed.
 */
@property (nonatomic, copy) NSArray<NSString *> *emptyViewSubtitleVariants API_AVAILABLE(ios(14.0));

@end

API_UNAVAILABLE(macos, watchos, tvos)
API_DEPRECATED_WITH_REPLACEMENT("-[CPListItem handler]", ios(12.0, 14.0))
@protocol CPListTemplateDelegate <NSObject>

/**
 The user has selected an item in the list template.
 
 Your app has an opportunity to perform any necessary operations to prepare for completing
 this item selection. The list template will display a spinner after a short delay.
 
 You must call the completion block after your app has finished loading and updated its UI.
 
 @param listTemplate The list template containing this item
 @param item The item selected by the user
 @param completionHandler A completion block you must call after you have updated your UI.
 */
- (void)listTemplate:(CPListTemplate *)listTemplate didSelectListItem:(CPListItem *)item completionHandler:(void (^)(void))completionHandler API_DEPRECATED_WITH_REPLACEMENT("-[CPListItem handler]", ios(12.0, 14.0));

@end

NS_ASSUME_NONNULL_END
