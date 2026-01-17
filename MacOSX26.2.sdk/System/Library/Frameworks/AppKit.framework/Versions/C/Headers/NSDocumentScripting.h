/*
        NSDocumentScripting.h
        AppKit Framework
        Copyright (c) 1997-2024, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSDocument.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

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

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
