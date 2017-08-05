//
//  GKBasePlayer.h
//  Game Center
//
//  Copyright 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

NS_CLASS_AVAILABLE(10_12, 10_0) __WATCHOS_AVAILABLE(3_0)
@interface GKBasePlayer : NSObject

@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY) NSString *playerID;

// This player's full name as displayed in the Game Center in-game UI. Use this when you need to display the player's name. The display name may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *displayName;

@end
