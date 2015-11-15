/*
    NSCollectionViewFlowLayout.h
    Application Kit
    Copyright (c) 2015, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSCollectionView.h>
#import <AppKit/NSCollectionViewLayout.h>

typedef NS_ENUM(NSInteger, NSCollectionViewScrollDirection) {
    NSCollectionViewScrollDirectionVertical,
    NSCollectionViewScrollDirectionHorizontal
} NS_ENUM_AVAILABLE_MAC(10_11);

NS_ASSUME_NONNULL_BEGIN

APPKIT_EXTERN NSString *const NSCollectionElementKindSectionHeader NS_AVAILABLE_MAC(10_11);
APPKIT_EXTERN NSString *const NSCollectionElementKindSectionFooter NS_AVAILABLE_MAC(10_11);

NS_CLASS_AVAILABLE_MAC(10_11)
@interface NSCollectionViewFlowLayoutInvalidationContext : NSCollectionViewLayoutInvalidationContext
#ifndef __OBJC2__
{
@private
    struct {
        unsigned int invalidateDelegateMetrics:1;
        unsigned int invalidateAttributes:1;
    } _flowLayoutInvalidationFlags;
}
#endif

@property BOOL invalidateFlowLayoutDelegateMetrics; // if set to NO, flow layout will not requery the collection view delegate for size information etc.
@property BOOL invalidateFlowLayoutAttributes; // if set to NO, flow layout will keep all layout information, effectively not invalidating - useful for a subclass which invalidates only a piece of itself

@end

@protocol NSCollectionViewDelegateFlowLayout <NSCollectionViewDelegate>
@optional

- (NSSize)collectionView:(NSCollectionView *)collectionView layout:(NSCollectionViewLayout*)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath;
- (NSEdgeInsets)collectionView:(NSCollectionView *)collectionView layout:(NSCollectionViewLayout*)collectionViewLayout insetForSectionAtIndex:(NSInteger)section;
- (CGFloat)collectionView:(NSCollectionView *)collectionView layout:(NSCollectionViewLayout*)collectionViewLayout minimumLineSpacingForSectionAtIndex:(NSInteger)section;
- (CGFloat)collectionView:(NSCollectionView *)collectionView layout:(NSCollectionViewLayout*)collectionViewLayout minimumInteritemSpacingForSectionAtIndex:(NSInteger)section;
- (NSSize)collectionView:(NSCollectionView *)collectionView layout:(NSCollectionViewLayout*)collectionViewLayout referenceSizeForHeaderInSection:(NSInteger)section;
- (NSSize)collectionView:(NSCollectionView *)collectionView layout:(NSCollectionViewLayout*)collectionViewLayout referenceSizeForFooterInSection:(NSInteger)section;

@end

NS_CLASS_AVAILABLE_MAC(10_11)
@interface NSCollectionViewFlowLayout : NSCollectionViewLayout
#ifndef __OBJC2__
{
@package
    struct {
        unsigned int delegateSizeForItem:1;
        unsigned int delegateReferenceSizeForHeader:1;
        unsigned int delegateReferenceSizeForFooter:1;
        unsigned int delegateInsetForSection:1;
        unsigned int delegateInteritemSpacingForSection:1;
        unsigned int delegateLineSpacingForSection:1;
        unsigned int delegateAlignmentOptions:1;
        unsigned int layoutDataIsValid:1;
        unsigned int delegateInfoIsValid:1;
        unsigned int roundsToScreenScale:1;
    } _gridLayoutFlags;
    
    CGFloat _interitemSpacing;
    CGFloat _lineSpacing;
    
    CGSize _itemSize; // for the cases the delegate method is not implemented
    CGSize _estimatedItemSize;
    CGSize _headerReferenceSize;
    CGSize _footerReferenceSize;
    NSEdgeInsets _sectionInset;
    
    id _data;
    CGSize _currentLayoutSize;
    
    NSMutableDictionary* _insertedItemsAttributesDict;
    NSMutableDictionary* _insertedSectionHeadersAttributesDict;
    NSMutableDictionary* _insertedSectionFootersAttributesDict;
    NSMutableDictionary* _deletedItemsAttributesDict;
    NSMutableDictionary* _deletedSectionHeadersAttributesDict;
    NSMutableDictionary* _deletedSectionFootersAttributesDict;
    
    NSCollectionViewScrollDirection _scrollDirection;
    NSDictionary *_rowAlignmentsOptionsDictionary;
    
    CGPoint _contentOffsetAdjustment;
    CGSize _contentSizeAdjustment;
    
    NSMutableArray* _indexPathsToValidate;
}
#endif

@property CGFloat minimumLineSpacing;
@property CGFloat minimumInteritemSpacing;
@property NSSize itemSize;
@property NSSize estimatedItemSize; // defaults to NSZeroSize - setting a non-zero size enables cells that self-size via -preferredLayoutAttributesFittingAttributes:
@property NSCollectionViewScrollDirection scrollDirection; // default is NSCollectionViewScrollDirectionVertical
@property NSSize headerReferenceSize;
@property NSSize footerReferenceSize;
@property NSEdgeInsets sectionInset;

@end

NS_ASSUME_NONNULL_END
