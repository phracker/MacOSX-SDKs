//
//  TKSmartCard.h
//  Copyright (c) 2013 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CryptoTokenKit/TKSmartCardATR.h>

@class TKSmartCard;
@class TKSmartCardSlot;

/// Represents pool of smart card reader slots.
NS_CLASS_AVAILABLE_MAC(10_10)
@interface TKSmartCardSlotManager : NSObject

/// Global pool of smart card reader slots.
/// Note that defaultManager instance is accessible only if the calling application has 'com.apple.security.smartcard' entitlement set to Boolean:YES.  If the calling application does not have this entitlement, defaultManager is always set to nil.
+ (instancetype)defaultManager;

/// Array of currently known slots in the system.  Slots are identified by NSString name instances.  Use KVO to be notified about slots arrivals and removals.
@property (readonly) NSArray *slotNames;

/// Instantiates smartcard reader slot of specified name.  If specified name is not registered, returns nil.
- (void)getSlotWithName:(NSString *)name reply:(void(^)(TKSmartCardSlot *slot))reply;

@end

/// Enumerates all possible slot states.
typedef NS_ENUM(NSInteger, TKSmartCardSlotState) {
    /// Slot is no longer known to the system.  This is terminal state for TKSmartCardSlot instance, once reached, the slot instance can never be revived.
    TKSmartCardSlotStateMissing        = 0,

    /// The slot is empty, no card is inserted.
    TKSmartCardSlotStateEmpty          = 1,

    /// The card was inserted into the slot and an initial probe is in progress.
    TKSmartCardSlotStateProbing        = 2,

    /// The card inserted in the slot does not answer.
    TKSmartCardSlotStateMuteCard       = 3,

    /// Card properly answered to reset.
    TKSmartCardSlotStateValidCard      = 4,

    // Following constants were introduced in 10.10 DP Seeds and replaced with names above before final release.  Do not use them.
    TKSmartCardNoSlot NS_ENUM_DEPRECATED_MAC(10_10, 10_10)         = TKSmartCardSlotStateMissing,
    TKSmartCardSlotEmpty NS_ENUM_DEPRECATED_MAC(10_10, 10_10)      = TKSmartCardSlotStateEmpty,
    TKSmartCardSlotProbing NS_ENUM_DEPRECATED_MAC(10_10, 10_10)    = TKSmartCardSlotStateProbing,
    TKSmartCardSlotMuteCard NS_ENUM_DEPRECATED_MAC(10_10, 10_10)   = TKSmartCardSlotStateMuteCard,
    TKSmartCardSlotValidCard NS_ENUM_DEPRECATED_MAC(10_10, 10_10)  = TKSmartCardSlotStateValidCard,
} NS_ENUM_AVAILABLE_MAC(10_10);

/// Represents single slot which can contain smartcard.
NS_CLASS_AVAILABLE_MAC(10_10)
@interface TKSmartCardSlot : NSObject

/// Current state of the slot.  Use KVO to be notified about state changes.
@property (readonly) TKSmartCardSlotState state;

/// ATR of the inserted smartcard, or nil if no or mute smartcard is inserted.
@property (readonly) TKSmartCardATR *ATR;

/// Name of the smart card reader slot.
@property (nonatomic, readonly) NSString *name;

/// Maximal length of input APDU that the slot is able to transfer to the card.
@property (nonatomic, readonly) NSInteger maxInputLength;

/// Maximal length of output APDU that the slot is able to transfer from the card.
@property (nonatomic, readonly) NSInteger maxOutputLength;

/// Creates new object representing currently inserted and valid card.
/// @discussion It is possible to instantiate multiple objects for single card, exclusivity is handled by sessions on the level of created smart card objects.
/// @return Newly created smart card object, or nil if slot does not contain valid card.
- (TKSmartCard *)makeSmartCard;

@end

/// Represents smart card inserted in the slot. Once the card is physically removed from the slot, the session object is invalid and will always fail the operation invoked on it.  In order to communicate with the card, an exclusive session must be established.
NS_CLASS_AVAILABLE_MAC(10_10)
@interface TKSmartCard : NSObject

/// Slot in which is this card inserted.
@property (nonatomic, readonly) TKSmartCardSlot *slot;

/// Flag indicating whether card is valid, i.e. it was not removed from the reader.  Use Key-Value-Observing to be notified about card removal.
@property (readonly) BOOL valid;

/// Bitmask containing allowed protocols to be used when communicating with the card.  This property is consulted only during connection to the card, changes are not propagated to already connected session.  By default, any protocol can be used.
@property TKSmartCardProtocol allowedProtocols;

/// Protocol used for communication with the smartcard.  If no card session is established, TKSmartCardProtocolNone is set.
@property (readonly) TKSmartCardProtocol currentProtocol;

/// Flag indicating whether card session should be considered as sensitive.  Sensitive session always gets card after reset before communicating with it and never leaves card without reset to be used by another smart card object.  This might be important in case that card session contain some important state which should not leak to another smart card object (possibly running in another, foreign application).  Default is NO.
@property BOOL sensitive;

/// User-specified context kept as long as the card is powered.  Once the card is removed or another TKSmartCard object opens session, this property is automatically set to nil.
@property id context;

/// Begins session with the card.
/// @discussion When session exists, other requests for sessions from other card objects to the same card are blocked. Session is reference-counted, the same amount of 'end' calls must be done to really terminate the session. Note that finishing session does not automatically mean that the card is disconnected; it only happens when another session from different card object is requested.
/// @param success Signals whether session was successfully started.
/// @param error More information about error preventing the transaction to start
- (void)beginSessionWithReply:(void(^)(BOOL success, NSError *error))reply;

/// Transmits raw command to the card.  This call is allowed only inside session.
/// @param request Request part of APDU
/// @param reponse Response part of APDU, or nil if communication with the card failed
/// @param error Error details when communication with the card failed
- (void)transmitRequest:(NSData *)request reply:(void(^)(NSData *response, NSError *error))reply;

/// Terminates the transaction. If no transaction is pending any more, the connection will be closed if there is another session in the system waiting for the transaction.
- (void)endSession;

@end

@interface TKSmartCard (APDULevelTransmit)

/// CLA byte which will be used for sendIns: APDU transmits.  Default value is 0x00.
@property UInt8 cla;

/// Flag indicating whether extended length APDUs should be used. It is automatically enabled only when used slot supports transmitting extended length commands and card announces that extended length APDU are supported in its ATR. However, caller can explicitely override this decision at its will.
@property BOOL useExtendedLength;

/// Transmits APDU to the card and returns response.
/// @discussion Asynchronous high level variant of command for transmitting APDU to the card.  Handles all ISO7816-4 APDU cases translation to proper sequences according to used protocol.  If useExtendedLength is enabled and it is decided that it is beneficial for current set of arguments, extended APDUs are used automatically.
/// @param ins INS code of the APDU
/// @param p1 P1 code of the APDU
/// @param p2 P2 code of the APDU
/// @param requestData Data field of the APDU.  Length of the data serves as Lc field of the APDU
/// @param le Expected number of bytes to be returned, or nil if no output data are expected (i.e. case1 or case3 APDUs). To get as much bytes as card provides, pass @0.
/// @param replyData Block of returned data without SW1SW2 bytes, or nil if an error occured.
/// @param sw SW1SW2 result code
/// @param error Contains error details when nil is returned.  Specific error is also filled in if there was no communication error, but card returned other SW code than 0x9000.
- (void)sendIns:(UInt8)ins p1:(UInt8)p1 p2:(UInt8)p2 data:(NSData *)requestData le:(NSNumber *)le
          reply:(void(^)(NSData *replyData, UInt16 sw, NSError *error))reply;

@end
