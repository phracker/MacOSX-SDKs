//
//  GKVoiceChat.h
//  GameKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

enum {
    GKVoiceChatPlayerConnected,
    GKVoiceChatPlayerDisconnected,
    GKVoiceChatPlayerSpeaking,
    GKVoiceChatPlayerSilent,
    GKVoiceChatPlayerConnecting
};
typedef NSInteger GKVoiceChatPlayerState;

// GKVoiceChat represents an instance of a named voice communications channel
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKVoiceChat : NSObject
@end
	
@interface GKVoiceChat (GKAdditions)
- (void)start;  // start receiving audio from the chat
- (void)stop;   // stop receiving audio from the chat

- (void)setMute:(BOOL)isMuted forPlayer:(NSString *)playerID;

@property(copy, NS_NONATOMIC_IOSONLY) void(^playerStateUpdateHandler)(NSString *playerID, GKVoiceChatPlayerState state);
@property(readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;  // name the chat was created with
@property(assign, getter=isActive, NS_NONATOMIC_IOSONLY) BOOL active; // make this session active and route the microphone 
@property(assign, NS_NONATOMIC_IOSONLY) float volume; // default 1.0 (max is 1.0, min is 0.0)


@property(readonly, NS_NONATOMIC_IOSONLY) NSArray *playerIDs __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0); // list of GKPlayerIDs

+ (BOOL)isVoIPAllowed;

@end
