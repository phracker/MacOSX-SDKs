/*	CFTree.h
	Copyright 1998-2001, Apple, Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFTREE__)
#define __COREFOUNDATION_CFTREE__ 1

#include <CoreFoundation/CFBase.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef const void *	(*CFTreeRetainCallBack)(const void *info);
typedef void		(*CFTreeReleaseCallBack)(const void *info);
typedef CFStringRef	(*CFTreeCopyDescriptionCallBack)(const void *info);
typedef struct {
    CFIndex				version;
    void *				info;
    CFTreeRetainCallBack		retain;
    CFTreeReleaseCallBack		release;	
    CFTreeCopyDescriptionCallBack	copyDescription;
} CFTreeContext;

typedef void (*CFTreeApplierFunction)(const void *value, void *context);

typedef struct __CFTree * CFTreeRef;

CF_EXPORT
CFTypeID CFTreeGetTypeID(void);

CF_EXPORT
CFTreeRef CFTreeCreate(CFAllocatorRef allocator, const CFTreeContext *context);

CF_EXPORT
CFTreeRef CFTreeGetParent(CFTreeRef tree);

CF_EXPORT
CFTreeRef CFTreeGetNextSibling(CFTreeRef tree);

CF_EXPORT
CFTreeRef CFTreeGetFirstChild(CFTreeRef tree);

CF_EXPORT
void CFTreeGetContext(CFTreeRef tree, CFTreeContext *context);

CF_EXPORT
CFIndex CFTreeGetChildCount(CFTreeRef tree);

CF_EXPORT
CFTreeRef CFTreeGetChildAtIndex(CFTreeRef tree, CFIndex idx);

CF_EXPORT
void CFTreeGetChildren(CFTreeRef tree, CFTreeRef *children);

CF_EXPORT
void CFTreeApplyFunctionToChildren(CFTreeRef tree, CFTreeApplierFunction applier, void *context);

CF_EXPORT
CFTreeRef CFTreeFindRoot(CFTreeRef tree);

CF_EXPORT
void CFTreeSetContext(CFTreeRef tree, const CFTreeContext *context);

/* adds newChild as tree's first child */
CF_EXPORT
void CFTreePrependChild(CFTreeRef tree, CFTreeRef newChild);

/* adds newChild as tree's last child */
CF_EXPORT
void CFTreeAppendChild(CFTreeRef tree, CFTreeRef newChild);

/* Inserts newSibling after tree.  tree and newSibling will have the same parent */
CF_EXPORT
void CFTreeInsertSibling(CFTreeRef tree, CFTreeRef newSibling);

/* Removes tree from its parent */
CF_EXPORT
void CFTreeRemove(CFTreeRef tree);

/* Removes all the children of tree */
CF_EXPORT
void CFTreeRemoveAllChildren(CFTreeRef tree);

/* NOTE: not yet implemented. */
CF_EXPORT
void CFTreeSortChildren(CFTreeRef tree, CFComparatorFunction comparator, void *context);

#if defined(__cplusplus)
}
#endif

#endif /* ! __COREFOUNDATION_CFTREE__ */

