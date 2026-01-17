#if !__has_include(<AVFCore/AVPlayerOutput.h>)
/*
 	File:		AVPlayerOutput.h
 
 	Framework:	AVFoundation
 
 	Copyright 2024 Apple Inc. All rights reserved.
 */

#import <AVFoundation/AVBase.h>
#import <CoreMedia/CMTaggedBufferGroup.h>
#import <CoreMedia/CMTagCollection.h>
#import <CoreGraphics/CGAffineTransform.h>

@class AVVideoOutputSpecification;
@class AVPlayerVideoOutputConfiguration;
@class AVPlayerItem;

NS_ASSUME_NONNULL_BEGIN

/*!
	@class      AVPlayerVideoOutput
	@abstract   AVPlayerVideoOutput offers a way to attach to an AVPlayer and receive video frames and video-related data vended through CMTaggedBufferGroups.
	@discussion AVPlayerVideoOutput can be attached to an AVPlayer using AVPlayer's method addVideoOutput:
				Note:  An AVPlayerVideoOutput can only be attached to a single player at a time, attempting to attach to multiple player will result in an exception being thrown.
				Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.2), ios(17.2), tvos(17.2), watchos(10.2), visionos(1.1))
@interface AVPlayerVideoOutput : NSObject
AV_INIT_UNAVAILABLE

/*!
	@method 	initWithSpecification:
	@abstract 	Creates an instance of AVPlayerVideoOutput, initialized with the specified video output specification.
	@param 		specification
				An instance of AVVideoOutputSpecification, used to recommend data channels to the AVPlayer associated with this AVPlayerVideoOutput.
				The tag collections owned by the AVVideoOutputSpecification will be given a priority based on their position in the array which they are held by AVVideoOutputSpecification, meaning position i takes priority over position i+1.
				This means that the player will first check if the tag collection at index 0 matches the shape of the current item's data channels.
				If the item's data channels would not be able satisfy the shape of the requested tag collection, it will fall back to the next collection and repeat this process.
				This continues until a tag collection or set of tag collection can be selected, otherwise if no collections match the shape of the item’s data channels then samples cannot be vended for that item.
	@result		An instance of AVPlayerVideoOutput.
	@discussion Output settings will be selected from the input AVVideoOutputSpecification based on the data channels selected for an item.
				If no output settings were set for the selected tag collection, then the default output settings from the AVVideoOutputSpecification will be used if those were set.
 */
- (instancetype)initWithSpecification:(AVVideoOutputSpecification *)specification;

/*!
	@method 	copyTaggedBufferGroupForHostTime:presentationTimeStamp:activeConfiguration
	@abstract	Retrieves a tagged buffer group that is appropriate for display at the specified host time.
	@param		hostTime
				A CMTime that expresses a desired host time.
	@param		presentationTimeStamp
				On return points to a CMTime whose value is the presentation time in terms of the corresponding AVPlayerItem's timebase for the copied tagged buffer group, or kCMTimeInvalid if no sample is available for the provided hostTime.
				Note: This timestamp is in terms of the timebase of the AVPlayerItem for which this sample is associated.
 	@param		activeConfiguration
 				On return points to the active configuration associated with the copied tagged buffer group, or nil, if no sample is available for the provided hostTime.
	@result		A tagged buffer group for the specified host time if a sample is available, and NULL otherwise.
	@discussion The client is responsible for releasing the returned CMTaggedBufferGroup.
 */
- (CMTaggedBufferGroupRef _Nullable)copyTaggedBufferGroupForHostTime:(CMTime)hostTime
											   presentationTimeStamp:(CMTime * _Nullable)presentationTimeStampOut
												 activeConfiguration:(AVPlayerVideoOutputConfiguration * _Nullable * _Nullable)activeConfigurationOut NS_REFINED_FOR_SWIFT CF_RETURNS_RETAINED;
@end

#pragma mark - CMTagCollectionExtensions Extensions
/*!
	@enum			CMTagCollectionVideoOutputPreset
	@discussion		Video output presets supported by CMTagCollectionCreateWithVideoOutputPreset.
	@constant		kCMTagCollectionVideoOutputPreset_Monoscopic
					Used for video output where there is no stereo view, e.g. kCMTagStereoNone.
	@constant 		kCMTagCollectionVideoOutputPreset_Stereoscopic
					Used for video output where there are two stereo views, for both left and right eyes, e.g. kCMTagStereoLeftAndRight.
 */
typedef CF_ENUM(uint32_t, CMTagCollectionVideoOutputPreset) {
	kCMTagCollectionVideoOutputPreset_Monoscopic,
	kCMTagCollectionVideoOutputPreset_Stereoscopic,
} API_AVAILABLE(macos(14.2), ios(17.2), tvos(17.2), watchos(10.2), visionos(1.1))
  CF_REFINED_FOR_SWIFT;

/*!
	@function	CMTagCollectionCreateWithVideoOutputPreset
	@abstract	Creates a CMTagCollection with the required tags to describe the specified video output requirements.
	@discussion	Convenience constructor to create a CMTagCollection with all of the required tags for use with video output interfaces.
	@param		allocator
				CFAllocator to use to create the collection and internal data structures.
	@param		preset
				CMTagCollectionVideoOutputPreset representing the desired video output scenario.
	@param		newCollectionOut
				Address of a location to the newly created CMTagCollection.  The client is responsible for releasing the returned CMTagCollection.
	@result		noErr if successful. Otherwise, an error describing why a tag collection could not be created.
 */

AVF_EXPORT OSStatus CMTagCollectionCreateWithVideoOutputPreset(
				CFAllocatorRef CM_NULLABLE allocator,
				CMTagCollectionVideoOutputPreset preset,
				CM_RETURNS_RETAINED_PARAMETER CMTagCollectionRef CM_NULLABLE * CM_NONNULL newCollectionOut)
				API_AVAILABLE(macos(14.2), ios(17.2), tvos(17.2), watchos(10.2), visionos(1.1))
				CF_REFINED_FOR_SWIFT;

/*!
	@class 		AVVideoOutputSpecification
	@abstract	AVVideoOutputSpecification offers a way to package CMTagCollections together with output settings. Allowing for direct association between output settings and specific tag collections, as well as default output settings which can be associated with all tag collections which do not have a specified mapping.
	@discussion	For more information about working with CMTagCollections and CMTags first look at <CoreMedia/CMTagCollection.h>
 */
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(14.2), ios(17.2), tvos(17.2), watchos(10.2), visionos(1.1))
@interface AVVideoOutputSpecification : NSObject<NSCopying>
AV_INIT_UNAVAILABLE

/*!
	@method	 	 initWithTagCollections:
 	@abstract	 Creates an instance of AVVideoOutputSpecification initialized with the specified tag collections.
 	@param		 tagCollections
				 Expects a non-empty array of CMTagCollections.  Tag collections are given priority based on their position in the array, where position i take priority over position i+1.
 	@discussion  This method throws an exception for the following reasons:
			 		- tagCollections is nil or has a count of 0.
					- tagCollections contains elements that are not of the type CMTagCollection.
 */
- (instancetype)initWithTagCollections:(NSArray *)tagCollections NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/*!
 	@method 		setOutputPixelBufferAttributes:forTagCollection:
 	@abstract   	Specifies a mapping between a tag collection and a set of pixel buffer attributes.
 	@param			pixelBufferAttributes
 					The client requirements for CVPixelBuffers related to the tags in tagCollection, expressed using the constants in <CoreVideo/CVPixelBuffer.h>.
 	@param			tagCollection
					A single tag collection for which these pixel buffer attributes should map to.
 	@discussion 	If this method is called twice on the same tag collection, the first requested pixel buffer attributes will be overridden.
 	@note			Pixel buffer attributes are translated into output settings, therefore, the rules of `-setOutputSettings:forTagCollection` apply to this method as well.
 					Namely, if you set pixel buffer attributes for a tag collection and then output settings for that same tag collection, your pixel buffer attributes will be overridden and vice-versa.
 	*/
- (void)setOutputPixelBufferAttributes:(nullable NSDictionary<NSString *, id> *)pixelBufferAttributes forTagCollection:(CMTagCollectionRef)tagCollection
		NS_REFINED_FOR_SWIFT API_DEPRECATED_WITH_REPLACEMENT("setOutputSettings:forTagCollection:", macos(14.2, API_TO_BE_DEPRECATED), ios(17.2, API_TO_BE_DEPRECATED), tvos(17.2, API_TO_BE_DEPRECATED), watchos(10.2, API_TO_BE_DEPRECATED), visionos(1.1, API_TO_BE_DEPRECATED));

/*!
	@method			setOutputSettings:forTagCollection
	@abstract		Specifies a mapping between a tag collection and a set of output settings.
 	@param			outputSettings
					The client requirements for output CVPixelBuffers related to the tags in tagCollection, expressed using the constants in AVVideoSettings.h.
 					For uncompressed video output, start with kCVPixelBuffer* keys in <CoreVideo/CVPixelBuffer.h>.
 					In addition to the keys in CVPixelBuffer.h, uncompressed video settings dictionaries may also contain the following keys:
 						- AVVideoAllowWideColorKey
 	@param			tagCollection
 					A single tag collection for which these output settings should map to.
 	@discussion		If this method is called twice on the same tag collection, the first requested output settings will be overridden.
 	@note			This method throws an exception for any of the following reasons:
 						- The settings will yield compressed output
 						- The settings do not honor the requirements list above for outputSettings.
 						- tagCollection does not match with any tag collection in -preferredTagCollections.
 */
- (void)setOutputSettings:(nullable NSDictionary<NSString *, id> *)outputSettings forTagCollection:(CMTagCollectionRef)tagCollection NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/*!
 	@property		preferredTagCollections
 	@abstract		Tag collections held by AVVideoOutputSpecification.
 	@discussion		Returns an array of CMTagCollections.
 */
@property (nonatomic, copy, readonly) NSArray *preferredTagCollections NS_REFINED_FOR_SWIFT;

/*!
 	@property		defaultPixelBufferAttributes
 	@abstract		The default client requirements for CVPixelBuffers related to all tag collections not explicitly set with setOutputPixelBufferAttributes:forTagCollection:, expressed using the constants in <CoreVideo/CVPixelBuffer.h>.
 	@discussion		NSDictionary where keys are of type NSString, values should match the type specified by the corresponding keys documentation in <CoreVideo/CVPixelBuffer.h>
 	@note 			Pixel buffer attributes are translated into output settings, therefore, the rules of defaultOutputSettings apply to defaultPixelBufferAttributes as well.  If defaultPixelBufferAttributes are set after setting defaultOutputSettings, the set output settings will be overridden and vice-versa.
 */
@property (nonatomic, readwrite, copy, nullable) NSDictionary<NSString *, id> *defaultPixelBufferAttributes
	API_DEPRECATED_WITH_REPLACEMENT("defaultOutputSettings", macos(14.2, API_TO_BE_DEPRECATED), ios(17.2, API_TO_BE_DEPRECATED), tvos(17.2, API_TO_BE_DEPRECATED), watchos(10.2, API_TO_BE_DEPRECATED), visionos(1.1, API_TO_BE_DEPRECATED));

/*!
 	@property		defaultOutputSettings
 	@abstract		The default client requirements for output CVPixelBuffers related to all tag collections not explicitly set with -setOutputSettings:forTagCollection, expressed using the constants in AVVideoSettings.h.
 					For uncompressed video output, start with kCVPixelBuffer* keys in <CoreVideo/CVPixelBuffer.h>.
					In addition to the keys in CVPixelBuffer.h, uncompressed video settings dictionaries may also contain the following keys:
						- AVVideoAllowWideColorKey
 	@discussion		NSDictionary where keys are of type NSString, values should match the type specified by the corresponding keys documentation in <AVFoundation/AVVideoSettings.h> and <CoreVideo/CVPixelBuffer.h>.
 	@note			The setter for this property throws an exception for any of the following reasons:
						 - The settings will yield compressed output
						 - The settings do not honor the requirements list above for outputSettings.
*/
@property (nonatomic, readwrite, copy, nullable) NSDictionary<NSString *, id> * NS_SWIFT_SENDABLE defaultOutputSettings
	API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

@end

/*!
	@class		AVPlayerVideoOutputConfiguration
	@abstract	An AVPlayerVideoOutputConfiguration carries an identifier for the AVPlayerItem the configuration is associated with as well as presentation settings for that item.
 	@discussion	Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.2), ios(17.2), tvos(17.2), watchos(10.2), visionos(1.1))
@interface AVPlayerVideoOutputConfiguration : NSObject
AV_INIT_UNAVAILABLE

/*!
	@property 	sourcePlayerItem
	@abstract	The AVPlayerItem which is the source of this configuration.
	@discussion	This AVPlayerItem can be seen as the source of all samples this configuration vended alongside.
 */
@property (nonatomic, readonly, weak) AVPlayerItem *sourcePlayerItem;

/*!
	@property	dataChannelDescriptions
	@abstract	List of data channels, represented as CMTagCollections, selected for this configuration.
	@discussion Returns an Array of CMTagCollections
 */
@property (nonatomic, readonly, copy) NSArray *dataChannelDescriptions NS_REFINED_FOR_SWIFT;

/*!
 	@property	preferredTransform
 	@abstract	The preferred transformation of the visual media data vended with this configuration. This transformation is acquired from the AVAssetTrack that was used to source the media data accompanying this configuration.
 	@discussion If no transform was specified by the source track a default value of CGAffineTransformIdentity is returned.
 */
@property (nonatomic, readonly) CGAffineTransform preferredTransform API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/*!
	@property 	activationTime
	@abstract 	Host time when this configuration became active on the player the vending output is attached to.
 */
@property (nonatomic, readonly) CMTime activationTime;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVPlayerOutput.h>
#endif
