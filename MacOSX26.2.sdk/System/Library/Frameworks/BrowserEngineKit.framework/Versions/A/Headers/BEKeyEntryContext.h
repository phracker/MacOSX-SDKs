//
//  BEKeyEntryContext.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BrowserEngineKit/BEKeyEntry.h>
#import <BrowserEngineKit/BEMacros.h>

#if BROWSERENGINEKIT_HAS_UIVIEW
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@interface BEKeyEntryContext : NSObject

/**
 * BEKeyEntry for which this context is representing.
 */
@property (strong, nonatomic, readonly) BEKeyEntry *keyEntry;

/**
 * Represents whether the web document is editable
 */
@property (nonatomic, assign, readwrite, getter=isDocumentEditable) BOOL documentEditable;

/**
 * Represents whether a character should be inserted.
 */
@property (nonatomic, assign, readwrite) BOOL shouldInsertCharacter;

/**
 *  Represents whether the key event should be evaluated within the context of a composed input mode.
 *
 *  When using an input mode with composed input, such as Chinese/Japanese/Korean, the markedText
 *  will be used to combine multiple key events into a single character.
 */
@property (nonatomic, assign, readwrite) BOOL shouldEvaluateForInputSystemHandling;

/**
 *  Initializes an instance of BEKeyEventContext with its corresponding `keyState`
 */
- (instancetype)initWithKeyEntry:(BEKeyEntry *)keyEntry NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // BROWSERENGINEKIT_HAS_UIVIEW
