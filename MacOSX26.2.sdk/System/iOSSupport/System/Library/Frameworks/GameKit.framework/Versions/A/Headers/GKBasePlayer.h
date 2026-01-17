// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

API_AVAILABLE(ios(10.0), macos(10.12), tvos(10.0), visionos(1.0), watchos(3.0))
@interface GKBasePlayer : NSObject<NSCopying>

@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY) NSString *playerID API_DEPRECATED_WITH_REPLACEMENT("Use ``GKPlayer/gamePlayerID`` or ``GKPlayer/teamPlayerID`` instead.", ios(10.0,13.0), macos(10.12,10.15), tvos(10.0,13.0), visionos(1.0,1.0), watchos(3.0,6.0));

/// This player's name representation as displayed in the Game Center in-game UI. Use this when you need to display the player's name. The display name may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *displayName;

@end
