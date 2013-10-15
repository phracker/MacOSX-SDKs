//
//  SocialDefines.h
//  Social
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define SOCIAL_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define SOCIAL_EXTERN	    extern __attribute__((visibility ("default")))
#endif

#define SOCIAL_CLASS_AVAILABLE(_desktopIntro, _iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(_desktopIntro, _iphoneIntro)

