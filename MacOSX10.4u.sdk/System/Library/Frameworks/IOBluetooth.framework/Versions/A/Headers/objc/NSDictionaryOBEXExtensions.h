/*
	Contains:	

	Version:	xxx put version here xxx

	Copyright:	(C) 2002-2004 by Apple Computer, Inc., all rights reserved.
*/

#import <IOKit/IOKitLib.h>
#import <stdlib.h>

#import <IOBluetooth/OBEX.h>

//===========================================================================================================================
//	NSMutableDictionary
//===========================================================================================================================

@interface NSMutableDictionary (NSDictionaryOBEXExtensions)

/* creation */

+(NSMutableDictionary*)dictionaryWithOBEXHeadersData:(const void*)inHeadersData headersDataSize:(size_t)inDataSize;
+(NSMutableDictionary*)dictionaryWithOBEXHeadersData:(NSData*)inHeadersData;

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

// Deprecated in favor of dictionaryWithOBEXHeadersData: above.

+(NSMutableDictionary*)withOBEXHeadersData:(const void*)inHeadersData headersDataSize:(size_t)inDataSize;


@end
