#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICollectionViewCompositionalLayout.h>)
//
//  UICollectionViewCompositionalLayout.h
//  UIKit
//
//  Copyright © 2017-2019 Apple Inc. All rights reserved.


#import <UIKit/UIKitDefines.h>
#import <UIKit/UICollectionViewLayout.h>

NS_ASSUME_NONNULL_BEGIN

@class NSCollectionLayoutSection;
@class NSCollectionLayoutGroup;
@class NSCollectionLayoutItem;
@class NSCollectionLayoutSupplementaryItem;
@class NSCollectionLayoutBoundarySupplementaryItem;
@class NSCollectionLayoutDecorationItem;

@class NSCollectionLayoutSize;
@class NSCollectionLayoutDimension;
@class NSCollectionLayoutSpacing;
@class NSCollectionLayoutEdgeSpacing;
@class NSCollectionLayoutAnchor;

@protocol NSCollectionLayoutEnvironment;
@protocol NSCollectionLayoutContainer;
@protocol NSCollectionLayoutVisibleItem;

typedef NS_ENUM(NSInteger, UIContentInsetsReference) {
    UIContentInsetsReferenceAutomatic,               // use system defined default
    UIContentInsetsReferenceNone,                    // no additional insets
    UIContentInsetsReferenceSafeArea,                // honor safe area
    UIContentInsetsReferenceLayoutMargins,           // honor layout margins
    UIContentInsetsReferenceReadableContent,         // honor readable content
} API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));


UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface UICollectionViewCompositionalLayoutConfiguration : NSObject<NSCopying>
@property(nonatomic) UICollectionViewScrollDirection scrollDirection;                                                       // default is UICollectionViewScrollDirectionVertical
@property(nonatomic) CGFloat interSectionSpacing;                                                                           // default is 0
@property(nonatomic,copy) NSArray<NSCollectionLayoutBoundarySupplementaryItem*> *boundarySupplementaryItems;
@property(nonatomic) UIContentInsetsReference contentInsetsReference API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));    // default is UIContentInsetsReferenceSafeArea
@end

typedef NSCollectionLayoutSection * _Nullable (^UICollectionViewCompositionalLayoutSectionProvider)(NSInteger section, id<NSCollectionLayoutEnvironment>);

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface UICollectionViewCompositionalLayout : UICollectionViewLayout
- (instancetype)initWithSection:(NSCollectionLayoutSection*)section;
- (instancetype)initWithSection:(NSCollectionLayoutSection*)section configuration:(UICollectionViewCompositionalLayoutConfiguration*)configuration;

- (instancetype)initWithSectionProvider:(UICollectionViewCompositionalLayoutSectionProvider)sectionProvider;
- (instancetype)initWithSectionProvider:(UICollectionViewCompositionalLayoutSectionProvider)sectionProvider configuration:(UICollectionViewCompositionalLayoutConfiguration*)configuration;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// Setting this property will invalidate the layout immediately to affect any changes
//    Note: any changes made to properties directly will have no effect.
@property(nonatomic,copy) UICollectionViewCompositionalLayoutConfiguration *configuration;
@end

typedef NS_ENUM(NSInteger,UICollectionLayoutSectionOrthogonalScrollingBehavior) {
    // default behavior. Section will layout along main layout axis (i.e. configuration.scrollDirection)
    UICollectionLayoutSectionOrthogonalScrollingBehaviorNone,
    
    // NOTE: For each of the remaining cases, the section content will layout orthogonal to the main layout axis (e.g. main layout axis == .vertical, section will scroll in .horizontal axis)
    
    // Standard scroll view behavior: UIScrollViewDecelerationRateNormal
    UICollectionLayoutSectionOrthogonalScrollingBehaviorContinuous,
    
    // Scrolling will come to rest on the leading edge of a group boundary
    UICollectionLayoutSectionOrthogonalScrollingBehaviorContinuousGroupLeadingBoundary,
    
    // Standard scroll view paging behavior (UIScrollViewDecelerationRateFast) with page size == extent of the collection view's bounds
    UICollectionLayoutSectionOrthogonalScrollingBehaviorPaging,
    
    // Fractional size paging behavior determined by the sections layout group's dimension
    UICollectionLayoutSectionOrthogonalScrollingBehaviorGroupPaging,
    
    // Same of group paging with additional leading and trailing content insets to center each group's contents along the orthogonal axis
    UICollectionLayoutSectionOrthogonalScrollingBehaviorGroupPagingCentered,
} API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0));

typedef void (^NSCollectionLayoutSectionVisibleItemsInvalidationHandler)(NSArray<id<NSCollectionLayoutVisibleItem>> *visibleItems, CGPoint contentOffset, id<NSCollectionLayoutEnvironment> layoutEnvironment);

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutSection : NSObject<NSCopying>
+ (instancetype)sectionWithGroup:(NSCollectionLayoutGroup*)group;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property(nonatomic) NSDirectionalEdgeInsets contentInsets;
@property(nonatomic) CGFloat interGroupSpacing;

// default is UIContentInsetsReferenceAutomatic i.e. following the layout configuration's contentInsetsReference
@property(nonatomic) UIContentInsetsReference contentInsetsReference API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0));

// default is .none
@property(nonatomic) UICollectionLayoutSectionOrthogonalScrollingBehavior orthogonalScrollingBehavior;

// Supplementaries associated with the boundary edges of the section
@property(nonatomic,copy) NSArray<NSCollectionLayoutBoundarySupplementaryItem*> *boundarySupplementaryItems;

// by default, section supplementaries will follow any section-specific contentInsets
@property(nonatomic) BOOL supplementariesFollowContentInsets;

// Called for each layout pass to allow modification of item properties right before they are displayed.
@property(nonatomic,copy,nullable) NSCollectionLayoutSectionVisibleItemsInvalidationHandler visibleItemsInvalidationHandler;

// decoration views anchored to the section's geometry (e.g. background decoration view)
@property(nonatomic,copy) NSArray<NSCollectionLayoutDecorationItem*> *decorationItems;
@end


UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutItem : NSObject<NSCopying>
+ (instancetype)itemWithLayoutSize:(NSCollectionLayoutSize*)layoutSize;
+ (instancetype)itemWithLayoutSize:(NSCollectionLayoutSize*)layoutSize supplementaryItems:(NSArray<NSCollectionLayoutSupplementaryItem*>*)supplementaryItems;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

//                       +---------------------+
//   +-------------+<----|Specified layout size|
//   |             |     +---------------------+
//   |  +-------+  |     +--------------------------+
//   |  |~~~~~~~|  |     |Final size (after         |
//   |  |~~~~~~~|<-+-----|contentInsets are applied)|
//   |  +-------+  |     +--------------------------+
//   |             |
//   +-------------+
//
//  Use contentInsets on an item to adjust the final size of the item after layout is computed.
//    useful for grid style layouts to apply even spacing around each the edges of each item.
//
//  Note: contentInsets are ignored for any axis with an .estimated dimension

@property(nonatomic) NSDirectionalEdgeInsets contentInsets;

//                     +--------+
//                     |  Top   |
//                     +--------+
//                          |
//                          |
//                  +-------+--------------------------+
//                  |       v                          |
//                  |    +------+                      |
//   +--------+     |    |~~~~~~|        +--------+    |
//   |Leading |-----+->  |~~~~~~| <------|Trailing|    |
//   +--------+     |    |~~~~~~|        +--------+    |
//                  |    +------+                      |
//                  |        ^                         |
//                  +--------+-------------------------+
//                           |
//                           |
//                      +--------+
//                      | Bottom |
//                      +--------+
//
//  Specifies additional space required surrounding and item when laying out.
//  Flexible spacing can be used to apportion remaining space after items are laid out to
//    evenly align items among available layout space.

@property(nonatomic,copy,nullable) NSCollectionLayoutEdgeSpacing *edgeSpacing;

@property(nonatomic,readonly) NSCollectionLayoutSize *layoutSize;
@property(nonatomic,readonly) NSArray<NSCollectionLayoutSupplementaryItem*> *supplementaryItems;
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutGroupCustomItem : NSObject<NSCopying>
+ (instancetype)customItemWithFrame:(CGRect)frame;
+ (instancetype)customItemWithFrame:(CGRect)frame zIndex:(NSInteger)zIndex;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property(nonatomic,readonly) CGRect frame;
@property(nonatomic,readonly) NSInteger zIndex;
@end

typedef NSArray<NSCollectionLayoutGroupCustomItem*> * _Nonnull(^NSCollectionLayoutGroupCustomItemProvider)(id<NSCollectionLayoutEnvironment> layoutEnvironment);

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutGroup : NSCollectionLayoutItem<NSCopying>

// Specifies a group that will have N items equally sized along the horizontal axis. use interItemSpacing to insert space between items
//
//   +------+--+------+--+------+
//   |~~~~~~|  |~~~~~~|  |~~~~~~|
//   |~~~~~~|  |~~~~~~|  |~~~~~~|
//   |~~~~~~|  |~~~~~~|  |~~~~~~|
//   +------+--+------+--+------+
//            ^        ^
//            |        |
//    +-----------------------+
//    |  Inter Item Spacing   |
//    +-----------------------+
//
+ (instancetype)horizontalGroupWithLayoutSize:(NSCollectionLayoutSize*)layoutSize subitem:(NSCollectionLayoutItem*)subitem count:(NSInteger)count;

// Specifies a group that will repeat items until available horizontal space is exhausted.
//   note: any remaining space after laying out items can be apportioned among flexible interItemSpacing defintions
+ (instancetype)horizontalGroupWithLayoutSize:(NSCollectionLayoutSize*)layoutSize subitems:(NSArray<NSCollectionLayoutItem*>*)subitems;

// Specifies a group that will have N items equally sized along the vertical axis. use interItemSpacing to insert space between items
//   +------+
//   |~~~~~~|
//   |~~~~~~|
//   |~~~~~~|
//   +------+
//   |      |<--+
//   +------+   |
//   |~~~~~~|   |    +-----------------------+
//   |~~~~~~|   +----|  Inter Item Spacing   |
//   |~~~~~~|   |    +-----------------------+
//   +------+   |
//   |      |<--+
//   +------+
//   |~~~~~~|
//   |~~~~~~|
//   |~~~~~~|
//   +------+
//
+ (instancetype)verticalGroupWithLayoutSize:(NSCollectionLayoutSize*)layoutSize subitem:(NSCollectionLayoutItem*)subitem count:(NSInteger)count;

// Specifies a group that will repeat items until available vertical space is exhausted.
//   note: any remaining space after laying out items can be apportioned among flexible interItemSpacing defintions
+ (instancetype)verticalGroupWithLayoutSize:(NSCollectionLayoutSize*)layoutSize subitems:(NSArray<NSCollectionLayoutItem*>*)subitems;

// Specifies a custom group with client-specified frames.
//   During layout, the itemProvider will be called with the group's current geometry provided via the NSCollectionLayoutEnvironment supplied.
//   The coordinate space for returned frames should be {0,0} relative to this group's geometry.
//   Custom groups can be nested arbitrarily inside other groups.
+ (instancetype)customGroupWithLayoutSize:(NSCollectionLayoutSize*)layoutSize itemProvider:(NSCollectionLayoutGroupCustomItemProvider)itemProvider;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// Supplementary items are "anchored" to the group's geometry.
@property(nonatomic,copy) NSArray<NSCollectionLayoutSupplementaryItem*> *supplementaryItems;

// Supplies additional spacing between items along the layout axis of the group
@property(nonatomic,copy,nullable) NSCollectionLayoutSpacing *interItemSpacing;

@property(nonatomic,readonly) NSArray<NSCollectionLayoutItem*> *subitems;

// for visual debugging; will print an ASCII art rendering to console
- (NSString*)visualDescription;

@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutDimension : NSObject<NSCopying>
// dimension is computed as a fraction of the width of the containing group
+ (instancetype)fractionalWidthDimension:(CGFloat)fractionalWidth;

// dimension is computed as a fraction of the height of the containing group
+ (instancetype)fractionalHeightDimension:(CGFloat)fractionalHeight;

// dimension with an absolute point value
+ (instancetype)absoluteDimension:(CGFloat)absoluteDimension;

// dimension is estimated with a point value. Actual size will be determined when the content is rendered.
+ (instancetype)estimatedDimension:(CGFloat)estimatedDimension;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property(nonatomic,readonly) BOOL isFractionalWidth;
@property(nonatomic,readonly) BOOL isFractionalHeight;
@property(nonatomic,readonly) BOOL isAbsolute;
@property(nonatomic,readonly) BOOL isEstimated;
@property(nonatomic,readonly) CGFloat dimension;
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutSize : NSObject<NSCopying>
+ (instancetype)sizeWithWidthDimension:(NSCollectionLayoutDimension*)width heightDimension:(NSCollectionLayoutDimension*)height;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property(nonatomic,readonly) NSCollectionLayoutDimension *widthDimension;
@property(nonatomic,readonly) NSCollectionLayoutDimension *heightDimension;
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutSpacing : NSObject<NSCopying>
+ (instancetype)flexibleSpacing:(CGFloat)flexibleSpacing;  // i.e. >=
+ (instancetype)fixedSpacing:(CGFloat)fixedSpacing;        // i.e. ==

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property(nonatomic,readonly) CGFloat spacing;
@property(nonatomic,readonly) BOOL isFlexibleSpacing;
@property(nonatomic,readonly) BOOL isFixedSpacing;
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutEdgeSpacing : NSObject<NSCopying>

// Edge spacing specifies additional outsets around items required when performing layout.
//   Edges may be omitted as-needed
//
//    +-----------------+--------+-----------------+------+-----------------+
//    |~~~~~~~~~~~~~~~~~|        |~~~~~~~~~~~~~~~~~|      |~~~~~~~~~~~~~~~~~|
//    |~~~~~~~~~~~~~~~~~|        |~~~~~~~~~~~~~~~~~|      |~~~~~~~~~~~~~~~~~|
//    |~~~~~~~~~~~~~~~~~|        |~~~~~~~~~~~~~~~~~|      |~~~~~~~~~~~~~~~~~|
//    |~~~~~~~~~~~~~~~~~|        |~~~~~~~~~~~~~~~~~|      |~~~~~~~~~~~~~~~~~|
//    |~~~~~~~~~~~~~~~~~|        |~~~~~~~~~~~~~~~~~|      |~~~~~~~~~~~~~~~~~|
//    |~~~~~~~~~~~~~~~~~|        |~~~~~~~~~~~~~~~~~|      |~~~~~~~~~~~~~~~~~|
//    |~~~~~~~~~~~~~~~~~|        |~~~~~~~~~~~~~~~~~|      |~~~~~~~~~~~~~~~~~|
//    |~~~~~~~~~~~~~~~~~|        |~~~~~~~~~~~~~~~~~|      |~~~~~~~~~~~~~~~~~|
//    |~~~~~~~~~~~~~~~~~|        |~~~~~~~~~~~~~~~~~|      |~~~~~~~~~~~~~~~~~|
//    |~~~~~~~~~~~~~~~~~|        |~~~~~~~~~~~~~~~~~|      |~~~~~~~~~~~~~~~~~|
//    +-----------------+        +-----------------+      +-----------------+
//    |                                                                     |
//    |        ^                         ^                          ^       |
//    +--------+-------------------------+--------------------------+-------+
//             |                         |                          |
//             |                         |                          |
//   +---------+-------------------------+--------------------------+--------------------------+
//   |NSCollectionLayoutEdgeSpacing(leading:nil, top: nil, bottom:.flexible(0.0), trailing:nil)|
//   |                                                                                         |
//   |*forces items to align to the top of their group's geometry                              |
//   +-----------------------------------------------------------------------------------------+

+ (instancetype)spacingForLeading:(nullable NSCollectionLayoutSpacing *)leading
                              top:(nullable NSCollectionLayoutSpacing *)top
                         trailing:(nullable NSCollectionLayoutSpacing *)trailing
                           bottom:(nullable NSCollectionLayoutSpacing *)bottom;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property(nonatomic,readonly,nullable) NSCollectionLayoutSpacing *leading;
@property(nonatomic,readonly,nullable) NSCollectionLayoutSpacing *top;
@property(nonatomic,readonly,nullable) NSCollectionLayoutSpacing *trailing;
@property(nonatomic,readonly,nullable) NSCollectionLayoutSpacing *bottom;
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutSupplementaryItem : NSCollectionLayoutItem<NSCopying>

//  Supplementary items are positioned (i.e. anchored) to coordinate spaces throughout the layout
//    In this example, a supplementary is anchored to the top+trailing edge of a cell.
//    Supplementary items can be anchored to items (and groups, since a group is-a item)
//    Boundary supplementary items can be anchored to sections and the global layout
//
//                                +-----+       +------------------------------------------+
//                                |~~~~~|       | edges: [.top,.trailing]                  |
//   +----------------------------+~~~~~|<------+ fractionalOffset: CGPoint(x:0.5,y:-0.5)  |
//   |                            |~~~~~|       +------------------------------------------+
//   |                            +--+--+
//   |                               |
//   |                               |
//   |                               |
//   |                               |
//   +-------------------------------+
//
//  Container anchors are used to specify positioning of an item within the host geometry (e.g. item, group, section)

+ (instancetype)supplementaryItemWithLayoutSize:(NSCollectionLayoutSize*)layoutSize elementKind:(NSString*)elementKind containerAnchor:(NSCollectionLayoutAnchor*)containerAnchor;

//                                                     +----------------------------------------------------+
//                                     +-----+         |* Container Anchor                                  |
//                                     |~~~~~|         |edges: [.top,.trailing] offset: CGPoint(x:10,y:-10) |
//                                     |~~~~~|<--------|                                                    |
//                                     |~~~~~|         |* Item Anchor:                                      |
//                                     +-----+         |edges: [.bottom, .leading]                          |
//   +-------------------------------+                 +----------------------------------------------------+
//   |                               |
//   |                               |
//   |                               |
//   |                               |
//   |                               |
//   |                               |
//   +-------------------------------+
//
//   Combine a container anchor with an item anchor for fine-grained positioning.
//     Optionally add an offset for additional refinement.

+ (instancetype)supplementaryItemWithLayoutSize:(NSCollectionLayoutSize*)layoutSize elementKind:(NSString*)elementKind containerAnchor:(NSCollectionLayoutAnchor*)containerAnchor itemAnchor:(NSCollectionLayoutAnchor*)itemAnchor;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property(nonatomic) NSInteger zIndex;

@property(nonatomic,readonly) NSString *elementKind;
@property(nonatomic,readonly) NSCollectionLayoutAnchor *containerAnchor;
@property(nonatomic,readonly,nullable) NSCollectionLayoutAnchor *itemAnchor;
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutBoundarySupplementaryItem : NSCollectionLayoutSupplementaryItem<NSCopying>

// Specify the alignment of the supplementary relative the containing geometry's coordinate space to
// position the boundary supplementary item.
//
//                                            +------------------------------------------+
//   +----------------------+                 |Boundary Supplementary Item               |
//   |                      |<----------------|* alignment: [.top, .leading]             |
//   +----------------------+                 |* absoluteOffset: CGPoint(x:0.0, y:-10.0) |
//                                            +------------------------------------------+
//   +----------------------------------+
//   |                                  |
//   |                                  |
//   |                                  |
//   |                                  |
//   |                                  |
//   |                                  |
//   |                                  |
//   |                                  |
//   |                                  |      +--------------------------------+
//   |                                  |<-----|        Section Geometry        |
//   |                                  |      +--------------------------------+
//   |                                  |
//   |                                  |
//   |                                  |
//   |                                  |
//   |                                  |
//   |                                  |
//   |                                  |
//   +----------------------------------+

+ (instancetype)boundarySupplementaryItemWithLayoutSize:(NSCollectionLayoutSize*)layoutSize elementKind:(NSString*)elementKind alignment:(NSRectAlignment)alignment;
+ (instancetype)boundarySupplementaryItemWithLayoutSize:(NSCollectionLayoutSize*)layoutSize elementKind:(NSString*)elementKind alignment:(NSRectAlignment)alignment absoluteOffset:(CGPoint)absoluteOffset;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// Default is YES. This will automatically extend the content area of the host geometry (e.g. section)
//   For .estimated sized supplementary items, this allows automatic adjustment of the layout. (e.g. dynamic text)
@property(nonatomic) BOOL extendsBoundary;

// Default is NO. Specify YES to keep the supplementary visible while any portion of the host geometry (e.g. section) is visible.
//   Occlusion disambiguation between other supplementaries will be managed automatically (e.g. section header + footer both pinned)
@property(nonatomic) BOOL pinToVisibleBounds;

@property(nonatomic,readonly) NSRectAlignment alignment;
@property(nonatomic,readonly) CGPoint offset;
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutDecorationItem : NSCollectionLayoutItem<NSCopying>

// Useful for setting a background decoration view behind a section's content area.
//
// contentInset can also be applied as-needed.
// Register the elementKind with the layout instance to associate with your custom view class/nib
//
//   +----------------------------------+
//   |                                  |
//   |  +----------------------------+  |      +--------------------------------+
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |      |Background Decoration Item      |
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~<--+------|* contentInsets applied         |
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |      +--------------------------------+
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |      +--------------------------------+
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |<-----|        Section Geometry        |
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |      +--------------------------------+
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |
//   |  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~|  |
//   |  +----------------------------+  |
//   |                                  |
//   +----------------------------------+

+ (instancetype)backgroundDecorationItemWithElementKind:(NSString*)elementKind;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property(nonatomic) NSInteger zIndex;      // default is 0; all other section items will be automatically be promoted to zIndex=1

@property(nonatomic,readonly) NSString *elementKind;
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@interface NSCollectionLayoutAnchor : NSObject<NSCopying>

//                       +------------------+  +------+   +------------------+
//                       | [.top, .leading] |  |[.top]|   | [.top,.trailing] |
//                       +--+---------------+  +---+--+   +---------------+--+
//                          |                      |                      |
//                          v                      v                      v
//                       +-----+----------------+-----+----------------+-----+
//                       |~~~~~|                |~~~~~|                |~~~~~|
//                       |~~~~~|                |~~~~~|                |~~~~~|
//                       +-----+                +-----+                +-----+
//                       |                                                   |
//                       +-----+                                       +-----+
//   +--------------+    |~~~~~|                                       |~~~~~|    +-------------+
//   |  [.leading]  |--->|~~~~~|                                       |~~~~~|<---| [.trailing] |
//   +--------------+    +-----+                                       +-----+    +-------------+
//                       |                                                   |
//                       +-----+                +-----+                +-----+
//                       |~~~~~|                |~~~~~|                |~~~~~|
//                       |~~~~~|                |~~~~~|                |~~~~~|
//                       +-----+----------------+-----+----------------+-----+
//                          ^                      ^                      ^
//                          |                      |                      |
//                      +---+---------------+ +----+----+  +--------------+----+
//                      |[.bottom, .leading]| |[.bottom]|  |[.bottom,.trailing]|
//                      +-------------------+ +---------+  +-------------------+
//
// Edges are specified as shown above.

+ (instancetype)layoutAnchorWithEdges:(NSDirectionalRectEdge)edges;

//                                +-----+       +------------------------------------+
//                                |~~~~~|       |      edges: [.top,.trailing]       |
//   +----------------------------+~~~~~|<------+ unitOffset: CGPoint(x:0.5,y:-0.5)  |
//   |                            |~~~~~|       +------------------------------------+
//   |                            +--+--+
//   |                               |
//   |                               |
//   |                               |
//   |                               |
//   +-------------------------------+
//
// To specify additional offsets, combine edges with absoluteOffset or unitOffset.

+ (instancetype)layoutAnchorWithEdges:(NSDirectionalRectEdge)edges absoluteOffset:(CGPoint)absoluteOffset;
+ (instancetype)layoutAnchorWithEdges:(NSDirectionalRectEdge)edges fractionalOffset:(CGPoint)fractionalOffset;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property(nonatomic,readonly) NSDirectionalRectEdge edges;
@property(nonatomic,readonly) CGPoint offset;
@property(nonatomic,readonly) BOOL isAbsoluteOffset;
@property(nonatomic,readonly) BOOL isFractionalOffset;
@end

API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@protocol NSCollectionLayoutContainer<NSObject>
@property(nonatomic,readonly) CGSize contentSize;                               // resolved size of container (before any insets are applied)
@property(nonatomic,readonly) CGSize effectiveContentSize;                      // after insets are applied
@property(nonatomic,readonly) NSDirectionalEdgeInsets contentInsets;            // values < 1.0 are interpreted as fractional values (e.g. leading:0.15 == 15% width)
@property(nonatomic,readonly) NSDirectionalEdgeInsets effectiveContentInsets;   // resolved value after resolving any unit values
@end

API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@protocol NSCollectionLayoutEnvironment<NSObject>
@property(nonatomic,readonly) id<NSCollectionLayoutContainer> container;
@property(nonatomic,readonly) UITraitCollection *traitCollection;
@end

API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0))
@protocol NSCollectionLayoutVisibleItem<NSObject,UIDynamicItem>
@property(nonatomic) CGFloat alpha;
@property(nonatomic) NSInteger zIndex;
@property(nonatomic, getter=isHidden) BOOL hidden;
@property(nonatomic) CGPoint center;
@property(nonatomic) CGAffineTransform transform;
@property(nonatomic) CATransform3D transform3D;

@property(nonatomic,readonly) NSString *name;
@property(nonatomic,readonly) NSIndexPath *indexPath;
@property(nonatomic,readonly) CGRect frame;
@property(nonatomic,readonly) CGRect bounds;
@property(nonatomic,readonly) UICollectionElementCategory representedElementCategory;
@property(nonatomic,readonly,nullable) NSString *representedElementKind;
@end

NS_ASSUME_NONNULL_END




#else
#import <UIKitCore/UICollectionViewCompositionalLayout.h>
#endif
