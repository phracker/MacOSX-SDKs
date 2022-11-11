//
//  IMAVControl.h
//
//  Copyright (c) 2008 Apple, Inc. All rights reserved.
//

/*! @header
 @discussion The IMAVControl API allows clients to display controls in iChat's video conference
 window while an iChat Theater session is running.
 */

#import <Foundation/Foundation.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

@interface IMAVControl : NSObject 
{
    id _contents;
}

- (id)target NS_DEPRECATED_MAC(10_5, 10_9);
- (void)setTarget:(id)anObject NS_DEPRECATED_MAC(10_5, 10_9);

- (SEL)action NS_DEPRECATED_MAC(10_5, 10_9);
- (void)setAction:(SEL)aSelector NS_DEPRECATED_MAC(10_5, 10_9);

- (NSInteger)tag NS_DEPRECATED_MAC(10_5, 10_9);
- (void)setTag:(NSInteger)anInt NS_DEPRECATED_MAC(10_5, 10_9);

- (BOOL)isEnabled NS_DEPRECATED_MAC(10_5, 10_9);
- (void)setEnabled:(BOOL)flag NS_DEPRECATED_MAC(10_5, 10_9);

- (NSInteger)integerValue NS_DEPRECATED_MAC(10_5, 10_9);
- (void)setIntegerValue:(NSInteger)anInteger NS_DEPRECATED_MAC(10_5, 10_9);

- (int)intValue NS_DEPRECATED_MAC(10_5, 10_9);
- (void)setIntValue:(int)anInt NS_DEPRECATED_MAC(10_5, 10_9);

- (float)floatValue NS_DEPRECATED_MAC(10_5, 10_9);
- (void)setFloatValue:(float)aFloat NS_DEPRECATED_MAC(10_5, 10_9);

- (double)doubleValue NS_DEPRECATED_MAC(10_5, 10_9);
- (void)setDoubleValue:(double)aDouble NS_DEPRECATED_MAC(10_5, 10_9);

@end

@interface IMAVButton : IMAVControl
{
}

- (NSInteger)state NS_DEPRECATED_MAC(10_5, 10_9);
- (void)setState:(NSInteger)value NS_DEPRECATED_MAC(10_5, 10_9);

@end

@interface IMAVButton (StandardControls)
/*! 
 @method playPauseButton
 @abstract Returns the play/pause button used in iChat Theater. If the button has a state of 1, it is playing
 otherwise it is paused.
 @result The IMAVButton.
 */
+ (IMAVButton *) playPauseButton NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
 @method forwardButton
 @abstract Returns the forward button used in iChat Theater.
 @result The IMAVButton.
 */
+ (IMAVButton *) forwardButton NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
 @method backwardButton
 @abstract Returns the backward button used in iChat Theater.
 @result The IMAVButton.
 */
+ (IMAVButton *) backwardButton NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
 @method muteButton
 @abstract Returns the mute/unmute button used in iChat Theater. If the button has a state of 1, it is muted
 otherwise it is paused.
 @result The IMAVSlider.
 */
+ (IMAVButton *) muteButton NS_DEPRECATED_MAC(10_5, 10_9);
@end

@interface IMAVSlider : IMAVControl
{
}

- (double)minValue NS_DEPRECATED_MAC(10_5, 10_9);
- (void)setMinValue:(double)aDouble NS_DEPRECATED_MAC(10_5, 10_9);
- (double)maxValue NS_DEPRECATED_MAC(10_5, 10_9);
- (void)setMaxValue:(double)aDouble NS_DEPRECATED_MAC(10_5, 10_9);

@end

@interface IMAVSlider (StandardControls)
/*! 
 @method timeSlider
 @abstract Returns the time slider used in iChat Theater.
 @result The IMAVSlider.
 */
+ (IMAVSlider *) timeSlider NS_DEPRECATED_MAC(10_5, 10_9);
@end

@interface IMAVControlBar : NSObject
{
}

/*! 
 @method controls
 @abstract Returns the controls that have been added to the control bar.
 @result An array of IMAVControls.
 */
- (NSArray *) controls NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
 @method addControl:
 @abstract Adds the specified control to the control bar.
 @param control The control to add. Generally this will be one of the 
 StandardControls specified in this header.
 */
- (void) addControl: (IMAVControl *) control NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
 @method removeControls:
 @abstract Removes the specified control from the control bar.
 @param control The control to remove. 
 */
- (void) removeControl: (IMAVControl *) control NS_DEPRECATED_MAC(10_5, 10_9);

/*! 
 @method removeAllControls:
 @abstract Removes all controls from the control bar.
 */
- (void) removeAllControls NS_DEPRECATED_MAC(10_5, 10_9);

@end

#endif
