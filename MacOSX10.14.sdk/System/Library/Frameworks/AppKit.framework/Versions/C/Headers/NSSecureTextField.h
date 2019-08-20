/*
        NSSecureTextField.h
        Application Kit
        Copyright (c) 1995-2018, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSTextField.h>
#import <AppKit/NSTextFieldCell.h>

@interface NSSecureTextField : NSTextField {
/*All instance variables are private*/
}
@end

@interface NSSecureTextFieldCell : NSTextFieldCell {
/*All instance variables are private*/
    @private
    BOOL _echosBullets APPKIT_IVAR;
    BOOL _csMode __unused APPKIT_IVAR;
}

@property BOOL echosBullets;

@end
