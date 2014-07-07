/*	NSAppleEventDescriptor.h
	Copyright 1997-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <ApplicationServices/ApplicationServices.h>

@class NSData;

@interface NSAppleEventDescriptor : NSObject <NSCopying> {
  @private
    AEDesc _desc;
    BOOL _hasValidDesc;
}

+ (NSAppleEventDescriptor *)descriptorWithDescriptorType:(DescType)descType data:(NSData *)data;
+ (NSAppleEventDescriptor *)listDescriptor;
+ (NSAppleEventDescriptor *)recordDescriptor;
+ (NSAppleEventDescriptor *)nullDescriptor;

+ (NSAppleEventDescriptor *)appleEventWithEventClass:(AEEventClass)eventClass eventID:(AEEventID)eventID targetDescriptor:(NSAppleEventDescriptor *)addressDescriptor returnID:(AEReturnID)returnID transactionID:(AETransactionID)transactionID;

- (id)initWithDescriptorType:(DescType)descType data:(NSData *)data;
- (id)initListDescriptor;
- (id)initRecordDescriptor;
- (id)init;

- (id)initWithEventClass:(AEEventClass)eventClass eventID:(AEEventID)eventID targetDescriptor:(NSAppleEventDescriptor *)addressDescriptor returnID:(AEReturnID)returnID transactionID:(AETransactionID)transactionID;

- (DescType)descriptorType;
- (NSData *)data;

- (NSAppleEventDescriptor *)coerceToDescriptorType:(DescType)descType;

// API for List and Record descriptors

- (int)numberOfItems;

// API for List descriptors (these also work for Records)

- (void)insertDescriptor:(NSAppleEventDescriptor *)descriptor atIndex:(long int)anIndex;
- (NSAppleEventDescriptor *)descriptorAtIndex:(long int)anIndex;
- (void)removeDecriptorAtIndex:(long int)anIndex;

// API for Record descriptors

- (void)setDescriptor:(NSAppleEventDescriptor *)descriptor forKeyword:(AEKeyword)keyword;
- (NSAppleEventDescriptor *)descriptorForKeyword:(AEKeyword)keyword;
- (void)removeDescriptorWithKeyword:(AEKeyword)keyword;

- (AEKeyword)keywordForDescriptorAtIndex:(long int)anIndex;
    // This API allows one to access all the keys in a record one by one.

// API for AppleEvent descriptors

- (AEEventClass)eventClass;
- (AEEventID)eventID;

- (AEReturnID)returnID;
- (AETransactionID)transactionID;

- (void)setParamDescriptor:(NSAppleEventDescriptor *)descriptor forKeyword:(AEKeyword)keyword;
- (NSAppleEventDescriptor *)paramDescriptorForKeyword:(AEKeyword)keyword;
- (void)removeParamDescriptorWithKeyword:(AEKeyword)keyword;

- (void)setAttributeDescriptor:(NSAppleEventDescriptor *)descriptor forKeyword:(AEKeyword)keyword;
- (NSAppleEventDescriptor *)attributeDescriptorForKeyword:(AEKeyword)keyword;


@end
