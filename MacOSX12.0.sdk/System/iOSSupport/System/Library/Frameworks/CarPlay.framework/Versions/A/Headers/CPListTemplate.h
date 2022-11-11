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

/*
 Actions that Siri will perform when users select the assistant cell.
 
 These actions require that your app supports the required SiriKit intents, and your app is of a supporting category.
 For CarPlay audio apps, this is limited to INPlayMediaIntent. For CarPlay communication apps, this is INStartCallIntent.
 */
typedef NS_ENUM(NSInteger, CPAssistantCellActionType) {
    CPAssistantCellActionTypePlayMedia = 0,
    CPAssistantCellActionTypeStartCall,
} API_AVAILABLE(ios(15.0));

/*
 Visibility of the Assistant Cell
 */
typedef NS_ENUM(NSInteger, CPAssistantCellVisibility) {
    CPAssistantCellVisibilityOff = 0,               // The list template will render without an assistant cell.
    CPAssistantCellVisibilityWhileLimitedUIActive,  // The list template will render with an assistant cell, only while Limited UI is active.
    CPAssistantCellVisibilityAlways,                // the list template will render with an assistant cell at all times.
} API_AVAILABLE(ios(15.0));

/*
 Position of the Assistant Cell
 */
typedef NS_ENUM(NSInteger, CPAssistantCellPosition) {
    CPAssistantCellPositionTop = 0, // The list template will display the assistant cell at the top of all visible cells.
    CPAssistantCellPositionBottom,  // The list template will display the assistant cell at the bottom of all visible cells.
} API_AVAILABLE(ios(15.0));

@protocol CPListTemplateDelegate;
@class CPListItem;

API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, watchos, tvos)
/**
 @c CPAssistantCellConfiguration encapsulates the configuration options for your assistant cell.
  
 @note The Assistant Cell is only supported by CarPlay Audio and Communication apps.
*/
@interface CPAssistantCellConfiguration : NSObject <NSSecureCoding>

/**
 Initialize an Assistant Cell Configuration with a position, visibility, and action representing the SiriKit intent that should be invoked when users select the assistant cell.
 */
- (instancetype)initWithPosition:(CPAssistantCellPosition)position visibility:(CPAssistantCellVisibility)visibility assistantAction:(CPAssistantCellActionType)assistantAction;

/**
 The position of the Assistant Cell.
 
 @note The default value of this property is @c CPAssistantCellPositionTop.
 */
@property (nonatomic, readonly) CPAssistantCellPosition position;

/**
 The visibility of the Assistant Cell.
 
 @note The default value of this property is @c CPAssistantCellVisibilityOff.
 */
@property (nonatomic, readonly) CPAssistantCellVisibility visibility;

/**
 The action that Siri will perform when users select the assistant cell.
 */
@property (nonatomic, readonly) CPAssistantCellActionType assistantAction;

@end

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
 Initialize a list template with one or more sections of items, an optional title, and configuration for the assistant cell via a @c CPAssistantCellConfiguration object.
 
 @note The Assistant Cell is only supported by CarPlay Audio and Communication Apps.
 
 @discussion Unlike @c CPListItem, your application will not receive a callback when the user selects the cell.
 Instead, configure an Intents app extention to receive user requests from SiriKit, in order to turn the requests into an
 app-specific actions.
 */
- (instancetype)initWithTitle:(nullable NSString *)title
                     sections:(NSArray <CPListSection *> *)sections
   assistantCellConfiguration:(nullable CPAssistantCellConfiguration *)assistantCellConfiguration API_AVAILABLE(ios(15.0));

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

#pragma mark - Assistant Cell

/**
 The configuration of the Assistant Cell.

 Assigning to this property will dynamically update the List Template to reflect the visibility, position, and intent identifier of the Assistant Cell.

 @note The Assistant Cell is only supported by CarPlay Audio and Communication Apps.
 
 @discussion Unlike @c CPListItem, your application will not receive a callback when the user selects the cell.
 Instead, configure an Intents app extention to receive user requests from SiriKit, in order to turn the requests into an
 app-specific actions.
 */
@property (nonatomic, nullable, strong) CPAssistantCellConfiguration *assistantCellConfiguration API_AVAILABLE(ios(15.0));

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
