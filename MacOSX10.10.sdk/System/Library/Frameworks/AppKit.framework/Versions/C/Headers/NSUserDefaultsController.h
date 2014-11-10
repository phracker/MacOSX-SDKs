/*
	NSUserDefaultsController.h
	Application Kit
	Copyright (c) 2002-2014, Apple Inc.
	All rights reserved.
 */

#import <AppKit/NSController.h>


@class NSDictionary, NSUserDefaults;

@interface NSUserDefaultsController : NSController {
@private
#if !__LP64__    
    void *_reserved3;
    void *_reserved4;
#endif
    NSUserDefaults *_defaults;
    NSMutableDictionary *_valueBuffer;
    NSDictionary *_initialValues;
    struct __userDefaultsControllerFlags {
        unsigned int _sharedInstance:1;
        unsigned int _appliesImmediately:1;
        unsigned int _reservedUserDefaultsController:30;
    } _userDefaultsControllerFlags;
}

+ (NSUserDefaultsController *)sharedUserDefaultsController;

- (instancetype)initWithDefaults:(NSUserDefaults *)defaults initialValues:(NSDictionary *)initialValues NS_DESIGNATED_INITIALIZER;    // if defaults is nil, the controller uses [NSUserDefaults standardUserDefaults]; if initialValues is nil, revertToInitialValues: has no effect
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (readonly, strong) NSUserDefaults *defaults;
@property (copy) NSDictionary *initialValues;

@property BOOL appliesImmediately;   // default: YES

@property (readonly) BOOL hasUnappliedChanges;

@property (readonly, strong) id values;    // accessor object for default values (independent of whether they are derived directly from the NSUserDefaults or from the initial values)

- (void)revert:(id)sender;
- (void)save:(id)sender;    // no effect if applies immediately
- (void)revertToInitialValues:(id)sender;    // no effect if no initial values are specified

@end

