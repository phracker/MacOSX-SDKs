//
//  MLMediaLibrary.h
//  MediaLibrary
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MLMediaSource;

API_DEPRECATED_BEGIN("MediaLibrary.framework will be removed in a future OS version. Use Photos.framework or iTunesLibrary.framework instead.", macos(10.9, 10.15))

NS_ASSUME_NONNULL_BEGIN
@interface MLMediaLibrary : NSObject

// The designated initializer
- (instancetype)initWithOptions:(NSDictionary<NSString *, id> *)options NS_DESIGNATED_INITIALIZER;

// Returns a dictionary of media sources by identifier.
// This will return nil the first time, which will kick off an async load of the media sources.
// A KVO notification is sent when the media sources have been loaded.
@property (readonly, copy, nullable) NSDictionary<NSString *, MLMediaSource *> *mediaSources;

@end

// Media Source Identifiers

extern NSString* const MLMediaSourcePhotosIdentifier;
extern NSString* const MLMediaSourceiPhotoIdentifier;
extern NSString* const MLMediaSourceiTunesIdentifier;
extern NSString* const MLMediaSourceApertureIdentifier;
extern NSString* const MLMediaSourceiMovieIdentifier;
extern NSString* const MLMediaSourceFinalCutIdentifier;
extern NSString* const MLMediaSourceGarageBandIdentifier;
extern NSString* const MLMediaSourceLogicIdentifier;
extern NSString* const MLMediaSourcePhotoBoothIdentifier;

// Custom media source identifiers
extern NSString* const MLMediaSourceCustomFoldersIdentifier;
extern NSString* const MLMediaSourceMoviesFolderIdentifier;
extern NSString* const MLMediaSourceAppDefinedFoldersIdentifier;

// Load Options keys (keys in the options dictionary argument to +mediaLibraryWithOptions:)

// MLMediaLoadSourceTypesKey
// MLMediaSourceType values ORed together as NSNumber
// This defines which sources to load based on library type.
// If not present, this will load all sources.
// For example:
//   MLMediaSourceTypeAudio includes iTunes, GarageBand and Logic
//   MLMediaSourceTypeImage includes iPhoto, Aperture and PhotoBooth
//   MLMediaSourceTypeMovie includes iMovie, Final Cut and Movies Folder
extern NSString* const MLMediaLoadSourceTypesKey;

// MLMediaLoadIncludeSourcesKey
// NSArray of NSStrings (media source identifiers)
// Defines which media sources to include when loading.
// If not present, load all available media sources
// This option is processed after MLMediaLoadSourceTypesKey
extern NSString* const MLMediaLoadIncludeSourcesKey;

// MLMediaLoadExcludeSourcesKey
// NSArray of NSStrings (media source identifiers)
// Defines which media sources to exclude when loading.
// This option is processed after MLMediaLoadIncludeSourcesKey
extern NSString* const MLMediaLoadExcludeSourcesKey;

// MLMediaLoadFoldersKey
// NSArray of NSStrings (identifiers that correspond to well-known folder locations)
// Specifies the well-known folders that should be searched for media files.
// If not present, none of the well-known folders will be provided
extern NSString* const MLMediaLoadFoldersKey;

// Identifiers for well-known folders:
extern NSString* const MLMediaLoadAppleLoops;
extern NSString* const MLMediaLoadMoviesFolder;

// MLMediaLoadAppFoldersKey
// NSArray of NSStrings (relative paths inside the caller's app bundle)
// Specifies one or more relative paths inside the caller's app bundle in which to search for media files.
extern NSString* const MLMediaLoadAppFoldersKey;

NS_ASSUME_NONNULL_END

API_DEPRECATED_END
