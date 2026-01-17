//
//  STKDefines.h
//  StickerKit
//
//  Created by Adam Bradford on 10/11/23.
//

#import <Foundation/Foundation.h>

#ifndef STK_EXTERN
#ifdef __cplusplus
#define STK_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define STK_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif

