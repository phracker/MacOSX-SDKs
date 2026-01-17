//
//  INImageNoteContent.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INNoteContent.h>

@class INImage;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos)
@interface INImageNoteContent : INNoteContent <NSSecureCoding, NSCopying>

- (instancetype)initWithImage:(INImage *)image;

// The image that comprises the note content
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *image;

@end
NS_ASSUME_NONNULL_END
