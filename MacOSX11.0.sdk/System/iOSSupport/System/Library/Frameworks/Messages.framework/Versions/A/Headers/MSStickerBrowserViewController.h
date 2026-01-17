/*!
 @header     MSStickerBrowserViewController
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <Messages/MSStickerBrowserView.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract The MSStickerBrowserViewController class creates a controller object that manages a MSStickerBrowserView.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSStickerBrowserViewController : UIViewController <MSStickerBrowserViewDataSource>

/*!
 @method   initWithStickerSize:
 @abstract Initializes a MSStickerBrowserViewController and configures it's MSStickerBrowserView with the provided sticker size class.
 */
- (instancetype)initWithStickerSize:(MSStickerSize)stickerSize NS_DESIGNATED_INITIALIZER;

/*!
 @property   stickerBrowserView
 @abstract   Returns the sticker browser view managed by the controller object.
 */
@property (nonatomic, strong, readonly) MSStickerBrowserView *stickerBrowserView;

/*!
 * @abstract Controls the size of the stickers are displayed at in the sticker browser view.
 */
@property (nonatomic, readonly) MSStickerSize stickerSize;

@end

NS_ASSUME_NONNULL_END
