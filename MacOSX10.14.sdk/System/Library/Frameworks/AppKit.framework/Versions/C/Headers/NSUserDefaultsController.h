/*
	NSUserDefaultsController.h
	Application Kit
	Copyright (c) 2002-2018, Apple Inc.
	All rights reserved.
 */

#import <Foundation/NSDictionary.h>
#import <AppKit/NSController.h>


NS_ASSUME_NONNULL_BEGIN

@class NSUserDefaults;

@interface NSUserDefaultsController : NSController {
@private
#if !__LP64__    
    void *_reserved3 APPKIT_IVAR;
    void *_reserved4 APPKIT_IVAR;
#endif
    NSUserDefaults *_defaults APPKIT_IVAR;
    NSMutableDictionary *_valueBuffer APPKIT_IVAR;
    NSDictionary *_initialValues APPKIT_IVAR;
    struct __userDefaultsControllerFlags {
        unsigned int _sharedInstance:1;
        unsigned int _appliesImmediately:1;
        unsigned int _reservedUserDefaultsController:30;
    } _userDefaultsControllerFlags APPKIT_IVAR;
}

@property (class, readonly, strong) NSUserDefaultsController *sharedUserDefaultsController;

- (instancetype)initWithDefaults:(nullable NSUserDefaults *)defaults initialValues:(nullable NSDictionary<NSString *, id> *)initialValues NS_DESIGNATED_INITIALIZER;    // if defaults is nil, the controller uses [NSUserDefaults standardUserDefaults]; if initialValues is nil, revertToInitialValues: has no effect
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (readonly, strong) NSUserDefaults *defaults;
@property (nullable, copy) NSDictionary<NSString *, id> *initialValues;

@property BOOL appliesImmediately;   // default: YES

@property (readonly) BOOL hasUnappliedChanges;

@property (readonly, strong) id values;    // accessor object for default values (independent of whether they are derived directly from the NSUserDefaults or from the initial values)

- (IBAction)revert:(nullable id)sender;
- (IBAction)save:(nullable id)sender;    // no effect if applies immediately
- (IBAction)revertToInitialValues:(nullable id)sender;    // no effect if no initial values are specified

@end

NS_ASSUME_NONNULL_END

