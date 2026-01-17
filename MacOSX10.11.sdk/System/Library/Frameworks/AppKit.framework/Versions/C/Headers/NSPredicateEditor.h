/*
        NSPredicateEditor.h
	Application Kit
	Copyright (c) 2006-2015, Apple Inc.
	All rights reserved.
*/


#import <Foundation/NSArray.h>
#import <AppKit/NSRuleEditor.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPredicateTemplate, NSArray, NSPredicateEditorRowTemplate;

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

/* Setter - Sets the NSPredicateEditorRowTemplates for the NSPredicateEditor.  When created, NSPredicateEditor contains a template representing compound predicates; if you wish to keep it, you should take care to include it in this array.
*/
/* Getter - Returns the row templates for this NSPredicateEditor.
*/
@property (copy) NSArray<NSPredicateEditorRowTemplate *> *rowTemplates;

@end

NS_ASSUME_NONNULL_END

