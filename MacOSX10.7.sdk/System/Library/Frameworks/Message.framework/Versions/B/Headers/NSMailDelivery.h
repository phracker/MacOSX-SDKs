//
//  NSMailDelivery.h
//  Message
//  
//  Copyright © 1997–2011 Apple Inc. All rights reserved.
//

/*! @header
    <code>NSMailDelivery.h</code> includes the class
    <code>NSMailDelivery</code>, which allows applications to send
    email using Mail.
 
    This API is deprecated. See  <a href="http://developer.apple.com/samplecode/SBSendEmail/index.html">SBSendEmail</a>
    for alternatives.
 */

#import <Foundation/Foundation.h>
#import <Message/MessageExport.h>

#if !__LP64__
// NSMailDelivery is not available in the 64-bit runtime

/*! The <code>NSMailDelivery</code> class enables applications to send
    email messages using Mail.  It includes the ability to send both
    plain text and MIME-encapsulated email messages through
    {@link deliverMessage:headers:format:protocol: deliverMessage:headers:format:protocol:},
    and also provides a simplified interface,
    {@link deliverMessage:subject:to: deliverMessage:subject:to:},
    for delivering basic messages easily.
 
    This API is deprecated. See  <a href="http://developer.apple.com/samplecode/SBSendEmail/index.html">SBSendEmail</a>
    for alternatives.

    @abstract class to enable delivery of an email message using Mail.
 */
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
@interface NSMailDelivery : NSObject {
}

/*!  <code>hasDeliveryClassBeenConfigured</code> returns YES/NO according
    to whether delivery accounts have been configured.
    @abstract Have delivery accounts have been configured?
 */
+ (BOOL)hasDeliveryClassBeenConfigured AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    <code>deliverMessage:headers:format:protocol:</code> is used to deliver
    a message vie email.  It may be MIME-encoded or plain text, but requires
    all header fields to be specified.

    For a simpler (but less flexible) interface, see
    {@link deliverMessage:subject:to: deliverMessage:subject:to:}.

    @abstract Deliver a message.
    @param messageBody
    the actual contents of the message.  If <code>messageFormat</code>
    is <code>NSASCIIMailFormat</code>, any rich text or attachments
    in messageBody will be lost.
    @param messageHeaders
    contains all of the values that will appear in the message header,
    for example, "To", "From", "Subject", etc.  If the value is an array,
    the elements in the array will converted to a comma seperated list of
    values in the message header
    @param messageFormat
    can be either NSASCIIMailFormat or NSMIMEMailFormat
    @param deliveryProtocol
    can be NSSMTPDeliveryProtocol or nil to use the platform's default
    deliveryProtocol (this is the preferred choice).
 */
+ (BOOL)deliverMessage:(NSAttributedString *)messageBody headers:(NSDictionary *)messageHeaders format:(NSString *)messageFormat protocol:(NSString *)deliveryProtocol AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    <code>deliverMessage:subject:to:</code> is a method for delivering basic
    messages via email.  For more complex requirements (such as MIME), see
    {@link deliverMessage:headers:format:protocol: deliverMessage:headers:format:protocol:}.
    @abstract Deliver a message (basic)
    @param messageBody is the plain text contents of the message
    @param messageSubject is the subject of the message
    @param destinationAddress is the recipient's email address, e.g. johndoe\@apple.com
 */
+ (BOOL)deliverMessage:(NSString *)messageBody subject:(NSString *)messageSubject to:(NSString *)destinationAddress AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

@end

/*!
    @const NSMIMEMailFormat
    @const NSASCIIMailFormat
    @abstract String constants used to specify the format in
    the +deliverMessage:headers:format:protocol: method.
*/
MESSAGE_EXPORT NSString *NSMIMEMailFormat AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
MESSAGE_EXPORT NSString *NSASCIIMailFormat AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @const NSSMTPDeliveryProtocol
    @abstract String constants used to specify the delivery protocol in
    the +deliverMessage:headers:format:protocol: method.
*/
MESSAGE_EXPORT NSString *NSSMTPDeliveryProtocol AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*!
    @const NSSendmailDeliveryProtocol
    @abstract Sendmail is no longer a supported sending protocol.  Invoking
    deliveryMessage:headers:format:protocol: with this protocol
    specified will immediately return NO and the message will
    not be delivered.
*/
MESSAGE_EXPORT NSString *NSSendmailDeliveryProtocol AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

#endif
