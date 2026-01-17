#if !__has_include(<AVKitCore/AVPlaybackSpeed.h>)
//
//  AVPlaybackSpeed.h
//  AVKit
//
//  Created by adesjarlais on 11/13/21.
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_OSX || TARGET_OS_MACCATALYST
#import <AVKit/AVKitDefines.h>
#else
#import <AVKit/AVKitDefines.h>
#endif // #TARGET_OS_OSX || TARGET_OS_MACCATALYST


NS_ASSUME_NONNULL_BEGIN

// MARK: -

/*!
 @class         AVPlaybackSpeed
 @abstract      Class used to define a user selectable playback speed in a playback UI.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVPlaybackSpeed : NSObject

AVKIT_INIT_UNAVAILABLE

/*!
 @property      systemDefaultSpeeds
 @abstract      A list of playback speeds to be used by default across the system.
 */
@property (nonatomic, readonly, class) NSArray<AVPlaybackSpeed *> *systemDefaultSpeeds;


/*!
 @method         initWithRate:localizedName:
 @param         rate
				The rate to be used when this playback speed is selected.
 @param         localizedName
				A localized name to be displayed representing this playback speed in a UI.
 @abstract      Initializes an AVPlaybackSpeed.
 */
- (instancetype)initWithRate:(float)rate localizedName:(NSString *)localizedName;


/*!
 @property      rate
 @abstract      The rate associated with this object. When this playback speed is selected this rate will be set in response to the play button being pressed.
 */
@property (nonatomic, readonly) float rate;

/*!
 @property      localizedName
 @abstract      A localized name for this playback speed.
 @discussion    This name will be used to represent this playback speed in playback UIs where more space is available.
 */
@property (nonatomic, readonly) NSString *localizedName;

/*!
 @property      localizedNumericName
 @abstract      A localized name for this playback speed used when space is limited.
 @discussion    This name will be used to represent this playback speed in playback UIs where limited space is available.
 */
@property (nonatomic, readonly) NSString *localizedNumericName;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVKitCore/AVPlaybackSpeed.h>
#endif
