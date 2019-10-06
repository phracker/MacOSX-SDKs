/*
	NSAccessibilityElement.h
	Application Kit
	Copyright (c) 2013-2019, Apple Inc.
	All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSAccessibilityConstants.h>
#import <AppKit/NSAccessibilityProtocols.h>

/* An NSAccessibilityElement is used to convey information regarding onscreen UI through the  accessibility API for UI that may not already have a single backing object. For example, if a single NSView subclass draws 4 buttons, it would vend 4 NSAccessibilityElements as accessibilityChildren. Note that as long as the UI is around, the vendor of NSAccessibilityElements must maintain ownership of the NSAccessibilityElements. */

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

API_AVAILABLE(macos(10.10))
@interface NSAccessibilityElement : NSObject <NSAccessibility>

+ (id)accessibilityElementWithRole:(NSAccessibilityRole)role frame:(NSRect)frame label:(nullable NSString *)label parent:(nullable id)parent;
- (void)accessibilityAddChildElement:(NSAccessibilityElement *)childElement;

// Accessibility frame in the cordinate system of the accessibility parent
@property NSRect accessibilityFrameInParentSpace;

@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
