/*
        NSPredicateEditor.h
	Application Kit
	Copyright (c) 2006-2018, Apple Inc.
	All rights reserved.
*/


#import <Foundation/NSArray.h>
#import <AppKit/NSRuleEditor.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPredicateTemplate, NSArray, NSPredicateEditorRowTemplate;

NS_CLASS_AVAILABLE(10_5, NA)
@interface NSPredicateEditor : NSRuleEditor {
    id _allTemplates APPKIT_IVAR;
    NSArray *_rootTrees APPKIT_IVAR;
    NSArray *_rootHeaderTrees APPKIT_IVAR;
    id _predicateTarget APPKIT_IVAR;
    SEL _predicateAction APPKIT_IVAR;
    struct {
	unsigned suppressAction:4;
	unsigned reserved:28;
    } _peFlags APPKIT_IVAR;
    id _predicateEditorReserved[3] APPKIT_IVAR;
}

/* Setter - Sets the NSPredicateEditorRowTemplates for the NSPredicateEditor.  When created, NSPredicateEditor contains a template representing compound predicates; if you wish to keep it, you should take care to include it in this array.
*/
/* Getter - Returns the row templates for this NSPredicateEditor.
*/
@property (copy) NSArray<NSPredicateEditorRowTemplate *> *rowTemplates;

@end

NS_ASSUME_NONNULL_END

