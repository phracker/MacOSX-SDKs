/* CoreAnimation - CATransaction.h

   Copyright (c) 2006-2007 Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <Foundation/NSObject.h>

/* Transactions are CoreAnimation's mechanism for batching multiple layer-
 * tree operations into atomic updates to the render tree. Every
 * modification to the layer tree requires a transaction to be part of.
 *
 * CoreAnimation supports two kinds of transactions, "explicit" transactions
 * and "implicit" transactions.
 *
 * Explicit transactions are where the programmer calls `[CATransaction
 * begin]' before modifying the layer tree, and `[CATransaction commit]'
 * afterwards.
 *
 * Implicit transactions are created automatically by CoreAnimation when the
 * layer tree is modified by a thread without an active transaction.
 * They are committed automatically when the thread's run-loop next
 * iterates. In some circumstances (i.e. no run-loop, or the run-loop
 * is blocked) it may be necessary to use explicit transactions to get
 * timely render tree updates. */

@interface CATransaction : NSObject

/* Begin a new transaction for the current thread; nests. */

+ (void)begin;

/* Commit all changes made during the current transaction. Raises an
 * exception if no current transaction exists. */

+ (void)commit;

/* Commits any extant implicit transaction. Will delay the actual commit
 * until any nested explicit transactions have completed. */

+ (void)flush;

/* Associate arbitratry keyed-data with the current transaction.
 *
 * Nested transactions have nested data scope, i.e. reading a key
 * searches for the innermost scope that has set it, setting a key
 * always sets it in the innermost scope.
 *
 * Currently supported transaction properties include:
 *
 * `animationDuration': default duration in seconds for animations
 * added to layers.
 *
 * `disableActions': when true, implicit actions for property changes
 * are suppressed. */

+ (id)valueForKey:(NSString *)key;
+ (void)setValue:(id)anObject forKey:(NSString *)key;

@end

/** Transaction property ids. **/

CA_EXTERN NSString * const kCATransactionAnimationDuration AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CA_EXTERN NSString * const kCATransactionDisableActions AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
