/*
        NSDocumentScripting.h
        AppKit Framework
        Copyright (c) 1997-2004, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSDocument.h>

@class NSCloseCommand;
@class NSScriptCommand;
@class NSScriptObjectSpecifier;
@class NSString;

@interface NSDocument (NSScripting)

- (NSString *)lastComponentOfFileName;
- (void)setLastComponentOfFileName:(NSString *)str;

- (id)handleSaveScriptCommand:(NSScriptCommand *)command;
- (id)handleCloseScriptCommand:(NSCloseCommand *)command;
- (id)handlePrintScriptCommand:(NSScriptCommand *)command;

- (NSScriptObjectSpecifier *)objectSpecifier;

@end
