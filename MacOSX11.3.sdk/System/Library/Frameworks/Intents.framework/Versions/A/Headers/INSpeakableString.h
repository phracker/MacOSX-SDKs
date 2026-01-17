//
//  INSpeakableString.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INSpeakable.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), macos(11.0), watchos(3.2))
@interface INSpeakableString : NSObject <INSpeakable, NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithVocabularyIdentifier:(NSString *)vocabularyIdentifier
                                spokenPhrase:(NSString *)spokenPhrase
                           pronunciationHint:(nullable NSString *)pronunciationHint NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithIdentifier:(NSString *)identifier
                      spokenPhrase:(NSString *)spokenPhrase
                 pronunciationHint:(nullable NSString *)pronunciationHint API_DEPRECATED("Please use -initWithVocabularyIdentifier:spokenPhrase:pronunciationHint:", ios(10.0, 11.0), watchos(3.2, 4.0)) API_UNAVAILABLE(macos, tvos);

- (instancetype)initWithSpokenPhrase:(NSString *)spokenPhrase API_AVAILABLE(ios(10.2));

@end

NS_ASSUME_NONNULL_END

