//
//  BETextInteractionDelegate.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>

@class BETextInteraction;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@protocol BETextInteractionDelegate

/**
 *  Invoked by the system when the selection is about to change in the document.
 */
- (void)systemWillChangeSelectionForInteraction:(BETextInteraction *)textInteraction;

/**
 *  Invoked by the system when the selection is about to change in the document.
 */
- (void)systemDidChangeSelectionForInteraction:(BETextInteraction *)textInteraction;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
