//
//  SCNTransaction.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/* Transactions are SceneKit's mechanism for batching multiple scene graph
 * operations into atomic updates. Every
 * modification to the scene graph requires a transaction to be part of. */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNTransaction : NSObject

/* Begin a new transaction for the current thread; nests. */
+ (void)begin;

/* Commit all changes made during the current transaction. */
+ (void)commit;

/* Commits any extant implicit transaction. Will delay the actual commit
 * until any nested explicit transactions have completed. */
+ (void)flush;

/* Methods to lock and unlock the global lock. */
+ (void)lock;
+ (void)unlock;

/* Accessors for the "animationDuration" per-thread transaction
 * property. Defines the default duration of animations. Defaults to 1/4s for explicit transactions, 0s for implicit transactions. */
+ (CFTimeInterval)animationDuration;
+ (void)setAnimationDuration:(CFTimeInterval)duration;

/* Accessors for the "animationTimingFunction" per-thread transaction
 * property. The default value is nil, when set to a non-nil value any
 * animations added to scene graph will have this value set as their
 * "timingFunction" property. */
+ (nullable CAMediaTimingFunction *)animationTimingFunction;
+ (void)setAnimationTimingFunction:(nullable CAMediaTimingFunction *)animationTimingFunction;

/* Accessors for the "disableActions" per-thread transaction property.
 * Defines whether or not the implicit animations are performed. 
 * Defaults to NO, i.e. implicit animations enabled. */
+ (BOOL)disableActions;
+ (void)setDisableActions:(BOOL)flag;

/* Accessors for the "completionBlock" per-thread transaction property.
 * Once set to a non-nil value the block is guaranteed to be called (on
 * the main thread) as soon as all animations subsequently added by
 * this transaction group have completed (or been removed). */
#if __BLOCKS__
+ (nullable void (^)(void))completionBlock;
+ (void)setCompletionBlock:(nullable void (^)(void))block;
#endif

/* Associate arbitrary keyed-data with the current transaction (i.e.
 * with the current thread).
 */
+ (nullable id)valueForKey:(NSString *)key;
+ (void)setValue:(nullable id)value forKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
