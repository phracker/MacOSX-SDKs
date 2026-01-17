/*
        NSPredicateEditor.h
	Application Kit
	Copyright (c) 2006-2019, Apple Inc.
	All rights reserved.
*/


#import <Foundation/NSArray.h>
#import <AppKit/NSRuleEditor.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@class NSArray, NSPredicateEditorRowTemplate;

API_AVAILABLE(macos(10.5))
@interface NSPredicateEditor : NSRuleEditor

/* Setter - Sets the NSPredicateEditorRowTemplates for the NSPredicateEditor.  When created, NSPredicateEditor contains a template representing compound predicates; if you wish to keep it, you should take care to include it in this array.
*/
/* Getter - Returns the row templates for this NSPredicateEditor.
*/
@property (copy) NSArray<NSPredicateEditorRowTemplate *> *rowTemplates;

@end




API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END

