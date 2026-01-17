#if !__has_include(<AVFCore/AVMetadataFormat.h>)
/*
    File:  AVMetadataFormat.h

    Framework:  AVFoundation
 
    Copyright 2010-2025 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

typedef NSString * AVMetadataFormat NS_STRING_ENUM;
typedef NSString * AVMetadataKeySpace NS_EXTENSIBLE_STRING_ENUM;
typedef NSString * AVMetadataKey NS_EXTENSIBLE_STRING_ENUM;

// CommonMetadata
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceCommon                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));

// Metadata common keys
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyTitle                                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyCreator                                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeySubject                                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyDescription                                API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyPublisher                                  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyContributor                                API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyCreationDate                               API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyLastModifiedDate                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyType                                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyFormat                                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyIdentifier                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeySource                                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyLanguage                                   API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyRelation                                   API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyLocation                                   API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyCopyrights                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyAlbumName                                  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyAuthor                                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyArtist                                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyArtwork                                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyMake                                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyModel                                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeySoftware                                   API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyAccessibilityDescription                   API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0), visionos(1.0));

// QuickTimeUserData
AVF_EXPORT AVMetadataFormat const AVMetadataFormatQuickTimeUserData                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceQuickTimeUserData                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));

// QuickTimeUserData keys
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyAlbum                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyArranger                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyArtist                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyAuthor                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyChapter                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyComment                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyComposer                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyCopyright                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyCreationDate                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyDescription                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyDirector                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyDisclaimer                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyEncodedBy                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyFullName                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyGenre                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyHostComputer                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyInformation                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyKeywords                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyMake                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyModel                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyOriginalArtist                  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyOriginalFormat                  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyOriginalSource                  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyPerformers                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyProducer                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyPublisher                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyProduct                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeySoftware                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeySpecialPlaybackRequirements     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyTrack                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyWarning                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyWriter                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyURLLink                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyLocationISO6709                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyTrackName                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyCredits                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyPhonogramRights                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyTaggedCharacteristic            API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyAccessibilityDescription        API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0), visionos(1.0));

// ISO UserData
AVF_EXPORT AVMetadataFormat const AVMetadataFormatISOUserData                                API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceISOUserData                            API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

// ISO UserData keys (includes 3GPP keys)
AVF_EXPORT AVMetadataKey const AVMetadataISOUserDataKeyCopyright                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataISOUserDataKeyTaggedCharacteristic                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// ISO User data key for the content creation date/time.
/// 
/// The value is date and time, formatted according to ISO 8601, when the content was created. For clips captured by recording devices, this is typically the date and time when the clip’s recording started. When stored in AV(Mutable)MetadataItem, the value type must be either NSDate or NSString. When NSString is used, the value uses one of ISO 8601 formats such as "2016-01-11T17:31:10Z".
AVF_EXPORT AVMetadataKey const AVMetadataISOUserDataKeyDate                                  API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataISOUserDataKeyAccessibilityDescription              API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyCopyright                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyAuthor                                API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyPerformer                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyGenre                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyRecordingYear                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyLocation                              API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyTitle                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyDescription                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyCollection                            API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyUserRating                            API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyThumbnail                             API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyAlbumAndTrack                         API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyKeywordList                           API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyMediaClassification                   API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyMediaRating                           API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

// QuickTimeMetadata
AVF_EXPORT AVMetadataFormat const AVMetadataFormatQuickTimeMetadata                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceQuickTimeMetadata                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));

// QuickTimeMetadata keys. For more information, see the QuickTime File Format Specification, available as part of the Mac OS X Reference Library at http://developer.apple.com/library/mac/navigation/
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyAuthor                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyComment                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCopyright                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCreationDate                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyDirector                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyDisplayName                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyInformation                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyKeywords                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyProducer                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyPublisher                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyAlbum                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyArtist                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyArtwork                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyDescription                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeySoftware                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyYear                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyGenre                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyiXML                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationISO6709                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyMake                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyModel                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyArranger                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyEncodedBy                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyOriginalArtist                  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyPerformer                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyComposer                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCredits                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyPhonogramRights                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCameraIdentifier                API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCameraFrameReadoutTime          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyTitle                           API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCollectionUser                  API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyRatingUser                      API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationName                    API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationBody                    API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationNote                    API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationRole                    API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationDate                    API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyDirectionFacing                 API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyDirectionMotion                 API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyContentIdentifier               API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyAccessibilityDescription        API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyIsMontage                       API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// A value of type kCMMetadataBaseDataType_UInt8 indicating whether this movie is intended to be played back at the full frame rate (1), or at a slow motion rate (0).
/// 
/// Historically, some apps have played movies recorded at frame rates of 120fps or higher in slow motion by default. With the introduction of this metadata, apps that record high-frame-rate movies may add this movie-level metadata to indicate whether the movie is intended to be played at the full frame rate (1) or at a slow motion rate (0). Apps that play movies may use this metadata, when present, to guide their behavior.
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyFullFrameRatePlaybackIntent     API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/// A value of type `kCMMetadataBaseDataType_UInt8` indicating whether this movie is intended as a Cinematic Video (1) or not (0).
/// 
/// This movie-level metadata is automatically added (with a value of 1) to a movie recorded using the Cinematic Video API. Clients can override it with a value of 0 to signal that this movie is not to be treated as a Cinematic Video by Apple's software like Photos.
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCinematicVideoIntent            API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));


/// A value of type kCMMetadataBaseDataType_UTF8 indicating the sensitivity of the camera to light in terms of ISO exposure index (e.g. "800"). See SMPTE RDD 18.
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCameraISOSensitivity            API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// A value of type kCMMetadataBaseDataType_UTF8 indicating the white balance value defined by the temperature in Kelvin units (e.g. "5500K" or "5500"). See SMPTE RDD 18.
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCameraWhiteBalance              API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// A value of type kCMMetadataBaseDataType_RawData indicating the reference white balance multiplication factor data for ProRes RAW.
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyWhiteBalanceByCCTWhiteBalanceFactors       API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// A value of type kCMMetadataBaseDataType_RawData indicating the reference color translation matrix data for ProRes RAW.
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyWhiteBalanceByCCTColorMatrices  API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// A value of type kCMMetadataBaseDataType_UTF8 indicating the exposure period expressed as an angle in minutes (1/60 degree) (e.g. "21600" or "360.00deg"").
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCameraShutterSpeedAngle                    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// A value of type kCMMetadataBaseDataType_UTF8 indicating the exposure period expressed as a time per one frame/field period in seconds.
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCameraShutterSpeedTime          API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// A value of type kCMMetadataBaseDataType_UTF8 indicating measure of the amount of light transmitted through the lens. It is the focal length divided by the effective lens aperture diameter (e.g. "F2.8" or "2.8").
/// 
/// This is track-level metadata for video track that is associated with the camera.
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCameraLensIrisFNumber           API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));


/// A value of type kCMMetadataBaseDataType_UTF8 indicating the lens model (e.g. "iPhone 16 Pro back camera 6.765mm f/1.78").
/// 
/// This is track-level metadata for video track that is associated with the camera.
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCameraLensModel                 API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// A value of type kCMMetadataBaseDataType_UTF8 indicating focal length normalized to the 35mm film equivalent value (e.g. "50.00mm").
/// 
/// This is track-level metadata for video track that is associated with the camera.
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCameraFocalLength35mmEquivalent API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

// iTunesMetadata
AVF_EXPORT AVMetadataFormat const AVMetadataFormatiTunesMetadata                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceiTunes                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));

// iTunesMetadata keys
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAlbum                              API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyArtist                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyUserComment                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyCoverArt                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyCopyright                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyReleaseDate                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyEncodedBy                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyPredefinedGenre                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyUserGenre                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeySongName                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyTrackSubTitle                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyEncodingTool                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyComposer                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAlbumArtist                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAccountKind                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAppleID                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyArtistID                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeySongID                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyDiscCompilation                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyDiscNumber                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyGenreID                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyGrouping                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyPlaylistID                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyContentRating                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyBeatsPerMin                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyTrackNumber                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyArtDirector                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyArranger                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAuthor                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyLyrics                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAcknowledgement                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyConductor                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyDescription                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyDirector                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyEQ                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyLinerNotes                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyRecordCompany                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyOriginalArtist                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyPhonogramRights                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyProducer                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyPerformer                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyPublisher                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeySoundEngineer                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeySoloist                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyCredits                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyThanks                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyOnlineExtras                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyExecProducer                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));

// ID3Metadata
AVF_EXPORT AVMetadataFormat const AVMetadataFormatID3Metadata                                API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceID3                                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));

// ID3Metadata keys
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyAudioEncryption                       /* AENC Audio encryption */                                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyAttachedPicture                       /* APIC Attached picture */                                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyAudioSeekPointIndex                   /* ASPI Audio seek point index */                               API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyComments                              /* COMM Comments */                                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyCommercial                            /* COMR Commercial frame */                                     API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyCommerical                            /* COMR Commercial frame */                                     API_DEPRECATED_WITH_REPLACEMENT("AVMetadataID3MetadataKeyCommercial", macos(10.7, 10.11), ios(4.0, 9.0), tvos(9.0, 9.0), watchos(1.0, 1.0)) API_UNAVAILABLE(visionos);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEncryption                            /* ENCR Encryption method registration */                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEqualization                          /* EQUA Equalization */                                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEqualization2                         /* EQU2 Equalisation (2) */                                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEventTimingCodes                      /* ETCO Event timing codes */                                   API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyGeneralEncapsulatedObject             /* GEOB General encapsulated object */                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyGroupIdentifier                       /* GRID Group identification registration */                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInvolvedPeopleList_v23                /* IPLS Involved people list */                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyLink                                  /* LINK Linked information */                                   API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyMusicCDIdentifier                     /* MCDI Music CD identifier */                                  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyMPEGLocationLookupTable               /* MLLT MPEG location lookup table */                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOwnership                             /* OWNE Ownership frame */                                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPrivate                               /* PRIV Private frame */                                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPlayCounter                           /* PCNT Play counter */                                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPopularimeter                         /* POPM Popularimeter */                                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPositionSynchronization               /* POSS Position synchronisation frame */                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyRecommendedBufferSize                 /* RBUF Recommended buffer size */                              API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyRelativeVolumeAdjustment              /* RVAD Relative volume adjustment */                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyRelativeVolumeAdjustment2             /* RVA2 Relative volume adjustment (2) */                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyReverb                                /* RVRB Reverb */                                               API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySeek                                  /* SEEK Seek frame */                                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySignature                             /* SIGN Signature frame */                                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySynchronizedLyric                     /* SYLT Synchronized lyric/text */                              API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySynchronizedTempoCodes                /* SYTC Synchronized tempo codes */                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyAlbumTitle                            /* TALB Album/Movie/Show title */                               API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyBeatsPerMinute                        /* TBPM BPM (beats per minute) */                               API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyComposer                              /* TCOM Composer */                                             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyContentType                           /* TCON Content type */                                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyCopyright                             /* TCOP Copyright message */                                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyDate                                  /* TDAT Date */                                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEncodingTime                          /* TDEN Encoding time */                                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPlaylistDelay                         /* TDLY Playlist delay */                                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalReleaseTime                   /* TDOR Original release time */                                API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyRecordingTime                         /* TDRC Recording time */                                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyReleaseTime                           /* TDRL Release time */                                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTaggingTime                           /* TDTG Tagging time */                                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEncodedBy                             /* TENC Encoded by */                                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyLyricist                              /* TEXT Lyricist/Text writer */                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyFileType                              /* TFLT File type */                                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTime                                  /* TIME Time */                                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInvolvedPeopleList_v24                /* TIPL Involved people list */                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyContentGroupDescription               /* TIT1 Content group description */                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTitleDescription                      /* TIT2 Title/songname/content description */                   API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySubTitle                              /* TIT3 Subtitle/Description refinement */                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInitialKey                            /* TKEY Initial key */                                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyLanguage                              /* TLAN Language(s) */                                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyLength                                /* TLEN Length */                                               API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyMusicianCreditsList                   /* TMCL Musician credits list */                                API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyMediaType                             /* TMED Media type */                                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyMood                                  /* TMOO Mood */                                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalAlbumTitle                    /* TOAL Original album/movie/show title */                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalFilename                      /* TOFN Original filename */                                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalLyricist                      /* TOLY Original lyricist(s)/text writer(s) */                  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalArtist                        /* TOPE Original artist(s)/performer(s) */                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalReleaseYear                   /* TORY Original release year */                                API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyFileOwner                             /* TOWN File owner/licensee */                                  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyLeadPerformer                         /* TPE1 Lead performer(s)/Soloist(s) */                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyBand                                  /* TPE2 Band/orchestra/accompaniment */                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyConductor                             /* TPE3 Conductor/performer refinement */                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyModifiedBy                            /* TPE4 Interpreted, remixed, or otherwise modified by */       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPartOfASet                            /* TPOS Part of a set */                                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyProducedNotice                        /* TPRO Produced notice */                                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPublisher                             /* TPUB Publisher */                                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTrackNumber                           /* TRCK Track number/Position in set */                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyRecordingDates                        /* TRDA Recording dates */                                      API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInternetRadioStationName              /* TRSN Internet radio station name */                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInternetRadioStationOwner             /* TRSO Internet radio station owner */                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySize                                  /* TSIZ Size */                                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyAlbumSortOrder                        /* TSOA Album sort order */                                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPerformerSortOrder                    /* TSOP Performer sort order */                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTitleSortOrder                        /* TSOT Title sort order */                                     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInternationalStandardRecordingCode    /* TSRC ISRC (international standard recording code) */         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEncodedWith                           /* TSSE Software/Hardware and settings used for encoding */     API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySetSubtitle                           /* TSST Set subtitle */                                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyYear                                  /* TYER Year */                                                 API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyUserText                              /* TXXX User defined text information frame */                  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyUniqueFileIdentifier                  /* UFID Unique file identifier */                               API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTermsOfUse                            /* USER Terms of use */                                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyUnsynchronizedLyric                   /* USLT Unsynchronized lyric/text transcription */              API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyCommercialInformation                 /* WCOM Commercial information */                               API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyCopyrightInformation                  /* WCOP Copyright/Legal information */                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOfficialAudioFileWebpage              /* WOAF Official audio file webpage */                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOfficialArtistWebpage                 /* WOAR Official artist/performer webpage */                    API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOfficialAudioSourceWebpage            /* WOAS Official audio source webpage */                        API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOfficialInternetRadioStationHomepage  /* WORS Official Internet radio station homepage */             API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPayment                               /* WPAY Payment */                                              API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOfficialPublisherWebpage              /* WPUB Publishers official webpage */                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyUserURL                               /* WXXX User defined URL link frame */                          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Icecast/ShoutCAST streaming metadata
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceIcy                                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

AVF_EXPORT AVMetadataKey const AVMetadataIcyMetadataKeyStreamTitle                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));
AVF_EXPORT AVMetadataKey const AVMetadataIcyMetadataKeyStreamURL                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// HTTP Live Streaming metadata
AVF_EXPORT AVMetadataFormat const AVMetadataFormatHLSMetadata                                API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));
/// HLS Metadata does not define its own keySpace or keys. Use of the keySpace AVMetadataKeySpaceQuickTimeMetadata and its keys is recommended.
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceHLSDateRange                           API_AVAILABLE(macos(10.11.3), ios(9.3), tvos(9.2), watchos(2.3), visionos(1.0));

/// Keys for metadata provided by AudioToolbox's AudioFile interface. See <AudioToolbox/AudioFile.h>
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceAudioFile                              API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0));

/// Metadata format for AVMetadataItems of unknown provenance. This can occur when metadata is provided generically by an intermediate interface, such as AudioToolbox's AudioFile interface.
AVF_EXPORT AVMetadataFormat const AVMetadataFormatUnknown                                    API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0));

/// Extra attribute keys
typedef NSString * AVMetadataExtraAttributeKey NS_EXTENSIBLE_STRING_ENUM;

/// When present in an item's extraAttributes dictionary, identifies the resource to be used as the item's value. Values for this key are of type NSString.
AVF_EXPORT AVMetadataExtraAttributeKey const AVMetadataExtraAttributeValueURIKey             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// When present in an item's extraAttributes dictionary, identifies the base URI against which other URIs related to the item are to be resolved, e.g. AVMetadataExtraAttributeValueURIKey. Values for this key are of type NSString.
AVF_EXPORT AVMetadataExtraAttributeKey const AVMetadataExtraAttributeBaseURIKey              API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// More information about the item; specific to the item keySpace & key.
/// 
/// For example, this key is used with the following ID3 tags:
/// TXXX, WXXX, APIC, GEOB: carries the Description
/// PRIV: carries the Owner Identifier
AVF_EXPORT AVMetadataExtraAttributeKey const AVMetadataExtraAttributeInfoKey                 API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

#else
#import <AVFCore/AVMetadataFormat.h>
#endif
