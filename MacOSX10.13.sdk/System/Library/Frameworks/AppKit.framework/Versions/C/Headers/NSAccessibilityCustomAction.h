/*
     NSAccessibilityCustomAction.h
     Application Kit
     Copyright (c) 2017 Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_MAC(10_13) @interface NSAccessibilityCustomAction : NSObject
{
@private
    NSString *_name;
    __weak id<NSObject> _target;
    BOOL (^_handler)();
    SEL _selector;
}

/* Creates a custom action that performs the action via a block handler.
    The block should return whether the action was executed successfully or not.
    The return status will help accessibility clients know what to communicate back to the user.
*/
- (instancetype)initWithName:(NSString *)name handler:(BOOL(^ _Nullable)())handler;

/* Creates a custom action that performs the action via selector/target.
    The selector should have a signature that returns a BOOL for the success status of the execution.
*/
- (instancetype)initWithName:(NSString *)name target:(id<NSObject>)target selector:(SEL)selector;

// A localized name that describes the action.  This is a string that may be displayed to the user.
@property (copy) NSString *name;

// The block that handles the execution of the action
@property (nullable, copy) BOOL (^handler)();

// The object that will perform the action via selector
@property (nullable, weak) id<NSObject> target;

/*
 The method that will be called on the target to perform the action.
 It must conform to one of the following signatures:
 - (BOOL)myPerformActionMethod;
 - (BOOL)myPerformActionMethod:(NSAccessibilityCustomAction *)action;
 */
@property (nullable) SEL selector;

@end

NS_ASSUME_NONNULL_END
