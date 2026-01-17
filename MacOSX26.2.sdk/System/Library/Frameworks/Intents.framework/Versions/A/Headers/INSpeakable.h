//
//  INSpeakable.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

API_AVAILABLE(ios(10.0), macos(11.0), watchos(3.2), tvos(14.0))
@protocol INSpeakable <NSObject>

@property (readonly, strong, nonnull, NS_NONATOMIC_IOSONLY) NSString *spokenPhrase;
@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *pronunciationHint;
@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *vocabularyIdentifier;

@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSArray<id<INSpeakable>> *alternativeSpeakableMatches;

@optional

@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier API_DEPRECATED("Please use vocabularyIdentifier", ios(10.0, 11.0), watchos(3.2, 4.0));

@end
