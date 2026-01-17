//
//  ILMessageFilterCapabilitiesQueryResponse.h
//  IdentityLookup
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

/// A response to an ILMessageFilterCapabilitiesQueryRequest.
IL_EXTERN API_AVAILABLE(ios(16.0), macCatalyst(16.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILMessageFilterCapabilitiesQueryResponse : NSObject <NSSecureCoding>

/// Array of type ILMessageFilterSubAction under Transactional
@property (nonatomic, copy) NSArray<NSNumber *> *transactionalSubActions;

/// Array of type ILMessageFilterSubAction under Promotional
@property (nonatomic, copy) NSArray<NSNumber *> *promotionalSubActions;

@end

NS_ASSUME_NONNULL_END
