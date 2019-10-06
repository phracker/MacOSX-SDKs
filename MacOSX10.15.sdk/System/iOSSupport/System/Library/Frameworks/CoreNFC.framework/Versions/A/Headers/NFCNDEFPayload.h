//
//  NFCNDEFPayload.h
//  CoreNFC
//
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef NFCNDEFPayload_h
#define NFCNDEFPayload_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @discussion Type Name Format value defined by NFC Data Exchange Format (NDEF) Technical Specification
 *             from NFC Forum.
 */
typedef NS_ENUM(uint8_t, NFCTypeNameFormat) {
    NFCTypeNameFormatEmpty             = 0x00,
    NFCTypeNameFormatNFCWellKnown      = 0x01,
    NFCTypeNameFormatMedia             = 0x02,
    NFCTypeNameFormatAbsoluteURI       = 0x03,
    NFCTypeNameFormatNFCExternal       = 0x04,
    NFCTypeNameFormatUnknown           = 0x05,
    NFCTypeNameFormatUnchanged         = 0x06
};

/*!
 * @class NFCNDEFPayload
 *
 * @discussion  A NDEF message payload consists of Type Name Format, Type, Payload Identifier, and Payload data.
 *              The NDEF payload cannot result into a record that is greater than 128KB in size.
 */
NS_EXTENSION_UNAVAILABLE("Not available to extensions") API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, macos, tvos)
@interface NFCNDEFPayload : NSObject<NSSecureCoding>

@property (nonatomic, assign) NFCTypeNameFormat typeNameFormat;
@property (nonatomic, copy) NSData *type;
@property (nonatomic, copy) NSData *identifier;
@property (nonatomic, copy) NSData *payload;

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @method initWithFormat:type:identifier:paylaod:
 *
 * @param format        NFCTypeNameFormat value.
 * @param type          Identifier describing the type of the payload.  Empty data indicates field is absent from the payload.
 * @param identifier    Identifier in the form of a URI reference.  Empty data indicates field is absent from the payload.
 * @param payload       Payload data.  Empty data indicates field is absent from the payload.
 *
 * This initializer uses the maximum payload chunk size defined by the NFC NDEF specification, i.e. 2^32-1 octets.
 */
- (instancetype)initWithFormat:(NFCTypeNameFormat)format type:(NSData *)type identifier:(NSData *)identifier payload:(NSData *)payload API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method initWithFormat:type:identifier:paylaod:
 *
 * @param format        NFCTypeNameFormat value.
 * @param type          Identifier describing the type of the payload.  Empty data indicates field is absent from the payload.
 * @param identifier    Identifier in the form of a URI reference.  Empty data indicates field is absent from the payload.
 * @param payload       Payload data.  Empty data indicates field is absent from the payload.
 * @param chunkSize     Maximum size of a payload chunk.  0 means no chunking on the payload, i.e. payload is fit in a single record.
 */
- (instancetype)initWithFormat:(NFCTypeNameFormat)format type:(NSData *)type identifier:(NSData *)identifier payload:(NSData *)payload chunkSize:(size_t)chunkSize API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end


@interface NFCNDEFPayload (ConvenienceHelpers)

/*!
 * @method wellKnownTypeURIRecordWithString:
 *
 * @param uri       URI string.  UTF-8 encoding representation will be used.
 *
 * @discussion      Used for creating NDEF URI payloads which cannot be represented with NSURL object.  These are URIs that contain characters
 *                  such as 'ä' and 'ö' which cannot be represent by the 7 bits ASCII encoding.
 */
+ (_Nullable instancetype)wellKnownTypeURIPayloadWithString:(NSString *)uri API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method wellKnownTypeURIPayloadWithURL:
 *
 * @param url       NSURL object.
 *
 * @discussion      Preferred convenience function for creating NDEF URI payload with common URLs such as "https://www.apple.com" or "tel:+1-555-555-5555".
 */
+ (_Nullable instancetype)wellKnownTypeURIPayloadWithURL:(NSURL *)url API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method wellKnownTypeTextPayloadWithString:locale:
 *
 * @param text      Text message.
 * @param locale    NSLocale object.  IANA language code specified by the locale will be saved with the payload.
 */
+ (_Nullable instancetype)wellKnownTypeTextPayloadWithString:(NSString *)text locale:(NSLocale *)locale API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);
+ (_Nullable instancetype)wellKnowTypeTextPayloadWithString:(NSString *)text locale:(NSLocale *)locale API_UNAVAILABLE(watchos, macos, tvos) API_DEPRECATED_WITH_REPLACEMENT("-wellKnownTypeTextPayloadWithString:locale", ios(13.0, 13.0));

/*!
 * @method      wellKnownTypeURIPayload
 *
 * @return      NSURL object base on a valid Well Known Type URI payload. nil if payload is not a URI.
 */
- (NSURL * _Nullable)wellKnownTypeURIPayload API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

/*!
 * @method wellKnownTypeTextPayloadWithLocale:
 *
 * @param locale    Returns NSLocale object that is constructed from the IANA language code stored with the text payload.
 * @return          NSString object base on a valid Well Known Type Text payload.  nil if payload is not a text.
 */
- (NSString * _Nullable)wellKnownTypeTextPayloadWithLocale:(NSLocale * _Nullable * _Nonnull)locale API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, macos, tvos);

@end
NS_ASSUME_NONNULL_END

#endif /* NFCNDEFPayload_h */
