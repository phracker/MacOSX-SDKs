//
//  ILClassificationUIExtensionContext.h
//  IdentityLookup
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/IdentityLookup.h>

NS_ASSUME_NONNULL_BEGIN

@class ILClassificationResponse;

/// Represents a Classification UI extension request's context.
IL_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(13.0)) API_UNAVAILABLE( macos, tvos, watchos)
@interface ILClassificationUIExtensionContext : NSExtensionContext

@property (nonatomic, getter=isReadyForClassificationResponse) BOOL readyForClassificationResponse;

@end

NS_ASSUME_NONNULL_END
