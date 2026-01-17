//
//  INIntent.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/INShortcutAvailabilityOptions.h>

NS_ASSUME_NONNULL_BEGIN

@class INImage;
@class INParameter;
@class INParameterImage;

API_AVAILABLE(ios(10.0), macos(11.0), watchos(3.2), tvos(14.0))
@interface INIntent : NSObject <NSCopying, NSSecureCoding>

// Returns the identifier of the receiver.
// Could be used to keep track of the entire transaction for resolve, confirm and handleIntent
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

// A human-understandable string representation of the intent's user-facing behavior
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *intentDescription API_AVAILABLE(ios(11.0), watchos(4.0));

// A human-understandable string that can be shown to the user as an suggestion of the phrase they might want to use when adding intent as a shortcut to Siri.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *suggestedInvocationPhrase API_AVAILABLE(ios(12.0), watchos(5.0));

// Defines additional contexts in which this intent is relevant to be suggested to the user. Applies to intents donated using INInteraction or set as suggested using INVoiceShortcutCenter.
@property (readwrite, assign, NS_NONATOMIC_IOSONLY) INShortcutAvailabilityOptions shortcutAvailability API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);

// Set an image associated with a parameter on the receiver. This image will be used in display of the receiver throughout the system.
- (void)setImage:(INImage * _Nullable)image forParameterNamed:(NSString *)parameterName API_AVAILABLE(ios(12.0), watchos(5.0)) NS_REFINED_FOR_SWIFT;
- (INImage * _Nullable)imageForParameterNamed:(NSString *)parameterName API_AVAILABLE(ios(12.0), watchos(5.0)) NS_REFINED_FOR_SWIFT;

// The image most relevant for display to the receiver, accounting for both parameter-associated images and other images defined in the receiver.
- (INImage * _Nullable)keyImage;

@end

NS_ASSUME_NONNULL_END
