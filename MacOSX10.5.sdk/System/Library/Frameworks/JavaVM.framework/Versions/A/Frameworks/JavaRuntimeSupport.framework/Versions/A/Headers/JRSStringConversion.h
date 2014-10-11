//
//  JRSStringConversion.h
//  Copyright 2008 Apple Inc. All rights reserved.
//

#include <CoreFoundation/CoreFoundation.h>

typedef enum _JRSConvertBytesStatus {
	JRS_CONVERT_OK,
	JRS_CONVERT_BUFFER_TOO_SMALL,
	JRS_CONVERT_INVALID_INPUT,
	JRS_CONVERT_UNKNOWN_ERR
} JRSConvertBytesStatus;

JRSConvertBytesStatus JRSConvertBytesToUnicode(uint8_t *bytes, CFIndex numBytes, CFIndex *usedByteLen, UniChar *unichars, CFIndex maxChars, CFIndex *usedCharLen, Boolean allowSubstitution);
