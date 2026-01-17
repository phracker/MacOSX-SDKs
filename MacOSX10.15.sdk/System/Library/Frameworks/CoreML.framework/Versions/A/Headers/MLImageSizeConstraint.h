//
//  MLImageSizeConstraint.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreML/MLImageSize.h>
#import <CoreML/MLImageSizeConstraintType.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLImageSizeConstraint  : NSObject <NSSecureCoding>

@property (readonly, nonatomic) MLImageSizeConstraintType type;

// Image size must fall within this range
@property (readonly, nonatomic) NSRange pixelsWideRange;
@property (readonly, nonatomic) NSRange pixelsHighRange;

// If type == MLImageSizeConstraintTypeEnumerated
// then the only image sizes present in this set are allowed.
@property (readonly, nonatomic) NSArray<MLImageSize *> *enumeratedImageSizes;

@end

NS_ASSUME_NONNULL_END
