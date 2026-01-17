//
//  NSSymbolEffect.h
//  Symbols
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef NSSymbolEffect_h
#define NSSymbolEffect_h

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark - Options

/// The behavior of repetition to use when a symbol effect is animating.
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolEffectOptionsRepeatBehavior: NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Creates and returns a repeat behavior that prefers to repeat indefinitely using periodic animations.
/// Periodic animations play the effect at regular intervals starting and stopping each time.
///
/// - Returns: A new behavior that prefers to repeat indefinitely using periodic animations.
+ (instancetype)behaviorPeriodic;

/// Creates and returns a repeat behavior with a preferred play count using periodic animations.
/// Periodic animations play the effect at regular intervals starting and stopping each time.
///
/// - Parameter count: The preferred number of times to play the
///   effect. Very
///   large or small values may be clamped.
///
/// - Returns: A new behavior with the preferred
/// play count using periodic animations.
+ (instancetype)behaviorPeriodicWithCount:(NSInteger)count;

/// Creates and returns a repeat behavior with a preferred repeat delay using periodic animations.
/// Periodic animations play the effect at regular intervals starting and stopping each time.
///
/// - Parameter delay: The preferred delay between repetitions,
///   in seconds.
///
/// - Returns: A new behavior that prefers to repeat indefinitely
/// with a specified delay using periodic animations.
+ (instancetype)behaviorPeriodicWithDelay:(double)delay;

/// Creates and returns a repeat behavior with a preferred play count and delay using periodic animations.
/// Periodic animations play the effect at regular intervals starting and stopping each time.
///
/// - Parameter count: The preferred number of times to play the
///   effect. Very
///   large or small values may be clamped.
///
/// - Parameter delay: The preferred delay between repetitions,
///   in seconds.
///
/// - Returns: A new behavior with the preferred
/// play count and delay using periodic animations.
+ (instancetype)behaviorPeriodicWithCount:(NSInteger)count delay:(double)delay;

/// Creates and returns a repeat behavior that prefers to repeat indefinitely,
/// using continuous animations if available.
/// Continuous animations have an intro, a body that runs as long as the effect is enabled, and an outro.
/// If available these animations provide a smoother animation when an effect repeats indefinitely.
///
/// - Returns: A new behavior that prefers to repeat indefinitely with continuous animations.
+ (instancetype)behaviorContinuous;

@end

/// Options configuring how symbol effects apply to symbol views.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolEffectOptions : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The default options.
+ (instancetype)options;

/// Convenience initializer that prefers to repeat indefinitely.
+ (instancetype)optionsWithRepeating API_DEPRECATED_WITH_REPLACEMENT("[NSSymbolEffectOptionsRepeatBehavior behaviorPeriodic]", macos(14.0, API_TO_BE_DEPRECATED), ios(17.0, API_TO_BE_DEPRECATED), tvos(17.0, API_TO_BE_DEPRECATED), watchos(10.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED));

/// Return a copy of the options that prefers to repeat indefinitely.
- (instancetype)optionsWithRepeating API_DEPRECATED_WITH_REPLACEMENT("[NSSymbolEffectOptionsRepeatBehavior behaviorPeriodic]", macos(14.0, API_TO_BE_DEPRECATED), ios(17.0, API_TO_BE_DEPRECATED), tvos(17.0, API_TO_BE_DEPRECATED), watchos(10.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED));

/// Convenience initializer that prefers not to repeat.
+ (instancetype)optionsWithNonRepeating;

/// Return a copy of the options that prefers not to repeat.
- (instancetype)optionsWithNonRepeating;

/// Convenience initializer setting a preferred repeat count.
///
/// - Parameter count: The preferred number of times to play the
///   effect. Very large or small values may be clamped.
///
/// - Returns: A new options object with the preferred repeat count.
+ (instancetype)optionsWithRepeatCount:(NSInteger)count API_DEPRECATED_WITH_REPLACEMENT("[NSSymbolEffectOptionsRepeatBehavior behaviorPeriodicWithCount:]", macos(14.0, API_TO_BE_DEPRECATED), ios(17.0, API_TO_BE_DEPRECATED), tvos(17.0, API_TO_BE_DEPRECATED), watchos(10.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED));

/// Return a copy of the options setting a preferred repeat count.
///
/// - Parameter count: The preferred number of times to play the
///   effect. Very large or small values may be clamped.
///
/// - Returns: A new options object with the preferred repeat count.
- (instancetype)optionsWithRepeatCount:(NSInteger)count API_DEPRECATED_WITH_REPLACEMENT("[NSSymbolEffectOptionsRepeatBehavior behaviorPeriodicWithCount:]", macos(14.0, API_TO_BE_DEPRECATED), ios(17.0, API_TO_BE_DEPRECATED), tvos(17.0, API_TO_BE_DEPRECATED), watchos(10.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED));

/// Convenience initializer setting the preferred speed multiplier.
///
/// - Parameter speed: the preferred speed multiplier to play the effect with.
/// The default multiplier is `1.0`. Very large or small values may
/// be clamped.
///
/// - Returns: A new instance with the preferred speed multiplier.
+ (instancetype)optionsWithSpeed:(double)speed;

/// Return a copy of the options setting the preferred speed multiplier.
///
/// - Parameter speed: The preferred speed multiplier to play the effect with.
/// The default multiplier is `1.0`. Very large or small values may
/// be clamped.
///
/// - Returns: A new instance with the preferred speed multiplier.
- (instancetype)optionsWithSpeed:(double)speed;

/// Convenience initializer setting a preferred repeat behavior.
///
/// - Parameter behavior: The preferred behavior when the effect is repeated.
///
/// - Returns: A new options object with the preferred repeat behavior.
+ (instancetype)optionsWithRepeatBehavior:(NSSymbolEffectOptionsRepeatBehavior *)behavior API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/// Return a copy of the options setting a preferred repeat behavior.
///
/// - Parameter behavior: The preferred behavior when the effect is repeated.
///
/// - Returns: A new options object with the preferred repeat behavior.
- (instancetype)optionsWithRepeatBehavior:(NSSymbolEffectOptionsRepeatBehavior *)behavior API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

@end

#pragma mark - Base Effect

/// An abstract base class for effects that can be applied to both NSImageViews and UIImageViews that have symbol-based images.
///
/// Don't use this class directly, instead use any of the concrete subclasses.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolEffect : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - Pulse Effect

/// A symbol effect that applies the Pulse animation to
/// symbol images.
///
/// The Pulse animation fades the opacity of either all layers in
/// the symbol, or of a subset of the layers in the symbol.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolPulseEffect : NSSymbolEffect

/// The default pulse effect, determined by the system.
+ (instancetype)effect;

/// Returns a copy of the effect that only animates annotated pulse layers.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Bounce Effect

/// A symbol effect that applies the Bounce animation to
/// symbol images.
///
/// The Bounce animation applies a transitory scaling effect to the symbol.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolBounceEffect : NSSymbolEffect

/// The default bounce effect, determined by the system.
+ (instancetype)effect;

/// Convenience initializer for a bounce effect that bounces up.
+ (instancetype)bounceUpEffect;

/// Convenience initializer for a bounce effect that bounces down.
+ (instancetype)bounceDownEffect;

/// Returns a copy of the effect that animates incrementally, by layer.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Variable Color Effect

/// A symbol effect that applies the Variable Color
/// animation to symbol images.
///
/// The Variable Color animation replaces the opacity of variable
/// layers in the symbol by a possibly repeating pattern that moves
/// up and possibly back down the variable layers. It has no effect
/// for non-variable color symbol images.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolVariableColorEffect : NSSymbolEffect

/// The default variable color effect, determined by the system.
+ (instancetype)effect;

/// Returns a copy of the effect that activates one layer at a time. This cancels the cumulative variant.
- (instancetype)effectWithIterative;

/// Returns a copy of the effect that activates each layer until all layers are active. This cancels the iterative variant.
- (instancetype)effectWithCumulative;

/// Returns a copy of the effect that animates in reverse after fully executing. This cancels the nonReversing variant.
- (instancetype)effectWithReversing;

/// Returns a copy of the effect that only animates forwards before restarting. This cancels the reversing variant.
- (instancetype)effectWithNonReversing;

/// Returns a copy of the effect that hides layers when they are inactive.
- (instancetype)effectWithHideInactiveLayers;

/// Returns a copy of the effect that draws layers with reduced (but non-zero)
/// opacity when they are inactive.
- (instancetype)effectWithDimInactiveLayers;

@end

#pragma mark - Scale Effect

/// A symbol effect that scales symbol images.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolScaleEffect : NSSymbolEffect

/// The default scaling effect, determined by the system.
+ (instancetype)effect;

/// Convenience initializer to create a scale effect with a scale up level.
+ (instancetype)scaleUpEffect;

/// Convenience initializer to create a scale effect with a scale down level.
+ (instancetype)scaleDownEffect;

/// Returns a copy of the effect that animates incrementally, by layer.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Appear Effect

/// A symbol effect that applies the Appear animation to
/// symbol images.
///
/// The Appear animation makes the symbol visible either as a whole,
/// or one motion group at a time.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolAppearEffect : NSSymbolEffect

/// The default appear effect, determined by the system.
+ (instancetype)effect;

/// Convenience initializer for an appear effect that appears scaling up.
+ (instancetype)appearUpEffect;

/// Convenience initializer for an appear effect that appears scaling down.
+ (instancetype)appearDownEffect;

/// Returns a copy of the effect that animates incrementally, by layer.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Disappear Effect

/// A symbol effect that applies the Disappear animation to
/// symbol images.
///
/// The Disappear animation makes the symbol visible either as a whole,
/// or one motion group at a time.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolDisappearEffect : NSSymbolEffect

/// The default disappear effect, determined by the system.
+ (instancetype)effect;

/// Convenience initializer for a disappear effect that disappears scaling up.
+ (instancetype)disappearUpEffect;

/// Convenience initializer for a disappear effect that disappears scaling down.
+ (instancetype)disappearDownEffect;

/// Returns a copy of the effect that animates incrementally, by layer.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Wiggle Effect

/// A symbol effect that applies the Wiggle animation to symbol images.
///
/// The Wiggle animation applies a transitory translation or rotation effect
/// to the symbol.
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolWiggleEffect : NSSymbolEffect

/// The default wiggle effect, determined by the system.
+ (instancetype)effect;

/// Convenience initializer for a wiggle effect that
/// rotates back and forth, starting by rotating clockwise.
+ (instancetype)wiggleClockwiseEffect;

/// Convenience initializer for a wiggle effect that
/// rotates back and forth, starting by rotating counter-clockwise.
+ (instancetype)wiggleCounterClockwiseEffect;

/// Convenience initializer for a wiggle effect that
/// moves back and forth horizontally, starting by moving left.
+ (instancetype)wiggleLeftEffect;

/// Convenience initializer for a wiggle effect that
/// moves back and forth horizontally, starting by moving right.
+ (instancetype)wiggleRightEffect;

/// Convenience initializer for a wiggle effect that
/// moves back and forth vertically, starting by moving up.
+ (instancetype)wiggleUpEffect;

/// Convenience initializer for a wiggle effect that
/// moves back and forth vertically, starting by moving down.
+ (instancetype)wiggleDownEffect;

/// Convenience initializer for a wiggle effect that moves back and forth
/// horizontally based on the current locale, starting by moving forward.
+ (instancetype)wiggleForwardEffect;

/// Convenience initializer for a wiggle effect that moves back and forth
/// horizontally based on the current locale, starting by moving backward.
+ (instancetype)wiggleBackwardEffect;

/// Convenience initializer for a wiggle effect that moves back and forth
/// along an axis, starting by moving toward a custom angle.
///
/// The angle is in degrees moving clockwise from the positive x-axis.
+ (instancetype)wiggleCustomAngleEffect:(double)angle;

/// Returns a copy of the effect that animates incrementally, by layer.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Rotate Effect

/// A symbol effect that applies the Rotate animation to
/// symbol images.
///
/// The Rotate animation rotates parts of a symbol around a
/// symbol-provided anchor point.
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolRotateEffect : NSSymbolEffect

/// The default rotate effect, determined by the system.
+ (instancetype)effect;

/// Convenience initializer for a rotate effect that rotates clockwise.
+ (instancetype)rotateClockwiseEffect;
    
/// Convenience initializer for a rotate effect that rotates counter-clockwise.
+ (instancetype)rotateCounterClockwiseEffect;

/// Returns a copy of the effect that animates incrementally, by layer.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - Breathe Effect

/// A symbol effect that applies the Breathe animation to
/// symbol images.
///
/// The Breathe animation smoothly scales a symbol up and down.
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolBreatheEffect : NSSymbolEffect

/// The default breathe effect, determined by the system.
+ (instancetype)effect;

/// Convenience initializer for a breathe effect that
/// pulses layers as they breathe.
+ (instancetype)breathePulseEffect;

/// Convenience initializer for a breathe effect that makes
/// the symbol breathe with no other styling.
+ (instancetype)breathePlainEffect;

/// Returns a copy of the effect that animates incrementally, by layer.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect that animates all layers of the symbol simultaneously.
- (instancetype)effectWithWholeSymbol;

@end

#pragma mark - DrawOn Effect

/// A symbol effect that applies the DrawOn animation to symbol images.
///
/// The DrawOn animation makes the symbol visible either as a whole, or
/// one motion group at a time, animating parts of the symbol with draw data.
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolDrawOnEffect : NSSymbolEffect

/// The default draw on effect, determined by the system.
+ (instancetype)effect;

/// Returns a copy of the effect requesting an animation that
/// applies separately to each motion group.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect requesting an animation that
/// applies to all motion groups simultaneously.
- (instancetype)effectWithWholeSymbol;

/// Returns a copy of the effect requesting an animation that
/// applies separately to each motion group, where only
/// one motion group is active at a time.
- (instancetype)effectWithIndividually;

@end

#pragma mark - DrawOff Effect

/// A symbol effect that applies the DrawOff animation to symbol images.
///
/// The DrawOff animation makes the symbol hidden either as a whole, or
/// one motion group at a time, animating parts of the symbol with draw data.
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolDrawOffEffect : NSSymbolEffect

/// The default draw off effect, determined by the system.
+ (instancetype)effect;

/// Returns a copy of the effect requesting an animation that
/// applies separately to each motion group.
- (instancetype)effectWithByLayer;

/// Returns a copy of the effect requesting an animation that
/// applies to all motion groups simultaneously.
- (instancetype)effectWithWholeSymbol;

/// Returns a copy of the effect requesting an animation that
/// applies separately to each motion group, where only
/// one motion group is active at a time.
- (instancetype)effectWithIndividually;

/// Returns a copy of the effect that animates in reverse. This cancels the nonReversed variant.
- (instancetype)effectWithReversed;

/// Returns a copy of the effect that only animates forwards. This cancels the reversed variant.
- (instancetype)effectWithNonReversed;

@end

#pragma mark - Base Content Transitions

/// An abstract base class for transitions that can be applied to both NSImageViews and
/// UIImageViews that have symbol-based images.
///
/// Don't use this class directly, instead use any of the concrete subclasses.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolContentTransition : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

#pragma mark - Replace Content Transition

#pragma mark - MagicReplace Content Transition

/// A symbol effect applies the MagicReplace animation to
/// symbol images.
///
/// The MagicReplace effect animates common elements across
/// symbol images.
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolMagicReplaceContentTransition : NSSymbolContentTransition
@end

/// A symbol effect that animates the replacement of one symbol image
/// with another.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolReplaceContentTransition : NSSymbolContentTransition

/// The default replace transition, determined by the system.
+ (instancetype)transition;

/// Convenience initializer for a replace content transition where the initial symbol
/// scales down as it is removed, and the new symbol scales up as it is added.
+ (instancetype)replaceDownUpTransition;

/// Convenience initializer for a replace content transition where the initial symbol
/// scales up as it is removed, and the new symbol scales up as it is added.
+ (instancetype)replaceUpUpTransition;

/// Convenience initializer for a replace content transition where the initial symbol
/// is removed with no animation, and the new symbol scales up as it is added.
+ (instancetype)replaceOffUpTransition;

/// Returns a copy of the content transition that animates incrementally, by layer.
- (instancetype)transitionWithByLayer;

/// Returns a copy of the content transition that animates all layers of the symbol simultaneously.
- (instancetype)transitionWithWholeSymbol;

/// Convenience initializer for a MagicReplace content transition with a configured Replace fallback.
+ (NSSymbolMagicReplaceContentTransition *)magicTransitionWithFallback:(NSSymbolReplaceContentTransition *)fallback API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

@end

#pragma mark - Automatic Content Transition

/// The default symbol transition, resolves to a particular transition in a
/// context-sensitive manner.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0)) NS_REFINED_FOR_SWIFT
@interface NSSymbolAutomaticContentTransition : NSSymbolContentTransition

/// The default automatic transition, determined by the system.
+ (instancetype)transition;

@end


NS_HEADER_AUDIT_END(nullability, sendability)

#endif /* NSSymbolEffect_h */
