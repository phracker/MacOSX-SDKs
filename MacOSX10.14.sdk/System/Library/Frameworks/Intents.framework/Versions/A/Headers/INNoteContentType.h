//
//  INNoteContentType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INNoteContentType_h
#define INNoteContentType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INNoteContentType) {
    INNoteContentTypeUnknown = 0,
    INNoteContentTypeText,
    INNoteContentTypeImage,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INNoteContentType_h
