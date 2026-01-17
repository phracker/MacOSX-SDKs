//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LAEnvironmentMechanism.h>
#import <LocalAuthentication/LACompanionType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0))
NS_SWIFT_NAME(LAEnvironment.MechanismCompanion)
NS_SWIFT_SENDABLE
@interface LAEnvironmentMechanismCompanion : LAEnvironmentMechanism

/// Type of the companion.
@property (nonatomic, readonly) LACompanionType type;

/// @brief Hash of the current companion pairing as returned by @c LAContext.domainState.companion.stateHash(for:)
/// @discussion If no companion are paired for this companion type, @c stateHash property is @c nil.
///             If at least one companion is paired for this companion type, @c stateHash is not @c nil and
///             it changes whenever the set of paired companions of this type is changed.
@property (nonatomic, readonly, nullable) NSData *stateHash;

@end

NS_ASSUME_NONNULL_END
