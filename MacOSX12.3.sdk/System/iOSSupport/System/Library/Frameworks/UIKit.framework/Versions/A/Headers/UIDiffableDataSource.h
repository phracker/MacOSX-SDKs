#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDiffableDataSource.h>)
//
//  UIDiffableDataSource.h
//  UIKit
//
//  Copyright © 2018-2019 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UICollectionView.h>
#import <UIKit/UITableView.h>
#import <UIKit/NSDiffableDataSourceSectionSnapshot.h>

NS_ASSUME_NONNULL_BEGIN

#if UIKIT_HAS_UIFOUNDATION_SYMBOLS

// A NSDiffableDataSourceSnapshot represents the complete state of a UI element (e.g. UICollectionView)
//
//    Snapshots can be created in two ways:
//    1. From a connected data source: e.g. UICollectionViewDiffableDataSource.snapshot()
//       This will contain the current state of the UI element.
//
//    2. Constructing a new instance: e.g. NSDiffableDataSourceSnapshot<Int,UUID>()
//       This will construct an empty snapshot with no section or item identifiers.
//
//    Notes:
//      1. All identifiers must be unique. Section and Item identifiers do not overlap and may contain values that exist in the other (i.e. it is OK
//         to have a section identifier == 1 and an item identifier == 1)
//
//      2. If you pass duplicate values in an item or section array (e.g. -appendItemsWithIdentifiers:), the system will throw an exception.
//

UIKIT_EXTERN API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0))
@interface NSDiffableDataSourceSnapshot<SectionIdentifierType,ItemIdentifierType> : NSObject<NSCopying>

// structure

@property(nonatomic,readonly) NSInteger numberOfItems;
@property(nonatomic,readonly) NSInteger numberOfSections;
@property(nonatomic,readonly) NSArray<SectionIdentifierType> *sectionIdentifiers;
@property(nonatomic,readonly) NSArray<ItemIdentifierType> *itemIdentifiers;

@property(nonatomic,readonly) NSArray<SectionIdentifierType> *reloadedSectionIdentifiers API_AVAILABLE(ios(15.0), tvos(15.0));
@property(nonatomic,readonly) NSArray<ItemIdentifierType> *reloadedItemIdentifiers API_AVAILABLE(ios(15.0), tvos(15.0));
@property(nonatomic,readonly) NSArray<ItemIdentifierType> *reconfiguredItemIdentifiers API_AVAILABLE(ios(15.0), tvos(15.0));

- (NSInteger)numberOfItemsInSection:(SectionIdentifierType)sectionIdentifier;
- (NSArray<ItemIdentifierType>*)itemIdentifiersInSectionWithIdentifier:(SectionIdentifierType)sectionIdentifier;
- (nullable SectionIdentifierType)sectionIdentifierForSectionContainingItemIdentifier:(ItemIdentifierType)itemIdentifier;

- (NSInteger)indexOfItemIdentifier:(ItemIdentifierType)itemIdentifier;             // If item identifier is not present returns NSNotFound
- (NSInteger)indexOfSectionIdentifier:(SectionIdentifierType)sectionIdentifier;    // If section identifier is not present returns NSNotFound

// items operations

- (void)appendItemsWithIdentifiers:(NSArray<ItemIdentifierType>*)identifiers;     // convenience: appends into last section
- (void)appendItemsWithIdentifiers:(NSArray<ItemIdentifierType>*)identifiers intoSectionWithIdentifier:(SectionIdentifierType)sectionIdentifier;

- (void)insertItemsWithIdentifiers:(NSArray<ItemIdentifierType>*)identifiers beforeItemWithIdentifier:(ItemIdentifierType)itemIdentifier;
- (void)insertItemsWithIdentifiers:(NSArray<ItemIdentifierType>*)identifiers afterItemWithIdentifier:(ItemIdentifierType)itemIdentifier;

- (void)deleteItemsWithIdentifiers:(NSArray<ItemIdentifierType>*)identifiers;
- (void)deleteAllItems;

- (void)moveItemWithIdentifier:(ItemIdentifierType)fromIdentifier beforeItemWithIdentifier:(ItemIdentifierType)toIdentifier;
- (void)moveItemWithIdentifier:(ItemIdentifierType)fromIdentifier afterItemWithIdentifier:(ItemIdentifierType)toIdentifier;

- (void)reloadItemsWithIdentifiers:(NSArray<ItemIdentifierType>*)identifiers;
// Reconfigures any existing cells for the items. Reconfiguring is more efficient than reloading an item, as it does not replace the
// existing cell with a new cell. Prefer reconfiguring over reloading unless you actually need an entirely new cell for the item.
- (void)reconfigureItemsWithIdentifiers:(NSArray<ItemIdentifierType>*)identifiers API_AVAILABLE(ios(15.0), tvos(15.0));

// section operations

- (void)appendSectionsWithIdentifiers:(NSArray<SectionIdentifierType>*)sectionIdentifiers;

- (void)insertSectionsWithIdentifiers:(NSArray<SectionIdentifierType>*)sectionIdentifiers beforeSectionWithIdentifier:(SectionIdentifierType)toSectionIdentifier;
- (void)insertSectionsWithIdentifiers:(NSArray<SectionIdentifierType>*)sectionIdentifiers afterSectionWithIdentifier:(SectionIdentifierType)toSectionIdentifier;

- (void)deleteSectionsWithIdentifiers:(NSArray<SectionIdentifierType>*)sectionIdentifiers;

- (void)moveSectionWithIdentifier:(SectionIdentifierType)fromSectionIdentifier beforeSectionWithIdentifier:(SectionIdentifierType)toSectionIdentifier;
- (void)moveSectionWithIdentifier:(SectionIdentifierType)fromSectionIdentifier afterSectionWithIdentifier:(SectionIdentifierType)toSectionIdentifier;

- (void)reloadSectionsWithIdentifiers:(NSArray<SectionIdentifierType>*)sectionIdentifiers;

@end

#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS

typedef UICollectionViewCell * _Nullable (^UICollectionViewDiffableDataSourceCellProvider)(UICollectionView * _Nonnull collectionView, NSIndexPath * _Nonnull indexPath, id _Nonnull itemIdentifier);
typedef UICollectionReusableView * _Nullable (^UICollectionViewDiffableDataSourceSupplementaryViewProvider)(UICollectionView* _Nonnull collectionView, NSString * _Nonnull elementKind, NSIndexPath * _Nonnull indexPath);


UIKIT_EXTERN API_AVAILABLE(ios(14.0),tvos(14.0))
@interface NSDiffableDataSourceSectionTransaction<SectionIdentifierType, ItemIdentifierType> : NSObject
@property(nonatomic,readonly) SectionIdentifierType sectionIdentifier;
@property(nonatomic,readonly) NSDiffableDataSourceSectionSnapshot<ItemIdentifierType> *initialSnapshot;
@property(nonatomic,readonly) NSDiffableDataSourceSectionSnapshot<ItemIdentifierType> *finalSnapshot;
@property(nonatomic,readonly) NSOrderedCollectionDifference<ItemIdentifierType> *difference;
@end

UIKIT_EXTERN API_AVAILABLE(ios(14.0),tvos(14.0))
@interface NSDiffableDataSourceTransaction<SectionIdentifierType, ItemIdentifierType> : NSObject
@property(nonatomic,readonly) NSDiffableDataSourceSnapshot<SectionIdentifierType, ItemIdentifierType> *initialSnapshot;
@property(nonatomic,readonly) NSDiffableDataSourceSnapshot<SectionIdentifierType, ItemIdentifierType> *finalSnapshot;
@property(nonatomic,readonly) NSOrderedCollectionDifference<ItemIdentifierType> *difference;
@property(nonatomic,readonly) NSArray<NSDiffableDataSourceSectionTransaction<SectionIdentifierType, ItemIdentifierType>*> *sectionTransactions;
@end

UIKIT_EXTERN API_AVAILABLE(ios(14.0),tvos(14.0)) NS_SWIFT_UI_ACTOR
@interface UICollectionViewDiffableDataSourceReorderingHandlers<SectionType,ItemType> : NSObject<NSCopying>
@property(nonatomic,copy,nullable) BOOL(^canReorderItemHandler)(ItemType);
@property(nonatomic,copy,nullable) void(^willReorderHandler)(NSDiffableDataSourceTransaction<SectionType, ItemType> *);
@property(nonatomic,copy,nullable) void(^didReorderHandler)(NSDiffableDataSourceTransaction<SectionType, ItemType> *);
@end

UIKIT_EXTERN API_AVAILABLE(ios(14.0),tvos(14.0)) NS_SWIFT_UI_ACTOR
@interface UICollectionViewDiffableDataSourceSectionSnapshotHandlers<ItemType> : NSObject<NSCopying>
@property(nonatomic,copy,nullable) BOOL(^shouldExpandItemHandler)(ItemType);
@property(nonatomic,copy,nullable) void(^willExpandItemHandler)(ItemType);
@property(nonatomic,copy,nullable) BOOL(^shouldCollapseItemHandler)(ItemType);
@property(nonatomic,copy,nullable) void(^willCollapseItemHandler)(ItemType);
@property(nonatomic,copy,nullable) NSDiffableDataSourceSectionSnapshot<ItemType>*(^snapshotForExpandingParentItemHandler)(ItemType, NSDiffableDataSourceSectionSnapshot<ItemType>*);
@end


UIKIT_EXTERN API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0)) NS_SWIFT_UI_ACTOR
@interface UICollectionViewDiffableDataSource<SectionIdentifierType,ItemIdentifierType> : NSObject<UICollectionViewDataSource>

- (instancetype)initWithCollectionView:(UICollectionView*)collectionView cellProvider:(UICollectionViewDiffableDataSourceCellProvider)cellProvider;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property(nonatomic,copy,nullable) UICollectionViewDiffableDataSourceSupplementaryViewProvider supplementaryViewProvider;

// Create a snapshot of the current UICollectionView data source state.
//   This snapshot can be mutated and later applied via -applySnapshot:animatingDifferences:

- (NSDiffableDataSourceSnapshot<SectionIdentifierType,ItemIdentifierType>*)snapshot UIKIT_SWIFT_ACTOR_INDEPENDENT;

// Apply a snapshot to the collection view committing to the new data source state.
//
//   animatingDifferences == YES: perform a diff between the current UICollectionView state and the snapshot, and animate the update.
//   animatingDifferences == NO: perform a diff between the current UICollectionView state and the snapshot, but don't animate the update.
//
//   If the (optional) completion block is specified, it will be called on the main queue when any animations are completed.
//
//  Note: you may call this from a background queue which will cause the diff (if needed) to be generated on the calling queue and the
//        final UI update to be applied back on the main queue. However, all applySnapshot invocations must be confined to the same queue.
//        (if you violate this restriction and mix calls between the main queue and some background queue, the framework
//         will log and/or assert to avoid deadlocks)

- (void)applySnapshot:(NSDiffableDataSourceSnapshot<SectionIdentifierType,ItemIdentifierType>*)snapshot animatingDifferences:(BOOL)animatingDifferences UIKIT_SWIFT_ACTOR_INDEPENDENT;
- (void)applySnapshot:(NSDiffableDataSourceSnapshot<SectionIdentifierType,ItemIdentifierType>*)snapshot animatingDifferences:(BOOL)animatingDifferences completion:(void(^ _Nullable)(void))completion NS_SWIFT_DISABLE_ASYNC UIKIT_SWIFT_ACTOR_INDEPENDENT;

// Apply a snapshot to the collection view using reloadData.
//
//  This always skips diffing, and immediately resets the UICollectionView to the new data source state without animation.
//  Generally this should only be used for specific cases where you need to fully reset the collection view's data to the
//  new state immediately (e.g. recycling the collection view for use with a completely different data set), or when you
//  specifically want to skip diffing (e.g. applying an exceptionally large changeset).

- (void)applySnapshotUsingReloadData:(NSDiffableDataSourceSnapshot<SectionIdentifierType,ItemIdentifierType>*)snapshot UIKIT_SWIFT_ACTOR_INDEPENDENT API_AVAILABLE(ios(15.0), tvos(15.0));
- (void)applySnapshotUsingReloadData:(NSDiffableDataSourceSnapshot<SectionIdentifierType,ItemIdentifierType>*)snapshot completion:(void(^ _Nullable)(void))completion NS_SWIFT_DISABLE_ASYNC UIKIT_SWIFT_ACTOR_INDEPENDENT API_AVAILABLE(ios(15.0), tvos(15.0));

// convert section index <-> SectionIdentifierType

- (nullable SectionIdentifierType)sectionIdentifierForIndex:(NSInteger)index API_AVAILABLE(ios(15.0), tvos(15.0));
- (NSInteger)indexForSectionIdentifier:(SectionIdentifierType)identifier API_AVAILABLE(ios(15.0), tvos(15.0));

// convert item NSIndexPath <-> ItemIdentifierType

- (nullable ItemIdentifierType)itemIdentifierForIndexPath:(NSIndexPath*)indexPath;
- (nullable NSIndexPath*)indexPathForItemIdentifier:(ItemIdentifierType)identifier;

// Reordering Support

@property(nonatomic,copy) UICollectionViewDiffableDataSourceReorderingHandlers<SectionIdentifierType, ItemIdentifierType> *reorderingHandlers API_AVAILABLE(ios(14.0),tvos(14.0));

// Section Snapshot Support

- (void)applySnapshot:(NSDiffableDataSourceSectionSnapshot<ItemIdentifierType>*)snapshot toSection:(SectionIdentifierType)sectionIdentifier animatingDifferences:(BOOL)animatingDifferences UIKIT_SWIFT_ACTOR_INDEPENDENT API_AVAILABLE(ios(14.0),tvos(14.0));
- (void)applySnapshot:(NSDiffableDataSourceSectionSnapshot<ItemIdentifierType>*)snapshot toSection:(SectionIdentifierType)sectionIdentifier animatingDifferences:(BOOL)animatingDifferences completion:(void (^ _Nullable)(void))completion UIKIT_SWIFT_ACTOR_INDEPENDENT NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(ios(14.0),tvos(14.0));
- (NSDiffableDataSourceSectionSnapshot<ItemIdentifierType>*)snapshotForSection:(SectionIdentifierType)section UIKIT_SWIFT_ACTOR_INDEPENDENT API_AVAILABLE(ios(14.0),tvos(14.0));

@property(nonatomic,copy) UICollectionViewDiffableDataSourceSectionSnapshotHandlers<ItemIdentifierType> *sectionSnapshotHandlers API_AVAILABLE(ios(14.0),tvos(14.0));

@end

typedef UITableViewCell * _Nullable (^UITableViewDiffableDataSourceCellProvider)(UITableView * _Nonnull tableView, NSIndexPath * _Nonnull indexPath, id _Nonnull itemIdentifier);

UIKIT_EXTERN API_AVAILABLE(ios(13.0),tvos(13.0),watchos(6.0)) NS_SWIFT_UI_ACTOR
@interface UITableViewDiffableDataSource<SectionIdentifierType,ItemIdentifierType> : NSObject<UITableViewDataSource>

- (instancetype)initWithTableView:(UITableView*)tableView cellProvider:(UITableViewDiffableDataSourceCellProvider)cellProvider;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// Create a snapshot of the current UITableView data source state.
//   This snapshot can be mutated and later applied via -applySnapshot:animatingDifferences:

- (NSDiffableDataSourceSnapshot<SectionIdentifierType,ItemIdentifierType>*)snapshot UIKIT_SWIFT_ACTOR_INDEPENDENT;

// Apply a snapshot to the table view committing to the new data source state.
//
//   animatingDifferences == YES: perform a diff between the current UITableView state and the snapshot, and animate the update.
//   animatingDifferences == NO: perform a diff between the current UITableView state and the snapshot, but don't animate the update.
//
//   If the (optional) completion block is specified, it will be called on the main queue when any animations are completed.
//
//  Note: you may call this from a background queue which will cause the diff (if needed) to be generated on the calling queue and the
//        final UI update to be applied back on the main queue. However, all applySnapshot invocations must be confined to the same queue.
//        (if you violate this restriction and mix calls between the main queue and some background queue, the framework
//         will log and/or assert to avoid deadlocks)

- (void)applySnapshot:(NSDiffableDataSourceSnapshot<SectionIdentifierType,ItemIdentifierType>*)snapshot animatingDifferences:(BOOL)animatingDifferences UIKIT_SWIFT_ACTOR_INDEPENDENT;
- (void)applySnapshot:(NSDiffableDataSourceSnapshot<SectionIdentifierType,ItemIdentifierType>*)snapshot animatingDifferences:(BOOL)animatingDifferences completion:(void(^ _Nullable)(void))completion NS_SWIFT_DISABLE_ASYNC UIKIT_SWIFT_ACTOR_INDEPENDENT;

// Apply a snapshot to the table view using reloadData.
//
//  This always skips diffing, and immediately resets the UITableView to the new data source state without animation.
//  Generally this should only be used for specific cases where you need to fully reset the table view's data to the
//  new state immediately (e.g. recycling the table view for use with a completely different data set), or when you
//  specifically want to skip diffing (e.g. applying an exceptionally large changeset).

- (void)applySnapshotUsingReloadData:(NSDiffableDataSourceSnapshot<SectionIdentifierType,ItemIdentifierType>*)snapshot UIKIT_SWIFT_ACTOR_INDEPENDENT API_AVAILABLE(ios(15.0), tvos(15.0));
- (void)applySnapshotUsingReloadData:(NSDiffableDataSourceSnapshot<SectionIdentifierType,ItemIdentifierType>*)snapshot completion:(void(^ _Nullable)(void))completion NS_SWIFT_DISABLE_ASYNC UIKIT_SWIFT_ACTOR_INDEPENDENT API_AVAILABLE(ios(15.0), tvos(15.0));

// convert section index <-> SectionIdentifierType

- (nullable SectionIdentifierType)sectionIdentifierForIndex:(NSInteger)index API_AVAILABLE(ios(15.0), tvos(15.0));
- (NSInteger)indexForSectionIdentifier:(SectionIdentifierType)identifier API_AVAILABLE(ios(15.0), tvos(15.0));

// convert item NSIndexPath <-> ItemIdentifierType

- (nullable ItemIdentifierType)itemIdentifierForIndexPath:(NSIndexPath*)indexPath;
- (nullable NSIndexPath*)indexPathForItemIdentifier:(ItemIdentifierType)identifier;

// Default value is UITableViewRowAnimationAutomatic. Change takes effect on the next update.

@property(nonatomic) UITableViewRowAnimation defaultRowAnimation;

@end


NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDiffableDataSource.h>
#endif
