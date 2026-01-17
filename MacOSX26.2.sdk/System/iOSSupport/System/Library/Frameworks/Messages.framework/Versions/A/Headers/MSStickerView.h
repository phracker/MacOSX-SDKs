/*!
 @header     MSStickerView
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class MSSticker;

/*!
 @class      MSStickerView
 @abstract   A UIView subclass that can display sticker assets.
 @discussion This class is a UIView subclass intended to display stickers. It provides
 drag and drop functionality so that user may drag the displayed sticker from this
 view and place it in the Messages transcript.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface MSStickerView : UIView

/*!
 @method   initWithFrame:sticker:
 @abstract   Initializes a MSStickerView with a frame and a MSSticker conforming object to display.
 */
- (instancetype)initWithFrame:(CGRect)frame sticker:(nullable MSSticker *)sticker;

/*!
 @property   sticker
 @abstract   The MSSticker object to display.
 @discussion Set this property to nil to remove the current sticker. Setting the
 sticker property does not change the size of a MSStickerView. Call sizeToFit to
 adjust the size of the view to match the sticker.
 */
@property (nonatomic, strong, readwrite, nullable) MSSticker *sticker;

/*!
 @property   animationDuration
 @abstract   The amount of time it takes to go through one cycle of the sticker animation.
 */
@property (nonatomic, readonly) NSTimeInterval animationDuration;

/*!
 @method    startAnimating
 @abstract  Starts animating the sticker in the receiver.
 @discussion This method always starts the animation from the first frame.
 */
- (void)startAnimating;

/*!
 @method    stopAnimating
 @abstract  Stops animating the sticker in the receiver.
 */
- (void)stopAnimating;

/*!
 @method   isAnimating
 @abstract   Returns a Boolean value indicating whether the animation is running.
 */
- (BOOL)isAnimating;

@end

NS_ASSUME_NONNULL_END
