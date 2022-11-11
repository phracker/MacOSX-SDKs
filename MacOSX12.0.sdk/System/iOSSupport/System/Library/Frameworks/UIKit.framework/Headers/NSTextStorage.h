#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSTextStorage.h>)
//
//  NSTextStorage.h
//  UIKit
//
//  Copyright (c) 2011-2018, Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>
#import <UIKit/NSAttributedString.h>
#import <UIKit/UIKitDefines.h>

@class NSArray, NSLayoutManager, NSNotification;

@protocol NSTextStorageDelegate;
@protocol NSTextStorageObserving;

NS_ASSUME_NONNULL_BEGIN

#if UIKIT_HAS_UIFOUNDATION_SYMBOLS

typedef NS_OPTIONS(NSUInteger, NSTextStorageEditActions) {
    NSTextStorageEditedAttributes = (1 << 0),
    NSTextStorageEditedCharacters = (1 << 1)
} API_AVAILABLE(macos(10.11), ios(7.0));


/* Note for subclassing NSTextStorage: NSTextStorage is a semi-abstract subclass of NSMutableAttributedString. It implements change management (beginEditing/endEditing), verification of attributes, delegate handling, and layout management notification. The one aspect it does not implement is the actual attributed string storage --- this is left up to the subclassers, which need to override the two NSMutableAttributedString primitives in addition to two NSAttributedString primitives:
 
 - (NSString *)string;
 - (NSDictionary *)attributesAtIndex:(NSUInteger)location effectiveRange:(NSRangePointer)range;

 - (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)str;
 - (void)setAttributes:(NSDictionary *)attrs range:(NSRange)range;
 
 These primitives should perform the change then call edited:range:changeInLength: to get everything else to happen.
*/

UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(7.0))
@interface NSTextStorage : NSMutableAttributedString <NSSecureCoding>

/**************************** Layout manager ****************************/

// NSLayoutManager objects owned by the receiver.
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<NSLayoutManager *> *layoutManagers;

// Adds aLayoutManager to the receiver.  Sends -[NSLayoutManager setTextStorage:] to aLayoutManager with the receiver.
- (void)addLayoutManager:(NSLayoutManager *)aLayoutManager;

// Removes aLayoutManager from the receiver if already owned by it.  Sends -[NSLayoutManager setTextStorage:] to aLayoutManager with nil.
- (void)removeLayoutManager:(NSLayoutManager *)aLayoutManager;


/**************************** Pending edit info ****************************/
// These methods return information about the editing status. Especially useful when there are outstanding beginEditing calls or during processEditing...

// The NSTextStorageEditActions mask indicating that there are pending changes for attributes, characters, or both.
@property (readonly, NS_NONATOMIC_IOSONLY) NSTextStorageEditActions editedMask;

// The range for pending changes. {NSNotFound, 0} when there is no pending changes.
@property (readonly, NS_NONATOMIC_IOSONLY) NSRange editedRange;

// The length delta for the pending changes.
@property (readonly, NS_NONATOMIC_IOSONLY) NSInteger changeInLength;


/**************************** Delegate ****************************/

@property (nullable, weak, NS_NONATOMIC_IOSONLY) id <NSTextStorageDelegate> delegate;


/**************************** Edit management ****************************/

// Notifies and records a recent change.  If there are no outstanding -beginEditing calls, this method calls -processEditing to trigger post-editing processes.  This method has to be called by the primitives after changes are made if subclassed and overridden.  editedRange is the range in the original string (before the edit).
- (void)edited:(NSTextStorageEditActions)editedMask range:(NSRange)editedRange changeInLength:(NSInteger)delta;

// Sends out -textStorage:willProcessEditing, fixes the attributes, sends out -textStorage:didProcessEditing, and notifies the layout managers of change with the -processEditingForTextStorage:edited:range:changeInLength:invalidatedRange: method.  Invoked from -edited:range:changeInLength: or -endEditing.
- (void)processEditing;


/**************************** Attribute fixing ****************************/

// Indicates if the receiver fixes invalidated attributes lazily.  The concrete UIKit subclass fixes attributes lazily by default.  The abstract class (hence, all custom subclasses) is not lazy.
@property (readonly, NS_NONATOMIC_IOSONLY) BOOL fixesAttributesLazily;

// Notes the range of attributes that requires validation.  If the NSTextStorage is not lazy this just calls fixAttributesInRange:.  If it is lazy this instead just records the range needing fixing in order to do it later.
- (void)invalidateAttributesInRange:(NSRange)range;

// Ensures all attributes in range are validated and ready to be used.  An NSTextStorage that is lazy is required to call the following method before accessing any attributes.  This gives the attribute fixing a chance to occur if necessary.  NSTextStorage subclasses that wish to support laziness must call it from all attribute accessors that they implement.  The default concrete subclass does call this from its accessors.
- (void)ensureAttributesAreFixedInRange:(NSRange)range;

/**************************** NSTextStorageObserving ****************************/
// An object conforming to NSTextStorageObserving observing and retaining NSTextStorage
@property (nullable, weak, NS_NONATOMIC_IOSONLY) id <NSTextStorageObserving> textStorageObserver API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);
@end


/****  NSTextStorage delegate methods ****/

@protocol NSTextStorageDelegate <NSObject>
@optional

// Sent inside -processEditing right before fixing attributes.  Delegates can change the characters or attributes.
- (void)textStorage:(NSTextStorage *)textStorage willProcessEditing:(NSTextStorageEditActions)editedMask range:(NSRange)editedRange changeInLength:(NSInteger)delta API_AVAILABLE(macos(10.11), ios(7.0));

// Sent inside -processEditing right before notifying layout managers.  Delegates can change the attributes.
- (void)textStorage:(NSTextStorage *)textStorage didProcessEditing:(NSTextStorageEditActions)editedMask range:(NSRange)editedRange changeInLength:(NSInteger)delta API_AVAILABLE(macos(10.11), ios(7.0));

@end

/**** Notifications ****/

UIKIT_EXTERN NSNotificationName const NSTextStorageWillProcessEditingNotification API_AVAILABLE(macos(10.0), ios(7.0));
UIKIT_EXTERN NSNotificationName const NSTextStorageDidProcessEditingNotification API_AVAILABLE(macos(10.0), ios(7.0));

#pragma mark NSTextStorageObserving
// NSTextStorageObserving defines the protocol for NSTextStorage controller objects observing changes in the text backing-store.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@protocol NSTextStorageObserving <NSObject>
// The document object
@property (nullable, strong, NS_NONATOMIC_IOSONLY) NSTextStorage *textStorage;

// The newCharRange is the range in the final string which was explicitly edited.  The invalidatedRange includes portions that changed as a result of attribute fixing. invalidatedRange is either equal to newCharRange or larger.  Controllers should not change the contents of the text storage during the execution of this message.
- (void)processEditingForTextStorage:(NSTextStorage *)textStorage edited:(NSTextStorageEditActions)editMask range:(NSRange)newCharRange changeInLength:(NSInteger)delta invalidatedRange:(NSRange)invalidatedCharRange;

// Transactional editing support
- (void)performEditingTransactionForTextStorage:(NSTextStorage *)textStorage usingBlock:(void (NS_NOESCAPE ^) (void))transaction;
@end

#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/NSTextStorage.h>
#endif
