//
//  MLMediaTypes.h
//  iLifeMediaBrowser
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

API_DEPRECATED_BEGIN("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.9, 10.15))

typedef NS_OPTIONS(NSUInteger, MLMediaSourceType)
{
	MLMediaSourceTypeAudio = 1 << 0,
	MLMediaSourceTypeImage = 1 << 1,
	MLMediaSourceTypeMovie = 1 << 2,
};

typedef NS_ENUM(NSUInteger, MLMediaType)
{
	MLMediaTypeAudio		= 1 << 0,
	MLMediaTypeImage		= 1 << 1,
	MLMediaTypeMovie		= 1 << 2,
};

NS_ASSUME_NONNULL_BEGIN

///////////// Media Group Type Identifiers
//
// Folders
extern NSString* const MLFolderRootGroupTypeIdentifier;
extern NSString* const MLFolderGroupTypeIdentifier;

// iTunes
extern NSString* const MLiTunesRootGroupTypeIdentifier;
extern NSString* const MLiTunesPlaylistTypeIdentifier;
extern NSString* const MLiTunesPurchasedPlaylistTypeIdentifier;
extern NSString* const MLiTunesPodcastPlaylistTypeIdentifier;
extern NSString* const MLiTunesVideoPlaylistTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLiTunesSmartPlaylistTypeIdentifier;
extern NSString* const MLiTunesFolderPlaylistTypeIdentifier;
extern NSString* const MLiTunesMoviesPlaylistTypeIdentifier;
extern NSString* const MLiTunesTVShowsPlaylistTypeIdentifier;
extern NSString* const MLiTunesAudioBooksPlaylistTypeIdentifier;
extern NSString* const MLiTunesMusicPlaylistTypeIdentifier;
extern NSString* const MLiTunesMusicVideosPlaylistTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLiTunesGeniusPlaylistTypeIdentifier;
extern NSString* const MLiTunesSavedGeniusPlaylistTypeIdentifier;
extern NSString* const MLiTunesiTunesUPlaylistTypeIdentifier;

// Photos
extern NSString* const MLPhotosRootGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosSharedGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosAlbumsGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosAlbumTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosFolderTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosSmartAlbumTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosPublishedAlbumTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosAllMomentsGroupTypeIdentifier API_DEPRECATED("No longer supported", macos(10.10, 10.15));
extern NSString* const MLPhotosMomentGroupTypeIdentifier API_DEPRECATED("No longer supported", macos(10.10, 10.15));
extern NSString* const MLPhotosAllCollectionsGroupTypeIdentifier API_DEPRECATED("No longer supported", macos(10.10, 10.15));
extern NSString* const MLPhotosCollectionGroupTypeIdentifier API_DEPRECATED("No longer supported", macos(10.10, 10.15));
extern NSString* const MLPhotosAllYearsGroupTypeIdentifier API_DEPRECATED("No longer supported", macos(10.10, 10.15));
extern NSString* const MLPhotosYearGroupTypeIdentifier API_DEPRECATED("No longer supported", macos(10.10, 10.15));
extern NSString* const MLPhotosLastImportGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosMyPhotoStreamTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosSharedPhotoStreamTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosFavoritesGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosFrontCameraGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.11, 10.15));
extern NSString* const MLPhotosLivePhotosGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.13, 10.15));
extern NSString* const MLPhotosLongExposureGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.13, 10.15));
extern NSString* const MLPhotosAnimatedGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.13, 10.15));
extern NSString* const MLPhotosPanoramasGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosVideosGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10, 10.15));
extern NSString* const MLPhotosSloMoGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10.3, 10.15));
extern NSString* const MLPhotosDepthEffectGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.12.1, 10.15));
extern NSString* const MLPhotosTimelapseGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10.3, 10.15));
extern NSString* const MLPhotosBurstGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10.3, 10.15));
extern NSString* const MLPhotosScreenshotGroupTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.11, 10.15));
extern NSString* const MLPhotosFacesAlbumTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10.3, 10.15));
extern NSString* const MLPhotosAllPhotosAlbumTypeIdentifier API_DEPRECATED("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.10.3, 10.15));

// iPhoto
extern NSString* const MLiPhotoRootGroupTypeIdentifier;
extern NSString* const MLiPhotoAlbumTypeIdentifier;
extern NSString* const MLiPhotoLibraryAlbumTypeIdentifier;
extern NSString* const MLiPhotoEventsFolderTypeIdentifier;
extern NSString* const MLiPhotoSmartAlbumTypeIdentifier;
extern NSString* const MLiPhotoEventAlbumTypeIdentifier;
extern NSString* const MLiPhotoLastImportAlbumTypeIdentifier;
extern NSString* const MLiPhotoLastNMonthsAlbumTypeIdentifier;
extern NSString* const MLiPhotoFlaggedAlbumTypeIdentifier;
extern NSString* const MLiPhotoFolderAlbumTypeIdentifier;
extern NSString* const MLiPhotoSubscribedAlbumTypeIdentifier;
extern NSString* const MLiPhotoFacesAlbumTypeIdentifier;
extern NSString* const MLiPhotoPlacesAlbumTypeIdentifier;
extern NSString* const MLiPhotoPlacesCountryAlbumTypeIdentifier;
extern NSString* const MLiPhotoPlacesProvinceAlbumTypeIdentifier;
extern NSString* const MLiPhotoPlacesCityAlbumTypeIdentifier;
extern NSString* const MLiPhotoPlacesPointOfInterestAlbumTypeIdentifier;
extern NSString* const MLiPhotoFacebookAlbumTypeIdentifier;
extern NSString* const MLiPhotoFlickrAlbumTypeIdentifier;
extern NSString* const MLiPhotoFacebookGroupTypeIdentifier;
extern NSString* const MLiPhotoFlickrGroupTypeIdentifier;
extern NSString* const MLiPhotoSlideShowAlbumTypeIdentifier;
extern NSString* const MLiPhotoLastViewedEventAlbumTypeIdentifier;
extern NSString* const MLiPhotoPhotoStreamAlbumTypeIdentifier;

// Aperture
extern NSString* const MLApertureRootGroupTypeIdentifier;
extern NSString* const MLApertureUserAlbumTypeIdentifier;
extern NSString* const MLApertureUserSmartAlbumTypeIdentifier;
extern NSString* const MLApertureProjectAlbumTypeIdentifier;
extern NSString* const MLApertureFolderAlbumTypeIdentifier;
extern NSString* const MLApertureProjectFolderAlbumTypeIdentifier;
extern NSString* const MLApertureLightTableTypeIdentifier;
extern NSString* const MLApertureFlickrGroupTypeIdentifier;
extern NSString* const MLApertureFlickrAlbumTypeIdentifier;
extern NSString* const MLApertureFacebookGroupTypeIdentifier;
extern NSString* const MLApertureFacebookAlbumTypeIdentifier;
extern NSString* const MLApertureSmugMugGroupTypeIdentifier;
extern NSString* const MLApertureSmugMugAlbumTypeIdentifier;
extern NSString* const MLApertureSlideShowTypeIdentifier;
extern NSString* const MLApertureAllPhotosTypeIdentifier;
extern NSString* const MLApertureFlaggedTypeIdentifier;
extern NSString* const MLApertureAllProjectsTypeIdentifier;
extern NSString* const MLApertureFacesAlbumTypeIdentifier;
extern NSString* const MLAperturePlacesAlbumTypeIdentifier;
extern NSString* const MLAperturePlacesCountryAlbumTypeIdentifier;
extern NSString* const MLAperturePlacesProvinceAlbumTypeIdentifier;
extern NSString* const MLAperturePlacesCityAlbumTypeIdentifier;
extern NSString* const MLAperturePlacesPointOfInterestAlbumTypeIdentifier;
extern NSString* const MLApertureLastImportAlbumTypeIdentifier;
extern NSString* const MLApertureLastNMonthsAlbumTypeIdentifier;
extern NSString* const MLApertureLastViewedEventAlbumTypeIdentifier;
extern NSString* const MLAperturePhotoStreamAlbumTypeIdentifier;

// GarageBand
extern NSString* const MLGarageBandRootGroupTypeIdentifier;
extern NSString* const MLGarageBandFolderGroupTypeIdentifier;

// Logic
extern NSString* const MLLogicRootGroupTypeIdentifier;
extern NSString* const MLLogicBouncesGroupTypeIdentifier;
extern NSString* const MLLogicProjectsGroupTypeIdentifier;
extern NSString* const MLLogicProjectTypeIdentifier;

// iMovie
extern NSString* const MLiMovieRootGroupTypeIdentifier;
extern NSString* const MLiMovieEventGroupTypeIdentifier;
extern NSString* const MLiMovieProjectGroupTypeIdentifier;
extern NSString* const MLiMovieEventLibraryGroupTypeIdentifier;
extern NSString* const MLiMovieEventCalendarGroupTypeIdentifier;
extern NSString* const MLiMovieFolderGroupTypeIdentifier;

// Final Cut
extern NSString* const MLFinalCutRootGroupTypeIdentifier;
extern NSString* const MLFinalCutEventGroupTypeIdentifier;
extern NSString* const MLFinalCutProjectGroupTypeIdentifier;
extern NSString* const MLFinalCutEventLibraryGroupTypeIdentifier;
extern NSString* const MLFinalCutEventCalendarGroupTypeIdentifier;
extern NSString* const MLFinalCutFolderGroupTypeIdentifier;

////////////////////////////////////////////////////////////////
// Media Object Attribute Keys

extern NSString* const MLMediaObjectDurationKey;		// NSNumber (double) in seconds
extern NSString* const MLMediaObjectArtistKey;			// NSString
extern NSString* const MLMediaObjectAlbumKey;			// NSString
extern NSString* const MLMediaObjectGenreKey;			// NSString
extern NSString* const MLMediaObjectKindKey;			// NSString
extern NSString* const MLMediaObjectTrackNumberKey;		// NSNumber
extern NSString* const MLMediaObjectBitRateKey;			// NSNumber (kbps)
extern NSString* const MLMediaObjectSampleRateKey;		// NSNumber (Hz)
extern NSString* const MLMediaObjectChannelCountKey;	// NSNumber
extern NSString* const MLMediaObjectResolutionStringKey;// NSString e.g. "{1280, 720}"
extern NSString* const MLMediaObjectCommentsKey;		// NSString
extern NSString* const MLMediaObjectKeywordsKey;		// NSArray of NSStrings
extern NSString* const MLMediaObjectProtectedKey;		// NSNumber (BOOL)

NS_ASSUME_NONNULL_END

API_DEPRECATED_END
