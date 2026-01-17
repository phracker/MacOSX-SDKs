/*!
 *  @header MPSImage.h
 *  @framework MPSCore.framework
 *
 *  @copyright Copyright (c) 2015-2017 Apple Inc. All rights reserved.
 *  @discussion A MPSImage is a MTLTexture abstraction that allows for more than 4 channels, and
 *              for temporary images.
 */

#ifndef MPSImage_h
#define MPSImage_h


#include <MPSCore/MPSCoreTypes.h>
#import <Metal/MTLBuffer.h>

#ifdef __cplusplus
extern "C" {
#endif


/*!
 *  @class      MPSImageDescriptor
 *  @dependency This depends on Metal.framework
 *  @abstract   A MPSImageDescriptor object describes a attributes of MPSImage and is used to
 *              create one (see MPSImage discussion below)
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), macCatalyst(13.0), tvos(10.0))
@interface MPSImageDescriptor : NSObject <NSCopying>
/*! @property   width
 *  @abstract   The width of the CNN image.
 *  @discussion The formal width of the CNN image in pixels.  Default = 1.
 */
@property (readwrite, nonatomic) NSUInteger width;

/*! @property   height
 *  @abstract   The height of the CNN image.
 *  @discussion The formal height of the CNN image in pixels. Default = 1.
 */
@property (readwrite, nonatomic) NSUInteger height;

/*! @property   featureChannels
 *  @abstract   The number of feature channels per pixel.  Default = 1.
 */
@property (readwrite, nonatomic) NSUInteger featureChannels;

/*! @property   numberOfImages
 *  @abstract   The number of images for batch processing.   Default = 1.
 */
@property (readwrite, nonatomic) NSUInteger numberOfImages;

/*! @property   pixelFormat
 *  @abstract   The MTLPixelFormat expected for the underlying texture.
 */
@property (readonly, nonatomic) MTLPixelFormat pixelFormat;


/*! @property   channelFormat
 *  @abstract   The storage format to use for each channel in the image.
 */
@property (readwrite, nonatomic) MPSImageFeatureChannelFormat channelFormat;

/*!
 @property cpuCacheMode
 @abstract Options to specify CPU cache mode of texture resource. Default = MTLCPUCacheModeDefaultCache
 */
@property (readwrite, nonatomic) MTLCPUCacheMode cpuCacheMode;

/*!
 @property storageMode
 @abstract To specify storage mode of texture resource.
 @discussion Storage mode options:
        @code
            Default =   MTLStorageModeShared on iOS
                        MTLStorageModeManaged on Mac OSX
            MTLStorageModeShared not supported on Mac OSX.
            See Metal headers for synchronization requirements when using StorageModeManaged
        @endcode
 */
@property (readwrite, nonatomic) MTLStorageMode storageMode;

/*!
 *  @property   usage
 *  @abstract   Description of texture usage.  Default = MTLTextureUsageShaderRead/Write
 */
@property (readwrite, nonatomic) MTLTextureUsage usage;

/*! @abstract   Create a MPSImageDescriptor for a single read/write cnn image.
 */
+(__nonnull instancetype) imageDescriptorWithChannelFormat: (MPSImageFeatureChannelFormat)channelFormat
                                                     width: (NSUInteger)width
                                                    height: (NSUInteger)height
                                           featureChannels: (NSUInteger)featureChannels;

/*! @abstract   Create a MPSImageDescriptor for a read/write cnn image with option to set usage and batch size (numberOfImages).
 */
+(__nonnull instancetype) imageDescriptorWithChannelFormat: (MPSImageFeatureChannelFormat)channelFormat
                                                     width: (NSUInteger)width
                                                    height: (NSUInteger)height
                                           featureChannels: (NSUInteger)featureChannels
                                            numberOfImages: (NSUInteger)numberOfImages
                                                     usage: (MTLTextureUsage)usage;

-(nonnull instancetype) copyWithZone: (NSZone* __nullable) zone
        MPS_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0));
@end

@class MPSKernel;
@class MPSImage;
typedef NSArray<MPSImage*>  MPSImageBatch;

/*! @abstract raise or lower the readcount of a batch by a set amount
 *  @discussion     In some circumstances, a MPSImage may appear in a MPSImageBatch
 *                  multiple times. This is particularly common when the MPSImage serves
 *                  as an accumulator across the entire batch, such as when accumulating
 *                  gradients for convolution weight update or batch statistics for
 *                  batch normalization.  A naive function would then end up incrementing
 *                  the state multiple times, probably leading to an error.
 *
 *                  MPSImageBatchIncrementReadCount() will efficiently increment the readCounts of
 *                  each object in the batch only once, avoiding this problem. Non-temporary
 *                  images and images with readCount already 0 will be ignored.
 *
 *                  CAUTION: At many places in MPS, the framework assumes all images
 *                  in the batch have the same characteristics, such as MPSImageFeatureChannelFormat.
 *                  At times, for example, it is necessary to patch in a special version of the
 *                  kernel to handle BFloat16 or another characteristic. When this happens, the
 *                  kernel generally can't respond correctly when some images in a batch have that
 *                  characteristic and some do not, because the special case handling code is hard
 *                  compiled in.  For this reason, all images in a batch should be constructed from
 *                  the same list of descriptor parameters.
 *
 *  @param  batch   The MPSImageBatch to increment
 *  @param  amount  The value to add to the read count for each unique image in the batch
 *  @return         The number of different images in the batch
 */
NSUInteger MPSImageBatchIncrementReadCount( MPSImageBatch * __nonnull batch, NSInteger amount )
    MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @abstract Call [MTLBlitEncoder synchronizeResource:] on unique resources*/
void MPSImageBatchSynchronize( MPSImageBatch * __nonnull batch, __nonnull id <MTLCommandBuffer> cmdBuf )
    MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @abstract Call [MTLBlitEncoder resourceSize] on unique resources and return sum */
NSUInteger MPSImageBatchResourceSize( MPSImageBatch * __nonnull batch )
    MPS_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0));

/*! @abstract   Iterate over unique images in the batch
 *  @discussion This function looks only at image address to determine uniqueness.
 *              The same texture stored in different MPSImages would be considered not unique.
 *
 *  @param      batch           The image batch
 *  @param      iteratorBlock   Callback block to execute once for each unique image.
 *                              Return a value greater than NSIntegerMin to terminate early.
 *                              The index gives the first position in the batch where the image appears.
 *                              Behavior is undefined if MPSImageBatchIterate is called recursively on the same images.
 *  @return     The value returned by the iterator block for the last image on which it ran */
NSInteger MPSImageBatchIterate( MPSImageBatch * __nonnull batch,
                                NSInteger (^__nonnull iteratorBlock)( MPSImage * __nonnull image, NSUInteger index ) )
    MPS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0));

/*! @abstract       A class  that allocates new MPSImage or MPSTemporaryImage
 *  @discussion     Sometimes it is prohibitively costly for MPS to figure out how
 *                  big an image should be in advance. In addition, you may want to
 *                  have some say over whether the image is a temporary image or not.
 *                  In such circumstances, the MPSImageAllocator is used to
 *                  provide the developer with an opportunity for just in time feedback
 *                  about how the image should be allocated.
 *
 *                  Two standard MPSImageAllocators are provided: MPSImageDefaultAllocator
 *                  and MPSTemporaryImageDefaultAllocator. You may of course provide
 *                  your own allocator instead.
 *
 *                  Example:
 *                  @code
 *                      // Note: MPSImageDefaultAllocator is already provided
 *                      //       by the framework under that name.  It is provided here
 *                      //       as sample code for writing your own variant.
 *                      -(MPSImage * __nonnull)  imageForCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
 *                                                     imageDescriptor: (MPSImageDescriptor * __nonnull) descriptor
 *                                                              kernel: (MPSKernel * __nonnull) kernel
 *                      {
 *                          MPSImage * result = [[MPSImage alloc] initWithDevice: cmdBuf.device
 *                                                               imageDescriptor: descriptor ];
 *
 *                          // make sure the object sticks around at least as lomg as the command buffer
 *                          [result retain];
 *                          [cmdBuf addCompletedHandler: ^(id <MTLCommandBuffer> c){[result release];}];
 *
 *                          // return autoreleased result
 *                          return [result autorelease];
 *                      };
 *
 *                      -(BOOL) supportsSecureCoding{ return YES; }
 *                      -(void)encodeWithCoder:(NSCoder * __nonnull)aCoder
 *                      {
 *                          [super encodeWithCoder: aCoder];
 *
 *                          // encode any data owned by the class at this level
 *                      }
 *
 *                      -(nullable instancetype) initWithCoder: (NSCoder*__nonnull) aDecoder
 *                      {
 *                          self =  [super initWithCoder: aDecoder ];
 *                          if( nil == self )
 *                              return self;
 *
 *                          // use coder to load any extra data kept by this object here
 *
 *                          return self;
 *                      }
 *                  @endcode
 *
 *              Please see [MPSImage defaultAllocator] and [MPSTemporaryImage defaultAllocator]
 *              for implentations of the protocol already provided by MPS.
 *
 *              When considering whether to write your own MPSImageAllocator, you should know
 *              the existing MPSImage and MPSTemporaryImage default allocators are optimized
 *              to make image batch allocation much faster than one MPSImage at a time in a loop.
 *              When possible, it can be better to use the MPS provided allocators and override
 *              the behavior in a padding policy instead, if the changes can be contained in
 *              the MPSImageDescriptor. This will help reduce CPU encode time. However, custom
 *              padding policies can inhibit optimizations in the MPSNNGraph, particularly node
 *              fusion, resulting in more work for the GPU. In cases where the custom padding method
 *              does not change filter properties but only adjusts the result image (e.g. adjust result
 *              feature channel format) then MPSNNPaddingMethodCustomWhitelistForNodeFusion may be
 *              used to signal that node fusion is acceptable. 
 */

@protocol MPSImageAllocator <NSObject, NSSecureCoding>
@required
/*! @abstract   Create a new MPSImage
 *  @discussion See class description for sample implementation
 *  @param          cmdBuf      The MTLCommandBuffer on which the image will be initialized.
 *                              cmdBuf.device encodes the MTLDevice.
 *  @param          descriptor  A MPSImageDescriptor containing the image format to use.
 *                              This format is the result of your MPSPadding policy.
 *  @param          kernel      The kernel that will overwrite the image returned by the filter.
 *                              Note that the MPS implementations of this protocol don't need
 *                              this field. It is provided for your convenience.
 *
 *  @return         A valid MPSImage or MPSTemporaryImage. It will be automatically released when the command buffer completes.
 */
-(MPSImage * __nonnull)  imageForCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                               imageDescriptor: (MPSImageDescriptor * __nonnull) descriptor
                                        kernel: (MPSKernel * __nonnull) kernel;

/* The allocator must support all three methods of NSSecureCoding as well:
 @property (class, readonly) BOOL supportsSecureCoding;
 - (void)encodeWithCoder:(NSCoder *__nonnull)aCoder;
 - (nullable instancetype)initWithCoder:(NSCoder *__nonnull)aDecoder NS_DESIGNATED_INITIALIZER;
 */
    
@optional
    /*! @abstract   Efficiently create an array of MPSImages with a common descriptor
     *  @discussion See class description for sample implementation
     *  @param          cmdBuf      The MTLCommandBuffer on which the image will be initialized.
     *                              cmdBuf.device encodes the MTLDevice.
     *  @param          descriptor  A MPSImageDescriptor containing the image format to use.
     *                              This format is the result of your MPSPadding policy.
     *  @param          kernel      The kernel that will overwrite the image returned by the filter.
     *                              Note that the MPS implementations of this protocol don't need
     *                              this field. It is provided for your convenience.
     *  @param          count       The number of images in the batch
     *
     *  @return         A valid MPSImage or MPSTemporaryImage. It will be automatically released when the command buffer completes.
     */
-(MPSImageBatch * __nonnull)  imageBatchForCommandBuffer: (__nonnull id <MTLCommandBuffer>) cmdBuf
                                         imageDescriptor: (MPSImageDescriptor * __nonnull) descriptor
                                                  kernel: (MPSKernel * __nonnull) kernel
                                                   count: (NSUInteger) count;
@end



#if defined(DOXYGEN)
    typedef enum MPSPurgeableState
#else
    typedef NS_ENUM(NSUInteger, MPSPurgeableState)
#endif
{
    MPSPurgeableStateAllocationDeferred MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), macCatalyst(13.0), tvos(10.0)) MPS_SWIFT_NAME(allocationDeferred) = 0,                // The buffer hasn't been allocated yet. Attempts to set purgeability will be ignored.
    MPSPurgeableStateKeepCurrent        MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), macCatalyst(13.0), tvos(10.0)) = MTLPurgeableStateKeepCurrent,
    
    MPSPurgeableStateNonVolatile        MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), macCatalyst(13.0), tvos(10.0)) = MTLPurgeableStateNonVolatile,
    MPSPurgeableStateVolatile           MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), macCatalyst(13.0), tvos(10.0)) = MTLPurgeableStateVolatile,
    MPSPurgeableStateEmpty              MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(10.0), macCatalyst(13.0), tvos(10.0)) = MTLPurgeableStateEmpty,
} NS_ENUM_AVAILABLE(10_11, 8_0)
#if defined(DOXYGEN)
    MPSPurgeableState
#endif
;
    
#if defined(DOXYGEN)
    typedef enum MPSDataLayout
#else
    typedef NS_ENUM(NSUInteger, MPSDataLayout)
#endif
{
    // output as order [imageNum][imageHeight][imageWidth][numberOfFeatureChannels]
    MPSDataLayoutHeightxWidthxFeatureChannels MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0)) MPS_SWIFT_NAME(HeightxWidthxFeatureChannels) = 0,
    // output as order [imageNum][numberOfFeatureChannels][imageHeight][imageWidth]
    MPSDataLayoutFeatureChannelsxHeightxWidth MPS_ENUM_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0)) = 1,
} NS_ENUM_AVAILABLE(10_13, 11_0)
#if defined(DOXYGEN)
    MPSDataLayout
#endif
;
    
/*!
 *  @struct     MPSImageReadWriteParams
 *  @abstract   these parameters are passed in to allow user to read/write to a particular set of featureChannels in an MPSImage
 */
typedef struct
{
    NSUInteger featureChannelOffset;               /**< featureChannel offset from which to read/write featureChannels, this should be a multiple of 4 */
    NSUInteger numberOfFeatureChannelsToReadWrite; /**< is number of featureChannels, should be greater than 0 and multiple of 4 unless featureChannelOffset is 0 */
}MPSImageReadWriteParams;

/*!
 *  @class      MPSImage
 *  @dependency This depends on Metal.framework
 *  @abstract   A MPSImage object describes a MTLTexture that may have more than 4 channels.
 *  @discussion Some image types, such as those found in convolutional neural networks (CNN) 
 *              differ from a standard texture in that they may have more than 4 channels
 *              per image. While the channels could hold RGBA data, they will more commonly 
 *              hold a number of structural permutations upon a multi-channel image as the neural
 *              network progresses. It is not uncommon for each pixel to have 32 or 64 channels 
 *              in it.
 *
 *              A standard MTLTexture may have no more than 4 channels. The additional
 *              channels are stored in slices of 2d texture array (i.e. texture type is MTLTextureType2DArray) 
 *              such that 4 consecutive channels are stored in each slice of this array.
 *              If the number of feature channels is N, number of array slices needed is (N+3)/4.
 *              E.g. a CNN image with width 3 and height 2 with 9 channels will be stored as
 * @code
 *              slice 0   RGBA   RGBA  RGBA
 *                        RGBA   RGBA  RGBA
 *
 *              slice 1      RGBA   RGBA   RGBA
 *                           RGBA   RGBA   RGBA         (ASCII art /diagonal offset/ intended to show a Z dimension)
 *
 *              slice 2         R???   R???   R???
 *                              R???   R???   R???
 *@endcode
 *              The width and height of underlying 2d texture array is the same as the width and height of the MPSImage.
 *              The array length is equal to (featureChannels + 3) / 4. Channels marked with ? are just
 *              for padding and should not contain NaNs or Infs.
 *
 *              A MPSImage can be container of multiple CNN images for batch processing. In order to create a
 *              MPSImage that contains N images, create MPSImageDescriptor with numberOfImages set to N.
 *
 *              Although a MPSImage can contain numberOfImages > 1, the actual number of images among these processed by MPSCNNKernel
 *              is controlled by z-dimension of the clipRect. A MPSCNNKernel processes n=clipRect.size.depth images from this collection.
 *              The starting source image index to process is given by offset.z. The starting index of the destination image is given by 
 *              clipRect.origin.z. The MPSCNNKernel takes n=clipRect.size.depth images from tje source at indices [offset.z, offset.z+n], 
 *              processes each independently and stores the result in the destination at indices [clipRect.origin.z, clipRect.origin.z+n] 
 *              respectively. Offset.z+n should be <= [src numberOfImage] and clipRect.origin.z+n should be <= [dest numberOfImages] and 
 *              offset.z must be >= 0.
 *
 *              Example: Suppose MPSCNNConvolution takes an input image with 8 channels and outputs an image with 16 channels. The number of
 *              slices needed in the source 2d texture array is 2 and the number of slices needed in the destination 2d array is 4. Suppose 
 *              the source batch size is 5 and destination batch size is 4. (Multiple N-channel images can be processed concurrently in a 
 *              batch.) The number of source slices will be 2*5=10 and number of destination slices will be 4*4=16. If you want to process
 *              just images 2 and 3 of the source and store the result at index 1 and 2 in the destination, you may achieve this by setting
 *              offset.z=2, clipRect.origin.z=1 and clipRect.size.depth=2. MPSCNNConvolution will take, in this case, slice 4 and 5 of source and
 *              produce slices 4 to 7 of destination. Similarly, slices 6 and 7 will be used to produce slices 8 to 11 of destination.
 *
 *              All MPSCNNKernels process images within each batch independently. That is, calling a MPSCNNKernel on an
 *              batch is formally the same as calling it on each image in the batch one at a time. However, quite a lot of CPU and GPU overhead 
 *              will be avoided if batch processing is used. This is especially important for better performance on small images.
 *
 *              If the number of feature channels is <= 4 and numberOfImages = 1 i.e. only one slice is needed to represent a MPSImage, the underlying
 *              metal texture type will be MTLTextureType2D rather than MTLTextureType2DArray.
 *
 *              There are also MPSTemporaryImages, intended for use for very short-lived image data that are produced and consumed
 *              immediately in the same MTLCommandBuffer. They are a useful way to minimize CPU-side texture allocation costs and 
 *              greatly reduce the amount of memory used by your image pipeline.
 *
 *              Creation of the underlying texture may in some cases occur lazily.  You should
 *              in general avoid calling MPSImage.texture except when unavoidable to avoid
 *              materializing memory for longer than necessary. When possible, use the other MPSImage
 *              properties to get information about the MPSImage instead.
 *
 *              Most MPSImages of 4 or fewer feature channels can generate quicklooks output in
 *              Xcode for easy visualization of image data in the object. MPSTemporaryImages can not.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), macCatalyst(13.0), tvos(10.0))
@interface MPSImage :  NSObject

/*!     Get a well known MPSImageAllocator that makes MPSImages */
+(nonnull id <MPSImageAllocator>)  defaultAllocator;

/*! @property device
 *  @abstract  The device on which the MPSImage will be used
 */
@property (readonly, retain, nonatomic, nonnull)  id <MTLDevice>    device;

/*! @property   width
 *  @abstract   The formal width of the image in pixels.
 */
@property (readonly, nonatomic) NSUInteger width;

/*! @property   height
 *  @abstract   The formal height of the image in pixels.
 */
@property (readonly, nonatomic) NSUInteger height;

/*! @property   featureChannels
 *  @abstract   The number of feature channels per pixel.
 */
@property (readonly, nonatomic) NSUInteger featureChannels;

/*! @property   numberOfImages
 *  @abstract   numberOfImages for batch processing
 */
@property (readonly, nonatomic) NSUInteger numberOfImages;

/*! @property   textureType
 *  @abstract   The type of the underlying texture, typically MTLTextureType2D
 *              or MTLTextureType2DArray
 */
@property (readonly, nonatomic) MTLTextureType textureType;

/*! @property   pixelFormat
 *  @abstract   The MTLPixelFormat of the underlying texture
 *  @discussion Note that in some cases, this value may be misleading. For example,
 *              float16 data (BFloat16) is sometimes stored in MTLPixelFormatRGBA16Unorm
 *              Please consult the featureChannelFormat.
 */
@property (readonly, nonatomic) MTLPixelFormat pixelFormat;

/*! @property   precision
 *  @abstract   The number of bits of numeric precision available for each feature channel.
 *  @discussion This is precision, not size.  That is, float is 24 bits, not 32. half
 *              precision floating-point is 11 bits, not 16. SNorm formats have one less
 *              bit of precision for the sign bit, etc. For formats like MTLPixelFormatB5G6R5Unorm
 *              it is the precision of the most precise channel, in this case 6.  When this
 *              information is unavailable, typically compressed formats, 0 will be returned.
 */
@property (readonly, nonatomic) NSUInteger precision;

/*!
 *  @property   usage
 *  @abstract   Description of texture usage.
 */
@property (readonly, nonatomic) MTLTextureUsage usage;

/*! @property   featureChannelFormat
 *  @abstract   The true encoding of the feature channels
 */
@property (readonly, nonatomic) MPSImageFeatureChannelFormat featureChannelFormat;

/*!
 *  @property   pixelSize
 *  @abstract   Number of bytes from the first byte of one pixel to the first byte of the next 
 *              pixel in storage order.  (Includes padding.)
 */
@property (readonly, nonatomic) size_t  pixelSize;


/*! @property   texture
 *  @abstract   The associated MTLTexture object.
 *              This is a 2D texture if numberOfImages is 1 and number of feature channels <= 4.
 *              It is a 2D texture array otherwise.
 *  @discussion To avoid the high cost of premature allocation of the underlying texture, avoid calling this
 *              property except when strictly necessary. [MPSCNNKernel encode...] calls typically cause
 *              their arguments to become allocated. Likewise, MPSImages initialized with -initWithTexture:
 *              featureChannels: have already been allocated.
 */
@property (readonly, nonnull, nonatomic) id <MTLTexture> texture;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (copy, atomic, nullable)  NSString *label;

/*! @abstract   The MPSImage from which this MPSImage was derived. Otherwise nil.
 *  @discussion This will point to the original image if this image was created using
 *              -batchRepresentation, -batchRepresentationWithRange: or
 *              -subImageWithFeatureChannelRange:.  */
@property (readonly, nullable, retain, nonatomic)  MPSImage * parent;

/*!
 *  @abstract   Initialize an empty image object
 *  @param      device              The device that the image will be used. May not be NULL.
 *  @param      imageDescriptor     The MPSImageDescriptor. May not be NULL.
 *  @return     A valid MPSImage object or nil, if failure.
 *  @discussion Storage to store data needed is allocated lazily on first use of MPSImage or
 *              when application calls MPSImage.texture
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                       imageDescriptor: (const MPSImageDescriptor * __nonnull) imageDescriptor;


/*! @abstract   Use -batchRepresentation or -subImageWithFeatureChannelRange instead
 *  @discussion Generally, you should call -batchRepresentation or -subImageWithFeatureChannelRange
 *              instead because they are safer. This is provided so that these interfaces will work
 *              with your MPSImage subclass.
 *
 *  @param  parent  The parent image that owns the texture. It may be a sub-image.
 *  @param  sliceRange  The range of MTLTexture2dArray slices to be included in the sub-image
 *  @param  featureChannels The number of feature channels in the new image. The number of images
 *                          is inferred.
 *  @return A MPSImage that references a subregion of the texel storage in parent instead of
 *              using its own storage.  */
-(nonnull instancetype) initWithParentImage: (MPSImage * __nonnull) parent
                                 sliceRange: (NSRange) sliceRange
                            featureChannels: (NSUInteger) featureChannels NS_DESIGNATED_INITIALIZER;


/*!
 *  @abstract   Initialize an MPSImage object using Metal texture. Metal texture has been created by
 *              user for specific number of feature channels and number of images.
 *  @param      texture          The MTLTexture allocated by the user to be used as backing for MPSImage.
 *  @param      featureChannels  Number of feature channels this texture contains.
 *  @return     A valid MPSImage object or nil, if failure.
 *  @discussion Application can let MPS framework allocate texture with properties specified in imageDescriptor 
 *              using initWithDevice:MPSImageDescriptor API above. However in memory intensive application, 
 *              you can save memory (and allocation/deallocation time) by using MPSTemporaryImage where MPS 
 *              framework aggressively reuse memory underlying textures on same command buffer. See MPSTemporaryImage
 *              class for details below. However, in certain cases, application developer may want more control
 *              on allocation, placement, reusing/recycling of memory backing textures used in application using
 *              Metal Heaps API. In this case, application can create MPSImage from pre-allocated texture using 
 *              initWithTexture:featureChannels.
 *
 *              MTLTextureType of texture can be MTLTextureType2D ONLY if featureChannels <= 4 in which case
 *              MPSImage.numberOfImages is set to 1. Else it should be MTLTextureType2DArray with
 *              arrayLength == numberOfImage * ((featureChannels + 3)/4). MPSImage.numberOfImages is set to
 *              texture.arrayLength / ((featureChannels + 3)/4).
 *
 *              For MTLTextures containing typical image data which application may obtain from MetalKit or 
 *              other libraries such as that drawn from a JPEG or PNG, featureChannels should
 *              be set to number of valid color channel e.g. for RGB data, even thought MTLPixelFormat will be
 *              MTLPixelFormatRGBA, featureChannels should be set to 3.
 *
 */
-(nonnull instancetype) initWithTexture: (nonnull id <MTLTexture>) texture
                        featureChannels: (NSUInteger) featureChannels;


/*
 * Use initWithDevice:texture: or initWithDevice:imageDescriptor: instead
 */
-(nonnull instancetype) init NS_UNAVAILABLE;


/*! @abstract       Make a representation of a MPSImage (batch) as a MPSImageBatch
 *  @discussion     Before the MPSImageBatch was introduced, several images could be concatenated
 *                  into a MPSImage as multiple image slices in a MTLTexture2DArray to make
 *                  a image batch. If the image contained more than 4 feature channels, then each
 *                  image would have round_up( feature channels / 4) slices and the total number
 *                  of slices in the MPSImage would be slices * number of images.
 *
 *                  Because many devices can operate on texture arrays of no more than 2048 slices,
 *                  storage in this format is limited. For example in InceptionV3, 2048 feature
 *                  channels at its widest point, the largest batch size that can be processed in
 *                  this way is 4, well under commonly accepted practice for training. Consequently,
 *                  the older batching style is deprecated and the MPSImageBatch is introduced.
 *                  It is also easier to manage sub-batches and to concatenate sub-batches for
 *                  memory management with the MPSImageBatch, so this format is favored going forward.
 *
 *                  To facilitate forward migration, this method will prepare an array of MPSImages that
 *                  each point to the appropriate set of slices in storage for the original image.
 *                  Since they share storage, writes to the parent will alter the content of the
 *                  children, and vice versa.
 *
 *                  If the original is a temporary image, the result will be a temporary image.
 *                  It will hold 1 readCount on the original. When the readCount drops to 0, it
 *                  will decrement the appropriate counter on the parent.
 *
 *                  This is a much cheaper form of the slice operator, and should be used instead
 *                  when the slice operator does not need to operate out of place.
 *
 *  @param  subRange  The range of images in the original image from which the batch will be derived.
 *  @return A MPSImageBatch referencing a subregion of the original batch image.
 */
-(MPSImageBatch * __nonnull)  batchRepresentationWithSubRange: (NSRange) subRange;
 
 /*! @abstract    Make a MPSImageBatch that points to the individual images in the MPSImage
  * @discussion   If the original is a temporary image, the result will be a temporary image.
  *               It will hold 1 readCount on the original. When the readCount drops to 0, it
  *               will decrement the appropriate counter on the parent.
  *  @return A MPSImageBatch aliasing the texel storage in the original batch image */
-(MPSImageBatch * __nonnull)  batchRepresentation;

/* @abstract    Make a sub-image that points to a subset of feature channels in the original
 * @discussion  This makes a MPSImage that points to a feature channel subregion within
 *              the original image. It is a much cheaper form of the slice operator in both
 *              memory usage and GPU time, and should be used instead when the slice operator
 *              does not need to operate out of place and the feature channel range is a
 *              multiple of 4.
 *
 *              If the original is a temporary image, the result will be a temporary image.
 *              It will hold 1 readCount on the original. When the readCount drops to 0, it
 *              will decrement the appropriate counter on the parent.
 *
 * @param       range     A range describing the sub-range within the MPSImage
 *                        to make the subImage within. The location and length
 *                        must be multiples of 4. If the length is too big, it
 *                        will be reduced to fit in the image.
 */
-(MPSImage * __nonnull) subImageWithFeatureChannelRange: (NSRange) range;
 
/*! @abstract       Get the number of bytes used to allocate underyling MTLResources
 *  @discussion     This is the size of the backing store of underlying MTLResources.
 *                  It does not include all storage used by the object, for example
 *                  the storage used to hold the MPSImage instantiation and MTLTexture
 *                  is not included. It only measures the size of the allocation
 *                  used to hold the texels in the image. This value is subject to
 *                  change between different devices and operating systems.
 *
 *                  Except when -initWithTexture:featureChannels: is used, most
 *                  MPSImages (including MPSTemporaryImages) are allocated without
 *                  a backing store. The backing store is allocated lazily when
 *                  it is needed, typically when the .texture property is called.
 *                  Consequently, in most cases, it should be inexpensive to make
 *                  a MPSImage to see how much memory it will need, and release it
 *                  if it is too large.
 *
 *                  This method may fail in certain circumstances, such as when the
 *                  MPSImage is created with -initWithTexture:featureChannels:, in
 *                  which case 0 will be returned. 0 will also be returned if
 *                  it is a sub-image or sub-batch (.parent is not nil).
 */
-(NSUInteger)  resourceSize
    MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));

/*! @abstract       Set (or query) the purgeability state of a MPSImage
 *  @discussion     Usage is per [MTLResource setPurgeableState:], except that the MTLTexture might be
 *                  MPSPurgeableStateAllocationDeferred, which means there is no texture to mark volatile / nonvolatile.
 *                  Attempts to set purgeability on MTLTextures that have not been allocated will be ignored.
 */
- (MPSPurgeableState)setPurgeableState:(MPSPurgeableState)state;

/*!
 *  @method         readBytes
 *  @abstract       Get the values inside MPSImage and put them in the Buffer passed in.
 *  @param          dataBytes                    The array allocated by the user to be used to put data from MPSImage, the length should be
 *                                               imageWidth * imageHeight * numberOfFeatureChannels and dataType should be inferred from pixelFormat
 *                                               defined in the Image Descriptor.
 *  @param          dataLayout                   The enum tells how to layout MPS data in the buffer.
 *  @param          bytesPerRow                  Bytes to stride to point to next row(pixel just below current one) in the user buffer.
 *  @param          featureChannelInfo           information user fills in to write to a set of feature channels in the image
 *  @param          imageIndex                   Image index in MPSImage to write to.
 *  @param          region                       region of the MPSImage to read from. A region is a structure with the origin in the Image from which to start
 *                                               reading values and a size which represents the width and height of the rectangular region to read from.
 *                                               The z direction denotes the number of images, thus for 1 image, origin.z = 0 and size.depth = 1
 *  @discussion     Use the enum to set data is coming in with what order. The data type will be determined by the pixelFormat
 *                  defined in the Image Descriptor.
 */
-(void)  readBytes: (void * __nonnull)dataBytes
        dataLayout: (MPSDataLayout)dataLayout
       bytesPerRow: (NSUInteger)bytesPerRow
            region: (MTLRegion)region
featureChannelInfo: (MPSImageReadWriteParams)featureChannelInfo
        imageIndex: (NSUInteger)imageIndex
        MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));


/*! @abstract       Set the values inside MPSImage with the Buffer passed in.
 *  @param          dataBytes                    The array allocated by the user to be used to put data from MPSImage, the length should be
 *                                               imageWidth * imageHeight * numberOfFeatureChannels and dataType should be inferred from pixelFormat
 *                                               defined in the Image Descriptor.
 *  @param          dataLayout                   The enum tells how to layout MPS data in the buffer.
 *  @param          bytesPerRow                  Bytes to stride to point to next row(pixel just below current one) in the user buffer.
 *  @param          region                       region of the MPSImage to write to. A region is a structure with the origin in the Image from which to start
 *                                               writing values and a size which represents the width and height of the rectangular region to write in.
 *                                               The z direction denotes the number of images, thus for 1 image, origin.z = 0 and size.depth = 1
 *  @param          featureChannelInfo           information user fills in to read from a set of feature channels in the image
 *  @param          imageIndex                   Image index in MPSImage to write to.
 *  @discussion     This method is used to copy data from the storage provided by dataBytes to the MPSImage. The ordering of data in
 *                  your dataBytes buffer is given by dataLayout. Each image may be stored as either a series of planar images (a series of single WxH images, one per
 *                  feature channel) or a single chunky image, WxHxfeature_channels. BytesPerRow and BytesPerImage are there to allow some padding between
 *                  successive rows and successive images. No padding is allowed between successive feature channels.
 */
-(void) writeBytes: (const void * __nonnull)dataBytes
        dataLayout: (MPSDataLayout)dataLayout
       bytesPerRow: (NSUInteger)bytesPerRow
            region: (MTLRegion)region
featureChannelInfo: (MPSImageReadWriteParams)featureChannelInfo
        imageIndex: (NSUInteger)imageIndex
        MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));

/*! @abstract       Set the values inside MPSImage with the Buffer passed in.
 *  @param          dataBytes                    The array allocated by the user to be used to put data from MPSImage, the length should be
 *                                               imageWidth * imageHeight * numberOfFeatureChannels and dataType should be inferred from pixelFormat
 *                                               defined in the Image Descriptor.
 *  @param          dataLayout                   The enum tells how to layout MPS data in the buffer.
 *  @param          bytesPerColumn               This is the stride in bytes from W[0] to W[1], for both HWC and CHW orderings in the buffer pointed to by dataBytes.
 *  @param          bytesPerRow                  Bytes to stride to point to next row(pixel just below current one, i.e. H[0] to H[1]) in the buffer pointed to by  dataBytes.
 *  @param          bytesPerImage                This is the stride in bytes from image[0] to image[1] im the buffer pointed to by dataBytes.
 *  @param          region                       region of the MPSImage to write to. A region is a structure with the origin in the Image from which to start
 *                                               writing values and a size which represents the width and height of the rectangular region to write in.
 *                                               The z direction denotes the number of images, thus for 1 image, origin.z = 0 and size.depth = 1
 *  @param          featureChannelInfo           information user fills in to read from a set of feature channels in the image
 *  @param          imageIndex                   Image index in MPSImage to write to.
 *  @discussion     This method is used to copy data from the storage provided by dataBytes to the MPSImage. The ordering of data in
 *                  your dataBytes buffer is given by dataLayout. Each image may be stored as either a series of planar images (a series of single WxH images, one per
 *                  feature channel) or a single chunky image, WxHxfeature_channels. BytesPerRow and BytesPerImage are there to allow some padding between
 *                  successive rows and successive images. No padding is allowed between successive feature channels.
 */
-(void) writeBytes: (const void * __nonnull)dataBytes
        dataLayout: (MPSDataLayout)dataLayout
    bytesPerColumn: (NSUInteger)bytesPerColumn
       bytesPerRow: (NSUInteger)bytesPerRow
     bytesPerImage: (NSUInteger)bytesPerImage
            region: (MTLRegion)region
featureChannelInfo: (MPSImageReadWriteParams)featureChannelInfo
        imageIndex: (NSUInteger)imageIndex
        MPS_AVAILABLE_STARTING( macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0));


/*!
 *  @method         readBytes
 *  @abstract       Get the values inside MPSImage and put them in the Buffer passed in.
 *  @param          dataBytes                    The array allocated by the user to be used to put data from MPSImage, the length should be
 *                                               imageWidth * imageHeight * numberOfFeatureChannels and dataType should be inferred from pixelFormat
 *                                               defined in the Image Descriptor.
 *  @param          dataLayout                   The enum tells how to layout MPS data in the buffer.
 *  @param          bytesPerRow                  Bytes to stride to point to next row(pixel just below current one) in the user buffer.
 *  @param          bytesPerImage                Bytes to stride to point to next dataBytes image. See region.size.depth for image count.
 *  @param          featureChannelInfo           information user fills in to write to a set of feature channels in the image
 *  @param          imageIndex                   Image index in MPSImage to write to.
 *  @param          region                       region of the MPSImage to read from. A region is a structure with the origin in the Image from which to start
 *                                               reading values and a size which represents the width and height of the rectangular region to read from.
 *                                               The z direction denotes the number of images, thus for 1 image, origin.z = 0 and size.depth = 1
 *
 *  @discussion     This method is used to copy data from the MPSImage to the storage provided by dataBytes. The ordering of data in
 *                  your dataBytes buffer is given by dataLayout. Each image may be stored as either a series of planar images (a series of single WxH images, one per
 *                  feature channel) or a single chunky image, WxHxfeature_channels. BytesPerRow and BytesPerImage are there to allow some padding between
 *                  successive rows and successive images. No padding is allowed between successive feature channels.
 *
 *                  BUG: Prior to MacOS 10.15, iOS/tvOS 13.0, incorrect behavior may be observed if region.size.depth != 1 or if
 *                       bytesPerRow allowed for unused padding between rows.
 *                  BUG: To provide for full capability to extract and insert content from arbitrarily sized buffers, there should
 *                       also be a featureChannelStride in addition to bytesPerRow and bytesPerImage. With the current design, when we finish the
 *                       last feature channel, the next byte will contain the 0th feature channel for the next texel or slice, depending
 *                       on packing order. This method can not be used to modify some but not all of the feature channels in an image.
 */
-(void)  readBytes: (void * __nonnull)dataBytes
        dataLayout: (MPSDataLayout)dataLayout
       bytesPerRow: (NSUInteger)bytesPerRow
     bytesPerImage: (NSUInteger)bytesPerImage
            region: (MTLRegion)region
featureChannelInfo: (MPSImageReadWriteParams)featureChannelInfo
        imageIndex: (NSUInteger)imageIndex
        MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));

/*!
 *  @method         writeBytes
 *  @abstract       Set the values inside MPSImage with the Buffer passed in.
 *  @param          dataBytes                    The array allocated by the user to be used to put data from MPSImage, the length should be
 *                                               imageWidth * imageHeight * numberOfFeatureChannels and dataType should be inferred from pixelFormat
 *                                               defined in the Image Descriptor.
 *  @param          dataLayout                   The enum tells how to layout MPS data in the buffer.
 *  @param          bytesPerRow                  Bytes to stride to point to next row(pixel just below current one) in the user buffer.
 *  @param          bytesPerImage                Bytes to stride to point to next dataBytes image. See region.size.depth for image count.
 *  @param          region                       region of the MPSImage to write to. A region is a structure with the origin in the Image from which to start
 *                                               writing values and a size which represents the width and height of the rectangular region to write in.
 *                                               The z direction denotes the number of images, thus for 1 image, origin.z = 0 and size.depth = 1
 *  @param          featureChannelInfo           information user fills in to read from a set of feature channels in the image
 *  @param          imageIndex                   Image index in MPSImage to write to.
 *  @discussion     Use the enum to set data is coming in with what order. The data type will be determined by the pixelFormat
 *                  defined in the Image Descriptor.
 *
 *                  BUG: Prior to MacOS 10.15, iOS/tvOS 13.0, incorrect behavior may be observed if region.size.depth != 1 or if
 *                       bytesPerRow allowed for unused padding between rows.
 *                  BUG: To provide for full capability to extract and insert content from arbitrarily sized buffers, there should
 *                       also be a featureChannelStride in addition to bytesPerRow and bytesPerImage. With the current design, when we finish the
 *                       last feature channel, the next byte will contain the 0th feature channel for the next texel or slice, depending
 *                       on packing order. This method can not be used to modify some but not all of the feature channels in an image.
 */
-(void) writeBytes: (const void * __nonnull)dataBytes
        dataLayout: (MPSDataLayout)dataLayout
       bytesPerRow: (NSUInteger)bytesPerRow
     bytesPerImage: (NSUInteger)bytesPerImage
            region: (MTLRegion)region
featureChannelInfo: (MPSImageReadWriteParams)featureChannelInfo
        imageIndex: (NSUInteger)imageIndex
        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));


/*!
 *  @method         readBytes
 *  @abstract       Get the values inside MPSImage and put them in the Buffer passed in.
 *  @param          dataBytes                    The array allocated by the user to be used to put data from MPSImage, the length should be
 *                                               imageWidth * imageHeight * numberOfFeatureChannels and dataType should be inferred from pixelFormat
 *                                               defined in the Image Descriptor.
 *  @param          dataLayout                   The enum tells how to layout MPS data in the buffer.
 *  @param          imageIndex                   Image index in MPSImage to read from.
 *  @discussion     Use the enum to set data is coming in with what order. The data type will be determined by the pixelFormat
 *                  defined in the Image Descriptor. Region is full image, buffer width and height is same as MPSImage width and height.
 */
-(void) readBytes: (void * __nonnull)dataBytes
       dataLayout: (MPSDataLayout)dataLayout
       imageIndex: (NSUInteger)imageIndex
        MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));


/*!
 *  @method         writeBytes
 *  @abstract       Set the values inside MPSImage with the Buffer passed in.
 *  @param          dataBytes                    The array allocated by the user to be used to put data from MPSImage, the length should be
 *                                               imageWidth * imageHeight * numberOfFeatureChannels and dataType should be inferred from pixelFormat
 *                                               defined in the Image Descriptor.
 *  @param          dataLayout                   The enum tells how to layout MPS data in the buffer.
 *  @param          imageIndex                   Image index in MPSImage to write to.
 *  @discussion     Use the enum to set data is coming in with what order. The data type will be determined by the pixelFormat
 *                  defined in the Image Descriptor. Region is full image, buffer width and height is same as MPSImage width and height.
 */
-(void) writeBytes: (const void * __nonnull)dataBytes
        dataLayout: (MPSDataLayout)dataLayout
        imageIndex: (NSUInteger)imageIndex
        MPS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0));

/*! @abstract   Flush the underlying MTLTexture from the device's caches, and invalidate any CPU caches if needed.
 *  @discussion This will call [id <MTLBlitEncoder> synchronizeResource: ] on the image's MTLTexture, if any.
 *              This is necessary for all MTLStorageModeManaged resources. For other resources, including temporary
 *              resources (these are all MTLStorageModePrivate), and textures that have not yet been allocated, nothing is done.
 *              It is more efficient to use this method than to attempt to do this yourself with the texture property.
 *  @param      commandBuffer       The commandbuffer on which to synchronize   */
-(void) synchronizeOnCommandBuffer: (__nonnull id <MTLCommandBuffer>) commandBuffer
        MPS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));


@end

/*!
 *  @class      MPSTemporaryImage
 *  @dependency MPSImage
 *  @abstract   MPSTemporaryImages are for MPSImages with short lifetimes.
 *
 *  @discussion What is temporary memory? It is memory, plain and simple. Analogy: If we
 *              use an app as an analogy for a command buffer, then "Regular memory"
 *              (such as what backs a MPSImage or the typical MTLTexture) would be memory 
 *              that you allocate at launch and never free. Temporary memory would be memory 
 *              that you free when you are done with it so it can be used for something 
 *              else as needed later in your app.  You /could/ write your app to allocate 
 *              everything you will ever need up front, but this is very inefficient and 
 *              quite frankly a pain to plan out in advance. You don't do it for your app,
 *              so why would you do it for your command buffers? 
 *
 *              Welcome to the 1970's! We have added a heap.
 *
 *              Unsurprisingly, MPSTemporaryImages can provide for profound reduction in
 *              the the amount of memory used by your application.  Like malloc, MPS 
 *              maintains a heap of memory usable in a command buffer. Over the lifetime 
 *              of a command buffer, the same piece of memory may be reused many times. 
 *              This means that each time the same memory is reused, it aliases with previous
 *              uses. If we aren't careful, we might find that needed data is overwritten
 *              by successive allocations. However, this is no different than accessing freed
 *              memory only to discover it doesn't contain what you thought it did anymore, 
 *              so you should be able to keep out of trouble by following a few simple rules,
 *              like with malloc.
 *
 *              To this end, we added some restrictions to help you out and get a bit more 
 *              performance. Some comments are appended in parentheses below to extend the
 *              analogy of command buffer = program:
 *
 *              - The textures are MTLStorageModePrivate. You can not, for example, use
 *                [MTLTexture getBytes...] or [MTLTexture replaceRegion...] with them. 
 *                MPSTemporaryImages are strictly read and written by the GPU. (There is
 *                protected memory to prevent other processes from overwriting your heap.)
 *
 *              - The temporary image may be used only on a single MTLCommandBuffer.
 *                This limits the chronology to a single linear time stream. (The heap
 *                is specific to just one command buffer. There are no mutexes to
 *                coordinate timing of simultaneous access by multiple GPUs. Nor are we
 *                likely to like them if there were. So, we disallow it.)
 *
 *              - The readCount property must be managed correctly. Please see
 *                the description of the readCount property for full details. (The readCount
 *                is a reference count for the block of memory that holds your data. The
 *                usual undefined behaviors apply to reading data that has been released.
 *                We assert when we can to prevent that from happening accidentally,
 *                just as a program might segfault. The readCount counts procedural users 
 *                of the object -- MPSKernel.encode... calls that read the MPSTemporaryImage. 
 *                As each reads from it, the readCount is automatically decremented. The 
 *                texture data will be freed in typical usage at the right time as the 
 *                readCount reaches zero, typically with little user involvement other
 *                than to set the readCount up front. We did examine using the main MPSTemporaryImage
 *                reference count for this instead so that ARC would do work for you automatically.
 *                Alas, ARC destroys things at end of scope rather than promptly, sometimes resulting
 *                in greatly increased memory usage. These allocations are large! So, we 
 *                use this method instead.)
 *
 *              Since MPSTemporaryImages can only be used with a single MTLCommandBuffer,
 *              and can not be used off the GPU, they generally should not be kept 
 *              around past the completion of the MTLCommandBuffer. The lifetime of
 *              MPSTemporaryImages is expected to be typically extremely short, perhaps 
 *              only a few lines of code. Like malloc, it is intended to be fairly cheap 
 *              to make MPSTemporaryImages and throw them away. Please do so.
 *
 *              To keep the lifetime of the underlying texture allocation as short as 
 *              possible, the underlying texture is not allocated until the first time
 *              the MPSTemporaryImage is used by a MPSCNNKernel or the .texture property
 *              is read. The readCount property serves to limit the lifetime on the
 *              other end.
 *
 *              You may use the MPSTemporaryImage.texture with MPSUnaryImageKernel -encode... methods,
 *              iff featureChannels <= 4 and the MTLTexture conforms to requirements of that MPSKernel.
 *              There is no locking mechanism provided to prevent a MTLTexture returned 
 *              from the .texture property from becoming invalid when the readCount reaches 0.
 *
 *              Finally, MPSTemporaryImages are complicated to use with blit encoders.
 *              Your application should assume that the MPSTemporaryImage is backed by a MTLHeap,
 *              and consequently needs a MTLFence to ensure that compute command encoders and other
 *              encoders do not trip over one another with heap based memory. MPS will almost never
 *              use a blit encoder for this reason. If you do need one, then you will need to make
 *              a new compute encoder to block on whatever previous compute encoder last used the
 *              heap block. (MPS will not tell you who previously used the heap block. That encoder
 *              is almost certainly long dead anyway.) If concurrent encoders are involved, then a
 *              barrier might be needed. Within that compute encoder, you will call -updateFence.
 *              End the compute encoder, make a blit encoder wait for the fence, do the blit, update
 *              a new fence, then make a new compute encoder, wait for the second fence, then you
 *              can continue. Possibly the second do-nothing compute encoder needs to be ended so
 *              MPS can be called. Frankly, we don't bother with blit encoders and just write a compute
 *              operation for copy / clear as needed, or better yet find a way to eliminate the
 *              clear / copy pass so we don't have to pay for it. Note: the most common use of a
 *              blit encoder, -synchronizeResource: can not encounter this problem because
 *              MPSTemporaryImages live in GPU private memory and can not be read by the CPU.
 *
 *              MPSTemporaryImages can otherwise be used wherever MPSImages are used.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), macCatalyst(13.0), tvos(10.0))
@interface  MPSTemporaryImage : MPSImage

/*!     Get a well known MPSImageAllocator that makes MPSTemporaryImages */
+(nonnull id <MPSImageAllocator>)  defaultAllocator;


/*!
 *  @abstract   Initialize a MPSTemporaryImage for use on a MTLCommandBuffer
 *
 *  @param      commandBuffer   The MTLCommandBuffer on which the MPSTemporaryImage will be exclusively used
 *
 *  @param      imageDescriptor A valid imageDescriptor describing the MPSImage format to create.
 *
 *  @return     A valid MPSTemporaryImage.  The object will be released when the command buffer
 *              is committed. The underlying texture will become invalid before this time
 *              due to the action of the readCount property.
 *
 */
+(nonnull instancetype) temporaryImageWithCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                        imageDescriptor: (const MPSImageDescriptor * __nonnull) imageDescriptor;


/*!
 *  @abstract       Low level interface for creating a MPSTemporaryImage using a MTLTextureDescriptor
 *  @discussion     This function provides access to MTLPixelFormats not typically covered by -initForCommandBuffer:imageDescriptor:
 *                  The feature channels will be inferred from the MTLPixelFormat without changing the width. 
 *                  The following restrictions apply:
 *  
 *                      MTLTextureType must be MTLTextureType2D or MTLTextureType2DArray
 *                      MTLTextureUsage must contain at least one of MTLTextureUsageShaderRead, MTLTextureUsageShaderWrite
 *                      MTLStorageMode must be MTLStorageModePrivate
 *                      depth must be 1
 *
 *  @param commandBuffer        The command buffer on which the MPSTemporaryImage may be used
 *  @param textureDescriptor    A texture descriptor describing the MPSTemporaryImage texture
 *
 *  @return     A valid MPSTemporaryImage.  The object will be released when the command buffer
 *              is committed. The underlying texture will become invalid before this time
 *              due to the action of the readCount property.
 */
+(nonnull instancetype) temporaryImageWithCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                      textureDescriptor: (const MTLTextureDescriptor * __nonnull) textureDescriptor;

/*!
 *  @abstract       Low level interface for creating a MPSTemporaryImage using a MTLTextureDescriptor
 *  @discussion     This function provides access to MTLPixelFormats not typically covered by -initForCommandBuffer:imageDescriptor:
 *                  The number of images will be inferred from number of slices in the descriptor.arrayLength and
 *                  the number of feature channels.
 *
 *                  The following restrictions apply:
 *
 *                      MTLTextureType must be MTLTextureType2D or MTLTextureType2DArray
 *                      MTLTextureUsage must contain at least one of MTLTextureUsageShaderRead, MTLTextureUsageShaderWrite
 *                      MTLStorageMode must be MTLStorageModePrivate
 *
 *  @param commandBuffer        The command buffer on which the MPSTemporaryImage may be used
 *  @param textureDescriptor    A texture descriptor describing the MPSTemporaryImage texture
 *
 *  @return     A valid MPSTemporaryImage.  The object will be released when the command buffer
 *              is committed. The underlying texture will become invalid before this time
 *              due to the action of the readCount property.
 */
+(nonnull instancetype) temporaryImageWithCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                      textureDescriptor: (const MTLTextureDescriptor * __nonnull) textureDescriptor
                                        featureChannels: (NSUInteger) featureChannels
                            MPS_AVAILABLE_STARTING(macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3));

/*! @abstract       Help MPS decide which allocations to make ahead of time
 *  @discussion     The texture cache that underlies the MPSTemporaryImage can automatically allocate new storage as
 *                  needed as you create new temporary images.  However, sometimes a more global view of what you
 *                  plan to make is useful for maximizing memory reuse to get the most efficient operation.
 *                  This class method hints to the cache what the list of images will be.
 *
 *                  It is never necessary to call this method. It is purely a performance and memory optimization.
 *
 *                  This method makes a conservative estimate of memory required and may not fully
 *                  cover temporary memory needs, resulting in additional allocations later that could
 *                  encounter pathological behavior, if they are too small. If the full extent and timing of the
 *                  workload is known in advance, it is recommended that MPSHintTemporaryMemoryHighWaterMark() be
 *                  used instead.
 *
 *  @param commandBuffer        The command buffer on which the MPSTemporaryImages will be used
 *  @param descriptorList       A NSArray of MPSImageDescriptors, indicating images that will be created
 */
+(void) prefetchStorageWithCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                     imageDescriptorList: (NSArray <MPSImageDescriptor*> * __nonnull) descriptorList;

/*! Unavailable. Use temporaryImageForCommandBuffer:textureDescriptor: or -temporaryImageForCommandBuffer:imageDescriptor: instead. */
-(nonnull instancetype) initWithTexture: (nonnull id <MTLTexture>) texture
                        featureChannels: (NSUInteger) featureChannels NS_UNAVAILABLE;

/*! Unavailable. Use itemporaryImageForCommandBuffer:textureDescriptor: instead. */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                       imageDescriptor: (const MPSImageDescriptor * __nonnull) imageDescriptor      NS_UNAVAILABLE;

/*
 *  @abstract       The number of times a temporary image may be read by a MPSCNNKernel
 *                  before its contents become undefined.
 *
 *  @discussion     MPSTemporaryImages must release their underlying textures for reuse
 *                  immediately after last use. So as to facilitate *prompt* convenient 
 *                  memory recycling, each time a MPSTemporaryImage is read by a 
 *                  MPSCNNKernel -encode... method, its readCount is automatically 
 *                  decremented. When the readCount reaches 0, the underlying texture is 
 *                  automatically made available for reuse to MPS for its own needs and for 
 *                  other MPSTemporaryImages prior to return from the -encode.. function.  
 *                  The contents of the texture become undefined at this time. 
 *
 *                  By default, the readCount is initialized to 1, indicating a image that
 *                  may be overwritten any number of times, but read only once.
 *
 *                  You may change the readCount as desired to allow MPSCNNKernels to read
 *                  the MPSTemporaryImage additional times. However, it is an error to change
 *                  the readCount once it is zero. It is an error to read or write to a
 *                  MPSTemporaryImage with a zero readCount. You may set the readCount to 0
 *                  yourself to cause the underlying texture to be returned to MPS. Writing
 *                  to a MPSTemporaryImage does not adjust the readCount.
 *
 *                  The Metal API Validation layer will assert if a MPSTemporaryImage is
 *                  deallocated with non-zero readCount to help identify cases when resources
 *                  are not returned promptly.
 */
@property (readwrite, nonatomic)  NSUInteger  readCount;


@end


    
#ifdef __cplusplus
}   // extern "C"
#endif


#endif /* MPSImage_h */
