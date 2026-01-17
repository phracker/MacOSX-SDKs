//
//  Copyright © 2025 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Provides a centralized management system for registering and unregistering smartcards
/// using their token IDs.
///
/// @discussion `Registered smartcard` keeps its itself accessible via Keychain and system will automatically
/// invoke an NFC slot when a cryptographic operation is required and asks to provide the registered card.
API_AVAILABLE(ios(26.0), macCatalyst(26.0), visionos(26.0)) API_UNAVAILABLE(macos, watchos, tvos)
NS_SWIFT_SENDABLE
@interface TKSmartCardTokenRegistrationManager : NSObject

/// Default instance of registration manager
@property (class, readonly) TKSmartCardTokenRegistrationManager *defaultManager;

/// Returns the tokenIDs of all currently registered smart card tokens
@property (readonly) NSArray<NSString *> *registeredSmartCardTokens;

- (instancetype)init NS_UNAVAILABLE;

/// Registers a smartcard with a specific token ID.
/// @param tokenID ID of the smartcard
/// @param promptMessage Message that will be shown in the presented system UI when an operation with this smartcard is requested.
/// @param error On failure, this parameter is set to error describing the failure. On success, it is set to 'nil'.
/// @discussion
///     In case the same tokenID is already registered, the registration data are overwritten.
///     In case the smartcard with provided tokenID isn't found in the system, failure is returned.
- (BOOL)registerSmartCardWithTokenID:(NSString *)tokenID promptMessage:(NSString *)promptMessage error:(NSError * _Nullable __autoreleasing *)error
NS_SWIFT_NAME(registerSmartCard(tokenID:promptMessage:));

/// Unregisters a smartcard for the provided token ID.
/// @param tokenID ID of the smartcard
/// @param error On failure, this parameter is set to error describing the failure. On success, it is set to 'nil'.
/// @discussion
///     In case the tokenID is not found, failure is returned.
- (BOOL)unregisterSmartCardWithTokenID:(NSString *)tokenID error:(NSError * _Nullable __autoreleasing *)error
NS_SWIFT_NAME(unregisterSmartCard(tokenID:));

@end

NS_ASSUME_NONNULL_END
