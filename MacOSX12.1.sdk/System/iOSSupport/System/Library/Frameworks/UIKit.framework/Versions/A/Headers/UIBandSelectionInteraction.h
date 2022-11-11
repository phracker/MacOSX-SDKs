#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBandSelectionInteraction.h>)
//
//  UIBandSelectionInteraction.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIInteraction.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIBandSelectionInteractionState) {
    UIBandSelectionInteractionStatePossible = 0,
    UIBandSelectionInteractionStateBegan,
    UIBandSelectionInteractionStateSelecting,
    UIBandSelectionInteractionStateEnded,
} API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIBandSelectionInteraction : NSObject <UIInteraction>

/// Indicates whether the interaction is enabled. Defaults to YES.
@property (nonatomic, getter=isEnabled) BOOL enabled;

/// The interaction's current state.
@property (nonatomic, readonly) UIBandSelectionInteractionState state;

/// The current selection rect. Returns CGRectNull when the interaction is inactive.
@property (nonatomic, readonly) CGRect selectionRect;

/// Modifier keys held at the beginning of the interaction.
@property (nonatomic, readonly) UIKeyModifierFlags initialModifierFlags;

/// Called when the interaction is about to begin.
/// Return a boolean indicating whether the interaction should begin at the given location.
@property (nonatomic, copy, nullable) BOOL (^shouldBeginHandler)(UIBandSelectionInteraction *interaction, CGPoint point);

/*!
 * @abstract Creates a UIBandSelectionInteraction with the given selection handler.
 *
 * @param selectionHandler  Called when the interaction's state and/or selection rect change.
 */
- (instancetype)initWithSelectionHandler:(void (^)(UIBandSelectionInteraction *interaction))selectionHandler;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END


#else
#import <UIKitCore/UIBandSelectionInteraction.h>
#endif
