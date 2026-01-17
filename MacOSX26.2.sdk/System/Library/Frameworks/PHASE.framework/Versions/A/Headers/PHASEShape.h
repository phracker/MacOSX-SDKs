//
//  PHASEShape.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEShape_h
#define PHASEShape_h

#import <ModelIO/ModelIO.h>
#import <PHASE/PHASEMaterial.h>
#import <PHASE/PHASETypes.h>

@class PHASEEngine;

NS_ASSUME_NONNULL_BEGIN

/****************************************************************************************************/
/*!
    @interface PHASEShapeElement
    @abstract A single element within a shape. The attached material defines its acoustical properties.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(PHASEShape.Element)
@interface PHASEShapeElement : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property material
    @abstract The shape's material defines the acoustical properties of this element.
*/
@property(nullable, nonatomic, strong) PHASEMaterial* material;

@end

/****************************************************************************************************/
/*!
    @interface PHASEShape
    @abstract The physical representation of an object within the simulated acoustic scene.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEShape : NSObject<NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithEngine:mesh
    @abstract Initialize a shape from a mesh.
    @discussion
        One PHASEShapeElement will be created for every submesh within the mesh.
    @note
        A single shape can be used to create multiple instances of sources and occluders.
        For example, a client could create a single shape for a window, then create multiple occluders from it.
        The same can be done with with sources.
    @param engine
        The engine this shape will be used with.
    @param mesh
        A Model I/O mesh object.
    @return
        A new shape object
*/
- (instancetype)initWithEngine:(PHASEEngine*)engine mesh:(MDLMesh*)mesh NS_DESIGNATED_INITIALIZER;

/*!
    @method initWithEngine:mesh
    @abstract Initialize a shape from an MDLMesh and a list of materials
    @param engine
        The engine this shape will be used with
    @param mesh
        A Model I/O mesh object.
    @param materials
        An array of PHASEMaterial objects that overrides any acoustical materials within the mesh object
    @return
        A new shape object
    @discussion
        The materials array cannot be empty and cannot contain nil entries, otherwise an exception is thrown.
        If the number of submeshes within the mesh are less than or equal to the size of the material array, the material will be assigned
        to the corresponding element. If the number of submeshes within the mesh is greater than the size of the material array, the material
        assigned to the element will be the index of the element modulo the number of materials. IE: given a mesh with 6 submeshes and an array
        of 3 materials, the element at index 5 will be assigned the material at index: 5 % 3 = 2.
*/
- (instancetype)initWithEngine:(PHASEEngine*)engine mesh:(MDLMesh*)mesh materials:(NSArray<PHASEMaterial*>*)materials;

/*!
    @property elements
    @abstract List of all the shape elements associated with this shape.
*/
@property(nonatomic, readonly, copy) NSArray<PHASEShapeElement*>* elements;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEShape_h */
