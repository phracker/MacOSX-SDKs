//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LABiometryType.h>
#import <LocalAuthentication/LACompanionType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos)
@interface LADomainStateBiometry : NSObject

/// Indicates biometry type available on the device.
@property (nonatomic, readonly) LABiometryType biometryType;

/// Contains state hash data for the available biometry type. Returns `nil` if no biometry entities are enrolled.
///
/// @discussion  If biometric database was modified (fingers, faces were removed or added), `stateHash`
///              data will change. Nature of such database changes cannot be determined
///              but comparing data of `stateHash` after different evaluatePolicy calls
///              will reveal the fact database was changed between the calls.
///
/// @warning Please note that the value returned by this property can change exceptionally between major OS versions even if
///          the state of biometry has not changed.
@property (nonatomic, readonly, nullable) NSData *stateHash;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos, visionos)
@interface LADomainStateCompanion : NSObject

/// Indicates types of companions paired with the device.
/// The elements are NSNumber-wrapped instances of @c `LACompanionType`.
@property (nonatomic, readonly) NSSet<NSNumber *> *availableCompanionTypes NS_REFINED_FOR_SWIFT;

/// Contains combined state hash data for all available companion types. . Returns `nil` if no companion devices are paired.
///
/// @discussion  As long as database of paired companion devices doesn't change,
///              `stateHash` stays the same for the same set of `availableCompanions`.
///
///              If database of paired companion devices was modified, `stateHash`
///              data will change. Nature of such database changes cannot be determined
///              but comparing data of `stateHash` after different policy evaluation
///              will reveal the fact database was changed between calls.
///
///              If you are interested in a state hash for a specific companion type
///              you can use `stateHashForCompanionType` method.
///
/// @warning Please note that the value returned by this property can change exceptionally between major OS versions even if
///          the list of paired companions has not changed.
@property (nonatomic, readonly, nullable) NSData *stateHash;

/// Returns state hash data for the given companion type.
///
/// @discussion  If database of paired devices of the given type was modified state hash
///              data will change. Nature of such database changes cannot be determined
///              but comparing data of state hash after different policy evaluation
///              will reveal the fact database was changed between calls.
///
/// @param companionType The companion type for which state hash data should be returned.
- (NSData * _Nullable)stateHashForCompanionType:(LACompanionType)companionType NS_SWIFT_NAME(stateHash(for:));

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos)
@interface LADomainState : NSObject

/// Contains biometric domain state.
@property (nonatomic, readonly) LADomainStateBiometry *biometry;

/// Contains companion domain state.
@property (nonatomic, readonly) LADomainStateCompanion *companion
API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos, visionos);

/// Contains combined state hash data for biometry and companion state hashes.
///
/// @warning Please note that the value returned by this property can change exceptionally between major OS versions even if
///          the list of paired companions has not changed.
@property (nonatomic, readonly, nullable) NSData *stateHash;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
