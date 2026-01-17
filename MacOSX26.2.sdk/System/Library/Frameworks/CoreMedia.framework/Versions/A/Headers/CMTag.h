/*
    File:  CMTag.h
	
	Framework:  CoreMedia
 
	Copyright © 2023-2024 Apple Inc. All rights reserved.
 
*/

#ifndef CMTAG_H
#define CMTAG_H

#include <CoreMedia/CMBase.h>
#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif
    
CF_IMPLICIT_BRIDGING_ENABLED

CM_ASSUME_NONNULL_BEGIN

#pragma pack(push)
#pragma pack()

#pragma mark - Errors

/*!
	@enum		CMTag Errors
	@discussion The OSStatus errors returned from the CMTag routines.
	@constant	kCMTagError_ParamErr Returned when caller passes incorrect input or output parameters.
	@constant		kCMTagError_AllocationFailed Returned if a necessary allocation failed.
*/
typedef CF_ENUM(OSStatus, CMTagError)
{
	kCMTagError_ParamErr = -15730,
	kCMTagError_AllocationFailed = -15731,
} CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTagCategory enums

/*!
	@enum CMTagCategory
	@abstract An enum indicating the available CMTagCategory identifiers that can be used to distinguish the tag from other kinds.
	@discussion Different kinds of CMTags may be defined or registered. Each will be associated with a category. CMTags with the same CMTagCategory will have the same kinds of values. The category serves as a namespace.
	@constant kCMTagCategory_Undefined Indicates there is no category specified for this value or it could not be determined. CMTags should typically not have this category except as sentinel values.
	@constant kCMTagCategory_MediaType Value is an OSType holding a CMMediaType.
	@constant kCMTagCategory_MediaSubType Value is an OSType holding a media subtype such as a video codec type.
	@constant kCMTagCategory_TrackID Value is a CMPersistentTrackID for a corresponding asset.
	@constant kCMTagCategory_ChannelID Value is the CMVideoTarget/CMVideoReceiver channel identifier.
	@constant kCMTagCategory_VideoLayerID Value is a signed 64-bit integer specifying the video layer identifier.
	@constant kCMTagCategory_PixelFormat Indicates the pixel format of the buffer or channel, if pixel-based. The type is an OSType corresponding to a pixel format (i.e., a kCVPixelFormatType_* type).
	@constant kCMTagCategory_PackingType Indicates this channel is packed in some way (e.g., frame packed, texture atlas). The value is an OSType carrying kCMPackingType_* constants.
	@constant kCMTagCategory_ProjectionType Indicates textures are related to a kind of texture projection (e.g., equirectangular). The value is an OSType carrying one of the kCMProjectionType_* constants.
	@constant kCMTagCategory_StereoView Indicates this channel is related to carrying stereographic views. The value is a Flags value carrying one of the kCMTagStereoViewComponent_* constants.
	@constant kCMTagCategory_StereoViewInterpretation Indicates this channel has non default stereo view interpretation (e.g., stereo eye view order is reversed.) Tags with this category will typically be associated with tags of category kCMTagCategory_StereoView. This tag alone however does not indicate which stereo eyes are present. The value is a Flags value carrying one of the kCMTagStereoInterpretationOption_* constants.
*/
typedef CF_ENUM(FourCharCode, CMTagCategory)
{
	kCMTagCategory_Undefined CF_REFINED_FOR_SWIFT	= 0,
	kCMTagCategory_MediaType 						= 'mdia',
	kCMTagCategory_MediaSubType 					= 'msub',
	kCMTagCategory_TrackID 							= 'trak',
	kCMTagCategory_ChannelID 						= 'vchn',
	kCMTagCategory_VideoLayerID						= 'vlay',
	kCMTagCategory_PixelFormat 						= 'pixf',
	kCMTagCategory_PackingType						= 'pack',
	kCMTagCategory_ProjectionType 					= 'proj',
	kCMTagCategory_StereoView 					= 'eyes',
	kCMTagCategory_StereoViewInterpretation 	= 'eyip',
} CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTagDataType enums

/*!
	@enum CMTagDataType
	@discussion The data type for the value of the CMTag.
	@constant kCMTagDataType_Invalid Value is a sentinel data type indicating it is not valid. The value should not be treated as a value.
	@constant kCMTagDataType_SInt64 Value is a signed 64-bit integer (e,g, int64_t).
	@constant kCMTagDataType_Float64 Value is a 64-bit floating point value (e.g., Float64).
	@constant kCMTagDataType_OSType Value is an OSType in the lower 32 bits of a 64-bit integer (e.g., OSType).
	@constant kCMTagDataType_Flags Value is a 64-bit integer holding option bits or flags.
*/
typedef CF_ENUM( uint32_t, CMTagDataType ) {
	kCMTagDataType_Invalid CF_REFINED_FOR_SWIFT	= 0,
	kCMTagDataType_SInt64						= 2,
	kCMTagDataType_Float64 						= 3,
	kCMTagDataType_OSType 						= 5,
	kCMTagDataType_Flags 						= 7,
} CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTagValue

/*!
	@typedef	CMTagValue
	@abstract	64-bit value interpreted within the context of the CMTagCategory.
	@discussion	The 64-bit value can be one of several data types fitting within that range and holding a category-specific value. Data types include numeric and non-numeric types. Examples of numeric include a signed 64-bit integer and a 64-bit floating point value. Non-numeric types include a single OSType and an OSType pair. The value may hold values including discrete values, bit flags, enums representable as a signed 64-bit integer or float and values encoding any of these.
*/
typedef uint64_t CMTagValue CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTag

/*!
	@typedef CMTag
	@abstract An efficient structure used to label something about a resource or other media construct.
	@discussion A structure holding a CMTagCategory, CMTagDataType, and a CMTagValue serving to represent a particular tag that might be assigned to or associated with another resource. There is only one of each of the category, the dataType and the value so any notion of "has" is about the respective singular element.  CMTags are a value type. No lifetime management such as allocation or retain and release semantics are needed. CMTags can be passed by value, returned by value and stored in other structures or arrays or on the stack.  CMTags carry a single value that can be carried in 64 bits. This can include data types such as signed 64-bit integers, floating point values fitting in 64 bits, up to 64 bit of flags, and other data types fitting within 64 bits. Signaling of the data type is carried in the CMTagDataType. The data types can be extended through registration with the CoreMedia team.  A CMTag value should not be used to carry pointers. If such a reference is needed, it is okay to carry an index into an out-of-band data structure that itself has a memory reference or an object reference.
	@field category CMTagCategory for the tag.
	@field dataType CMTagDataType for the tag indicating the data type of the value.
	@field value CMTagValue for the value of the CMTag (e.g., a signed 64-bit integer.)
 */
struct CMTag {
	CMTagCategory category;
	CMTagDataType dataType;
	CMTagValue value;
} CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));
typedef struct CMTag CMTag CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTag data type and value accessors

/*!
	@function	CMTagIsValid
	@abstract   Tests if a CMTag is valid.
	@param tag The CMTag to evaluate.
	@result		Returns false if the tag's dataType is kCMTagDataType_Invalid, true otherwise.
*/
CM_INLINE Boolean CMTagIsValid( CMTag tag ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagGetValueDataType
	@abstract   Returns the dataType field of the CMTag.
	@param tag CMTag from which to extract the data type.
	@result		kCMTagDataType_* value.
*/
CM_EXPORT CMTagDataType CMTagGetValueDataType( CMTag tag ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTag constants

/*!
	@constant   kCMTagInvalid
	@abstract	CMTag with an unspecified or "null" value.
 */
CM_EXPORT const CMTag kCMTagInvalid CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - MediaType convenience tags

/*!
	@constant kCMTagMediaTypeVideo
	@abstract A CMTag of category kCMTagCategory_MediaType and the value kCMMediaType_Video (OSType).
 */
CM_EXPORT const CMTag kCMTagMediaTypeVideo CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagMediaSubTypeMebx
	@abstract A CMTag of category kCMTagCategory_MediaType and the value kCMMetadataFormatType_Boxed (OSType).
 */
CM_EXPORT const CMTag kCMTagMediaSubTypeMebx CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagMediaTypeAudio
	@abstract A CMTag of category kCMTagCategory_MediaType and the value kCMMediaType_Audio (OSType).
 */
CM_EXPORT const CMTag kCMTagMediaTypeAudio CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagMediaTypeMetadata
	@abstract A CMTag of category kCMTagCategory_MediaType and the value kCMMediaType_Metadata (OSType).
 */
CM_EXPORT const CMTag kCMTagMediaTypeMetadata CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - StereoView data types and convenience tags

/*!
	@abstract Flags used with kCMTagCategory_StereoView tags to signal the nature of the stereo views carried in a buffer or channel.
	@discussion A "stereo eye" is either for the left eye or for the right eye. A CMTag signaling of stereo views can indicate the presence of one "stereo eye", both stereo eyes or no stereo eyes. A CMTag having a CMTagCategory of kCMTagCategory_StereoView has a value that is a set of kCMTagStereoViewComponent_* flags (see CMTagMakeWithFlagsValue()) that can be set to indicate the stereo eyes carried.  If neither the left nor the right stereo eye is signaled, this can be interpreted to mean that this is not stereo view related and is instead monoscopic video. If it is not stereo related, a kCMTagCategory_StereoView CMTag need not be associated with the buffer or channel.  kCMTagCategory_StereoView does not prescribe how the stereo views are carried. It might be contained in some kind of multiview carriage or might be frame packed in some way. The kCMTagCategory_PackingType will typically be available if frame packing of stereo views is used. The presence of a CMTag with kCMTagCategory_StereoView alone is insufficient to imply if there is some kind of packing or other mechanism required. Additional CMTags with other CMTagCategories may be necessary.  One or more kCMTagCategory_StereoView tags may be present in a collection. When considering which stereo eyes are represented by the collection, the same semantic can be expressed in more than one way in the collection. Specifying the same CMTag more than once has no meaning as the first occurrence indicates the stereo eye or stereo eyes are present.
	Here are compatible semantics expressed by one or more CMTags:
	- a single CMTag with kCMTagStereoViewsOption_LeftEye bitwise ORed with kCMTagStereoViewsOption_RightEye.
	- two kCMTagCategory_StereoView CMTags with one CMTag having the value kCMTagStereoViewsOption_LeftEye and the other CMTag having the value kCMTagStereoViewsOption_RightEye.
	- three or more CMTags made up of a CMTag with kCMTagStereoViewsOption_LeftEye bitwise ORed with kCMTagStereoViewsOption_RightEye and both a CMTag with only kCMTagStereoViewsOption_LeftEye and a CMTag with kCMTagStereoViewsOption_RightEye.
	Likewise, if a collection contains only one or more CMTags with one stereo eye (e.g., kCMTagStereoViewsOption_LeftEye), only that stereo eye should be considered present.  The absence of a kCMTagCategory_StereoView CMTag is meant to indicate there is no stereo view present. If this signaling of no stereo eyes is associated with a buffer or channel that carries stereo eye views, the buffer or channel should be configured to present only a monoscopic view. This might be in the form of some fallback to a default view corresponding to a stereo eye or even to some other view it includes or can synthesize.
	@constant kCMTagStereoViewsOption_LeftEye the left stereo eye is present in encoded or decoded video buffers.
	@constant kCMTagStereoViewsOption_RightEye the right stereo eye is present in encoded or decoded video buffers.
 */
typedef CF_OPTIONS(uint64_t, CMStereoViewComponents)
{
	kCMStereoView_None          = 0,
	kCMStereoView_LeftEye 		= 1UL << 0,
	kCMStereoView_RightEye 		= 1UL << 1
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagStereoLeftEye
	@abstract A CMTag of category kCMTagCategory_StereoView and the value kCMTagStereoViewComponent_LeftEye (Flags).
 */
CM_EXPORT const CMTag kCMTagStereoLeftEye CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagStereoRightEye
	@abstract A CMTag of category kCMTagCategory_StereoView and the value kCMTagStereoViewComponent_RightEye (Flags).
 */
CM_EXPORT const CMTag kCMTagStereoRightEye CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagStereoLeftAndRightEye
	@abstract A CMTag of category kCMTagCategory_StereoView and the value of the bitwise OR of kCMTagStereoViewComponent_LeftEye and kCMTagStereoViewComponent_RightEye (Flags).
 */
CM_EXPORT const CMTag kCMTagStereoLeftAndRightEye CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagStereoNone
	@abstract A CMTag of category kCMTagCategory_StereoView and the value of kCMTagStereoViewComponent_None. (Flags)
 */
CM_EXPORT const CMTag kCMTagStereoNone CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - StereoViewInterpretation data types and convenience tags

/*!
	@abstract Flags used with kCMTagCategory_StereoViewInterpretation tags to signal additional information that may be important to the interpretation of stereo views carried in a buffer or channel.
	@discussion A buffer or channel may carry one or more stereo eye views. The signaling of the presence of individual stereo eye views can be done using CMTags with a kCMTagCategory_StereoView category and correspondng kCMTagStereoViewComponent_* constants. There may however be additional signaling that is valuable beyond the presence of a stereo eye. The kCMTagCategory_StereoViewInterpretation category allows additional signaling that may be relevant for interpretation of storage, ordering or other details regarding the stereo views.  A CMTag having a CMTagCategory of kCMTagCategory_StereoViewInterpretation has a value that is a set of kCMStereoViewInterpretation_* flags (see CMTagMakeWithFlagsValue()) that can be set to indicate additional aspects of the stereo view or stereo views. The absence of a flag indicates the default interpretation of that feature or aspect should occur. If a flag is set, the semantic of that feature and only that feature should be inferred.  Two stereo view interpretations are currently defined.  One is that the order of stereo views is the reverse of the default of left then right. Here, order can be the geometric order such as in frame packed video or in something such as storage order.  The second is that buffers or channels contain views other than the left stereo eye view and the right stereo eye view. Such a view might be used as an alternative when perhaps monoscopic view is to be used instead of selecting the left or right stereo view or synthesizing something based upon the left and right stereo eye views.  The absence of a kCMTagCategory_StereoViewInterpretation CMTag is meant to indicate defaults are used.  Specifying kCMStereoViewInterpretation_Default is equivalent to the absence of a CMTag with category kCMTagCategory_StereoViewInterpretation.
	@constant kCMStereoViewInterpretation_Default no additional interpretation other than the default is implied by this tag. The absence of a tag of the kCMTagCategory_StereoViewInterpretation is considered equivalent to a CMTag having the kCMStereoViewInterpretation_Default value.
	@constant kCMStereoViewInterpretation_StereoOrderReversed the order of the stereo left eye and stereo right eye are reversed from the default of left being first and right being second in whatever geometric sense or storage sense that might imply. If set to 0, the order is the default left and then right eye.
	@constant kCMStereoViewInterpretation_AdditionalViews one or more additional views may be present beyond stereo left and stereo right eyes (e.g,. a “centerline” view). If set to 0, there are no additional views beyond the stereo views or no additional views can be determined to exist.
 */
typedef CF_OPTIONS(uint64_t, CMStereoViewInterpretationOptions)
{
	kCMStereoViewInterpretation_Default      			= 0,
	kCMStereoViewInterpretation_StereoOrderReversed 	= 1UL << 0,
	kCMStereoViewInterpretation_AdditionalViews 		= 1UL << 1
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagStereoInterpretationOrderReversed
	@abstract A CMTag of category kCMTagCategory_StereoViewInterpretation and the value of kCMStereoViewInterpretation_StereoOrderReversed (Flags).
 */
CM_EXPORT const CMTag kCMTagStereoInterpretationOrderReversed CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - ProjectionType data types and convenience tags

/*!
	@abstract Constants used with kCMTagCategory_ProjectionType to signal the nature of a video projection carried in a buffer or channel.
	@discussion A video projection can be one of several types. Examples include 360 degree equirectangular, 180 degree half equirectangular, or a fisheye.  A CMTag having a CMTagCategory of kCMTagCategory_ProjectionType has a value that is an OSType indicating the kind of projection using a kCMProjectionType_* constant.  The kCMProjectionType_Rectangular projection type can signal that there is no projection other than the default 2D view. This is provided so it is possible to still signal a kCMTagCategory_ProjectionType CMTag but indicates it has no effect. 	The kCMProjectionType_ParametricImmersive projection type indicates a projection described mathematically by a model of camera lens calibration parameters. Parameters may be found in lens calibration metadata in kCMFormatDescriptionExtension_CameraCalibrationDataLensCollection with algorithm_kind parametric. If a kCMTagCategory_ProjectionType CMTag is not signaled, a rectangular projection is implied.  The kCMTagCategory_ProjectionType tag may be associated with other tags if projection related parameters are also signaled. What is carried will be defined for the specific type of projection.
	@constant kCMProjectionType_Rectangular There is no projection.This is a traditional 2D texture. Default if no projection type tag is signaled.
	@constant kCMProjectionType_Equirectangular The projection is a 360 degree equirectangular projection.
	@constant kCMProjectionType_HalfEquirectangular The projection is a 180 degree equirectangular projection.
	@constant kCMProjectionType_Fisheye This projection is used by Apple Immersive Video (AIV) video and requires AIME metadata to provide the projection details.  Only use this projection when working with AIV content.
	@constant kCMProjectionType_ParametricImmersive The projection is defined with a parametric description of lens distortion and image dewarping parameters. 
 */
typedef CF_ENUM(uint64_t, CMProjectionType)
{
	kCMProjectionType_Rectangular 			= 'rect',
	kCMProjectionType_Equirectangular 		= 'equi',
	kCMProjectionType_HalfEquirectangular 	= 'hequ',
	kCMProjectionType_Fisheye 				= 'fish',
	kCMProjectionType_ParametricImmersive API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))	= 'prim',
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagProjectionTypeRectangular
	@abstract A CMTag of category kCMTagCategory_ProjectionType and the value kCMTagProjectionType_Rectangular (OSType).
 */
CM_EXPORT const CMTag kCMTagProjectionTypeRectangular CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagProjectionTypeEquirectangular
	@abstract A CMTag of category kCMTagCategory_ProjectionType and the value kCMTagProjectionType_Equirectangular (OSType).
 */
CM_EXPORT const CMTag kCMTagProjectionTypeEquirectangular CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagProjectionTypeHalfEquirectangular
	@abstract A CMTag of category kCMTagCategory_ProjectionType and the value kCMProjectionType_HalfEquirectangular (OSType).
 */
CM_EXPORT const CMTag kCMTagProjectionTypeHalfEquirectangular
	API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/*!
	@constant kCMTagProjectionTypeFisheye
	@abstract A CMTag of category kCMTagCategory_ProjectionType and the value kCMTagProjectionType_Fisheye (OSType).
 */
CM_EXPORT const CMTag kCMTagProjectionTypeFisheye CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagProjectionTypeParametricImmersive
	@abstract A CMTag of category kCMTagCategory_ProjectionType and the value kCMTagProjectionType_ParametricImmersive (OSType).
 */
CM_EXPORT const CMTag kCMTagProjectionTypeParametricImmersive CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));


#pragma mark - PackingType data types and convenience tags

/*!
	@abstract Constants used with kCMTagCategory_PackingType to signal the nature of any packing applied in a buffer or channel.
	@discussion A video packing can be one of several types including frame-packing for stereo views or texture atlasing. A CMTag having a CMTagCategory of kCMTagCategory_PackingType has a value that is an OSType indicating the kind of packing using a kCMPackingType_* constant.  Examples of frame-packing include side-by-side and over-under packing, There may be related CMTags if a kind of packing requires additional parameters. The requirements will be documented with the specific kind of packing.
	@constant kCMPackingType_None There is no packing. This is a traditional 2D texture. For this case no packing tag needs to be used.
	@constant kCMPackingType_SideBySide The packing uses a horizontal side-by-side packing of two views. By default, the left stereo eye view is to the left of the right stereo eye view. If the view order is reversed, indicated by kCMTagCategory_StereoViewInterpretation/kCMStereoViewInterpretation_StereoOrderReversed, then the right view is to the left of the left stereo view.
	@constant kCMPackingType_OverUnder The packing uses a vertical over-under (or top-and-bottom) packing of two views. By default, the left stereo eye view is above the right stereo eye view. If the view order is reversed, indicated by kCMTagCategory_StereoViewInterpretation/kCMStereoViewInterpretation_StereoOrderReversed, then the right view is above the left stereo view.
 */
typedef CF_ENUM(uint64_t, CMPackingType)
{
	kCMPackingType_None 			= 'none',
	kCMPackingType_SideBySide 	= 'side',
	kCMPackingType_OverUnder 	= 'over',
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagPackingTypeNone
	@abstract A CMTag of category kCMTagCategory_PackingType and the value kCMTagPackingType_None (OStype).
 */
CM_EXPORT const CMTag kCMTagPackingTypeNone CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagPackingTypeSideBySide
	@abstract A CMTag of category kCMTagCategory_PackingType and the value kCMTagPackingType_SideBySide (OStype).
 */
CM_EXPORT const CMTag kCMTagPackingTypeSideBySide CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagPackingTypeOverUnder
	@abstract A CMTag of category kCMTagCategory_PackingType and the value kCMTagPackingType_OverUnder (OStype).
 */
CM_EXPORT const CMTag kCMTagPackingTypeOverUnder CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTag accessors and creation

/*!
	@function	CMTagGetCategory
	@abstract   Returns the CMTagCategory field of the CMTag.
	@param tag CMTag to access.
	@result		CMTagCategory of the tag.
*/
CM_INLINE CMTagCategory CMTagGetCategory( CMTag tag ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCategoryEqualToTagCategory
	@abstract   Tests if the CMTagCategory fields of two CMTags are equal.
	@discussion Function evaluates if two tag categories are structurally equivalent. This can also be performed using the == operator with the fields but this inline can be useful if one wants to catch invocations.
	@param	 	tag1 First CMTag to test.
	@param 		tag2 Second CMTag to test.
	@result		Boolean indicating if the tag categories are equal.
*/
CM_INLINE Boolean CMTagCategoryEqualToTagCategory( CMTag tag1, CMTag tag2 ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagGetValue
	@abstract   Returns the raw 64-bit CMTagValue field of the CMTag.
	@discussion The CMTagValue is returned without consideration for the encoded data type.
	@param		tag CMTag to access.
	@result		CMTagValue of the tag.
*/
CM_INLINE CMTagValue CMTagGetValue( CMTag tag ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagHasCategory
	@abstract   Returns true if the CMTag has the specified CMTagCategory.
	@param tag CMTag to evaluate.
	@param category CMTagCategory to check for.
	@result		CMTagCategory of the tag.
*/
CM_INLINE Boolean CMTagHasCategory( CMTag tag, CMTagCategory category ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagHasSInt64Value
	@abstract	Checks if the tag represents a signed 64-bit value.
	@param tag CMTag to evaluate.
	@result	Returns true if the CMTag carries a signed 64-bit value indicated by a data type of kCMTagDataType_SInt64, false otherwise.
*/
CM_EXPORT Boolean CMTagHasSInt64Value( CMTag tag ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagGetSInt64Value
	@abstract   Returns the signed 64-bit value carried by the CMTag.
	@discussion This should only be called on a CMTag with a data type of kCMTagDataType_SInt64. Calling it with a CMTag having another data type is undefined.
	@param tag CMTag to evaluate.
	@result	Signed 64-bit integer.
*/
CM_EXPORT int64_t CMTagGetSInt64Value( CMTag tag ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagHasFloat64Value
	@abstract	Checks if the tag represents a 64-bit float value.
	@param tag CMTag to evaluate.
	@result	Returns true if the CMTag carries a 64-bit float indicated by a data type of kCMTagDataType_Float64, false otherwise.
*/
CM_EXPORT Boolean CMTagHasFloat64Value( CMTag tag ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagGetFloat64Value
	@abstract   Returns the 64-bit floating point value carried by the CMTag.
	@discussion This should only be called on a CMTag with a data type of kCMTagDataType_Float64. Calling it with a CMTag having another data type is undefined.
	@param tag CMTag to evaluate.
	@result	64-bit float.
*/
CM_EXPORT Float64 CMTagGetFloat64Value( CMTag tag ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagHasOSTypeValue
	@abstract	Checks if the tag represents an OSType value.
	@param tag CMTag to evaluate.
	@result	Returns true if the CMTag carries an OSType indicated by a data type of kCMTagDataType_OSType, false otherwise.
*/
CM_EXPORT Boolean CMTagHasOSTypeValue( CMTag tag ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagGetOSTypeValue
	@abstract   Returns the single OSType value carried by the CMTag.
	@discussion This should only be called on a CMTag with a data type of kCMTagDataType_OSType. Calling it with a CMTag having another data type is undefined.
	@param tag CMTag to evaluate.
	@result	OSType.
*/
CM_EXPORT OSType CMTagGetOSTypeValue( CMTag tag ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagHasFlagsValue
	@abstract	Checks if the tag represents an flags value.
	@param tag CMTag to evaluate.
	@result	Returns true if the CMTag carries 64 bits of flags indicated by a data type of kCMTagDataType_Flags, false otherwise.
*/
CM_EXPORT Boolean CMTagHasFlagsValue( CMTag tag ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagGetFlagsValue
	@abstract   Returns the 64 bits of flags as an unsigned 64-bit integer carried by the CMTag.
	@discussion This should only be called on a CMTag with a data type of kCMTagDataType_Flags. Calling it with a CMTag having another data type is undefined.
	@param tag CMTag to evaluate.
	@result	Unsigned 64-bit integer holding the flags value.
*/
CM_EXPORT uint64_t CMTagGetFlagsValue( CMTag tag ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTag creation functions

/*!
	@function	CMTagMakeWithSInt64Value
	@abstract   Create a CMTag holding a signed 64-bit integer.
	@discussion This function creates a valid CMTag with the data type kCMTagDataType_SInt64 and have a signed 64-bit integer value.
	@param category CMTagCategory for the created CMTag.
	@param value A signed 64-bit integer to encode in the returned CMTag.
	@result A CMTag.
*/
CM_EXPORT CMTag CMTagMakeWithSInt64Value( CMTagCategory category, int64_t value ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagMakeWithFloat64Value
	@abstract   Create a CMTag holding a 64-bit float.
	@discussion This function creates a valid CMTag with the data type kCMTagDataType_Float64 and have a 64-bit floating point value.
	@param category CMTagCategory for the created CMTag.
	@param value A 64-bit float to encode in the returned CMTag.
	@result A CMTag.
*/
CM_EXPORT CMTag CMTagMakeWithFloat64Value( CMTagCategory category, Float64 value ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagMakeWithOSTypeValue
	@abstract   Create a CMTag holding an OSType.
	@discussion This function creates a valid CMTag with the data type kCMTagDataType_OSType and have an OSType value.
	@param category CMTagCategory for the created CMTag.
	@param value An OSType to encode in the returned CMTag.
	@result A CMTag.
*/
CM_EXPORT CMTag CMTagMakeWithOSTypeValue( CMTagCategory category, OSType value ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));


/*!
	@function	CMTagMakeWithFlagsValue
	@abstract   Create a CMTag holding a 64 bits of flags.
	@discussion This function creates a valid CMTag with the data type kCMTagDataType_Flags and has an unsigned 64-bit integer value holding the flags.
	@param category CMTagCategory for the created CMTag.
	@param flagsForTag An unsigned 64-bit integer to encode in the returned CMTag.
	@result A CMTag.
*/
CM_EXPORT CMTag CMTagMakeWithFlagsValue( CMTagCategory category, uint64_t flagsForTag ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTag equality

/*
	Routines to test equality of one CMTag struct type to another struct of the same category.
*/

/*!
	@function	CMTagEqualToTag
	@abstract   Tests if two CMTags are equal.
	@discussion Function evaluates if two tags are structurally equivalent. It performs a field by field comparison.
	@param tag1 First CMTag to test for equality.
	@param tag2 Second CMTag to test for equality.
	@result		Returns true if the two tags are equal, false otherwise.
*/
CM_EXPORT Boolean CMTagEqualToTag( CMTag tag1, CMTag tag2 ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCompare
	@abstract   Compares two CMTags in an ordered fashion returning a CFComparisonResult based upon the ordering of the tags.
	@discussion The entirety of a CMTag can be compared against a second CMTag in an ordered way.  The details of how the comparison is performed is an internal implementation detail. The comparison is performed as tag1 COMPARISON tag2 where COMPARISON is the ordering operation.  The ordering will be stable under a release of the framework but may change in the future. Therefore, an ordered CMTag array serialized in one version of the framework should not be assumed to be ordered the same in another version of the framework. This is best handled by retrieving the original array of CMTags and then reinserting with the new order.
	@param tag1 First CMTag to compare in ordered fashion.
	@param tag2 Second CMTag to compare in ordered fashion.
	@result		The CFComparisonResult indicating the order of tag1 compared to tag2.
*/
CM_EXPORT CFComparisonResult CMTagCompare( CMTag tag1, CMTag tag2 ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCategoryValueEqualToValue
	@abstract   Compares two CMTagCategory values for equality.
	@discussion Equality can also be tested by comparing the values with == but this is provided for consistency with other tests here.
	@param tag1 First CMTag to test for equality.
	@param tag2 Second CMTag to test for equality.
	@result		Boolean indicating if the tag values are equal.
*/
CM_INLINE Boolean CMTagCategoryValueEqualToValue( CMTag tag1, CMTag tag2 ) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagHash
	@abstract   Calculates a hash code for the CMTag.
	@param tag CMTag to hash.
	@result		The created CFHashCode.
*/
CM_EXPORT CFHashCode CMTagHash( CMTag tag) CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@function	CMTagCopyDescription
	@abstract   Creates a CFString with a description of a CMTag (just like CFCopyDescription).
	@discussion This can be used from within CFShow on an object that contains CMTag fields. It is also useful from other client debugging code.  The caller owns the returned CFString, and is responsible for releasing it.  Descriptions are not localized so are likely suitable only for debugging.
	@param allocator CFAllocator to use in creating the description string.  Pass kCFAllocatorDefault to use the default allocator.
	@param tag CMTag to describe.
	@result		The created CFString description.
*/
CM_EXPORT CFStringRef CM_NULLABLE CMTagCopyDescription(
	CFAllocatorRef CM_NULLABLE allocator,
	CMTag tag ) CF_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTag serialization

/*!
	@function	CMTagCopyAsDictionary
	@abstract   Returns a CFDictionary version of a CMTag.
	@discussion This is useful when putting CMTag in CF container types.  The caller owns the returned CFDictionary, and is responsible for releasing it.
	@param tag 	The CMTag from which to create the dictionary.
	@param allocator	CFAllocator with which to create a dictionary. Pass kCFAllocatorDefault to use the default allocator.
	@result     A CFDictionary version of the CMTag.
*/
CM_EXPORT CFDictionaryRef CM_NULLABLE CMTagCopyAsDictionary(
				CMTag tag,
				CFAllocatorRef CM_NULLABLE  allocator) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));
/*!
	@function	CMTagMakeFromDictionary
	@abstract   Reconstitutes a CMTag struct from a CFDictionary previously created by CMTagCopyAsDictionary.
	@discussion This is useful when getting CMTag from CF container types.  If the CFDictionary does not have the requisite keyed values, kCMTagInvalid is returned.
	@param	dict	A CFDictionary from which to create a CMTag.
	@result		The created CMTag.
*/
CM_EXPORT CMTag CMTagMakeFromDictionary(
				CFDictionaryRef CM_NONNULL dict) CF_SWIFT_UNAVAILABLE("Unavailable in Swift")
				API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - Tag Dictionary Keys

/*!
	@constant kCMTagValueKey
	@discussion CFDictionary key for value field of a CMTag.
*/
CM_EXPORT const CFStringRef kCMTagValueKey CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagCategoryKey
	@discussion CFDictionary key for category field of a CMTag.
*/
CM_EXPORT const CFStringRef kCMTagCategoryKey CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/*!
	@constant kCMTagDataTypeKey
	@discussion CFDictionary key for dataType field of a CMTag.
*/
CM_EXPORT const CFStringRef kCMTagDataTypeKey CF_SWIFT_UNAVAILABLE("Unavailable in Swift") API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

#pragma mark - CMTag Inline Routine Definitions

/*
	Macros for testing CMTag validity and data type
 */
#define CMTAG_IS_VALID(tag) ((Boolean)(((tag).dataType) != kCMTagDataType_Invalid))

#define CMTAG_IS_INVALID(tag) ((Boolean)(((tag).dataType) == kCMTagDataType_Invalid))

/*
	Inline routine definitions
	
	Prototypes are above
 */

CM_INLINE CMTagCategory CMTagGetCategory( CMTag tag )
{
	return tag.category;
}

CM_INLINE CMTagValue CMTagGetValue( CMTag tag )
{
	return tag.value;
}

CM_INLINE Boolean CMTagHasCategory( CMTag tag, CMTagCategory category )
{
	return ( CMTagGetCategory( tag ) == category );
}

CM_INLINE Boolean CMTagCategoryEqualToTagCategory( CMTag tag1, CMTag tag2 )
{
	return tag1.category == tag2.category;
}

CM_INLINE Boolean CMTagIsValid( CMTag tag )
{
	return CMTAG_IS_VALID( tag );
}

CM_INLINE Boolean CMTagCategoryValueEqualToValue( CMTag tag1, CMTag tag2 )
{
	return (tag1.category == tag2.category) &&	// categories must match
		(CMTagGetValueDataType(tag1) == CMTagGetValueDataType(tag2)) &&	// data types must match
		(tag1.value == tag2.value);
}

#pragma pack(pop)
    
CM_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#ifdef __cplusplus
}
#endif
	
#endif // CMTAG_H
