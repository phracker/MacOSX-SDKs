/*
     File:       CarbonCore/AVLTree.h
 
     Contains:   Interfaces for AVL balanced trees.
 
     Version:    CarbonCore-472~1
 
     Copyright:  © 1999-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AVLTREE__
#define __AVLTREE__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif


/* The visit stage for AVLWalk() walkProcs */

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k


/*
 *  AVLTree
 *  
 *  Discussion:
 *    Prototypes for routines which create, destroy, allow for
 *    insertion, deleting, and iteration of routines in an AVL balanced
 *    binary tree. 
 *    
 *    An AVL tree is a balanced, binary tree which is fairly fast for
 *    finds and acceptably fast for insertion and deletion.  The tree
 *    is kept balanced, so that the heights of any given node's left
 *    and right branches never differ by more than 1, which keeps
 *    performance from being too horribe in the degenerate case.
 *    
 *    
 *    Very loosely based on some public domain source code for doing
 *    avl trees and on the discussion in Sedgewick "Algorithms" book.
 */
typedef UInt16 AVLVisitStage;
enum {
  kAVLPreOrder                  = 0,
  kAVLInOrder                   = 1,
  kAVLPostOrder                 = 2
};

/* The order the tree is walked or disposed of. */
typedef UInt16 AVLOrder;
enum {
  kLeftToRight                  = 0,
  kRightToLeft                  = 1
};

/* The type of the node being passed to a callback proc. */
typedef UInt16 AVLNodeType;
enum {
  kAVLIsTree                    = 0,
  kAVLIsLeftBranch              = 1,
  kAVLIsRightBranch             = 2,
  kAVLIsLeaf                    = 3,
  kAVLNullNode                  = 4
};

enum {
  errItemAlreadyInTree          = -960,
  errNotValidTree               = -961,
  errItemNotFoundInTree         = -962,
  errCanNotInsertWhileWalkProcInProgress = -963,
  errTreeIsLocked               = -964
};

/*  The structure of a tree.  It's opaque; don't assume it's 36 bytes in size.*/
struct AVLTreeStruct {
  OSType              signature;
  unsigned long       privateStuff[8];
};
typedef struct AVLTreeStruct            AVLTreeStruct;
typedef AVLTreeStruct *                 AVLTreePtr;
/*
    Every tree must have a function which compares the data for two items and returns < 0, 0, or >0
    for the items - < 0 if the first item is 'before' the second item according to some criteria,
    == 0 if the two items are identical according to the criteria, or > 0 if the first item is
    'after' the second item according to the criteria.  The comparison function is also passed the
    node type, but most of the time this can be ignored.
*/
typedef CALLBACK_API( SInt32 , AVLCompareItemsProcPtr )(AVLTreePtr tree, const void *i1, const void *i2, AVLNodeType nd_typ);
/*
    Every tree must have a itemSizeProc; this routine gets passed a pointer to the item's data and
    returns the size of the data.  If a tree contains records of a fixed size, this function can
    just return sizeof( that-struct ); otherwise it should calculate the size of the item based on
    the data for the item.
*/
typedef CALLBACK_API( UInt32 , AVLItemSizeProcPtr )(AVLTreePtr tree, const void *itemPtr);
/*
    A tree may have an optional disposeItemProc, which gets called whenever an item is removed
    from the tree ( via AVLRemove() or when AVLDispose() deletes all of the items in the tree ).
    This might be useful if the nodes in the tree own 'resources'  ( like, open files ) which
    should be released before the item is removed.
*/
typedef CALLBACK_API( void , AVLDisposeItemProcPtr )(AVLTreePtr tree, const void *dataP);
/*
    The common way to iterate across all of the items in a tree is via AVLWalk(), which takes
    a walkProcPtr.  This function will get called for every item in the tree three times, as
    the tree is being walked across.  First, the walkProc will get called with visitStage ==
    kAVLPreOrder, at which point internally the node of the tree for the given data has just
    been reached.  Later, this function will get called with visitStage == kAVLInOrder, and
    lastly this function will get called with visitStage == kAVLPostOrder.
    The 'minimum' item in the tree will get called with visitStage == kInOrder first, followed
    by the 'next' item in the tree, up until the last item in the tree structure is called.
    In general, you'll only care about calls to this function when visitStage == kAVLInOrder.
*/
typedef CALLBACK_API( OSErr , AVLWalkProcPtr )(AVLTreePtr tree, const void *dataP, AVLVisitStage visitStage, AVLNodeType node, UInt32 level, SInt32 balance, void *refCon);
typedef STACK_UPP_TYPE(AVLCompareItemsProcPtr)                  AVLCompareItemsUPP;
typedef STACK_UPP_TYPE(AVLItemSizeProcPtr)                      AVLItemSizeUPP;
typedef STACK_UPP_TYPE(AVLDisposeItemProcPtr)                   AVLDisposeItemUPP;
typedef STACK_UPP_TYPE(AVLWalkProcPtr)                          AVLWalkUPP;
/*
 *  NewAVLCompareItemsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern AVLCompareItemsUPP
NewAVLCompareItemsUPP(AVLCompareItemsProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewAVLItemSizeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern AVLItemSizeUPP
NewAVLItemSizeUPP(AVLItemSizeProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewAVLDisposeItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern AVLDisposeItemUPP
NewAVLDisposeItemUPP(AVLDisposeItemProcPtr userRoutine)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewAVLWalkUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern AVLWalkUPP
NewAVLWalkUPP(AVLWalkProcPtr userRoutine)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeAVLCompareItemsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeAVLCompareItemsUPP(AVLCompareItemsUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeAVLItemSizeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeAVLItemSizeUPP(AVLItemSizeUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeAVLDisposeItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeAVLDisposeItemUPP(AVLDisposeItemUPP userUPP)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeAVLWalkUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeAVLWalkUPP(AVLWalkUPP userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeAVLCompareItemsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SInt32
InvokeAVLCompareItemsUPP(
  AVLTreePtr          tree,
  const void *        i1,
  const void *        i2,
  AVLNodeType         nd_typ,
  AVLCompareItemsUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeAVLItemSizeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern UInt32
InvokeAVLItemSizeUPP(
  AVLTreePtr      tree,
  const void *    itemPtr,
  AVLItemSizeUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeAVLDisposeItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeAVLDisposeItemUPP(
  AVLTreePtr         tree,
  const void *       dataP,
  AVLDisposeItemUPP  userUPP)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeAVLWalkUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeAVLWalkUPP(
  AVLTreePtr     tree,
  const void *   dataP,
  AVLVisitStage  visitStage,
  AVLNodeType    node,
  UInt32         level,
  SInt32         balance,
  void *         refCon,
  AVLWalkUPP     userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
    Create an AVL tree.  The compareItemsProc and the sizeItemProc are required; disposeItemProc is
    optional and can be nil.  The refCon is stored with the list, and is passed back to the
    compareItemsProc, sizeItemProc, and disposeItemsProc calls.  The allocation of the tree ( and all
    nodes later added to the list with AVLInsert ) will be created in what is the current zone at the
    time AVLInit() is called.  Always call AVLDispose() to dispose of a list created with AVLInit().
*/
/*
 *  AVLInit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
AVLInit(
  UInt32               flags,
  AVLCompareItemsUPP   compareItemsProc,
  AVLItemSizeUPP       sizeItemProc,
  AVLDisposeItemUPP    disposeItemProc,
  void *               refCon,
  AVLTreePtr *         tree)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Dispose of an AVL tree.  This will dispose of each item in the tree in the order specified,
    call the tree's disposeProc proc for each item, and then dispose of the space allocated for
    the tree itself.
*/
/*
 *  AVLDispose()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
AVLDispose(
  AVLTreePtr *  tree,
  AVLOrder      order)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Iterate across all of the items in the tree, in the order specified.  kLeftToRight is
    basically lowest-to-highest order, kRightToLeft is highest-to-lowest order.  For each
    node in the tree, it will call the walkProc with three messages ( at the appropriate 
    time ).  First, with kAVLPreOrder when the walking gets to this node in the tree,
    before handling either the left or right subtree, secondly, with kAVLInOrder after
    handling one subtree but before handling the other, and lastly with kAVLPostOrder after
    handling both subtrees.  If you want to handle items in order, then only do something
    if the visit stage is kAVLInOrder.  You can only call AVLRemove() from inside a walkProc
    if visit stage is kAVLPostOrder ( because if you remove a node during the pre or in order
    stages you will corrupt the list ) OR if you return a non-zero result from the walkProc
    call which called AVLRemove() to immediately terminate the walkProc.  Do not call AVLInsert()
    to insert a node into the tree from inside a walkProc.
    The walkProc function gets called with the AVLTreePtr, a pointer to the data for the
    current node ( which you can change in place as long as you do not affect the order within
    the tree ), the visit stage, the type of the current node ( leaf node, right or left branch,
    or full tree ), the level within the tree ( the root is level 1 ), the balance for the
    current node, and the refCon passed to AVLWalk().  This refCon is different from the one passed
    into AVLInit(); use AVLGetRefCon() to get that refCon if you want it inside a walkProc.
    ( Most walkProcs will not care about the values for node type, level, or balance. )
*/
/*
 *  AVLWalk()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
AVLWalk(
  AVLTreePtr   tree,
  AVLWalkUPP   walkProc,
  AVLOrder     order,
  void *       walkRefCon)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*  Return  the number of items in the given tree.*/
/*
 *  AVLCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
AVLCount(
  AVLTreePtr   tree,
  UInt32 *     count)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Return the one-based index-th item from the tree by putting it's data at dataPtr
    if dataPtr is non-nil, and it's size into *itemSize if itemSize is non-nil.
    If index is out of range, return errItemNotFoundInTree.  ( Internally, this does
    an AVLWalk(), so the tree can not be modified while this call is in progress ).
*/
/*
 *  AVLGetIndItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
AVLGetIndItem(
  AVLTreePtr   tree,
  UInt32       index,
  void *       dataPtr,
  UInt32 *     itemSize)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Insert the given item into the tree.  This will call the tree's sizeItemProc
    to determine how big the item at data is, and then will make a copy of the
    item and insert it into the tree in the appropriate place.  If an item already
    exists in the tree with the same key ( so that the compareItemsUPP returns 0
    when asked to compare this item to an existing one ), then it will return
    errItemNotFoundInTree.
*/
/*
 *  AVLInsert()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
AVLInsert(
  AVLTreePtr    tree,
  const void *  data)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Remove any item from the tree with the given key.  If dataPtr != nil, then
    copy the item's data to dataPtr before removing it from the tree.  Before
    removing the item, call the tree's disposeItemProc to let it release anything
    used by the data in the tree.  It is not necessary to fill in a complete
    record for key, only that the compareItemsProc return 0 when asked to compare
    the data at key with the node in the tree to be deleted.  If the item cannot
    be found in the tree, this will return errItemNotFoundInTree.
*/
/*
 *  AVLRemove()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
AVLRemove(
  AVLTreePtr    tree,
  const void *  key,
  void *        dataPtr,
  UInt32 *      itemSize)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Find the item in the tree with the given key, and return it's data in
    dataPtr ( if dataPtr != nil ), and it's size in *itemSize ( if itemSize
    != nil ).  It is not necessary to fill in a complete record for key,
    only that the compareItemsProc return 0 when asked to compare the data
    at key with the node in the tree to be deleted.  If the item cannot
    be found in the tree, this will return errItemNotFoundInTree.
*/
/*
 *  AVLFind()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
AVLFind(
  AVLTreePtr    tree,
  const void *  key,
  void *        dataPtr,
  UInt32 *      itemSize)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Get the refCon for the given tree ( set in AVLInit ) and return it.
    If the given tree is invalid, then return nil.
*/
/*
 *  AVLGetRefcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
AVLGetRefcon(
  AVLTreePtr   tree,
  void **      refCon)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __AVLTREE__ */

