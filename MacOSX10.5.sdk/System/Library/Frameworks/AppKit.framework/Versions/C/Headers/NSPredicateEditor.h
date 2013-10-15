/*
        NSPredicateEditor.h
	Application Kit
	Copyright (c) 2006-2007, Apple Inc.
	All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

#import <AppKit/NSRuleEditor.h>

@class NSPredicateTemplate, NSArray;

@interface NSPredicateEditor : NSRuleEditor {
    id _allTemplates;
    
    NSArray *_rootItems;
    NSArray *_rootHeaderItems;
    
    id _predicateTarget;
    SEL _predicateAction;
    
    struct {
	unsigned settingValue:1;
	unsigned reserved:31;
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
