/*
	NSAppleEventDescriptor.h
	Copyright (c) 1997-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <ApplicationServices/ApplicationServices.h>

@class NSData;

@interface NSAppleEventDescriptor : NSObject<NSCopying> {
    @private
    AEDesc _desc;
    BOOL _hasValidDesc;
    char _padding[3];
}

// Create an autoreleased NSAppleEventDescriptor whose AEDesc type is typeNull.
+ (NSAppleEventDescriptor *)nullDescriptor;

// Given some data, and a four-character type code, create and return an autoreleased NSAppleEventDescriptor that contains that data, with that type.
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (NSAppleEventDescriptor *)descriptorWithDescriptorType:(DescType)descriptorType bytes:(const void *)bytes length:(unsigned int)byteCount;
#endif
+ (NSAppleEventDescriptor *)descriptorWithDescriptorType:(DescType)descriptorType data:(NSData *)data;

// Given a value, create and return an autoreleased NSAppleEventDescriptor that contains that value, with an appropriate type (typeBoolean, typeEnumerated, typeSInt32, or typeType, respectively).
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (NSAppleEventDescriptor *)descriptorWithBoolean:(Boolean)boolean;
+ (NSAppleEventDescriptor *)descriptorWithEnumCode:(OSType)enumerator;
+ (NSAppleEventDescriptor *)descriptorWithInt32:(SInt32)signedInt;
+ (NSAppleEventDescriptor *)descriptorWithTypeCode:(OSType)typeCode;
#endif

// Given a string, create and return an autoreleased NSAppleEventDescriptor that contains that string, as typeUnicodeText.
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (NSAppleEventDescriptor *)descriptorWithString:(NSString *)string;
#endif

// Create and return an autoreleased event, list, or record NSAppleEventDescriptor, respectively.
+ (NSAppleEventDescriptor *)appleEventWithEventClass:(AEEventClass)eventClass eventID:(AEEventID)eventID targetDescriptor:(NSAppleEventDescriptor *)targetDescriptor returnID:(AEReturnID)returnID transactionID:(AETransactionID)transactionID;
+ (NSAppleEventDescriptor *)listDescriptor;
+ (NSAppleEventDescriptor *)recordDescriptor;

// The designated initializer.  The initialized object takes ownership of the passed-in AEDesc, and will call AEDisposeDesc() on it at deallocation time.
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (id)initWithAEDescNoCopy:(const AEDesc *)aeDesc;
#endif

// Other initializers.
- (id)initWithDescriptorType:(DescType)descriptorType bytes:(const void *)bytes length:(unsigned int)byteCount;
- (id)initWithDescriptorType:(DescType)descriptorType data:(NSData *)data;
- (id)initWithEventClass:(AEEventClass)eventClass eventID:(AEEventID)eventID targetDescriptor:(NSAppleEventDescriptor *)targetDescriptor returnID:(AEReturnID)returnID transactionID:(AETransactionID)transactionID;
- (id)initListDescriptor;
- (id)initRecordDescriptor;

// Return a pointer to the AEDesc that is encapsulated by the object.
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (const AEDesc *)aeDesc;
#endif

// Get the four-character type code or the data from a fully-initialized descriptor.
- (DescType)descriptorType;
- (NSData *)data;

// Return the contents of a descriptor, after coercing the descriptor's contents to typeBoolean, typeEnumerated, typeSInt32, or typeType, respectively.
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (Boolean)booleanValue;
- (OSType)enumCodeValue;
- (SInt32)int32Value;
- (OSType)typeCodeValue;
#endif

// Return the contents of a descriptor as a string, after coercing the descriptor's contents to typeUnicodeText.
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (NSString *)stringValue;
#endif

// Accessors for an event descriptor.
- (AEEventClass)eventClass;
- (AEEventID)eventID;
- (AEReturnID)returnID;
- (AETransactionID)transactionID;

// Set, retrieve, or remove parameter descriptors inside an event descriptor.
- (void)setParamDescriptor:(NSAppleEventDescriptor *)descriptor forKeyword:(AEKeyword)keyword;
- (NSAppleEventDescriptor *)paramDescriptorForKeyword:(AEKeyword)keyword;
- (void)removeParamDescriptorWithKeyword:(AEKeyword)keyword;

// Set or retrieve attribute descriptors inside an event descriptor.
- (void)setAttributeDescriptor:(NSAppleEventDescriptor *)descriptor forKeyword:(AEKeyword)keyword;
- (NSAppleEventDescriptor *)attributeDescriptorForKeyword:(AEKeyword)keyword;

// Return the number of items inside a list or record descriptor.
- (int)numberOfItems;

// Set, retrieve, or remove indexed descriptors inside a list or record descriptor.
- (void)insertDescriptor:(NSAppleEventDescriptor *)descriptor atIndex:(long int)index;
- (NSAppleEventDescriptor *)descriptorAtIndex:(long int)index;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (void)removeDescriptorAtIndex:(long int)index;
#else
- (void)removeDecriptorAtIndex:(long int)index;
#endif

// Set, retrieve, or remove keyed descriptors inside a record descriptor.
- (void)setDescriptor:(NSAppleEventDescriptor *)descriptor forKeyword:(AEKeyword)keyword;
- (NSAppleEventDescriptor *)descriptorForKeyword:(AEKeyword)keyword;
- (void)removeDescriptorWithKeyword:(AEKeyword)keyword;

// Return the keyword associated with an indexed descriptor inside a record descriptor.
- (AEKeyword)keywordForDescriptorAtIndex:(long int)index;

// Create and return a descriptor of the requested type, doing a coercion if that's appropriate and possible.
- (NSAppleEventDescriptor *)coerceToDescriptorType:(DescType)descriptorType;

@end
