//
//  AVB17221AECPMessage.h
//  AudioVideoBridging
//
//  Copyright (c) 2011-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if AVB_TAPI
#import "AVBConstants.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@class AVBMACAddress;

/*!
	@class		AVB17221AECPMessage
	@abstract	AVB17221AECPMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol message.
	@discussion	AVB17221AECPMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol (AECP) message.
				This class is a abstract class providing the support for the common format shared between the different
				AECP message types.
 */
API_AVAILABLE(macos(10.8))
@interface AVB17221AECPMessage : NSObject <NSCopying>

/*!
	@property	messageType
	@abstract	The message_type field of the AECP message.
 */
@property (assign) AVB17221AECPMessageType messageType;
/*!
	@property	status
	@abstract	The status field of the AECP message.
 */
@property (assign) AVB17221AECPStatusCode status;
/*!
	@property	targetEntityID
	@abstract	The target_entity_id field of the AECP message.
 */
@property (assign) uint64_t targetEntityID API_AVAILABLE(macos(10.9));
/*!
	@property	controllerEntityID
	@abstract	The controller_entity_id field of the AECP message.
 */
@property (assign) uint64_t controllerEntityID API_AVAILABLE(macos(10.9));
/*!
	@property	sequenceID
	@abstract	The sequence_id field of the AECP message.
 */
@property (assign) uint16_t sequenceID;

/*!
	@property	sourceMAC
	@abstract	The source_mac field of the AECP message.
 */
@property (copy) AVBMACAddress *sourceMAC;

/*!
	@method		errorForStatusCode:
	@abstract	This method returns an NSError filled out with an appropriate description for the passed in status code.
	@result		An NSError instance within the AVBErrorDomain with the status code and an appropriate description.
				Will return nil if status code is success or in progress.
 */
+ (nullable NSError *)errorForStatusCode:(AVB17221AECPStatusCode)statusCode;

/*!
	@method		errorForStatusCode
	@abstract	This method returns an NSError filled out with an appropriate description for the message's status code.
	@result		An NSError instance within the AVBErrorDomain with the status code and an appropriate description.
				Will return nil if status code is success or in progress.
 */
- (nullable NSError *)errorForStatusCode;

@end






/*!
 @class		AVB17221AECPAEMMessage
 @abstract	AVB17221AECPAEMMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol, AVDECC Entity Model message.
 @discussion	AVB17221AECPAEMMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol (AECP), AVDECC Entity Model (AEM) message.
 This class is a concrete subclass of AVB17221AECPMessage which provides support for the AEM messages.
 */
API_AVAILABLE(macos(10.8))
@interface AVB17221AECPAEMMessage : AVB17221AECPMessage
{
@private
	uint16_t rawCommandType;
}

/*!
	@property	commandType
	@abstract	The command_type field of the AECP AEM message.
 */
@property (assign) AVB17221AEMCommandType commandType;
/*!
	@property	unsolicited
	@abstract	The u field of the AECP AEM message.
 */
@property (assign, getter=isUnsolicited) BOOL unsolicited;
/*!
 @property	controllerRequest
 @abstract	The cr field of the AECP AEM message.
 */
@property (assign, getter=isControllerRequest) BOOL controllerRequest API_AVAILABLE(macos(10.9));

/*!
	@property	commandSpecificData
	@abstract	The command_specific_data field of the AECP AEM message.
 */
@property (copy, nullable) NSData *commandSpecificData;

/*!
	@method		commandMessage
	@abstract	This method returns an AVB17221AECPAEMMessage instance setup as an AEM command.
	@result		An AVB17221AECPAEMMessage instance pre-setup as an AEM command.
 */
+ (AVB17221AECPAEMMessage *)commandMessage;

/*!
	@method		responseMessage
	@abstract	This method returns an AVB17221AECPAEMMessage instance setup as an AEM response.
	@result		An AVB17221AECPAEMMessage instance pre-setup as an AEM response.
 */
+ (AVB17221AECPAEMMessage *)responseMessage;

@end



@class AVB17221AECPAddressAccessTLV;


/*!
	@class		AVB17221AECPAddressAccessMessage
	@abstract	AVB17221AECPAddressAccessMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol, Address Access message.
	@discussion	AVB17221AECPAddressAccessMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol (AECP), Address Access message.
				This class is a concrete subclass of AVB17221AECPMessage which provides support for the Address Access messages.
 */
API_AVAILABLE(macos(10.8))
@interface AVB17221AECPAddressAccessMessage : AVB17221AECPMessage

/*!
	@property	tlvs
	@abstract	An array of AVB17221AECPAddressAccessTLV objects representing the tlv_data field of the AECP Address Access message.
 */
@property (copy, nullable) NSArray <AVB17221AECPAddressAccessTLV *>*tlvs;

/*!
	@method		commandMessage
	@abstract	This method returns an AVB17221AECPAddressAccessMessage instance setup as an Address Access command.
	@result		An AVB17221AECPAddressAccessMessage instance pre-setup as an Address Access command.
 */
+ (AVB17221AECPAddressAccessMessage *)commandMessage;

/*!
	@method		responseMessage
	@abstract	This method returns an AVB17221AECPAEMMessage instance setup as an Address Access response.
	@result		An AVB17221AECPAddressAccessMessage instance pre-setup as an Address Access response.
 */
+ (AVB17221AECPAddressAccessMessage *)responseMessage;

@end






/*!
	@class		AVB17221AECPAddressAccessTLV
	@abstract	AVB17221AECPAddressAccessTLV encapsulates a TLV from an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol, Address Access message.
	@discussion	AVB17221AECPAddressAccessTLV encapsulates a TLV from an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol (AECP), Address Access message.
 */
API_AVAILABLE(macos(10.8))
@interface AVB17221AECPAddressAccessTLV : NSObject

/*!
	@property	mode
	@abstract	The mode field of the Address Access TLV.
 */
@property (assign) AVB17221AECPAddressAccessTLVMode mode;
/*!
	@property	address
	@abstract	The address field of the Address Access TLV.
 */
@property (assign) uint64_t address;
/*!
	@property	memoryData
	@abstract	The memory_data field of the Address Access TLV.
 */
@property (copy, nullable) NSData *memoryData;

@end






/*!
	@class		AVB17221AECPAVCMessage
	@abstract	AVB17221AECPAVCMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol, Legacy AV/C message.
	@discussion	AVB17221AECPAVCMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol (AECP), Legacy AV/C message.
				This class is a concrete subclass of AVB17221AECPMessage which provides support for the Legacy AV/C messages.
 */
API_AVAILABLE(macos(10.8))
@interface AVB17221AECPAVCMessage : AVB17221AECPMessage

/*!
	@property	commandResponse
	@abstract	The avc_command_response field of the AECP AEM message.
 */
@property (copy, nullable) NSData *commandResponse;

@end






/*!
	@class		AVB17221AECPVendorMessage
	@abstract	AVB17221AECPVendorMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol, Vendor Unique message.
	@discussion	AVB17221AECPVendorMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol (AECP), Vendor Unique message.
				This class is a concrete subclass of AVB17221AECPMessage which provides support for the AEM messages.
 */
API_AVAILABLE(macos(10.8))
@interface AVB17221AECPVendorMessage : AVB17221AECPMessage

/*!
	@property	protocolID
	@abstract	The protocol_id field of the AECP Vendor Unique message.
 */
@property (assign) uint64_t protocolID;
/*!
	@property	protocolSpecificData
	@abstract	The protocol_specific_data field of the AECP Vendor Unique message.
 */
@property (copy, nullable) NSData *protocolSpecificData;

@end

NS_ASSUME_NONNULL_END

