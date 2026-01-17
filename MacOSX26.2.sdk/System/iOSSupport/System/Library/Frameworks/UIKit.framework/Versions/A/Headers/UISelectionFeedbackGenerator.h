#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISelectionFeedbackGenerator.h>)
//
//  UISelectionFeedbackGenerator.h
//  UIKit
//
//  Copyright © 2016-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIFeedbackGenerator.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// UISelectionFeedbackGenerator is used to give user feedback when a selection changes
UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(visionos, tvos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UISelectionFeedbackGenerator : UIFeedbackGenerator

/// call when the selection changes (not on initial selection)
- (void)selectionChanged;

/// call when the selection changes (not on initial selection)
/// provide the location in the `view` the change occured at
- (void)selectionChangedAtLocation:(CGPoint)location API_AVAILABLE(ios(17.5)) API_UNAVAILABLE(visionos) NS_SWIFT_NAME(selectionChanged(at:));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISelectionFeedbackGenerator.h>
#endif
