/*
	NSUserDefaultsController.h
	Application Kit
	Copyright (c) 2002-2005, Apple Computer, Inc.
	All rights reserved.
 */

#import <AppKit/NSController.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@class NSDictionary, NSUserDefaults;

@interface NSUserDefaultsController : NSController {
@private
	void *_reserved3;
	void *_reserved4;
    NSUserDefaults *_defaults;
    NSMutableDictionary *_valueBuffer;
    NSDictionary *_initialValues;
    struct __userDefaultsControllerFlags {
        unsigned int _sharedInstance:1;
        unsigned int _appliesImmediately:1;
        unsigned int _reservedUserDefaultsController:30;
    } _userDefaultsControllerFlags;
}

+ (id)sharedUserDefaultsController;

- (id)initWithDefaults:(NSUserDefaults *)defaults initialValues:(NSDictionary *)initialValues;    // designated initializer; // if defaults is nil, the controller uses [NSUserDefaults standardUserDefaults]; if initialValues is nil, revertToInitialValues: has no effect

- (NSUserDefaults *)defaults;
- (void)setInitialValues:(NSDictionary *)initialValues;
- (NSDictionary *)initialValues;

- (void)setAppliesImmediately:(BOOL)flag;   // default: YES
- (BOOL)appliesImmediately;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)hasUnappliedChanges;
#endif

- (id)values;    // accessor object for default values (independent of whether they are derived directly from the NSUserDefaults or from the initial values)

- (void)revert:(id)sender;
- (void)save:(id)sender;    // no effect if applies immediately
- (void)revertToInitialValues:(id)sender;    // no effect if no initial values are specified

@end

#endif
