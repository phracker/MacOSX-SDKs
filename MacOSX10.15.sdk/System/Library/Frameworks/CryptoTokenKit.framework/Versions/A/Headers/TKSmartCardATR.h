//
//  TKSmartCardATR.h
//  Copyright (c) 2013 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TKTLVRecord.h"

NS_ASSUME_NONNULL_BEGIN

/// Bitmask of available SmartCard protocols.
typedef NS_OPTIONS(NSUInteger, TKSmartCardProtocol) {
    TKSmartCardProtocolNone  = 0,
    TKSmartCardProtocolT0    = (1L << 0),
    TKSmartCardProtocolT1    = (1L << 1),
    TKSmartCardProtocolT15   = (1L << 15),
    TKSmartCardProtocolAny   = (1L << 16) - 1,
} API_AVAILABLE(macos(10.10));

/// Represents single interface-bytes group of ATR.
API_AVAILABLE(macos(10.10))
@interface TKSmartCardATRInterfaceGroup : NSObject

/// TA interface byte of ATR group, or nil if TA is not present.
@property (nonatomic, readonly, nullable) NSNumber *TA;

/// TB interface byte of ATR group, or nil if TB is not present.
@property (nonatomic, readonly, nullable) NSNumber *TB;

/// TC interface byte of ATR group, or nil if TC is not present.
@property (nonatomic, readonly, nullable) NSNumber *TC;

/// Protocol number for this group.  First group (global) has protocol unassigned, contains nil.
@property (nonatomic, readonly, nullable) NSNumber *protocol;

@end

/// Represents parsed SmartCard ATR.  Provides routine for parsing byte stream or NSData with binary ATR and accessors to parsed ATR parts.
API_AVAILABLE(macos(10.10))
@interface TKSmartCardATR : NSObject

/// Parses ATR from binary data block
/// @param bytes Data containing full valid ATR
/// @return Parsed ATR instance, or nil when #bytes do not contain valid ATR.
- (nullable instancetype)initWithBytes:(NSData *)bytes;

/// Parses ATR from stream.
/// @param source Provides one byte of ATR from the stream or -1 in case of an error
/// @return Parsed ATR instance, or nil when #source method failed or an invalid ATR is detected
- (nullable instancetype)initWithSource:(int(^)(void))source;

/// Full ATR as string of bytes
@property (nonatomic, readonly) NSData *bytes;

/// Array of NSNumber of protocols indicated in ATR, in the correct order (i.e. the default protocol comes first), duplicates sorted out.
@property (nonatomic, readonly) NSArray<NSNumber *> *protocols;

/// Retrieves interface group with specified index.
/// @param index Index of the requested interface group.  Indexing conforms to ISO7816-3, i.e. starts from 1.
/// @return Interface group with given index, or nil of no such group was present.
- (nullable TKSmartCardATRInterfaceGroup *)interfaceGroupAtIndex:(NSInteger)index;

// Retrieves interface group belonging to specified protocol.
/// @param protocol Protocol number for which the interface group is requested.
- (nullable TKSmartCardATRInterfaceGroup *)interfaceGroupForProtocol:(TKSmartCardProtocol)protocol;

/// Just historical bytes of ATR, without Tck and interface bytes.
@property (nonatomic, readonly) NSData *historicalBytes;

/// An array of TKCompactTLVRecord instances with TLV records parsed from historical bytes.  If historical bytes are
/// not structured using Compact TLV encoding, nil is returned.
/// @note In case that ATR historical bytes begin with 0x00, the last three bytes (status indicator) are automatically
///       appended into the returned records as if historical bytes would begin with 0x80 and 0x8 record is present
///       in historical bytes.
@property (nonatomic, readonly, nullable) NSArray<TKCompactTLVRecord *> *historicalRecords
API_AVAILABLE(macos(10.12));

@end

NS_ASSUME_NONNULL_END
