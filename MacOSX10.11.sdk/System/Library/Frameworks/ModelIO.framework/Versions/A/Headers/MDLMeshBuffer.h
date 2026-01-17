/*!
 @header MDLMeshBuffer.h
 @framework ModelIO
 @abstract Protocols for creating and backing mesh vertex and index buffers
 @discussion Apps can use these protocols to back buffers with custom memory 
             types such as GPU or File based memory
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum MDLMeshBufferType
 @abstract Type of data a MDLMeshBuffer has been allocated for
 */
typedef NS_ENUM(NSUInteger, MDLMeshBufferType) {
    MDLMeshBufferTypeVertex = 1,
    MDLMeshBufferTypeIndex = 2,
};

@protocol MDLMeshBuffer;
@protocol MDLMeshBufferAllocator;
@protocol MDLMeshBufferZone;

/*!
 @class MDLMeshBufferMap
 @abstract Represents a reference to memory of a mapped MeshBuffer
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLMeshBufferMap : NSObject

/*!
 @method initWithBytes:deallocator:
 @abstract Called by implementor of MDLMeshBuffer protocol to create the map
           and arrange for unmapping on deallocation.
 */
-(instancetype) initWithBytes:(void*)bytes
                  deallocator:(nullable void (^)())deallocator;

/*!
 @property bytes
 @abstract Mutable pointer to data in a MDLMeshBuffer object.
 */
@property (nonatomic, readonly) void *bytes;

@end

/*!
 @protocol MDLMeshBuffer
 @abstract Used by ModelIO to represent a buffer to be filled with vertex and 
           index data
 @discussion Supports deep copy of data by conforming to the NSCopying protocol
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@protocol MDLMeshBuffer <NSObject, NSCopying>

/*!
 @method fillData:offset:
 @abstract Fills buffer with data at offset
 @param data Data to fill buffer with
 @param offset Byte offset in buffer to begin filling data
 @discussion Fills data.length bytes of data.  Will not write beyond length of 
             this buffer.
 */
- (void)fillData:(NSData *)data offset:(NSUInteger)offset;

/*!
 @method map
 @abstract CPU access to buffer's memory
 @return An MDLMeshBufferMap object to read or modify a buffer's memory
 @discussion The buffer will remain mapped as long as the returned MDLMeshBufferMap
             object exists. Mapping a buffer may impose restrictions on a system.
             For instance,  if the implementing class maps an OpenGL buffer, that
             buffer may be  unavailable for rendering while mapped, and cause a
             draw failure.  Precautions must be taken in such cases.
 */
- (MDLMeshBufferMap *)map;

/*!
 @property length
 @abstract Size in bytes of the buffer allocation
 */
@property (nonatomic, readonly) NSUInteger length;

/*!
 @property allocator
 @abstract Allocator object used to create this buffer.
 @discussion This allcoator used for copy and relayout operations (such as when 
             a new vertex descriptor is applied to a vertex buffer)
 */
@property (nonatomic, readonly, retain) id<MDLMeshBufferAllocator> allocator;

/*!
 @property zone
 @abstract Zone from which this buffer was created
 @discussion This zone will be used for copy and relayout operations (such as 
             when a new vertex descriptor is applied to a vertex buffer).  If
             the default zone is used this will be nil.
 */
@property (nonatomic, readonly, retain) id<MDLMeshBufferZone> zone;

/*!
 @property type
 @abstract the intended type of the buffer
 */
@property (nonatomic, readonly) MDLMeshBufferType type;

@end


/*!
 @class MDLMeshBufferData
 @abstract A CPU memory backed mesh buffer
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLMeshBufferData : NSObject <MDLMeshBuffer>

/*! 
 @method initWithType:length
 @abstract instantiate a new data backed mesh buffer
 @param type the intended use of the buffer
 @param length the size of buffer to allocate, in bytes
 */
- (instancetype)initWithType:(MDLMeshBufferType)type length:(NSUInteger)length;

/*!
 @method initWithType:data
 @abstract instantiate a new data backed mesh buffer
 @param type the intended use of the buffer
 @param data the data to be used as a mesh buffer. It will be copied.
 */
- (instancetype)initWithType:(MDLMeshBufferType)type data:(nullable NSData*)data;

@property (nonatomic, readonly, retain) NSData *data;

@end




/*!
 @protocol MDLMeshBufferZone
 @abstract A reference to a logical pool of memory from which mesh buffers would 
           be allocated
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@protocol MDLMeshBufferZone <NSObject>

/*!
 @property capacity
 @abstract Total size of memory in the zone
 */
@property (nonatomic, readonly) NSUInteger capacity;

/*!
 @property allocator
 @abstract Allocator used to create the zone
 */
@property (nonatomic, readonly) id<MDLMeshBufferAllocator> allocator;

@end



/*!
 @protocol MDLMeshBufferAllocator
 @abstract Object for allocating buffers to back vertex and index data
 @discussion Accepted by MDLAsset init method.  Implementor creates objects 
             implementing MDLMeshBuffer with memory to be filled with vertex and 
             index data during 3d file loading and parsing.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@protocol MDLMeshBufferAllocator <NSObject>

/*!
 @method newZone:
 @abstract Create a zone which can be used to allocate MDLMeshBuffer objects
 @param capacity Total size in bytes of all buffers which can be created from 
        this zone
 */
-(id<MDLMeshBufferZone>)newZone:(NSUInteger)capacity;

/*!
 @method newZoneForBuffersWithSize:andType:
 @abstract Create a zone which can be used to allocate MDLMeshBuffer objects
 @param sizes Sizes of each buffer to be created in this zone
 @param types Type of each buffer to be created in this zone. Values to be of
              MDLMeshBufferType
 @discussion Will create a zone from which MDLMeshBuffer objects can be 
             allocated.  This will allocate a zone with enough capacity
             for each of the buffers with sizes and types specified even taking
             into any alignment restrictions necessary to use these buffers.
 */
-(id<MDLMeshBufferZone>)newZoneForBuffersWithSize:(NSArray<NSNumber*>*)sizes
                                          andType:(NSArray<NSNumber*>*)types;

/*!
 @method newBuffer:type:
 @abstract Create a buffer in a default zone
 @param length Size of buffer to be created in bytes
 @param type Type of data to be stored in this buffer
 */
-(id<MDLMeshBuffer>)newBuffer:(NSUInteger)length
                        type:(MDLMeshBufferType)type;
/*!
 @method newBufferWithData:type:
 @abstract Create a buffer in a default zone and fill with data in the supplied 
           NSData object
 @param data Memory to fill the buffer with
 @param type Type of data to be stored in this buffer
 */
-(id<MDLMeshBuffer>)newBufferWithData:(NSData *)data
                                type:(MDLMeshBufferType)type;

/*!
 @method newBufferFromZone:length:type:
 @abstract Create a buffer from a given zone with the given length
 @return An object conforming to the MDLMeshBuffer protocol.  Returns nil the 
         buffer could not be allocated in the zone given.
 @param zone Zone from which to allocate the memory
 @param data Values with which to fill the buffer
 @param type Type of data to be stored in this buffer
 @discussion An implementing MDLMeshBufferAllocator object may increase the size 
             of the zone if the buffer could not be allocated with the current 
             zone size.  Alternatively the implementation may return nil if the 
             buffer could not be allocated.

 */
-(nullable id<MDLMeshBuffer>)newBufferFromZone:(nullable id<MDLMeshBufferZone>)zone
                                       length:(NSUInteger)length
                                         type:(MDLMeshBufferType)type;

/*!
 @method newBufferFromZone:data:type:
 @abstract Create a buffer from a given zone and fill with data in the supplied 
           NSData object
 @return An object conforming to the MDLMeshBuffer protocol.  Returns nil the 
         buffer could not be allocated in the given zone
 @param zone Zone from which to allocate the memory
 @param data Values with which to fill the buffer
 @param type Type of data to be stored in this buffer
 @discussion An implementing MDLMeshBufferAllocator object may increase the size 
             of the zone if the buffer could not be allocated with the current 
             zone size. Alternatively the implementation may return nil if the 
             buffer could not be allocated.
 */
-(nullable id<MDLMeshBuffer>)newBufferFromZone:(nullable id<MDLMeshBufferZone>)zone
                                         data:(NSData *)data
                                         type:(MDLMeshBufferType)type;

@end



/*!
 An allocator to use when backing with an NSData is appropriate.
 */
MDL_EXPORT
@interface MDLMeshBufferDataAllocator: NSObject <MDLMeshBufferAllocator>

@end

/*!
 A default zone that can be use for convenience 
 */
@interface MDLMeshBufferZoneDefault : NSObject <MDLMeshBufferZone>

@property (nonatomic, readonly) NSUInteger capacity;
@property (nonatomic, readonly, retain) id<MDLMeshBufferAllocator> allocator;

@end

NS_ASSUME_NONNULL_END
