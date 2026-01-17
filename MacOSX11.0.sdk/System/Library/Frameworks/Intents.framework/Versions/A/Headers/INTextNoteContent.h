//
//  INTextNoteContent.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INNoteContent.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INTextNoteContent : INNoteContent <NSSecureCoding, NSCopying>

- (instancetype)initWithText:(NSString *)text;

// The text that comprises the note content
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *text;

@end
NS_ASSUME_NONNULL_END
