//
//  CPVoiceControlTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPTemplate.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPVoiceControlState encapsulates the title variants and image(s) for a single voice control
 state, like listening, loading, or recognized.

 Your app may initialize the voice control template with one or more states, and
 you may call @c activateVoiceControlState: to switch between states you've defined.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPVoiceControlState : NSObject <NSSecureCoding>

/**
 Initialize a voice control state with a title and image.

 @param identifier A custom identifier you can use to identify this voice control state. You'll also
 switch to this state by specifying this identifier.
 @param titleVariants An array of title variants. The Voice Control template will select the longest
 variant that fits your specified content.
 @param image An image to be animated while this template is visible. The system
 enforces a minimum cycle duration of 0.3 seconds and a maximum cycle duration of 5 seconds.
 Voice Control state images may be a maximum of 150 by 150 points.
 @param repeats For an animated image, YES if the animation should repeat indefinitely, NO
 to run the animation only once.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                     titleVariants:(nullable NSArray <NSString *> *)titleVariants
                             image:(nullable UIImage *)image
                           repeats:(BOOL)repeats;

@property (nullable, nonatomic, readonly, copy) NSArray <NSString *> *titleVariants;

@property (nullable, nonatomic, readonly, strong) UIImage *image;

@property (nonatomic, readonly, copy) NSString *identifier;

@property (nonatomic, readonly) BOOL repeats;

@end

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPVoiceControlTemplate : CPTemplate

/**
 Initialize a voice control template with a list of voice control states.

 @param voiceControlStates An array of voice control states for this template. Your app can switch between these states after the template is presented.

 @note By default, the Voice Control template will begin on the first state specified.

 @warning You may specify a maximum of 5 voice control states. If you specify more than 5, only the first 5 will be available.
 */
- (instancetype)initWithVoiceControlStates:(NSArray <CPVoiceControlState *> *)voiceControlStates;

@property (nonatomic, readonly, copy) NSArray <CPVoiceControlState *> *voiceControlStates;

/**
 Switch the voice control template to the state corresponding with a particular identifier.

 @param identifier An identifier corresponding to one of the voice control states used to initialize this template.

 @note The Voice Control template applies a rate-limit for voice control states; the template will
 ignore voice control state changes that occur too rapidly or frequently in a short period of time.

 @warning You must first present this voice control template through your @c CPInterfaceController before
 activating a voice control state, otherwise this method will have no effect.
 When the Voice Control template is first presented, the first state you specify in
 @c initWithVoiceControlStates: will be visible.
 */
- (void)activateVoiceControlStateWithIdentifier:(NSString *)identifier;

/**
 The currently-active voice control state identifier.
 */
@property (nonatomic, readonly, copy, nullable) NSString *activeStateIdentifier;

@end

NS_ASSUME_NONNULL_END
