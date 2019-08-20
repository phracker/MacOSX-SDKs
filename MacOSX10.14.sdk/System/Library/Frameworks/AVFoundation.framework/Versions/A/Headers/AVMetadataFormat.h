/*
    File:  AVMetadataFormat.h

    Framework:  AVFoundation
 
    Copyright 2010-2017 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

typedef NSString * AVMetadataFormat NS_STRING_ENUM;
typedef NSString * AVMetadataKeySpace NS_EXTENSIBLE_STRING_ENUM;
typedef NSString * AVMetadataKey NS_EXTENSIBLE_STRING_ENUM;

// CommonMetadata
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceCommon                                 NS_AVAILABLE(10_7, 4_0);

// Metadata common keys
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyTitle                                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyCreator                                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeySubject                                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyDescription                                NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyPublisher                                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyContributor                                NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyCreationDate                               NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyLastModifiedDate                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyType                                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyFormat                                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyIdentifier                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeySource                                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyLanguage                                   NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyRelation                                   NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyLocation                                   NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyCopyrights                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyAlbumName                                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyAuthor                                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyArtist                                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyArtwork                                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyMake                                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeyModel                                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataCommonKeySoftware                                   NS_AVAILABLE(10_7, 4_0);

// QuickTimeUserData
AVF_EXPORT AVMetadataFormat const AVMetadataFormatQuickTimeUserData                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceQuickTimeUserData                      NS_AVAILABLE(10_7, 4_0);

// QuickTimeUserData keys
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyAlbum                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyArranger                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyArtist                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyAuthor                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyChapter                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyComment                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyComposer                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyCopyright                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyCreationDate                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyDescription                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyDirector                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyDisclaimer                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyEncodedBy                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyFullName                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyGenre                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyHostComputer                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyInformation                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyKeywords                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyMake                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyModel                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyOriginalArtist                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyOriginalFormat                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyOriginalSource                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyPerformers                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyProducer                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyPublisher                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyProduct                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeySoftware                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeySpecialPlaybackRequirements     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyTrack                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyWarning                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyWriter                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyURLLink                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyLocationISO6709                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyTrackName                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyCredits                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyPhonogramRights                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeUserDataKeyTaggedCharacteristic            NS_AVAILABLE(10_8, 5_0);

// ISO UserData
AVF_EXPORT AVMetadataFormat const AVMetadataFormatISOUserData                                NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceISOUserData                            NS_AVAILABLE(10_9, 7_0);

// ISO UserData keys (includes 3GPP keys)
AVF_EXPORT AVMetadataKey const AVMetadataISOUserDataKeyCopyright                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataISOUserDataKeyTaggedCharacteristic                  NS_AVAILABLE(10_10, 8_0);

/*!
 @constant		AVMetadataISOUserDataKeyDate
 @abstract		ISO User data key for the content creation date/time.
 @discussion	The value is date and time, formatted according to ISO 8601, when the content was created. For clips captured by recording devices, this is typically the date and time when the clip’s recording started. When stored in AV(Mutable)MetadataItem, the value type must be either NSDate or NSString. When NSString is used, the value uses one of ISO 8601 formats such as "2016-01-11T17:31:10Z".
*/
AVF_EXPORT AVMetadataKey const AVMetadataISOUserDataKeyDate                                  NS_AVAILABLE(10_12, 10_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyCopyright                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyAuthor                                NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyPerformer                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyGenre                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyRecordingYear                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyLocation                              NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyTitle                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyDescription                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyCollection                            NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyUserRating                            NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyThumbnail                             NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyAlbumAndTrack                         NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyKeywordList                           NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyMediaClassification                   NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVMetadataKey const AVMetadata3GPUserDataKeyMediaRating                           NS_AVAILABLE(10_9, 7_0);

// QuickTimeMetadata
AVF_EXPORT AVMetadataFormat const AVMetadataFormatQuickTimeMetadata                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceQuickTimeMetadata                      NS_AVAILABLE(10_7, 4_0);

// QuickTimeMetadata keys. For more information, see the QuickTime File Format Specification, available as part of the Mac OS X Reference Library at http://developer.apple.com/library/mac/navigation/
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyAuthor                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyComment                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCopyright                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCreationDate                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyDirector                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyDisplayName                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyInformation                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyKeywords                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyProducer                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyPublisher                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyAlbum                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyArtist                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyArtwork                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyDescription                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeySoftware                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyYear                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyGenre                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyiXML                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationISO6709                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyMake                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyModel                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyArranger                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyEncodedBy                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyOriginalArtist                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyPerformer                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyComposer                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCredits                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyPhonogramRights                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCameraIdentifier                NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCameraFrameReadoutTime          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyTitle                           NS_AVAILABLE(10_7, 4_3);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyCollectionUser                  NS_AVAILABLE(10_7, 4_3);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyRatingUser                      NS_AVAILABLE(10_7, 4_3);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationName                    NS_AVAILABLE(10_7, 4_3);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationBody                    NS_AVAILABLE(10_7, 4_3);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationNote                    NS_AVAILABLE(10_7, 4_3);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationRole                    NS_AVAILABLE(10_7, 4_3);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyLocationDate                    NS_AVAILABLE(10_7, 4_3);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyDirectionFacing                 NS_AVAILABLE(10_7, 4_3);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyDirectionMotion                 NS_AVAILABLE(10_7, 4_3);
AVF_EXPORT AVMetadataKey const AVMetadataQuickTimeMetadataKeyContentIdentifier               NS_AVAILABLE(10_11, 9_0);

// iTunesMetadata
AVF_EXPORT AVMetadataFormat const AVMetadataFormatiTunesMetadata                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceiTunes                                 NS_AVAILABLE(10_7, 4_0);

// iTunesMetadata keys
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAlbum                              NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyArtist                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyUserComment                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyCoverArt                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyCopyright                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyReleaseDate                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyEncodedBy                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyPredefinedGenre                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyUserGenre                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeySongName                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyTrackSubTitle                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyEncodingTool                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyComposer                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAlbumArtist                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAccountKind                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAppleID                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyArtistID                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeySongID                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyDiscCompilation                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyDiscNumber                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyGenreID                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyGrouping                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyPlaylistID                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyContentRating                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyBeatsPerMin                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyTrackNumber                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyArtDirector                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyArranger                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAuthor                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyLyrics                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyAcknowledgement                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyConductor                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyDescription                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyDirector                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyEQ                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyLinerNotes                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyRecordCompany                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyOriginalArtist                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyPhonogramRights                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyProducer                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyPerformer                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyPublisher                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeySoundEngineer                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeySoloist                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyCredits                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyThanks                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyOnlineExtras                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataiTunesMetadataKeyExecProducer                       NS_AVAILABLE(10_7, 4_0);

// ID3Metadata
AVF_EXPORT AVMetadataFormat const AVMetadataFormatID3Metadata                                NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceID3                                    NS_AVAILABLE(10_7, 4_0);

// ID3Metadata keys
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyAudioEncryption                       /* AENC Audio encryption */                                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyAttachedPicture                       /* APIC Attached picture */                                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyAudioSeekPointIndex                   /* ASPI Audio seek point index */                               NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyComments                              /* COMM Comments */                                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyCommercial                            /* COMR Commercial frame */                                     NS_AVAILABLE(10_11, 9_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyCommerical                            /* COMR Commercial frame */                                     NS_DEPRECATED(10_7, 10_11, 4_0, 9_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEncryption                            /* ENCR Encryption method registration */                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEqualization                          /* EQUA Equalization */                                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEqualization2                         /* EQU2 Equalisation (2) */                                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEventTimingCodes                      /* ETCO Event timing codes */                                   NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyGeneralEncapsulatedObject             /* GEOB General encapsulated object */                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyGroupIdentifier                       /* GRID Group identification registration */                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInvolvedPeopleList_v23                /* IPLS Involved people list */                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyLink                                  /* LINK Linked information */                                   NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyMusicCDIdentifier                     /* MCDI Music CD identifier */                                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyMPEGLocationLookupTable               /* MLLT MPEG location lookup table */                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOwnership                             /* OWNE Ownership frame */                                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPrivate                               /* PRIV Private frame */                                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPlayCounter                           /* PCNT Play counter */                                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPopularimeter                         /* POPM Popularimeter */                                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPositionSynchronization               /* POSS Position synchronisation frame */                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyRecommendedBufferSize                 /* RBUF Recommended buffer size */                              NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyRelativeVolumeAdjustment              /* RVAD Relative volume adjustment */                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyRelativeVolumeAdjustment2             /* RVA2 Relative volume adjustment (2) */                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyReverb                                /* RVRB Reverb */                                               NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySeek                                  /* SEEK Seek frame */                                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySignature                             /* SIGN Signature frame */                                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySynchronizedLyric                     /* SYLT Synchronized lyric/text */                              NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySynchronizedTempoCodes                /* SYTC Synchronized tempo codes */                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyAlbumTitle                            /* TALB Album/Movie/Show title */                               NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyBeatsPerMinute                        /* TBPM BPM (beats per minute) */                               NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyComposer                              /* TCOM Composer */                                             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyContentType                           /* TCON Content type */                                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyCopyright                             /* TCOP Copyright message */                                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyDate                                  /* TDAT Date */                                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEncodingTime                          /* TDEN Encoding time */                                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPlaylistDelay                         /* TDLY Playlist delay */                                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalReleaseTime                   /* TDOR Original release time */                                NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyRecordingTime                         /* TDRC Recording time */                                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyReleaseTime                           /* TDRL Release time */                                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTaggingTime                           /* TDTG Tagging time */                                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEncodedBy                             /* TENC Encoded by */                                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyLyricist                              /* TEXT Lyricist/Text writer */                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyFileType                              /* TFLT File type */                                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTime                                  /* TIME Time */                                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInvolvedPeopleList_v24                /* TIPL Involved people list */                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyContentGroupDescription               /* TIT1 Content group description */                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTitleDescription                      /* TIT2 Title/songname/content description */                   NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySubTitle                              /* TIT3 Subtitle/Description refinement */                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInitialKey                            /* TKEY Initial key */                                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyLanguage                              /* TLAN Language(s) */                                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyLength                                /* TLEN Length */                                               NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyMusicianCreditsList                   /* TMCL Musician credits list */                                NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyMediaType                             /* TMED Media type */                                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyMood                                  /* TMOO Mood */                                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalAlbumTitle                    /* TOAL Original album/movie/show title */                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalFilename                      /* TOFN Original filename */                                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalLyricist                      /* TOLY Original lyricist(s)/text writer(s) */                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalArtist                        /* TOPE Original artist(s)/performer(s) */                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOriginalReleaseYear                   /* TORY Original release year */                                NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyFileOwner                             /* TOWN File owner/licensee */                                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyLeadPerformer                         /* TPE1 Lead performer(s)/Soloist(s) */                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyBand                                  /* TPE2 Band/orchestra/accompaniment */                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyConductor                             /* TPE3 Conductor/performer refinement */                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyModifiedBy                            /* TPE4 Interpreted, remixed, or otherwise modified by */       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPartOfASet                            /* TPOS Part of a set */                                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyProducedNotice                        /* TPRO Produced notice */                                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPublisher                             /* TPUB Publisher */                                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTrackNumber                           /* TRCK Track number/Position in set */                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyRecordingDates                        /* TRDA Recording dates */                                      NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInternetRadioStationName              /* TRSN Internet radio station name */                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInternetRadioStationOwner             /* TRSO Internet radio station owner */                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySize                                  /* TSIZ Size */                                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyAlbumSortOrder                        /* TSOA Album sort order */                                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPerformerSortOrder                    /* TSOP Performer sort order */                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTitleSortOrder                        /* TSOT Title sort order */                                     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyInternationalStandardRecordingCode    /* TSRC ISRC (international standard recording code) */         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyEncodedWith                           /* TSSE Software/Hardware and settings used for encoding */     NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeySetSubtitle                           /* TSST Set subtitle */                                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyYear                                  /* TYER Year */                                                 NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyUserText                              /* TXXX User defined text information frame */                  NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyUniqueFileIdentifier                  /* UFID Unique file identifier */                               NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyTermsOfUse                            /* USER Terms of use */                                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyUnsynchronizedLyric                   /* USLT Unsynchronized lyric/text transcription */              NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyCommercialInformation                 /* WCOM Commercial information */                               NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyCopyrightInformation                  /* WCOP Copyright/Legal information */                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOfficialAudioFileWebpage              /* WOAF Official audio file webpage */                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOfficialArtistWebpage                 /* WOAR Official artist/performer webpage */                    NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOfficialAudioSourceWebpage            /* WOAS Official audio source webpage */                        NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOfficialInternetRadioStationHomepage  /* WORS Official Internet radio station homepage */             NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyPayment                               /* WPAY Payment */                                              NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyOfficialPublisherWebpage              /* WPUB Publishers official webpage */                          NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT AVMetadataKey const AVMetadataID3MetadataKeyUserURL                               /* WXXX User defined URL link frame */                          NS_AVAILABLE(10_7, 4_0);

// Icecast/ShoutCAST streaming metadata
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceIcy                                    NS_AVAILABLE(10_10, 8_0);

AVF_EXPORT AVMetadataKey const AVMetadataIcyMetadataKeyStreamTitle                           NS_AVAILABLE(10_10, 8_0);
AVF_EXPORT AVMetadataKey const AVMetadataIcyMetadataKeyStreamURL                             NS_AVAILABLE(10_10, 8_0);

// HTTP Live Streaming metadata
AVF_EXPORT AVMetadataFormat const AVMetadataFormatHLSMetadata                                NS_AVAILABLE(10_10, 8_0);
// HLS Metadata does not define its own keySpace or keys. Use of the keySpace AVMetadataKeySpaceQuickTimeMetadata and its keys is recommended.
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceHLSDateRange                           NS_AVAILABLE(10_11_3, 9_3);

// Keys for metadata provided by AudioToolbox's AudioFile interface. See <AudioToolbox/AudioFile.h>
AVF_EXPORT AVMetadataKeySpace const AVMetadataKeySpaceAudioFile                              NS_AVAILABLE(10_13, 11_0);

// Metadata format for AVMetadataItems of unknown provenance. This can occur when metadata is provided generically by an intermediate interface, such as AudioToolbox's AudioFile interface.
AVF_EXPORT AVMetadataFormat const AVMetadataFormatUnknown                                    NS_AVAILABLE(10_13, 11_0);

// Extra attribute keys
typedef NSString * AVMetadataExtraAttributeKey NS_EXTENSIBLE_STRING_ENUM;

/*!
 @constant		AVMetadataExtraAttributeValueURIKey
 @abstract
	When present in an item's extraAttributes dictionary, identifies the resource to be used as the item's value. Values for this key are of type NSString.
*/
AVF_EXPORT AVMetadataExtraAttributeKey const AVMetadataExtraAttributeValueURIKey             NS_AVAILABLE(10_10, 8_0);

/*!
 @constant		AVMetadataExtraAttributeBaseURIKey
 @abstract
	When present in an item's extraAttributes dictionary, identifies the base URI against which other URIs related to the item are to be resolved, e.g. AVMetadataExtraAttributeValueURIKey. Values for this key are of type NSString.
*/
AVF_EXPORT AVMetadataExtraAttributeKey const AVMetadataExtraAttributeBaseURIKey              NS_AVAILABLE(10_10, 8_0);

/*!
	@constant		AVMetadataExtraAttributeInfoKey
	@abstract		More information about the item; specific to the 
					item keySpace & key.
	@discussion		For example, this key is used with the following ID3 tags:
					TXXX, WXXX, APIC, GEOB: carries the Description
					PRIV: carries the Owner Identifier
 */
AVF_EXPORT AVMetadataExtraAttributeKey const AVMetadataExtraAttributeInfoKey                 NS_AVAILABLE(10_11, 9_0);

