//
//  INVoiceShortcutCenter.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INIntent;
@class INShortcut;
@class INVoiceShortcut;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Lets you access shortcuts that have been added to Siri
 @seealso INVoiceShortcut
 */
API_AVAILABLE(ios(12.0), macos(12.0), watchos(5.0)) API_UNAVAILABLE(tvos)
@interface INVoiceShortcutCenter : NSObject

@property (class, strong, readonly) INVoiceShortcutCenter *sharedCenter;

/*!
 @note Use the @c sharedCenter singleton.
 */
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @note Use the @c sharedCenter singleton.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Get all of the shortcuts associated with this app that have been added to Siri.
 These could have either been added with `INUIAddVoiceShortcutViewController`, or separately by the user in the Shortcuts app.
 */
- (void)getAllVoiceShortcutsWithCompletion:(void(^)(NSArray<INVoiceShortcut *> * _Nullable voiceShortcuts, NSError * _Nullable error))completionHandler;

/*!
 @abstract Get a single shortcut (associated with this app) that has been added to Siri, by its identifier.
 */
- (void)getVoiceShortcutWithIdentifier:(NSUUID *)identifier completion:(void(^)(INVoiceShortcut * _Nullable voiceShortcut, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(getVoiceShortcut(with:completion:));

/*!
 @abstract Set some shortcuts that should be suggested to the user to add to Siri.
 @discussion These suggestions are shown to the user in the Shortcuts app.
 */
- (void)setShortcutSuggestions:(NSArray<INShortcut *> *)suggestions;

@end

NS_ASSUME_NONNULL_END
