/*!
 @header     MSStickerBrowserViewDataSource
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class MSSticker;
@class MSStickerBrowserView;

/*!
 * @abstract The MSStickerBrowserViewDataSource protocol declares the methods that the Sticker Browser View uses to access the contents of its data source object.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@protocol MSStickerBrowserViewDataSource <NSObject>

/*!
 * @abstract Returns the number of Stickers that the sticker browser should show.
 * @param stickerBrowserView The sticker browser view .
 * @result The number of stickers.
 */
- (NSInteger)numberOfStickersInStickerBrowserView:(MSStickerBrowserView *)stickerBrowserView;

/*!
 * @abstract Returns the sticker that the sticker browser should show in the browser.
 * @param stickerBrowserView The sticker browser view.
 * @param index The index of the sticker to show.
 * @result A MSSticker object.
 */
- (MSSticker *)stickerBrowserView:(MSStickerBrowserView *)stickerBrowserView stickerAtIndex:(NSInteger)index;

@end

NS_ASSUME_NONNULL_END
