/*!
 @header MDLAsset.h
 @framework ModelIO
 @abstract Structures for representing contents of 3d model files
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLObject.h>
#import <ModelIO/MDLVertexDescriptor.h>
#import <ModelIO/MDLMeshBuffer.h>
#import <Foundation/NSURL.h>
#import <simd/simd.h>

/*!
 @class MDLAsset
 
 @abstract An MDLAsset represents the contents of a model file.
 
@discussion

 Each asset contains a collection of hierarchies of objects, where each object 
 in the asset is the top level of a hierarchy. Objects include transforms, 
 lights, cameras, and meshes.
 
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


NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_11, 9_0)
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
- (instancetype)initWithURL:(NSURL *)URL
           vertexDescriptor:(nullable MDLVertexDescriptor*)vertexDescriptor
            bufferAllocator:(nullable id<MDLMeshBufferAllocator>)bufferAllocator;

/*! 
 @method initWithURL:vertexDescriptor:bufferAllocator:preserveTopology
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
- (BOOL)exportAssetToURL:(NSURL *)URL;
- (BOOL)exportAssetToURL:(NSURL *)URL error:(NSError * __nullable * __nullable)error;

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
 @method boundingBoxAtTime:
 @abstract The bounds of the MDLAsset at the specified time
 */
- (MDLAxisAlignedBoundingBox)boundingBoxAtTime:(NSTimeInterval)time;

/*!
 @property bounds
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
             of specifying animation data, this value defaults to 0
 */
@property (nonatomic, readwrite) NSTimeInterval startTime;

/*!
 @property endTime
 @abstract End time bracket of animation data
 @discussion If no animation data was specified by resource or resource incapable
             of specifying animation data, this value defaults to 0
 */
@property (nonatomic, readwrite) NSTimeInterval endTime;

/*!
 @property URL
 @abstract  URL used to create the asset
 @discussion If no animation data was specified by resource or resource incapable 
             of specifying animation data, this value defaults to 0
 */
@property (nonatomic, readonly, retain, nullable) NSURL *URL;

/*!
 @property bufferAllocator
 @abstract  Allocator used to create vertex and index buffers
 */
@property (nonatomic, readonly, retain) id<MDLMeshBufferAllocator> bufferAllocator;

/*!
 @property vertexDescriptor
 @abstract  Vertex descriptor set upon asset initialization
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
 The number of top level objects
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

@end

NS_ASSUME_NONNULL_END
