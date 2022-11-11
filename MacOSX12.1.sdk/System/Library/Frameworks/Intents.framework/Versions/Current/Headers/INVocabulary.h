//
//  INVocabulary.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol INSpeakable;

typedef NS_ENUM(NSInteger, INVocabularyStringType) {
    /// The name of a contact as a person will say it, for example “Jon Smith”, “Apple”.
    INVocabularyStringTypeContactName = 1,

    /// The name of a group of contacts as a person will say it, for example "Tahoe Trip".
    INVocabularyStringTypeContactGroupName,

    /// A keyword associated with an image or images, for example "food", "Vacation".
    INVocabularyStringTypePhotoTag = 100,

    /// The name for a photograph album, for example "WWDC 2015 Karaoke".
    /// You may find that INVocabularyStringTypePhotoTag is a better match for concepts that are similar to, but not exactly, albums.
    INVocabularyStringTypePhotoAlbumName,

    /// The name a user has created for a workout, for example  “Half Marathon”, “Kettlebell exercise”
    INVocabularyStringTypeWorkoutActivityName = 200,

    /// The name of a vehicle configuration profile, for example "Roadtrip", "Rally", "Good Weather".
    /// For use by automaker apps that are enabled to work with CarPlay <https://developer.apple.com/carplay/>.
    INVocabularyStringTypeCarProfileName = 300,
    
    /// The name of a vehicle as a person will say it, for example “BMW”, “My Convertible”.
    INVocabularyStringTypeCarName API_AVAILABLE(ios(10.3), watchos(6.0)),
    
    /// The name of an organization to pay as a person will say it, for example “PG&E”, “Comcast”.
    INVocabularyStringTypePaymentsOrganizationName API_AVAILABLE(ios(10.3), watchos(6.0)) = 400,
    
    /// The name of an account nick name as a person will say it, for example “Checking”, “Rainy day savings”.
    INVocabularyStringTypePaymentsAccountNickname API_AVAILABLE(ios(10.3), watchos(6.0)),
    
    /// The title of a note, task, or task list as a person will say it; for example, "Grocery list" or "Weekly meeting minutes".
    INVocabularyStringTypeNotebookItemTitle API_AVAILABLE(ios(11.0), watchos(6.0)) = 500,
    
    /// The name of the note or task list's group (folder, directory, account); for example, "iCloud" or "Shopping"
    INVocabularyStringTypeNotebookItemGroupName API_AVAILABLE(ios(11.0), watchos(6.0)),
    
    /// The title of a playlist as a person will say it, for example "Today's Hits".
    INVocabularyStringTypeMediaPlaylistTitle API_AVAILABLE(ios(13.0), watchos(6.0)) = 700,
    
    /// The name of a music artist as a person will say it, for example "The Beatles".
    INVocabularyStringTypeMediaMusicArtistName API_AVAILABLE(ios(13.0), watchos(6.0)),
    
    /// The title of an audiobook as a person will say it, for example "The Time Machine".
    INVocabularyStringTypeMediaAudiobookTitle API_AVAILABLE(ios(13.0), watchos(6.0)),
    
    /// The name of an audiobook author as a person will say it, for example "Mary Shelley".
    INVocabularyStringTypeMediaAudiobookAuthorName API_AVAILABLE(ios(13.0), watchos(6.0)),
    
    /// The name of a Podcast or Radio show title as a person will say it, for example "Fresh Air".
    INVocabularyStringTypeMediaShowTitle API_AVAILABLE(ios(13.0), watchos(6.0))
} API_AVAILABLE(ios(10.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos);

API_AVAILABLE(ios(10.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos)
@interface INVocabulary : NSObject

+ (instancetype)sharedVocabulary;

/// Replaces all vocabulary strings already set for the given type.
/// Strings should be sorted by their expected importance to the user, in descending order.
/// There is no guarantee that every provided string will be used, but preference is given to strings at the beginning of the set.
/// Any strings larger than 1024 bytes when encoded as UTF-16 (roughly 500 characters) will be discarded.
- (void)setVocabularyStrings:(NSOrderedSet<NSString *> *)vocabulary ofType:(INVocabularyStringType)type;

- (void)setVocabulary:(NSOrderedSet<id<INSpeakable>> *)vocabulary ofType:(INVocabularyStringType)type API_AVAILABLE(ios(11.0), watchos(6.0));

/// Removes all vocabulary strings for every INVocabularyStringType the calling app has previously registered.
- (void)removeAllVocabularyStrings;

@end

NS_ASSUME_NONNULL_END
