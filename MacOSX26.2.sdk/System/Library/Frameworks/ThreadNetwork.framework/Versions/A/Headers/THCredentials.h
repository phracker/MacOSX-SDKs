//
//  THCredentials.h
//  ThreadNetwork
//
//  Copyright © 2021 Apple. All rights reserved.
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern __attribute__((visibility ("default")))

/// A class that contains credentials for a Thread network.
///
/// A Thread network defines parameters that all connected devices use.
/// ``THCredentials`` provides these parameters.
API_AVAILABLE(ios(15.0)) @interface THCredentials : NSObject<NSSecureCoding>

/*
 * @description:
 *
 * All the fields represents Credentials field.
 *
 * Note :
 * If activeOperationalDataSet is nil after retrieving the credentials,
 * use rest of the parameter to join the Thread Network
 */

/// The Thread network name.
@property (nonatomic, nullable, readonly) NSString *networkName;
/// The Thread network extended PAN identifier.
@property (nonatomic, nullable, readonly) NSData *extendedPANID;
/// The identifer of an active Thread network Border Agent.
///
/// This property’s value is the MAC Extended Address, a random identifier that
/// the active Thread network border router generates.
@property (nonatomic, nullable, readonly) NSData *borderAgentID;
/// The essential operational parameters for the Thread network.
///
/// The framework parses this property, then extracts and sets
/// ``THCredentials/channel``, ``THCredentials/extendedPANID``,
/// ``THCredentials/networkKey``, ``THCredentials/networkName``,
/// ``THCredentials/panID``, and ``THCredentials/PSKC`` when you call
/// ``THClient/storeCredentialsForBorderAgent:activeOperationalDataSet:completion:``.
@property (nonatomic, nullable, readonly) NSData *activeOperationalDataSet;
/// The sixteen byte Thread network key.
@property (nonatomic, nullable, readonly) NSData *networkKey;
/// The sixteen byte Thread network pre-shared key for the Commissioner.
@property (nonatomic, nullable, readonly) NSData *PSKC;
/// The Thread network radio channel.
@property (nonatomic) uint8_t channel;
/// The two byte Thead network PAN identifier.
@property (nonatomic, nullable, readonly) NSData *panID;

/// The date and time that the framework stored the credential in the database.
@property (nonatomic, nullable, readonly) NSDate *creationDate;
/// The date and time that the framework updated the credential in the database.
@property (nonatomic, nullable, readonly) NSDate *lastModificationDate;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

