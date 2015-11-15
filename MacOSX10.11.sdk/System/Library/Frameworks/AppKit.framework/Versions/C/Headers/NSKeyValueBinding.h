/*
	NSKeyValueBinding.h
	Application Kit
	Copyright (c) 2002-2015, Apple Inc.
	All rights reserved.
 */

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>


NS_ASSUME_NONNULL_BEGIN

@class NSString, NSError, NSAttributeDescription;

APPKIT_EXTERN id NSMultipleValuesMarker;
APPKIT_EXTERN id NSNoSelectionMarker;
APPKIT_EXTERN id NSNotApplicableMarker;

APPKIT_EXTERN BOOL NSIsControllerMarker(__nullable id object);

// keys for the returned dictionary of -infoForBinding:
APPKIT_EXTERN NSString * NSObservedObjectKey;
APPKIT_EXTERN NSString * NSObservedKeyPathKey;
APPKIT_EXTERN NSString * NSOptionsKey;

@interface NSObject (NSKeyValueBindingCreation)

+ (void)exposeBinding:(NSString *)binding;    // bindings specified here will be exposed automatically in -exposedBindings (unless implementations explicitly filter them out, for example in subclasses)
@property (readonly, copy) NSArray<NSString *> *exposedBindings;   // for a new key exposed through this method, the default implementation simply falls back to key-value coding
- (nullable Class)valueClassForBinding:(NSString *)binding;    // optional - mostly for matching transformers

/* Bindings are considered to be a property of the object which is bound (the object the following two methods are sent to) and all information related to bindings should be retained by the object; all standard bindings on AppKit objects (views, cells, table columns, controllers) unbind their bindings automatically when they are released, but if you create key-value bindings for other kind of objects, you need to make sure that you remove those bindings when you release them (observed objects don't retain their observers, so controllers/model objects might continue referencing and messaging the objects that was bound to them).
*/
- (void)bind:(NSString *)binding toObject:(id)observable withKeyPath:(NSString *)keyPath options:(nullable NSDictionary<NSString *, id> *)options;    // placeholders and value transformers are specified in options dictionary
- (void)unbind:(NSString *)binding;

/* Returns a dictionary with information about a binding or nil if the binding is not bound (this is mostly for use by subclasses which want to analyze the existing bindings of an object) - the dictionary contains three key/value pairs: NSObservedObjectKey: object bound, NSObservedKeyPathKey: key path bound, NSOptionsKey: dictionary with the options and their values for the bindings.
*/
- (nullable NSDictionary<NSString *, id> *)infoForBinding:(NSString *)binding;

/* Returns an array of NSAttributeDescriptions that describe the options for aBinding. The descriptions are used by Interface Builder to build the options editor UI of the bindings inspector. Each binding may have multiple options. The options and attribute descriptions have 3 properties in common: 

- The option "name" is derived from the attribute description name. 

- The type of UI built for the option is based on the attribute type. 

- The default value shown in the options editor comes from the attribute description's defaultValue.*/


- (NSArray<NSAttributeDescription *> *)optionDescriptionsForBinding:(NSString *)aBinding NS_AVAILABLE_MAC(10_5);


@end

@interface NSObject (NSPlaceholders)

+ (void)setDefaultPlaceholder:(nullable id)placeholder forMarker:(nullable id)marker withBinding:(NSString *)binding;    // marker can be nil or one of NSMultipleValuesMarker, NSNoSelectionMarker, NSNotApplicableMarker
+ (nullable id)defaultPlaceholderForMarker:(nullable id)marker withBinding:(NSString *)binding;    // marker can be nil or one of NSMultipleValuesMarker, NSNoSelectionMarker, NSNotApplicableMarker

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


/* Given that the receiver has been registered with -objectDidBeginEditing: as the editor of some object, and not yet deregistered by a subsequent invocation of -objectDidEndEditing:, attempt to commit the result of the editing. When committing has either succeeded or failed, send the selected message to the specified object with the context info as the last parameter. The method selected by didCommitSelector must have the same signature as:

    - (void)editor:(id)editor didCommit:(BOOL)didCommit contextInfo:(void *)contextInfo;

If an error occurs while attempting to commit, because key-value coding validation fails for example, an implementation of this method should typically send the NSView in which editing is being done a -presentError:modalForWindow:delegate:didRecoverSelector:contextInfo: message, specifying the view's containing window.
*/
- (void)commitEditingWithDelegate:(nullable id)delegate didCommitSelector:(nullable SEL)didCommitSelector contextInfo:(nullable void *)contextInfo;


/* During autosaving, commit editing may fail, due to a pending edit.  Rather than interrupt the user with an unexpected alert, this method provides the caller with the option to either present the error or fail silently, leaving the pending edit in place and the user's editing uninterrupted.  This method attempts to commit editing, but if there is a failure the error is returned to the caller to be presented or ignored as appropriate.  If an error occurs while attempting to commit, an implementation of this method should return NO as well as the generated error by reference.  Returns YES if commit is successful.
 
 If you have enabled autosaving in your application, and your application has custom objects that implement or override the NSEditor protocol, you must also implement this method in those NSEditors.
 */
- (BOOL)commitEditingAndReturnError:(NSError **)error   NS_AVAILABLE_MAC(10_7);

@end

// constants for binding names
APPKIT_EXTERN NSString * NSAlignmentBinding;
APPKIT_EXTERN NSString * NSAlternateImageBinding;
APPKIT_EXTERN NSString * NSAlternateTitleBinding;
APPKIT_EXTERN NSString * NSAnimateBinding;
APPKIT_EXTERN NSString * NSAnimationDelayBinding;
APPKIT_EXTERN NSString * NSArgumentBinding;
APPKIT_EXTERN NSString * NSAttributedStringBinding;
APPKIT_EXTERN NSString * NSContentArrayBinding;
APPKIT_EXTERN NSString * NSContentArrayForMultipleSelectionBinding;
APPKIT_EXTERN NSString * NSContentBinding;
APPKIT_EXTERN NSString * NSContentDictionaryBinding		NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * NSContentHeightBinding;
APPKIT_EXTERN NSString * NSContentObjectBinding;
APPKIT_EXTERN NSString * NSContentObjectsBinding;
APPKIT_EXTERN NSString * NSContentSetBinding;
APPKIT_EXTERN NSString * NSContentValuesBinding;
APPKIT_EXTERN NSString * NSContentWidthBinding;
APPKIT_EXTERN NSString * NSCriticalValueBinding;
APPKIT_EXTERN NSString * NSDataBinding;
APPKIT_EXTERN NSString * NSDisplayPatternTitleBinding;
APPKIT_EXTERN NSString * NSDisplayPatternValueBinding;
APPKIT_EXTERN NSString * NSDocumentEditedBinding;
APPKIT_EXTERN NSString * NSDoubleClickArgumentBinding;
APPKIT_EXTERN NSString * NSDoubleClickTargetBinding;
APPKIT_EXTERN NSString * NSEditableBinding;
APPKIT_EXTERN NSString * NSEnabledBinding;
APPKIT_EXTERN NSString * NSExcludedKeysBinding		NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * NSFilterPredicateBinding;
APPKIT_EXTERN NSString * NSFontBinding;
APPKIT_EXTERN NSString * NSFontBoldBinding;
APPKIT_EXTERN NSString * NSFontFamilyNameBinding;
APPKIT_EXTERN NSString * NSFontItalicBinding;
APPKIT_EXTERN NSString * NSFontNameBinding;
APPKIT_EXTERN NSString * NSFontSizeBinding;
APPKIT_EXTERN NSString * NSHeaderTitleBinding;
APPKIT_EXTERN NSString * NSHiddenBinding;
APPKIT_EXTERN NSString * NSImageBinding;
APPKIT_EXTERN NSString * NSIncludedKeysBinding		NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * NSInitialKeyBinding		NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * NSInitialValueBinding		NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * NSIsIndeterminateBinding;
APPKIT_EXTERN NSString * NSLabelBinding;
APPKIT_EXTERN NSString * NSLocalizedKeyDictionaryBinding		NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * NSManagedObjectContextBinding;
APPKIT_EXTERN NSString * NSMaximumRecentsBinding;
APPKIT_EXTERN NSString * NSMaxValueBinding;
APPKIT_EXTERN NSString * NSMaxWidthBinding;
APPKIT_EXTERN NSString * NSMinValueBinding;
APPKIT_EXTERN NSString * NSMinWidthBinding;
APPKIT_EXTERN NSString * NSMixedStateImageBinding;
APPKIT_EXTERN NSString * NSOffStateImageBinding;
APPKIT_EXTERN NSString * NSOnStateImageBinding;
APPKIT_EXTERN NSString * NSPositioningRectBinding            NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * NSPredicateBinding;
APPKIT_EXTERN NSString * NSRecentSearchesBinding;
APPKIT_EXTERN NSString * NSRepresentedFilenameBinding;
APPKIT_EXTERN NSString * NSRowHeightBinding;
APPKIT_EXTERN NSString * NSSelectedIdentifierBinding;
APPKIT_EXTERN NSString * NSSelectedIndexBinding;
APPKIT_EXTERN NSString * NSSelectedLabelBinding;
APPKIT_EXTERN NSString * NSSelectedObjectBinding;
APPKIT_EXTERN NSString * NSSelectedObjectsBinding;
APPKIT_EXTERN NSString * NSSelectedTagBinding;
APPKIT_EXTERN NSString * NSSelectedValueBinding;
APPKIT_EXTERN NSString * NSSelectedValuesBinding;
APPKIT_EXTERN NSString * NSSelectionIndexesBinding;
APPKIT_EXTERN NSString * NSSelectionIndexPathsBinding;
APPKIT_EXTERN NSString * NSSortDescriptorsBinding;
APPKIT_EXTERN NSString * NSTargetBinding;
APPKIT_EXTERN NSString * NSTextColorBinding;
APPKIT_EXTERN NSString * NSTitleBinding;
APPKIT_EXTERN NSString * NSToolTipBinding;
APPKIT_EXTERN NSString * NSTransparentBinding		NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * NSValueBinding;
APPKIT_EXTERN NSString * NSValuePathBinding;
APPKIT_EXTERN NSString * NSValueURLBinding;
APPKIT_EXTERN NSString * NSVisibleBinding;
APPKIT_EXTERN NSString * NSWarningValueBinding;
APPKIT_EXTERN NSString * NSWidthBinding;

// constants for binding options
APPKIT_EXTERN NSString * NSAllowsEditingMultipleValuesSelectionBindingOption;
APPKIT_EXTERN NSString * NSAllowsNullArgumentBindingOption;
APPKIT_EXTERN NSString * NSAlwaysPresentsApplicationModalAlertsBindingOption;
APPKIT_EXTERN NSString * NSConditionallySetsEditableBindingOption;
APPKIT_EXTERN NSString * NSConditionallySetsEnabledBindingOption;
APPKIT_EXTERN NSString * NSConditionallySetsHiddenBindingOption;
APPKIT_EXTERN NSString * NSContinuouslyUpdatesValueBindingOption;
APPKIT_EXTERN NSString * NSCreatesSortDescriptorBindingOption;
APPKIT_EXTERN NSString * NSDeletesObjectsOnRemoveBindingsOption;
APPKIT_EXTERN NSString * NSDisplayNameBindingOption;
APPKIT_EXTERN NSString * NSDisplayPatternBindingOption;
APPKIT_EXTERN NSString * NSContentPlacementTagBindingOption		NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString * NSHandlesContentAsCompoundValueBindingOption;
APPKIT_EXTERN NSString * NSInsertsNullPlaceholderBindingOption;
APPKIT_EXTERN NSString * NSInvokesSeparatelyWithArrayObjectsBindingOption;
APPKIT_EXTERN NSString * NSMultipleValuesPlaceholderBindingOption;
APPKIT_EXTERN NSString * NSNoSelectionPlaceholderBindingOption;
APPKIT_EXTERN NSString * NSNotApplicablePlaceholderBindingOption;
APPKIT_EXTERN NSString * NSNullPlaceholderBindingOption;
APPKIT_EXTERN NSString * NSRaisesForNotApplicableKeysBindingOption;
APPKIT_EXTERN NSString * NSPredicateFormatBindingOption;
APPKIT_EXTERN NSString * NSSelectorNameBindingOption;
APPKIT_EXTERN NSString * NSSelectsAllWhenSettingContentBindingOption;
APPKIT_EXTERN NSString * NSValidatesImmediatelyBindingOption;
APPKIT_EXTERN NSString * NSValueTransformerNameBindingOption;
APPKIT_EXTERN NSString * NSValueTransformerBindingOption;

NS_ASSUME_NONNULL_END

