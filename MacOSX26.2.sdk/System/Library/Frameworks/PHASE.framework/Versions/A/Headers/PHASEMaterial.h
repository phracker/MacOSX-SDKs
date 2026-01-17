//
//  PHASEMaterial.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEMaterial_h
#define PHASEMaterial_h

#import <PHASE/PHASETypes.h>

NS_ASSUME_NONNULL_BEGIN

@class PHASEEngine;

#pragma mark - PHASEMaterialPreset

/*!
    @enum PHASEMaterialPreset
    @abstract Material preset
*/
typedef NS_ENUM(NSInteger, PHASEMaterialPreset) {
    PHASEMaterialPresetCardboard = 'mCrd',
    PHASEMaterialPresetGlass = 'mGls',
    PHASEMaterialPresetBrick = 'mBrk',
    PHASEMaterialPresetConcrete = 'mCcr',
    PHASEMaterialPresetDrywall = 'mDrw',
    PHASEMaterialPresetWood = 'mWud',
};


#pragma mark - PHASEMaterial

/****************************************************************************************************/
/*!
    @interface PHASEMaterial
    @abstract A PHASEMaterial describes the acoustic properties of a material.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEMaterial : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithEngine:preset
    @abstract Initialize a new material from a preset.
*/
- (instancetype)initWithEngine:(PHASEEngine*)engine preset:(PHASEMaterialPreset)preset;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEMaterial_h*/
