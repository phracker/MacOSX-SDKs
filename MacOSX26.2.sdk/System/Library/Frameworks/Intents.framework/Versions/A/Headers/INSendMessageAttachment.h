//
//  INSendMessageAttachment.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INFile;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), watchos(7.0), macos(12.0))
API_UNAVAILABLE(tvos)
@interface INSendMessageAttachment : NSObject

+ (INSendMessageAttachment *)attachmentWithAudioMessageFile:(INFile *)audioMessageFile;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INFile *audioMessageFile;

@end

NS_ASSUME_NONNULL_END
