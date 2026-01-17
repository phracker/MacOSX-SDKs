//
//  TKTLVRecord.h
//  Copyright (c) 2013-2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Type used for identifying TLV format tags.
/// Although for some encodings tags can have theoretically any length,
/// this implementation supports tag length only up to 64bits.
typedef UInt64 TKTLVTag
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0));

/// Base class representing Tag-Length-Value record.
/// Every record has its tag and binary value represented as NSData instance.  Allows retrieving record's tag,
/// value (as NSData object) and binary representation of the record. Existing subclasses implement assorted
/// encodings - TKBERTLVRecord, TKSimpleTLVRecord and TKCompactTLVRecord.
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKTLVRecord : NSObject

/// Tag value of the record.
@property (nonatomic, readonly) TKTLVTag tag;

/// Value field of the record.
@property (nonatomic, readonly) NSData *value;

/// Data object containing whole encoded record, including tag, length and value.
@property (nonatomic, readonly) NSData *data;

/// Parses TLV record from data block
/// @param data Data block containing serialized form of TLV record.
/// @return newly parsed record instance or nil if data do not represent valid record.
+ (nullable instancetype)recordFromData:(NSData *)data;

/// Parses sequence of TLV records from data block.
/// The amount of records is determined by the length of input data block.
/// @param data Data block containing zero or more serialized forms of TLV record.
/// @return An array of TLV record instances parsed from input data block or nil if data do not form valid TLV record sequence.
+ (nullable NSArray<TKTLVRecord *> *)sequenceOfRecordsFromData:(NSData *)data;

- (instancetype)init NS_UNAVAILABLE;

@end

/// TKBERTLVRecord implements encoding using BER-TLV encoding rules.
/// It is able to parse BER-encoded data and always produces DER-encoded data.
/// No interpretation of tag values is made, all values are treated only as NSData irrespective of the tag.
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKBERTLVRecord : TKTLVRecord

/// Encodes tag using BER-TLV tag encoding rules.
/// @param tag Tag value to encode
/// @return Binary block containing encoded tag value.
+ (NSData *)dataForTag:(TKTLVTag)tag;

/// Creates TLV record with specified tag and value.
/// @param tag Tag value for the new record.
/// @param value Value for the new record.
/// @return Newly created TLV record.
- (instancetype)initWithTag:(TKTLVTag)tag value:(NSData *)value;

/// Creates TKBERTLVRecord with specified tag and array of children TKTLVRecord instances as subrecords.
/// @param tag Tag value for the new record.
/// @param records Array of TKTLVRecord instances serving as subrecords of this record.
/// @return Newly created TLV record.
- (instancetype)initWithTag:(TKTLVTag)tag records:(NSArray<TKTLVRecord *> *)records;

@end

/// TKSimpleTLVRecord implements Simple-TLV encoding according to ISO7816-4.
/// Tag is number in range <1..254> encoded as single byte, length is either single byte specifying length 0-254
/// or 3 bytes encoded as 0xff followed by 2 bytes of big-endian encoded number.
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKSimpleTLVRecord : TKTLVRecord

/// Creates TLV record with specified tag and value.
/// @param tag Tag value for the new record.
/// @param value Value for the new record.
/// @return Newly created TLV record.
- (instancetype)initWithTag:(UInt8)tag value:(NSData *)value;

@end

/// TKCompactTLVRecord implements Compact-TLV encoding according to ISO7816-4
/// Tag is number in range <0..15> encoded as high 4 bits of initial byte, length is number in range <0..15>
/// encoded as low 4 bits of initial byte.  Value immediatelly follows leading byte.
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKCompactTLVRecord : TKTLVRecord

/// Creates TLV record with specified tag and value.
/// @param tag Tag value for the new record.
/// @param value Value for the new record.
/// @return Newly created TLV record.
- (instancetype)initWithTag:(UInt8)tag value:(NSData *)value;

@end

NS_ASSUME_NONNULL_END
