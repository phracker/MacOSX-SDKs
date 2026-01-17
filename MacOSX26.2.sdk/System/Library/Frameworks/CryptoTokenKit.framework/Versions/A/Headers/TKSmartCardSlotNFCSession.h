//
//  Copyright © 2024 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// NFC session that's related to NFC smart card slot which was created.
/// @discussion Lifetime of this session object is tied to the NFC smart card slot lifetime
///             and once the NFC slot disappears (eg. after a user cancellation, calling end session, or an NFC timeout)
///             the functions will start to fail and return `TKErrorCodeObjectNotFound` error.
API_AVAILABLE(ios(26.0), macCatalyst(26.0), visionos(26.0)) API_UNAVAILABLE(macos, watchos, tvos)
NS_SWIFT_SENDABLE
@interface TKSmartCardSlotNFCSession : NSObject

/// Smart card slot name of the NFC slot that was created together with this session.
@property (nullable, nonatomic, copy, readonly) NSString *slotName;

/// Clients should only receive the session
- (instancetype)init NS_UNAVAILABLE;

/// Updates the message of the system-presented NFC UI.
/// @param message Message that should be displayed
/// @param error Specific error describing why the operation failed
/// @return Returns `YES` if the alert message was updated, `NO` if an error occured.
- (BOOL)updateWithMessage:(NSString *)message error:(NSError * _Nullable __autoreleasing *)error
NS_SWIFT_NAME(update(message:));

/// Ends the NFC slot session and dismisses the system-presented NFC UI (if present).
- (void)endSession;

@end

NS_ASSUME_NONNULL_END
