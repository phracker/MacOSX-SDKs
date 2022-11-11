/*!
    @header     MFMailComposeViewController
    @abstract   The MFMailComposeViewController class provides an interface for editing and sending email.
    @discussion MFMailComposeViewController is used for implementing a simple interface for users to enter
                and send email.
    @copyright  Copyright 2008-2016 Apple Inc. All rights reserved.
*/
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN


/*!
    @enum       MFMailComposeResult
    @abstract   Composition result sent to the delegate upon user completion.
    @discussion This result will inform of the user's choice in regards to email composition.  If the user
                cancels the composition, <tt>MFMailComposeResultCancelled</tt> will be sent to the delegate.
                Typically <tt>MFMailComposeResultSent</tt> or <tt>MFMailComposeResultSaved</tt> will
                be sent, but <tt>MFMailComposeResultFailed</tt> will be sent in the case of failure.
                </p>Send may only be interpreted as a successful queueing of the message for later sending.
                The actual send will occur when the device is able to send.
    @constant   MFMailComposeResultCancelled   User canceled the composition.
    @constant   MFMailComposeResultSaved       User successfully saved the message.
    @constant   MFMailComposeResultSent        User successfully sent/queued the message.
    @constant   MFMailComposeResultFailed      User's attempt to save or send was unsuccessful.
*/
typedef NS_ENUM(NSInteger, MFMailComposeResult) {
    MFMailComposeResultCancelled,
    MFMailComposeResultSaved,
    MFMailComposeResultSent,
    MFMailComposeResultFailed
} API_AVAILABLE(ios(3.0));

/*!
    @const      MFMailComposeErrorDomain
    @abstract   Error domain for NSError values stemming from the MFMailCompose API.
    @discussion This error domain is used as the domain for all NSError instances stemmming from the
                MFMailCompose API.  Valid error code values are declared in the <tt>MFMailComposeErrorCode</tt>
                space.
*/
extern NSErrorDomain const MFMailComposeErrorDomain API_AVAILABLE(ios(3.0));

/*!
    @enum       MFMailComposeErrorCode
    @abstract   Error codes for NSError values stemming from the MFMailCompose API.
    @discussion These error codes are used as the codes for all NSError instances stemmming from the
                MFMailCompose API.  These are the only valid values for NSError instances with the
                <tt>MFMailComposeErrorDomain</tt> domain.
    @constant   MFMailComposeErrorCodeSaveFailed    Generic error indicating a save failed.
    @constant   MFMailComposeErrorCodeSendFailed    Generic error indicating a send failed.
*/
typedef NS_ENUM(NSInteger, MFMailComposeErrorCode) {
    MFMailComposeErrorCodeSaveFailed,
    MFMailComposeErrorCodeSendFailed
} API_AVAILABLE(ios(3.0));

@protocol MFMailComposeViewControllerDelegate;

/*!
    @class       MFMailComposeViewController
    @abstract    The MFMailComposeViewController class provides an interface for editing and sending email.
    @discussion  The MFMailComposeViewController class manages all user interaction.  The client needs to set the recipient or
                 recipients.  The client may also set the subject and the body of the message.  Attachments may be added, if
                 so desired.  After setup, the client needs to only display the view.</p>The provided delegate will be informed
                 of the user's composition completion and how they chose to complete the operation.<p>Prior to use, clients
                 should verify the user has set up the device for sending email via <tt>+[MFMailComposeViewController canSendMail]</tt>.
*/
API_AVAILABLE(ios(3.0))
@interface MFMailComposeViewController : UINavigationController
{
@private
    id _internal;
}

/*!
    @method     canSendMail
    @abstract   Returns <tt>YES</tt> if the user has set up the device for sending email.
    @discussion The client may continue to set the recipients and content if the return value was <tt>YES</tt>.  If <tt>NO</tt>
                was the result, the client has a couple options.  It may choose to simply notify the user of the inability to
                send mail, or it may issue a "mailto" URL via <tt>-[UIApplication openURL:]</tt>.
*/
+ (BOOL)canSendMail;

/*!
    @property   mailComposeDelegate
    @abstract   This property is the delegate for the MFMailComposeViewControllerDelegate method callbacks.
 */
@property (nonatomic, nullable, weak) id<MFMailComposeViewControllerDelegate> mailComposeDelegate;

/*!
    @method     setSubject:
    @abstract   This method sets the Subject header for the email message.
    @discussion This method will set the Subject header for the email message.  This should be called prior to display.
                Newlines are removed from the parameter.
                </p>After the view has been presented to the user, this method will no longer change the value.
    @param      subject  A NSString specifying the message's Subject header.
*/
- (void)setSubject:(NSString *)subject;

/*!
    @method     setToRecipients:
    @abstract   This method sets the To header for the email message to the specified email addresses.
    @discussion This method will set the To header for the email message.  This should be called prior to display.
                </p>Recipient addresses should be specified as per RFC5322.
                </p>After the view has been presented to the user, this method will no longer change the value.
    @param      toRecipients  A NSArray of NSString instances specifying the email addresses of recipients.
*/
- (void)setToRecipients:(nullable NSArray<NSString *> *)toRecipients;

/*!
    @method     setCcRecipients:
    @abstract   This method sets the CC header for the email message to the specified email addresses.
    @discussion This method will set the CC header for the email message.  This should be called prior to display.
                </p>Recipient addresses should be specified as per RFC5322.
                </p>After the view has been presented to the user, this method will no longer change the value.
    @param      ccRecipients  A NSArray of NSString instances specifying the email addresses of recipients.
 */
- (void)setCcRecipients:(nullable NSArray<NSString *> *)ccRecipients;

/*!
    @method     setBccRecipients:
    @abstract   This method sets the BCC header for the email message to the specified email addresses.
    @discussion This method will set the BCC header for the email message.  This should be called prior to display.
                </p>Recipient addresses should be specified as per RFC5322.
                </p>After the view has been presented to the user, this method will no longer change the value.
    @param      bccRecipients    A NSArray of NSString instances specifying the email addresses of recipients.
 */
- (void)setBccRecipients:(nullable NSArray<NSString *> *)bccRecipients;

/*!
    @method     setMessageBody:isHTML:
    @abstract   This method sets the body of the email message to the specified content.
    @discussion This method will set the body of the email message.  This should be called prior to display.
                The user's signature, if specified, will be added after the body content.
    @param      body A NSString containing the body contents of the email message.
    @param      isHTML  A boolean value indicating if the body argument is to be interpreted as HTML content.
*/
- (void)setMessageBody:(NSString *)body isHTML:(BOOL)isHTML;

/*!
    @method     addAttachmentData:mimeType:fileName:
    @abstract   This method adds the specified attachment to the email message.
    @discussion This method adds the specified attachment to the email message.  This should be called prior to display.
                Attachments will be appended to the end of the message.
    @param      attachment   NSData containing the contents of the attachment.  Must not be <tt>nil</tt>.
    @param      mimeType     NSString specifying the MIME type for the attachment, as specified by the IANA
                                (http://www.iana.org/assignments/media-types/). Must not be <tt>nil</tt>.
    @param      filename     NSString specifying the intended filename for the attachment.  This is displayed below
                                the attachment's icon if the attachment is not decoded when displayed.  Must not be <tt>nil</tt>.
*/
- (void)addAttachmentData:(NSData *)attachment mimeType:(NSString *)mimeType fileName:(NSString *)filename;

/*!
 @method     setPreferredSendingEmailAddress:
 @abstract   This method sets the preferred sending account of the email message.
 @discussion This method will set the sending account of the message to the specified email address if the user has an account with such an address set up. If there is no account with such an address, the default account will be used instead.
 The sending email address should be specified as per RFC5322.
 After the view has been presented to the user, this method will no longer change the value.
 @param      emailAddress  A NSString specifying the preferred email address used to send this message.
 */
- (void)setPreferredSendingEmailAddress:(NSString *)emailAddress API_AVAILABLE(ios(11.0));

@end


/*!
    @protocol    MFMailComposeViewControllerDelegate
    @abstract    Protocol for delegate callbacks to MFMailComposeViewController instances.
    @discussion  This protocol must be implemented for delegates of MFMailComposeViewController instances.  It will
                 be called at various times while the user is composing, sending, saving, or canceling email composition.
*/
@protocol MFMailComposeViewControllerDelegate <NSObject>
@optional
/*!
    @method     mailComposeController:didFinishWithResult:error:
    @abstract   Delegate callback which is called upon user's completion of email composition.
    @discussion This delegate callback will be called when the user completes the email composition.  How the user chose
                to complete this task will be given as one of the parameters to the callback.  Upon this call, the client
                should remove the view associated with the controller, typically by dismissing modally.
    @param      controller   The MFMailComposeViewController instance which is returning the result.
    @param      result       MFMailComposeResult indicating how the user chose to complete the composition process.
    @param      error        NSError indicating the failure reason if failure did occur.  This will be <tt>nil</tt> if
                             result did not indicate failure.
*/
- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(nullable NSError *)error;

@end

NS_ASSUME_NONNULL_END
