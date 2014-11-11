/*
    NSTextFieldCell.h
    Application Kit
    Copyright (c) 1994-2014, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSActionCell.h>

typedef NS_ENUM(NSUInteger, NSTextFieldBezelStyle) {
    NSTextFieldSquareBezel  = 0,
    NSTextFieldRoundedBezel = 1
};

@class NSColor;

@interface NSTextFieldCell : NSActionCell  {
    /*All instance variables are private*/
    NSColor *_backgroundColor;
    NSColor *_textColor;
    struct __tfFlags {
        unsigned int drawsBackground:1;
        unsigned int bezelStyle:3;
        unsigned int thcSortDirection:2;
        unsigned int thcSortPriority:4;
        unsigned int mini:1;
        unsigned int textColorIgnoresNormalDisableFlag:1;
        unsigned int textColorDisableFlag:1;
        unsigned int thcForceHighlightForSort:1;
        unsigned int invalidTextColor:1;
        unsigned int notificationForMarkedText:1;
        unsigned int inToolbar:1;
        unsigned int hasTextLayer:1;
        unsigned int isButtonTitle:1;
        unsigned int allowTightening:1;
        unsigned int thcHighlighted:1;
        unsigned int reservedTextFieldCell:11;
    } _tfFlags;
}

@property (copy) NSColor *backgroundColor;
@property BOOL drawsBackground;
@property (copy) NSColor *textColor;
- (NSText *)setUpFieldEditorAttributes:(NSText *)textObj;

@property NSTextFieldBezelStyle bezelStyle;

@property (copy) NSString *placeholderString;
@property (copy) NSAttributedString *placeholderAttributedString;

- (void)setWantsNotificationForMarkedText:(BOOL)flag NS_AVAILABLE_MAC(10_5);

/* Returns an array of locale identifiers representing keyboard input sources allowed to be enabled when the receiver has the keyboard focus.
 */
@property (copy) NSArray *allowedInputSourceLocales NS_AVAILABLE_MAC(10_5);

@end

