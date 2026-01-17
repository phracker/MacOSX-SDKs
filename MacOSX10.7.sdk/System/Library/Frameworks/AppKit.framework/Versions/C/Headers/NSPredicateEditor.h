/*
        NSPredicateEditor.h
	Application Kit
	Copyright (c) 2006-2011, Apple Inc.
	All rights reserved.
*/


#import <AppKit/NSRuleEditor.h>

@class NSPredicateTemplate, NSArray;

NS_CLASS_AVAILABLE(10_5, NA)
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

