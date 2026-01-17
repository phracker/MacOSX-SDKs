//
//  INIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class INImage;
@class INParameter;
@class INParameterImage;

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INIntent : NSObject <NSCopying, NSSecureCoding>

// Returns the identifier of the receiver.
// Could be used to keep track of the entire transaction for resolve, confirm and handleIntent
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

// A human-understandable string representation of the intent's user-facing behavior
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *intentDescription API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

// A human-understandable string that can be shown to the user as an suggestion of the phrase they might want to use when adding intent as a shortcut to Siri.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *suggestedInvocationPhrase API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx);

// Set an image associated with a parameter on the receiver. This image will be used in display of the receiver throughout the system.
- (void)setImage:(INImage * _Nullable)image forParameterNamed:(NSString *)parameterName API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)) NS_REFINED_FOR_SWIFT;
- (INImage * _Nullable)imageForParameterNamed:(NSString *)parameterName API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14)) NS_REFINED_FOR_SWIFT;

// The image most relevant for display to the receiver, accounting for both parameter-associated images and other images defined in the receiver.
- (INImage * _Nullable)keyImage;

@end

NS_ASSUME_NONNULL_END
