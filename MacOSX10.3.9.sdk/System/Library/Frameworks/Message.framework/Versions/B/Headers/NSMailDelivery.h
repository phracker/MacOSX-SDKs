/*
        NSMailDelivery.h
        Message Framework
        Copyright (c) 1997, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <Message/MessageExport.h>


@interface NSMailDelivery : NSObject
{
}

+ (BOOL)hasDeliveryClassBeenConfigured;
    // Returns YES if delivery accounts have been configured or not.  

+ (BOOL)deliverMessage: (NSAttributedString *)messageBody headers: (NSDictionary *)messageHeaders format: (NSString *)messageFormat protocol: (NSString *)deliveryProtocol;
    //
    // messageBody is the actual contents of the message.  If messageFormat is NSASCIIMailFormat,
    //	any rich text or attachments in messageBody will be lost
    //
    // messageHeaders contains all of the values that will appear in the message header,
    //	for example, "To", "From", "Subject", etc.  If the value is an array, the elements
    //	in the array will converted to a comma seperated list of values in the message header
    //
    // messageFormat can be either NSASCIIMailFormat or NSMIMEMailFormat
    //
    // deliveryProtocol can be NSSMTPDeliveryProtocol
    //  or nil to use the platform's default deliveryProtocol (this is the preferred choice).
    //


+ (BOOL)deliverMessage:(NSString *)messageBody subject:(NSString *)messageSubject to:(NSString *)destinationAddress;
    //
    // messageBody is the plain text contents of the message
    //
    // messageSubject is the subject of the message
    //
    // destinationAddress is the recipient's email address, e.g. johndoe@apple.com
    //


@end

MESSAGE_EXPORT NSString *NSMIMEMailFormat;
MESSAGE_EXPORT NSString *NSASCIIMailFormat;
    // String constants used to specify the format in the
    // +deliverMessage:headers:format:protocol: method.

MESSAGE_EXPORT NSString *NSSMTPDeliveryProtocol;
    // String constants used to specify the delivery protocol
    // in the +deliverMessage:headers:format:protocol: method.


MESSAGE_EXPORT NSString *NSSendmailDeliveryProtocol;
    // Sendmail is no longer a supported sending protocol.  Invoking
    // deliveryMessage:headers:format:protocol: with this protocol
    // specified will immediately return NO and the message will
    // not be delivered.  

