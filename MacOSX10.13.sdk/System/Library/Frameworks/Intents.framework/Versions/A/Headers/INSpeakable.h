//
//  INSpeakable.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol INSpeakable <NSObject>

@property (readonly, nonnull, NS_NONATOMIC_IOSONLY) NSString *spokenPhrase;
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *pronunciationHint;
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *vocabularyIdentifier;

@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSArray<id<INSpeakable>> *alternativeSpeakableMatches;

@optional

@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier API_DEPRECATED("Please use vocabularyIdentifier", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@end
