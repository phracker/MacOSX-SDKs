//
//  MAMusicHaptics.h
//  MediaAccessibility
//

/* Music Haptics plays haptic tracks along with audio tracks based on the Now Playing Session.
   To participate in Music Haptics, add the following key to the Info.plist of the app:
 
 MusicHapticsSupported -> True
 
 To indicate which track is playing accurately, supply the international standard recording code as part of
 the NowPlayingInfo in the NowPlayingInfoCenter, using the following key:
 
 MPNowPlayingInfoPropertyInternationalStandardRecordingCode
 
 Use the MAMusicHapticsManager class to observe the status of haptic track playback.
 */

#ifdef __OBJC__

#ifndef MediaAccessibility_MAMusicHapticsManager_h
#define MediaAccessibility_MAMusicHapticsManager_h

#import <Foundation/Foundation.h>
#import <MediaAccessibility/MADefinitions.h>

NS_ASSUME_NONNULL_BEGIN

MA_EXPORT NSNotificationName const MAMusicHapticsManagerActiveStatusDidChangeNotification API_AVAILABLE(ios(18.0), tvos(18.0), watchos(11.0), macos(15.0), visionos(2.0)) NS_SWIFT_NAME(MAMusicHapticsManager.activeStatusDidChangeNotification);

MA_EXPORT API_AVAILABLE(ios(18.0), tvos(18.0), watchos(11.0), macos(15.0), visionos(2.0))
@interface MAMusicHapticsManager : NSObject

@property (nonatomic, readonly, class) MAMusicHapticsManager *sharedManager;

/*!
 @abstract Whether the user setting to indicate Music Haptics are currently active.
 @result A boolean result.
 */
@property (nonatomic, readonly) BOOL isActive;

/*!
 @abstract In an asynchronous completion handler, returns whether a specific media track with the supplied
 ISRC has an available haptic track.
 */
- (void)checkHapticTrackAvailabilityForMediaMatchingCode:(NSString *)internationalStandardRecordingCode completionHandler:(void (NS_SWIFT_SENDABLE ^ _Nullable)(BOOL musicHapticsAvailable))completionHandler NS_SWIFT_ASYNC_NAME(isHapticTrackAvailable(forMediaMatching:));

/*!
 @abstract Determine the status of haptic playback for the now playing track asynchronously. This will only be delivered for the app that is the active Now Playing app.
 */
- (nullable id<NSCopying>)addStatusObserver:(void (^)(NSString *internationalStandardRecordingCode, BOOL musicHapticsActive))statusHandler;
- (void)removeStatusObserver:(id<NSCopying>)registrationToken;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif

#ifdef __swift__
// This struct is not available in Objective-C. Its only purpose is to create a namespace for accessibility symbols in Swift.
typedef struct MAMusicHaptics { void *_reserved; } MAMusicHaptics;
#endif

#endif

