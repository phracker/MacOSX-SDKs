/*
        NSTreeNode.h
	AppKit
	Copyright (c) 2007-2015, Apple Inc.
	All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>

NS_ASSUME_NONNULL_BEGIN

@class NSIndexPath, NSSortDescriptor, NSTreeController;

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

+ (null_unspecified instancetype)treeNodeWithRepresentedObject:(null_unspecified id)modelObject;
- (instancetype)initWithRepresentedObject:(null_unspecified id)modelObject;

@property (null_unspecified, readonly, strong) id representedObject;

    // stats
@property (readonly, strong) NSIndexPath *indexPath; // represents the receivers location in entire tree
@property (getter=isLeaf, readonly) BOOL leaf; // determined by (count of child nodes == 0)
    
@property (nullable, readonly, copy) NSArray<NSTreeNode *> *childNodes;    // traversal
@property (null_unspecified, readonly, strong) NSMutableArray<NSTreeNode *> *mutableChildNodes; // returns a mutable proxy - parentNode of inserted/removed child nodes is automatically updated
- (nullable NSTreeNode *)descendantNodeAtIndexPath:(NSIndexPath *)indexPath; // traversal begins with receiver

@property (nullable, readonly, assign) NSTreeNode *parentNode;

    // sorts the entire subtree
- (void)sortWithSortDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors recursively:(BOOL)recursively;

@end

NS_ASSUME_NONNULL_END

