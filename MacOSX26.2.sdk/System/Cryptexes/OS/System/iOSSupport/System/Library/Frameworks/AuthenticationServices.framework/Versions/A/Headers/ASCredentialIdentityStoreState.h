//
//  ASCredentialIdentityStoreState.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(14.0), macos(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASCredentialIdentityStoreState : NSObject

/*! @abstract Get the enabled state of the credential identity store.
 @result YES if the credential identity store is enabled.
 @dicussion You can only modify the credential identity store when it is enabled.
 */
@property (nonatomic, readonly, getter=isEnabled) BOOL enabled;

/*! @abstract Get whether the credential identity store supports incremental updates.
 @result YES if the credential identity store supports incremental updates.
 @discussion You should examine the value returned by this property to find out if
 the credential identity store can accept incremental updates. If incremental updates
 are supported, you can update the credential identity store with only the new changes
 since the last time it was updated. Otherwise, you should update the credential identity
 store by adding all credential identities.
 */
@property (nonatomic, readonly) BOOL supportsIncrementalUpdates;

@end

NS_ASSUME_NONNULL_END
