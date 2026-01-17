//
//  MPVolumeSettings.h
//  MediaPlayer
//
//  Copyright 2008-2019 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

MP_UNAVAILABLE_BEGIN(tvos, watchos, macos, visionos)

MP_EXTERN void MPVolumeSettingsAlertShow(void)
    MP_DEPRECATED("Use MPVolumeView to present volume controls.", ios(2.0, 11.3));
MP_EXTERN void MPVolumeSettingsAlertHide(void)
    MP_DEPRECATED("Use MPVolumeView to present volume controls.", ios(2.0, 11.3));
MP_EXTERN BOOL MPVolumeSettingsAlertIsVisible(void)
    MP_DEPRECATED("Use MPVolumeView to present volume controls.", ios(2.0, 11.3));

MP_UNAVAILABLE_END
