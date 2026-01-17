/*
	NSViewController.h
	Application Kit
	Copyright (c) 2006-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSNibDeclarations.h>
#import <AppKit/NSResponder.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class NSArray, NSBundle, NSPointerArray, NSView;

@interface NSViewController : NSResponder {
    @private
    NSString *_nibName;
    NSBundle *_nibBundle;
    id _representedObject;
    NSString *_title;
    IBOutlet NSView *view;
    NSArray *_topLevelObjects;
    NSPointerArray *_editors;
    id _autounbinder;
    id _reserved[3];
}

/* The designated initializer. The specified nib should typically have the class of the file's owner set to NSViewController, or a subclass of yours, with the "view" outlet connected to a view. If you pass in a nil nib name then -nibName will return nil and -loadView will throw an exception; you most likely must also invoke -setView: before -view is invoked, or override -loadView. If you pass in a nil bundle then -nibBundle will return nil and -loadView will interpret it using the same rules as -[NSNib initWithNibNamed:bundle:].
*/
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil;

/* The object whose value is being presented in the view. The default implementation of -setRepresentedObject: doesn't copy the passed-in object, it retains it. (In another words, "representedObject" is a to-one relationship, not an attribute.) This class is key-value coding and key-value observing compliant for "representedObject" so when you use it as the file's owner of a view's nib you can bind controls to the file's owner using key paths that start with "representedObject."
*/
- (void)setRepresentedObject:(id)representedObject;
- (id)representedObject;

/* The localized title of the view. This class doesn't actually do anything with the value of this property other than hold onto it, and be KVC and KVO compliant for "title." The default implementation of -setTitle: copies the passed-in object ("title" is an attribute). This property is here because so many anticipated uses of this class will involve letting the user choose among multiple named views using a pulldown menu or something like that.
*/
- (void)setTitle:(NSString *)title;
- (NSString *)title;

/* Return the view. The default implementation of this method first invokes [self loadView] if the view hasn't been set yet.
*/
- (NSView *)view;

/* Instantiate the view and then set it. The default implementation of this method invokes [self nibName] and [self nibBundle] and then uses the NSNib class to load the nib with this object as the file's owner. If the "view" outlet of the file's owner in the nib is properly connected, the regular nib loading machinery will send this object a -setView: message.
*/
- (void)loadView;

/* Return the name of the nib to be loaded to instantiate the view, and the bundle from which to load it. The default implementations of these merely return whatever value was passed to the initializer.
*/
- (NSString *)nibName;
- (NSBundle *)nibBundle;

/* Set the view. You can invoke this method immediately after creating the object to specify a view that's created in a different manner than what -view's default implementation would do.
*/
- (void)setView:(NSView *)view;

/* Conformance to KVB's NSEditor informal protocol. The default implementations of these methods pass on the message to each registered editor, which are typically controls in the nib that are bound to the nib file's owner. You can override these methods to customize what is done when your view's presentation to the user is about to end because, for example, the user has selected another of a set of views or hit a panel's OK button (committing time) or because the user has hit a panel's Cancel button (discarding time). This class also conforms to KVB's NSEditorRegistration informal protocol, but you're not encouraged to override those methods.
*/
- (void)commitEditingWithDelegate:(id)delegate didCommitSelector:(SEL)didCommitSelector contextInfo:(void *)contextInfo;
- (BOOL)commitEditing;
- (void)discardEditing;

@end

#endif
