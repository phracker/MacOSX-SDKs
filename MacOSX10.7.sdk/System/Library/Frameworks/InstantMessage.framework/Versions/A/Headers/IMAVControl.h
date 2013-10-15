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

- (id)target;
- (void)setTarget:(id)anObject;

- (SEL)action;
- (void)setAction:(SEL)aSelector;

- (NSInteger)tag;
- (void)setTag:(NSInteger)anInt;

- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;

- (NSInteger)integerValue;
- (void)setIntegerValue:(NSInteger)anInteger;

- (int)intValue;
- (void)setIntValue:(int)anInt;

- (float)floatValue;
- (void)setFloatValue:(float)aFloat;

- (double)doubleValue;
- (void)setDoubleValue:(double)aDouble;

@end

@interface IMAVButton : IMAVControl
{
}

- (NSInteger)state;
- (void)setState:(NSInteger)value;

@end

@interface IMAVButton (StandardControls)
/*! 
 @method playPauseButton
 @abstract Returns the play/pause button used in iChat Theater. If the button has a state of 1, it is playing
 otherwise it is paused.
 @result The IMAVButton.
 */
+ (IMAVButton *) playPauseButton;

/*! 
 @method forwardButton
 @abstract Returns the forward button used in iChat Theater.
 @result The IMAVButton.
 */
+ (IMAVButton *) forwardButton;

/*! 
 @method backwardButton
 @abstract Returns the backward button used in iChat Theater.
 @result The IMAVButton.
 */
+ (IMAVButton *) backwardButton;

/*! 
 @method muteButton
 @abstract Returns the mute/unmute button used in iChat Theater. If the button has a state of 1, it is muted
 otherwise it is paused.
 @result The IMAVSlider.
 */
+ (IMAVButton *) muteButton;
@end

@interface IMAVSlider : IMAVControl
{
}

- (double)minValue;
- (void)setMinValue:(double)aDouble;
- (double)maxValue;
- (void)setMaxValue:(double)aDouble;

@end

@interface IMAVSlider (StandardControls)
/*! 
 @method timeSlider
 @abstract Returns the time slider used in iChat Theater.
 @result The IMAVSlider.
 */
+ (IMAVSlider *) timeSlider;
@end

@interface IMAVControlBar : NSObject
{
}

/*! 
 @method controls
 @abstract Returns the controls that have been added to the control bar.
 @result An array of IMAVControls.
 */
- (NSArray *) controls;

/*! 
 @method addControl:
 @abstract Adds the specified control to the control bar.
 @param control The control to add. Generally this will be one of the 
 StandardControls specified in this header.
 */
- (void) addControl: (IMAVControl *) control;

/*! 
 @method removeControls:
 @abstract Removes the specified control from the control bar.
 @param control The control to remove. 
 */
- (void) removeControl: (IMAVControl *) control;

/*! 
 @method removeAllControls:
 @abstract Removes all controls from the control bar.
 */
- (void) removeAllControls;

@end

#endif
