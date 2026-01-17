/*	NSSerialization.h
	Copyright (c) 1993-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSData.h>

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
#warning The API is this header is obsolete and deprecated in 10.2.
#warning Stop using this API and including this header.
// Note also that this API does not handle modern property list object graphs.
#endif

/***************	Serialization of very basic types	***********/

@interface NSMutableData (NSMutableDataSerialization)

- (void)serializeInt:(int)value;
- (void)serializeInts:(int *)intBuffer count:(unsigned)numInts;
- (void)serializeInt:(int)value atIndex:(unsigned)index;
- (void)serializeInts:(int *)intBuffer count:(unsigned)numInts atIndex:(unsigned)index;
- (void)serializeAlignedBytesLength:(unsigned)length;

@end

@interface NSData (NSDataDeserialization)

- (int)deserializeIntAtIndex:(unsigned)index;
- (void)deserializeInts:(int *)intBuffer count:(unsigned)numInts atIndex:(unsigned)index;
- (int)deserializeIntAtCursor:(unsigned *)cursor;
- (void)deserializeInts:(int *)intBuffer count:(unsigned)numInts atCursor:(unsigned *)cursor;
- (unsigned)deserializeAlignedBytesLengthAtCursor:(unsigned *)cursor;
- (void)deserializeBytes:(void *)buffer length:(unsigned)bytes atCursor:(unsigned *)cursor;

@end

/********* 	Objective-C Type Serialization ************************/

@protocol NSObjCTypeSerializationCallBack

- (void)serializeObjectAt:(id *)object ofObjCType:(const char *)type intoData:(NSMutableData *)data;
- (void)deserializeObjectAt:(id *)object ofObjCType:(const char *)type fromData:(NSData *)data atCursor:(unsigned *)cursor;

@end

@interface NSMutableData (NSMutableDataObjcTypeSerialization)

- (void)serializeDataAt:(const void *)data ofObjCType:(const char *)type context:(id <NSObjCTypeSerializationCallBack>)callback;

@end

@interface NSData (NSDataObjCTypeDeserialization)

- (void)deserializeDataAt:(void *)data ofObjCType:(const char *)type atCursor:(unsigned *)cursor context:(id <NSObjCTypeSerializationCallBack>)callback;

@end

/***************	Property List Serialization	***************/

@interface NSSerializer : NSObject

+ (void)serializePropertyList:(id)aPropertyList intoData:(NSMutableData *)mdata;
+ (NSData *)serializePropertyList:(id)aPropertyList;

@end

@interface NSDeserializer : NSObject
    
+ (id)deserializePropertyListFromData:(NSData *)data atCursor:(unsigned *)cursor mutableContainers:(BOOL)mut;
+ (id)deserializePropertyListLazilyFromData:(NSData *)data atCursor:(unsigned *)cursor length:(unsigned)length mutableContainers:(BOOL)mut;
+ (id)deserializePropertyListFromData:(NSData *)serialization mutableContainers:(BOOL)mut;

@end

