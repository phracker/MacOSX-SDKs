//
//  TKSmartCard.h
//  Copyright (c) 2013 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CryptoTokenKit/TKSmartCardATR.h>

NS_ASSUME_NONNULL_BEGIN

@class TKSmartCard;
@class TKSmartCardSlot;
@class TKSmartCardUserInteraction;

/// Represents pool of SmartCard reader slots.
API_AVAILABLE(macos(10.10))
@interface TKSmartCardSlotManager : NSObject

/// Global pool of SmartCard reader slots.
/// Note that defaultManager instance is accessible only if the calling application has 'com.apple.security.smartcard' entitlement set to Boolean:YES.  If the calling application does not have this entitlement, defaultManager is always set to nil.
@property (class, nullable, readonly) TKSmartCardSlotManager *defaultManager;

/// Array of currently known slots in the system.  Slots are identified by NSString name instances.  Use KVO to be notified about slots arrivals and removals.
@property (readonly) NSArray<NSString *> *slotNames;

/// Instantiates smartcard reader slot of specified name.  If specified name is not registered, reports nil.
- (void)getSlotWithName:(NSString *)name reply:(void(^)(TKSmartCardSlot *__nullable slot))reply;

/// Gets SmartCard reader slot with specified name.  If reader slot with this name does not exist, returns nil.
- (nullable TKSmartCardSlot *)slotNamed:(NSString *)name
API_AVAILABLE(macos(10.13));

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
} API_AVAILABLE(macos(10.10));

/// Enumerates all possible PIN character sets.
typedef NS_ENUM(NSInteger, TKSmartCardPINCharset) {
    /// PIN is only composed of digits.
    TKSmartCardPINCharsetNumeric             = 0,

    /// PIN can be composed of digits and letters.
    TKSmartCardPINCharsetAlphanumeric        = 1,

    /// PIN can be composed of digits and uppercase letters.
    TKSmartCardPINCharsetUpperAlphanumeric   = 2,
} API_AVAILABLE(macos(10.11));

/// Enumerates all possible PIN encoding types.
typedef NS_ENUM(NSInteger, TKSmartCardPINEncoding) {
    /// Characters are encoded in Binary format (1234 => 01h 02h 03h 04h).
    TKSmartCardPINEncodingBinary    = 0,

    /// Characters are encoded in ASCII format (1234 => 31h 32h 33h 34h).
    TKSmartCardPINEncodingASCII     = 1,

    /// Characters (only digits) are encoded in BCD format (1234 => 12h 34h).
    TKSmartCardPINEncodingBCD       = 2,
} API_AVAILABLE(macos(10.11));

/// Enumerates all posible PIN justification types.
typedef NS_ENUM(NSInteger, TKSmartCardPINJustification) {
    /// Justify to the left.
    TKSmartCardPINJustificationLeft     = 0,

    /// Justify to the right.
    TKSmartCardPINJustificationRight    = 1,
}  API_AVAILABLE(macos(10.11));

/// Bitmask specifying condition(s) under which PIN entry should be considered complete.
typedef NS_OPTIONS(NSUInteger, TKSmartCardPINCompletion) {
    /// Completion by reaching the maximum PIN length.
    TKSmartCardPINCompletionMaxLength  = (1L << 0),

    /// Completion by pressing the validation key.
    TKSmartCardPINCompletionKey        = (1L << 1),

    /// Completion by timeout expiration.
    TKSmartCardPINCompletionTimeout    = (1L << 2),
}  API_AVAILABLE(macos(10.11));

/// Bitmask specifying whether PIN confirmation should be requested.
typedef NS_OPTIONS(NSUInteger, TKSmartCardPINConfirmation) {
    /// No confirmation requested.
    TKSmartCardPINConfirmationNone      = 0,

    /// Confirmation (entry) of the new PIN requested.
    TKSmartCardPINConfirmationNew       = (1L << 0),

    /// Confirmation (entry) of the current PIN requested.
    TKSmartCardPINConfirmationCurrent   = (1L << 1),
}  API_AVAILABLE(macos(10.11));

/// Specifies PIN formatting properties.
API_AVAILABLE(macos(10.11))
@interface TKSmartCardPINFormat : NSObject

/// Format of PIN characters.
/// @note Default value: TKSmartCardPINCharsetNumeric
@property TKSmartCardPINCharset charset;

/// Encoding of PIN characters.
/// @note Default value: TKSmartCardPINEncodingASCII
@property TKSmartCardPINEncoding encoding;

/// Minimum number of characters to form a valid PIN.
/// @note Default value: 4
@property NSInteger minPINLength;

/// Maximum number of characters to form a valid PIN.
/// @note Default value: 8
@property NSInteger maxPINLength;

/// Total length of the PIN block in bytes.
/// @note Default value: 8
@property NSInteger PINBlockByteLength;

/// PIN justification within the PIN block.
/// @note Default value: TKSmartCardPINJustificationLeft
@property TKSmartCardPINJustification PINJustification;

/// Offset in bits within the PIN block to mark a location for filling in the formatted PIN (justified with respect to PINJustification).
/// @note Default value: 0
/// @discussion Note that the value of PINBitOffset indirectly controls the internal system units indicator. If PINBitOffset is byte aligned (PINBitOffset mod 8 is equal to 0), the internal representation of PINBitOffset gets converted from bits to bytes.
@property NSInteger PINBitOffset;

/// Offset in bits within the PIN block to mark a location for filling in the PIN length (always left justified).
/// @note Default value: 0
/// @discussion Note that the value of PINLengthBitOffset indirectly controls the internal system units indicator. If PINLengthBitOffset is byte aligned (PINLengthBitOffset mod 8 is equal to 0), the internal representation of PINLengthBitOffset gets converted from bits to bytes.
@property NSInteger PINLengthBitOffset;

/// Size in bits of the PIN length field. If set to 0, PIN length is not written.
/// @note Default value: 0
@property NSInteger PINLengthBitSize;

@end

/// Delegate for user interactions involving the SmartCard reader.
API_AVAILABLE(macos(10.11))
@protocol TKSmartCardUserInteractionDelegate
@optional

/// A valid character has been entered.
- (void)characterEnteredInUserInteraction:(TKSmartCardUserInteraction *)interaction;

/// A correction key has been pressed.
- (void)correctionKeyPressedInUserInteraction:(TKSmartCardUserInteraction *)interaction;

/// The validation key has been pressed (end of PIN entry).
- (void)validationKeyPressedInUserInteraction:(TKSmartCardUserInteraction *)interaction;

/// An invalid character has been entered.
- (void)invalidCharacterEnteredInUserInteraction:(TKSmartCardUserInteraction *)interaction;

/// Indicates that the old PIN needs to be entered.
- (void)oldPINRequestedInUserInteraction:(TKSmartCardUserInteraction *)interaction;

/// Indicates that the new PIN needs to be entered.
- (void)newPINRequestedInUserInteraction:(TKSmartCardUserInteraction *)interaction;

/// Indicates that the new PIN needs to be confirmed (re-entered).
- (void)newPINConfirmationRequestedInUserInteraction:(TKSmartCardUserInteraction *)interaction;

@end

/// Represents handle to a user interaction involving the SmartCard reader.
/// @discussion It is a proxy object obtained as a result of invoking the userInteractionFor*** family of methods in TKSmartCardSlot and TKSmartCard.
API_AVAILABLE(macos(10.11))
@interface TKSmartCardUserInteraction : NSObject

/// Delegate for state observing of the interaction.
@property (weak, nullable) id<TKSmartCardUserInteractionDelegate> delegate;

/// Initial interaction timeout. If set to 0, the reader-defined default timeout is used.
/// @note Default value: 0
@property NSTimeInterval initialTimeout;

/// Timeout after the first key stroke. If set to 0, the reader-defined default timeout is used.
/// @note Default value: 0
@property NSTimeInterval interactionTimeout;

/// Runs the interaction.
- (void)runWithReply: (void(^)(BOOL success, NSError *__nullable error))reply;

/// Attempts to cancel a running interaction. Note that for some interactions, this functionality might not be available.
/// @return Returns NO if the operation is not running, or cancelling is not supported.
- (BOOL)cancel;

@end

/// User interaction for the secure PIN operations on the SmartCard reader.
/// @note Result is available after the interaction has been successfully completed.
API_AVAILABLE(macos(10.11))
@interface TKSmartCardUserInteractionForPINOperation : TKSmartCardUserInteraction

/// Bitmask specifying condition(s) under which PIN entry should be considered complete.
/// @note Default value: TKSmartCardPINCompletionKey
@property TKSmartCardPINCompletion PINCompletion;

/// List of message indices referring to a predefined message table. It is used to specify the type and number of messages displayed during the PIN operation.
/// @discussion If nil, the reader does not display any message (reader specific). Typically, PIN verification takes 1 message, PIN modification 1-3 messages.
/// @note Default value: nil
@property (nullable) NSArray<NSNumber *> *PINMessageIndices;

/// Locale defining the language of displayed messages. If set to nil, the user's current locale is used.
/// @note Default value: the user's current locale
@property (null_resettable) NSLocale *locale;

/// SW1SW2 result code.
@property UInt16 resultSW;

/// Optional block of returned data (without SW1SW2 bytes).
@property (nullable) NSData *resultData;

@end

/// User interaction for the secure PIN verification on the SmartCard reader.
/// @note Result is available after the interaction has been successfully completed.
API_AVAILABLE(macos(10.11))
@interface TKSmartCardUserInteractionForSecurePINVerification : TKSmartCardUserInteractionForPINOperation

@end

/// User interaction for the secure PIN change on the SmartCard reader.
/// @note Result is available after the interaction has been successfully completed.
API_AVAILABLE(macos(10.11))
@interface TKSmartCardUserInteractionForSecurePINChange : TKSmartCardUserInteractionForPINOperation

/// Bitmask specifying whether PIN confirmation should be requested.
/// @note Default value: TKSmartCardPINConfirmationNone
@property TKSmartCardPINConfirmation PINConfirmation;

@end

/// Represents single slot which can contain SmartCard.
API_AVAILABLE(macos(10.10))
@interface TKSmartCardSlot : NSObject

/// Current state of the slot.  Use KVO to be notified about state changes.
@property (readonly) TKSmartCardSlotState state;

/// ATR of the inserted SmartCard, or nil if no or mute SmartCard is inserted.
@property (readonly, nullable) TKSmartCardATR *ATR;

/// Name of the SmartCard reader slot.
@property (nonatomic, readonly) NSString *name;

/// Maximal length of input APDU that the slot is able to transfer to the card.
@property (nonatomic, readonly) NSInteger maxInputLength;

/// Maximal length of output APDU that the slot is able to transfer from the card.
@property (nonatomic, readonly) NSInteger maxOutputLength;

/// Creates new object representing currently inserted and valid card.
/// @discussion It is possible to instantiate multiple objects for single card, exclusivity is handled by sessions on the level of created SmartCard objects.
/// @return Newly created SmartCard object, or nil if slot does not contain valid card.
- (nullable TKSmartCard *)makeSmartCard;

@end

/// Represents SmartCard inserted in the slot. Once the card is physically removed from the slot, the session object is invalid and will always fail the operation invoked on it.  In order to communicate with the card, an exclusive session must be established.
API_AVAILABLE(macos(10.10))
@interface TKSmartCard : NSObject

/// Slot in which is this card inserted.
@property (nonatomic, readonly) TKSmartCardSlot *slot;

/// Flag indicating whether card is valid, i.e. it was not removed from the reader.  Use Key-Value-Observing to be notified about card removal.
@property (readonly) BOOL valid;

/// Bitmask containing allowed protocols to be used when communicating with the card.  This property is consulted only during connection to the card, changes are not propagated to already connected session.  By default, any protocol can be used.
@property TKSmartCardProtocol allowedProtocols;

/// Protocol used for communication with the SmartCard.  If no card session is established, TKSmartCardProtocolNone is set.
@property (readonly) TKSmartCardProtocol currentProtocol;

/// Flag indicating whether card session should be considered as sensitive.  Sensitive session always gets card after reset before communicating with it and never leaves card without reset to be used by another SmartCard object.  This might be important in case that card session contain some important state which should not leak to another SmartCard object (possibly running in another, foreign application).  Default is NO.
@property BOOL sensitive;

/// User-specified context kept as long as the card is powered.  Once the card is removed or another TKSmartCard object opens session, this property is automatically set to nil.
@property (nullable) id context;

/// Begins session with the card.
/// @discussion When session exists, other requests for sessions from other card objects to the same card are blocked. Session is reference-counted, the same amount of 'end' calls must be done to really terminate the session. Note that finishing session does not automatically mean that the card is disconnected; it only happens when another session from different card object is requested.
/// @param success Signals whether session was successfully started.
/// @param error More information about error preventing the transaction to start
- (void)beginSessionWithReply:(void(^)(BOOL success, NSError *__nullable error))reply;

/// Transmits raw command to the card.  This call is allowed only inside session.
/// @param request Request part of APDU
/// @param reponse Response part of APDU, or nil if communication with the card failed
/// @param error Error details when communication with the card failed
- (void)transmitRequest:(NSData *)request reply:(void(^)(NSData *__nullable response, NSError *__nullable error))reply;

/// Terminates the transaction. If no transaction is pending any more, the connection will be closed if there is another session in the system waiting for the transaction.
- (void)endSession;

/// Creates a new user interaction object for secure PIN verification using the SmartCard reader facilities (typically a HW keypad).
/// @note This interaction is only allowed within a session.
/// @param PINFormat PIN format descriptor.
/// @param APDU Predefined APDU in which the SmartCard reader fills in the PIN.
/// @param PINByteOffset Offset in bytes within APDU data field to mark a location of a PIN block for filling in the entered PIN (currently unused, must be 0).
/// @return A new user interaction object, or nil if this feature is not supported by the SmartCard reader. After the interaction has been successfully completed the operation result is available in the result properites.
- (nullable TKSmartCardUserInteractionForSecurePINVerification *)userInteractionForSecurePINVerificationWithPINFormat:(TKSmartCardPINFormat *)PINFormat
                                                                                                                  APDU:(NSData *)APDU
                                                                                                         PINByteOffset:(NSInteger)PINByteOffset
                                                                                                                NS_AVAILABLE(10_11, 9_0);

/// Creates a new user interaction object for secure PIN change using the SmartCard reader facilities (typically a HW keypad).
/// @note This interaction is only allowed within a session.
/// @param PINFormat PIN format descriptor.
/// @param APDU Predefined APDU in which the SmartCard reader fills in the PIN(s).
/// @param currentPINByteOffset Offset in bytes within APDU data field to mark a location of a PIN block for filling in the current PIN.
/// @param newPINByteOffset Offset in bytes within APDU data field to mark a location of a PIN block for filling in the new PIN.
/// @return A new user interaction object, or nil if this feature is not supported by the SmartCard reader. After the interaction has been successfully completed the operation result is available in the result properites.
- (nullable TKSmartCardUserInteractionForSecurePINChange *)userInteractionForSecurePINChangeWithPINFormat:(TKSmartCardPINFormat *)PINFormat
                                                                                                     APDU:(NSData *)APDU
                                                                                     currentPINByteOffset:(NSInteger)currentPINByteOffset
                                                                                         newPINByteOffset:(NSInteger)newPINByteOffset
                                                                                                NS_AVAILABLE(10_11, 9_0);

@end

/// Extension of base TKSmartCard interface implementing ISO7816-3 and ISO7816-4 structured APDU transmission.
@interface TKSmartCard (APDULevelTransmit)

/// CLA byte which will be used for sendIns: APDU transmits.  Default value is 0x00.
@property UInt8 cla
API_AVAILABLE(macos(10.10));

/// Flag indicating whether extended length APDUs should be used. It is automatically enabled only when used slot supports transmitting extended length commands and card announces that extended length APDU are supported in its ATR. However, caller can explicitly override this decision.
@property BOOL useExtendedLength
API_AVAILABLE(macos(10.10));

/// Flag indicating whether command chaining of APDU with data field longer than 255 bytes can be used.  It is automatically enabled when card announces that command chaining is supported in its ATR.  However, caller can explicitly override this decision.
@property BOOL useCommandChaining
API_AVAILABLE(macos(10.12));

/// Transmits APDU to the card and returns response.
/// @discussion Asynchronous high level variant of command for transmitting APDU to the card.  Handles all ISO7816-4 APDU cases translation to proper sequences according to used protocol.  Consults useExtendedAPDU and useCommandChaining properties and uses these modes whenever appropriate and beneficial for sending requested APDU request.
/// @param ins INS code of the APDU
/// @param p1 P1 code of the APDU
/// @param p2 P2 code of the APDU
/// @param requestData Data field of the APDU, or nil if no input data field should be present (i.e case1 or case2 APDUs).  Length of the data serves as Lc field of the APDU.
/// @param le Expected number of bytes to be returned, or nil if no output data are expected (i.e. case1 or case3 APDUs). To get as much bytes as card provides, pass @0.
/// @param replyData Block of returned data without SW1SW2 bytes, or nil if an error occured.
/// @param sw SW1SW2 result code, first two bytes of returned card's reply.
/// @param error Contains error details when nil is returned.  Specific error is also filled in if there was no communication error, but card returned other SW code than 0x9000.
- (void)sendIns:(UInt8)ins p1:(UInt8)p1 p2:(UInt8)p2 data:(nullable NSData *)requestData le:(nullable NSNumber *)le
          reply:(void(^)(NSData *__nullable replyData, UInt16 sw, NSError *__nullable error))reply
API_AVAILABLE(macos(10.10));

/// Synchronous variant of session creation.  Begins the session, executes given block and ends session.
/// @param error Error receiving more information when transaction failed to start or block failed for some reason.
/// @param block Block to be executed when the session was successfully begun.
/// @return Returns YES if the session was successfully begun and block returned YES, otherwise NO.
- (BOOL)inSessionWithError:(NSError **)error executeBlock:(BOOL(^)(NSError **error))block
API_AVAILABLE(macos(10.12));

/// Transmits APDU to the card and returns response.
/// @discussion Synchronous high level variant of command for transmitting APDU to the card.  Handles all ISO7816-4 APDU cases translation to proper sequences according to used protocol.  Should be used in block passed to -[TKSmartCard inSessionWithError:executeBlock:] method.
/// @param ins INS code of the APDU
/// @param p1 P1 code of the APDU
/// @param p2 P2 code of the APDU
/// @param data Data field of the APDU.  Length of the data serves as Lc field of the APDU
/// @param le Expected number of bytes to be returned, or nil if no output data are expected (i.e. case1 or case3 APDUs). To get as much bytes as card provides, pass @0.
/// @param sw On output, filled with SW1SW2 result code
/// @param error Contains error details when nil is returned.  Specific error is also filled in if there was no communication error, but card returned other SW code than 0x9000.
/// @return Returned data field, excluding SW status bytes.  If an error occured, returns nil.
- (nullable NSData *)sendIns:(UInt8)ins p1:(UInt8)p1 p2:(UInt8)p2 data:(nullable NSData *)requestData
                          le:(nullable NSNumber *)le sw:(UInt16 *)sw error:(NSError **)error
API_AVAILABLE(macos(10.12));

@end

NS_ASSUME_NONNULL_END
