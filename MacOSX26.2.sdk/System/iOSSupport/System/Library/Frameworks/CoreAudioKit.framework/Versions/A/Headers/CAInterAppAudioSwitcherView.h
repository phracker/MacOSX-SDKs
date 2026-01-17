// =================================================================================================
// CAInterAppAudioSwitcherView.h
// =================================================================================================
/*
 File:		CAInterAppAudioSwitcherView.h
 Framework:	CoreAudioKit
 
 Copyright (c) 2014 Apple Inc. All Rights Reserved.
 */


#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioUnit.h>

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("Inter-App Audio API is deprecated in favor of Audio Units", ios(8.0, 13.0), macCatalyst(14.0, 14.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface CAInterAppAudioSwitcherView : UIView
@property (getter = isShowingAppNames) BOOL showingAppNames; // Defaults to NO

// Node apps should pass their output audio unit
// Host apps should pass null
- (void)setOutputAudioUnit:(nullable AudioUnit)au;
- (CGFloat) contentWidth;

@end
NS_ASSUME_NONNULL_END
