#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<ShareSheet/ShareSheetDefines.h>)
//
//  ShareSheetDefines.h
//  ShareSheet
//
//  Created by Jacob Klapper on 2/19/18.
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define SHARESHEET_EXTERN    extern "C" __attribute__((visibility ("default")))
#else
#define SHARESHEET_EXTERN    extern __attribute__((visibility ("default")))
#endif

#else
#import <ShareSheet/ShareSheetDefines.h>
#endif
