#import <MessageUI/MFMessageComposeViewController.h>


NS_ASSUME_NONNULL_BEGIN

@interface MFMessageComposeViewController (UPI)

/// @method     setUPIVerificationCodeSendCompletion:
/// @abstract   Configures the instance of `MFMessageComposeViewController` for UPI device validation
/// @discussion If the host app has the `com.apple.developer.upi-device-validation` managed entitlement, this
///             will configure the instance of `MFMessageComposeViewController` with non-editable recipients
///             and body fields. This API is only functional on devices with SMS capability and is only
///             compatible with non-iMessagable recipients. The send completion handler will be invoked with
///             `YES` only once the SMS was successfully transmitted to the sender's cellular carrier. If the
///             SMS failed to send, the completion handler will be invoked with `NO`.
///
///             The completion handler will be in invoked on the main thread. It will only be invoked after
///             `MFMessageComposeViewController` delegate's `-messageComposeViewController:didFinishWithResult:`
///             method was called. That method is called in response to user action (the user hit cancel or
///             send); the send completion handler is called with the transmission result of the message. It
///             will not be called at all if `-messageComposeViewController:didFinishWithResult:` was not
///             called with `MessageComposeResultSent`.
///
///             Because it can take some time to send a message, the completion handler could be invoked
///             after the `MFMessageComposeViewController` instance is deallocated.
/// @param      completion      A block invoked with a BOOL of whether the message was actually sent.
- (void)setUPIVerificationCodeSendCompletion:(void (^)(BOOL didSend))completion NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(ios(17.0));

@end

NS_ASSUME_NONNULL_END
