/*!
 *  @header Morphology.h
 *  vImage_Framework
 *
 *  See vImage/vImage.h for more on how to view the headerdoc documentation for functions declared herein.
 *
 *  @copyright Copyright (c) 2002-2016 by Apple Inc. All rights reserved.
 *
 *  @discussion Morphology functions modify the shape of dark and light elements in an image.  They can enlarge
 *              light structural elements (Dilate) or make them smaller by making the darker regions larger (Erode).
 *              The filters can be used in combination fill in holes (Dilate then Erode) or remove fine structure
 *              (Erode then Dilate).  The Erode and Dilate filters can themselves have structure. For example, you
 *              can Dilate in the shape of a star, in which case single pixel bright signal (such as stars in a night 
 *              sky) assume a star shape.  Larger structure elements assume something of a star-like shape, but generally will
 *              not become fully recognizable as such until the size of the filter exceeds the size of the image
 *              structure element. A small circular filter can turn a rectangle into a larger rectangle with round corners.
 *              Many other examples abound.
 *
 *              Min is a special case for an Erode function with a rectangular kernel that contains all the same value.
 *              Max is a special case for a Dilate function with a rectangular kernel that contains all the same value.
 *              Min and Max make use of a faster algorithm that can operate at much reduced cost.
 *
 *  @ignorefuncmacro VIMAGE_NON_NULL
 */

#ifndef VIMAGE_MORPHOLOGY_H
#define VIMAGE_MORPHOLOGY_H

#include <vImage/vImage_Types.h>


#ifdef __cplusplus
extern "C" {
#endif

    
/*!
 *  @functiongroup Dilate
 *  @discussion  A dilate filter uses a shaped probe to trace a 3D surface. Imagine the kernel to define a 2D surface with
 *               the third dimension the values in the kernel.  This is then lowered down over the image, itself treated
 *               as a 3D surface. The result image is the height at which the surface makes contact with the image for 
 *               each pixel in the image. In this respect it operates like a scanning electron microscope with an adjustable
 *               probe shape. In code:
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      int r = 0;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              r = MAX( r, src[i+y-kernel_height/2][j+x-kernel_width/2] - k[y*kernel_width+x] )
 *                          }
 *                      }
 *
 *                      // normalize for kernel center not 0
 *                      r += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *
 *                      // saturate overflow to representable range
 *                      result[i][j] = CLIP( r );
 *                  }
 *               @/textblock </pre>
 *               The ARGB variants apply the filter to the four channels in parallel. It should be noted that the application
 *               of the filter to the image causes the structure elements in the filter to be reflected into the image, reversed 
 *               top to bottom and left to right. Also, if the center of the kernel is not 0, a general lightening of the image
 *               will occur. Some functions will run much faster if the center of the kernel is 0.
 */

/*!
 *  @function vImageDilate_Planar8
 *  @abstract Apply a dilate filter to a Planar8 image
 *  @discussion  This is a general purpose dilate filter for Planar8 data. It is optimized to handle the special cases that occur
 *               in image masks -- large contiguous regions of all 0xff or 0x0. If your filter is all 0's, you should use vImageMax_Planar8
 *               instead. 
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      int r = 0;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              r = MAX( r, src[i+y-kernel_height/2][j+x-kernel_width/2] - k[y*kernel_width+x] )
 *                          }
 *                      }
 *
 *                      // normalize for kernel center not 0
 *                      r += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *
 *                      // saturate overflow to representable range
 *                      result[i][j] = CLIP( r );
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the dilate filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image. 
 *
 *                Does not work in place.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the dilate filter.
 *                              It allows the dilate filter to operate in a tiled fashion for tiles that do not start on the 
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the dilate filter.
 *                              It allows the dilate filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel               A pointer to a array of filter values of dimension kernel_height x kernel_width.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                  0                           If kvImageGetTempBufferSize was among the flags, then no work was done.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageDilate_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const unsigned char *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,5) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


    
/*!
 *  @function vImageDilate_PlanarF
 *  @abstract Apply a dilate filter to a PlanarF image
 *  @discussion  This is a general purpose dilate filter for Planar8 data. If your filter is all 0's, you should use vImageMax_PlanarF
 *               instead.
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      float r = -INFINITY;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              r = MAX( r, src[i+y-kernel_height/2][j+x-kernel_width/2] - k[y*kernel_width+x] )
 *                          }
 *                      }
 *
 *                      // normalize for kernel center not 0
 *                      r += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *
 *                      // saturate overflow to representable range
 *                      result[i][j] = r;
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the dilate filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                Does not work in place. Floating-point values have host endianness.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the dilate filter.
 *                              It allows the dilate filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the dilate filter.
 *                              It allows the dilate filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel               A pointer to a array of filter values of dimension kernel_height x kernel_width.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                  0                           If kvImageGetTempBufferSize was among the flags, then no work was done.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageDilate_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,5) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImageDilate_ARGB8888
 *  @abstract Apply a dilate filter to a ARGB8888 image
 *  @discussion  This is a general purpose dilate filter for ARGB8888 data. If your filter is all 0's, you should use vImageMax_ARGB8888
 *               instead.
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      int a = 0;
 *                      int r = 0;
 *                      int g = 0;
 *                      int b = 0;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              a = MAX( a, src[i+y-kernel_height/2][j+x-kernel_width/2][0] - k[y*kernel_width+x] )
 *                              r = MAX( r, src[i+y-kernel_height/2][j+x-kernel_width/2][1] - k[y*kernel_width+x] )
 *                              g = MAX( g, src[i+y-kernel_height/2][j+x-kernel_width/2][2] - k[y*kernel_width+x] )
 *                              b = MAX( b, src[i+y-kernel_height/2][j+x-kernel_width/2][3] - k[y*kernel_width+x] )
 *                          }
 *                      }
 *
 *                      // normalize for kernel center not 0
 *                      a += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      r += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      g += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      b += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *
 *                      // saturate overflow to representable range
 *                      result[i][j][0] = (flags & kvImageLeaveAlphaUnchanged) ? src[i][j] : CLIP( a );
 *                      result[i][j][1] = CLIP( r );
 *                      result[i][j][2] = CLIP( g );
 *                      result[i][j][3] = CLIP( b );
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the dilate filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                Does not work in place. If kvImageLeaveAlphaUnchanged is not used, it works for any channel order.
 *                If kvImageLeaveAlphaUnchanged is used, then the alpha must be first. 
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the dilate filter.
 *                              It allows the dilate filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the dilate filter.
 *                              It allows the dilate filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel               A pointer to a array of filter values of dimension kernel_height x kernel_width.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *
 *             kvImageLeaveAlphaUnchanged   The alpha channel (first byte of pixel in memory) is copied to the destination
 *                                          without modification, instead of having a dilate filter applied to it.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                  0                           If kvImageGetTempBufferSize was among the flags, then no work was done.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageDilate_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const unsigned char *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,5) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImageDilate_ARGBFFFF
 *  @abstract Apply a dilate filter to a ARGBFFFF image
 *  @discussion  This is a general purpose dilate filter for ARGBFFFF data. If your filter is all 0's, you should use vImageMax_ARGBFFFF
 *               instead.
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      float a = -INFINITY;
 *                      float r = -INFINITY;
 *                      float g = -INFINITY;
 *                      float b = -INFINITY;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              a = MAX( a, src[i+y-kernel_height/2][j+x-kernel_width/2][0] - k[y*kernel_width+x] )
 *                              r = MAX( r, src[i+y-kernel_height/2][j+x-kernel_width/2][1] - k[y*kernel_width+x] )
 *                              g = MAX( g, src[i+y-kernel_height/2][j+x-kernel_width/2][2] - k[y*kernel_width+x] )
 *                              b = MAX( b, src[i+y-kernel_height/2][j+x-kernel_width/2][3] - k[y*kernel_width+x] )
 *                          }
 *                      }
 *
 *                      // normalize for kernel center not 0
 *                      a += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      r += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      g += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      b += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *
 *                      // saturate overflow to representable range
 *                      result[i][j][0] = (flags & kvImageLeaveAlphaUnchanged) ? src[i][j] : a;
 *                      result[i][j][1] = r;
 *                      result[i][j][2] = g;
 *                      result[i][j][3] = b;
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the dilate filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                Does not work in place.  If kvImageLeaveAlphaUnchanged is not used, it works for any channel order.
 *                If kvImageLeaveAlphaUnchanged is used, then the alpha must be first. Floating-point values have host
 *                endianness.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the dilate filter.
 *                              It allows the dilate filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the dilate filter.
 *                              It allows the dilate filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel               A pointer to a array of filter values of dimension kernel_height x kernel_width.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *
 *             kvImageLeaveAlphaUnchanged   The alpha channel (first float in pixel in memory) is copied to the destination
 *                                          without modification, instead of having a dilate filter applied to it.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                  0                           If kvImageGetTempBufferSize was among the flags, then no work was done.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageDilate_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,5) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

    
/*!
 *  @functiongroup Erode
 *  @discussion  An erode filter uses a shaped probe to trace a 3D surface. Imagine the kernel to define a 2D surface with
 *               the third dimension the values in the kernel.  This is then elevated from underneath the image, itself treated
 *               as a 3D surface. The result image is the height at which the surface makes contact with the image for
 *               each pixel in the image. 
 *
 *               In code:
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      int r = MAX_CHANNEL_VALUE;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              r = MIN( r, src[i+y-kernel_height/2][j+x-kernel_width/2] - k[y*kernel_width+x] )
 *                          }
 *                      }
 *
 *                      // normalize for kernel center not 0
 *                      r += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *
 *                      // saturate overflow to representable range
 *                      result[i][j] = CLIP( r );
 *                  }
 *               @/textblock </pre>
 *               The ARGB variants apply the filter to the four channels in parallel. It should be noted that the application
 *               of the filter to the image causes the structure elements in the filter to be reflected into the image, reversed
 *               top to bottom and left to right. Also, if the center of the kernel is not 0, a general lightening of the image
 *               will occur. Some functions will run much faster if the center of the kernel is 0.
 */


/*!
 *  @function vImageErode_Planar8
 *  @abstract Apply a erode filter to a Planar8 image
 *  @discussion  This is a general purpose erode filter for Planar8 data. If your filter is all 0's, you should use vImageMin_Planar8
 *               instead.
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      int r = MAX_CHANNEL_VALUE;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              r = MIN( r, src[i+y-kernel_height/2][j+x-kernel_width/2] - k[y*kernel_width+x] )
 *                          }
 *                      }
 *
 *                      // normalize for kernel center not 0
 *                      r += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *
 *                      // saturate overflow to representable range
 *                      result[i][j] = CLIP( r );
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the erode filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                Does not work in place.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the erode filter.
 *                              It allows the erode filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the erode filter.
 *                              It allows the erode filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel               A pointer to a array of filter values of dimension kernel_height x kernel_width.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                  0                           If kvImageGetTempBufferSize was among the flags, then no work was done.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageErode_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const unsigned char *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,5) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImageErode_PlanarF
 *  @abstract Apply a erode filter to a PlanarF image
 *  @discussion  This is a general purpose erode filter for Planar8 data. If your filter is all 0's, you should use vImageMin_PlanarF
 *               instead.
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      float r = INFINITY;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              r = MIN( r, src[i+y-kernel_height/2][j+x-kernel_width/2] - k[y*kernel_width+x] )
 *                          }
 *                      }
 *
 *                      // normalize for kernel center not 0
 *                      r += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *
 *                      // saturate overflow to representable range
 *                      result[i][j] = r;
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the erode filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                Does not work in place. Floating-point values have host endianness.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the erode filter.
 *                              It allows the erode filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the erode filter.
 *                              It allows the erode filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel               A pointer to a array of filter values of dimension kernel_height x kernel_width.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                  0                           If kvImageGetTempBufferSize was among the flags, then no work was done.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageErode_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,5) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

    
/*!
 *  @function vImageErode_ARGB8888
 *  @abstract Apply a erode filter to a ARGB8888 image
 *  @discussion  This is a general purpose erode filter for ARGB8888 data. If your filter is all 0's, you should use vImageMin_ARGB8888
 *               instead.
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      int a = 255;
 *                      int r = 255;
 *                      int g = 255;
 *                      int b = 255;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              a = MIN( a, src[i+y-kernel_height/2][j+x-kernel_width/2][0] - k[y*kernel_width+x] )
 *                              r = MIN( r, src[i+y-kernel_height/2][j+x-kernel_width/2][1] - k[y*kernel_width+x] )
 *                              g = MIN( g, src[i+y-kernel_height/2][j+x-kernel_width/2][2] - k[y*kernel_width+x] )
 *                              b = MIN( b, src[i+y-kernel_height/2][j+x-kernel_width/2][3] - k[y*kernel_width+x] )
 *                          }
 *                      }
 *
 *                      // normalize for kernel center not 0
 *                      a += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      r += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      g += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      b += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *
 *                      // saturate overflow to representable range
 *                      result[i][j][0] = (flags & kvImageLeaveAlphaUnchanged) ? src[i][j] : CLIP( a );
 *                      result[i][j][1] = CLIP( r );
 *                      result[i][j][2] = CLIP( g );
 *                      result[i][j][3] = CLIP( b );
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the erode filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                Does not work in place. If kvImageLeaveAlphaUnchanged is not used, it works for any channel order.
 *                If kvImageLeaveAlphaUnchanged is used, then the alpha must be first.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the erode filter.
 *                              It allows the erode filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the erode filter.
 *                              It allows the erode filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel               A pointer to a array of filter values of dimension kernel_height x kernel_width.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *
 *             kvImageLeaveAlphaUnchanged   The alpha channel (first byte of pixel in memory) is copied to the destination
 *                                          without modification, instead of having a erode filter applied to it.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                  0                           If kvImageGetTempBufferSize was among the flags, then no work was done.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageErode_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const unsigned char *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,5) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

    
/*!
 *  @function vImageErode_ARGBFFFF
 *  @abstract Apply a erode filter to a ARGBFFFF image
 *  @discussion  This is a general purpose erode filter for ARGBFFFF data. If your filter is all 0's, you should use vImageMin_ARGBFFFF
 *               instead.
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      float a = INFINITY;
 *                      float r = INFINITY;
 *                      float g = INFINITY;
 *                      float b = INFINITY;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              a = MIN( a, src[i+y-kernel_height/2][j+x-kernel_width/2][0] - k[y*kernel_width+x] )
 *                              r = MIN( r, src[i+y-kernel_height/2][j+x-kernel_width/2][1] - k[y*kernel_width+x] )
 *                              g = MIN( g, src[i+y-kernel_height/2][j+x-kernel_width/2][2] - k[y*kernel_width+x] )
 *                              b = MIN( b, src[i+y-kernel_height/2][j+x-kernel_width/2][3] - k[y*kernel_width+x] )
 *                          }
 *                      }
 *
 *                      // normalize for kernel center not 0
 *                      a += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      r += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      g += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *                      b += k[y * (kernel_height/2) * kernel_width + kernel_width/2 ];
 *
 *                      // saturate overflow to representable range
 *                      result[i][j][0] = (flags & kvImageLeaveAlphaUnchanged) ? src[i][j] : a;
 *                      result[i][j][1] = r;
 *                      result[i][j][2] = g;
 *                      result[i][j][3] = b;
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the erode filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                Does not work in place.  If kvImageLeaveAlphaUnchanged is not used, it works for any channel order.
 *                If kvImageLeaveAlphaUnchanged is used, then the alpha must be first. Floating-point values have host
 *                endianness.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the erode filter.
 *                              It allows the erode filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the erode filter.
 *                              It allows the erode filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel               A pointer to a array of filter values of dimension kernel_height x kernel_width.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *
 *             kvImageLeaveAlphaUnchanged   The alpha channel (first float in pixel in memory) is copied to the destination
 *                                          without modification, instead of having a erode filter applied to it.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                  0                           If kvImageGetTempBufferSize was among the flags, then no work was done.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageErode_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,5) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

    
/*!
 *  @functiongroup Max
 *  @discussion     A max filter is a special case of a dilate filter, in which the filter elements are all 0. 
 *                  This allows a much, much faster algorithm to be used.
 */
    
/*!
 *  @function   vImageMax_Planar8
 *  @abstract   Apply a max filter to a Planar8 image.
 *  @discussion A max filter is a special case dilate filter, in which the filter elements are all 0. It is much faster than the normal dilate.
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      int r = 0;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              r = MAX( r, src[i+y-kernel_height/2][j+x-kernel_width/2] )
 *                          }
 *                      }
 *
 *                      // saturate overflow to representable range
 *                      result[i][j] = r;
 *                  }
 *               @/textblock </pre>
 *                If only part of the max filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                Does not work in place, unless the kvImageDoNotTile flag is used.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param tempBuffer           May be NULL. An optional temp buffer in which to store temporary computation. To find the size
 *                              of the temp buffer, call the function with the desired parameters and pass the kvImageGetTempBufferSize
 *                              flag. The size of the temp buffer will be returned from the left hand side of the function in
 *                              place of an error code, and no work will be done on the image data. A temp buffer can provide a speed 
 *                              improvement, if it can be allocated once and reused. This saves a bunch of VM faults on first use of 
 *                              the newly allocated temp buffer.
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the max filter.
 *                              It allows the max filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the max filter.
 *                              It allows the max filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread. It also
 *                                          allows the function to work in place, though more slowly.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                 >=0                          If kvImageGetTempBufferSize was among the flags, then no work was done.
 *                                              Instead, the size of the temp buffer needed is returned.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageMax_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function   vImageMax_PlanarF
 *  @abstract   Apply a max filter to a PlanarF image.
 *  @discussion A max filter is a special case dilate filter, in which the filter elements are all 0. It is much faster than the normal dilate.
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      float r = -INFINITY;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              r = MAX( r, src[i+y-kernel_height/2][j+x-kernel_width/2] )
 *                          }
 *                      }
 *
 *                      // saturate overflow to representable range
 *                      result[i][j] = r;
 *                  }
 *               @/textblock </pre>
 *                If only part of the max filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                Does not work in place, unless the kvImageDoNotTile flag is used.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param tempBuffer           May be NULL. An optional temp buffer in which to store temporary computation. To find the size 
 *                              of the temp buffer, call the function with the desired parameters and pass the kvImageGetTempBufferSize
 *                              flag. The size of the temp buffer will be returned from the left hand side of the function in
 *                              place of an error code, and no work will be done on the image data. A temp buffer can provide a speed
 *                              improvement, if it can be allocated once and reused. This saves a bunch of VM faults on first use of
 *                              the newly allocated temp buffer.
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the max filter.
 *                              It allows the max filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the max filter.
 *                              It allows the max filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread. It also
 *                                          allows the function to work in place, though more slowly.
 *
 *             kvImageGetTempBufferSize     Return the size of the temp buffer needed.  Do no work.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                 >=0                          If kvImageGetTempBufferSize was among the flags, then no work was done.
 *                                              Instead, the size of the temp buffer needed is returned.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageMax_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImageMax_ARGB8888
 *  @abstract Apply a max filter to a ARGB8888 image
 *  @discussion  This is a special purpose dilate filter for ARGB8888 data, for rectangular kernels with value 0. It is much faster than the normal dilate.
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      int a = 0;
 *                      int r = 0;
 *                      int g = 0;
 *                      int b = 0;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              a = MAX( a, src[i+y-kernel_height/2][j+x-kernel_width/2][0] )
 *                              r = MAX( r, src[i+y-kernel_height/2][j+x-kernel_width/2][1] )
 *                              g = MAX( g, src[i+y-kernel_height/2][j+x-kernel_width/2][2] )
 *                              b = MAX( b, src[i+y-kernel_height/2][j+x-kernel_width/2][3] )
 *                          }
 *                      }
 *
 *                      // saturate overflow to representable range
 *                      result[i][j][0] = (flags & kvImageLeaveAlphaUnchanged) ? src[i][j] : a;
 *                      result[i][j][1] = r;
 *                      result[i][j][2] = g;
 *                      result[i][j][3] = b;
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the max filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                If kvImageLeaveAlphaUnchanged is not used, it works for any channel order.
 *                If kvImageLeaveAlphaUnchanged is used, then the alpha must be first.
 *                Does not work in place, unless the kvImageDoNotTile flag is used, in which case it will probably 
 *                run more slowly.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param tempBuffer           May be NULL. An optional temp buffer in which to store temporary computation. To find the size
 *                              of the temp buffer, call the function with the desired parameters and pass the kvImageGetTempBufferSize
 *                              flag. The size of the temp buffer will be returned from the left hand side of the function in
 *                              place of an error code, and no work will be done on the image data. A temp buffer can provide a speed
 *                              improvement, if it can be allocated once and reused. This saves a bunch of VM faults on first use of
 *                              the newly allocated temp buffer.
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the max filter.
 *                              It allows the max filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the max filter.
 *                              It allows the max filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread. 
 *                                          kvImageDoNotTile will also allow the filter to run in place, though more slowly.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *
 *             kvImageLeaveAlphaUnchanged   The alpha channel (first byte of pixel in memory) is copied to the destination
 *                                          without modification, instead of having a max filter applied to it.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                 >=0                          If kvImageGetTempBufferSize was among the flags, then no work was done.
 *                                              Instead, the size of the temp buffer needed is returned.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageMax_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

    
/*!
 *  @function vImageMax_ARGBFFFF
 *  @abstract Apply a max filter to a ARGBFFFF image
 *  @discussion  This is a special purpose dilate filter for ARGBFFFF data, for rectangular kernels with value 0. It is much faster than the normal dilate.
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      float a = -INFINITY;
 *                      float r = -INFINITY;
 *                      float g = -INFINITY;
 *                      float b = -INFINITY;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              a = MAX( a, src[i+y-kernel_height/2][j+x-kernel_width/2][0] )
 *                              r = MAX( r, src[i+y-kernel_height/2][j+x-kernel_width/2][1] )
 *                              g = MAX( g, src[i+y-kernel_height/2][j+x-kernel_width/2][2] )
 *                              b = MAX( b, src[i+y-kernel_height/2][j+x-kernel_width/2][3] )
 *                          }
 *                      }
 *
 *                      // saturate overflow to representable range
 *                      result[i][j][0] = (flags & kvImageLeaveAlphaUnchanged) ? src[i][j] : a;
 *                      result[i][j][1] = r;
 *                      result[i][j][2] = g;
 *                      result[i][j][3] = b;
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the max filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                If kvImageLeaveAlphaUnchanged is not used, it works for any channel order.
 *                If kvImageLeaveAlphaUnchanged is used, then the alpha must be first.
 *                Does not work in place, unless the kvImageDoNotTile flag is used, in which case it will probably
 *                run more slowly.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param tempBuffer           May be NULL. An optional temp buffer in which to store temporary computation. To find the size
 *                              of the temp buffer, call the function with the desired parameters and pass the kvImageGetTempBufferSize
 *                              flag. The size of the temp buffer will be returned from the left hand side of the function in
 *                              place of an error code, and no work will be done on the image data. A temp buffer can provide a speed
 *                              improvement, if it can be allocated once and reused. This saves a bunch of VM faults on first use of
 *                              the newly allocated temp buffer.
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the max filter.
 *                              It allows the max filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the max filter.
 *                              It allows the max filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread.
 *                                          kvImageDoNotTile will also allow the filter to run in place, though more slowly.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *
 *             kvImageLeaveAlphaUnchanged   The alpha channel (first byte of pixel in memory) is copied to the destination
 *                                          without modification, instead of having a max filter applied to it.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                 >=0                          If kvImageGetTempBufferSize was among the flags, then no work was done.
 *                                              Instead, the size of the temp buffer needed is returned.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageMax_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @functiongroup Min
 *  @discussion     A min filter is a special case of an erode filter, in which the filter elements are all 0.
 *                  This allows a much, much faster algorithm to be used.
 */

/*!
 *  @function   vImageMin_Planar8
 *  @abstract   Apply a min filter to a Planar8 image.
 *  @discussion A min filter is a special case erode filter, in which the filter elements are all 0.  It is much faster than the normal erode.
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      int r = MAX_CHANNEL_VALUE;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              r = MIN( r, src[i+y-kernel_height/2][j+x-kernel_width/2] )
 *                          }
 *                      }
 *
 *                      // saturate overflow to representable range
 *                      result[i][j] = r;
 *                  }
 *               @/textblock </pre>
 *                If only part of the min filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                Does not work in place, unless the kvImageDoNotTile flag is used.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param tempBuffer           May be NULL. An optional temp buffer in which to store temporary computation. To find the size
 *                              of the temp buffer, call the function with the desired parameters and pass the kvImageGetTempBufferSize
 *                              flag. The size of the temp buffer will be returned from the left hand side of the function in
 *                              place of an error code, and no work will be done on the image data. A temp buffer can provide a speed
 *                              improvement, if it can be allocated once and reused. This saves a bunch of VM faults on first use of
 *                              the newly allocated temp buffer.
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the min filter.
 *                              It allows the min filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the min filter.
 *                              It allows the min filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread. It also
 *                                          allows the function to work in place, though more slowly.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                 >=0                          If kvImageGetTempBufferSize was among the flags, then no work was done.
 *                                              Instead, the size of the temp buffer needed is returned.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageMin_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function   vImageMin_PlanarF
 *  @abstract   Apply a min filter to a PlanarF image.
 *  @discussion A min filter is a special case erode filter, in which the filter elements are all 0. It is much faster than the normal erode.
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      float r = INFINITY;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              r = MIN( r, src[i+y-kernel_height/2][j+x-kernel_width/2] )
 *                          }
 *                      }
 *
 *                      // saturate overflow to representable range
 *                      result[i][j] = r;
 *                  }
 *               @/textblock </pre>
 *                If only part of the min filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                Does not work in place, unless the kvImageDoNotTile flag is used.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param tempBuffer           May be NULL. An optional temp buffer in which to store temporary computation. To find the size
 *                              of the temp buffer, call the function with the desired parameters and pass the kvImageGetTempBufferSize
 *                              flag. The size of the temp buffer will be returned from the left hand side of the function in
 *                              place of an error code, and no work will be done on the image data. A temp buffer can provide a speed
 *                              improvement, if it can be allocated once and reused. This saves a bunch of VM faults on first use of
 *                              the newly allocated temp buffer.
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the min filter.
 *                              It allows the min filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the min filter.
 *                              It allows the min filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread. It also
 *                                          allows the function to work in place, though more slowly.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                 >=0                          If kvImageGetTempBufferSize was among the flags, then no work was done.
 *                                              Instead, the size of the temp buffer needed is returned.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageMin_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImageMin_ARGB8888
 *  @abstract Apply a min filter to a ARGB8888 image
 *  @discussion  This is a special purpose erode filter for ARGB8888 data, for rectangular kernels with value 0. It is much faster than the normal erode.
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      int a = MAX_CHANNEL_VALUE;
 *                      int r = MAX_CHANNEL_VALUE;
 *                      int g = MAX_CHANNEL_VALUE;
 *                      int b = MAX_CHANNEL_VALUE;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              a = MIN( a, src[i+y-kernel_height/2][j+x-kernel_width/2][0] )
 *                              r = MIN( r, src[i+y-kernel_height/2][j+x-kernel_width/2][1] )
 *                              g = MIN( g, src[i+y-kernel_height/2][j+x-kernel_width/2][2] )
 *                              b = MIN( b, src[i+y-kernel_height/2][j+x-kernel_width/2][3] )
 *                          }
 *                      }
 *
 *                      // saturate overflow to representable range
 *                      result[i][j][0] = (flags & kvImageLeaveAlphaUnchanged) ? src[i][j] : a;
 *                      result[i][j][1] = r;
 *                      result[i][j][2] = g;
 *                      result[i][j][3] = b;
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the min filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                If kvImageLeaveAlphaUnchanged is not used, it works for any channel order.
 *                If kvImageLeaveAlphaUnchanged is used, then the alpha must be first.
 *                Does not work in place, unless the kvImageDoNotTile flag is used, in which case it will probably
 *                run more slowly.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param tempBuffer           May be NULL. An optional temp buffer in which to store temporary computation. To find the size
 *                              of the temp buffer, call the function with the desired parameters and pass the kvImageGetTempBufferSize
 *                              flag. The size of the temp buffer will be returned from the left hand side of the function in
 *                              place of an error code, and no work will be done on the image data. A temp buffer can provide a speed
 *                              improvement, if it can be allocated once and reused. This saves a bunch of VM faults on first use of
 *                              the newly allocated temp buffer.
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the min filter.
 *                              It allows the min filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the min filter.
 *                              It allows the min filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread.
 *                                          kvImageDoNotTile will also allow the filter to run in place, though more slowly.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *
 *             kvImageLeaveAlphaUnchanged   The alpha channel (first byte of pixel in memory) is copied to the destination
 *                                          without modification, instead of having a min filter applied to it.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                 >=0                          If kvImageGetTempBufferSize was among the flags, then no work was done.
 *                                              Instead, the size of the temp buffer needed is returned.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageMin_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

    
/*!
 *  @function vImageMin_ARGBFFFF
 *  @abstract Apply a min filter to a ARGBFFFF image
 *  @discussion  This is a special purpose erode filter for ARGBFFFF data, for rectangular kernels with value 0. It is much faster than the normal erode.
 *
 *               <pre> @textblock
 *                  for each pixel result[i][j] in the image{
 *                      float a = INFINITY;
 *                      float r = INFINITY;
 *                      float g = INFINITY;
 *                      float b = INFINITY;
 *                      for( y = 0; y < kernel_height; y++ ){
 *                          for( x = 0; x < kernel_width; x++ ){
 *                              a = MIN( a, src[i+y-kernel_height/2][j+x-kernel_width/2][0] )
 *                              r = MIN( r, src[i+y-kernel_height/2][j+x-kernel_width/2][1] )
 *                              g = MIN( g, src[i+y-kernel_height/2][j+x-kernel_width/2][2] )
 *                              b = MIN( b, src[i+y-kernel_height/2][j+x-kernel_width/2][3] )
 *                          }
 *                      }
 *
 *                      // saturate overflow to representable range
 *                      result[i][j][0] = (flags & kvImageLeaveAlphaUnchanged) ? src[i][j] : a;
 *                      result[i][j][1] = r;
 *                      result[i][j][2] = g;
 *                      result[i][j][3] = b;
 *                  }
 *               @/textblock </pre>
 *
 *                If only part of the min filter of the entire image is desired, use srcOffsetToROI_X/Y to set the positioning
 *                of the result tile relative to the src image.
 *
 *                If kvImageLeaveAlphaUnchanged is not used, it works for any channel order.
 *                If kvImageLeaveAlphaUnchanged is used, then the alpha must be first.
 *                Does not work in place, unless the kvImageDoNotTile flag is used, in which case it will probably
 *                run more slowly.
 *
 *  @param src                  The input image
 *  @param dest                 A preallocated buffer to contain the result image
 *  @param tempBuffer           May be NULL. An optional temp buffer in which to store temporary computation. To find the size
 *                              of the temp buffer, call the function with the desired parameters and pass the kvImageGetTempBufferSize
 *                              flag. The size of the temp buffer will be returned from the left hand side of the function in
 *                              place of an error code, and no work will be done on the image data. A temp buffer can provide a speed
 *                              improvement, if it can be allocated once and reused. This saves a bunch of VM faults on first use of
 *                              the newly allocated temp buffer.
 *  @param srcOffsetToROI_X     An offset added to the horizontal position in the src image when calculating the min filter.
 *                              It allows the min filter to operate in a tiled fashion for tiles that do not start on the
 *                              left edge of the source image.
 *  @param srcOffsetToROI_Y     An offset added to the vertical position in the src image when calculating the min filter.
 *                              It allows the min filter to operate in a tiled fashion for tiles that do not start on the
 *                              top edge of the source image.
 *  @param kernel_height        The height of the rectangular kernel. Must be an odd number.
 *  @param kernel_width         The width of the rectangular kernel. Must be an odd number.
 *  @param flags                The following flags values are allowed:
 *      <pre> @textblock
 *             kvImageNoFlags               Default operation
 *
 *             kvImageDoNotTile             Turn off internal multithreading. Useful if, for example, you are doing your own
 *                                          multithreading and just want the filter to run local to the current thread.
 *                                          kvImageDoNotTile will also allow the filter to run in place, though more slowly.
 *
 *             kvImageGetTempBufferSize     Return 0.  Do no work.
 *
 *             kvImageLeaveAlphaUnchanged   The alpha channel (first byte of pixel in memory) is copied to the destination
 *                                          without modification, instead of having a min filter applied to it.
 *      @/textblock </pre>
 *  @return The following error codes may result:
 *      <pre> @textblock
 *             kvImageNoError                   Success.
 *                 >=0                          If kvImageGetTempBufferSize was among the flags, then no work was done.
 *                                              Instead, the size of the temp buffer needed is returned.
 *
 *             kvImageRoiLargerThanInputBuffer  dest->width and dest->height must be less than or equal to the corresponding
 *                                              dimensions in the src image
 *
 *             kvImageInvalidKernelSize         The kernel_height and kernel_width must not be evenly divisible by 2.
 *      @/textblock </pre>
 */
vImage_Error vImageMin_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  vImagePixelCount kernel_height, vImagePixelCount kernel_width, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


#ifdef __cplusplus
}
#endif

#endif /* MORPHOLOGY_H */
