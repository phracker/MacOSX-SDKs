//
//  INPerson+SiriAdditions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INPerson.h>

#import <Intents/INSpeakable.h>

NS_ASSUME_NONNULL_BEGIN

@interface INPerson (SiriAdditions) <INSpeakable>

// This property is filled in with what Siri thinks are close matches to what the user said
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *siriMatches API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx);

// This property is set to YES when the user says things like "Search for messages from me", etc.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) BOOL isMe API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@end

NS_ASSUME_NONNULL_END
