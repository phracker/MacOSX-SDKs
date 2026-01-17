/*!
 *  @header MetalPerformanceShaders.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 */

#import <MPSCore/MPSCore.h>
#import <MPSImage/MPSImage.h>
#import <MPSMatrix/MPSMatrix.h>
#import <MPSNeuralNetwork/MPSNeuralNetwork.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  MPSSupportsMTLDevice
 *  @abstract   Determine whether a MetalPerformanceShaders.framework  supports a MTLDevice.
 *  @discussion Use this function to determine whether a MTLDevice can be used with interfaces in MetalPerformanceShaders.framework.
 *  @param      device          A valid MTLDevice
 *  @return     YES             The device is supported.
 *              NO              The device is not supported
 */
BOOL    MPSSupportsMTLDevice( __nullable id <MTLDevice> device )  MPS_AVAILABLE_STARTING( macos(10.13), ios(9.0), tvos(9.0));



//
//  These headers contain doxygen formatted documentation. They are human readable as is,
//  but can be processed as such to make something a bit nicer looking.  Our version of
//  the doxygen PDF output may be found in MetalPerformanceShaders.framework/Documentation:
//
//      open `xcrun --show-sdk-path -sdk iphoneos9.0`/System/Library/Frameworks/MetalPerformanceShaders.framework/Documentation/MetalPerformanceShaders.pdf
//
//  Associated man pages are installed in the SDKROOT.
//
//      man -M `xcrun --show-sdk-path -sdk iphoneos9.0`/usr/share/man  MPSKernel
//

/*! @mainpage Metal Performance Shaders - High Performance Kernels on Metal
 *  @section  section_introduction  Introduction
 *
 *  MetalPerformanceShaders.framework is a framework of highly optimized compute and graphics shaders that are
 *  designed to integrate easily and efficiently into your Metal application.  These data-parallel 
 *  primitives are specially tuned to take advantage of the unique hardware characteristics of each
 *  iOS GPU to ensure optimal performance. Applications adopting MetalPerformanceShaders can be sure of achieving
 *  optimal performance without needing to update their own hand-written shaders for each new iOS GPU 
 *  generation. MetalPerformanceShaders can be used along with the application's existing Metal resources (such as 
 *  the MTLCommandBuffer, MTLBuffer and MTLTexture objects) and shaders.
 *
 *  In iOS 9, MetalPerformanceShaders.framework provides a series of commonly-used image processing primitives for 
 *  image effects on Metal textures.
 *
 *  In iOS 10, MetalPerformanceShaders.framework adds support for the following kernels:
 *  -  collection of kernels to implement and run neural networks using previously obtained training data, on the GPU
 *  -  new image processing filters to perform color-conversion and for building a gaussian pyramid
 *
 *  @subsection subsection_usingMPS  Using MPS
 *  To use MPS:
 *   @code
 *      link:     -framework MetalPerformanceShaders
 *      include:  #include <MetalPerformanceShaders/MetalPerformanceShaders.h>
 *
 *      Advisory: MetalPerformanceShaders features are broken up into many subheaders which are
 *                included by MetalPerformanceShaders.h.   The exact placement of interfaces in
 *                headers is subject to change, as functionality in component sub-frameworks can
 *                move into MPSCore.framework when the functionality needs to be shared by
 *                multiple components when features are added. To avoid source level breakage,
 *                #include the top level MetalPerformanceShaders.h header instead of lower
 *                level headers.  iOS 11 already broke source compatibility for lower level headers
 *                and future releases will probably do so again. The only supported method of
 *                including MPS symbols is the top level framework header.
 *    @endcode
 *    On macOS, MetalPerformanceShaders.framework is 64-bit only.  If you are still supporting
 *    the 32-bit i386 architecture, you can link just your 64-bit slice to MPS using a Xcode
 *    user defined build setting.  For example, you can add a setting called LINK_MPS:
 *    @code
 *        LINK_MPS
 *            Debug    -framework MetalPerformanceShaders
 *                Intel architecture            <leave this part empty>
 *            Release  -framework MetalPerformanceShaders
 *                Intel architecture            <leave this part empty>
 *    @endcode
 *
 *    The 64-bit intel architectures will inherit from the generic definition on the Debug and
 *    Release lines. Next, add $(MPS_LINK) to the Other Linker Flags line in your Xcode build
 *    settings.
 *
 *    In code segments built for both i386 and x86-64 you will need to keep the i386 segment
 *    from attempting to use MPS. In C, C++ and Objective C, a simple #ifdef will work fine.
 *    @code
 *        BOOL IsMPSSupported( id <MTLDevice> device )
 *        {
 *        #ifdef __i386__
 *            return NO;
 *        #else
 *            return MPSSupportsMTLDevice(device);
 *        #endif
 *        }
 *    @endcode
 *
 *
 *  @section section_data    Data containers
 *  @subsection subsection_metal_containers  MTLTextures and MTLBuffers
 *
 *  Most data operated on by Metal Performance Shaders must be in a portable data container appropriate
 *  for use on the GPU, such as a MTLTexture, MTLBuffer or MPSImage/MPSMatrix/MPSVector.  The first two
 *  should be self-explanatory based on your previous experience with Metal.framework. MPS will use these
 *  directly when it can.  The other three are wrapper classes designed to make MTLTextures and MTLBuffers
 *  easier to use, especially when the data may be packed in the texture or buffer in an unusual order, or
 *  typical notions like texel do not map to the abstraction (e.g. feature channel) well. MPSImages and
 *  MPSMatrices also come in "temporary" variants. Temporary images and matrices aggressively share
 *  memory with one another, saving a great deal of processor time allocating and tearing down textures.
 *  (This uses MTLHeaps underneath, if you are familiar with that feature.) MPS manages the aliasing to
 *  keep you safe. In exchange you must manage the resource readCount.
 *
 *  Most MPSImage and MPSCNN filters operate only on floating-point or normalized texture formats.
 *  If your data is in a UInteger or Integer MTLPixelFormat (e.g. MTLPixelFormatR8Uint as opposed
 *  to MTLPixelFormatR8Unorm) then you may need to make a texture view of the texture to change
 *  the type using [(id <MTLTexture>) newTextureViewWithPixelFormat:(MTLPixelFormat)pixelFormat],
 *  to reinterpret the data to a normalized format of corresponding signedness and precision. In certain
 *  cases such as thresholding corresponding adjustments (e.g. /255) may have to also be made to
 *  parameters passed to the MPSKernel.
 *
 *  @subsection subsection_mpsimage  MPSImages
 *  Convolutional neural networking (CNN) filters may need more than the four data channels that a
 *  MTLTexture can provide. In these cases, the MPSImage is used instead as an abstraction
 *  layer on top of a MTLTexture. When more than 4 channels are needed, additional textures in the texture2d 
 *  array are added to hold additional channels in sets of four. The MPSImage tracks this information as the 
 *  number of "feature channels" in an image.
 *
 *  @subsection subsection_mpstemporaryimage  MPSTemporaryImages
 *  The MPSTemporaryImage (subclass of MPSImage) extends the MPSImage to provide advanced caching of
 *  reusable memory to increase performance and reduce memory footprint. They are intended as fast
 *  GPU-only storage for intermediate image data needed only transiently within a single MTLCommandBuffer.
 *  They accelerate the common case of image data which is created only to be consumed and destroyed
 *  immediately by the next operation(s) in a MTLCommandBuffer.  MPSTemporaryImages provide convenient and 
 *  simple way to save memory by automatically aliasing other MPSTemporaryImages in the MTLCommandBuffer.
 *  Because they alias (share texel storage with) other textures in the same MTLCommandBuffer, the valid 
 *  lifetime of the data in a MPSTeporaryImage is extremely short, limited to a portion of a MTLCommandBuffer. 
 *  You can not read or write data to a MPSTemporaryImage using the CPU, or use the data in other MTLCommandBuffers.
 *  Use regular MPSImages for more persistent storage.
 *
 *  Why do we need MPSTemporaryImages?  Consider what it would be like to write an app without a heap.
 *  All allocations would have to be either on the stack or staticly allocated at app launch. You
 *  would find that allocations that persist for the lifetime of the app are very wasteful when an object
 *  is only needed for a few microseconds. Likewise, once the memory is statically partitioned in this way,
 *  it is hard to dynamically reuse memory for other purposes as different tasks are attempted and the needs
 *  of the app change. Finally, having to plan everything out in advance is just plain inconvenient! Isn't it
 *  nicer to just call malloc() or new as needed? Yes, it is. Even if it means we have to also call free(),
 *  find leaks and otherwise manage the lifetime of the allocation through some mechanism like reference counting,
 *  or add __strong and __weak so that ARC can help us, we do it.
 *
 *  It should be therefore of little surprise that after the heap data structure by JWJ Williams in 1964, the
 *  heap has been a mainstay of computer science since. The heap allocator was part of the C language a decade
 *  later. Yet, 50 years on, why is it not used in GPU programming? Developers routinely still allocate resources
 *  up front that stay live for the lifetime of the program (command buffer). Why would you do that?
 *  MPSTemporaryImages are MPSImages that use a memory allocated by a command buffer associated heap to store
 *  texels. They only use the memory they need for the part of the command buffer that they need it in, and the
 *  memory is made available for other MPSTemporaryImages that live in another part of the same command buffer.
 *  This allows for a very high level of memory reuse. In the context of a MPSNNGraph, for example, the
 *  InceptionV3 neural network requires 121 MPSImages to hold intermediate results. However, since it uses
 *  MPSTemporaryImages instead, these are reduced to just four physical allocations of the same size as one of
 *  the original images. Do you believe most of your work should be done using MPSTemporaryImages? You should.
 *  You only need the persistent MPSImage for storage needed outside the context of the command buffer, for
 *  example those images that might be read from or written to by the CPU. Use MPSTemporaryImages for
 *  transient storage needs. In aggregate, they are far less expensive than regular MPSImages. Create them,
 *  use them, throw them away, all within a few lines of code. Make more just in time as needed.
 *
 *  @section section_discussion     The MPSKernel
 *
 *  The MPSKernel is the base class for all MPS kernels. It defines baseline behavior for all MPS 
 *  kernels, declaring the device to run the kernel on, some debugging options and a user-friendly
 *  label, should one be required. From this are derived the MPSUnaryImageKernel and MPSBinaryImageKernel
 *  sub-classes which define shared behavior for most image processing kernels (filters) such as
 *  edging modes, clipping and tiling support for image operations that consume one or two source textures.
 *  Neither these or the MPSKernel are typically be used directly. They just provide API abstraction
 *  and in some cases may allow some level of polymorphic manipulation of MPS image kernel objects.
 *
 *  Subclasses of the MPSUnaryImageKernel and MPSBinaryImageKernel provide specialized -init and -encode 
 *  methods to encode various image processing primitives into your MTLCommandBuffer, and may also
 *  provide additional configurable properties on their own. Many such image filters are available:
 *  There are convolutions (generic, box, Sobel, and Gaussian) to do edge detection, sharpening and 
 *  blurring, morphological operators -- Min, Max, Dilate and Erode -- and histogram operations. 
 *  In addition, there are median, resampling filters and others. All of these run on the GPU directly 
 *  on MTLTextures and MTLBuffers.
 *
 *  As the MPSKernel/MPSUnaryImageKernel/MPSBinaryImageKernel classes serve to unify a diversity of image
 *  operations into a simple consistent interface and calling sequence to apply image filters, 
 *  subclasses implement details that diverge from the norm. For example, some filters may take a small 
 *  set of parameters (e.g. a convolution kernel) to govern how they function. However, the overall 
 *  sequence for using MPSKernel subclasses remains the same:
 *
 *  -#  Allocate the usual Metal objects: MTLDevice, MTLCommandQueue, and MTLCommandBuffer 
 *      to drive a Metal compute pipeline. If your application already uses Metal, chances are you 
 *      have most of these things already. MPS will fit right in to this workflow. It can 
 *      encode onto MTLCommandBuffers inline with your own workload.
 *
 *  -#  Create an appropriate MPSKernel object. For example, if you want to do a Gaussian blur, make
 *      a MPSImageGaussianBlur object.  MPSKernel objects are generally light weight but can be reused
 *      to save some setup time. They can not be used by multiple threads concurrently, so if you
 *      are using Metal from many threads concurrently, make extra MPSKernel objects. MPSKernel objects
 *      conform to <NSCopying>.
 *
 *  -#  Call [MPSKernelSubclass  encodeToCommandBuffer:...]. Parameters for other -encode... calls
 *      vary by filter type, but operate similarly. They create a MTLCommandEncoder, write commands to 
 *      run the filter into the MTLCommandBuffer and then end the MTLCommandEncoder.  This means
 *      you must call -endEncoding on your current MTLCommandEncoder before calling a MPSKernel encode
 *      method. You can at this point release the MPSKernel or keep it around to use again to save
 *      some setup cost.
 *
 *  -#  If you wish to encode futher commands of your own on the MTLCommandBuffer, you must
 *      create a new MTLCommandEncoder to do so.  
 *
 *  -#  (Standard Metal) When you are done with the MTLCommandBuffer, submit it to the device using
 *      typical Metal commands, such as [MTLCommandBuffer commit]. The MPS filter will begin
 *      running on the GPU. You can either use [MTLCommandBuffer waitUntilCompleted] or
 *      [MTLCommandBuffer addCompletedHandler:] to be notified when the work is done.
 *
 *  Each MPSKernel is allocated against a particular MTLDevice. A single filter may not be used with
 *  multiple MTLDevices. (You will need to make multiple MPSKernels for that.) This is necessary because
 *  the [MPSKernel initWithDevice:...] methods sometimes allocate MTLBuffers and MTLTextures to hold
 *  data passed in as parameters to the -init method and a MTLDevice is required to make those. MPSKernels
 *  provide a copy method that allow them to be copied for a new device.
 *
 *  MPSKernel objects are not entirely thread safe. While they may be used in a multithreaded context,
 *  you should not attempt to have multiple MPSKernel objects writing to the same MTLCommandBuffer at
 *  the same time. They share restrictions with the MTLCommandEncoder in this regard. In limited
 *  circumstances, the same MPSKernel can be used to write to multiple MTLCommandBuffers concurrently.
 *  However, that only works if the MPSKernel is treated as an immutable object. That is, if MPSKernel
 *  subclass properties of a shared filter are changed, then the change can be reflected on the other
 *  thread while the other thread is encoding its work, leading to undefined behavior. It is generally
 *  safest to just make copies of MPSKernel objects, one for each thread.
 *
 *  For more information, please see MPSTypes.h.
 *
 *  @subsection subsection_properties  MPS{Unary/Binary}ImageKernel properties
 *  The MPS{Unary/Binary}ImageKernel base classes define several properties common to all MPSKernels:
 *
 *  @subsubsection  subsubsection_clipRect  MPSKernel clipRect
 *  The clipRect property, common to MPSKernel sublcasses that write to a destination texture, describes
 *  the sub-rectangle of the destination texture overwritten by the filter. If the clipRect is larger than
 *  the destination texture, the intersection between the clipRect and destination texture bounds will be used.
 *  The clipRect may be used to avoid doing work to obscured regions of the destination image, or to
 *  manage tiling and to limit operations to parts of an image if for example, the user drew a rectangle
 *  on the screen and asked you to just apply the filter there.
 *
 *      extern MTLRegion MPSRectNoClip; //Pass this rectangle to fill the entire destination texture.
 *
 *  @subsubsection  subsubsection_MPSoffset  MPSOffset
 *  The offset (or primaryOffset or secondaryOffset) property, common to MPSKernel subclasses that 
 *  use a source texture from which pixel data is read, describes the positioning of the source image
 *  relative to the result texture. A offset of {0,0,0} indicates that the top left pixel of the source
 *  texture is the center pixel used to  create the top left corner of the destination texture clipRect.
 *  An offset of {1,2,0} positions the top left corner of the clipRect at {x=1, y=2, z=0} of the source
 *  image. The offset is the position of the top left corner of the clipRect in the source coordinate
 *  frame. It can be used for tiling and for translating an image up/down or left/right by pixel increments. 
 *  If there is no clipRect then the offset is the top left corner of the region read by the filter.
 *  If there are multiple source textures, then the primaryOffset describes the top left corner of the 
 *  region read in the primary source texture. The secondaryOffset describes the top left corner of the
 *  region read in the secondary source texture, and so forth.
 *
 *  @subsubsection  subsubsection_edgemode  MPSKernelEdgeMode
 *  The edgeMode (or primaryEdgeMode or secondaryEdgeMode)describes the behavior of texture reads that
 *  stray off the edge of the source image. This can happen if the offset is negative, meaning read
 *  off the top or left edge of the image.  It can also happen if the clipRect.size + offset
 *  is larger than the source image, meaning read off the bottom and right of the image. It is
 *  also possible for filters that have a filter window that stretches to examine neighboring pixels,
 *  such as convolution, morphology and resampling filters.  If there are multiple source textures, 
 *  then the primaryEdgeMode describes the MPSKernelEdgeMode to use with primary source texture. 
 *  The secondaryEdgeMode describes the MPSKernelEdgeMode to use with the secondary source texture, 
 *  and so forth.
 *
 *      typedef NS_ENUM(NSUInteger, MPSImageEdgeMode)
 *
 *      MPSImageEdgeModeZero       Out of bound pixels are (0,0,0,1) for image formats without
 *                                      alpha channel and (0,0,0,0) for image with pixel format with an
 *                                      alpha channel
 *
 *      MPSImageEdgeModeClamp      Out of bound pixels are clamped to nearest edge pixel
 *
 *  @subsubsection  subsubsection_options  MPSKernelOptions
 *  Each MPSKernel takes a MPSKernelOptions bit mask to indicate various options to use when running the filter:
 *
 *      typedef NS_OPTIONS(NSUInteger, MPSKernelOptions)
 *
 *      MPSKernelOptionsNone                     Use default options
 *
 *      MPSKernelOptionsSkipAPIValidation        Do not spend time looking at parameters passed to MPS
 *                                              for errors.
 *
 *      MPSKernelOptionsAllowReducedPrecision    When possible, MPSKernels use a higher precision data representation internally than
 *                                              the destination storage format to avoid excessive accumulation of computational
 *                                              rounding error in the result. MPSKernelOptionsAllowReducedPrecision advises the
 *                                              MPSKernel that the destination storage format already has too much precision for
 *                                              what is ultimately required downstream, and the MPSKernel may use reduced precision
 *                                              internally when it feels that a less precise result would yield better performance.
 *                                              When enabled, the precision of the result may vary by hardware and operating system.
 *
 *  @section subsection_availableFilters     Available MPSKernels
 *
 *  @subsection subsection_convolution  Image Convolution
 *  @subsubsection subsubsection_kernel The Image Convolution Kernel
 *  The convolution filter is at its simplest the weighted average of a pixel with its nearest neighbors.
 *  The weights are provided by a convolution kernel.  The number and position of the nearest neighbors 
 *  that are considered are given by the size of the convolution kernel. For example, a convolution kernel
 *  might be the following 5x5 array of weights:
 *  @code
 *              1       2       3       2       1
 *              2       4       6       4       2
 *              3       6      [9]      6       3
 *              2       4       6       4       2
 *              1       2       3       2       1
 *  @endcode
 *  In order to calculate this 5x5 convolution result, one would multiply all of the pixels in the
 *  image within (5/2=) 2 pixels of the desired pixel by its corresponding weight, add them up and divide by
 *  a divisor to renormalize the results. Then, repeat for all other pixels in the area you wish to convolve.
 *
 *  For those MPS filters where the convolution kernel is passed in, you provide the kernel as a
 *  normalized float array. That is, the kernel weights have the divisor already divided into them and
 *  as a consequence should usually sum to 1.0. In our tent example above, the sum over the area of the kernel 
 *  is 81, so one would normalize it as follows:
 *  @code
 *              1/81    2/81    3/81    2/81    1/81
 *              2/81    4/81    6/81    4/81    2/81
 *              3/81    6/81   [9/81]   6/81    3/81
 *              2/81    4/81    6/81    4/81    2/81
 *              1/81    2/81    3/81    2/81    1/81
 *  @endcode
 *  It is not strictly necessary that the filter weights add up to 1.0f.  Edge detection filters frequently add up
 *  to zero. You may decide to have the area under the filter be a bit bigger or smaller than 1.0 to increase
 *  or reduce the contrast in the result.
 *
 *  The MxN kernel is passed in as a 1-dimensional data array in row major order.
 *
 *  Some convolution filters also have a notion of a bias. This is a number to be added to the
 *  result before it is written out to result texture. A bias might be used to uniformly brighten an image,
 *  set a video range baseline (e.g. 0 might actually be encoded as 16/255) or to make negative signal
 *  representable on a unorm image. 
 *
 *          A unorm image is an image comprised of unsigned normalized samples. A typical 8-bit image (e.g. 
 *          MTLPixelFormatRGBA8Unorm) is a unorm image. It has unsigned samples that represent values between
 *          [0,1]. In the case of MTLPixelFormatRGBA8Unorm, the encoding of 0 is 0, and the encoding of 1.0f
 *          is UINT8_MAX (255).
 *
 *  @subsubsection subsubsection_box  The Box, Tent and Gaussian Filters
 *  There are many different convolution kernel shapes which can produce different results. A kernel consisting
 *  of all 1's is called a Box filter. It is very quick to calculate and may run nearly as fast as a texture
 *  copy, even for very large blur radii. The blur effect that you get, however, can be square in appearance
 *  and may not be entirely appealing under close scrutiny. A second pass of the box will lead to a Tent kernel. 
 *  (The 5x5 tent above can be reduced into two 3x3 Box filters.) Its appearance is more pleasing. Tent 
 *  operations can be found in sample code for window shadows. Both Box and Tent filters are provided by 
 *  MPS. Multiple passes of a box and/or tent  filters will tend to converge towards a gaussian line shape 
 *  and produce a smoother blur effect. MPS also provides a Gaussian blur, though it uses a different method.
 *
 *  @subsubsection subsubsection_laplacian   Laplacian and Unsharp Mask Filters
 *  One can in practice also subtract a blur from the image to produce a sharpening effect (unsharp mask). This
 *  is done by preparing a convolution kernel which is a scaled image less a blur to reduce the low frequency
 *  component of an image. This can reduce blur, but may also emphasize noise in the image.  As an example, we
 *  can do identity minus a box blur:
 *  @code
 *                  | 1   1   1 |
 *      k0 * [1] -  | 1   1   1 | * k2
 *                  | 1   1   1 |
 *  @endcode
 *  If we pick k0 = 9 and k2 = 1, so that the two kernels have equal weight, we arrive at:
 *  @code
 *      |-1  -1  -1 |
 *      |-1   8  -1 |
 *      |-1  -1  -1 |
 *  @endcode
 *  This is a Laplacian filter for calculating image gradients (including diagonals in this case).
 *
 *      Caution: because this convolution kernel has negative regions, it can produce negative 
 *      results as well as positive ones from ordinary image data. If you intend to store the 
 *      result in a unorm texture, you'll need to scale it and add a positive value to it to avoid 
 *      having the negative signal clamped off. (e.g. p' = 0.5*p+0.5).
 *
 *  An unsharp mask filter is the sum between the original image and a scaled result of the Laplacian 
 *  filter. The scaling factor (and filter size and shape) adjusts the nature of the low frequency 
 *  signal and the degree to which it is removed. This work can usually be combined into the convolution 
 *  kernel, to do the whole thing in one pass.
 *
 *  @subsubsection subsubsection_sobel   Sobel Edge detection
 *  Instead of integrating over an area, Convolution filters can also differentiate over an
 *  area by subtracting adjacent pixels.  One such  filter is the Sobel edge detection filter. 
 *  It produces bright signal where there are large differences between one pixel and the next 
 *  and black elsewhere:
 *  @code
 *      | -1  0   1 |       | 1   2   1 |
 *   Gx=| -2  0   2 |   Gy= | 0   0   0 |
 *      | -1  0   1 |       |-1  -2  -1 |
 *
 *
 *      result = sqrt( Convolve(src, Gx) * Convolve(src * Gx) +
 *                     Convolve(src, Gy) * Convolve(src * Gy))
 *  @endcode
 *
 *  @subsubsection subsubsection_otherfilters   Other Filters
 *  Other effects can be achieved as well, such as emboss:
 *  @code
 *     -1   0   0
 *      0   0   0
 *      0   0   1
 *  @endcode
 *  @subsubsection subsubsection_separability   Separable Convolution
 *  Some convolution kernels are separable. That is, the filter weights can be factored into the product
 *  of two smaller sets of weights. As an example, the tent kernel shown above can be factored into a 
 *  horizontal and vertical 1-dimensional kernel each containing [1 2 3 2 1]. In this way, what might otherwise
 *  have been a 5x5 convolution with 25 multiplies and 24 adds is instead a 5x1 and 1x5 convolution with 
 *  a total of 10 multiplies and 8 adds and possibly some extra load/store traffic for the two-pass algorithm. 
 *  The savings get bigger for bigger filter areas. MPS convolution filters will automatically separate 
 *  kernels to run faster, when possible. Some filters with fixed kernels such as Box and Guassian are inherently
 *  separable. We attempt to factor the general convolution kernel into 2 1D kernels in the -initWithDevice:...
 *  method.  If you want to factor it yourself, make two MPSImageConvolution objects with 1D kernels.
 *
 *  @subsubsection subsubsection_convolveAvailability   Convolutions in MPS
 *  Convolution filters provided by MPS include:
 *
 *      MPSImageConvolution       <MPSImage/MPSImageConvolution.h>        General convolution
 *      MPSImageGassianBlur       <MPSImage/MPSImageConvolution.h>        Gaussian blur
 *      MPSImageBox               <MPSImage/MPSImageConvolution.h>        Box blur
 *      MPSImageTent              <MPSImage/MPSImageConvolution.h>        Tent blur
 *
 * @subsection subsection_morphology  Morphology
 *  Morphological operators are similar to convolutions in that they find a result by looking at the nearest
 *  neighbors of each pixel in the image. Instead of calculating a weighted average, morphological operators
 *  scan the kernel area looking for the maximum or minimum pixel value. The MPSImageAreaMax and 
 *  MPSImageAreaMin filters return the raw maximum and minimum color channel value in the kernel area for
 *  each pixel, respectively. The MPSImageDilate and MPSImageErode filters do the same thing, except that the probe 
 *  shape need not be a rectangle, and instead can be nearly any shape you desire, such as a antialiased 
 *  oval, star or heart shape.
 *
 *  When applied, the max and dilate filters have the effect of adding their shape on to the periphery of
 *  bright objects in the image. A single bright pixel, such as might be found in a photograph of a starry
 *  night sky will become the shape of a probe -- a rectangle for max, and perhaps a 5-pointed star if
 *  that is the shape you chose for the dilate filter kernel. Larger objects will adopt more rectangular
 *  or star quality into their shape. (An oval or circular probe would round the corners of a rectangular 
 *  object, for example.)  The min and erode filters do similar things to the darker regions of the image.
 *
 *  When a dilate filter is followed by an erode filter (or max followed by min) with similar filters, the 
 *  effect is known as a close operator. Expanding bright areas only to erode them away again leaves most of
 *  the image in roughly the same shape as it started, but small dark areas that are completely removed by the 
 *  dilate operator are not replaced by the erode. Dark noise may be removed. Small enclosed dark area may
 *  be completely filled in by bright signal.  Similarly erode followed by dilate is an open operator. It 
 *  will tend to remove bright fine detail and fill in small bright areas surrounded by dark lines.
 *
 *  To make a MPS morphology filter with a text glyph draw black text on a white background. MPS
 *  morphology filters must have a center pixel with value 0.
 *
 *
 *  Morphology filters provided by MPS include:
 *
 *      MPSImageAreaMax  <MPSImage/MPSImageMorphology.h>       Area Max
 *      MPSImageAreaMin  <MPSImage/MPSImageMorphology.h>       Area Min
 *      MPSImageDilate   <MPSImage/MPSImageMorphology.h>       Dilate
 *      MPSImageErode    <MPSImage/MPSImageMorphology.h>       Erode
 *
 *  @subsection subsection_histogram     Histogram
 *  A image may be examined by taking the histogram of its pixels. This gives the distribution of the various
 *  intensities per color channel. The MPSImageHistogram filter can be used to calculate a histogram for a MTLTexture.
 *
 *  In some cases, as a result of image processing operations the very dark and light regions of the intensity
 *  spectrum can become unpopulated. Perhaps a photograph is underexposed or overexposed. The MPSImageHistogramEqualization
 *  filter will redistribute the intensities to a more uniform distribution, correcting such problems. 
 *  The MPSImageHistogramSpecification class allows you to cause an image to conform to a different histogram. 
 *
 *
 *  Histogram filters provided by MPS include:
 *
 *      MPSImageHistogram              <MPSImage/MPSImageHistogram.h>     Calculate the histogram of an image
 *      MPSImageHistogramEqualization  <MPSImage/MPSImageHistogram.h>     Redistribute intensity in an image to equalize
 *                                                                          the histogram
 *      MPSImageHistogramSpecification <MPSImage/MPSImageHistogram.h>     A generalized version of histogram equalization
 *                                                                          operation. Convert the image so that its histogram
 *                                                                          matches the desired histogram provided to the
 *                                                                          histogram specification filter.
 *
 * @subsection subsection_median  Image Median
 *  Median filters find the median value in a region surrounding each pixel in the source image.  It is frequently
 *  used to remove noise from the image, but may also be used to remove fine detail like a open filter. It is widely
 *  used in image processing because in many cases it can remove noise while at the same time preserving edges.
 *
 *  Median filters provided by MPS include:
 *
 *      MPSImageMedian                <MPSImage/MPSImageMedian.h>         Calculate the median of an image using a
 *                                                                     square filter window.
 *
 *  @subsection subsection_resampling  Image Resampling
 *  Resampling operations are used to convert one regular array of pixels to another regular array of pixels,
 *  typically along a different set of axes and/or using a different sampling period. Changing the sampling period
 *  will enlarge or reduce images and/or distort the aspect ratio. Change of axis results in rotations or arbitrary
 *  affine transforms. 
 *
 *  For most imaging work on the GPU, resampling can be quickly and simply done as part of another pass using a 
 *  Euler matrices or quaternions to transform the coordinate space followed by linear filtering to interpolate the
 *  value found there. However, this can lead to somewhat muddy images and may result in loss of signal when 
 *  downsampling by more than a factor of two unless a low pass filter is applied first. It is also prone to 
 *  the development of Moire patterns in regions of the image with regularly repeating signal, such as a picture
 *  of a masonry grid on the side of a building. 
 *
 *  The MPS resampling routines use a higher quality (but more expensive) Lanczos resampling algorithm. 
 *  Especially with photographic images, it will usually produce a much nicer result. It does not require a low pass
 *  filter be applied to the image before down sampling. However, some ringing can occur near high frequency regions 
 *  of the image, making the algorithm less suitable for vector art.
 *
 *  MetalPerformanceShaders.framework provides a MPSImageScale functions to allow for simple resizing of images into the clipRect
 *  of the result image. They can operate with preservation of aspect ratio or not.
 *
 *      MPSImageLanczosScale        <MPSImage/MPSResample.h>   Resize or adjust aspect ratio of an image using a Lanczos filter.
 *      MPSImageBilinearScale       <MPSImage/MPSResample.h>   Resize or adjust aspect ratio of an image using bilinear interpolation.
 *
 *  Each method has its own advantages. The bilinear method is faster. However, downsampling by more than a factor
 *  of two will lead to data loss, unless a low pass filter is applied before the downsampling operation.  The
 *  lanczos filter method does not have this problem and usually looks better. However, it can lead to ringing
 *  at sharp edges, making it better for photographs than vector art.
 *
 *  @subsection subsection_threshold     Image Threshold
 *  Thresholding operations are commonly used to separate elements of image structure from the rest of an image. 
 *  Generally, these operate by making some sort of simple comparison test, for example color_intensity > 0.5, and
 *  then writing out 0 or 1 (actual values configurable) depending on the truth or falsehood of the result. It is 
 *  frequently used in computer vision, or to accentuate edge detection filters. 
 *
 *  A variety of thresholding operators are supported:
 *
 *      MPSImageThresholdBinary           <MPSImage/MPSImageThreshold.h>  srcPixel > thresholdVal ? maxVal : 0
 *      MPSImageThresholdBinaryInverse    <MPSImage/MPSImageThreshold.h>  srcPixel > thresholdVal ? 0 : maxVal
 *      MPSImageThresholdTruncate         <MPSImage/MPSImageThreshold.h>  srcPixel > thresholdVal ? thresholdVal : srcPixel
 *      MPSImageThresholdToZero           <MPSImage/MPSImageThreshold.h>  srcPixel > thresholdVal ? srcPixel : 0
 *      MPSImageThresholdToZeroInverse    <MPSImage/MPSImageThreshold.h>  srcPixel > thresholdVal ? 0 : srcPixel
 *      MPSImageKeypoint                  <MPSImage/MPSImageKeypoint.h>  return a list of pixels that are greathr than a threshold value
 *
 *  @subsection subsection_images_statistics  Image Statistics
 *  Several statistical operators are available which return statistics for the entire image, or
 *  a subregion. These operators are:
 *
 *      MPSImageStatisticsMinAndMax       <MPSImage/MPSImageStatistics.h> return maximum and minimum values in the image for each channel
 *      MPSImageStatisticsMean            <MPSImage/MPSImageStatistics.h> return the mean channel value over the region of interest
 *      MPSImageStatisticsMeanAndVariance <MPSImage/MPSImageStatistics.h> return the mean channel value and variance of each channel over the region of interest
 *
 *  These filters return the results in a small (1x1 or 2x1) texture. The region over which the
 *  statistical operator is applied is regulated by the clipRectSource property.
 *
 *  @subsection subsection_math     Math Filters
 *  Arithmetic filters take two source images, a primary source image and a secondary source image, as input and
 *  output a single destination image. The filters apply an element-wise arithmetic operator to each pixel in a primary source
 *  image and a corresponding pixel in a secondary source image over a specified region. The supported arithmetic operators
 *  are addition, subtraction, multiplication, and division.
 *
 *  These filters take additional parameters: primaryScale, secondaryScale, and bias and apply them to the primary source
 *  pixel (x) and secondary source pixel (y) in the following way:
 *
 *      MPSImageAdd         <MPSImage/MPSImageMath.h>  Element-wise addition operator:      result = ((primaryScale * x) + (secondaryScale * y)) + bias
 *      MPSImageSubtract    <MPSImage/MPSImageMath.h>  Element-wise subtraction operator    result = ((primaryScale * x) - (secondaryScale * y)) + bias
 *      MPSImageMultiply    <MPSImage/MPSImageMath.h>  Element-wise multiplication operator result = ((primaryScale * x) * (secondaryScale * y)) + bias
 *      MPSImageDivide      <MPSImage/MPSImageMath.h>  Element-wise division operator       result = ((primaryScale * x) / (secondaryScale * y)) + bias
 *
 *  These filters also take the following additional parameters: secondarySourceStrideInPixelsX and secondarySourceStrideInPixelsY.
 *  The default value of these parameters is 1. Setting both of these parameters to 0 results in the secondarySource image being
 *  handled as a single pixel.
 *
 *  @subsection subsection_CNN     Convolutional Neural Networks
 *  Convolutional Neural Networks (CNN) is a machine learning technique that attempts to model the visual cortex as a sequence 
 *  of convolution, rectification, pooling and normalization steps. Several CNN filters commonly derived from the MPSCNNKernel
 *  base class are provided to help you implement these steps as efficiently as possible.
 *

 *      MPSCNNNeuronLinear              <MPSNeuralNetwork/MPSCNNConvolution.h>       A linear neuron activation function
 *      MPSCNNNeuronReLU                <MPSNeuralNetwork/MPSCNNConvolution.h>       A neuron activation function with rectified linear units
 *      MPSCNNNeuronSigmoid             <MPSNeuralNetwork/MPSCNNConvolution.h>       A sigmoid neuron activation function 1/(1+e**-x)
 *      MPSCNNNeuronHardSigmoid         <MPSNeuralNetwork/MPSCNNConvolution.h>       A hard sigmoid neuron activation function clamp((a*x)+b, 0, 1)
 *      MPSCNNNeuronTanH                <MPSNeuralNetwork/MPSCNNConvolution.h>       A neuron activation function using hyperbolic tangent
 *      MPSCNNNeuronAbsolute            <MPSNeuralNetwork/MPSCNNConvolution.h>       An absolute neuron activation function |x|
 *      MPSCNNNeuronSoftPlus            <MPSNeuralNetwork/MPSCNNConvolution.h>       A parametric SoftPlus neuron activation function a*log(1+e**(b*x))
 *      MPSCNNNeuronSoftSign            <MPSNeuralNetwork/MPSCNNConvolution.h>       A SoftSign neuron activation function x/(1+|x|)
 *      MPSCNNNeuronELU                 <MPSNeuralNetwork/MPSCNNConvolution.h>       A parametric ELU neuron activation function x<0 ? (a*(e**x-1)) : x
 *      MPSCNNConvolution               <MPSNeuralNetwork/MPSCNNConvolution.h>       A 4D convolution tensor
 *      MPSCNNConvolutionTranspose      <MPSNeuralNetwork/MPSCNNConvolution.h>       A 4D convolution transpose tensor
 *      MPSCNNFullyConnected            <MPSNeuralNetwork/MPSCNNConvolution.h>       A fully connected CNN layer
 *      MPSCNNPoolingMax                <MPSNeuralNetwork/MPSCNNPooling.h>           The maximum value in the pooling area
 *      MPSCNNPoolingAverage            <MPSNeuralNetwork/MPSCNNPooling.h>           The average value in the pooling area
 *      MPSCNNPoolingL2Norm             <MPSNeuralNetwork/MPSCNNPooling.h>           The L2-Norm value in the pooling area
 *      MPSCNNDilatedPoolingMax         <MPSNeuralNetwork/MPSCNNPooling.h>           The maximum value in the dilated pooling area
 *      MPSCNNSpatialNormalization      <MPSNeuralNetwork/MPSCNNNormalization.h>
 *      MPSCNNCrossChannelNormalization <MPSNeuralNetwork/MPSCNNNormalization.h>
 *      MPSCNNSoftmax                   <MPSNeuralNetwork/MPSCNNSoftMax.h>           exp(pixel(x,y,k))/sum(exp(pixel(x,y,0)) ... exp(pixel(x,y,N-1))
 *      MPSCNNLogSoftmax                <MPSNeuralNetwork/MPSCNNSoftMax.h>           pixel(x,y,k) - ln(sum(exp(pixel(x,y,0)) ... exp(pixel(x,y,N-1)))
 *      MPSCNNUpsamplingNearest         <MPSNeuralNetwork/MPSCNNUpsampling.h>        A nearest upsampling layer.
 *      MPSCNNUpsamplingBilinear        <MPSNeuralNetwork/MPSCNNUpsampling.h>        A bilinear upsampling layer.
 *
 *  MPSCNNKernels operate on MPSImages.  MPSImages are at their core MTLTextures. However, whereas
 *  MTLTextures commonly represent image or texel data, a MPSImage is a more abstract representation
 *  of image features. The channels within a MPSImage do not necessarily correspond to colors in a
 *  color space. (Though, they can.) As a result, there can be many more than four of them. 32 or 64 channels
 *  per pixel is not uncommon.  This is achieved on the MTLTexture hardware abstraction by inserting
 *  extra RGBA pixels to handle the additional feature channels (if any) beyond 4. These extra pixels are
 *  stored as multiple slices of a 2D image array.  Thus, each CNN pixel in a 32-channel image is represented
 *  as 8 array slices, with 4-channels stored per-pixel in each slice.  The width and height of the MTLTexture
 *  is the same as the width and height of the MPSImage.  The number of slices in the MTLTexture is given by
 *  the number of feature channels rounded up to a multiple of 4.
 *
 *  MPSImages can be created from existing MTLTextures. They may also be created anew from a MPSImageDescriptor
 *  and backed with either standard texture memory, or as MPSTemporaryImages using memory drawn from MPS's
 *  internal cached texture backing store.  MPSTemporaryImages can provide great memory usage and CPU time savings,
 *  but come with significant restrictions that should be understood before using them. For example, their contents
 *  are only valid during the GPU-side execution of a single MTLCommandBuffer and can not be read from or written to
 *  by the CPU. They are provided as an efficient way to hold CNN computations that are used immediately within the
 *  scope of the same MTLCommandBuffer and then discarded. We also support concatenation by allowing the user to 
 *  define from which destination feature channel to start writing the output of the current layer. In this way
 *  the application can make a large MPSImage or MPSTemporaryImage and fill in parts of it with multiple layers
 *  (as long as the destination feature channel offset is a multiple of 4).
 *
 *  The standard MPSCNNConvolution operator also does dilated convolution and sub-pixel convolution. There are
 *  also bit-wise convolution operators that can use only a single bit for precision of the weights. The
 *  precision of the image can be reduced to 1 bit in this case as well.  The bit {0,1} represents {-1,1}.
 *
 *  @subsection subsection_RNN     Recurrent Neural Networks
 *
 *  @subsection subsection_matrix_primitives     Matrix Primitives
 *
 *  Some CNN Tips:
 *  - Think carefully about the edge mode requested for pooling layers. The default is clamp to zero, but there
 *    are times when clamp to edge value may be better.
 *  - To avoid falling off the edge of an image for filters that have a filter area (convolution, pooling) set the
 *    MPSCNNKernel.offset = (MPSOffset){ .x = kernelWidth/2, .y = kernelHeight/2, .z = 0}; and reduce the size 
 *    of the output image by {kernelWidth-1, kernelHeight-1,0}. The filter area stretcheds up and to the left
 *    of the MPSCNNKernel.offset by {kernelWidth/2, kernelHeight/2}. While consistent with other MPS imaging operations,
 *    this behavior is different from some other CNN implementations.
 *  - If setting the offset and making MPSImages to hold intermediates are taking up a lot of your time,
 *    consider using the MPSNNGraph instead. It will automate these tasks.
 *  - Please remember:
 *      MPSCNNConvolution takes weights in the order weight[outputChannels][kernelHeight][kernelWidth][inputChannels / groups]
 *      MPSCNNFullyConnected takes weights in the order weight[outputChannels][sourceWidth][sourceHeight][inputChannels]
 *  - Initialize MPSCNNKernels once and reuse them
 *  - You can use MPSCNNNeurons and other Filters in MPS to perform pre-processing of images, such as scaling and resizing.
 *  - Specify a neuron filter with MPSCNNConvolution descriptor to combine the convolution and neuron operations.
 *  - Use MPSTemporaryImages for intermediate images that live for a short period of time (less than one MTLCommandBuffer).
 *      MPSTemporaryImages can reduce the amount of memory used by the convolutional neural network by several fold, and
 *      similarly reduce the amount of CPU time spent allocating storage and latency between MTLCommandBuffer.commit
 *      and when the work actually starts on the GPU.  MPSTemporaryImage are for short lived storage within the time 
 *      period of the execution of a single MTLCommandBuffer. You can not read or write to a MPSTemporaryImage using the CPU.
 *      Generally, they should be created as needed and thrown away promptly.  Persistent objects should not retain them.
 *      Please be sure to understand the use of the MPSTemporaryImage.readCount.
 *  - Because MPS encodes its work in place in your MTLCommandBuffer, you always have the option to insert your own
 *      code in between MPSCNNKernels as a Metal shader for tasks not covered by MPS. You need not use MPS for everything.
 *
 *  @section  section_validation    MPS API validation
 *  MPS uses the same API validation layer that Metal uses to alert you to API mistakes while
 *  you are developing your code. While this option is turned on (Xcode: Edit Scheme: options: Metal API Validation),
 *  common programming errors will either trigger an assert or send a warning to the the debug log. Except
 *  in the case of serious errors, little or no spew should arrive in the console under standard usage. 
 *  You can also try the MPSKernel.options parameter MPSKernelOptionsSkipAPIValidation to skip most of this checking.
 *  The flag may also lead to small reductions in CPU cost.
 *
 *  Note: where APIs are tagged nonnull, MPS expects that the value is not NULL. The validation layer
 *        may do some checking and assert. If you turn that off, then undefined behavior is the result of 
 *        passing nil, and your application will likely be terminated.
 *
 *
 *  @section  section_usage         How to Add MetalPerformanceShaders.framework to your project
 *
 *  Xcode:
 *
 *      1.  Click project file at left, then appropriate target, then select Build Phases.
 *      2.  Open the "Link Binary With Libraries" disclosure triangle
 *      3.  Click the [+] button in the "Link Binary With Libraries" view to add a new library
 *      4.  Select MetalPerformanceShaders.framework from the list.
 *      5.  Click the Add button.
 *
 *  Command Line:
 *
 *      clang  -framework MetalPerformanceShaders    file.c -o file.o
 *
 *  @section  section_support   How to Determine if MPS Works on Your Device
 *  To test whether MPS works on your device, you may call MPSSupportsMTLDevice(id<MTLDevice>).
 *  It will return YES if the device is supported.
 *
 *  @section  section_inplace   In Place Operation
 *  Some MPS filters can operate in place. In-place operation means that the
 *  same texture is used to hold both the input image and the result image. Operating
 *  in place is a great way to save memory, time and energy. You can use a MPS
 *  filter in place using [MPSKernel encodeToCommandBuffer:inPlaceTexture:copyAllocator:].
 *
 *  Unfortunately, it is not always possible for MPS filters to run in place.
 *  Whether a particular MPSKernel can operate in place can vary according to the
 *  hardware it is running on, the operating system version and the parameters and 
 *  properties passed to it. You may not assume that because a MPSKernel works in place
 *  today on a particular device that it will continue to do so in the future. 
 *
 *  To simplify error handling with failed in-place operation, [MPSKernel 
 *  encodeToCommandBuffer:inPlaceTexture:fallbackCopyAllocator:] takes an optional MPSCopyAllocator
 *  parameter. It is used to create a new texture when in-place operation is not possible 
 *  so as to allow the operation to proceed out of place in a reliable fashion instead. 
 *  (When this happens the input texture is released and replaced with a new texture.) 
 *  To make use of this feature, you will need to write a MPSCopyAllocator block.
 *
 *  @subsection subsection_micopyallocator  MPSCopyAllocator
 *  Some MPSKernel objects may not be able to operate in place. When that occurs, and in-place
 *  operation is requested, MPS will call back to this block to get a new texture
 *  to overwrite instead. To avoid spending long periods of time allocating pages to back the
 *  MTLTexture, the block should attempt to reuse textures. The texture returned from the
 *  MPSCopyAllocator will be returned instead of the sourceTexture from the MPSKernel method
 *  on return. Here is a minimal MPSCopyAllocator implementation:
 *  @code
 *  // A MPSCopyAllocator to handle cases where in-place operation fails.
 *  MPSCopyAllocator myAllocator = ^id <MTLTexture>( MPSKernel * __nonnull filter,
 *                                                  __nonnull id <MTLCommandBuffer> cmdBuf,
 *                                                  __nonnull id <MTLTexture> sourceTexture)
 *  {
 *      MTLPixelFormat format = sourceTexture.pixelFormat;  // FIXME: is this format writable?
 *      MTLTextureDescriptor *d = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: format
 *                                   width: sourceTexture.width
 *                                  height: sourceTexture.height
 *                               mipmapped: NO];
 *      d.usage = MTLTextureUsageShaderRead | MTLTextureUsageShaderWrite;
 *
 *      //FIXME: Allocating a new texture each time is slow. They take up to 1 ms each.
 *      //       There are not too many milliseconds in a video frame! You can recycle
 *      //       old textures (or MTLBuffers and make textures from them) and reuse
 *      //       the memory here.
 *      id <MTLTexture> result = [cmdBuf.device newTextureWithDescriptor: d];
 *
 *      // FIXME: If there is any metadata associated with sourceTexture such as colorspace
 *      //        information, MTLResource.label, MTLResource.cpuCacheMode mode,
 *      //        MTLResource.MTLPurgeableState, etc., it may need to be similarly associated
 *      //        with the new texture, to avoid losing your metadata.
 *
 *      // FIXME: If filter.clipRect doesn't cover the entire image, you may need to copy
 *      //        pixels from sourceTexture to result or regions of result will be
 *      //        uninitialized. You can make a MTLCommandEncoder to encode work on the
 *      //        MTLCommandBuffer here to do that work, if necessary. It will be scheduled
 *      //        to run immediately before the MPSKernel work. Do not call
 *      //        [MTLCommandBuffer enqueue/commit/waitUntilCompleted/waitUntilScheduled]
 *      //        in the MPSCopyAllocator block. Make sure to call -endEncoding on the
 *      //        MTLCommandEncoder so that the MTLCommandBuffer has no active encoder
 *      //        before returning.
 *
 *      // CAUTION: The next command placed on the MTLCommandBuffer after the MPSCopyAllocator
 *      //          returns is almost assuredly going to be encoded with a MTLComputeCommandEncoder.
 *      //          Creating any other type of encoder in the MPSCopyAllocator will probably cost
 *      //          an additional 0.5 ms of both CPU _AND_ GPU time (or more!) due to a double
 *      //          mode switch penalty.
 *
 *      return result;
 *      // d is autoreleased
 *  };
 *  @endcode
 *
 *       filter          A valid pointer to the MPSKernel that is calling the MPSCopyAllocator. From
 *                       it you can get the clipRect of the intended operation.
 *       cmdBuf          A valid MTLCommandBuffer. It can be used to obtain the device against
 *                       which to allocate the new texture. You may also enqueue operations on
 *                       the commandBuffer to initialize the texture. You may not submit, enqueue
 *                       or wait for completion of the command buffer.
 *       sourceTexture   The texture that is providing the source image for the filter. You may
 *                       wish to copy its size and MTLPixelFormat for the new texture, but it is
 *                       not requred.
 *
 *       return          A new valid MTLTexture to use as the destination for the MPSKernel.
 *                       The format of the returned texture does not need to match sourceTexture.
 *
 *  @section  section_mpsnngraph   The MPSNNGraph
 *  New for macOS 10.13, iOS/tvOS 11 is a higher level graph API, intended to simplify the creation of
 *  neural networks. The graph is a network of MPSNNFilterNodes, MPSNNImageNodes and  MPSNNStateNodes. 
 *  MPSNNImageNodes represent MPSImages or MPSTemporaryImages. MPSNNFilterNodes represent MPSCNNKernel
 *  objects -- each of the lower level MPSCNNKernel subclasses has a sister object that is a
 *  subclass of the MPSNNFilterNode. Finally, MPSStateNodes stand in for MPSState objects. 
 *
 *  MPSState objects are also new for macOS 10.13, iOS/tvOS 11. They stand in for bits of opaque state that
 *  need to be handed  between filter nodes.  For example, a MPSCNNConvolutionTranspose filter may need to
 *  know the original size of the filter passed into the corresponding MPSCNNConvolution node farther up the
 *  tree. There is a corresponding MPSCNNConvolutionState object that tracks this information. You will
 *  encounter state objects only infrequently. Most graphs are made up of images and filters.
 *
 *  To represent a graph, one usually first creates a MPSNNImageNode. This represents the input image or
 *  tensor into the graph. Next one creates a the first filter node to process that input image. For example,
 *  we may make a MPSCNNNeuronLinearNode to normalize the data before the rest of the graph sees it. (y = 2x-1)
 *  Then, we can add our first convolution in the graph.
 *  @code
 *      //  Graph:   [Image] -> [Linear neuron filter] -> (result image) -> [convolution filter] -> (result image)...
 *      MPSNNImageNode *startNode = [MPSImageNode nodeWithHandle: nil];
 *      MPSCNNNeuronLinearNode *norm = [MPSCNNNeuronLinearNode nodeWithSource: startNode a: 2.0f b: -1.0f ];
 *      MPSCNNConvolutionNode *c = [MPSCNNConvolutionNode nodeWithSource: norm.resultImage
 *                                                               weights: [[MyWeights alloc] initWithPath: "weights1.dat"]];
 *      ...
 *  @endcode
 *  There are some features to notice about each object. First of all, each image node can have a handle 
 *  associated with it. The handle is your object that you write. It should conform to the <MPSHandle>
 *  protocol, which specifies that the object should have a label and conform to NSSecureCoding. (The MTLTexture
 *  does have a label property but doesn't conform to NSSecureCoding.) NSSecureCoding is used when you
 *  save the graph to disk using a NSCoder. It isn't used otherwise. You can use a MTLResource here if 
 *  you don't plan to save the graph to disk.  What is the handle for?  When the MPSNNGraph object is 
 *  constructed -- the MPSNNGraph takes the network of filter, state and image nodes and rolls it into
 *  an object that can actually encode work to a MTLCommandBuffer -- the graph object will traverse the
 *  graph from back to front and determine which image nodes are not produced by filters in the graph.
 *  These, it will inteprety to be graph input images.  There may be input states too. When it does so, 
 *  it will represent these image and state nodes as the handles you attach to them. Therefore, the handles
 *  probably should be objects of your own making that refer back to your own data structures that identify
 *  various images that you know about. 
 *
 *  Continuing on to the neuron filter, which we are using to just take the usual image [0,1] range and stretch
 *  to [-1,1] before the rest of the graph sees it, we see we can pass in the linear filter parameters when constructing
 *  it here. All filter nodes also produce a result image. This is used as the argument when constructing the
 *  convolution filter node next, to show that the product of the neuron filter is the input to the convolution
 *  filter.
 *
 *  The convolution object constructor also takes a weights object. The weights object is an object that you write
 *  that conforms to the MPSCNNConvolutionDataSource protocol. MPS does not provide an object that conforms
 *  to this protocol, though you can see some examples in sample code that use this interface.  The convolution
 *  data source object is designed to provide for deferred loading of convolution weights. Convolution weights
 *  can be large. In aggregate, the storage for all the weights in the MPSNNGraph, plus the storage for your
 *  copy of them might start to approach the storage limits of the machine for larger graphs. In order to lessen
 *  this impact, the convolution weights are unpacked for each convolution in turn and then purged from memory
 *  so that only the single MPSNNGraph copy remains.  This happens when the MPSCNNConvolutionDataSource load
 *  and purge methods are called. You should not load the weights until -load is called. (You probably should
 *  however verify that the file, if any, is there and is well formed in the object -init method.) When -purge 
 *  is called, you should release any bulky storage that the object owns and and make the object as light weight
 *  as is reasonable. The MPSCNNConvolutionDataSource.descriptor may include a neuron filter operation.
 *
 *  Other object types should be straightforward. 
 *
 *  @section  subsection_mpsnngraph_usage   MPSNNGraph usage
 *  Once the network of MPSNNFilterNodes, MPSNNImageNodes and MPSNNStateNodes is created, the next
 *  step is to identify the MPSNNImageNode that contains the result of your graph -- typically, this
 *  is the last one you made -- and make a MPSNNGraph with it:
 *  @code
 *      MPSNNGraph *graph = [[MPSNNGraph alloc] initWithDevice: mtlDevice
 *                                                 resultImage: resultImage];
 *  @endcode
 *  If graph creation fails, nil will be returned here. When it is constructed, the graph iterates over
 *  the network of nodes, starting at the result image and working backwards. Any MPSNNImageNodes and states 
 *  that are used that are not created by a MPSNNFilterNode are interpreted to be graph inputs. The
 *  identity of these are given by the MPSNNGraph.sourceImageHandles and MPSNNGraph.sourceStateHandles. 
 *  Each handle is your object that refers back to a particular image or state node. The order of the handles
 *  matches the order of the images or states that should be passed to the [MPSNNGraph encodeToCommandBuffer:...]
 *  call. Similarly, you can get the identity of any intermediate images that you requested to see (See
 *  MPSNNImageNode.exportFromGraph property) and the identity of any result MPSStates that are produced
 *  by the graph that are not used.   The graph has a destinationImageAllocator that overrides the 
 *  MPSNNImageNode.destinationImageAllocator. (see subsection MPSNNGraph intermediate image allocation)
 *  Typically, this serves to make a default temporary image into a normal image, as a convenience.
 *
 *  When you are ready to encode a graph to a command buffer, the operation follows as per much of the 
 *  rest of MPS. 
 *  @code
 *      id <MTLDevice> mtlDevice = MTLCreateSystemDefaultDevice();
 *      id <MTLCommandQueue> mtlCommandQueue.commandBuffer = mtlDevice.newCommandQueue;
 *      id <MTLCommandBuffer> cmdBuf = mtlCommandQueue.commandBuffer;
 *      MPSImage *inputImage = [[MPSImage alloc] initWithDevice: mtlDevice imageDescriptor: myDescriptor];
 *      // put some data into the input image here. See MTLTexture.replaceBytes...
 *      MPSImage * result = [myGraph encodeToCommandBuffer: cmdBuf sourceImages: @[inputImage] ];
 *      [cmdBuf addCompletedHandler: ^(id <MTLCommandBuffer> buf){
 *            // Notify your app that the work is done and the values in result
 *            // are ready for inspection.
 *       }];
 *      [cmdBuf commit];
 *
 *      // While we are working on that, encode something else
 *      id <MTLCommandBuffer> cmdBuf2 = mtlCommandQueue.commandBuffer;
 *      MPSImage * result2 = [myGraph encodeToCommandBuffer: cmdBuf2 sourceImages: @[inputImage2] ];
 *      [cmdBuf2 addCompletedHandler: ^(id <MTLCommandBuffer> buf){
 *            // Notify your app that the work is done and the values in result2
 *            // are ready for inspection.
 *       }];
 *      [cmdBuf2 commit];
 *      ...
 *  @endcode
 *  The extra synchronization from [id <MTLCommandBuffer> waitForCompletion] should be avoided. It can
 *  be exceptionally costly because the wait for new work to appear allows the GPU clock to spin down.
 *  Factor of two or more performance increases are common with -addCompletedHandler:.
 *
 *  @section  subsection_mpsnngraph_sizing   MPSNNGraph intermediate image sizing and centering
 *  The MPSNNGraph will automatically size and center the intermediate images that appear in the graph.
 *  However, different neural network frameworks do so differently. In addition, some filters may 
 *  at times operate on only valid pixels in the source image, whereas others may "look beyond the
 *  edges" so as to keep the result image size the same as the input. Occasionally some filters will
 *  want to produce results for which any input is valid. Perhaps some want to behave in between. Torch
 *  has some particularly inventive edging policies for pooling that have valid invalid regions and 
 *  invalid invalid regions beyond the edges of the image.
 *
 *  Whatever the behavior, you will use the MPSNNFilter.paddingPolicy property to configure behavior.
 *  In its simplest form, a paddingPolicy is a object (possibly written by you, though MPS provides some)
 *  that conforms to the MPSNNPadding protocol. It should at minimum provide a padding method, which codes
 *  for common methods to size the result image, how to center it on the input image and where to place
 *  the remainder in cases where the image size isn't exactly divisible by the stride. This is a bitfield.
 *  You can use:
 *  @code
 *      [MPSNNDefaultPadding paddingWithMethod: MPSNNPaddingMethodAlign... | MPSNNPaddingMethodAddRemainderTo...
 *                                              MPSNNPaddingMethodSize... ];
 *  @endcode
 *  To quickly configure one of these. The filters also have a default padding policy, which may be
 *  appropriate most of the time.  
 *
 *  Occasionally, something fancy needs to be done. In that case, the padding policy should set the 
 *  MPSNNPaddingMethodCustom bit and implement the optional destinationImageDescriptorForSourceImages:
 *  sourceStates:forKernel:suggestedDescriptor: method. The MPSNNGraph will use the MPSNNPadding.paddingMethod
 *  to generate an initial guess for the configuration of the MPSCNNKernel.offset and the size and formatting
 *  of the result image and hand that to you in the form of a MPSImageDescriptor. You can modify the descriptor
 *  or the kernel (also passed to you) in your custom destinationImageDescriptorForSourceImages:sourceStates:
 *  forKernel:suggestedDescriptor: method, or just ignore it and make a new descriptor.
 *
 *  @section  subsection_mpsnngraph_image_allocation   MPSNNGraph intermediate image allocation
 *  Typically the graph will make MPSTemporaryImages for these, based on the MPSImageDescriptor obtained
 *  from the padding policy. Temporary images alias one another and can be used to save a lot of memory,
 *  in the same way that malloc saves memory in your application by allowing you to reserve memory for 
 *  a time, use it, then free it for reuse for something else. Ideally, most of the storage in your graph
 *  should be temporary images.
 *
 *  Because temporary images don't (shouldn't) last long, and can't be read by the CPU, some images
 *  probably can't be temporary. By default, the final image returned from the graph is not temporary.
 *  (See MPSNNGraph.destinationImageAllocator to adjust).  Also, you may request that certain intermediate
 *  images be non-temporary so that you can access their contents from outside the graph using the
 *  MPSNNImageNode.exportFromGraph property. 
 *
 *  Temporary images often take up almost no additional memory. Regular images always do.  Some large graphs will only
 *  be able to run using temporary memory, as regular images would overwhelm the machine. Even if you allocate
 *  all your images up front and reuse them over and over, you will still very likely use much more memory with
 *  regular images, than if you just allocate temporary images as needed. Because temporary images do not
 *  generally allocate large amounts of storage, they are much cheaper and faster to use.
 *
 *  What kind of image is created after each filter node can be adjusted using the MPSNNImageNode.imageAllocator 
 *  property.  Two standard allocators are provided as MPSImage.defaultAllocator and MPSTemporaryImage.defaultAllocator.
 *  You may of course write your own. This might be necessary for example if you wish to maintain your own 
 *  MTLHeap and allocate from it.
 *
 *  @section  subsection_mpsnngraph_debugging   MPSNNGraph debugging tips
 *  In typical usage, some refinement, especially of padding policies, may be required to get the expected answer
 *  from MPS. If the result image is the wrong size, padding is typically the problem. When the answers are incorrect,
 *  the MPSCNNKernel.offset or other property may be incorrectly configured at some stage.  As the graph is generated 
 *  starting from an output image node, you may create other graphs starting at any image node within the graph. 
 *  This will give you a view into the result produced from each intermediate layer with a minimum of fuss.  In 
 *  addition, the usual NSObject -debugDescription method is available to inspect objects to make sure they conform 
 *  to expectation.
 *
 *  Note that certain operations such as neuron filters that follow convolution filters and image concatenation
 *  may be optimized away by the MPSNNGraph when it is constructed. The convolution can do neuron operations as
 *  part of its operation.  Concatenation is best done by writing the result of earlier filter passes in the right
 *  place using MPSCNNKernel.destinationFeatureChannelOffset rather than by adding an extra copy. Other optimizations 
 *  may be added as framework capabilities improve.
 *
 *  @section  section_samplecode   Sample Image Processing Example
 *      @code
 *       #import <MetalPerformanceShaders/MetalPerformanceShaders.h>
 *
 *       // Blur the input texture (in place if possible) on MTLCommandQueue q, and return the new texture.
 *       // This is a trivial example. It is not necessary or necessarily advised to enqueue a MPSKernel on
 *       // its own MTLCommandBuffer  or using its own MTLComputeCommandEncoder. Group work together.
 *       //
 *       // Here we assume that you have already gotten a MTLDevice using MTLCreateSystemDefaultDevice() or
 *       // MTLCopyAllDevices(), used it to create a MTLCommandQueue with MTLDevice.newCommandQueue, and 
 *       // similarly made textures with the device as needed.
 *       void  MyBlurTextureInPlace( id <MTLTexture> __strong *inTexture, float blurRadius, id <MTLCommandQueue> q)
 *       {
 *          // Create "the usual Metal objects".
 *          // MPS does not need a dedicated MTLCommandBuffer or MTLComputeCommandEncoder. 
 *          // This is a trivial example. You should reuse the MTL objects you already have, if you have them.
 *          id <MTLDevice> device = q.device;
 *          id <MTLCommandBuffer> buffer = [q commandBuffer];
 *
 *          // Create a MPS filter.
 *          MPSImageGaussianBlur *blur = [[MPSImageGaussianBlur alloc] initWithDevice: device];
 *          if( nil == blur )
 *              MyHandleError(kOutOfMemory);
 *
 *          // Set all MPSKernel properties to taste.
 *          blur.sigma = blurRadius;
 *          // defaults are okay here for other MPSKernel properties. (clipRect, origin, edgeMode)
 *
 *          // Attempt to do the work in place.  Since we provided a copyAllocator as an out-of-place
 *          // fallback, we don't need to check to see if it succeeded or not.
 *          [ blur encodeToCommandBuffer: commandBuffer
 *                        inPlaceTexture: inTexture         // may replace *inTexture
 *                         copyAllocator: myAllocator ];    // See MPSCopyAllocator definition for a sample myAllocator
 *          [ blur release];
 *
 *          // the usual metal enqueue process
 *          [buffer waitUntilCompleted];    // slow!  Try enqueing more work on this or the next 
 *                                          // command buffer instead of waiting every time.
 *
 *          return result;
 *      }
 *
 *      @endcode
 *
 *  @section section_tuning     MPS Tuning Hints
 *  MPS has been tuned for excellent performance across a diversity of devices
 *  and filter parameters. The tuning process focuses on minimizing both CPU and GPU
 *  latency for back to back calls on the same MTLCommmandBuffer.  It is possible,
 *  however, to inadvertently undo this optimization effort by introducing costly 
 *  operations into the pipeline around the MPS filter, leading to
 *  disappointing overall results.
 *
 *  Here are some elements of good practice to avoid common pitfalls:
 *
 *  -#  Don't wait for results to complete before enqueuing more work.
 *  There can be a significant delay (up to 2.5 ms) just to get
 *  an empty MTLCommandBuffer through the pipeline to where
 *  [MTLCommandBuffer  waitUntilCompleted] returns. Instead,
 *  start encoding the next command buffer(s) while you wait
 *  for the first one to complete. Enqueue them too, so they can
 *  start immediately after the previous one exits the GPU. Don't
 *  wait for the CPU kernel to notice the first command buffer
 *  is done and start taking it apart and eventually make a callback
 *  to userland before beginning work on encoding the next one.
 *  By allowing the CPU and GPU to work concurrently in this way,
 *  throughput can be enhanced by up to a factor of ten.
 *
 *  -#  There is a large cost to allocating buffers and textures.
 *  The cost can swamp the CPU, preventing you from keeping
 *  the GPU busy. Try to preallocate and reuse MTLResource
 *  objects as much as possible. The MPSTemporaryImage may be
 *  used instead for short-lived dynamic allocations.
 *
 *  -#  There is a cost to switching between render and compute
 *  encoders. Each time a new render encoder is used, there
 *  can be a substantial GPU mode switch cost that may
 *  undermine your throughput. To avoid the cost, try to
 *  batch compute work together. Since making a new MTLCommandBuffer
 *  forces you to make a new MTLCommandEncoder too, try to
 *  do more work with fewer MTLCommandBuffers.
 *
 *  -#  On currently available iOS devices we find that for some 
 *  image operations, particularly those involving multiple passes -
 *  for example, if you are chaining multiple MPS image filters
 *  together — performance can be improved by up a factor of two 
 *  by breaking the work into tiles about 512 kB in size. Use
 *  -sourceRegionForDestinationSize: to find the MPSRegion needed
 *  for each tile. 
 */

#ifdef __cplusplus
}
#endif

