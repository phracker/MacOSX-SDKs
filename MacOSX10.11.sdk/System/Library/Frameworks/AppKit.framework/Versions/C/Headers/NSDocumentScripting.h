/*
        NSDocumentScripting.h
        AppKit Framework
        Copyright (c) 1997-2015, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSDocument.h>

NS_ASSUME_NONNULL_BEGIN

@class NSCloseCommand;
@class NSScriptCommand;
@class NSScriptObjectSpecifier;
@class NSString;

@interface NSDocument (NSScripting)

@property (copy) NSString *lastComponentOfFileName;

- (nullable id)handleSaveScriptCommand:(NSScriptCommand *)command;
- (nullable id)handleCloseScriptCommand:(NSCloseCommand *)command;
- (nullable id)handlePrintScriptCommand:(NSScriptCommand *)command;

@property (readonly, strong) NSScriptObjectSpecifier *objectSpecifier;

@end

NS_ASSUME_NONNULL_END
