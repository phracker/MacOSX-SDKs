/*
	NSKeyValueBinding.h
	Application Kit
	Copyright (c) 2002-2003, Apple Computer, Inc.
	All rights reserved.
 */

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

@class NSArray, NSDictionary, NSString;

APPKIT_EXTERN id NSMultipleValuesMarker;
APPKIT_EXTERN id NSNoSelectionMarker;
APPKIT_EXTERN id NSNotApplicableMarker;

APPKIT_EXTERN BOOL NSIsControllerMarker(id object);

@interface NSObject (NSKeyValueBindingCreation)

+ (void)exposeBinding:(NSString *)binding;    // bindings specified here will be exposed automatically in -exposedBindings (unless implementations explicitly filter them out, for example in subclasses)
- (NSArray *)exposedBindings;   // for a new key exposed through this method, the default implementation simply falls back to key-value coding
- (Class)valueClassForBinding:(NSString *)binding;    // optional - mostly for matching transformers

// bindings are considered to be a property of the object which is bound (the object the following two methods are sent to) and all information related to bindings should be retained by the object; all standard bindings on AppKit objects (views, cells, table columns, controllers) unbind their bindings automatically when they are released, but if you create key-value bindings for other kind of objects, you need to make sure that you remove those bindings when you release them (observed objects don't retain their observers, so controllers/model objects might continue referencing and messaging the objects that was bound to them)
- (void)bind:(NSString *)binding toObject:(id)observable withKeyPath:(NSString *)keyPath options:(NSDictionary *)options;    // placeholders and value transformers are specified in options dictionary
- (void)unbind:(NSString *)binding;

@end

@interface NSObject (NSPlaceholders)

+ (void)setDefaultPlaceholder:(id)placeholder forMarker:(id)marker withBinding:(NSString *)binding;    // marker can be nil or one of NSMultipleValuesMarker, NSNoSelectionMarker, NSNotApplicableMarker
+ (id)defaultPlaceholderForMarker:(id)marker withBinding:(NSString *)binding;    // marker can be nil or one of NSMultipleValuesMarker, NSNoSelectionMarker, NSNotApplicableMarker

@end

// methods implemented by controllers (and potentially documents)
@interface NSObject (NSEditorRegistration)

- (void)objectDidBeginEditing:(id)editor;
- (void)objectDidEndEditing:(id)editor;

@end

// methods implemented by controllers and user interface elements
@interface NSObject (NSEditor)

- (void)discardEditing;    // forces changing to end (reverts back to the original value)
- (BOOL)commitEditing;    // returns whether end editing was successful (while trying to apply changes to a model object, there might be validation problems or so that prevent the operation from being successful

@end

#endif
