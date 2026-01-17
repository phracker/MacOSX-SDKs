//
//  BEAudioSession.h
//  BrowserEngineCore
//

#import <Foundation/Foundation.h>
#import <BrowserEngineCore/BEMacros.h>
 
NS_ASSUME_NONNULL_BEGIN

@class AVAudioSession;
@class AVAudioSessionPortDescription;

/// An object that represents an audio session
API_AVAILABLE(ios(26.0))
API_UNAVAILABLE(macos, watchos, tvos, visionos)
@interface BEAudioSession : NSObject

/// Creates a BE audio session from an  AV audio session
///
/// - Parameters:
///   - session: The AV audio session
-(instancetype)initWithAudioSession:(AVAudioSession*)audioSession;

/// Gets the set of output ports that are available for routing.
@property (readonly, nullable) NSArray<AVAudioSessionPortDescription *> *availableOutputs;

/*!
    @brief Select a preferred output port for audio routing.
    Setting a nil value will clear the preference.
*/
- (BOOL)setPreferredOutput:(nullable AVAudioSessionPortDescription *)outPort error:(NSError **)outError;

/// Get the preferred output port.  Will be nil if no preference has been set.
@property (readonly, nullable) AVAudioSessionPortDescription *preferredOutput;

@end

NS_ASSUME_NONNULL_END
