//
//  PHASEMedium.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEMedium_h
#define PHASEMedium_h

#import <PHASE/PHASETypes.h>

NS_ASSUME_NONNULL_BEGIN

@class PHASEEngine;

/*!
    @enum PHASEMediumPreset
    @abstract Medium preset
*/
typedef NS_ENUM(NSInteger, PHASEMediumPreset) {
    PHASEMediumPresetAir = 'mdAr',
}
NS_SWIFT_NAME(PHASEMedium.Preset);

/****************************************************************************************************/
/*!
    @interface PHASEMedium
    @abstract A PHASEMedium describes the acoustic properties of a medium.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface PHASEMedium : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithEngine:preset
    @abstract Initialize a new medium from a preset.
*/
- (instancetype)initWithEngine:(PHASEEngine*)engine preset:(PHASEMediumPreset)preset;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEMedium_h */
