//
//  CSSearchableItemAttributeSet_Media.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>
#import <CoreSpotlight/CSSearchableItemAttributeSet_General.h>

NS_ASSUME_NONNULL_BEGIN

@interface CSSearchableItemAttributeSet (CSMedia)

//The list of editor/editors that have worked on this item.
@property(nullable, copy) NSArray<NSString*> *editors;

//The list of people who are visible in an image or movie or written about in a document.
@property(nullable, copy) NSArray<NSString*> *participants;

//The list of projects that this item is part of.
//For example if you were working on a movie, all of the movie files could be marked
//as belonging to the project "My movie"
@property(nullable, copy) NSArray<NSString*> *projects;

// This is the date that the file was last downloaded / received.
@property(nullable, strong) NSDate *downloadedDate;

//This attribute indicates where the item was obtained from.
//Examples:
//- downloaded file may refer to the site they were downloaded from,the refering URL, etc
//- files received by email may indicate who sent the file, the message subject, etc
@property(nullable, copy) NSArray<NSString*> *contentSources;

//This is a comment related to a file.
@property(nullable, copy) NSString *comment;

//This is the copyright of the content.
@property(nullable, copy) NSString *copyright;

//This is the date that the item was last used
@property(nullable, strong) NSDate *lastUsedDate;

//This is the date that the contents of the item were created
@property(nullable, strong) NSDate *contentCreationDate;

//This is the date that the contents of the item were last modified
@property(nullable, strong) NSDate *contentModificationDate;

//This is the date that the item was moved into the current location.
@property(nullable, strong) NSDate *addedDate;

//This is the duration, in seconds, of the content of the item (if appropriate).
@property(nullable, strong) NSNumber *duration;

//A list of contacts that are somehow associated with this document, beyond what is captured as Author.
@property(nullable, copy) NSArray<NSString*> *contactKeywords;

//The codecs used to encode/decode the media
@property(nullable, copy) NSArray<NSString*> *codecs;

//Media types present in the content
@property(nullable, copy) NSArray<NSString*> *mediaTypes;

//Whether the content is prepared for streaming.  Should be 0 for not streamable, 1 for streamable.
@property (nullable, strong, getter=isStreamable) NSNumber *streamable;

//The total bit rate (audio & video combined) of the media
@property(nullable, strong) NSNumber *totalBitRate;
//The video bit rate
@property(nullable, strong) NSNumber *videoBitRate;
//The audio bit rate
@property(nullable, strong) NSNumber *audioBitRate;

//The delivery type of the item.  Should be 0 for fast start and 1 for RTSP.
@property(nullable, strong) NSNumber *deliveryType;

//Used to indicate company/Organization that created the document.
@property(nullable, copy) NSArray<NSString*> *organizations;

//Used to indicate the role of the document creator
@property(nullable, copy) NSString *role;

//Used to designate the languages of the intellectual content of the
//resource. Recommended best practice for the values of the Language
//element is defined by BCP 47.
@property(nullable, copy) NSArray<NSString*> *languages;

//Used to provide a link to information about rights held in and
//over the resource. Typically a Rights element will contain a
//rights management statement for the resource, or reference a
//service providing such information. Rights information often
//encompasses Intellectual Property Rights (IPR), Copyright, and
//various Property Rights. If the rights element is absent, no
//assumptions can be made about the status of these and other rights
//with respect to the resource.
@property(nullable, copy) NSString *rights;

//Used to designate the entity responsible for making the resource
//available. Examples of a Publisher include a person, an
//organization, or a service. Typically, the name of a Publisher
//should be used to indicate the entity.
@property(nullable, copy) NSArray<NSString*> *publishers;

//Used to designate the entity responsible for making contributions
//to the content of the resource. Examples of a Contributor include
//a person, an organization or a service. Typically, the name of a
//Contributor should be used to indicate the entity.
@property(nullable, copy) NSArray<NSString*> *contributors;

//Used to designate the extent or scope of the content of the
//resource. Coverage will typically include spatial location
//(a place name or geographic co-ordinates), temporal period (a period label, date, or date range)
//or jurisdiction (such as a named administrative entity).
//Recommended best practice is to select a value from a controlled vocabulary, and that, where appropriate,
//named places or time periods be used in preference to numeric identifiers such as sets of co-ordinates or date ranges.
@property(nullable, copy) NSArray<NSString*> *coverage;

//User rating of this item out of 5 stars
@property(nullable, strong) NSNumber *rating;

//A description of the rating.  E.g. the number of reviewers.
@property(nullable, copy) NSString *ratingDescription;

//User play count of this item
@property(nullable, strong) NSNumber *playCount;

//Information about the item
@property(nullable, copy) NSString *information;

//Director of the item (e.g. movie director)
@property(nullable, copy) NSString *director;

//Producer of the content
@property(nullable, copy) NSString *producer;

//Genre of the item (e.g. movie genre)
@property(nullable, copy) NSString *genre;

//Performers in the movie
@property(nullable, copy) NSArray<NSString*> *performers;

//Original format of the movie
@property(nullable, copy) NSString *originalFormat;

//Original source of the movie
@property(nullable, copy) NSString *originalSource;

//Whether or not the item is local. Should be 1 if true, 0 otherwise.
@property(nullable, strong, getter=isLocal) NSNumber *local;

//Whether or not the item has explicit content. Should be 1 if explicit, 0 for clean.
@property(nullable, strong) NSNumber *contentRating;

//URL of the item
@property(nullable, strong) NSURL *URL;

@end

@interface CSSearchableItemAttributeSet (CSMusic)

//The sample rate of the audio data contained in the file. The sample rate is a
//float value representing hz (audio_frames/second). For example: 44100.0, 22254.54.
@property(nullable, strong) NSNumber *audioSampleRate;

//The number of channels in the audio data contained in the file. This item only represents
//the number of discreet channels of audio data found in the file. It does not indicate
//any configuration of the data in regards to a user's speaker setup.
@property(nullable, strong) NSNumber *audioChannelCount;

//The tempo of the music contained in the audio file in Beats Per Minute.
@property(nullable, strong) NSNumber *tempo;

//The musical key of the song/composition contained in an audio file.
//For example: C, Dm, F#m, Bb.
@property(nullable, copy) NSString *keySignature;

//The time signature of the musical composition contained in the audio/MIDI file.
//For example: "4/4", "7/8".
@property(nullable, copy) NSString *timeSignature;

//The name of the application that encoded the data contained in the audio file.
@property(nullable, copy) NSString *audioEncodingApplication;

//The composer of the song/composition contained in the audio file.
@property(nullable, copy) NSString *composer;

//The lyricist/text writer for song/composition contained in the audio file.
@property(nullable, copy) NSString *lyricist;

//The title for a collection of media. This is analagous to a record album,
//or photo album whichs are collections of audio or images.
@property(nullable, copy) NSString *album;

//The artist for the media
@property(nullable, copy) NSString *artist;

//The track number of a song/composition when it is part of an album
@property(nullable, strong) NSNumber *audioTrackNumber;

//The recording date of the song/composition. This information differs from
//the contentCreationDate attribute as it indicates the date that the
//'art' was created, in contrast to contentCreationDate which for example, could indicate
//the creation date of an edited or 'mastered' version of the original art.
@property(nullable, strong) NSDate *recordingDate;

//The musical genre of the song/composition contained in the audio file.
//For example: Jazz, Pop, Rock, Classical.
@property(nullable, copy) NSString *musicalGenre;

//This attribute indicates whether the MIDI sequence contained in the file is setup for use with a General MIDI device.  Should be 1 if true, 0 otherwise.
@property(nullable, strong,getter=isGeneralMIDISequence) NSNumber *generalMIDISequence;

//Meta data attribute that stores the category of
//instrument. Files should have an instrument associated with
//them ("Other Instrument" is provided as a catch-all). For some
//categories, like "Keyboards" there are instrument names which
//provide a more detailed instrument definition (e.g., Piano,Organ, etc.)
@property(nullable, copy) NSString *musicalInstrumentCategory;

//Meta data attribute that stores the name of instrument
//(relative to the instrument category) Files can have an
//instrument name associated with them if they have certain
//instrument categories (e.g., the category Percussion has
//                       multiple instruments, including Conga and Bongo).
@property(nullable, copy) NSString *musicalInstrumentName;

@end

NS_ASSUME_NONNULL_END
