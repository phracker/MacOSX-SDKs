/*
        NSStoryboardSegue.h
        Application Kit
        Copyright (c) 2013-2015, Apple Inc.
        All rights reserved.
*/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_MAC(10_10)
@interface NSStoryboardSegue : NSObject {
@private
    void (^_performHandler)(void);
    NSString *_identifier;
    id _sourceController;
    id _destinationController;
    void (^_prepareHandler)(void);
}

// Convenience constructor for returning a segue that performs a handler block in its -perform method.
+ (instancetype)segueWithIdentifier:(NSString *)identifier source:(id)sourceController destination:(id)destinationController performHandler:(void (^)(void))performHandler;

/* This is the designated initializer for NSStoryboardSegue. If a developer implements a NSStoryboardSegue subclass, they can override this method to perform init-time logic. When a segue starts, a new instance of NSStoryboardSegue will be created with this method, and then perform will subsequently be invoked. */
- (instancetype)initWithIdentifier:(NSString *)identifier source:(id)sourceController destination:(id)destinationController NS_DESIGNATED_INITIALIZER;

/* NSStoryboardSegue instances have optional identifiers that can be assigned in Interface Builder. These identifiers can be used in overrides of -[NSViewController prepareForSegue:sender:] to differentiate segues. */
@property (nullable, readonly, copy) NSString *identifier;

/* Subclasses of NSStoryboardSegue can use this property to access the source view or window controller that is being segued away from. */
@property (readonly, strong) id sourceController;

/* Subclasses of NSStoryboardSegue can use this property to access the destination view or window controller that's being segued to. This property is also essential for overrides of -[NSViewController prepareForSegue:sender:], which is passed to the source view controller. This property allows the receiver of -[NSViewController prepareForSegue:sender:] to access and pass configuration data to the destination controller. */
@property (readonly, strong) id destinationController;

/* This method is implemented by NSStoryboardSegue subclasses to present a custom transition between two controllers. */
- (void)perform;

@end

@protocol NSSeguePerforming <NSObject>

@optional

/* Subclasses should override this to do any necessary work preparing for the destination ViewController or WindowController.
 */
- (void)prepareForSegue:(NSStoryboardSegue *)segue sender:(nullable id)sender NS_AVAILABLE_MAC(10_10);

/* Performs the identified Segue created from this WindowController. Throws exception if identifier is nil or not associated with the receiver.
 */
- (void)performSegueWithIdentifier:(NSString *)identifier sender:(nullable id)sender NS_AVAILABLE_MAC(10_10);

/* Invoked immediately prior to initiating a segue. Return NO to prevent the segue from firing. The default implementations in NSViewController and NSWindowController return YES. This method is invoked when -performSegueWithIdentifier:sender: is used.
 */
- (BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(nullable id)sender NS_AVAILABLE_MAC(10_10);

@end

NS_ASSUME_NONNULL_END
