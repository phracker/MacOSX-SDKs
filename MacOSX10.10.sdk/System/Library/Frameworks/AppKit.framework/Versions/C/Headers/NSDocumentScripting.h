/*
        NSDocumentScripting.h
        AppKit Framework
        Copyright (c) 1997-2014, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSDocument.h>

@class NSCloseCommand;
@class NSScriptCommand;
@class NSScriptObjectSpecifier;
@class NSString;

@interface NSDocument (NSScripting)

@property (copy) NSString *lastComponentOfFileName;

- (id)handleSaveScriptCommand:(NSScriptCommand *)command;
- (id)handleCloseScriptCommand:(NSCloseCommand *)command;
- (id)handlePrintScriptCommand:(NSScriptCommand *)command;

@property (readonly, strong) NSScriptObjectSpecifier *objectSpecifier;

@end
