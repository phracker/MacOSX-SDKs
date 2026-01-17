//
//  INStickerType.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#ifndef INStickerType_h
#define INStickerType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INStickerType) {
    INStickerTypeUnknown = 0,
    INStickerTypeEmoji,
    INStickerTypeGeneric,
} API_AVAILABLE(ios(18.0), macos(15.0), watchos(11.0)) API_UNAVAILABLE(tvos);

#endif // INStickerType_h
