/*
	NSKeyValueBinding.h
	Application Kit
	Copyright (c) 2002-2005, Apple Computer, Inc.
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

// keys for the returned dictionary of -infoForBinding:
APPKIT_EXTERN NSString *NSObservedObjectKey		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSObservedKeyPathKey		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSOptionsKey		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

@interface NSObject (NSKeyValueBindingCreation)

+ (void)exposeBinding:(NSString *)binding;    // bindings specified here will be exposed automatically in -exposedBindings (unless implementations explicitly filter them out, for example in subclasses)
- (NSArray *)exposedBindings;   // for a new key exposed through this method, the default implementation simply falls back to key-value coding
- (Class)valueClassForBinding:(NSString *)binding;    // optional - mostly for matching transformers

/* Bindings are considered to be a property of the object which is bound (the object the following two methods are sent to) and all information related to bindings should be retained by the object; all standard bindings on AppKit objects (views, cells, table columns, controllers) unbind their bindings automatically when they are released, but if you create key-value bindings for other kind of objects, you need to make sure that you remove those bindings when you release them (observed objects don't retain their observers, so controllers/model objects might continue referencing and messaging the objects that was bound to them).
*/
- (void)bind:(NSString *)binding toObject:(id)observable withKeyPath:(NSString *)keyPath options:(NSDictionary *)options;    // placeholders and value transformers are specified in options dictionary
- (void)unbind:(NSString *)binding;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Returns a dictionary with information about a binding or nil if the binding is not bound (this is mostly for use by subclasses which want to analyze the existing bindings of an object) - the dictionary contains three key/value pairs: NSObservedObjectKey: object bound, NSObservedKeyPathKey: key path bound, NSOptionsKey: dictionary with the options and their values for the bindings.
*/
- (NSDictionary *)infoForBinding:(NSString *)binding;
#endif

@end

@interface NSObject (NSPlaceholders)

+ (void)setDefaultPlaceholder:(id)placeholder forMarker:(id)marker withBinding:(NSString *)binding;    // marker can be nil or one of NSMultipleValuesMarker, NSNoSelectionMarker, NSNotApplicableMarker
+ (id)defaultPlaceholderForMarker:(id)marker withBinding:(NSString *)binding;    // marker can be nil or one of NSMultipleValuesMarker, NSNoSelectionMarker, NSNotApplicableMarker

@end

// methods implemented by controllers, CoreData's managed object contexts (and potentially documents)
@interface NSObject (NSEditorRegistration)

- (void)objectDidBeginEditing:(id)editor;
- (void)objectDidEndEditing:(id)editor;

@end

// methods implemented by controllers, CoreData's managed object contexts, and user interface elements
@interface NSObject (NSEditor)

- (void)discardEditing;    // forces changing to end (reverts back to the original value)
- (BOOL)commitEditing;    // returns whether end editing was successful (while trying to apply changes to a model object, there might be validation problems or so that prevent the operation from being successful

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Given that the receiver has been registered with -objectDidBeginEditing: as the editor of some object, and not yet deregistered by a subsequent invocation of -objectDidEndEditing:, attempt to commit the result of the editing. When committing has either succeeded or failed, send the selected message to the specified object with the context info as the last parameter. The method selected by didCommitSelector must have the same signature as:

    - (void)editor:(id)editor didCommit:(BOOL)didCommit contextInfo:(void *)contextInfo;

If an error occurs while attempting to commit, because key-value coding validation fails for example, an implementation of this method should typically send the NSView in which editing is being done a -presentError:modalForWindow:delegate:didRecoverSelector:contextInfo: message, specifying the view's containing window.
*/
- (void)commitEditingWithDelegate:(id)delegate didCommitSelector:(SEL)didCommitSelector contextInfo:(void *)contextInfo;

#endif

@end

// constants for binding names
APPKIT_EXTERN NSString *NSAlignmentBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSAlternateImageBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSAlternateTitleBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSAnimateBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSAnimationDelayBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSArgumentBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSAttributedStringBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSContentArrayBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSContentArrayForMultipleSelectionBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSContentBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSContentHeightBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSContentObjectBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSContentObjectsBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSContentSetBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSContentValuesBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSContentWidthBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSCriticalValueBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSDataBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSDisplayPatternTitleBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSDisplayPatternValueBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSDocumentEditedBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSDoubleClickArgumentBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSDoubleClickTargetBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSEditableBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSEnabledBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSFilterPredicateBinding        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSFontBinding                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSFontBoldBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSFontFamilyNameBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSFontItalicBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSFontNameBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSFontSizeBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSHeaderTitleBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSHiddenBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSImageBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSIsIndeterminateBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSLabelBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSManagedObjectContextBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSMaximumRecentsBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSMaxValueBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSMaxWidthBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSMinValueBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSMinWidthBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSMixedStateImageBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSOffStateImageBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSOnStateImageBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSPredicateBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSRecentSearchesBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSRepresentedFilenameBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSRowHeightBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectedIdentifierBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectedIndexBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectedLabelBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectedObjectBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectedObjectsBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectedTagBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectedValueBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectedValuesBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectionIndexesBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectionIndexPathsBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSortDescriptorsBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSTargetBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSTextColorBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSTitleBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSToolTipBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSValueBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSValuePathBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSValueURLBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSVisibleBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSWarningValueBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSWidthBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// constants for binding options
APPKIT_EXTERN NSString *NSAllowsEditingMultipleValuesSelectionBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSAllowsNullArgumentBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSAlwaysPresentsApplicationModalAlertsBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSConditionallySetsEditableBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSConditionallySetsEnabledBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSConditionallySetsHiddenBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSContinuouslyUpdatesValueBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSCreatesSortDescriptorBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSDeletesObjectsOnRemoveBindingsOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSDisplayNameBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSDisplayPatternBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSHandlesContentAsCompoundValueBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSInsertsNullPlaceholderBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSInvokesSeparatelyWithArrayObjectsBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSMultipleValuesPlaceholderBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSNoSelectionPlaceholderBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSNotApplicablePlaceholderBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSNullPlaceholderBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSRaisesForNotApplicableKeysBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSPredicateFormatBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectorNameBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSSelectsAllWhenSettingContentBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSValidatesImmediatelyBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSValueTransformerNameBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSValueTransformerBindingOption		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#endif
