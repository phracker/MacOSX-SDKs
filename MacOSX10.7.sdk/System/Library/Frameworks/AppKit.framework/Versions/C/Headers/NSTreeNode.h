/*
        NSTreeNode.h
	AppKit
	Copyright (c) 2007-2011, Apple Inc.
	All rights reserved.
 */

#import <Foundation/NSObject.h>


@class NSArray, NSMutableArray, NSIndexPath, NSTreeController;

NS_CLASS_AVAILABLE(10_5, NA)
@interface NSTreeNode : NSObject {
    id _childNodesProxy;
    id _representedObject;
    __strong void *_observationInfo;
    id _reserved2;
    NSMutableArray *_childNodes;
    NSTreeNode *_parentNode;//not retained
    struct __NSTreeNodeFlags {
	unsigned int ignoreObserving:1;
	unsigned int reserved:31;
    } _NSTreeNodeFlags;
}

+ (id)treeNodeWithRepresentedObject:(id)modelObject;
- (id)initWithRepresentedObject:(id)modelObject;

- (id)representedObject;

    // stats
- (NSIndexPath *)indexPath; // represents the receivers location in entire tree
- (BOOL)isLeaf; // determined by (count of child nodes == 0)
    
- (NSArray *)childNodes;    // traversal
- (NSMutableArray *)mutableChildNodes; // returns a mutable proxy - parentNode of inserted/removed child nodes is automatically updated
- (NSTreeNode *)descendantNodeAtIndexPath:(NSIndexPath *)indexPath; // traversal begins with receiver

- (NSTreeNode *)parentNode;

    // sorts the entire subtree
- (void)sortWithSortDescriptors:(NSArray *)sortDescriptors recursively:(BOOL)recursively;

@end

