/**
 @header
 
 NSAccessibility additions to SKNode.
 
 @copyright 2015 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SKNode.h>

@interface SKNode (NSAccessibility)

// See the NSAccessibility Protocol Reference in Apple's developer documentation for detailed analysis of these properties and methods.

// Return YES if the UIElement should be exposed
@property (nonatomic, getter = isAccessibilityElement) BOOL accessibilityElement;

// Role, non - localized
@property (nonatomic, nullable, copy) NSString *accessibilityRole;

// Human readable role description
@property (nonatomic, nullable, copy) NSString *accessibilityRoleDescription;

// Sub-role, non - localized
@property (nonatomic, nullable, copy) NSString *accessibilitySubrole;

// The frame of the UIElement in screen coordinates.
@property (nonatomic) CGRect accessibilityFrame;

// Element containing this UIElement
@property (nonatomic, nullable, weak) id accessibilityParent;

// Array of UIElements that represent children of the current UIElement
@property (nonatomic, nullable, copy) NSArray *accessibilityChildren;

// Instance description (e.g. a tool tip)
@property (nonatomic, nullable, copy) NSString *accessibilityHelp;

// Description of UIElement
@property (nonatomic, nullable, copy) NSString *accessibilityLabel;

// Returns YES if the element responds to user events
@property (nonatomic, getter = isAccessibilityEnabled) BOOL accessibilityEnabled;

/* Returns the deepest descendant of the UIElement hierarchy that contains the point. You can assume the point has already been determined to lie within the receiver. Override this method to do deeper hit testing within a UIElement. The point is bottom-left relative screen coordinates.
 */
- (nullable id)accessibilityHitTest:(CGPoint)point;

@end
