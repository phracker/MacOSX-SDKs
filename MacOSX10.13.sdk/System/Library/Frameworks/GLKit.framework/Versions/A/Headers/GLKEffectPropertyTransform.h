//
//  GLKEffectPropertyTransform.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKEffectProperty.h>
#import <GLKit/GLKMath.h>

/*
 GLKEffectPropertyTransformm 

 GLKEffectPropertyTransform maintains three primary matrices:
      
      _projectionMatrix
      _modelviewMatrix

 and 1 derived matrix: _normalMatrix.

 When the modelview matrix is changed the normalMatrix is marked as stale.
 If the normalMatrix is subsequently retrieved after being marked stale
 the normalMatrix selector will recalculate the normalMatrix to return
 a current result with respect to the modelviewMatrix.
*/
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GLKEffectPropertyTransform : GLKEffectProperty 
{
    @private
    
    // Primary matrices
    GLKMatrix4  _modelviewMatrix, _projectionMatrix;
    
    // Derived matrix
    GLKMatrix3  _normalMatrix;
}

// Properties                                                                                    // Default Value
@property (nonatomic, assign)   GLKMatrix4   modelviewMatrix, projectionMatrix;                  // Identity for all
@property (nonatomic, readonly) GLKMatrix3   normalMatrix;                                       // Identity 

@end
NS_ASSUME_NONNULL_END