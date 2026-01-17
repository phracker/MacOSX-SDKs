/*
	NSUserInterfaceValidation.h
	Application Kit
	Copyright (c) 1999-2024, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

/*
This file defines the protocols used by AppKit's standard user interface validation mechanism.  The NSValidatedUserInterfaceItem protocol must be implemented by validated objects. The validated object should send a -validateUserInterfaceItem: message to its validator.  A validator can be determined by calling the -[NSApplication targetForAction:to:from:] method from the -update method in the validated object.

You can extend this functionality by introducing a new set of protocols that are targeted to your specific validated objects.  NSMenuItem protocol is one example extending this validation machinery to allow validators to modify menu items being validated. These are the steps to extend UI validation:
 
 1) Declare a subprotocol of NSValidatedUserInterfaceItem
    You can add as many features as you want for your validated objects in this protocol
    i.e.
        @protocol NSValidatedToolbarItem <NSValidatedUserInterfaceItem>
        - (NSImage *)image;
        - (void)setImage:(NSImage *)image
        - (NSString *)toolTip;
        - (void)setToolTip:(NSString *)toolTip;
        @end

 2) Declare validation method for validators
    You should declare your new selector that takes your object as the argument.
    i.e.
        @protocol NSToolbarItemValidation
        - (BOOL)validateToolbarItem:(id <NSValidatedToolbarItem>)item;
        @end

 3) Implement your -update method
    You should first check if your current validator responds to your validation method,
    then, the generic -validateUserInterfaceItem: method. This way, your object can be automatically
    enabled/disabled by the kit's standard objects like NSTextView without any additional code.
    i.e.
        - (void)update {
            id validator = [NSApp targetForAction:[self action] to:[self target] from:self];

            if ((validator == nil) || ![validator respondsToSelector:[self action]]) {
                [self setEnabled:NO];
            } else if ([validator respondsToSelector:@selector(validateToolbarItem:)]) {
                [self setEnabled:[validator validateToolbarItem:self]];
            } else if ([validator respondsToSelector:@selector(validateUserInterfaceItem:)]) {
                [self setEnabled:[validator validateUserInterfaceItem:self]];
            } else {
                [self setEnabled:YES];
            }
        }

 4) Implement category methods for standard objects (Optional)
    Now you can implement default validation methods for standard objects like NSTextView or NSDocument.
    i.e.
        @implementation NSTextView (NSToolbarItemValidation)
    
        - (BOOL)validateToolbarItem:(id <NSValidatedToolbarItem>)item {
            BOOL returnValue = [self validateUserInterfaceItem:item];

            // Your own validation
        
            return returnValue;
        }
        @end
*/

/* Protocol implemented by validated objects */
NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@protocol NSValidatedUserInterfaceItem
@property (readonly, nullable) SEL action NS_SWIFT_UI_ACTOR;
@property (readonly) NSInteger tag NS_SWIFT_UI_ACTOR;
@end

/* Protocol implemented by validator objects */
@protocol NSUserInterfaceValidations
- (BOOL)validateUserInterfaceItem:(id <NSValidatedUserInterfaceItem>)item NS_SWIFT_UI_ACTOR;
@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
