//
//  CXCallUpdate.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXHandle;

// Any property that is not set will be ignored

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0))  API_UNAVAILABLE(macos, tvos, watchos)
@interface CXCallUpdate : NSObject <NSCopying>

/// Handle for the remote party (for an incoming call, the caller; for an outgoing call, the callee)
@property (nonatomic, copy, nullable) CXHandle *remoteHandle;

/// Override the computed caller name to a provider-defined value.
/// Normally the system will determine the appropriate caller name to display (e.g. using the user's contacts) based on the supplied caller identifier. Set this property to customize.
@property (nonatomic, copy, nullable) NSString *localizedCallerName;

/// Whether the call can be held on its own or swapped with another call
@property (nonatomic) BOOL supportsHolding;

/// Whether the call can be grouped (merged) with other calls when it is ungrouped
@property (nonatomic) BOOL supportsGrouping;

/// The call can be ungrouped (taken private) when it is grouped
@property (nonatomic) BOOL supportsUngrouping;

/// The call can send DTMF tones via hard pause digits or in-call keypad entries
@property (nonatomic) BOOL supportsDTMF;

/// The call includes video in addition to audio.
@property (nonatomic) BOOL hasVideo;

@end

NS_ASSUME_NONNULL_END
