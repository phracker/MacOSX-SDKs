//
//  INSpeakable.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol INSpeakable <NSObject>

@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *spokenPhrase;
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *pronunciationHint;
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@end
