// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialDescriptor.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @abstract A string indicating a transport for communicating with an authenticator.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
typedef NSString *ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransport NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(ASAuthorizationSecurityKeyPublicKeyCredentialDescriptor.Transport);

/*! @abstract Indicates using USB or Lightning to communicate with an authenticator.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransport const ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransportUSB NS_SWIFT_NAME(usb);

/*! @abstract Indiciates using NFC to communicate with an authenticator.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransport const ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransportNFC NS_SWIFT_NAME(nfc);

/*! @abstract Indicates using Bluetooth, including BLE, to communicate with an authenticator.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
extern ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransport const ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransportBluetooth NS_SWIFT_NAME(bluetooth);

/*! @abstract Returns a list of all transports the device currently supports for communicating with an authenticator.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
NSArray<ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransport> *ASAuthorizationAllSupportedPublicKeyCredentialDescriptorTransports(void) NS_SWIFT_NAME(getter:ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransport.allSupported());

/*! @abstract An object to describe a credential on a security key.
 */
API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface ASAuthorizationSecurityKeyPublicKeyCredentialDescriptor : NSObject <ASAuthorizationPublicKeyCredentialDescriptor>

- (instancetype)initWithCredentialID:(NSData *)credentialID transports:(NSArray<ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransport> *)allowedTransports NS_DESIGNATED_INITIALIZER;

/*! @abstract An array indicating transports for the credential indicated by credentialID.
 */
@property (nonatomic) NSArray<ASAuthorizationSecurityKeyPublicKeyCredentialDescriptorTransport> *transports;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
