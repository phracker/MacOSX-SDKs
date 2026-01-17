//
//  HKCharacteristicObjects.h
//  HealthKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

#import <Foundation/Foundation.h>

/*!
 @class     HKBiologicalSexObject
 @abstract  A wrapper object for HKBiologicalSex enumeration.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKBiologicalSexObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKBiologicalSex biologicalSex;

@end

/*!
 @class     HKBloodTypeObject
 @abstract  A wrapper object for HKBloodType enumeration.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKBloodTypeObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKBloodType bloodType;

@end

/*!
 @class     HKFitzpatrickSkinTypeObject
 @abstract  A wrapper object for HKFitzpatrickSkinType enumeration.
 */
HK_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0))
@interface HKFitzpatrickSkinTypeObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKFitzpatrickSkinType skinType;

@end

/*!
 @class     HKWheelchairUseObject
 @abstract  A wrapper object for HKWheelchairUse enumeration.
 */
HK_EXTERN API_AVAILABLE(ios(10.0), watchos(3.0))
@interface HKWheelchairUseObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKWheelchairUse wheelchairUse;

@end

/*!
 @class     HKActivityMoveModeObject
 @abstract  A wrapper object for HKActivityMoveMode enumeration.
 */
HK_EXTERN API_AVAILABLE(ios(14.0), watchos(7.0))
@interface HKActivityMoveModeObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKActivityMoveMode activityMoveMode;

@end
