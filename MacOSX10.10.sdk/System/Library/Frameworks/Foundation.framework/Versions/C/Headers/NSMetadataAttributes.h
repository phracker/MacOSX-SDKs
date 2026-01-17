/*	NSMetadataAttributes.h
        Copyright (c) 2004-2014, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>

@class NSString;

// The following NSMetadataItem attributes are available on Mac OS and iOS.

FOUNDATION_EXPORT NSString * const NSMetadataItemFSNameKey NS_AVAILABLE(10_7, 5_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemDisplayNameKey NS_AVAILABLE(10_7, 5_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemURLKey NS_AVAILABLE(10_7, 5_0); // NSURL
FOUNDATION_EXPORT NSString * const NSMetadataItemPathKey NS_AVAILABLE(10_7, 5_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemFSSizeKey NS_AVAILABLE(10_7, 5_0); // file size in bytes; unsigned long long NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemFSCreationDateKey NS_AVAILABLE(10_7, 5_0); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemFSContentChangeDateKey NS_AVAILABLE(10_7, 5_0); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemContentTypeKey NS_AVAILABLE(10_9, 8_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemContentTypeTreeKey NS_AVAILABLE(10_9, 8_0); // NSArray of NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemIsUbiquitousKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber

FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemHasUnresolvedConflictsKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsDownloadedKey NS_DEPRECATED(10_7, 10_9, 5_0, 7_0, "Use NSMetadataUbiquitousItemDownloadingStatusKey instead"); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadingStatusKey NS_AVAILABLE(10_9, 7_0); // NSString ; download status of this item. The values are the three strings defined below:
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadingStatusNotDownloaded  NS_AVAILABLE(10_9, 7_0); // this item has not been downloaded yet. Use startDownloadingUbiquitousItemAtURL:error: to download it.
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadingStatusDownloaded     NS_AVAILABLE(10_9, 7_0); // there is a local version of this item available. The most current version will get downloaded as soon as possible.
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadingStatusCurrent        NS_AVAILABLE(10_9, 7_0); // there is a local version of this item and it is the most up-to-date version known to this device.
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsDownloadingKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsUploadedKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsUploadingKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemPercentDownloadedKey NS_AVAILABLE(10_7, 5_0); // double NSNumber; range [0..100]
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemPercentUploadedKey NS_AVAILABLE(10_7, 5_0); // double NSNumber; range [0..100]
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadingErrorKey NS_AVAILABLE(10_9, 7_0); // NSError; the error when downloading the item from iCloud failed, see the NSUbiquitousFile section in FoundationErrors.h
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemUploadingErrorKey NS_AVAILABLE(10_9, 7_0); // NSError; the error when uploading the item to iCloud failed, see the NSUbiquitousFile section in FoundationErrors.h
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemDownloadRequestedKey NS_AVAILABLE(10_10, 8_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsExternalDocumentKey NS_AVAILABLE(10_10, 8_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemContainerDisplayNameKey NS_AVAILABLE(10_10, 8_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemURLInLocalContainerKey NS_AVAILABLE(10_10, 8_0); // NSURL

// The following NSMetadataItem attributes are available on Mac OS for non-ubiquitious items only. The constants are equal to the corresponding ones in <Metadata/MDItem.h>.

FOUNDATION_EXPORT NSString * const NSMetadataItemAttributeChangeDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemKeywordsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemTitleKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAuthorsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemEditorsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemParticipantsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemProjectsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemDownloadedDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemWhereFromsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemCommentKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemCopyrightKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemLastUsedDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemContentCreationDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemContentModificationDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemDateAddedKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemDurationSecondsKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemContactKeywordsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemVersionKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemPixelHeightKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemPixelWidthKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemPixelCountKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemColorSpaceKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemBitsPerSampleKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemFlashOnOffKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemFocalLengthKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemAcquisitionMakeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAcquisitionModelKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemISOSpeedKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemOrientationKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemLayerNamesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemWhiteBalanceKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemApertureKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemProfileNameKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemResolutionWidthDPIKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemResolutionHeightDPIKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemExposureModeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemExposureTimeSecondsKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemEXIFVersionKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemCameraOwnerKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemFocalLength35mmKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemLensModelKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemEXIFGPSVersionKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAltitudeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemLatitudeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemLongitudeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemSpeedKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemTimestampKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSTrackKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemImageDirectionKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemNamedLocationKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemGPSStatusKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSMeasureModeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDOPKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSMapDatumKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDestLatitudeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDestLongitudeKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDestBearingKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDestDistanceKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSProcessingMethodKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSAreaInformationKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDateStampKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemGPSDifferentalKey NS_AVAILABLE_MAC(10_9); // NSNumber

FOUNDATION_EXPORT NSString * const NSMetadataItemCodecsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemMediaTypesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemStreamableKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemTotalBitRateKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemVideoBitRateKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemAudioBitRateKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemDeliveryTypeKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemAlbumKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemHasAlphaChannelKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemRedEyeOnOffKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemMeteringModeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemMaxApertureKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemFNumberKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemExposureProgramKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemExposureTimeStringKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemHeadlineKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemInstructionsKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemCityKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemStateOrProvinceKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemCountryKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemTextContentKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemAudioSampleRateKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemAudioChannelCountKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemTempoKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemKeySignatureKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemTimeSignatureKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAudioEncodingApplicationKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemComposerKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemLyricistKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAudioTrackNumberKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemRecordingDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemMusicalGenreKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemIsGeneralMIDISequenceKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemRecordingYearKey NS_AVAILABLE_MAC(10_9); // NSNumber

FOUNDATION_EXPORT NSString * const NSMetadataItemOrganizationsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemLanguagesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemRightsKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemPublishersKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemContributorsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemCoverageKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemSubjectKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemThemeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemDescriptionKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemIdentifierKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAudiencesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings

FOUNDATION_EXPORT NSString * const NSMetadataItemNumberOfPagesKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemPageWidthKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemPageHeightKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemSecurityMethodKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemCreatorKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemEncodingApplicationsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemDueDateKey NS_AVAILABLE_MAC(10_9); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemStarRatingKey NS_AVAILABLE_MAC(10_9); // NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemPhoneNumbersKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemEmailAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemInstantMessageAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemKindKey NS_AVAILABLE_MAC(10_9); // NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemRecipientsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemFinderCommentKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemFontsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemAppleLoopsRootKeyKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAppleLoopsKeyFilterTypeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAppleLoopsLoopModeKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAppleLoopDescriptorsKey NS_AVAILABLE_MAC(10_9); // NSArray of NSStrings
FOUNDATION_EXPORT NSString * const NSMetadataItemMusicalInstrumentCategoryKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemMusicalInstrumentNameKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemCFBundleIdentifierKey NS_AVAILABLE_MAC(10_9); // NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemInformationKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemDirectorKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemProducerKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemGenreKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemPerformersKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemOriginalFormatKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemOriginalSourceKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAuthorEmailAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemRecipientEmailAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemAuthorAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemRecipientAddressesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemIsLikelyJunkKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemExecutableArchitecturesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemExecutablePlatformKey NS_AVAILABLE_MAC(10_9); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemApplicationCategoriesKey NS_AVAILABLE_MAC(10_9); // NSArray of NSString

FOUNDATION_EXPORT NSString * const NSMetadataItemIsApplicationManagedKey NS_AVAILABLE_MAC(10_9); // boolean NSNumber
