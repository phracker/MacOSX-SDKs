/*	NSPropertyList.h
	Copyright (c) 2002-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#include <CoreFoundation/CFPropertyList.h>

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

@class NSData, NSString;

enum {
    NSPropertyListImmutable = kCFPropertyListImmutable,
    NSPropertyListMutableContainers = kCFPropertyListMutableContainers,
    NSPropertyListMutableContainersAndLeaves = kCFPropertyListMutableContainersAndLeaves
};
typedef NSUInteger NSPropertyListMutabilityOptions;

enum {
    NSPropertyListOpenStepFormat = kCFPropertyListOpenStepFormat,
    NSPropertyListXMLFormat_v1_0 = kCFPropertyListXMLFormat_v1_0,
    NSPropertyListBinaryFormat_v1_0 = kCFPropertyListBinaryFormat_v1_0
};
typedef NSUInteger NSPropertyListFormat;

@interface NSPropertyListSerialization : NSObject {
    void *reserved[6];
}

+ (BOOL)propertyList:(id)plist isValidForFormat:(NSPropertyListFormat)format;
+ (NSData *)dataFromPropertyList:(id)plist format:(NSPropertyListFormat)format errorDescription:(NSString **)errorString;
+ (id)propertyListFromData:(NSData *)data mutabilityOption:(NSPropertyListMutabilityOptions)opt format:(NSPropertyListFormat *)format errorDescription:(NSString **)errorString;

@end

#endif

