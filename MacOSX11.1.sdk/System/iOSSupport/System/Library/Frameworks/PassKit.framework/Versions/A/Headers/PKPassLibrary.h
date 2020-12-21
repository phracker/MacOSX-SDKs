//
//  PKPassLibrary.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//
//  Threading contract: no concurrent usage.

#import <Foundation/Foundation.h>
#import <PassKit/PKPass.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PKPassLibraryAddPassesStatus) {
    PKPassLibraryDidAddPasses,
    PKPassLibraryShouldReviewPasses,
    PKPassLibraryDidCancelAddPasses,
} API_AVAILABLE(ios(7.0), watchos(3.0));


typedef NS_ENUM(NSUInteger, PKAutomaticPassPresentationSuppressionResult) {
    PKAutomaticPassPresentationSuppressionResultNotSupported = 0,   // Suppression is not supported for this device
    PKAutomaticPassPresentationSuppressionResultAlreadyPresenting,  // Passes are already being presented and cannot be suppressed
    PKAutomaticPassPresentationSuppressionResultDenied,             // Suppression was denied due to lack of entitlement
    PKAutomaticPassPresentationSuppressionResultCancelled,          // Suppression was cancelled before the response handler was fired
    PKAutomaticPassPresentationSuppressionResultSuccess             // Suppression of automatic pass presentation was successful
} __WATCHOS_PROHIBITED API_AVAILABLE(ios(9.0));

typedef NSUInteger PKSuppressionRequestToken;

API_AVAILABLE(ios(6.0), watchos(3.0))
@interface PKPassLibrary : NSObject

// The library is not available on iPad in 6.0.
+ (BOOL)isPassLibraryAvailable API_AVAILABLE(ios(6.0), watchos(3.0));

// These methods may be used to temporarily disable the automatic presentation of passes when a device encounters a contactless field.
// Use of these methods require an entitlement. Otherwise, requesting will always return a PKAutomaticPassPresentationSuppressionResultDenied as the result.
+ (PKSuppressionRequestToken)requestAutomaticPassPresentationSuppressionWithResponseHandler:(void(^)(PKAutomaticPassPresentationSuppressionResult result))responseHandler API_AVAILABLE(ios(9.0)) __WATCHOS_PROHIBITED NS_EXTENSION_UNAVAILABLE("Not available to extensions");
+ (void)endAutomaticPassPresentationSuppressionWithRequestToken:(PKSuppressionRequestToken)requestToken API_AVAILABLE(ios(9.0)) __WATCHOS_PROHIBITED NS_EXTENSION_UNAVAILABLE("Not available to extensions");
+ (BOOL)isSuppressingAutomaticPassPresentation API_AVAILABLE(ios(9.0)) __WATCHOS_PROHIBITED NS_EXTENSION_UNAVAILABLE("Not available to extensions");

// If device supports adding payment passes, this method will return YES. Otherwise, NO will be returned.
+ (BOOL)isPaymentPassActivationAvailable API_DEPRECATED("Use -[PKPassLibrary isPaymentPassActivationAvailable] instead", ios(8.0, 9.0));

// If this pass library supports activating payment passes, this method will return YES. Otherwise, NO will be returned.
- (BOOL)isPaymentPassActivationAvailable API_DEPRECATED("Use -[PKPassLibrary isSecureElementPassActivationAvailable] instead", ios(9.0, API_TO_BE_DEPRECATED));

@property (nonatomic, assign, readonly, getter=isSecureElementPassActivationAvailable) BOOL secureElementPassActivationAvailable API_AVAILABLE(ios(13.4));

// These return only local passes the process is entitled to access.
- (NSArray<PKPass *> *)passes;
- (nullable PKPass *)passWithPassTypeIdentifier:(NSString *)identifier serialNumber:(NSString *)serialNumber;
- (NSArray<PKPass *> *)passesOfType:(PKPassType)passType API_AVAILABLE(ios(8.0), watchos(3.0));

// This returns the remote payment passes from attached devices
- (NSArray<PKPaymentPass *> *)remotePaymentPasses API_DEPRECATED("Use -[PKPassLibrary remoteSecureElementPasses] instead", ios(9.0, API_TO_BE_DEPRECATED));

@property (nonatomic, copy, readonly) NSArray<PKSecureElementPass *> *remoteSecureElementPasses API_AVAILABLE(ios(13.4));

- (void)removePass:(PKPass *)pass;

// This returns YES even if the process is not entitled to access the pass in the library.  An app like Mail is not entitled to get
// pass from the library, but it should avoid presenting UI for adding an email attachment pass that is already in the library.
- (BOOL)containsPass:(PKPass *)pass;

// This will fail if a pass with matching identifier and serial number is not already present in the library, or if the process
// is not entitled to access the pass. To add a completely new pass, use PKAddPassesViewController.
- (BOOL)replacePassWithPass:(PKPass *)pass;

// The user will be prompted to grant permission for the calling process to add passes to the Pass Library. The user may respond
// by allowing the passes to be added, or requesting to review the passes. The selection will be returned in the completionHandler
// as a PKPassLibraryAddPassesStatus. If PKPassLibraryPassesPresentReview is returned, you must present a PKAddPassesViewController
// initialized with the passes so that the user may review and add the passes manually. The completion handler for this method is
// called on an arbitrary queue - dispatch to the main queue if you're presenting UI.
- (void)addPasses:(NSArray<PKPass *> *)passes withCompletionHandler:(nullable void(^)(PKPassLibraryAddPassesStatus status))completion API_AVAILABLE(ios(7.0), watchos(3.0));

// Opens the card setup flow (in Wallet on iPhone, Settings on iPad). Use this to direct a user to card setup directly from your app.
- (void)openPaymentSetup API_AVAILABLE(ios(8.3)) __WATCHOS_PROHIBITED;

// Presents the pass for use above the current application. The pass must already be in the pass library for this to have effect.
- (void)presentPaymentPass:(PKPaymentPass *)pass API_DEPRECATED("Use -[PKPassLibrary presentSecureElementPass:] instead", ios(10.0, API_TO_BE_DEPRECATED)) __WATCHOS_PROHIBITED;
- (void)presentSecureElementPass:(PKSecureElementPass *)pass API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos);


// Returns YES if either the current device or an attached device both supports adding payment passes and does not already contain
// a payment pass with the supplied primary account identifier.
- (BOOL)canAddPaymentPassWithPrimaryAccountIdentifier:(NSString *)primaryAccountIdentifier API_DEPRECATED("Use -[PKPassLibrary canAddSecureElementPassWithPrimaryAccountIdentifier] instead", ios(9.0, API_TO_BE_DEPRECATED));
- (BOOL)canAddSecureElementPassWithPrimaryAccountIdentifier:(NSString *)primaryAccountIdentifier NS_SWIFT_NAME(canAddSecureElementPass(primaryAccountIdentifier:)) API_AVAILABLE(ios(13.4));

// If the library can add Felica passes, this method will return YES. Otherwise, NO will be returned.
- (BOOL)canAddFelicaPass API_AVAILABLE(ios(10.1), watchos(3.1));

// These methods may be utilized to activate a payment pass that is provisioned but currently in the inactive state, by providing
// either a cryptographic OTP, or an activation code.
- (void)activatePaymentPass:(PKPaymentPass *)paymentPass withActivationData:(NSData *)activationData completion:(nullable void(^)(BOOL success, NSError *error))completion API_DEPRECATED("Use activateSecureElementPass:withActivationData:completion: instead", ios(8.0, API_TO_BE_DEPRECATED));
- (void)activatePaymentPass:(PKPaymentPass *)paymentPass withActivationCode:(NSString *)activationCode completion:(nullable void(^)(BOOL success, NSError *error))completion API_DEPRECATED("Use activatePaymentPass:withActivationData:completion: instead", ios(8.0, 9.0)) __WATCHOS_PROHIBITED;
- (void)activateSecureElementPass:(PKSecureElementPass *)secureElementPass withActivationData:(NSData *)activationData completion:(nullable void(^)(BOOL success, NSError * _Nullable error))completion NS_SWIFT_NAME(activate(_:activationData:completion:)) API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos);

// Sign a payload using the pass
- (void)signData:(NSData *)signData withSecureElementPass:(PKSecureElementPass *)secureElementPass completion:(void(^)(NSData * _Nullable signedData, NSData * _Nullable signature, NSError * _Nullable error))completion NS_SWIFT_NAME(sign(_:using:completion:)) API_AVAILABLE(ios(13.4), watchos(6.2));
@end

// This notification is issued by a library instance, with that instance as the sender.  If there are no instantiated library objects,
// no notifications. There are no guarantees about what thread or queue these come in on.
typedef NSString * PKPassLibraryNotificationName NS_EXTENSIBLE_STRING_ENUM;
extern PKPassLibraryNotificationName const PKPassLibraryDidChangeNotification API_AVAILABLE(ios(6.0), watchos(3.0));
extern PKPassLibraryNotificationName const PKPassLibraryRemotePaymentPassesDidChangeNotification API_AVAILABLE(ios(9.0), watchos(3.0));

// Entries in user info dictionary for PKPassLibraryDidChangeNotification.
// - PKPassLibraryAddedPassesUserInfoKey is the key for an array of passes
// - PKPassLibraryReplacementPassesUserInfoKey is the key for an array of passes
// - PKPassLibraryRemovedPassInfosUserInfoKey is the key for an array of dictionaries, each of which has keys
//   PKPassLibraryPassTypeIdentifierUserInfoKey and PKPassLibrarySerialNumberUserInfoKey mapping to strings.
typedef NSString * PKPassLibraryNotificationKey NS_STRING_ENUM;
extern PKPassLibraryNotificationKey const PKPassLibraryAddedPassesUserInfoKey API_AVAILABLE(ios(6.0), watchos(3.0));
extern PKPassLibraryNotificationKey const PKPassLibraryReplacementPassesUserInfoKey API_AVAILABLE(ios(6.0), watchos(3.0));
extern PKPassLibraryNotificationKey const PKPassLibraryRemovedPassInfosUserInfoKey API_AVAILABLE(ios(6.0), watchos(3.0));

extern PKPassLibraryNotificationKey const PKPassLibraryPassTypeIdentifierUserInfoKey API_AVAILABLE(ios(6.0), watchos(3.0));
extern PKPassLibraryNotificationKey const PKPassLibrarySerialNumberUserInfoKey API_AVAILABLE(ios(6.0), watchos(3.0));

NS_ASSUME_NONNULL_END
