#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICollectionLayoutList.h>)
//
//  UICollectionLayoutList.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UICollectionViewCompositionalLayout.h>
#import <UIKit/UIKitDefines.h>

@class UIColor, UISwipeActionsConfiguration, UIListSeparatorConfiguration;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UICollectionLayoutListAppearance) {
    UICollectionLayoutListAppearancePlain,
    UICollectionLayoutListAppearanceGrouped,
    UICollectionLayoutListAppearanceInsetGrouped API_UNAVAILABLE(tvos),
    UICollectionLayoutListAppearanceSidebar API_UNAVAILABLE(tvos),
    UICollectionLayoutListAppearanceSidebarPlain API_UNAVAILABLE(tvos),
} API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

typedef NS_ENUM(NSInteger, UICollectionLayoutListHeaderMode) {
    /// No headers are shown
    UICollectionLayoutListHeaderModeNone,
    
    /// Uses supplementary views of kind UICollectionElementKindSectionHeader to show headers
    UICollectionLayoutListHeaderModeSupplementary,
    
    /// Styles the first item in a section as a header. This is especially useful when using hierarchical data sources to be able to expand and collapse the header.
    UICollectionLayoutListHeaderModeFirstItemInSection,
} API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

typedef NS_ENUM(NSInteger, UICollectionLayoutListFooterMode) {
    /// No footers are shown
    UICollectionLayoutListFooterModeNone,
    
    /// Uses supplementary views of kind UICollectionElementKindSectionFooter to show footers
    UICollectionLayoutListFooterModeSupplementary,
} API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));


typedef UISwipeActionsConfiguration *_Nullable (^UICollectionLayoutListSwipeActionsConfigurationProvider)(NSIndexPath *indexPath) API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(tvos);

/// A block that is executed by list sections to provide granular control over separator appearance.
///
/// @param itemIndexPath The index path of the item for which separators are being configured.
/// @param sectionSeparatorConfiguration The list section's separator configuration for this cell. This configuration contains
/// the values for separator visibility and insets according to the current state of the item.
///
/// @return The configuration to use for separators at \c itemIndexPath.
typedef UIListSeparatorConfiguration *_Nonnull (^UICollectionLayoutListItemSeparatorHandler)(NSIndexPath *_Nonnull indexPath, UIListSeparatorConfiguration *_Nonnull sectionSeparatorConfiguration) API_AVAILABLE(ios(14.5), watchos(7.4)) API_UNAVAILABLE(tvos);


/// A list configuration can be used to layout a section inside a UICollectionViewCompositionalLayout as a list.
UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0))
@interface UICollectionLayoutListConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithAppearance:(UICollectionLayoutListAppearance)appearance NS_DESIGNATED_INITIALIZER;


// appearance:

/// The overall appearance of the section.
@property (nonatomic, readonly) UICollectionLayoutListAppearance appearance;

/// Whether this section shows separators or not. For additional control, see separatorConfiguration.
/// Note that when this property is NO, the separatorConfiguration is ineffective.
@property (nonatomic) BOOL showsSeparators API_UNAVAILABLE(tvos);

/// The preferred configuration for separators. Used as a baseline for a section in a list using this \c UICollectionLayoutListConfiguration
@property (nonatomic, copy) UIListSeparatorConfiguration *separatorConfiguration API_AVAILABLE(ios(14.5), watchos(7.4)) API_UNAVAILABLE(tvos);

/// This handler is executed when the list section is configuring separator appearance for an item. The index path for the item being configured and
/// a resolved separator configuration are passed in to this block. The configuration returned from this block will be treated as the final
/// separator configuration for this item.
@property (nonatomic, copy, nullable) UICollectionLayoutListItemSeparatorHandler itemSeparatorHandler API_AVAILABLE(ios(14.5), watchos(7.4)) API_UNAVAILABLE(tvos);

/// The background color of the section.
/// Defaults to nil, indicating the system background color for the specified appearance is used.
@property (nonatomic, nullable, strong) UIColor *backgroundColor;


// swipe actions:

/// Called when list is about to show leading swipe actions for a particular index path.
/// Return either a UISwipeActionsConfiguration object or nil if this index path does not show swipe actions.
@property (nonatomic, copy, nullable) UICollectionLayoutListSwipeActionsConfigurationProvider leadingSwipeActionsConfigurationProvider API_UNAVAILABLE(tvos);

/// Called when list is about to show trailing swipe actions for a particular index path.
/// Return either a UISwipeActionsConfiguration object or nil if this index path does not show swipe actions.
@property (nonatomic, copy, nullable) UICollectionLayoutListSwipeActionsConfigurationProvider trailingSwipeActionsConfigurationProvider API_UNAVAILABLE(tvos);


// headers & footers:

/// Defines whether the section has a header. Defaults to UICollectionLayoutListHeaderModeNone.
@property (nonatomic) UICollectionLayoutListHeaderMode headerMode;
/// Defines whether the section has a footer. Defaults to UICollectionLayoutListFooterModeNone.
@property (nonatomic) UICollectionLayoutListFooterMode footerMode;

@end


@interface NSCollectionLayoutSection (UICollectionLayoutListSection)

/// Creates a list section using the specified configuration. You should pass the layoutEnvironment from inside the UICollectionViewCompositionalLayoutSectionProvider.
+ (instancetype)sectionWithListConfiguration:(UICollectionLayoutListConfiguration *)configuration layoutEnvironment:(id<NSCollectionLayoutEnvironment>)layoutEnvironment API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

@end


@interface UICollectionViewCompositionalLayout (UICollectionLayoutListSection)

/// Creates a compositional layout containing only list sections of the specified configuration.
+ (instancetype)layoutWithListConfiguration:(UICollectionLayoutListConfiguration *)configuration API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UICollectionLayoutList.h>
#endif
