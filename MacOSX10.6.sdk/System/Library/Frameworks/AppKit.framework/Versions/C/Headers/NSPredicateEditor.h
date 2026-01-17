/*
        NSPredicateEditor.h
	Application Kit
	Copyright (c) 2006-2009, Apple Inc.
	All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

#import <AppKit/NSRuleEditor.h>

@class NSPredicateTemplate, NSArray;

@interface NSPredicateEditor : NSRuleEditor {
    id _allTemplates;
    NSArray *_rootTrees;
    NSArray *_rootHeaderTrees;
    id _predicateTarget;
    SEL _predicateAction;
    struct {
	unsigned suppressAction:4;
	unsigned reserved:28;
    } _peFlags;
    id _predicateEditorReserved[3];
}

/* Sets the NSPredicateEditorRowTemplates for the NSPredicateEditor.  When created, NSPredicateEditor contains a template representing compound predicates; if you wish to keep it, you should take care to include it in this array.
*/
- (void)setRowTemplates:(NSArray *)rowTemplates;

/* Returns the row templates for this NSPredicateEditor.
*/
- (NSArray *)rowTemplates;

@end

#endif
