//
//  GKVoiceChat.h
//  Game Center
//
//  Copyright 2010-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, GKVoiceChatPlayerState) {
    GKVoiceChatPlayerConnected,
    GKVoiceChatPlayerDisconnected,
    GKVoiceChatPlayerSpeaking,
    GKVoiceChatPlayerSilent,
    GKVoiceChatPlayerConnecting
};

@class GKPlayer;


NS_ASSUME_NONNULL_BEGIN
/// GKVoiceChat represents an instance of a named voice communications channel
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_PROHIBITED
@interface GKVoiceChat : NSObject

- (void)start;  /// start receiving audio from the chat
- (void)stop;   /// stop receiving audio from the chat

- (void)setPlayer:(GKPlayer *)player muted:(BOOL)isMuted NS_AVAILABLE(10_10, 8_0);

@property(copy, NS_NONATOMIC_IOSONLY) void(^playerVoiceChatStateDidChangeHandler)(GKPlayer *player, GKVoiceChatPlayerState state) NS_AVAILABLE(10_10, 8_0);

@property(readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;  // name the chat was created with
@property(assign, getter=isActive, NS_NONATOMIC_IOSONLY)    BOOL active; // make this session active and route the microphone
@property(assign, NS_NONATOMIC_IOSONLY) float volume; // default 1.0 (max is 1.0, min is 0.0)

@property(readonly, NS_NONATOMIC_IOSONLY) NSArray<GKPlayer *> *players NS_AVAILABLE(10_10, 8_0); // array of GKPlayer *

+ (BOOL)isVoIPAllowed;

@end

@interface GKVoiceChat (Deprecated)
@property(copy, NS_NONATOMIC_IOSONLY) void(^playerStateUpdateHandler)(NSString *playerID, GKVoiceChatPlayerState state) NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use setPlayerVoiceChatStateDidChangeHandler:") ;
@end

@interface GKVoiceChat (Obsoleted)
/*** This property is obsolete. ***/
@property(readonly, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *playerIDs NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "use players") ;

/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)setMute:(BOOL)isMuted forPlayer:(NSString *)playerID NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "This is never invoked and its implementation does nothing, use setPlayer:muted:") ;
@end
NS_ASSUME_NONNULL_END
