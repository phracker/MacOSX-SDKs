/*
	NSController.h
	Application Kit
	Copyright (c) 2002-2014, Apple Inc.
	All rights reserved.
 */

#import <AppKit/NSKeyValueBinding.h>
#import <CoreFoundation/CoreFoundation.h>


@class NSMutableArray, NSMutableDictionary, NSMutableSet;

@interface NSController : NSObject <NSCoding> {
@private
#if !__LP64__
    void *_reserved;
    void *_reserved2;
#endif
    int _specialPurposeType;
    id _bindingAdaptor;
    NSMutableArray *_editors;
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
#if !__LP64__
    NSMutableDictionary *_reservedOther;
#endif
@protected    // all instance variables are private
    id _modelObservingTracker;
    id _expectedObservingInfo;
    id _singleValueAccessor;
}

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (void)objectDidBeginEditing:(id)editor;
- (void)objectDidEndEditing:(id)editor;
- (void)discardEditing;
- (BOOL)commitEditing;
- (void)commitEditingWithDelegate:(id)delegate didCommitSelector:(SEL)didCommitSelector contextInfo:(void *)contextInfo;
@property (getter=isEditing, readonly) BOOL editing;

@end

