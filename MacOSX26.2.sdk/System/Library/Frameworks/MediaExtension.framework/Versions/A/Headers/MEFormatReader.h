/*
	File:  MEFormatReader.h

	Framework:  MediaExtension

	Copyright © 2024 Apple Inc. All rights reserved.


	Overview

	This file contains the interface/protocol for MediaExtension format readers. Developers who wish to build MediaExtension
	format readers using this API will need to include the required entitlement along with a provisioning profile when building
	their extensions. For more information about public entitlements and provisioning profiles see:
	https://developer.apple.com/documentation/bundleresources/entitlements
	https://developer.apple.com/help/account/manage-provisioning-profiles/create-a-development-provisioning-profile

	MediaExtension Format Reader Entitlement

	The format reader must include the public entitlement key "com.apple.developer.mediaextension.formatreader" with a boolean
	value set to true. A provisioning profile will be needed to use this entitlement.

	MediaExtension Format Reader Info.plist File Information

	The following standard bundle Info.plist keys have significance for MediaExtension format readers:

	- CFBundleVersion
		This version number will be used to select among any duplicate installations of MediaExtension format readers with the
		same ClassImplementationID. The version formatting should follow standard CFBundleVersion guidelines, with any major,
		minor, and update versions having values in the range of 0-255.
	- CFBundleDisplayName
		This name will be displayed to identify the format readers in the System Settings listing of extension format readers.
		The name can be localized using standard bundle localization techniques. If no display name is provided, the system
		will use the file name of the MediaExtension format reader bundle.
	- CFBundleIconName
	- CFBundleIconFile
		The icon referenced here will displayed along with the CFBundleDisplayName in the System Settings listing of extension
		format readers. If no icon is provided, the system will use a generic icon.

	MediaExtension format readers will also need to include two specialized dictionaries in their Info.plist files. One dictionary
	is required and describes ExtensionKit information, while the other is optional and registers the format reader media format
	with the system.

	EXAppExtensionAttributes Dictionary

	The EXAppExtensionAttributes dictionary is required by ExtensionKit. The following keys will be needed for MediaExtension
	format readers (see also MEExtensionPlugin.h):

	- ClassImplementationID
		This should be a string similar to the bundle identifier of the format reader. It should start with the reverse
		domain identifier of the developer to prevent collisions with other developers, and for clarity contain
		".formatreader." and the name of the media format. If the developer envisions multiple variants of the same media
		format, the name should include strings to make each format reader unique. An example might be something like
		"com.mycompany.formatreader.mymediaformat.formatvariant".
	- EXExtensionPointIdentifier
		The string "com.apple.mediaextension.formatreader" (kMEFormatReaderExtensionPointName).
	- EXPrincipalClass
		The name of the format reader factory class, conforming to the MEFormatReaderExtension protocol.
	- MTFileNameExtensionArray
		An array of strings describing the file name extension strings (without the .) of all file types supported
		by the format reader. There should be at least one entry for each type of media file supported.
	- MTUTTypeArray
		An array of strings describing the UTType identifier associated with the media the format reader supports. There
		should be at least one entry for the media type that is supported.
	- ObjectName
		A user-readable string describing the format reader. This string is used for uniquely identifying format readers
		and possibly for debug logging but is typically not visible to users.

	UTExportedTypeDeclarations Dictionary

	The UTExportedTypeDeclarations dictionary is optional and allows the format reader to register its supported format
	from the MTUTTypeArray above with the system so that media files can be recognized and opened by other applications.
	For general information on how to make a UTExportedTypeDeclarations dictionary, see documentation here:
	https://developer.apple.com/documentation/bundleresources/information_property_list/utexportedtypedeclarations

	- UTTypeDescription
		A user-readable string describing the media "kind". This name will be displayed in Finder. This string can be
		localized by making localized variants of the Info.plist file.
	- UTTypeConformsTo
		An array of UTType identifiers. The first entry should be set to the abstract type for MediaExtension
		format readers, "com.apple.mediaextension-content". This type also conforms to higher level abstract types such as
		"public.movie" and "public.audiovisual-content". Additional types can also be included as well if desired.
	- UTTypeIdentifier
		A UTType identifier string that should match the value in MTUTTypeArray in the EXAppExtensionAttributes dictionary.
	- UTTypeTagSpecification
		Inside the UTTypeTagSpecification dictionary, the public.filename-extension key should have a value matching the
		MTFileNameExtensionArray in the EXAppExtensionAttributes dictionary.
	- public.mime-type
		This key is optional but should be a MIME type that corresponds to the format.


	To report bugs, go to:  http://developer.apple.com/bugreporter/

*/

#ifndef MEFormatReader_h
#define MEFormatReader_h

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CMSampleBuffer.h>
#import <CoreMedia/CMFormatDescription.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

// forward declarations
@class MEFileInfo;
@class METrackInfo;
@class MEHEVCDependencyInfo;
@class MESampleCursorChunk;
@class MESampleLocation;
@class MEEstimatedSampleLocation;
@class MEByteSource;
@protocol METrackReader;
@protocol MESampleCursor;
@protocol MEFormatReader;

#pragma mark - MEFormatReader Defines

/*!
	@enum 			MEFileInfoFragmentsStatus
	@discussion		Describes whether a file supports or contains fragments. For QuickTime movie and ISO files, it indicates the presence of an 'mvex' box, which is necessary in order to signal the possible presence of later 'moof' boxes.
	@constant		MEFileInfoCouldNotContainFragments
		The file is not capable of being extended by fragments.
	@constant		MEFileInfoContainsFragments
		The file is capable of being extended by fragments *and* contains at least one fragment.
	@constant		MEFileInfoCouldContainButDoesNotContainFragments
		The file is capable of being extended by fragments, but does not contain any fragments.
*/
typedef NS_ENUM(NSInteger, MEFileInfoFragmentsStatus) {
	MEFileInfoCouldNotContainFragments      			= 0,
	MEFileInfoContainsFragments        					= 1,
	MEFileInfoCouldContainButDoesNotContainFragments    = 2
} NS_SWIFT_NAME(MEFileInfo.FragmentsStatus) API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);


/*!
	@enum			MEFormatReaderParseAdditionalFragmentsStatus
	@abstract		Informational status flags returned by parseAdditionalFragmentsWithCompletionHandler.
	@discussion		A combination of these values may be returned in the statusOut field from parseAdditionalFragmentsWithCompletionHandler.
	@constant		MEFormatReaderParseAdditionalFragmentsStatusSizeIncreased
		Set if the size of the file increased.
	@constant		MEFormatReaderParseAdditionalFragmentsStatusFragmentAdded
		Set if one or more fragments were added.
	@constant		MEFormatReaderParseAdditionalFragmentsStatusFragmentsComplete
		Set if no more fragments can be added. Further calls to parseAdditionalFragmentsWithCompletionHandler will return an error.
*/
typedef NS_OPTIONS(NSUInteger, MEFormatReaderParseAdditionalFragmentsStatus) {
	MEFormatReaderParseAdditionalFragmentsStatusSizeIncreased		= 1 << 0,
	MEFormatReaderParseAdditionalFragmentsStatusFragmentAdded		= 1 << 1,
	MEFormatReaderParseAdditionalFragmentsStatusFragmentsComplete	= 1 << 2,
} API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

#pragma mark - MEFormatReaderInstantiationOptions

/*!
	@class			MEFormatReaderInstantiationOptions
	@abstract		A class that encapsulates options to be passed to MEFormatReaderExtension
	@discussion		The class MEFormatReaderInstantiationOptions is mutable, with options set through instance properties.
*/
NS_SWIFT_SENDABLE API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MEFormatReaderInstantiationOptions : NSObject <NSCopying>

/*!
	@property		allowIncrementalFragmentParsing
	@abstract		Enables support for parsing additional fragments
	@discussion		If YES, requests that the MEFormatReader be configured to support calls to parseAdditionalFragments. By default the MEFormatReader does not support calls to parseAdditionalFragments.
*/
@property (nonatomic, readonly) BOOL allowIncrementalFragmentParsing;

@end


#pragma mark - MEFormatReaderExtension

/*!
	@protocol		MEFormatReaderExtension
	@abstract		Provides a factory method for creating MEFormatReader objects.
	@discussion		The MEFormatReaderExtension protocol provides a factory method to create a new MEFormatReader when provided with an MEByteSource object. MEFormatReaderExtension is always instantiated by the Media Toolbox, and the MEByteSource object is also created by Media Toolbox based on the specified media asset. All async methods in MEFormatReader/METrackReader/MESampleCursor are allowed to call the completion handlers on any thread or queue.
*/
API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@protocol MEFormatReaderExtension <NSObject>

- (instancetype)init;

/*!
	@method			formatReaderWithByteSource
	@abstract		The factory method to create a new MEFormatReader.
	@discussion		Creates a new MEFormatReader given an MEByteSource, with optional MEFileReaderInstantiationOptions.
	@param			primaryByteSource
		The primary MEByteSource instance for the format reader. The MEFormatReader should retain this object for use when responding to later requests for information, and release it in the object finalize method.
	@param			options
		An optional instance of MEFormatReaderInstantiationOptions
	@param			error
		On return, if initialization of the MEFormatReader fails, points to an NSError describing the nature of the failure.
	@result			A newly created instance of MEFormatReader.
*/
- (id<MEFormatReader> _Nullable)formatReaderWithByteSource:(MEByteSource *)primaryByteSource options:(MEFormatReaderInstantiationOptions * _Nullable)options error:(NSError *__autoreleasing _Nullable * _Nullable)error;

@end


#pragma mark - MEFormatReader

/*!
	@protocol		MEFormatReader
	@abstract		The primary object for a MediaExtension format reader, representing a single media asset.
	@discussion		The MEFormatReader protocol provides an interface for the MediaToolbox to interact with MediaExtension format readers, which provide information about media assets. MEFormatReader objects are always instantiated by the MediaToolbox. To create an MEFormatReader object, MediaToolbox first creates a primary MEByteSource object around a source media asset. It then creates an MEFormatReaderExtension object and calls its formatReaderWithByteSource method. MEFormatReaders should expect to run in a sandboxed process with restricted access to the filesystem, network and other kernel resources.
*/
API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@protocol MEFormatReader <NSObject>

/*!
	@method			loadFileInfoWithCompletionHandler
	@abstract		Asynchronously loads the MEFileInfo object with properties of the media asset.
	@discussion		This method should provide either a valid MEFileInfo object or nil in case of failure.  If the method fails, the NSError will contain error information.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'fileInfo'
			The returned MEFileInfo object.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)loadFileInfoWithCompletionHandler:(void (^)(MEFileInfo* _Nullable fileInfo, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(fileInfo());

/*!
	@method			loadMetadataWithCompletionHandler
	@abstract		Asynchronously loads the array of AVMetadataItems representing metadata from the media asset.
	@discussion		This method should provide either a valid NSArray or nil. If the method fails, the NSError will contain error information.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'metadata'
			The returned NSArray of AVMetadataItem objects.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)loadMetadataWithCompletionHandler:(void (^)(NSArray< AVMetadataItem * > * _Nullable metadata, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(metadata());

/*!
	@method			loadTrackReadersWithCompletionHandler
	@abstract		Asynchronously loads the array of METrackReader objects representing the tracks in the media asset.
	@discussion		This method should provide either a valid NSArray object or nil. If the method fails, the NSError will contain error information.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'trackReaders'
			The returned NSArray of METrackReader objects.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)loadTrackReadersWithCompletionHandler:(void (^)(NSArray< id<METrackReader> > * _Nullable trackReaders, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(trackReaders());

@optional

/*!
	@method			parseAdditionalFragmentsWithCompletionHandler
	@abstract		Asynchronously incorporates additional fragments that have been appended since the file was last parsed.
	@discussion		Parses additional fragments of the media asset if they exist. Media asset formats that do not support incremental fragments do not need implement this method. The MEFormatReader must have been instantiated with the MEFormatReaderInstantiationOptions property allowIncrementalFragmentParsing set to YES. Does nothing unless the MEFileInfo property fragmentsStatus is MEFileInfoContainsFragments. Once this function returns an error, later calls should also always fail.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'fragmentStatus'
			The returned MEFormatReaderParseAdditionalFragmentsStatus flags with status information.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil. Returns an error of MEFormatReaderErrorUnsupportedFeature if the MEFormatReaderInstantiationOptions property allowIncrementalFragmentParsing was not set to YES at creation time. Returns an error of MEFormatReaderErrorParsingFailure if there was a parsing failure.
*/
- (void)parseAdditionalFragmentsWithCompletionHandler:(void (^)(MEFormatReaderParseAdditionalFragmentsStatus fragmentStatus, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(parseAdditionalFragments());

@end


#pragma mark - MEFileInfo

/*!
	 @interface		MEFileInfo
	 @abstract		A class incorporating file properties parsed from the media asset.
	 @discussion	The MEFileInfo properties are parsed asynchronously through the loadFileInfoWithCompletionHandler method of MEFormatReader.
*/
NS_SWIFT_SENDABLE API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MEFileInfo : NSObject <NSCopying>

/*!
	@property		duration
	@abstract		The duration of the media asset if known, otherwise kCMTimeInvalid.
*/
@property (nonatomic) CMTime duration;

/*!
	@property		fragmentsStatus
	@abstract		Indicates if the media asset is capable of being extended by fragments or contains fragments
	@discussion		See the MEFileInfoFragmentsStatus values for details of the return value. The value will default to MEFileInfoCouldNotContainFragments.
*/
@property (nonatomic) MEFileInfoFragmentsStatus fragmentsStatus;

/*!
	@property		sidecarFileName
	@abstract		The sidecar filename used by the MediaExtension.
	@discussion		Represents a new or existing sidecar file located in the same directory as the primary media file. The filename should include the file extension, and should not contain the file path, or contain any slashes. The file extension should be supported by the format reader, and present in the EXAppExtensionAttributes and UTExportedTypeDeclarations dictionaries in the MediaExtension format reader Info.plist.
*/
@property (nonatomic, copy, nullable) NSString* sidecarFileName API_AVAILABLE(macos(26.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

@end


#pragma mark - METrackReader

/*!
	@protocol		METrackReader
	@abstract		Provides information about a track within a media asset.
	@discussion		The MEFormatReader creates METrackReader objects for each track in the media asset. MEFormatReader plugin authors should provide code to implement the METrackReader protocol methods. Since not every method or property applies to every track type, those that don't make sense should return default values.
*/
API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@protocol METrackReader <NSObject>

/*!
	@method			loadTrackInfoWithCompletionHandler
	@abstract		Asynchronously loads the METrackInfo object with properties of the media asset track.
	@discussion		This method should provide either a valid METrackInfo object or nil.  If the method fails, the NSError will contain error information.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'trackInfo'
			The returned METrackInfo object if the method succeeds, otherwise nil.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
 */
- (void)loadTrackInfoWithCompletionHandler:(void (^)(METrackInfo* _Nullable trackInfo, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(trackInfo());

/*!
	@method			generateSampleCursorAtPresentationTimeStamp
	@abstract		Provides a new MESampleCursor object pointing to the sample at or near the specified presentation timestamp.
	@discussion		The new MESampleCursor will point to the last sample with a PTS less than or equal to presentationTimeStamp, or if there are no such samples, the first sample in PTS order. 
	@param			presentationTimeStamp
		The desired PTS.
    @param 			completionHandler
		The handler that will be invoked when the method completes.
		'sampleCursor'
			The returned MESampleCursor if the method succeeds, otherwise nil.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)generateSampleCursorAtPresentationTimeStamp:(CMTime)presentationTimeStamp completionHandler:(void (^)(id<MESampleCursor> _Nullable sampleCursor, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(sampleCursor(atPresentationTimeStamp:));

/*!
	@method			generateSampleCursorAtFirstSampleInDecodeOrderWithCompletionHandler
	@abstract		Provides a new MESampleCursor object pointing to the first sample in decode order.
	@discussion		The new MESampleCursor will point to the first sample in decode order regardless of the presentation time.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'sampleCursor'
			The returned MESampleCursor if the method succeeds, otherwise nil.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)generateSampleCursorAtFirstSampleInDecodeOrderWithCompletionHandler:(void (^)(id<MESampleCursor> _Nullable sampleCursor, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(sampleCursorAtFirstSampleInDecodeOrder());

/*!
	@method			generateSampleCursorAtLastSampleInDecodeOrderWithCompletionHandler
	@abstract		Provides a new MESampleCursor object pointing to the last sample in decode order.
	@discussion		The new MESampleCursor will point to the last sample in decode order regardless of the presentation time.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'sampleCursor'
			The returned MESampleCursor if the method succeeds, otherwise nil.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)generateSampleCursorAtLastSampleInDecodeOrderWithCompletionHandler:(void (^)(id<MESampleCursor> _Nullable sampleCursor, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(sampleCursorAtLastSampleInDecodeOrder());

@optional

/*!
	@method			loadUneditedDurationWithCompletionHandler
	@abstract		Returns the duration of the track as a CMTime disregarding any edits.
	@discussion		This information may be used by the MediaToolbox to validate edit information or to check if the media is suitable for gapless playback.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'uneditedDuration'
			A valid duration if the method succeeds, otherwise kCMTimeInvalid.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)loadUneditedDurationWithCompletionHandler:(void (^)(CMTime uneditedDuration, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(uneditedDuration());

/*!
	@method			loadTotalSampleDataLengthWithCompletionHandler
	@abstract		Loads the total size in bytes of all the samples in the track.
	@discussion		If the method fails, the NSError will contain error information.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'totalSampleDataLength'
			A valid data length if the method succeeds, otherwise 0.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)loadTotalSampleDataLengthWithCompletionHandler:(void (^)(int64_t totalSampleDataLength, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(totalSampleDataLength());

/*!
	@method			loadEstimatedDataRateWithCompletionHandler
	@abstract		Loads the approximate data rate of the track in bytes per second as a floating point number.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'estimatedDataRate'
			A valid data rate if the method succeeds, otherwise 0.0.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)loadEstimatedDataRateWithCompletionHandler:(void (^)(Float32 estimatedDataRate, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(estimatedDataRate());

/*!
	@method			loadMetadataWithCompletionHandler
	@abstract		Asynchronously loads an NSArray object with metadata from the media asset track.
	@discussion		This method should provide either a valid NSArray object or nil. If the method fails, the NSError will contain error information.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'metadata'
			An NSArray of AVMetadataItem objects if the method succeeds, otherwise nil.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)loadMetadataWithCompletionHandler:(void (^)(NSArray< AVMetadataItem * > * _Nullable metadata, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(metadata());

@end


#pragma mark - METrackInfo

/*!
	@interface		METrackInfo
	@abstract		A class incorporating track properties parsed from the media asset.
	@discussion		The METrackInfo properties are parsed asynchronously through the loadTrackInfoWithCompletionHandler method of METrackReader.
*/
NS_SWIFT_SENDABLE API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface METrackInfo : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

/*!
	@method			initWithMediaType
	@abstract		Initializes a new METrackInfo instance.
	@discussion		The main initializer for the METrackInfo class. After creating the class, the METrackReader should fill in all the relevant properties with the values read in from the media track.
	@param			mediaType
		The media type of the track.
	@param			trackID
		An integer identifying the track within the media asset.
	@param			formatDescriptions
		The format descriptions for the track, as an NSArray.
	@result			A new instance of METrackInfo.
*/
- (instancetype)initWithMediaType:(CMMediaType)mediaType trackID:(CMPersistentTrackID)trackID formatDescriptions:(NSArray*)formatDescriptions NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/*!
	@property		mediaType
	@abstract		The media type of the track.
	@discussion		This value is set through the class initializer.
*/
@property (nonatomic, readonly) CMMediaType mediaType;

/*!
	@property		trackID
	@abstract		An integer identifying the track within the media asset.
	@discussion		The track ID is used to uniquely identify the track within the MEFormatReader. Track IDs must be unique within a media asset but do not need to be unique across assets. If a media format does not have a native concept of track IDs, track IDs may be assigned starting from 1. The track ID value of 0 is reserved to indicate an invalid track ID. This value is set through the class initializer.
*/
@property (nonatomic, readonly) CMPersistentTrackID trackID;

/*!
	@property		enabled
	@abstract		A BOOL value indicating whether the track is enabled by default.
*/
@property (nonatomic, getter=isEnabled) BOOL enabled;

/*!
	@property		formatDescriptions
	@abstract		The format descriptions for the track, as an NSArray.
	@discussion		This value is set through the class initializer.
*/
@property (nonatomic, copy, readonly) NSArray* formatDescriptions NS_REFINED_FOR_SWIFT;

@end

API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface METrackInfo (OptionalProperties)

/*!
	@property		naturalTimescale
	@abstract		The natural timescale of the track, as a CMTimeScale value.
*/
@property (nonatomic) CMTimeScale naturalTimescale;

/*!
	@property		trackEdits
	@abstract		Returns the array of edit segments for the given track.
	@discussion		Each NSValue in the array contains a CMTimeMapping object describing the track edit. The CMTimeMapping.target time ranges for successive edits must partition the time range from 0 to the track's duration. In other words, for edit index = 0 the CMTimeMapping.target.start must be kCMTimeZero, while for edit index > 0, the CMTimeMapping.target.start must match the CMTimeRangeGetEnd(CMTimeMapping.target) for edit (index - 1). It is valid for a track to have an empty trackEdits array; this means that there is nothing at all in the track and the track duration is zero. If this property is implemented for media asset formats that do not support edit segments, it can return nil.
*/
@property (nonatomic, copy, nullable) NSArray< NSValue * >* trackEdits NS_REFINED_FOR_SWIFT;


@end

API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface METrackInfo (LanguageTagOptionalProperties)

/*!
	@property		extendedLanguageTag
	@abstract		Indicates the language tag associated with the track, as an IETF BCP 47 (RFC 4646) language identifier.
	@discussion		This property may be used by the MediaToolbox to group similar language tracks together or to match audio and caption tracks. If no language tag is indicated, this property should be set to nil.
*/
@property (nonatomic, copy, nullable) NSString* extendedLanguageTag;

@end

API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface METrackInfo (VideoSpecificOptionalProperties)

/*!
	@property		naturalSize
	@abstract		Indicates the natural dimensions of the media data referenced by the track as a CGSize.
	@discussion		This property is only valid for tracks with visual media types and should return CGSizeZero if implemented for other track types.
*/
@property (nonatomic) CGSize naturalSize;

/*!
	@property		preferredTransform
	@abstract		Indicates the preferred affine display transform of the track media for visual display.
	@discussion		Returns an CGAffineTransform representing the preferred affine transform of the track for visual display. This property is only valid for tracks with visual media types and should return CGAffineTransformIdentity if implemented for other track types.
*/
@property (nonatomic) CGAffineTransform preferredTransform;

/*!
	@property		nominalFrameRate
	@abstract		The frame rate of the track, in frames per second, as a 32-bit floating point number.
	@discussion		For field-based video tracks that carry one field per media sample, the value of this property is the field rate, not the frame rate. This information from this property may be used by the MediaToolbox to calculate the maximum playback speed.
*/
@property (nonatomic) Float32 nominalFrameRate;

/*!
	@property		requiresFrameReordering
	@abstract		Indicates whether frame reordering occurs in the track.
	@discussion		The value is YES if frame reordering occurs, NO otherwise. This property is only valid for tracks with video media type and should return NO for if implemented for other track types.
*/
@property (nonatomic) BOOL requiresFrameReordering;

@end


#pragma mark - MESampleCursor

/*!
	@protocol		MESampleCursor
	@abstract		Provides information about samples within a track of a media asset.
	@discussion		The Media Toolbox creates an MESampleCursor object by calling one of the METrackReader sample cursor creation methods. It then makes method calls using the MESampleCursor protocol. MESampleCursors can deliver sample data either by providing sample location and sample chunk information, or by directly generating a sample buffer.
*/
API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@protocol MESampleCursor <NSObject, NSCopying>

/*!
	@property		presentationTimeStamp
	@abstract		The presentation timestamp (PTS) of the sample at the current position of the cursor.
*/
@property (nonatomic, readonly) CMTime presentationTimeStamp;

/*!
	@property		decodeTimeStamp
	@abstract		The decode timestamp (DTS) of the sample at the current position of the cursor.
*/
@property (nonatomic, readonly) CMTime decodeTimeStamp;

/*!
	@property		currentSampleDuration
	@abstract		Indicates the decode duration of the sample at the receiver's current position.
	@discussion		If the receiver must be advanced past its current position in order to determine the decode duration of the current sample, the value of currentSampleDuration is equal to kCMTimeIndefinite. This can occur with streaming formats such as MPEG-2 transport streams.
*/
@property (nonatomic, readonly) CMTime currentSampleDuration;

/*!
	@property		currentSampleFormatDescription
	@abstract		The format description for the sample at the current position of the cursor.
*/
@property (nonatomic, readonly, nullable) __attribute__((NSObject)) CMFormatDescriptionRef currentSampleFormatDescription;

/*!
	@method			stepInDecodeOrderByCount
	@abstract		Moves the cursor a given number of samples in decode order.
	@discussion		If the request would advance the cursor past the last sample or before the first sample, the cursor should be set to point to that limiting sample and actualStepCount will report the number of samples the cursor was able to move.
	@param			stepCount
		The number of samples to move. If positive, step forward this many samples. If negative, step backward (-stepCount) samples.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'actualStepCount'
			The final count of steps taken.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)stepInDecodeOrderByCount:(int64_t)stepCount completionHandler:(void (^)(int64_t actualStepCount, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(stepInDecodeOrder(by:completionHandler:));

/*!@
	@method			stepInPresentationOrderByCount
	@abstract		Moves the cursor a given number of samples in presentation order.
	@discussion		If the request would advance the cursor past the last sample or before the first sample, the cursor should be set to point to that limiting sample and actualStepCount will report the number of samples the cursor was able to move. If decode order and presentation order are the same (ie, the samples are not reordered), this method should have the same effect as stepInDecodeOrderByCount.
	@param			stepCount
		The number of samples to move. If positive, step forward this many samples. If negative, step backward (-stepCount) samples.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'actualStepCount'
			The final count of steps taken.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)stepInPresentationOrderByCount:(int64_t)stepCount completionHandler:(void (^)(int64_t actualStepCount, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(stepInPresentationOrder(by:completionHandler:));

/*!
	@method			stepByDecodeTime
	@abstract		Moves the cursor by a given deltaDecodeTime on the decode timeline.
	@discussion		If the request would advance the cursor past the end of the last sample or before the first sample, the cursor should be set to point to that limiting sample, and positionWasPinned will be set to YES. Otherwise, positionWasPinned will be set to NO.
	@param			deltaDecodeTime
		The cursor is moved to the sample at decode time (current sample decode time + deltaDecodeTime).
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'actualDecodeTime'
			The final cursor decode time. Because sample cursors snap to sample boundaries when stepped, this value may not be equal to (current sample decode time + deltaDecodeTime) even if the cursor was not pinned.
		'positionWasPinned'
			YES if the request attempted to advance the cursor beyond the track limits, otherwise NO.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)stepByDecodeTime:(CMTime)deltaDecodeTime completionHandler:(void (^)(CMTime actualDecodeTime, BOOL positionWasPinned, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(stepByDecodeTime(_:completionHandler:));

/*!
	@method			stepByPresentationTime
	@abstract		Moves the cursor by a given deltaPresentationTime on the presentation timeline.
	@discussion		If the request would advance the cursor past the end of the last sample or before the first sample, the cursor should be set to point to that limiting sample, and positionWasPinned will be set to YES. Otherwise, positionWasPinned will be set to NO.
	@param			deltaPresentationTime
		The cursor is moved to the sample at presentation time (current sample presentation time + deltaPresentationTime).
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'actualPresentationTime'
			The final cursor presentation time. Because sample cursors snap to sample boundaries when stepped, this value may not be equal to (current sample presentation time + deltaPresentationTime) even if the cursor was not pinned.
		'positionWasPinned'
			YES if the request attempted to advance the cursor beyond the track limits, otherwise NO.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)stepByPresentationTime:(CMTime)deltaPresentationTime completionHandler:(void (^)(CMTime actualPresentationTime, BOOL positionWasPinned, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(stepByPresentationTime(_:completionHandler:));

@optional

/*!
	@property		syncInfo
	@abstract		Retrieves decoder synchronization information about the sample pointed to by the cursor.
	@discussion		The returned value will be an AVSampleCursorSyncInfo structure with any valid flags set. If this kind of synchronization information does not make sense for the sequence of samples, this property should not be implemented.
*/
@property (nonatomic, readonly) AVSampleCursorSyncInfo syncInfo;

/*!
	@property		sampleDependencyInfo
	@abstract		Retrieves generic dependency information about the sample pointed to by the cursor.
	@discussion		The returned value will be an AVSampleCursorDependencyInfo structure with any valid flags set. If this kind of dependency information does not make sense for the sequence of samples, this property should not be implemented.
*/
@property (nonatomic, readonly) AVSampleCursorDependencyInfo dependencyInfo;

/*!
	@property		hevcDependencyInfo
	@abstract		Retrieves additional information necessary to recover complete sample dependency information.
	@discussion		hevcDependencyInfo is an optional property that communicates additional sample dependency information not contained in syncInfo or dependencyInfo. Examples of this are the NAL unit type of an HEVC sync sample or the number of samples necessary to refresh the decoder after a USAC Independent Frame. For formats where this information does not make sense, this property should be set to nil.
*/
@property (nonatomic, readonly, copy) MEHEVCDependencyInfo* hevcDependencyInfo;

/*!
	@property		decodeTimeOfLastSampleReachableByForwardSteppingThatIsAlreadyLoadedByByteSource
	@abstract		Retrieves the duration of the content playable from the cursor as a CMTime.
	@discussion		Indicates the time difference between the current cursor DTS and last reachable sample DTS. This is necessary to play assets with e.g. HTTP URLs as it indicates what samples have already been loaded by the byte source.
*/
@property (nonatomic, readonly) CMTime decodeTimeOfLastSampleReachableByForwardSteppingThatIsAlreadyLoadedByByteSource;

/*!
	@method			samplesWithEarlierDTSsMayHaveLaterPTSsThanCursor
	@abstract		Tests for an earlier boundary in sample reordering.
	@discussion		This method tests for a boundary in the reordering from decode order to presentation order, determining when it could be possible for any sample earlier in decode order than the receiver current sample to have a presentation time later than the current sample of the specified cursor. This test can be used to limit backward scans, e.g. to start forward playback. For example, with the argument cursor fixed, step the receiver backwards until it is impossible for any earlier-in-decode-order receiver samples to be later-in-presentation-order than the argument cursor sample. If sample reordering does not make sense for the track content, this method should not be implemented. If this method is not implemented, clients should assume the samples are not reordered.
	@param			cursor
		An instance of id<MESampleCursor> with which to test the sample reordering boundary.
	@result			YES if it is possible earlier samples in decode order than that of the receiver can have a presentation timestamp later than that of the specified sample cursor, otherwise NO. If the receiver and argument cursors reference different sequences of samples, for example if they were created by different instances of MTTrackReader, the results are undefined.
*/
-(BOOL)samplesWithEarlierDTSsMayHaveLaterPTSsThanCursor:(id<MESampleCursor>)cursor NS_SWIFT_NAME(samplesWithEarlierDTSsMayHaveLaterPTSs(than:));

/*!
	@method			samplesWithLaterDTSsMayHaveEarlierPTSsThanCursor
	@abstract		Tests for a later boundary in sample reordering.
	@discussion		This method tests for a boundary in the reordering from decode order to presentation order, determining when it could be possible for any sample later in decode order than the receiver current sample to have a presentation time earlier than the current sample of the specified cursor. This test can be used to limit forward scans, e.g. to start reverse playback. For example, with the argument cursor fixed, step the receiver forwards until it is impossible for any later-in-decode-order receiver samples to be earlier-in-presentation-order than the argument cursor sample. If sample reordering does not make sense for the track content, this method should not be implemented. If this method is not implemented, clients should assume the samples are not reordered.
	@param			cursor
		An instance of id<MESampleCursor> with which to test the sample reordering boundary.
	@result			YES if it is possible later samples in decode order than that of the receiver can have a presentation timestamp earlier than that of the specified sample cursor, otherwise NO. If the receiver and argument cursors reference different sequences of samples, for example if they were created by different instances of MTTrackReader, the results are undefined.
*/
-(BOOL)samplesWithLaterDTSsMayHaveEarlierPTSsThanCursor:(id<MESampleCursor>)cursor NS_SWIFT_NAME(samplesWithLaterDTSsMayHaveEarlierPTSs(than:));

/*!
 Overview of MESampleCursor Sample Delivery
 
 An MESampleCursor can return sample data to CoreMedia in one of two ways. Either it can return just information about the sample data location in the media and let CoreMedia do the actual reading of the data, or it can read the data iself and return sample buffers directly.
 
 The MESampleCursor allows CoreMedia to read the data
 ----------------------------------------------------
 
 This is the preferred method to deliver sample data. It allows CoreMedia to optimize data I/O read operations, potentially combining multiple smaller reads into a single larger read for better performance. There are four methods available to deliver the required sample location information.
 
 - sampleLocationReturningError:error
 This is the main method to return sample location information. In order to allow CoreMedia to optimize I/O, the MESampleCursor must provide either this method or the two methods estimatedSampleLocationReturningError: and refineSampleLocation:. For formats where samples are stored in contiguous groups or blocks, this method will be used together with chunkDetailsReturningError:. For formats where samples are stored individually (e.g. video), implementation of chunkDetailsReturningError: is optional.
 
 - chunkDetailsReturningError:error
 For formats where samples are stored in contiguous groups, blocks, or chunks (e.g. audio), this method is used to indicate details about how many samples are stored in each grouping and the sample offset within the group. After determining the chunk information, CoreMedia will then call either sampleLocationReturningError: or estimatedSampleLocationReturningError: followed by refineSampleLocation: to locate individual samples within the chunk.
 
 - estimatedSampleLocationReturningError:error
 In some cases it is not possible to directly determine the sample location and return it through sampleLocationReturningError:. Instead, the sample location must be determined in two steps: a coarse estimatation followed by a refinement operation to find the exact location. This method returns the coarse estimation of the location, and the second step is refineSampleLocation:refinementData: to return the exact location. Both methods must be implemented to support this functionality.
  
 - refineSampleLocation:refinementData:refinementDataLength:refinedLocation:error
 This method returns the exact sample location information as a second step after the coarse estimate from estimatedSampleLocationReturningError:. This method must be implemented together with estimatedSampleLocationReturningError: in order to support the two-step location functionality.
 
 The MESampleCursor reads sample buffers directly
 ------------------------------------------------

 In cases where it is not possible to let CoreMedia read the sample data using location information, the MESampleCursor will need to read the sample data itself using the MEByteSource and deliver sample data buffers to CoreMedia. This is less efficient for data I/O because it does not allow CoreMedia to optimize read operations.
  
 - loadSampleBufferContainingSamplesToEndCursor:completionHandler:
 This method delivers sample buffers directly, so it allows the MESampleCursor full flexibility in reading and unpacking the samples from the media. The MESampleCursor must use the MEByteSource directly to seek and read the sample data. This method can deliver sample buffers either with one sample (e.g. for video tracks) or with blocks of samples (e.g. for audio). It is also suitable for cases where samples must be synthesized using metadata from the media (e.g. for timecode tracks).
 
 Practical Examples
 ------------------
 
 (1) Samples are stored in groups interleaved among other samples
 The MESampleCursor should implement sampleLocationReturningError: and chunkDetailsReturningError: to allow CoreMedia to locate the chunks and find samples inside the chunks.
 
 (2) Samples are stored in blocks interleaved among other samples, but some samples are non-contiguous
 The MESampleCursor should implement sampleLocationReturningError:, chunkDetailsReturningError:, and loadSampleBufferContainingSamplesToEndCursor:. For contiguous samples, sampleLocationReturningError: should return with no error and the samples will be read this way. For non-contiguous samples, sampleLocationReturningError: and chunkDetailsReturningError: should return MEErrorLocationNotAvailable and CoreMedia will then attempt to read the samples using loadSampleBufferContainingSamplesToEndCursor:.
 
 (3) Sample location cannot be directly determined in one step
 If the sample location cannot be determined as a one-step process but is possible using a two-step, "coarse estimate followed by refinement" process, then the MESampleCursor should implement estimatedSampleLocationReturningError: and refineSampleLocation: instead of sampleLocationReturningError:. If determining the sample location does not fit into either the one-step or two-step model, then the MESampleCursor should implement loadSampleBufferContainingSamplesToEndCursor:.
 
 (4) Sample data must be unpacked or prepared in some way before delivering to CoreMedia
 If the sample data cannot be read directly by CoreMedia, then the MESampleCursor should implement loadSampleBufferContainingSamplesToEndCursor: to read the data itself, unpack or prepare it as appropriate, and deliver it in sample buffers.

*/

/*!
	@method  		chunkDetailsReturningError
	@abstract		Returns information about the chunk holding the sample indicated by the cursor.
	@discussion		If the sample resides in a contiguous chunk of the file among similar samples, chunkDetails returns information about that chunk. Note: For some media asset formats it is not practical to implement chunkDetails. In this case chunkDetails should return MEErrorLocationNotAvailable and loadSampleBufferContainingSamplesToEndCursor must be used to load the sample data.
	@param			error
		If provided, returns error information in the event that the method fails.
	@result			Returns an instance of MESampleCursorChunk with details about the chunk if successful, returns NULL and fails with MEErrorLocationNotAvailable if sampleCursor does not support chunkDetails, or returns NULL if the method otherwise fails with error.
*/
- (MESampleCursorChunk * _Nullable) chunkDetailsReturningError:(NSError *__autoreleasing _Nullable * _Nullable) error NS_SWIFT_NAME(chunkDetails());

/*!
	@method			sampleLocationReturningError
	@abstract		Returns the location and byte source of the sample indicated by the cursor.
	@discussion		This method is used to allow the system to handle reading the sample data. Sample data is expected to be contiguous. For some media asset formats, most samples are contiguous but there are exceptions; such MESampleCursors should support both sampleLocation and loadSampleBufferContainingSamplesToEndCursor. For samples that are not contiguous, sampleLocation should return MEErrorLocationNotAvailable. For other media asset formats, it is not practical to implement sampleLocation; such MESampleCursors must implement loadSampleBufferContainingSamplesToEndCursor instead.
	@param			error
		If provided, returns error information in the event that the method fails.
	@result			Returns an instance of MESampleLocation with information about the sample location if successful, returns NULL and fails with MEErrorLocationNotAvailable if the sample is not contiguous or this method is not supported, in which case loadSampleBufferContainingSamplesToEndCursor must be called instead in order to load the sample data, or returns NULL if the method otherwise fails with error.
*/
- (MESampleLocation * _Nullable) sampleLocationReturningError:(NSError *__autoreleasing _Nullable * _Nullable) error NS_SWIFT_NAME(sampleLocation());

/*!
	@method			estimatedSampleLocationReturningError
	@abstract		Returns an estimate of the sample location indicated by the cursor that can later be refined using refineSampleLocation.
	@discussion		Optional addition to sampleLocationReturningError. For formats that need to read some data on a per-sample basis to produce the exact sample location, it may be more efficient to read a slightly larger chunk of data containing both the data necessary to produce the exact sample location and the actual sample data. The exact sample location will then be requested in a subsequent call to refineSampleLocation. It is possible to indicate that no refinement is necessary by returning a value for refinementDataLocation that has a zero length. If a non-zero length refinement location is returned, the range for the estimated sample location returned must fully cover the refined range returned by refineSampleLocation and the refinement data location. Note: Implementing estimatedSampleLocationReturningError also requires implementing refineSampleLocation. If the sample indicated by the cursor is not contiguous, this method will return MEErrorLocationNotAvailable. In this case the loadSampleBufferContainingSamplesToEndCursor must be used to load the sample data.
	@param			error
		If provided, returns error information in the event that the method fails.
	@result			Returns an instance of MEEstimatedSampleLocation with information about the estimated sample location if successful, returns NULL and fails with MEErrorLocationNotAvailable if the sample is not contiguous or this method is not supported, in which case loadSampleBufferContainingSamplesToEndCursor must be called instead in order to load the sample data, or returns NULL if the method otherwise fails with error.
 */
- (MEEstimatedSampleLocation * _Nullable) estimatedSampleLocationReturningError:(NSError *__autoreleasing _Nullable * _Nullable)error NS_SWIFT_NAME(estimatedSampleLocation());

/*!
	@method			refineSampleLocation
	@abstract		Produces an exact sample location based on data returned from a call to estimatedSampleLocationReturningError.
	@discussion		See the discussion in estimatedSampleLocationReturningError for details.
	@param			estimatedSampleLocation
		The value that was previously returned in the MEEstimatedSampleLocation object from estimatedSampleLocationReturningError
	@param			refinementData
		The refinement data returned from estimateSampleLocation in MEEstimatedSampleLocation.
	@param			refinementDataLength
		The length of refinementData in bytes.
	@param			refinedLocationOut
		Returns the exact starting file offset and size of the sample in bytes.
	@param			error
		If provided, returns error information in the event that the method fails.
	@result			YES if the method succeeds, NO if it fails. If the method fails, error will contain error information.
*/
- (BOOL)refineSampleLocation:(AVSampleCursorStorageRange)estimatedSampleLocation
		refinementData:(const uint8_t *)refinementData
		refinementDataLength:(size_t)refinementDataLength
		refinedLocation:(AVSampleCursorStorageRange * _Nonnull)refinedLocationOut
		error:(NSError *__autoreleasing _Nullable * _Nullable)error
NS_SWIFT_NAME(refineSampleLocation(_:refinementData:refinementDataLength:refinedLocation:));

/*!
	@method			loadSampleBufferContainingSamplesToEndCursor
	@abstract		Builds a sample buffer containing the sample(s) at the cursor.
	@discussion		This method is to be implemented by those plugin format readers that always load sample data in order to answer cursor queries. If a plugin format reader does not implement sampleLocation, implementing loadSampleBufferContainingSamplesToEndCursor is required. If the MESampleCursor does implement sampleLocation, implementing loadSampleBufferContainingSamplesToEndCursor is optional. Important note: If there is a change of format description between the receiver and endSampleCursor, the returned sample buffer must contain only the contiguous samples with the same format description as the first sample. If there is no sample data between cursor and endSampleCursor, this method should return an empty sample buffer. This method should only provide a NULL sample buffer when there is an error.
	@param			endSampleCursor
		If not nil, indicates the last sample that the new sample buffer should contain. If endSampleCursor refers to a sample earlier than the receiver, this method should fail and return MEErrorNoSamples as error code. If endSampleCursor is nil or refers to the same sample as the receiver, only a single sample should be returned in the new sample buffer.
	@param			completionHandler
		The handler that will be invoked when the method completes.
		'newSampleBuffer'
			A CMSampleBufferRef with the newly created sample buffer. If the sample cursor is implemented in Objective-C, it is the responsibility of the sample cursor implementation to balance the creation of this sample buffer by calling CFRelease.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)loadSampleBufferContainingSamplesToEndCursor:(nullable id<MESampleCursor>)endSampleCursor completionHandler:(void (^)(CMSampleBufferRef _Nullable newSampleBuffer, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(loadSampleBufferContainingSamples(to:completionHandler:));

/*!
	@method			loadPostDecodeProcessingMetadataWithCompletionHandler
	@abstract		Asynchronously loads a dictionary that represents frame level metadata for post decode processing.
	@discussion		This method should provide either a valid NSDictionary or nil. If the method fails, the NSError will contain error information.
					The post decode processing metadata could either be contained in the media asset primary file or be located in a separate related "sidecar" file. If contained in a separate file with a different extension, that file extension should be included in the EXAppExtensionAttributes and UTExportedTypeDeclarations dictionaries in the MediaExtension format reader Info.plist. The metadata returned should contain sequence level metadata for post decode processing, along with optional frame level metadata if present.
	@param			completionHandler
		The handler that will be invoked when the method completes, or if it is nil.
		'postDecodeProcessingMetadata'
			The returned NSDictionary should conform to a CFPropertyList.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil.
*/
- (void)loadPostDecodeProcessingMetadataWithCompletionHandler:(void (^)(NSDictionary<NSString *, id> * NS_SWIFT_SENDABLE _Nullable postDecodeProcessingMetadata, NSError * _Nullable error))completionHandler 
	NS_SWIFT_ASYNC_NAME(postDecodeProcessingMetadata());

@end


#pragma mark - MESampleCursorChunk

/*!
	@interface		MESampleCursorChunk
	@abstract		Provides information about the chunk of media where a sample is located.
	@discussion		An instance of this class is returned by calls to the MESampleCursor method chunkDetails.
*/
NS_SWIFT_SENDABLE API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MESampleCursorChunk : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

/*!
	@property		initWithByteSource
	@abstract		The initializer for the MESampleCursorChunk class.
	@param			byteSource
		The MEByteSource to be used to read the data for the sample.
	@param			chunkStorageRange
		The offset location and length of the sample's chunk within the MEByteSource.
	@param			chunkInfo
		A completed AVSampleCursorChunkInfo with details about the chunk in the media.
	@param			sampleIndexWithinChunk
		The offset of the sample within the chunk, in samples.
*/
- (instancetype)initWithByteSource:(MEByteSource *)byteSource chunkStorageRange:(AVSampleCursorStorageRange)chunkStorageRange chunkInfo:(AVSampleCursorChunkInfo)chunkInfo sampleIndexWithinChunk:(CFIndex)sampleIndexWithinChunk NS_DESIGNATED_INITIALIZER;

/*!
	@property		byteSource
	@abstract		The MEByteSource to be used to read the data for the sample.
*/
@property (nonatomic, readonly, retain) MEByteSource* byteSource;

/*!
	@property		chunkStorageRange
	@abstract		The offset location and length of the sample's chunk, in bytes, within the MEByteSource.
	@discussion		The length should be set to 0 if there is no chunk associated with the sample.
*/
@property (nonatomic, readonly) AVSampleCursorStorageRange chunkStorageRange;

/*!
	@property		chunkInfo
	@abstract		Provides information about the chunk of media samples.
*/
@property (nonatomic, readonly) AVSampleCursorChunkInfo chunkInfo;

/*!
	@property		sampleIndexWithinChunk
	@abstract		The offset of the sample within the chunk, in samples.
	@discussion		Index value 0 corresponds to the start of the chunk. You would step back this many samples to position the cursor at the start of the chunk. Subtract from the chunkInfo.chunkSampleCount field to obtain the number of samples to the end of the chunk.
*/
@property (nonatomic, readonly) CFIndex sampleIndexWithinChunk;

@end


#pragma mark - MESampleLocation

/*!
	@interface		MESampleLocation
	@abstract		Provides information about the sample location with the media.
	@discussion		An instance of this class is returned by calls to the MESampleCursor method sampleLocation.
*/
NS_SWIFT_SENDABLE API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MESampleLocation : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

/*!
	@property		initWithByteSource
	@abstract		The initializer for the MESampleLocation class.
	@param			byteSource
		The MEByteSource to be used to read the data for the sample.
	@param			sampleLocation
		The starting file offset and size in bytes of the sample.
*/
- (instancetype)initWithByteSource:(MEByteSource *)byteSource sampleLocation:(AVSampleCursorStorageRange)sampleLocation NS_DESIGNATED_INITIALIZER;

/*!
	@property		sampleLocation
	@abstract		The starting file offset and size in bytes of the sample.
*/
@property (nonatomic, readonly) AVSampleCursorStorageRange sampleLocation;

/*!
	@property		byteSource
	@abstract		The MEByteSource to be used to read the data for the sample.
*/
@property (nonatomic, retain, readonly) MEByteSource* byteSource;

@end


#pragma mark - MEEstimatedSampleLocation

/*!
	@interface		MEEstimatedSampleLocation
	@abstract		Provides information about the estimated sample location with the media.
	@discussion		An instance of this class is returned by calls to the MESampleCursor method estimatedSampleLocationReturningError.
*/
NS_SWIFT_SENDABLE API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MEEstimatedSampleLocation : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

/*!
	@property		initWithByteSource
	@abstract		The initializer for the MEEstimatedSampleLocation class.
	@param			byteSource
		The MEByteSource to be used to read the data for the sample.
	@param			estimatedSampleLocation
		The estimated starting file offset and size in bytes of the sample.
	@param			refinementDataLocation
		The starting file offset and size in bytes of the the data necessary to provide an accurate sample location.
*/
- (instancetype)initWithByteSource:(MEByteSource *)byteSource estimatedSampleLocation:(AVSampleCursorStorageRange)estimatedSampleLocation refinementDataLocation:(AVSampleCursorStorageRange)refinementDataLocation NS_DESIGNATED_INITIALIZER;

/*!
	@property		estimatedSampleLocation
	@abstract		The estimated starting file offset and size in bytes of the sample.
*/
@property (nonatomic, readonly) AVSampleCursorStorageRange estimatedSampleLocation;

/*!
	@property		refinementDataLocation
	@abstract		The starting file offset and size in bytes of the the data necessary to provide an accurate sample location.
	@discussion		The refinement data can be provided to the MESampleCursor method refineSampleLocation to determine the exact sample location.
*/
@property (nonatomic, readonly) AVSampleCursorStorageRange refinementDataLocation;

/*!
	@property		byteSource
	@abstract		The MEByteSource to be used to read the data for the sample.
*/
@property (nonatomic, retain, readonly) MEByteSource* byteSource;

@end


#pragma mark - MEHEVCDependencyInfo

/*!
	@interface		MEHEVCDependencyInfo
	@abstract		Provides information about the HEVC dependency attributes of a sample.
	@discussion		An instance of this class is returned by MESampleCursor property hevcDependencyInfo.
*/
NS_SWIFT_SENDABLE API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MEHEVCDependencyInfo : NSObject <NSCopying>

/*!
	@property		temporalSubLayerAccess
	@abstract		YES if the sample is an HEVC 'TSA' picture, NO otherwise.
	@discussion		Maps to the kCMSampleAttachmentKey_HEVCTemporalSubLayerAccess sample buffer attachment.
*/
@property (nonatomic, getter=hasTemporalSubLayerAccess) BOOL temporalSubLayerAccess;

/*!
	@property		stepwiseTemporalSubLayerAccess
	@abstract		YES if the sample is an HEVC 'STSA' picture, NO otherwise.
	@discussion		Maps to the kCMSampleAttachmentKey_HEVCStepwiseTemporalSubLayerAccess sample buffer attachment.
*/
@property (nonatomic, getter=hasStepwiseTemporalSubLayerAccess) BOOL stepwiseTemporalSubLayerAccess;

/*!
	@property		syncSampleNALUnitType
	@abstract		The NAL unit type for HEVC 'sync' sample groups, or -1 if this information is not available.
	@discussion		Maps to the kCMSampleAttachmentKey_HEVCSyncSampleNALUnitType sample buffer attachment.
*/
@property (nonatomic) int16_t syncSampleNALUnitType;

@end


#pragma mark - MEHEVCDependencyInfo (HEVCTemporalLevelInfo)

/*!
	@category		MEHEVCDependencyInfo HEVCTemporalLevelInfo
	@abstract		Indicates a video frame's level within a hierarchical frame dependency structure.
	@discussion		The properties here map to the kCMSampleAttachmentKey_HEVCTemporalLevelInfo sample buffer attachment dictionary.
*/
NS_SWIFT_SENDABLE API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MEHEVCDependencyInfo (HEVCTemporalLevelInfo)

/*!
	@property		temporalLevel
	@abstract		The HEVC temporal level, or -1 if this information is not available.
	@discussion		Maps to the kCMHEVCTemporalLevelInfoKey_TemporalLevel sample buffer attachment.
*/
@property (nonatomic) int16_t temporalLevel;

/*!
	@property		profileSpace
	@abstract		The HEVC profile space, or -1 if this information is not available.
	@discussion		Maps to the kCMHEVCTemporalLevelInfoKey_ProfileSpace sample buffer attachment.
*/
@property (nonatomic) int16_t profileSpace;

/*!
	@property		tierFlag
	@abstract		The HEVC tier level flag, or -1 if this information is not available.
	@discussion		Maps to the kCMHEVCTemporalLevelInfoKey_TierFlag sample buffer attachment.
*/
@property (nonatomic) int16_t tierFlag;

/*!
	@property		profileIndex
	@abstract		The HEVC profile index, or -1 if this information is not available.
	@discussion		Maps to the kCMHEVCTemporalLevelInfoKey_ProfileIndex sample buffer attachment.
*/
@property (nonatomic) int16_t profileIndex;

/*!
	@property		profileCompatibilityFlags
	@abstract		The HEVC profile compatibility flags (4 bytes), or nil of this information is not available.
	@discussion		Maps to the kCMHEVCTemporalLevelInfoKey_ProfileCompatibilityFlags sample buffer attachment.
*/
@property (nonatomic, copy, nullable) NSData* profileCompatibilityFlags;

/*!
	@property		constraintIndicatorFlags
	@abstract		The HEVC constraint indicator flags (6 bytes), or nil of this information is not available.
	@discussion		Maps to the kCMHEVCTemporalLevelInfoKey_ConstraintIndicatorFlags sample buffer attachment.
*/
@property (nonatomic, copy, nullable) NSData* constraintIndicatorFlags;

/*!
	@property		levelIndex
	@abstract		The HEVC level index, or -1 if this information is not available.
	@discussion		Maps to the kCMHEVCTemporalLevelInfoKey_LevelIndex sample buffer attachment.
*/
@property (nonatomic) int16_t levelIndex;

@end


#pragma mark - MEByteSource

/*!
	@interface		MEByteSource
	@abstract		Provides read access to the data in a media asset file.
	@discussion		The Media Toolbox passes an MEByteSource instance for the media asset's primary file when initializing an MEFormatReader object. The MEFormatReader may request additional MEByteSources be created for related files in the same directory as the primary file by calling the byteSourceForRelatedFileName method.
*/
NS_SWIFT_SENDABLE API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface MEByteSource : NSObject

+ (instancetype) new NS_UNAVAILABLE;

- (instancetype) init NS_UNAVAILABLE;

/*!
	@property   	fileName
	@abstract		The name of a MEByteSource's file.
	@discussion		The name of the source file for the MEByteSource.
*/
@property (nonatomic, readonly) NSString* fileName;

/*!
	@property   	contentType
	@abstract		A UTType indicating the format of the MEByteSource's file.
	@discussion		A UTType indicating the format of the source file for the MEByteSource.
*/
@property (nonatomic, readonly, nullable) UTType* contentType;

/*!
	@property		fileLength
	@abstract		The length of the MEByteSource's file.
	@discussion		The length in bytes of the source file for the MEByteSource, or 0 if that information is not available.
*/
@property (nonatomic, readonly) int64_t fileLength;

/*!
	@property		relatedFileNamesInSameDirectory
	@abstract		The array of related file names in the MEByteSource's parent directory.
	@discussion		The array of related files within the MEByteSource's parent directory that are accessible to the MEByteSource. Only the relative file names are returned, not the paths. If no related files are available, returns an empty array.
*/
@property (nonatomic, readonly) NSArray<NSString *> * relatedFileNamesInSameDirectory;

/*!
	@method     	readDataOfLength:fromOffset:toDestination:completionHandler:
	@abstract		Reads bytes from an MEByteSource asynchronously into a buffer.
	@discussion		Asynchronously reads out the specified number of bytes starting at the indicated offset. Returns the actual number of bytes read out in bytesRead. Read attempts that extend beyond the end of the MEByteSource will succeed if they include at least one valid byte before the end of the MEByteSource.
	@param			length
		The number of bytes to read.
	@param			offset
		The relative offset in bytes from the beginning of the file from which to start reading.
	@param			dest
		The block of memory to hold the data to be read.  Must be at least num bytes in length.
	@param 			completionHandler
		The handler that will be invoked when the method completes.
		'bytesRead'
			The actual number of bytes read.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil. Returns MEErrorEndOfStream if no more bytes can be read.
*/
- (void) readDataOfLength:(size_t)length fromOffset:(int64_t)offset toDestination:(void *)dest completionHandler:(void (^)(size_t bytesRead, NSError * _Nullable error))completionHandler NS_SWIFT_UNAVAILABLE("Use 'read(length:from:completionHandler:)' instead");

/*!
	@method     	readDataOfLength:fromOffset:completionHandler:
	@abstract		Reads bytes from an MEByteSource asynchronously into an NSData object.
	@discussion		Asynchronously reads out the specified number of bytes starting at the indicated offset. Returns the actual number of bytes read out in bytesRead. Read attempts that extend beyond the end of the MEByteSource will succeed if they include at least one valid byte before the end of the MEByteSource.
	@param			length
		The number of bytes to read.
	@param			offset
		The relative offset in bytes from the beginning of the file from which to start reading.
	@param			completionHandler
		Completion block called when the method completes.
		'data'
			The NSData object holding the data that have been read. The NSData length property will indicate the actual number of bytes read.
		'error'
			An NSError object that will contain error information if the method fails, otherwise nil. Returns MEErrorEndOfStream if no more bytes can be read.
*/
- (void) readDataOfLength:(size_t)length fromOffset:(int64_t)offset completionHandler:(void (^)(NSData * _Nullable data, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(read(length:from:completionHandler:));

/*!
	@method     	readDataOfLength:fromOffset:toDestination:bytesRead:error
	@abstract		Reads bytes from an MEByteSource synchronously into a buffer.
	@discussion		Synchronously reads out the specified number of bytes starting at the indicated offset. Returns the actual number of bytes read out in bytesReadOut. Read attempts that extend beyond the end of the MEByteSource will succeed if they include at least one valid byte before the end of the MEByteSource.
	@param			length
		The number of bytes to read.
	@param			offset
		The relative offset in bytes from the beginning of the file from which to start reading.
	@param			dest
		The block of memory to hold the data to be read.  Must be at least num bytes in length.
	@param			bytesReadOut
		The actual number of bytes read.
	@param			error
		Reports any errors. Returns MEErrorEndOfStream if no more bytes can be read.
	@result			Returns YES if successful, NO if an error occured.
*/
- (BOOL) readDataOfLength:(size_t)length fromOffset:(int64_t)offset toDestination:(void *)dest bytesRead:(size_t *)bytesReadOut error:(NSError * __autoreleasing _Nullable * _Nullable)error NS_SWIFT_UNAVAILABLE("Use 'read(length:from:completionHandler:)' instead");

/*!
	@method			availableLengthAtOffset:
	@abstract		Returns the number of available bytes from the offset within the MEByteSource.
	@discussion		Returns the number of available bytes at the time of the query. This value could change over time. Attempting to read past this value may cause slow I/O.
	@param			offset
		The offset in bytes from the beginning of the MEByteSource.
	@result			Returns the number of available bytes from the offset, or 0 if that information is not available.
*/
- (int64_t) availableLengthAtOffset:(int64_t)offset NS_SWIFT_NAME(availableLength(at:));

/*!
	@method			byteSourceForRelatedFileName:error:
	@abstract		Requests creation of a new MEByteSource for a related file.
	@discussion		Requests creation of a new MEByteSource for a file related to the receiving MEByteSource. The scope of fileName that may be opened is restricted. Only files in the same directory as the receiver MEByteSource may be accessed, and the file extension must match one of the extensions listed in the format reader bundle plist.
	@param			fileName
		The relative file name in the receiver MEByteSource's parent directory.
	@param			errorOut
		Reports any errors. Returns MEErrorPermissionDenied if the file cannot be accessed or is prohibited.
	@result			Returns nil if fileName refers to a file that cannot be accessed or is prohibited, or if an error occured. The returned MEByteSource is autoreleased.
*/
- (MEByteSource * _Nullable) byteSourceForRelatedFileName:(NSString *)fileName error:(NSError * _Nullable * _Nullable)errorOut NS_SWIFT_NAME(byteSourceForRelatedFileName(_:));

@end


NS_ASSUME_NONNULL_END

#endif /* MEFormatReader_h */

