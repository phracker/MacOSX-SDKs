/*
	NSAppleEventDescriptor.h
	Copyright (c) 1997-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <ApplicationServices/ApplicationServices.h>

@class NSData;

@interface NSAppleEventDescriptor : NSObject<NSCopying, NSSecureCoding> {
    @private
    AEDesc _desc;
    BOOL _hasValidDesc;
    char _padding[3];
}

// Create an autoreleased NSAppleEventDescriptor whose AEDesc type is typeNull.
+ (NSAppleEventDescriptor *)nullDescriptor;

// Given some data, and a four-character type code, create and return an autoreleased NSAppleEventDescriptor that contains that data, with that type.
+ (NSAppleEventDescriptor *)descriptorWithDescriptorType:(DescType)descriptorType bytes:(const void *)bytes length:(NSUInteger)byteCount;
+ (NSAppleEventDescriptor *)descriptorWithDescriptorType:(DescType)descriptorType data:(NSData *)data;

// Given a value, create and return an autoreleased NSAppleEventDescriptor that contains that value, with an appropriate type (typeBoolean, typeEnumerated, typeSInt32, or typeType, respectively).
+ (NSAppleEventDescriptor *)descriptorWithBoolean:(Boolean)boolean;
+ (NSAppleEventDescriptor *)descriptorWithEnumCode:(OSType)enumerator;
+ (NSAppleEventDescriptor *)descriptorWithInt32:(SInt32)signedInt;
+ (NSAppleEventDescriptor *)descriptorWithTypeCode:(OSType)typeCode;

// Given a string, create and return an autoreleased NSAppleEventDescriptor that contains that string, as typeUnicodeText.
+ (NSAppleEventDescriptor *)descriptorWithString:(NSString *)string;

// Create and return an autoreleased event, list, or record NSAppleEventDescriptor, respectively.
+ (NSAppleEventDescriptor *)appleEventWithEventClass:(AEEventClass)eventClass eventID:(AEEventID)eventID targetDescriptor:(NSAppleEventDescriptor *)targetDescriptor returnID:(AEReturnID)returnID transactionID:(AETransactionID)transactionID;
+ (NSAppleEventDescriptor *)listDescriptor;
+ (NSAppleEventDescriptor *)recordDescriptor;

// The designated initializer.  The initialized object takes ownership of the passed-in AEDesc, and will call AEDisposeDesc() on it at deallocation time.
- (id)initWithAEDescNoCopy:(const AEDesc *)aeDesc;

// Other initializers.
- (id)initWithDescriptorType:(DescType)descriptorType bytes:(const void *)bytes length:(NSUInteger)byteCount;
- (id)initWithDescriptorType:(DescType)descriptorType data:(NSData *)data;
- (id)initWithEventClass:(AEEventClass)eventClass eventID:(AEEventID)eventID targetDescriptor:(NSAppleEventDescriptor *)targetDescriptor returnID:(AEReturnID)returnID transactionID:(AETransactionID)transactionID;
- (id)initListDescriptor;
- (id)initRecordDescriptor;

// Return a pointer to the AEDesc that is encapsulated by the object.
- (const AEDesc *)aeDesc NS_RETURNS_INNER_POINTER;

// Get the four-character type code or the data from a fully-initialized descriptor.
- (DescType)descriptorType;
- (NSData *)data;

// Return the contents of a descriptor, after coercing the descriptor's contents to typeBoolean, typeEnumerated, typeSInt32, or typeType, respectively.
- (Boolean)booleanValue;
- (OSType)enumCodeValue;
- (SInt32)int32Value;
- (OSType)typeCodeValue;

// Return the contents of a descriptor as a string, after coercing the descriptor's contents to typeUnicodeText.
- (NSString *)stringValue;

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
- (NSInteger)numberOfItems;

// Set, retrieve, or remove indexed descriptors inside a list or record descriptor.
- (void)insertDescriptor:(NSAppleEventDescriptor *)descriptor atIndex:(NSInteger)index;
- (NSAppleEventDescriptor *)descriptorAtIndex:(NSInteger)index;
- (void)removeDescriptorAtIndex:(NSInteger)index;

// Set, retrieve, or remove keyed descriptors inside a record descriptor.
- (void)setDescriptor:(NSAppleEventDescriptor *)descriptor forKeyword:(AEKeyword)keyword;
- (NSAppleEventDescriptor *)descriptorForKeyword:(AEKeyword)keyword;
- (void)removeDescriptorWithKeyword:(AEKeyword)keyword;

// Return the keyword associated with an indexed descriptor inside a record descriptor.
- (AEKeyword)keywordForDescriptorAtIndex:(NSInteger)index;

// Create and return a descriptor of the requested type, doing a coercion if that's appropriate and possible.
- (NSAppleEventDescriptor *)coerceToDescriptorType:(DescType)descriptorType;

@end
