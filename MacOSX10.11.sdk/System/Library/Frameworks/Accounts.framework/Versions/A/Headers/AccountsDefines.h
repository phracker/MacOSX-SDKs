//
//  AccountsDefines.h
//  Accounts
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//


#ifdef __cplusplus
#define ACCOUNTS_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define ACCOUNTS_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#define ACCOUNTS_CLASS_AVAILABLE(_desktopIntro, _iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(_desktopIntro, _iphoneIntro)
