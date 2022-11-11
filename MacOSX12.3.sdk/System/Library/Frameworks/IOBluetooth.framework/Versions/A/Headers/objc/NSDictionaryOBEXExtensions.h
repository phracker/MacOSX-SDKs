/*
	Contains:	OBEX Header construction routines.
	Copyright:	(C) 2010 by Apple, Inc., all rights reserved.
*/

#import <IOKit/IOKitLib.h>
#import <stdlib.h>

#import <IOBluetooth/OBEX.h>

//===========================================================================================================================
//	NSMutableDictionary
//===========================================================================================================================

API_UNAVAILABLE(ios, watchos, tvos)
@interface NSMutableDictionary (NSDictionaryOBEXExtensions)

/* creation */

+(instancetype)dictionaryWithOBEXHeadersData:(const void*)inHeadersData headersDataSize:(size_t)inDataSize;
+(instancetype)dictionaryWithOBEXHeadersData:(NSData*)inHeadersData;

/* Utilities */

-(NSMutableData *)getHeaderBytes;

/* Adding headers to the dictionary */

-(OBEXError)addTargetHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;
-(OBEXError)addHTTPHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;
-(OBEXError)addBodyHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength endOfBody:(BOOL)isEndOfBody;
-(OBEXError)addWhoHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;
-(OBEXError)addConnectionIDHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;
-(OBEXError)addApplicationParameterHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;
-(OBEXError)addByteSequenceHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;
-(OBEXError)addObjectClassHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;
-(OBEXError)addAuthorizationChallengeHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;
-(OBEXError)addAuthorizationResponseHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;
-(OBEXError)addTimeISOHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;
-(OBEXError)addTypeHeader:(NSString*)type;
-(OBEXError)addLengthHeader:(uint32_t)length;
-(OBEXError)addTime4ByteHeader:(uint32_t)time4Byte;
-(OBEXError)addCountHeader:(uint32_t)inCount;
-(OBEXError)addDescriptionHeader:(NSString*)inDescriptionString;
-(OBEXError)addNameHeader:(NSString*)inNameString;
-(OBEXError)addUserDefinedHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;

-(OBEXError)addImageHandleHeader:(NSString*)type;
-(OBEXError)addImageDescriptorHeader:(const void*)inHeaderData	length:(uint32_t)inHeaderDataLength;


+(instancetype)withOBEXHeadersData:(const void*)inHeadersData headersDataSize:(size_t)inDataSize API_DEPRECATED("No longer supported", macos(10.2, 10.7)) API_UNAVAILABLE(ios, watchos, tvos);


@end
