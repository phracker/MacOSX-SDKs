#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICanvasFeedbackGenerator.h>)
//
//  UICanvasFeedbackGenerator.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <UIKit/UIFeedbackGenerator.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(17.5)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UICanvasFeedbackGenerator : UIFeedbackGenerator

/// Provide user feedback that an alignment occured, such as snapping to a guide or ruler.
/// - Parameter location: The location in the feedback's view where the alignment occured.
- (void)alignmentOccurredAtLocation:(CGPoint)location NS_SWIFT_NAME(alignmentOccurred(at:));

/// Provide user feedback that a path has been completed and/or recognized.
/// Can be used for things like path drawing and shape recognition.
/// - Parameter location: The location in the feedback's view where the completion occured.
- (void)pathCompletedAtLocation:(CGPoint)location NS_SWIFT_NAME(pathCompleted(at:));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UICanvasFeedbackGenerator.h>
#endif
