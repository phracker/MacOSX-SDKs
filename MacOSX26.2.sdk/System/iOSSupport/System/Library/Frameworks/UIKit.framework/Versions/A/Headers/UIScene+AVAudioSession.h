#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIScene+AVAudioSession.h>)
//
//  UIScene+AVAudioSession.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIScene.h>

@class AVAudioSession;

API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, watchos, tvos, macos)
@interface UIScene (AVAudioSession)

// Access the AVAudioSession containing all sounds that implicitly belong
// to this UIScene (e.g. RealityKit sounds played from a RealityView
// in the UIScene.) This AVAudioSession is always configured with a
// head-tracked spatial experience anchored to this UIScene so trying
// to modify that on the session will throw an error. The default audio
// session is only non-nil for scene types that might have implicitly
// associated audio objects. It is recommended clients access and
// interact with this audio session not from a main actor.
- (void)getDefaultAudioSessionWithCompletionHandler:(void(^_Nonnull)(AVAudioSession * _Nullable))handler NS_SWIFT_ASYNC_NAME(getter:defaultAudioSession()) NS_SWIFT_NONISOLATED API_UNAVAILABLE(watchos);

@end

#else
#import <UIKitCore/UIScene+AVAudioSession.h>
#endif
