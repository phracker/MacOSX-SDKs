/*!
 @header MDLAsset.h
 @framework ModelIO
 @abstract Structures for representing contents of 3d model files
 @copyright Copyright © 2016 Apple, Inc. All rights reserved.
 */

#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLAssetResolver.h>
#import <ModelIO/MDLObject.h>
#import <ModelIO/MDLVertexDescriptor.h>
#import <ModelIO/MDLMeshBuffer.h>
#import <ModelIO/MDLAnimation.h>
#import <Foundation/NSURL.h>
#import <simd/simd.h>

@class MDLLightProbe;
@class MDLTexture;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class MDLAsset
 
 @abstract An MDLAsset represents the contents of a model file.
 
 @discussion Each asset contains a collection of hierarchies of objects, where 
             each object in the asset is the top level of a hierarchy. Objects
             include transforms, lights, cameras, and meshes.
 
 MDLAssets are typically instantiated from NSURLs that refer to a model resource.

 The model resource may represented timed information, for example, a series of 
 mesh morphs. If the asset is timed, then the framerate will be non-zero, and the 
 firstFrame and lastFrame properties will indicate the range for which sample 
 data exists. Samples before or after that range will be clamped. Some model 
 resource representations allow continuous sampling, others are discrete. In the 
 discrete case, if a requested sample time is not on a discrete boundary the 
 returned sample will be the sample exactly on the sample time, or if no such is 
 available, the immediately preceding sample. If no time is specified for a 
 sample, the first data will be returned.
 
 An asset's bounding box can be queried without traversing the hierarchy of 
 objects.
 
 Fast enumeration of an MDLAsset iterates the top level objects contained within.
 */



API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLAsset : NSObject <NSCopying, NSFastEnumeration>

/*!
 @method initWithURL:
 @abstract Initialize an MDLAsset using the contents of the resource located at 
           the indicated URL
 @discussion Vertex layout (i.e. vertexDescriptor) will be specified by ModelIO 
             depending on attributes of the resource.  Buffers will be allocated 
             using a default NSData based allocator

             Submeshes will be converted to triangle topology.
 */
- (instancetype)initWithURL:(NSURL *)URL;
/*!
 @method initWithURL:vertexDescriptor:bufferAllocator:
 @abstract Initialize an MDLAsset using the contents of the resource located at 
           URL, ensuring that the asset conforms to the supplied vertexDescriptor, 
           and buffers are allocated in the supplied allocator
 
 @discussion The default behavior is to triangulate any discovered meshes and to
             conform the mesh to the supplied vertexDescriptor.
 
             If nil is passed as the vertexDescriptor, then a vertexDescriptor
             will be created according to the attributes of the resource.
 
             If nil is passed as the bufferAllocator, buffers will be allocated
             using a default NSData based allocator.
 
             Submeshes will be converted to triangle topology.
  */
- (instancetype)initWithURL:(nullable NSURL *)URL
           vertexDescriptor:(nullable MDLVertexDescriptor*)vertexDescriptor
            bufferAllocator:(nullable id<MDLMeshBufferAllocator>)bufferAllocator;

/*!
 @method initWithBufferAllocator:
 @abstract Initialize an empty MDLAsset with a buffer allocator to be used during
           other operations.
 */
- (instancetype)initWithBufferAllocator:(nullable id<MDLMeshBufferAllocator>)bufferAllocator;

/*! 
 @method initWithURL:vertexDescriptor:bufferAllocator:preserveTopology:error:
 @abstract Same as initWithURL:vertexDescriptor:bufferAllocator: except that
           if preserveTopology is YES, a topology buffer might be created on the
           submeshes.
 
 @discussion If all faces in a submesh have the same vertex count, then the 
             submesh will a geometry type corresponding to that vertex count.
             For example, if all faces have four vertices, then the geometry
             type will be MDLGeometryTypeQuads. If faces have a varying number
             of vertices, then the the submesh type will be 
             MDLGeometryTypeVariableTopology, and a faceTopologyBuffer will be
             created.
 */
- (instancetype)initWithURL:(NSURL *)URL
           vertexDescriptor:(nullable MDLVertexDescriptor*)vertexDescriptor
            bufferAllocator:(nullable id<MDLMeshBufferAllocator>)bufferAllocator
           preserveTopology:(BOOL)preserveTopology
                      error:(NSError * __nullable * __nullable)error;

/*!
 @method exportAssetToURL:
 @abstract Export an asset to the specified URL.
 @return YES is returned if exporting proceeded successfully,
 */
- (BOOL)exportAssetToURL:(NSURL *)URL NS_SWIFT_UNAVAILABLE("Use exportAssetToURL:error");

/*!
 @method exportAssetToURL:error:
 @abstract Export an asset to the specified URL.
 @return YES is returned if exporting proceeded successfully,
 */
- (BOOL)exportAssetToURL:(NSURL *)URL error:(NSError * __nullable * __nullable)error;

/*!
 @abstract Return the object at the specified path, or nil if none exists there
 */
- (MDLObject*)objectAtPath:(NSString*)path API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @method canImportFileExtension:
 @abstract Indicates whether MDLAsset object can be initialized with resource
           with the given extension
 @return YES is returned if MDLAsset is able to load and represent assets with 
           the given extension
 */
+ (BOOL)canImportFileExtension:(NSString *)extension;

/*!
 @method canImportFileExtension:
 @abstract Indicates whether MDLAsset object can export asset to resource with
           the given extension
 @return YES is returned if MDLAsset is able is able to export assets to 
         resources with the given extension
 */
+ (BOOL)canExportFileExtension:(NSString *)extension;

/*!
 @method childObjectsOfClass:
 @abstract Inspects an asset's hierarchy for objects of the specified class type
 @return returns an NSArray of all objects in the asset matching the requested class
 @discussion This can be used to get references to all MDLMesh objects, MDLLights,
             etc. if objectClass is not a subclass of MDLObject, an exception will be
             raised.
 */
- (NSArray<MDLObject*>*)childObjectsOfClass:(Class)objectClass;

/*!
 @method loadTextures
 @abstract Iterates over all material properties on all materials. If they are string
           values or NSURL values, and can be resolved as textures, then the string 
           and NSURL values will be replaced by MDLTextureSampler values.
 */
- (void)loadTextures API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @method boundingBoxAtTime:
 @abstract The bounds of the MDLAsset at the specified time
 */
- (MDLAxisAlignedBoundingBox)boundingBoxAtTime:(NSTimeInterval)time;

/*!
 @property boundingBox
 @abstract The bounds of the MDLAsset at the earliest time sample
 */
@property (nonatomic, readonly) MDLAxisAlignedBoundingBox boundingBox;

/*!
 @property frameInterval
 @abstract Inherent frame rate of an asset
 @discussion If no framerate was specified by resource or resource uncapable of 
             specifying framerate, this value defaults to 0
 */
@property (nonatomic, readwrite) NSTimeInterval frameInterval;

/*!
 @property startTime
 @abstract Start time bracket of animation data
 @discussion If no animation data was specified by resource or resource incapable 
             of specifying animation data, this value defaults to 0. If startTime
             was set explicitly, then the value of startTime will be the lesser
             of the set value and the animated values.
 */
@property (nonatomic, readwrite) NSTimeInterval startTime;

/*!
 @property endTime
 @abstract End time bracket of animation data
 @discussion If no animation data was specified by resource or resource incapable
             of specifying animation data, this value defaults to 0. If the
             endTime was set explicitly, then the value of endTime will be the
             greater of the set value and the animated values.
 */
@property (nonatomic, readwrite) NSTimeInterval endTime;

/*!
 @property upAxis
 @abstract Scene up axis
 @discussion Some imported formats specify a scene up axis. By default Y-axis (0, 1, 0) is used
 but other values are supported.
 */
@property (nonatomic, readwrite) vector_float3 upAxis API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @property URL
 @abstract URL used to create the asset
 @discussion If the asset was not created with a URL, nil will be returned.
 */
@property (nonatomic, readonly, retain, nullable) NSURL *URL;

/*!
 @property AssetResolver
 @abstract Resolver asset that helps find associated files
 @discussion The default asset resolver is the RelativeAssetResolver
 */
@property (nonatomic, retain, nullable) id<MDLAssetResolver> resolver API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/*!
 @property bufferAllocator
 @abstract  Allocator used to create vertex and index buffers
 */
@property (nonatomic, readonly, retain) id<MDLMeshBufferAllocator> bufferAllocator;

/*!
 @property vertexDescriptor
 @abstract Vertex descriptor set upon asset initialization
 @discussion Will be nil if there was no descriptor set
 */
@property (nonatomic, readonly, retain, nullable) MDLVertexDescriptor *vertexDescriptor;

/*!
 @method addObject:
 @abstract Add a top level object to an asset.
 @discussion If the object was already in the asset, this has no effect.
 */
- (void)addObject:(MDLObject *)object;

/*!
 @method removeObject:
 @abstract Remove a top level object from an asset.
 @discussion If the object not in the asset, this has no effect.
 */
- (void)removeObject:(MDLObject *)object;

/*!
 @property count
 @abstract The number of top level objects
 */
@property (nonatomic, readonly) NSUInteger count;

/*!
 @method objectAtIndexedSubscript:
 @abstract return the indexed top level object
 */
- (nullable MDLObject *)objectAtIndexedSubscript:(NSUInteger)index;

/*!
 @method objectAtIndex:
 @abstract return the indexed top level object
 */
- (MDLObject *)objectAtIndex:(NSUInteger)index;

/*!
 @property masters
 @abstract Master objects that can be instanced into the asset's object hierarchy
 @see MDLObjectContainerComponent
 */
@property (nonatomic, retain) id<MDLObjectContainerComponent> masters;

/*!
 @property animations
 @abstract Animations that can be bound to MDLObjects (@see MDLAnimationBindComponent)
 @see MDLObjectContainerComponent
 */
@property (nonatomic, retain) id<MDLObjectContainerComponent> animations API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

@end

@protocol MDLLightProbeIrradianceDataSource <NSObject>
/**
 Bounding box of the source scene for which you are adding light probes.
 */
@property MDLAxisAlignedBoundingBox boundingBox;

@optional
/**
 Spherical harmonics level used to calculate the spherical harmonics coefficients.
 */
@property NSUInteger sphericalHarmonicsLevel;

/**
 Given a position in the source scene, returns the spherical harmonics coefficients
 at that point.
 
 The data returned is an array of 32-bit floating-point values, containing three non-interleaved 
 data sets corresponding to the red, green, and blue sets of coefficients. The array’s length is 
 determined by the sphericalHarmonicsLevel property.
 */
-(NSData *)sphericalHarmonicsCoefficientsAtPosition:(vector_float3)position;
@end

/**
 Given a light probe density, method places light probes in the scene according to the
 passed in placement heuristic type. The higher the density, the greater the number of 
 light probes placed in the scene.
 
 Using the placement heuristic MDLProbePlacementUniformGrid places the light probes in the
 scene as a uniform grid. The placement heuristic MDLProbePlacementIrradianceDistribution 
 places the light probes in areas of greatest irradiance change. 
 */
@interface MDLAsset (MDLLightBaking)
+ (NSArray<MDLLightProbe *> *)placeLightProbesWithDensity:(float)value heuristic:(MDLProbePlacement)type
                                usingIrradianceDataSource:(id<MDLLightProbeIrradianceDataSource>)dataSource;
@end

NS_ASSUME_NONNULL_END
