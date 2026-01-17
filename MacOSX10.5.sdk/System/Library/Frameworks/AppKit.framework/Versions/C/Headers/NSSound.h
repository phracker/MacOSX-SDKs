/*
        NSSound.h
	Application Kit
	Copyright (c) 1997-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSBundle.h>
#import <Foundation/NSDate.h>

@class NSData, NSURL, NSPasteboard;

APPKIT_EXTERN NSString * const NSSoundPboardType;

@interface NSSound : NSObject <NSCopying, NSCoding> {
@private
    id _delegate;
    id _info;
    id _reserved[6];
    NSUInteger _sFlags;
}

/* If this finds & creates the sound, only name is saved when archived.
*/
+ (id)soundNamed:(NSString *)name;

/* When archived, byref ? saves url : saves contents.
*/
- (id)initWithContentsOfURL:(NSURL *)url byReference:(BOOL)byRef;


- (id)initWithContentsOfFile:(NSString *)path byReference:(BOOL)byRef;

/* Whether the data comes in from disk, or via this method, NSSound expects it to have a proper magic number, sound header, and data.  Only uncompressed AIFF data is currently supported.
*/
- (id)initWithData:(NSData *)data;

- (BOOL)setName:(NSString *)string;
- (NSString *)name;

// Pasteboard support
+ (BOOL)canInitWithPasteboard:(NSPasteboard *)pasteboard;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
+ (NSArray*)soundUnfilteredTypes;
#endif
- (id)initWithPasteboard:(NSPasteboard *)pasteboard;
- (void)writeToPasteboard:(NSPasteboard *)pasteboard;

// Sound operations
- (BOOL)play;		/* sound is played asynchronously */
- (BOOL)pause;		/* returns NO if sound not paused */
- (BOOL)resume;		/* returns NO if sound not resumed */
- (BOOL)stop;
- (BOOL)isPlaying;

- (id)delegate;
- (void)setDelegate:(id)aDelegate;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Returns the duration of the sound in seconds.
*/
- (NSTimeInterval)duration;

/* Sets and gets the volume for the sound without affecting the system-wide volume. The valid range is between 0. and 1., inclusive.
*/
- (void)setVolume:(float)volume;
- (float)volume;

/* If the sound is playing, currentTime returns the number of  seconds into the sound where playing is occurring.  If the sound is not playing, currentTime returns the number of seconds into the sound where playing would start.
*/
- (NSTimeInterval)currentTime;

/* Sets the location of the currently playing audio to seconds. If the sound is not playing, this sets the number of seconds into the sound where playing would begin. The currentTime is not archived, copied, or stored on the pasteboard - all new sounds start with a currentTime of 0.
*/
- (void)setCurrentTime:(NSTimeInterval)seconds;

/* Sets whether the sound should automatically restart when it is finished playing.  If the sound is currently playing, this takes effect immediately. The default is NO.  A looping sound does not send sound:didFinishPlaying: to its delegate unless it is sent a stop message.
*/
- (void)setLoops:(BOOL)val;

/* Returns whether the sound will automatically restart when it is finished playing. */
- (BOOL)loops;

/* Set the UID of the audio device where playback will occur.  Pass nil to play on the default output device.
*/
- (void)setPlaybackDeviceIdentifier:(NSString *)deviceUID;

/* Get the UID of the audio device where playback will occur.  Returns nil if playback tracks the default device, which is the default.
*/
- (NSString *)playbackDeviceIdentifier;

/* Set the channel mapping for the sound.  Pass an array of NSNumbers, which maps sound channels to device channels.  Pass -1 to indicate that a particular sound channel should be ignored.  For any channel, instead of an NSNumber, you may also pass an NSArray of NSNumbers to map a single sound channel to multiple device channels.
*/
- (void)setChannelMapping:(NSArray *)channelMapping;

/* Get the channel mapping for the sound.  By default, a stereo sound maps its first and second channels to the left and right device channels, while a mono sound maps its single channel across every device channel.
*/
- (NSArray *)channelMapping;

#endif

@end

@interface NSSound(NSDeprecated)

/* Methods that were deprecated in Mac OS 10.5. You can now use +soundUnfilteredTypes to get an array of Uniform Type Identifiers (UTIs).
*/
+ (NSArray *)soundUnfilteredFileTypes;
+ (NSArray *)soundUnfilteredPasteboardTypes;

@end

@interface NSObject (NSSoundDelegateMethods)

- (void)sound:(NSSound *)sound didFinishPlaying:(BOOL)aBool;

@end

@interface NSBundle (NSBundleSoundExtensions)

/* May return nil if no file found
*/
- (NSString *)pathForSoundResource:(NSString *)name;

@end

