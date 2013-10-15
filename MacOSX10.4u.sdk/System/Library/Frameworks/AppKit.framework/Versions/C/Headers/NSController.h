/*
	NSController.h
	Application Kit
	Copyright (c) 2002-2005, Apple Computer, Inc.
	All rights reserved.
 */

#import <AppKit/NSKeyValueBinding.h>
#import <CoreFoundation/CoreFoundation.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@class NSMutableArray, NSMutableDictionary, NSMutableSet;

@interface NSController : NSObject <NSCoding> {
@private
    void *_reserved;
    void *_reserved2;
    int _specialPurposeType;
    id _bindingAdaptor;
    CFMutableArrayRef _editors;
    NSMutableArray *_declaredKeys;
    NSMutableDictionary *_dependentKeyToModelKeyTable;
    NSMutableDictionary *_modelKeyToDependentKeyTable;
    NSMutableArray *_modelKeysToRefreshEachTime;
    struct __bindingsControllerFlags {
        unsigned int _alwaysPresentsApplicationModalAlerts:1;
        unsigned int _refreshesAllModelKeys:1;
        unsigned int _multipleObservedModelObjects:1;
        unsigned int _isEditing:1;
        unsigned int _reservedController:28;
    } _bindingsControllerFlags;
    NSMutableDictionary *_reservedOther;
@protected    // all instance variables are private
    id _modelObservingTracker;
    id _expectedObservingInfo;
    id _singleValueAccessor;
}

- (void)objectDidBeginEditing:(id)editor;
- (void)objectDidEndEditing:(id)editor;
- (void)discardEditing;
- (BOOL)commitEditing;
- (void)commitEditingWithDelegate:(id)delegate didCommitSelector:(SEL)didCommitSelector contextInfo:(void *)contextInfo;
- (BOOL)isEditing;

@end

#endif
