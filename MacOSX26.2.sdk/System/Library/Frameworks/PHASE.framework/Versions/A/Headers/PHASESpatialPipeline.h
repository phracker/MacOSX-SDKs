//
//  PHASESpatialPipeline.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASESpatialPipeline_h
#define PHASESpatialPipeline_h

#import <PHASE/PHASETypes.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - PHASESpatialCategory

typedef NSString* PHASESpatialCategory NS_TYPED_ENUM;

/*!
    @constant PHASESpatialCategoryDirectPathTransmission
 */
OS_EXPORT PHASESpatialCategory const PHASESpatialCategoryDirectPathTransmission;

/*!
    @constant PHASEEarlyReflections
 */
OS_EXPORT PHASESpatialCategory const PHASESpatialCategoryEarlyReflections;

/*!
    @constant PHASELateReverb
 */
OS_EXPORT PHASESpatialCategory const PHASESpatialCategoryLateReverb;

#pragma mark - PHASESpatialPipelineFlags

/****************************************************************************************************/
/*!
    @enum PHASESpatialPipelineFlags
    @abstract Spatial pipeline flags.
    @constant PHASESpatialPipelineFlagDirectPathTransmission
        Direct Path Transmission.
    @constant PHASESpatialPipelineFlagEarlyReflections
        Early Reflections.
    @constant PHASESpatialPipelineFlagLateReverb
        Late Reverb.
*/
typedef NS_OPTIONS(NSUInteger, PHASESpatialPipelineFlags) {
    PHASESpatialPipelineFlagDirectPathTransmission = 1UL << 0,
    PHASESpatialPipelineFlagEarlyReflections = 1UL << 1,
    PHASESpatialPipelineFlagLateReverb = 1UL << 2,
}
NS_SWIFT_NAME(PHASESpatialPipeline.Flags);

#pragma mark - PHASESpatialPipelineEntry

@class PHASENumberMetaParameterDefinition;

/****************************************************************************************************/
/*!
    @class PHASESpatialPipelineEntry
    @abstract Spatial Pipeline Entry.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASESpatialPipelineEntry : NSObject

/*!
    @property sendLevel
    @abstract Send level.
    @note
        Values are clamped to the range [0, 1]. Default value is 1.
*/
@property(nonatomic) double sendLevel;

/*!
    @property sendLevelMetaParameterDefinition
    @abstract An optional metaparameter used to drive the send level during playback.
*/
@property(nonatomic, strong, nullable) PHASENumberMetaParameterDefinition* sendLevelMetaParameterDefinition;

@end

#pragma mark - PHASESpatialPipeline

/****************************************************************************************************/
/*!
    @class PHASESpatialPipeline
    @abstract Spatial Pipeline.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASESpatialPipeline : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithFlags
    @abstract Initialize a Spatial Pipeline with the provided flags.
    @discussion
        It's invalid to pass flags == 0 to this function. Doing so will return nil.
    @param flags
        Options for direct path transmission, early reflections, late reverb, etc.
*/
- (nullable instancetype)initWithFlags:(PHASESpatialPipelineFlags)flags NS_DESIGNATED_INITIALIZER;

/*!
    @property flags
    @abstract Spatial Pipeline Flags.
*/
@property(nonatomic, readonly) PHASESpatialPipelineFlags flags;

/*!
    @property entries
    @abstract A dictionary of entries in the Spatial Pipeline.
    @discussion
        Upon initialization, an entry will be created for every flag in the PHASESpatialPipelineFlags passed to PHASESpatialPipeline:initWithFlags.
*/
@property(readonly, copy) NSDictionary<PHASESpatialCategory, PHASESpatialPipelineEntry*>* entries;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASESpatialPipeline_h */
