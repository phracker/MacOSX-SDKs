//
//  ILMessageFilterExtension.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

/// Parent class for a MessageFilter extension's principal class.
IL_EXTERN API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILMessageFilterExtension : NSObject
@end

NS_ASSUME_NONNULL_END
