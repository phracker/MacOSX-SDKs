/*
	NSTextInputContext.h
	Application Kit
	Copyright (c) 2008-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSTextInputClient.h>


NS_ASSUME_NONNULL_BEGIN

@class NSEvent;

NS_CLASS_AVAILABLE(10_6, NA)
@interface NSTextInputContext : NSObject {
@private
    id _client; // weak reference

    NSArray *_inputLocales;

    void *_documentID;
    id _keyBindings;
    id _keyBindingManager;

    NSString *_commandCharacters;

    NSInteger _documentRefcon;

    id _reserved[2];
    id _auxiliary;

    struct {
	unsigned int _acceptsGlyphInfo:1;
	unsigned int _secureInput:1;

	unsigned int _attributedString:1;
	unsigned int _fractionOfDistance:1;
	unsigned int _baselineDelta:1;
	unsigned int _windowLevel:1;
	unsigned int _drawsVertically:1;

	unsigned int _compatibilityMode:1;
	unsigned int _hasTS:1;
	unsigned int _hasLM:1;

	unsigned int _inputLocaleGeneration:16;
	unsigned int _blockTSM:1;
	unsigned int _keyProcess:1;
	unsigned int _preflight:1;
	unsigned int _bindingFound:1;

	unsigned int _unmarkbeforeinsert:1;
	unsigned int _completionHandlingClient:1;
    } _ticFlags;
}

/* The current activated text input context object. The Cocoa Text Input system communicates primarily with the client of the activated input context via the NSTextInputClient protocol.
 */
+ (nullable NSTextInputContext *)currentInputContext;

/* The designated initializer.
 */
- (instancetype)initWithClient:(id <NSTextInputClient>)theClient;

/**** Properties *****/
/* Returns the owner of this input context. The owner, typically an NSView, retains its NSTextInputContext instance. NSTextInputContext doesn't retain its client.
 */
@property(readonly) id <NSTextInputClient> client; 

/* Indicates whether the client handles NSGlyphInfoAttributeName or not. The default value is determined by examining the return value sending -validAttributesForMarkedText to client at initialization.
 */
@property BOOL acceptsGlyphInfo;

/* Specifies the set of keyboard input source locales allowed when this input context is active. NSAllRomanInputSourcesLocaleIdentifier can be specified as a valid locale.
 */
@property(nullable, copy) NSArray<NSString *> *allowedInputSourceLocales;


/**** Activation *****/
/* Invoked when the receiver gets activated/deactivated.
 */
- (void)activate;
- (void)deactivate;

/**** Input source interface ****/
/* Tells the Cocoa Text Input system to handle mouse/key events. Returns YES if the system consumed the event.
 */
- (BOOL)handleEvent:(NSEvent *)theEvent;

/* Notifies the system to discard the current conversion session. The client should clear its marked range when sending this message.
 */
- (void)discardMarkedText;

/* Notifies the Cocoa Text Input system that the position information previously queried via methods like -firstRectForCharacterRange:actualRange: needs to be updated.
 */
- (void)invalidateCharacterCoordinates;


/**** Text Input sources handling ****/
/* Text Input source handling API identifies text input sources with text input source identifier strings (i.e. "com.apple.inputmethod.Kotoeri.Japanese") supplied by the underlying TextInputSources framework. The ID corresponds to the kTISPropertyInputSourceID attribute.
 */

/* The array of keyboard text input source identifier strings available to the receiver.
 */
@property(nullable, readonly) NSArray<NSString *> *keyboardInputSources;

/* The identifier string for the selected keyboard text input source.
 */
@property(nullable, copy) NSString *selectedKeyboardInputSource;


/**** Text Input source attributes ****/
/* Returns the display name for inputSourceIdentifier.
 */
+ (nullable NSString *)localizedNameForInputSource:(NSString *)inputSourceIdentifier;
@end

/**** Notifications ****/
/* Notified whenever the selected text input source changes.
 */
APPKIT_EXTERN NSString * NSTextInputContextKeyboardSelectionDidChangeNotification NS_AVAILABLE_MAC(10_6);

NS_ASSUME_NONNULL_END

