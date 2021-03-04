#if !__has_include(<AVFCore/AVMetadataIdentifiers.h>)
/*
    File:		AVMetadataIdentifiers.h

    Framework:  AVFoundation
 
    Copyright 2014-2019 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

typedef NSString * AVMetadataIdentifier NS_EXTENSIBLE_STRING_ENUM;

// CommonMetadata
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierTitle                                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierCreator                                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierSubject                                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierDescription                                API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierPublisher                                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierContributor                                API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierCreationDate                               API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierLastModifiedDate                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierType                                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierFormat                                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierAssetIdentifier                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierSource                                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierLanguage                                   API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierRelation                                   API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierLocation                                   API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierCopyrights                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierAlbumName                                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierAuthor                                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierArtist                                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierArtwork                                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierMake                                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierModel                                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierSoftware                                   API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataCommonIdentifierAccessibilityDescription                   API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0));

// QuickTimeUserData
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataAlbum                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataArranger                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataArtist                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataAuthor                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataChapter                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataComment                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataComposer                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataCopyright                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataCreationDate                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataDescription                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataDirector                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataDisclaimer                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataEncodedBy                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataFullName                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataGenre                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataHostComputer                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataInformation                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataKeywords                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataMake                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataModel                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataOriginalArtist                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataOriginalFormat                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataOriginalSource                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataPerformers                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataProducer                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataPublisher                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataProduct                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataSoftware                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataSpecialPlaybackRequirements     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataTrack                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataWarning                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataWriter                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataURLLink                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataLocationISO6709                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataTrackName                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataCredits                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataPhonogramRights                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataTaggedCharacteristic            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeUserDataAccessibilityDescription        API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0));

// ISO UserData (includes 3GPP)
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierISOUserDataCopyright                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierISOUserDataDate                                  API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierISOUserDataTaggedCharacteristic                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierISOUserDataAccessibilityDescription              API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataCopyright                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataAuthor                                API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataPerformer                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataGenre                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataRecordingYear                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataLocation                              API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataTitle                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataDescription                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataCollection                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataUserRating                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataThumbnail                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataAlbumAndTrack                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataKeywordList                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataMediaClassification                   API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifier3GPUserDataMediaRating                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));

// QuickTimeMetadata. For more information, see the QuickTime File Format Specification, available as part of the Mac OS X Reference Library at http://developer.apple.com/library/mac/navigation/
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataAuthor                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataComment                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataCopyright                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataCreationDate                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataDirector                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataDisplayName                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataInformation                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataKeywords                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataProducer                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataPublisher                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataAlbum                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataArtist                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataArtwork                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataDescription                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataSoftware                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataYear                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataGenre                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataiXML                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataLocationISO6709                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataMake                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataModel                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataArranger                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataEncodedBy                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataOriginalArtist                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataPerformer                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataComposer                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataCredits                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataPhonogramRights                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataCameraIdentifier                API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataCameraFrameReadoutTime          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataTitle		                   API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataCollectionUser                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataRatingUser                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataLocationName                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataLocationBody                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataLocationNote                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataLocationRole                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataLocationDate                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataDirectionFacing                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataDirectionMotion                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataPreferredAffineTransform        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataDetectedFace                    API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataDetectedHumanBody               API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(tvos, watchos);
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataDetectedCatBody                 API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(tvos, watchos);
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataDetectedDogBody                 API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(tvos, watchos);
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataDetectedSalientObject           API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(tvos, watchos);
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataVideoOrientation                API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataContentIdentifier               API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataAccessibilityDescription        API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0));

/*!
 @constant AVMetadataIdentifierQuickTimeMetadataAutoLivePhoto
 @abstract A value of type kCMMetadataBaseDataType_UInt8 indicating whether this Live Photo movie was captured in "Auto" mode.
 @discussion
   Clients capturing LivePhoto content may add this movie-level metadata to signify that the movie content should only be used (when swiping between photos, or force-touching a photo) if it's sufficiently dynamic. For instance, photos of static scenes or documents are to be excluded from the Live Photo experience.
*/
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataAutoLivePhoto                   API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));
/*!
 @constant AVMetadataIdentifierQuickTimeMetadataLivePhotoVitalityScore
 @abstract A value of type kCMMetadataBaseDataType_Float32.
 @discussion
    Live Photo movies may be algorithmically scored from 0. to 1. on their level of vitality. A Live Photo movie with a low vitality score offers little dynamism to the still photo it accompanies. The vitality score is normalized and independent of the vitality scoring version of the algorithm (see AVMetadataIdentifierQuickTimeMetadataLivePhotoVitalityScoringVersion). If a Live Photo movie contains the AVMetadataIdentifierQuickTimeMetadataAutoLivePhoto key and its value is non-zero, apps should read the AVMetadataIdentifierQuickTimeMetadataLivePhotoVitalityScore value and only display the movie's content if the score is 0.5 or higher.
    If the capture session includes a metadata output configured to provide face, dog, or cat metadata objects, their presence will greatly increase the vitality score.
*/
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataLivePhotoVitalityScore          API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @constant AVMetadataIdentifierQuickTimeMetadataLivePhotoVitalityScoringVersion
 @abstract A value of type kCMMetadataBaseDataType_UInt32.
 @discussion
    The version of the algorithm that scored the Live Photo movie for vitality.
*/
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataLivePhotoVitalityScoringVersion API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @constant AVMetadataIdentifierQuickTimeMetadataSpatialOverCaptureQualityScore
 @abstract A value of type kCMMetadataBaseDataType_Float32.
 @discussion
    The video may be scored by a heuristic which considers factors such as exposure and focus.  The value ranges from 0-1, where a score below 0.5 indicates the asset has serious flaws.
*/
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataSpatialOverCaptureQualityScore          API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @constant AVMetadataIdentifierQuickTimeMetadataSpatialOverCaptureQualityScoringVersion
 @abstract A value of type kCMMetadataBaseDataType_UInt32.
 @discussion
    The version of the algorithm that provided the spatial over capture quality score.
*/
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataSpatialOverCaptureQualityScoringVersion API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @constant AVMetadataIdentifierQuickTimeMetadataLocationHorizontalAccuracyInMeters
 @abstract A value of type kCMMetadataBaseDataType_Float32.
 @discussion
    The horizontal accuracy of the provided location data (usually specified by AVMetadataIdentifierQuickTimeMetadataLocationISO6709).
*/
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierQuickTimeMetadataLocationHorizontalAccuracyInMeters API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0));

// iTunesMetadata
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataAlbum                              API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataArtist                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataUserComment                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataCoverArt                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataCopyright                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataReleaseDate                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataEncodedBy                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataPredefinedGenre                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataUserGenre                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataSongName                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataTrackSubTitle                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataEncodingTool                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataComposer                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataAlbumArtist                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataAccountKind                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataAppleID                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataArtistID                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataSongID                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataDiscCompilation                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataDiscNumber                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataGenreID                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataGrouping                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataPlaylistID                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataContentRating                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataBeatsPerMin                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataTrackNumber                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataArtDirector                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataArranger                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataAuthor                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataLyrics                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataAcknowledgement                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataConductor                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataDescription                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataDirector                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataEQ                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataLinerNotes                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataRecordCompany                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataOriginalArtist                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataPhonogramRights                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataProducer                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataPerformer                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataPublisher                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataSoundEngineer                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataSoloist                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataCredits                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataThanks                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataOnlineExtras                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifieriTunesMetadataExecProducer                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));

// ID3Metadata
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataAudioEncryption                       /* AENC Audio encryption */                                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataAttachedPicture                       /* APIC Attached picture */                                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataAudioSeekPointIndex                   /* ASPI Audio seek point index */                               API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataComments                              /* COMM Comments */                                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataCommercial                            /* COMR Commercial frame */                                     API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataCommerical                            /* COMR Commercial frame */                                     API_DEPRECATED("No longer supported", macos(10.10, 10.11), ios(8.0, 9.0), tvos(9.0, 9.0), watchos(1.0, 1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataEncryption                            /* ENCR Encryption method registration */                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataEqualization                          /* EQUA Equalization */                                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataEqualization2                         /* EQU2 Equalisation (2) */                                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataEventTimingCodes                      /* ETCO Event timing codes */                                   API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataGeneralEncapsulatedObject             /* GEOB General encapsulated object */                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataGroupIdentifier                       /* GRID Group identification registration */                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataInvolvedPeopleList_v23                /* IPLS Involved people list */                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataLink                                  /* LINK Linked information */                                   API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataMusicCDIdentifier                     /* MCDI Music CD identifier */                                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataMPEGLocationLookupTable               /* MLLT MPEG location lookup table */                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOwnership                             /* OWNE Ownership frame */                                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataPrivate                               /* PRIV Private frame */                                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataPlayCounter                           /* PCNT Play counter */                                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataPopularimeter                         /* POPM Popularimeter */                                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataPositionSynchronization               /* POSS Position synchronisation frame */                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataRecommendedBufferSize                 /* RBUF Recommended buffer size */                              API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataRelativeVolumeAdjustment              /* RVAD Relative volume adjustment */                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataRelativeVolumeAdjustment2             /* RVA2 Relative volume adjustment (2) */                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataReverb                                /* RVRB Reverb */                                               API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataSeek                                  /* SEEK Seek frame */                                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataSignature                             /* SIGN Signature frame */                                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataSynchronizedLyric                     /* SYLT Synchronized lyric/text */                              API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataSynchronizedTempoCodes                /* SYTC Synchronized tempo codes */                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataAlbumTitle                            /* TALB Album/Movie/Show title */                               API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataBeatsPerMinute                        /* TBPM BPM (beats per minute) */                               API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataComposer                              /* TCOM Composer */                                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataContentType                           /* TCON Content type */                                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataCopyright                             /* TCOP Copyright message */                                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataDate                                  /* TDAT Date */                                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataEncodingTime                          /* TDEN Encoding time */                                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataPlaylistDelay                         /* TDLY Playlist delay */                                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOriginalReleaseTime                   /* TDOR Original release time */                                API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataRecordingTime                         /* TDRC Recording time */                                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataReleaseTime                           /* TDRL Release time */                                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataTaggingTime                           /* TDTG Tagging time */                                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataEncodedBy                             /* TENC Encoded by */                                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataLyricist                              /* TEXT Lyricist/Text writer */                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataFileType                              /* TFLT File type */                                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataTime                                  /* TIME Time */                                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataInvolvedPeopleList_v24                /* TIPL Involved people list */                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataContentGroupDescription               /* TIT1 Content group description */                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataTitleDescription                      /* TIT2 Title/songname/content description */                   API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataSubTitle                              /* TIT3 Subtitle/Description refinement */                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataInitialKey                            /* TKEY Initial key */                                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataLanguage                              /* TLAN Language(s) */                                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataLength                                /* TLEN Length */                                               API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataMusicianCreditsList                   /* TMCL Musician credits list */                                API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataMediaType                             /* TMED Media type */                                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataMood                                  /* TMOO Mood */                                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOriginalAlbumTitle                    /* TOAL Original album/movie/show title */                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOriginalFilename                      /* TOFN Original filename */                                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOriginalLyricist                      /* TOLY Original lyricist(s)/text writer(s) */                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOriginalArtist                        /* TOPE Original artist(s)/performer(s) */                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOriginalReleaseYear                   /* TORY Original release year */                                API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataFileOwner                             /* TOWN File owner/licensee */                                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataLeadPerformer                         /* TPE1 Lead performer(s)/Soloist(s) */                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataBand                                  /* TPE2 Band/orchestra/accompaniment */                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataConductor                             /* TPE3 Conductor/performer refinement */                       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataModifiedBy                            /* TPE4 Interpreted, remixed, or otherwise modified by */       API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataPartOfASet                            /* TPOS Part of a set */                                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataProducedNotice                        /* TPRO Produced notice */                                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataPublisher                             /* TPUB Publisher */                                            API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataTrackNumber                           /* TRCK Track number/Position in set */                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataRecordingDates                        /* TRDA Recording dates */                                      API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataInternetRadioStationName              /* TRSN Internet radio station name */                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataInternetRadioStationOwner             /* TRSO Internet radio station owner */                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataSize                                  /* TSIZ Size */                                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataAlbumSortOrder                        /* TSOA Album sort order */                                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataPerformerSortOrder                    /* TSOP Performer sort order */                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataTitleSortOrder                        /* TSOT Title sort order */                                     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataInternationalStandardRecordingCode    /* TSRC ISRC (international standard recording code) */         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataEncodedWith                           /* TSSE Software/Hardware and settings used for encoding */     API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataSetSubtitle                           /* TSST Set subtitle */                                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataYear                                  /* TYER Year */                                                 API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataUserText                              /* TXXX User defined text information frame */                  API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataUniqueFileIdentifier                  /* UFID Unique file identifier */                               API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataTermsOfUse                            /* USER Terms of use */                                         API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataUnsynchronizedLyric                   /* USLT Unsynchronized lyric/text transcription */              API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataCommercialInformation                 /* WCOM Commercial information */                               API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataCopyrightInformation                  /* WCOP Copyright/Legal information */                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOfficialAudioFileWebpage              /* WOAF Official audio file webpage */                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOfficialArtistWebpage                 /* WOAR Official artist/performer webpage */                    API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOfficialAudioSourceWebpage            /* WOAS Official audio source webpage */                        API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOfficialInternetRadioStationHomepage  /* WORS Official Internet radio station homepage */             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataPayment                               /* WPAY Payment */                                              API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataOfficialPublisherWebpage              /* WPUB Publishers official webpage */                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierID3MetadataUserURL                               /* WXXX User defined URL link frame */                          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));

AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierIcyMetadataStreamTitle                           API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));
AVF_EXPORT AVMetadataIdentifier const AVMetadataIdentifierIcyMetadataStreamURL                             API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));


#else
#import <AVFCore/AVMetadataIdentifiers.h>
#endif
