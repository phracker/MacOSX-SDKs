/*
        NSSecureTextField.h
        Application Kit
        Copyright (c) 1995-2015, Apple Inc.
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
    BOOL _echosBullets;
    BOOL _csMode;
}

@property BOOL echosBullets;

@end
