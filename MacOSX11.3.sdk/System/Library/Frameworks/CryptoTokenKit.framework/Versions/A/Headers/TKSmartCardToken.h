//
//  TKSmartCardToken.h
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <CryptoTokenKit/TKToken.h>
#import <CryptoTokenKit/TKSmartCard.h>

NS_ASSUME_NONNULL_BEGIN

@class TKSmartCardTokenSession;
@class TKSmartCardToken;
@protocol TKSmartCardTokenDriverDelegate;
@class TKSmartCardTokenDriver;

/*!
 @discussion Context of a SmartCard PIN authentication operation.
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKTokenSmartCardPINAuthOperation : TKTokenAuthOperation

/*!
 @discussion PIN formatting properties.
 @note The property is initialized with a default instance of TKSmartCardPINFormat.
 */
@property TKSmartCardPINFormat *PINFormat;

/*!
 @discussion APDU template into which PIN gets filled in. If set to nil, the system will not attempt to authenticate by sending the formatted APDU to the SmartCard, but rather the token itself is expected to perform the authentication.  It is preferred to provide APDUTemplate if possible, because it allows using hardware PINPad for secure PIN entry (provided that the reader has one).
 */
@property (nullable, copy) NSData *APDUTemplate;

/*!
 @discussion Offset in bytes within APDU template to mark the location for filling in the PIN.
 */
@property NSInteger PINByteOffset;

/*!
 @discussion TKSmartCard to which the formatted APDU gets sent in order to authenticate (used only if 'APDUTemplate' is set).
 */
@property (nullable) TKSmartCard *smartCard;

/*!
 @discussion PIN value which will be set when 'finishWithError:' gets triggered.  Note that the PIN is not set in case that APDUTemplate was set.  In this case, PIN was already sent to the card using specified template.
 */
@property (nullable, copy) NSString *PIN;

@end

/*!
 @abstract TKSmartCardTokenSession represents token session based on SmartCard token.
 @discussion When implementing SmartCard token extension, subclass TKSmartCardTokenSession and implement TKTokenSessionDelegate on it.  Use #token property to get access and send APDUs to the underlying SmartCard.
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKSmartCardTokenSession : TKTokenSession

/*!
 @abstract contains TKSmartCard instance with active exclusive session and SmartCard application selected.
 @discussion This property can be accessed only when handling one of the methods of TKTokenSessionDelegate protocol.  If associated token has set AID property, then the returned card has opened exclusive session to the card and the application is already selected.  Therefore there is no need to call -[TKSmartCard beginSessionWithReply:]) on returned SmartCard instance in such case and system will take care of terminating session when current token request servicing is finished,  -[TKSmartCard endSession] must not be called either.

 You can store any kind of context state information representing state of the card into smartCard.context property.  This property will be automatically set to nil if the card is reset or accessed by different TKSmartCard instance (possibly in another process).  Checking TKSmartCard.context property for previously stored value can be used to avoid potentially costly restoring of SmartCard state before performing the operation.
 */
@property (readonly) TKSmartCard *smartCard;

@end

/*!
 @abstract TKSmartCardToken base class for implementing SmartCard based token.
 @discussion When implementing SmartCard token extension, subclass TKSmartCardToken and implement TKTokenDelegate on it.
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKSmartCardToken : TKToken

/*!
 @discussion Initializes token instance with specified attributes.
 @param smartCard TKSmartCard instance representing connection to SmartCard on which the intance should operate.
 @param AID ISO7816-4 application ID which is preselected on the card.
 @param instanceID Unique, persistent identifier of this token.  This is typically implemented by some kind of SmartCard serial number.
 @param tokenDriver associated driver which initiated creation of this token.
 */
- (instancetype)initWithSmartCard:(TKSmartCard *)smartCard AID:(nullable NSData *)AID instanceID:(NSString *)instanceID tokenDriver:(TKSmartCardTokenDriver *)tokenDriver NS_DESIGNATED_INITIALIZER;

/*!
 @discussion This is AID which is specified in extension's plist NSExtensionAttributes as @c com.apple.ctk.aid attribute. If the attribute specifies array of multiple AIDs, this parameter represents AID which was found on the card and is already preselected.  If @c com.apple.ctk.aid is not present, no application is automatically preselected and value of this property is nil.
 */
@property (readonly, nullable) NSData *AID;

- (instancetype)initWithTokenDriver:(TKTokenDriver *)tokenDriver instanceID:(NSString *)instanceID NS_UNAVAILABLE;

@end

/*!
 @abstract TKSmartCardTokenDriver represents driver for specific SmartCard type.
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(11.0), watchos(4.0))
@interface TKSmartCardTokenDriver : TKTokenDriver

@end

/*!
 @discussion TKSmartCardTokenDriverDelegate is used to implement creation of new token instance according to the SmartCard.
 */
@protocol TKSmartCardTokenDriverDelegate<TKTokenDriverDelegate>

/*!
 @discussion Called by system when new SmartCard is detected.  You must override this method to create a new valid token TKSmartCardToken instance for @c smartCard.
 @param smartCard Target SmartCard.
 @param AID ISO7816-4 AID (application ID) which is already selected on the card.  If @c com.apple.ctk.aid is not present, no application is selected and this parameter is nil.
 @param error Error details if operation fails.
 @return Newly created token instance representing @c smartCard.  If an error occurs or driver decides that it does not want to handle specified smartCard as token, return nil.
 */
- (nullable TKSmartCardToken *)tokenDriver:(TKSmartCardTokenDriver *)driver createTokenForSmartCard:(TKSmartCard *)smartCard AID:(nullable NSData *)AID error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
