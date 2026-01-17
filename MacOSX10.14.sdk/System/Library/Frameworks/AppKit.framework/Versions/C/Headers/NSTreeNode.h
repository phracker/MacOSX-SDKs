/*
        NSTreeNode.h
	AppKit
	Copyright (c) 2007-2018, Apple Inc.
	All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSIndexPath, NSSortDescriptor, NSTreeController;

NS_CLASS_AVAILABLE(10_5, NA)
@interface NSTreeNode : NSObject {
    id _childNodesProxy APPKIT_IVAR;
    id _representedObject APPKIT_IVAR;
    void *_observationInfo APPKIT_IVAR;
    id _reserved2 APPKIT_IVAR;
    NSMutableArray *_childNodes APPKIT_IVAR;
    __weak NSTreeNode *_parentNode APPKIT_IVAR;
    struct __NSTreeNodeFlags {
	unsigned int ignoreObserving:1;
	unsigned int reserved:31;
    } _NSTreeNodeFlags APPKIT_IVAR;
}

+ (instancetype)treeNodeWithRepresentedObject:(nullable id)modelObject;
- (instancetype)initWithRepresentedObject:(nullable id)modelObject;

@property (nullable, readonly, strong) id representedObject;

@property (readonly, strong) NSIndexPath *indexPath; // represents the receiver's location in the entire tree
@property (getter=isLeaf, readonly) BOOL leaf; // determined by (count of child nodes == 0)
    
@property (nullable, readonly, copy) NSArray<NSTreeNode *> *childNodes; // traversal
@property (readonly, strong) NSMutableArray<NSTreeNode *> *mutableChildNodes; // returns a mutable proxy - parentNode of inserted/removed child nodes is automatically updated
- (nullable NSTreeNode *)descendantNodeAtIndexPath:(NSIndexPath *)indexPath; // traversal begins with receiver

@property (nullable, readonly, weak) NSTreeNode *parentNode;

// sorts the entire subtree
- (void)sortWithSortDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors recursively:(BOOL)recursively;

@end

NS_ASSUME_NONNULL_END

