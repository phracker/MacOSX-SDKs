//
//  INNoteContentType.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef INNoteContentType_h
#define INNoteContentType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INNoteContentType) {
    INNoteContentTypeUnknown = 0,
    INNoteContentTypeText,
    INNoteContentTypeImage,
} API_DEPRECATED("This enum is no longer used", ios(11.0, 12.0), watchos(4.0, 5.0)) API_UNAVAILABLE(macos, tvos);

#endif // INNoteContentType_h
