#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPencilInteraction.h>)
//
//  UIPencilInteraction.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIInteraction.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/* Preferred actions available to the user in Settings.
 */
typedef NS_ENUM(NSInteger, UIPencilPreferredAction) {
    /* No action, or the user has disabled pencil interactions in Accessibility settings */
    UIPencilPreferredActionIgnore = 0,
    
    /* Switch between the current tool and eraser */
    UIPencilPreferredActionSwitchEraser,
    
    /* Switch between the current tool and the previously used tool */
    UIPencilPreferredActionSwitchPrevious,
    
    /* Show and hide the color palette */
    UIPencilPreferredActionShowColorPalette,
    
} API_AVAILABLE(ios(12.1)) API_UNAVAILABLE(watchos, tvos);


@protocol UIPencilInteractionDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(12.1)) API_UNAVAILABLE(watchos, tvos) @interface UIPencilInteraction : NSObject <UIInteraction>

@property (class, nonatomic, readonly) UIPencilPreferredAction preferredTapAction;
@property (class, nonatomic, readonly) BOOL prefersPencilOnlyDrawing;

@property (nonatomic, weak, nullable) id <UIPencilInteractionDelegate> delegate;

@property (nonatomic, getter=isEnabled) BOOL enabled;

@end


API_AVAILABLE(ios(12.1)) API_UNAVAILABLE(watchos, tvos) @protocol UIPencilInteractionDelegate <NSObject>

@optional

/* Called when the user taps on the side of the pencil, if the interaction's view is in a visible view hierarchy.
 *
 * The delegate may do anything in this method.  To perform the user's preferred action (as set in Settings), 
 * consult the preferredTapAction class property of UIPencilInteraction.
 */
- (void)pencilInteractionDidTap:(UIPencilInteraction *)interaction;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPencilInteraction.h>
#endif
