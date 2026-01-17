/*!
 @header     MSStickerBrowserView
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <Messages/MSStickerBrowserViewDataSource.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum       MSStickerSize
 @abstract   Sticker size is used to control the display size of the stickers in the Sticker Browser View.
 @constant   MSStickerSizeSmall     Stickers will be drawn in a small frame.
 @constant   MSStickerSizeRegular   Stickers will be drawn in a medium frame.
 @constant   MSStickerSizeLarge     Stickers will be drawn in a large frame.
 */
typedef NS_ENUM(NSInteger, MSStickerSize) {
    MSStickerSizeSmall,
    MSStickerSizeRegular,
    MSStickerSizeLarge,
} NS_ENUM_AVAILABLE_IOS(10_0);

/*!
 @class      MSStickerBrowserView
 @abstract   A UIView subclass that can display a collection of sticker assets.
 @discussion This class is a UIView subclass intended to display a collection of
 stickers. It provides drag and drop functionality so that user may drag an individual
 stickers from this view and place it in the Messages transcript. Stickers may also be
 tapped to add them directly to Messages input field.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSStickerBrowserView : UIView

/*!
 @method   initWithFrame:
 @abstract   Initializes a MSStickerBrowserView with a frame using the regular size class.
 */
- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;

/*!
 @method   initWithFrame:stickerSize:
 @abstract   Initializes a MSStickerBrowserView with a frame and sticker size class.
 @discussion Sticker images will be laid out in a grid similar to a UICollectionView
 configured with flow layout.
 @property size hints the size of the cells, the size a sticker is drawn at will
 vary based on the device. Sticker images will be scaled down to fit in the grid cell. If the
 sticker image is smaller than the cell size measured in pixels then it will be  centered
 in the grid cell.
 */
- (instancetype)initWithFrame:(CGRect)frame stickerSize:(MSStickerSize)stickerSize NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The sticker size class.
 */
@property (nonatomic, assign, readonly) MSStickerSize stickerSize;

/*!
 @abstract The Sticker Browser View data source.
 */
@property (nonatomic, weak, nullable) id<MSStickerBrowserViewDataSource> dataSource;

/*!
 @abstract The Sticker Browser View content offset.
 */
@property (nonatomic, assign, readwrite) CGPoint contentOffset;

/*!
 @abstract The Sticker Browser View content inset.
 */
@property (nonatomic, assign, readwrite) UIEdgeInsets contentInset;

/*!
 @abstract animate Sticker Browser View at constant velocity to new offset.
 */
- (void)setContentOffset:(CGPoint)contentOffset animated:(BOOL)animated;


/*!
 @abstract Asks the Sticker Browser View to reload its data from its data source.
 */
- (void)reloadData;

@end

NS_ASSUME_NONNULL_END
