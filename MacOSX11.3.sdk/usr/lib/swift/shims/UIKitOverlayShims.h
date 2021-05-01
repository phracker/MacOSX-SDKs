//===--- UIKitOverlayShims.h ---===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===--------------------===//

#ifndef SWIFT_STDLIB_SHIMS_UIKIT_OVERLAY_H
#define SWIFT_STDLIB_SHIMS_UIKIT_OVERLAY_H

@import UIKit;

#if __has_feature(nullability)
#pragma clang assume_nonnull begin
#endif

#if TARGET_OS_TV || TARGET_OS_IOS
static inline BOOL _swift_UIKit_UIFocusEnvironmentContainsEnvironment(
                                                                      id<UIFocusEnvironment> environment,
                                                                      id<UIFocusEnvironment> otherEnvironment
                                                                      ) API_AVAILABLE(ios(11.0), tvos(11.0)) {
    return [UIFocusSystem environment:environment containsEnvironment:otherEnvironment];
}
#endif // TARGET_OS_TV || TARGET_OS_IOS

#if TARGET_OS_IOS

API_AVAILABLE(ios(13.0))
@interface UICommand()

- (instancetype)initWithTitle:(NSString *)title
                        image:(nullable UIImage *)image
                       action:(SEL)action
                 propertyList:(nullable id)propertyList
                   alternates:(NSArray<UICommandAlternate *> *)alternates
         discoverabilityTitle:(nullable NSString *)discoverabilityTitle
                   attributes:(UIMenuElementAttributes)attributes
                        state:(UIMenuElementState)state NS_REFINED_FOR_SWIFT NS_DESIGNATED_INITIALIZER;

@end

API_AVAILABLE(ios(13.0))
@interface UIKeyCommand()

- (instancetype)initWithTitle:(NSString *)title
                        image:(nullable UIImage *)image
                       action:(SEL)action
                        input:(NSString *)input
                modifierFlags:(UIKeyModifierFlags)modifierFlags
                 propertyList:(nullable id)propertyList
                   alternates:(NSArray<UICommandAlternate *> *)alternates
         discoverabilityTitle:(nullable NSString *)discoverabilityTitle
                   attributes:(UIMenuElementAttributes)style
                        state:(UIMenuElementState)state NS_REFINED_FOR_SWIFT NS_DESIGNATED_INITIALIZER;

@end

#endif // TARGET_OS_IOS

#if __has_feature(nullability)
#pragma clang assume_nonnull end
#endif

//===--------------------===//
// diffable data source     //
//===--------------------===//

#if TARGET_OS_TV || TARGET_OS_IOS

#if __has_feature(nullability)
#pragma clang assume_nonnull begin
#endif

typedef UITableViewCell * _Nullable (^UITableViewDiffableDataSourceCellProvider)(UITableView * _Nonnull, NSIndexPath * _Nonnull, id _Nonnull);
typedef UICollectionViewCell * _Nullable (^UICollectionViewDiffableDataSourceCellProvider)(UICollectionView * _Nonnull,NSIndexPath * _Nonnull, id _Nonnull);

typedef UICollectionViewCell * _Nullable(^UIDiffableDataSourceCollectionViewCellProvider)(UICollectionView*, NSIndexPath *indexPath, id identifier);
typedef UICollectionReusableView * _Nullable(^UIDiffableDataSourceSupplementaryViewProvider)(UICollectionView *, NSString *kind, NSIndexPath *indexPath);

typedef NSString * _Nonnull(^UIDiffableDataSourceCellReuseIdentifierProvider)(id _Nonnull identifier);
typedef void(^UIDiffableDataSourceCollectionViewCellConfigurationHandler)(__kindof UICollectionViewCell  * _Nonnull , id _Nonnull identifier);

typedef NSString * _Nonnull(^UIDiffableDataSourceSupplementaryViewReuseIdentifierProvider)(NSString * _Nonnull kind, NSIndexPath * _Nonnull indexPath);
typedef void(^UIDiffableDataSourceSupplementaryViewConfigurationHandler)(__kindof UICollectionReusableView * _Nonnull, NSString * _Nonnull kind, NSIndexPath * _Nonnull indexPath);

typedef UITableViewCell * _Nullable(^UIDiffableDataSourceTableViewCellProvider)(__kindof UITableView * _Nonnull, NSIndexPath * _Nonnull, id _Nonnull identifier);
typedef void(^UIDiffableDataSourceTableViewCellConfigurationHandler)(__kindof UITableViewCell  * _Nonnull , id _Nonnull identifier);

@class __UIDiffableDataSourceSnapshot;
@class _UIDiffableDataSourceSectionController;
@class _UIDiffableDataSourceItemRenderer;
@protocol _UICollectionViewAnimationContext;
@class _UIDiffableDataSourceTransaction;
@class _UIDiffableDataSourceItemRenderer;

typedef BOOL (^_UIDiffableDataSourceCanReorderItemHandler)(id _Nonnull identifier);
typedef void (^_UIDiffableDataSourceDidReorderItemsHandler)(_UIDiffableDataSourceTransaction  _Nonnull *transaction, NSArray * _Nonnull reorderedItems);
typedef void(^__UIDiffableDataSourceCellObserver)(__kindof UICollectionViewCell * _Nonnull cell, NSIndexPath * _Nonnull indexPath, id _Nonnull identifier);


API_AVAILABLE(ios(13.0), tvos(13.0))
@interface __UIDiffableDataSource : NSObject

- (instancetype)initWithCollectionView:(UICollectionView*)collectionView
                          cellProvider:(UIDiffableDataSourceCollectionViewCellProvider)cellProvider;

- (instancetype)initWithCollectionView:(UICollectionView *)collectionView
                    sectionControllers:(NSArray<_UIDiffableDataSourceSectionController*>*)sectionControllers
            rendererIdentifierProvider:(id  _Nonnull (^)(id _Nonnull))rendererIdentifierProvider;


- (instancetype)initWithCollectionView:(UICollectionView *)collectionView
                         itemRenderers:(NSArray<_UIDiffableDataSourceItemRenderer *> *)itemRenderers
            rendererIdentifierProvider:(id  _Nonnull (^)(id _Nonnull))rendererIdentifierProvider;

- (instancetype)initWithCollectionView:(UICollectionView *)collectionView
                          cellProvider:(UIDiffableDataSourceCollectionViewCellProvider)cellProvider
                            dataSource:(id<UICollectionViewDataSource>)dataSource;

- (instancetype)initWithCollectionView:(UICollectionView*)collectionView
               reuseIdentifierProvider:(UIDiffableDataSourceCellReuseIdentifierProvider)cellReuseProvider
              cellConfigurationHandler:(UIDiffableDataSourceCollectionViewCellConfigurationHandler)cellConfigurationHandler;

- (NSString*)description;       

- (instancetype)initWithTableView:(UITableView*)tableView
                     cellProvider:(UIDiffableDataSourceTableViewCellProvider)cellProvider;

- (instancetype)initWithTableView:(UITableView*)tableView
          reuseIdentifierProvider:(UIDiffableDataSourceCellReuseIdentifierProvider)cellResueProvider
         cellConfigurationHandler:(UIDiffableDataSourceTableViewCellConfigurationHandler)cellConfigurationHandler;

@property(nonatomic) UITableViewRowAnimation tableViewDefaultRowAnimation;
@property(nonatomic,weak,readonly,nullable) UITableView *tableView;
@property(nonatomic,copy) UITableViewDiffableDataSourceCellProvider tableViewCellProvider;

@property(nonatomic,weak,readonly,nullable) UICollectionView *collectionView;
@property(nonatomic,weak,readonly,nullable) UICollectionView *_collectionView;  

@property(nonatomic,nullable,copy) UIDiffableDataSourceSupplementaryViewProvider supplementaryViewProvider;

@property(nonatomic,readonly) NSInteger numberOfItems;
@property(nonatomic,readonly) NSInteger numberOfSections;
@property(nonatomic,readonly) NSArray *sectionIdentifiers;
@property(nonatomic,readonly) NSArray *itemIdentifiers;

- (NSInteger)numberOfItemsInSection:(id)sectionIdentifier;
- (NSArray*)itemIdentifiersInSectionWithIdentifier:(id)sectionIdentifier;
- (nullable id)sectionIdentifierForSectionContainingItemIdentifier:(id)identifier;

- (NSInteger)indexOfItemIdentifier:(id)itemIdentifier;
- (NSInteger)indexOfSectionIdentifier:(id)sectionIdentifier;

- (void)appendItemsWithIdentifiers:(NSArray*)identifiers;
- (void)appendItemsWithIdentifiers:(NSArray*)identifiers intoSectionWithIdentifier:(id _Nullable)sectionIdentifier;

- (void)insertItemsWithIdentifiers:(NSArray*)identifiers beforeItemWithIdentifier:(id)itemIdentifier;
- (void)insertItemsWithIdentifiers:(NSArray*)identifiers afterItemWithIdentifier:(id)itemIdentifier;

- (void)deleteItemsWithIdentifiers:(NSArray*)identifiers;
- (void)deleteAllItems;

- (void)moveItemWithIdentifier:(id)fromIdentifier beforeItemWithIdentifier:(id)toIdentifier;
- (void)moveItemWithIdentifier:(id)fromIdentifier afterItemWithIdentifier:(id)toIdentifier;

- (void)reloadItemsWithIdentifiers:(NSArray*)identifiers;

- (void)appendSectionsWithIdentifiers:(NSArray*)sectionIdentifiers;

- (void)insertSectionsWithIdentifiers:(NSArray*)sectionIdentifiers beforeSectionWithIdentifier:(id)toSectionIdentifier;
- (void)insertSectionsWithIdentifiers:(NSArray*)sectionIdentifiers afterSectionWithIdentifier:(id)toSectionIdentifier;

- (void)deleteSectionsWithIdentifiers:(NSArray*)sectionIdentifiers;

- (void)moveSectionWithIdentifier:(id)fromSectionIdentifier beforeSectionWithIdentifier:(id)toSectionIdentifier;
- (void)moveSectionWithIdentifier:(id)fromSectionIdentifier afterSectionWithIdentifier:(id)toSectionIdentifier;

- (void)reloadSectionsWithIdentifiers:(NSArray*)sectionIdentifiers;


- (nullable id)itemIdentifierForIndexPath:(NSIndexPath*)indexPath;
- (nullable NSIndexPath*)indexPathForItemIdentifier:(id)identifier;


- (__UIDiffableDataSourceSnapshot*)snapshot;
- (__UIDiffableDataSourceSnapshot*)emptySnapshot;
- (void)applyDifferencesFromSnapshot:(__UIDiffableDataSourceSnapshot*)snapshot;
- (void)reloadFromSnapshot:(__UIDiffableDataSourceSnapshot*)snapshot;
- (void)applyDifferencesFromSnapshot:(__UIDiffableDataSourceSnapshot *)snapshot animatingDifferences:(BOOL)animatingDifferences;
- (void)applyDifferencesFromSnapshot:(__UIDiffableDataSourceSnapshot *)snapshot animatingDifferences:(BOOL)animatingDifferences completion:(void(^ _Nullable)(void))completion;

- (void)_applyDifferencesFromSnapshot:(__UIDiffableDataSourceSnapshot *)snapshot customAnimationsProvider:(void(^)(id<_UICollectionViewAnimationContext> _Nonnull))customAnimationsProvider;
- (void)_applyDifferencesFromSnapshot:(__UIDiffableDataSourceSnapshot *)snapshot viewPropertyAnimator:(UIViewPropertyAnimator*)animator customAnimationsProvider:(void(^)(id<_UICollectionViewAnimationContext> _Nonull))customAnimationsProvider;

- (void)appendSectionWithIdentifier:(id)sectionIdentifier;
- (void)insertSectionWithIdentifier:(id)sectionIdentifier beforeSectionWithIdentifier:(id)toSectionIdentifier;
- (void)insertSectionWithIdentifier:(id)sectionIdentifier afterSectionWithIdentifier:(id)toSectionIdentifier;
- (void)applySnapshot:(__UIDiffableDataSourceSnapshot*)snapshot;


@property(nonatomic,nullable,copy) UIDiffableDataSourceSupplementaryViewReuseIdentifierProvider supplementaryReuseIdentifierProvider;
@property(nonatomic,nullable,copy) UIDiffableDataSourceSupplementaryViewConfigurationHandler supplementaryViewConfigurationHandler;

@property(nonatomic,copy) UICollectionViewDiffableDataSourceCellProvider collectionViewCellProvider;
@property(nonatomic,copy) __UIDiffableDataSourceCellObserver cellObserver;

@property(nonatomic,readonly) NSArray<_UIDiffableDataSourceSectionController*> *sectionControllers;

- (void)addAssociatedSectionControllerIfNeeded:(_UIDiffableDataSourceSectionController*)sectionController;
- (nullable _UIDiffableDataSourceSectionController*)associatedSectionControllerForItemIdentifier:(id)itemIdentifier;
- (nullable _UIDiffableDataSourceSectionController*)associatedSectionControllerForSectionIdentifier:(id)sectionIdentifier;

- (NSInteger)_numberOfSectionsForCollectionView:(UICollectionView*)collectionView NS_SWIFT_NAME(_numberOfSectionsForCollectionView(_:));
- (NSInteger)_numberOfItemsInSection:(NSInteger)section collectionView:(UICollectionView*)collectionView NS_SWIFT_NAME(_numberOfItemsInSection(_:collectionView:));
- (UICollectionViewCell*)_cellForItemAtIndexPath:(NSIndexPath*)indexPath collectionView:(UICollectionView*)collectionView NS_SWIFT_NAME(_cellForItemAtIndexPath(_:collectionView:));
- (UICollectionReusableView*)_viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath collectionView:(UICollectionView *)collectionView NS_SWIFT_NAME(_viewForSupplementaryElementOfKind(_:atIndexPath:collectionView:));

- (NSInteger)_numberOfSectionsForTableView:(UITableView*)tableView NS_SWIFT_NAME(_numberOfSectionsForTableView(_:));
- (NSInteger)_numberOfRowsInSection:(NSInteger)section tableView:(UITableView*)tableView NS_SWIFT_NAME(_numberOfRowsInSection(_:tableView:));
- (UITableViewCell*)_cellForRowAtIndexPath:(NSIndexPath*)indexPath tableView:(UITableView*)tableView NS_SWIFT_NAME(_cellForRowAtIndexPath(_:tableView:));

- (NSInteger)_numberOfSectionsForCollectionViewDeprecatedSPI:(UICollectionView*)collectionView NS_SWIFT_NAME(numberOfSections(for:));
- (NSInteger)_numberOfItemsInSectionDeprecatedSPI:(NSInteger)section collectionView:(UICollectionView*)collectionView NS_SWIFT_NAME(numberOfItems(inSection:collectionView:));
- (UICollectionViewCell*)_cellForItemAtIndexPathDeprecatedSPI:(NSIndexPath*)indexPath collectionView:(UICollectionView*)collectionView NS_SWIFT_NAME(cellForItem(at:collectionView:));
- (UICollectionReusableView*)_viewForSupplementaryElementOfKindDeprecatedSPI:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath collectionView:(UICollectionView *)collectionView NS_SWIFT_NAME(viewForSupplementaryElement(ofKind:at:collectionView:));

- (NSInteger)_numberOfSectionsForTableViewDeprecatedSPI:(UITableView*)tableView NS_SWIFT_NAME(numberOfSections(for:));
- (NSInteger)_numberOfRowsInSectionDeprecatedSPI:(NSInteger)section tableView:(UITableView*)tableView NS_SWIFT_NAME(numberOfRows(inSection:tableView:));
- (UITableViewCell*)_cellForRowAtIndexPathDeprecatedSPI:(NSIndexPath*)indexPath tableView:(UITableView*)tableView NS_SWIFT_NAME(cellForRow(at:tableView:));


@property(nonatomic,copy,nullable) void(^willApplySnapshotHandler)(_UIDiffableDataSourceTransaction *transaction);
@property(nonatomic,copy,nullable) void(^didApplySnapshotHandler)(_UIDiffableDataSourceTransaction *transaction);
@property(nonatomic,copy,nullable) _UIDiffableDataSourceCanReorderItemHandler canReorderItemHandler;

- (BOOL)canMoveItemAtIndexPath:(NSIndexPath*)indexPath;
- (void)_commitReorderingForItemAtIndexPath:(NSIndexPath*)sourceIndexPath toDestinationIndexPath:(NSIndexPath*)destinationIndexPath;
@end


API_AVAILABLE(ios(13.0), tvos(13.0))
@interface __UIDiffableDataSourceSnapshot : __UIDiffableDataSource<NSCopying>
- (instancetype)init;
@end

API_AVAILABLE(ios(13.0), tvos(13.0))
@interface NSDiffableDataSourceSnapshot()
@property(nonatomic,readonly) __UIDiffableDataSourceSnapshot *impl;
- (instancetype)initWithDataSource:(__UIDiffableDataSource * _Nullable)dataSource;
@end

#if __has_feature(nullability)
#pragma clang assume_nonnull end
#endif


#endif // TARGET_OS_TV || TARGET_OS_IOS


#if TARGET_OS_IOS

#if __has_feature(nullability)
#pragma clang assume_nonnull begin
#endif

API_AVAILABLE(ios(13.0))
@interface UIAction()
- (instancetype)initWithTitle:(NSString *)title
                        image:(nullable UIImage *)image
                   identifier:(nullable UIActionIdentifier)identifier
         discoverabilityTitle:(nullable NSString *)discoverabilityTitle
                   attributes:(UIMenuElementAttributes)attributes
                        state:(UIMenuElementState)state
                      handler:(UIActionHandler)handler NS_REFINED_FOR_SWIFT NS_DESIGNATED_INITIALIZER;
@end

API_AVAILABLE(ios(13.0))
@interface UIMenu()
- (instancetype)initWithTitle:(NSString *)title
                        image:(nullable UIImage *)image
                   identifier:(nullable UIMenuIdentifier)identifier
                      options:(UIMenuOptions)options
                     children:(NSArray<UIMenuElement *> *)children NS_REFINED_FOR_SWIFT NS_DESIGNATED_INITIALIZER;
@end

#if __has_feature(nullability)
#pragma clang assume_nonnull end
#endif

#endif

#endif // SWIFT_STDLIB_SHIMS_UIKIT_OVERLAY_H

