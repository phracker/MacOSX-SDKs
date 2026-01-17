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

@class UIColor, UISwipeActionsConfiguration;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UICollectionLayoutListAppearance) {
    UICollectionLayoutListAppearancePlain,
    UICollectionLayoutListAppearanceGrouped,
    UICollectionLayoutListAppearanceInsetGrouped API_UNAVAILABLE(tvos),
    UICollectionLayoutListAppearanceSidebar API_UNAVAILABLE(tvos),
    UICollectionLayoutListAppearanceSidebarPlain API_UNAVAILABLE(tvos),
} API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

typedef NS_ENUM(NSInteger, UICollectionLayoutListHeaderMode) {
    UICollectionLayoutListHeaderModeNone, /// No headers are shown
    UICollectionLayoutListHeaderModeSupplementary, /// Uses supplementary views of kind UICollectionElementKindSectionHeader to show headers
    UICollectionLayoutListHeaderModeFirstItemInSection, /// Styles the first item in a section as a header. This is especially useful when using hierarchical data sources to be able to expand and collapse the header.
} API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

typedef NS_ENUM(NSInteger, UICollectionLayoutListFooterMode) {
    UICollectionLayoutListFooterModeNone, /// No footers are shown
    UICollectionLayoutListFooterModeSupplementary, /// Uses supplementary views of kind UICollectionElementKindSectionFooter to show footers
} API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));


typedef UISwipeActionsConfiguration *_Nullable (^UICollectionLayoutListSwipeActionsConfigurationProvider)(NSIndexPath *indexPath) API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(tvos);


/// A list configuration can be used to layout a section inside a UICollectionViewCompositionalLayout as a list.
UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0))
@interface UICollectionLayoutListConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithAppearance:(UICollectionLayoutListAppearance)appearance NS_DESIGNATED_INITIALIZER;


// appearance:

/// The overall appearance of the section.
@property (nonatomic, readonly) UICollectionLayoutListAppearance appearance;

/// Whether this section shows separators or not.
@property (nonatomic) BOOL showsSeparators API_UNAVAILABLE(tvos);

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

/// Definies whether the section has a header. Defaults to UICollectionLayoutListHeaderModeNone.
@property (nonatomic) UICollectionLayoutListHeaderMode headerMode;
/// Definies whether the section has a footer. Defaults to UICollectionLayoutListFooterModeNone.
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
