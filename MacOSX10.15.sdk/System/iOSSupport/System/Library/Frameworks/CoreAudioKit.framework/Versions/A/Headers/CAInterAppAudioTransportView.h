// =================================================================================================
// CAInterAppAudioTransportView.h
// =================================================================================================
/*
 File:		CAInterAppAudioTransportView.h
 Framework:	CoreAudioKit
 
 Copyright (c) 2014 Apple Inc. All Rights Reserved.
 */

#import <UIKit/UIKit.h>
#import <AudioUnit/AudioUnit.h>


NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("Inter-App Audio API is deprecated in favor of Audio Units", ios(8.0, 13.0)) API_UNAVAILABLE(macCatalyst, macos, tvos, watchos)
@interface CAInterAppAudioTransportView : UIView
@property(getter=isEnabled)							BOOL enabled;

@property(nonatomic,readonly,getter=isPlaying)		BOOL playing;
@property(nonatomic,readonly,getter=isRecording)	BOOL recording;
@property(nonatomic,readonly,getter=isConnected)	BOOL connected;

/* Appearance properties */
@property(nonatomic,strong)UIColor *labelColor;
@property(nonatomic,strong)UIFont  *currentTimeLabelFont;

@property(nonatomic,strong)UIColor *rewindButtonColor;
@property(nonatomic,strong)UIColor *playButtonColor;
@property(nonatomic,strong)UIColor *pauseButtonColor;
@property(nonatomic,strong)UIColor *recordButtonColor;

-(void) setOutputAudioUnit: (AudioUnit) au;

@end
NS_ASSUME_NONNULL_END
