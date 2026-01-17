/*
	NSController.h
	Application Kit
	Copyright (c) 2002-2018, Apple Inc.
	All rights reserved.
 */

#import <AppKit/NSKeyValueBinding.h>
#import <CoreFoundation/CoreFoundation.h>


NS_ASSUME_NONNULL_BEGIN

@class NSMutableArray, NSMutableDictionary, NSMutableSet;

@interface NSController : NSObject <NSCoding, NSEditor, NSEditorRegistration> {
@private
#if !__LP64__
    void *_reserved APPKIT_IVAR;
    void *_reserved2 APPKIT_IVAR;
#endif
    int _specialPurposeType APPKIT_IVAR;
    id _bindingAdaptor APPKIT_IVAR;
    NSMutableArray *_editors APPKIT_IVAR;
    NSMutableArray *_declaredKeys APPKIT_IVAR;
    NSMutableDictionary *_dependentKeyToModelKeyTable APPKIT_IVAR;
    NSMutableDictionary *_modelKeyToDependentKeyTable APPKIT_IVAR;
    NSMutableArray *_modelKeysToRefreshEachTime APPKIT_IVAR;
    struct __bindingsControllerFlags {
        unsigned int _alwaysPresentsApplicationModalAlerts:1;
        unsigned int _refreshesAllModelKeys:1;
        unsigned int _multipleObservedModelObjects:1;
        unsigned int _isEditing:1;
        unsigned int _reservedController:28;
    } _bindingsControllerFlags APPKIT_IVAR;
#if !__LP64__
    NSMutableDictionary *_reservedOther APPKIT_IVAR;
#endif
@protected    // all instance variables are private
    id _modelObservingTracker APPKIT_IVAR;
    id _expectedObservingInfo APPKIT_IVAR;
    id _singleValueAccessor APPKIT_IVAR;
}

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (void)objectDidBeginEditing:(id<NSEditor>)editor;
- (void)objectDidEndEditing:(id<NSEditor>)editor;
- (void)discardEditing;
- (BOOL)commitEditing;
- (void)commitEditingWithDelegate:(nullable id)delegate didCommitSelector:(nullable SEL)didCommitSelector contextInfo:(nullable void *)contextInfo;
@property (getter=isEditing, readonly) BOOL editing;

@end

NS_ASSUME_NONNULL_END

