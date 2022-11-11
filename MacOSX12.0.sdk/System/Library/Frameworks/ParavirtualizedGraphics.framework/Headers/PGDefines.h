//
//  PGDefines.h
//  ParavirtualizedGraphics
//
//  Copyright © 2018-2020 Apple Inc. All rights reserved.
//

#ifndef PGDefines_h
#define PGDefines_h

#define PG_EXPORT __attribute__((visibility ("default")))
#ifdef __cplusplus
#define PG_EXTERN extern "C" PG_EXPORT
#else
#define PG_EXTERN extern PG_EXPORT
#endif

#define PG_SUPPORT_EFI 1
#define PG_SUPPORT_PAUSE_UNPAUSE 1
#define PG_SUPPORT_CURSOR_GLYPH_HANDLER2 1
#define PG_SUPPORT_DISPLAY_SLEEP_HANDLER 1
#define PG_SUPPORT_DISPLAY_SLEEP PG_SUPPORT_DISPLAY_SLEEP_HANDLER
#define PG_SUPPORT_RESET 1
#define PG_SUPPORT_MODELIST_RESPONSIVENESS_HANDLER 1

#endif /* PGDefines_h */
