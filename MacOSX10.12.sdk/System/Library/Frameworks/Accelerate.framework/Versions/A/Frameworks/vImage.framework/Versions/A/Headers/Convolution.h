/*!
 *  @header Convolution.h
 *  vImage_Framework
 *
 *  See vImage/vImage.h for more on how to view the headerdoc documentation for functions declared herein.
 *
 *  @copyright Copyright (c) 2002-2016 by Apple Inc. All rights reserved.
 *
 *  @discussion Convolution is a weighted average between a pixel and its neighboring pixels. By smoothing
 *              out high frequency signal, convolution can be used to blur an image. By subtracting out the
 *              low frequency signal, it can be used to produce a sharpening effect. Convolution is also used
 *              with a variety of filters such as Laplace and Sobel to detect edges in the image. Here we also 
 *              provide a deconvolution filter that attempts to iteratively undo the effect of a convolution. 
 *              Where the convolution kernel can be accurately determined, it can be used to remove focus 
 *              problems, motion blur and distortion introduced by the lens.
 *
 *      <pre>@textblock
 *              =========================================================================
 *              ======    MOST VIMAGE CONVOLUTION FUNCTIONS DO NOT WORK IN PLACE    =====
 *              =========================================================================
 *      @/textblock </pre>
 *
 *              Since a weighted average of nearby pixels can for some positions extend off the edge of the
 *              input image, a variety of edging modes are provided which specify what happens in such
 *              cases:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually 
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0} 
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image. 
 *              
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels. 
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content. 
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel 
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *      @/textblock </pre>
 *              Only one edging mode may be active at a time.  Please see the Convolution section in
 *              the vImage Programming Guide for a better description of edging modes.
 *              (https://developer.apple.com/library/ios/documentation/Performance/Conceptual/vImage/vImage.pdf)
 *
 *
 *              When calling these interfaces from within the context of your own tiling engine,
 *              it may be necessary to produce a result tile starting from different points in the
 *              input image. Simply repackaging the input image by adjusting the height, width and
 *              src->data to achieve this affect will not work correctly because it introduces 
 *              artificial edges into the input image. (See discussion of edging modes above.)
 *              Instead, X and Y offset parameters are provided. Simply pass in the whole input image
 *              and use the X and Y offsets to adjust the position of the content used to produce
 *              the output image.  The size of the output tile is given by the dest->height and width.
 *
 *  @ignorefuncmacro VIMAGE_NON_NULL
 */


#ifndef VIMAGE_CONVOLUTION_H
#define VIMAGE_CONVOLUTION_H


#ifdef __cplusplus
extern "C" {
#endif

#include <vImage/vImage_Types.h>

/*!
 *  @functiongroup General Convolution
 *  @discussion A general convolve filter allows you to provide an arbitrary set of weights to use 
 *              in the weighted average between each pixel and its neighbors. As such, it is a 
 *              very flexible tool for achieving a variety of image effects, from blurring to sharpening
 *              to edge detection to sub-pixel image translation and motion blur.  
 *
 *              Some filters such as edge detection filters take the first derivative of the image 
 *              surface. Since a derivative can be either positive or negative  and some formats such
 *              as Planar8 (unorm8) can only represent positive numbers, the general convolution is also
 *              available in a form which allows you to provide a bias to add to the weighted sum before
 *              the divisor is applied, to shift the values into the positive.  You might provide a 
 *              bias of 128 * divisor to move the encoding for 0 to 128 so that negative numbers are
 *              representable, for example. (In this case, -20 would now be encoded as 128-20=108.)
 *
 *              Finally, vImage provides multikernel convolution, which allows a different kernel, bias
 *              and divisor to be used for each color channel. This might allow for the position of the
 *              different color channels to be shifted independently, or for alpha to be blurred differently
 *              from color.
 *      <pre>@textblock
 *              =========================================================================
 *              ======    MOST VIMAGE CONVOLUTION FUNCTIONS DO NOT WORK IN PLACE    =====
 *              =========================================================================
 *      @/textblock </pre>
 */

/*!
 *  @function vImageConvolve_Planar8
 *  @abstract General convolution on a Planar8 image.
 *  @discussion This filter applies a convolution filter of your choosing to a Planar8 image. 
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              int sum = 0;
 *              
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sum += kernel_element[i][j] * 
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2]
 *                               [x+j+srcOffsetToROI_X- kernel_width/2];
 *              }
 *              // Correct for the scaling introduced by multiplying by the weights table
 *              sum = (sum + divisor/2) / divisor;
 *
 *              // write out result
 *              result[y][x] = CLAMP(sum, 0, 255);
 *          }
 *      @/textblock </pre>
 *              (Above, we imagine the kernel to be a 2D array of size kernel_height by kernel_width.
 *              However, in practice it is passed in as a contiguous 1D array of size kernel_height *
 *              kernel_width.)
 *
 *              This filter does not work in place.
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const int16_t kernel[9] = { 1, 2, 1,
 *                                                      2, 4, 2,
 *                                                      1, 2, 1 };
 *                          @/textblock </pre>
 *
 *                          The kernel values may not sum in any combination to be outside the range
 *                          [-2**23, 2**23), or modulo overflow in the accumulator may result.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param divisor          The weighted sum of nearby pixels is typically a large number, which must be corrected
 *                          to fit back into the image format of the destination image. The correction factor 
 *                          is passed in as divisor here, and is divided from the sum before the result is 
 *                          returned. Typically, the divisor is the sum over the area of the kernel. If the divisor
 *                          is 0, 1 will be used instead.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the 
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of 
 *                                      the temp buffer to use with this function and this set of 
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided: 
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal 
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageConvolve_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const int16_t *kernel, uint32_t kernel_height, uint32_t kernel_width, int32_t divisor, Pixel_8 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );
    
/*!
 *  @function vImageConvolve_PlanarF
 *  @abstract General convolution on a PlanarF image.
 *  @discussion This filter applies a convolution filter of your choosing to a PlanarF image.
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              float sum = 0;
 *
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sum += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2]
 *                               [x+j+srcOffsetToROI_X- kernel_width/2];
 *              }
 *
 *              // write out result
 *              result[y][x] = sum;
 *          }
 *      @/textblock </pre>
 *              (Above, we imagine the kernel to be a 2D array of size kernel_height by kernel_width.
 *              However, in practice it is passed in as a contiguous 1D array of size kernel_height *
 *              kernel_width.)
 *
 *              This filter does not work in place.
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const float kernel[9] =   { 1./16, 2./16, 1./16,
 *                                                      2./16, 4./16, 2./16,
 *                                                      1./16, 2./16, 1./16 };
 *                          @/textblock </pre>
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageConvolve_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, uint32_t kernel_height, uint32_t kernel_width, Pixel_F backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

    
/*!
 *  @function vImageConvolve_ARGB8888
 *  @abstract General convolution on a ARGB888 image of any channel order.
 *  @discussion This filter applies a convolution filter of your choosing to a ARGB8888 image.
 *              This filter will work on any four-channel, 8-bit per component image format, not just ARGB.
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              int sumA = 0;
 *              int sumR = 0;
 *              int sumG = 0;
 *              int sumB = 0;
 *
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sumA += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][0];
 *                  sumR += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][1];
 *                  sumG += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][2];
 *                  sumB += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][3];
 *              }
 *              // Correct for the scaling introduced by multiplying by the weights table
 *              sumA = (sumA + divisor/2) / divisor;
 *              sumR = (sumR + divisor/2) / divisor;
 *              sumG = (sumG + divisor/2) / divisor;
 *              sumB = (sumB + divisor/2) / divisor;
 *
 *              // write out result
 *              result[y][x][0] = CLAMP(sumA, 0, 255);
 *              result[y][x][1] = CLAMP(sumR, 0, 255);
 *              result[y][x][2] = CLAMP(sumG, 0, 255);
 *              result[y][x][3] = CLAMP(sumB, 0, 255);
 *          }
 *      @/textblock </pre>
 *              (Above, we imagine the kernel to be a 2D array of size kernel_height by kernel_width.
 *              However, in practice it is passed in as a contiguous 1D array of size kernel_height *
 *              kernel_width.)
 *
 *              This filter does not work in place.
 *
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const int16_t kernel[9] = { 1, 2, 1,
 *                                                      2, 4, 2,
 *                                                      1, 2, 1 };
 *                          @/textblock </pre>
 *
 *                          The kernel values may not sum in any combination to be outside the range
 *                          [-2**23, 2**23), or modulo overflow in the accumulator may result.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param divisor          The weighted sum of nearby pixels is typically a large number, which must be corrected
 *                          to fit back into the image format of the destination image. The correction factor
 *                          is passed in as divisor here, and is divided from the sum before the result is
 *                          returned. Typically, the divisor is the sum over the area of the kernel. If the divisor
 *                          is 0, 1 will be used instead.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageConvolve_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const int16_t *kernel, uint32_t kernel_height, uint32_t kernel_width, int32_t divisor, const Pixel_8888 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 *  @function vImageConvolve_ARGBFFFF
 *  @abstract General convolution on a ARGBFFFF image of any channel order.
 *  @discussion This filter applies a convolution filter of your choosing to a ARGBFFFF image.
 *              This filter will work on any four-channel, float per component image format, not just ARGB.
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              float sumA = 0;
 *              float sumR = 0;
 *              float sumG = 0;
 *              float sumB = 0;
 *
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sumA += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][0];
 *                  sumR += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][1];
 *                  sumG += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][2];
 *                  sumB += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][3];
 *              }
 *
 *              // write out result
 *              result[y][x][0] = sumA;
 *              result[y][x][1] = sumR;
 *              result[y][x][2] = sumG;
 *              result[y][x][3] = sumB;
 *          }
 *      @/textblock </pre>
 *              (Above, we imagine the kernel to be a 2D array of size kernel_height by kernel_width.
 *              However, in practice it is passed in as a contiguous 1D array of size kernel_height *
 *              kernel_width.)
 *
 *              This filter does not work in place.
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const float kernel[9] =   { 1./16, 2./16, 1./16,
 *                                                      2./16, 4./16, 2./16,
 *                                                      1./16, 2./16, 1./16 };
 *                          @/textblock </pre>
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageConvolve_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, uint32_t kernel_height, uint32_t kernel_width, const Pixel_FFFF backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*!
 *  @function vImageConvolveWithBias_Planar8
 *  @abstract General convolution on a Planar8 image with added bias.
 *  @discussion This filter applies a convolution filter of your choosing to a Planar8 image.
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              int sum = 0;
 *
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sum += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2]
 *                               [x+j+srcOffsetToROI_X- kernel_width/2];
 *              }
 *              // Correct for the scaling introduced by multiplying by the weights table
 *              sum = (sum + bias) / divisor;
 *
 *              // write out result
 *              result[y][x] = CLAMP(sum, 0, 255);
 *          }
 *      @/textblock </pre>
 *              (Above, we imagine the kernel to be a 2D array of size kernel_height by kernel_width.
 *              However, in practice it is passed in as a contiguous 1D array of size kernel_height *
 *              kernel_width.)
 *
 *              This filter does not work in place.
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const int16_t kernel[9] = { 1, 2, 1,
 *                                                      2, 4, 2,
 *                                                      1, 2, 1 };
 *                          @/textblock </pre>
 *
 *                          The kernel values may not sum in any combination to be outside the range
 *                          [-2**23, 2**23), or modulo overflow in the accumulator may result.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param divisor          The weighted sum of nearby pixels is typically a large number, which must be corrected
 *                          to fit back into the image format of the destination image. The correction factor
 *                          is passed in as divisor here, and is divided from the sum before the result is
 *                          returned. Typically, the divisor is the sum over the area of the kernel. If the divisor
 *                          is 0, 1 will be used instead.
 *
 *  @param bias             This value is added to the sum of weighted pixels before the divisor is applied.
 *                          It can serve to both control rounding and adjust the brightness of the result.
 *                          A large bias (e.g 128 * divisor) may be required for some kernels to return
 *                          representable results, such as edge detection filters.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageConvolveWithBias_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const int16_t *kernel, uint32_t kernel_height, uint32_t kernel_width, int32_t divisor, int32_t bias, Pixel_8 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 *  @function vImageConvolveWithBias_PlanarF
 *  @abstract General convolution on a PlanarF image with added bias.
 *  @discussion This filter applies a convolution filter of your choosing to a PlanarF image.
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              float sum = bias;
 *
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sum += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2]
 *                               [x+j+srcOffsetToROI_X- kernel_width/2];
 *              }
 *
 *              // write out result
 *              result[y][x] = sum;
 *          }
 *      @/textblock </pre>
 *              (Above, we imagine the kernel to be a 2D array of size kernel_height by kernel_width.
 *              However, in practice it is passed in as a contiguous 1D array of size kernel_height *
 *              kernel_width.)
 *
 *              This filter does not work in place.
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const float kernel[9] =   { 1./16, 2./16, 1./16,
 *                                                      2./16, 4./16, 2./16,
 *                                                      1./16, 2./16, 1./16 };
 *                          @/textblock </pre>
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param bias             This value is added to the sum of weighted pixels.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageConvolveWithBias_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, uint32_t kernel_height, uint32_t kernel_width, float bias, Pixel_F backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );


/*!
 *  @function vImageConvolveWithBias_ARGB8888
 *  @abstract General convolution on a ARGB888 image of any channel order with bias.
 *  @discussion This filter applies a convolution filter of your choosing to a ARGB8888 image.
 *              This filter will work on any four-channel, 8-bit per component image format, not just ARGB.
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              int sumA = 0;
 *              int sumR = 0;
 *              int sumG = 0;
 *              int sumB = 0;
 *
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sumA += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][0];
 *                  sumR += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][1];
 *                  sumG += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][2];
 *                  sumB += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][3];
 *              }
 *              // Correct for the scaling introduced by multiplying by the weights table
 *              sumA = (sumA + bias[0]) / divisor;
 *              sumR = (sumR + bias[1]) / divisor;
 *              sumG = (sumG + bias[2]) / divisor;
 *              sumB = (sumB + bias[3]) / divisor;
 *
 *              // write out result
 *              result[y][x][0] = CLAMP(sumA, 0, 255);
 *              result[y][x][1] = CLAMP(sumR, 0, 255);
 *              result[y][x][2] = CLAMP(sumG, 0, 255);
 *              result[y][x][3] = CLAMP(sumB, 0, 255);
 *          }
 *      @/textblock </pre>
 *              (Above, we imagine the kernel to be a 2D array of size kernel_height by kernel_width.
 *              However, in practice it is passed in as a contiguous 1D array of size kernel_height *
 *              kernel_width.)
 *
 *              This filter does not work in place.
 *
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const int16_t kernel[9] = { 1, 2, 1,
 *                                                      2, 4, 2,
 *                                                      1, 2, 1 };
 *                          @/textblock </pre>
 *
 *                          The kernel values may not sum in any combination to be outside the range
 *                          [-2**23, 2**23), or modulo overflow in the accumulator may result.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param divisor          The weighted sum of nearby pixels is typically a large number, which must be corrected
 *                          to fit back into the image format of the destination image. The correction factor
 *                          is passed in as divisor here, and is divided from the sum before the result is
 *                          returned. Typically, the divisor is the sum over the area of the kernel. If the divisor
 *                          is 0, 1 will be used instead.
 *
 *  @param bias             This value is added to the sum of weighted pixels before the divisor is applied.
 *                          It can serve to both control rounding and adjust the brightness of the result.
 *                          A large bias (e.g 128 * divisor) may be required for some kernels, such as edge 
 *                          detection filters, to return representable results.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageConvolveWithBias_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const int16_t *kernel, uint32_t kernel_height, uint32_t kernel_width, int32_t divisor, int32_t bias, const Pixel_8888 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 *  @function vImageConvolveWithBias_ARGBFFFF
 *  @abstract General convolution on a ARGBFFFF image of any channel order with bias.
 *  @discussion This filter applies a convolution filter of your choosing to a ARGBFFFF image.
 *              This filter will work on any four-channel, float per component image format, not just ARGB.
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              float sumA = bias[0];
 *              float sumR = bias[1];
 *              float sumG = bias[2];
 *              float sumB = bias[3];
 *
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sumA += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][0];
 *                  sumR += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][1];
 *                  sumG += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][2];
 *                  sumB += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][3];
 *              }
 *
 *              // write out result
 *              result[y][x][0] = sumA;
 *              result[y][x][1] = sumR;
 *              result[y][x][2] = sumG;
 *              result[y][x][3] = sumB;
 *          }
 *      @/textblock </pre>
 *              (Above, we imagine the kernel to be a 2D array of size kernel_height by kernel_width.
 *              However, in practice it is passed in as a contiguous 1D array of size kernel_height *
 *              kernel_width.)
 *
 *              This filter does not work in place.
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const float kernel[9] =   { 1./16, 2./16, 1./16,
 *                                                      2./16, 4./16, 2./16,
 *                                                      1./16, 2./16, 1./16 };
 *                          @/textblock </pre>
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param bias             This value is added to the sum of weighted pixels.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageConvolveWithBias_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y,  const float *kernel, uint32_t kernel_height, uint32_t kernel_width, float bias,  const Pixel_FFFF backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );


/*!
 *  @function vImageConvolveMultiKernel_ARGB8888
 *  @abstract General convolution on a ARGB8888 image of any channel order with separate bias, kernel and divisor for each channel.
 *  @discussion This filter applies a convolution filter of your choosing to a ARGB8888 image.
 *              This filter will work on any four-channel, 8-bit per component image format, not just ARGB.
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              int sumA = 0;
 *              int sumR = 0;
 *              int sumG = 0;
 *              int sumB = 0;
 *				const int16_t *kA = kernel[0];
 *				const int16_t *kR = kernel[1];
 *				const int16_t *kG = kernel[2];
 *				const int16_t *kB = kernel[3];
 *
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sumA += kA[i*kernel_width+j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][0];
 *                  sumR += kR[i*kernel_width+j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][1];
 *                  sumG += kG[i*kernel_width+j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][2];
 *                  sumB += kB[i*kernel_width+j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][3];
 *              }
 *              // Correct for the scaling introduced by multiplying by the weights table
 *              sumA = (sumA + bias[0]) / divisor[0];
 *              sumR = (sumR + bias[1]) / divisor[1];
 *              sumG = (sumG + bias[2]) / divisor[2];
 *              sumB = (sumB + bias[3]) / divisor[3];
 *
 *              // write out result
 *              result[y][x][0] = CLAMP(sumA, 0, 255);
 *              result[y][x][1] = CLAMP(sumR, 0, 255);
 *              result[y][x][2] = CLAMP(sumG, 0, 255);
 *              result[y][x][3] = CLAMP(sumB, 0, 255);
 *          }
 *      @/textblock </pre>
 *              (Above, we imagine the kernel to be a 2D array of size kernel_height by kernel_width.
 *              However, in practice it is passed in as a contiguous 1D array of size kernel_height *
 *              kernel_width.)
 *
 *              This filter does not work in place.
 *
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           An array of 4 pointers to weights of dimension kernel_height x kernel_width.
 *                          The kernel values in each array may not sum in any combination to be outside the range
 *                          [-2**23, 2**23), or modulo overflow in the accumulator may result.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param divisor          The weighted sum of nearby pixels is typically a large number, which must be corrected
 *                          to fit back into the image format of the destination image. The correction factor
 *                          is passed in as divisor here, and is divided from the sum before the result is
 *                          returned. Typically, the divisor is the sum over the area of the kernel. If the divisor
 *                          is 0, 1 will be used instead.
 *
 *  @param bias             This array of values is added to the sum of weighted pixels for each channel respectively
 *                          before the divisor is applied. It can serve to both control rounding and adjust the 
 *                          brightness of the result. A large bias (e.g 128 * divisor) may be required for some 
 *                          kernels, such as edge detection filters, to return representable results.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageConvolveMultiKernel_ARGB8888(    const vImage_Buffer *src, 
                                                    const vImage_Buffer *dest, 
                                                    void *tempBuffer, 
                                                    vImagePixelCount srcOffsetToROI_X, 
                                                    vImagePixelCount srcOffsetToROI_Y,  
                                                    const int16_t *kernels[4], 		
                                                    uint32_t kernel_height, 
                                                    uint32_t kernel_width, 
                                                    const int32_t divisors[4], 
													const int32_t biases[4], 
                                                    const Pixel_8888 backgroundColor,
                                                    vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

    
/*!
 *  @function vImageConvolveMultiKernel_ARGBFFFF
 *  @abstract General convolution on a ARGBFFFF image of any channel order with separate bias and kernel for each channel.
 *  @discussion This filter applies a convolution filter of your choosing to a ARGBFFFF image.
 *              This filter will work on any four-channel, float per component image format, not just ARGB.
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              float sumA = bias[0];
 *              float sumR = bias[1];
 *              float sumG = bias[2];
 *              float sumB = bias[3];
 *				const float *kA = kernel[0];
 *				const float *kR = kernel[1];
 *				const float *kG = kernel[2];
 *				const float *kB = kernel[3];
 *
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sumA += kA[i*kernel_width+j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][0];
 *                  sumR += kR[i*kernel_width+j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][1];
 *                  sumG += kG[i*kernel_width+j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][2];
 *                  sumB += kB[i*kernel_width+j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2] [x+j+srcOffsetToROI_X- kernel_width/2][3];
 *              }
 *
 *              // write out result
 *              result[y][x][0] = sumA;
 *              result[y][x][1] = sumR;
 *              result[y][x][2] = sumG;
 *              result[y][x][3] = sumB;
 *          }
 *      @/textblock </pre>
 *              (Above, we imagine the kernel to be a 2D array of size kernel_height by kernel_width.
 *              However, in practice it is passed in as a contiguous 1D array of size kernel_height *
 *              kernel_width.)
 *
 *              This filter does not work in place.
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const float kernel[9] =   { 1./16, 2./16, 1./16,
 *                                                      2./16, 4./16, 2./16,
 *                                                      1./16, 2./16, 1./16 };
 *                          @/textblock </pre>
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param bias             This value is added to the sum of weighted pixels.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageConvolveMultiKernel_ARGBFFFF(    const vImage_Buffer *src, 
                                                    const vImage_Buffer *dest, 
                                                    void *tempBuffer, 
                                                    vImagePixelCount srcOffsetToROI_X, 
                                                    vImagePixelCount srcOffsetToROI_Y,  
                                                    const float *kernels[4], 
                                                    uint32_t kernel_height, 
                                                    uint32_t kernel_width, 
													const float biases[4], 
                                                    const Pixel_FFFF backgroundColor,
                                                    vImage_Flags flags ) VIMAGE_NON_NULL(1,2,6,9,10)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );




/*!
 * @functiongroup Richardson-Lucy Deconvolution
 *
 * @discussion Richardson-Lucy deconvolution (a.k.a. Lucy-Richardson) is an iterative procedure for estimating what an original image
 *  probably was before a convolution, given the convolution end result and the kernel used to create it.  It is typically used to fix blurring caused
 *  by lens distortion, most famously for the Hubble telescope, but also to improve images in confocal microscopy and other uses. When used
 *  to correct loss of signal due to physical limitations of the imaging system, the point spread function (kernel) is estimated from known
 *  parameters associated with the lensing system. It can also be used to sharpen images that have been digitally blurred, as long as the 
 *  original convolution kernel is known or can be estimated.
 *
 *  This routine iteratively uses the following formula:
 *      <pre>@textblock
 *		e[i+1] = e[i] x (psf0 * ( e[0] / (psf1 * e[i]) ) )
 *
 *		where:
 *              e[0] = the observed image (src parameter)
 *              e[n] = the result of the nth iteration
 *              psf  = point spread function (kernel for call to convolution)
 *				x    = multiply operator
 *              '*'  = convolution operator
 *      @/textblock </pre>
 *  As with any sharpening operation, Richardson-Lucy amplifies noise, and at some number of iterations the noise becomes noticeable as artifacts.
 *      <pre>@textblock
 *              =========================================================================
 *              ======    MOST VIMAGE CONVOLUTION FUNCTIONS DO NOT WORK IN PLACE    =====
 *              =========================================================================
 *      @/textblock </pre>
 */
    
    
/*!
 * @function vImageRichardsonLucyDeConvolve_Planar8
 * @abstract Perform N iterations of a Lucy-Richardson deconvolution on Planar8 data
 * @discussion
 *  This routine iteratively uses the following formula:
 *      <pre>@textblock
 *		e[i+1] = e[i] x (psf0 * ( e[0] / (psf1 * e[i]) ) )
 *
 *		where:
 *              e[0] = the observed image (src parameter)
 *              e[n] = the result of the nth iteration
 *              psf  = point spread function (kernel for call to convolution)
 *				x    = multiply operator
 *              '*'  = convolution operator
 *      @/textblock </pre>
 *
 *  The work in these functions is currently done internally with floating point precision. If you plan to call this function multiple times
 *  (rather than with iterationCount > 1) on 8-bit per channel images, you can save some computation by converting the 8-bit image data to
 *  single precision floating-point yourself using something like vImageConvert_Planar8toPlanarF and iterating on the appropriate
 *  floating-point Richardson Lucy variant. Convert back, when you are done.
 *
 *  Does not work in place.
 * @param src           The input image
 *
 * @param dest          A preallocated buffer to receive the result image. 
 *                      This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const int16_t kernel[9] = { 1, 2, 1,
 *                                                      2, 4, 2,
 *                                                      1, 2, 1 };
 *                          @/textblock </pre>
 *
 *                          This is psf0 in the formula given in the discussion.
 *
 *  @param kernel2          A pointer to a second 1D array of weights of dimension kernel_height2 x kernel_width2.
 *                          This is psf1 in the formula given in the discussion.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel1. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel1. It must be an odd number.
 *
 *  @param kernel_height2   The height of the 2D table of weights passed in as kernel2. It must be an odd number.
 *
 *  @param kernel_width2    The width of the 2D table of weights passed in as kernel2. It must be an odd number.
 *
 *  @param divisor          The divisor to use to correct for the volume under kernel.
 *
 *  @param divisor2         The divisor to use to correct for the volume under kernel2.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *  
 *  @param iterationCount   The number of Richardson-Lucy iterations to perform on the data before returning. 
 *                          If 0, the src buffer is coped to dest.
 *
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageRichardsonLucyDeConvolve_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, const int16_t *kernel, const int16_t *kernel2, uint32_t kernel_height, uint32_t kernel_width, uint32_t kernel_height2, uint32_t kernel_width2, int32_t divisor, int32_t divisor2, Pixel_8 backgroundColor, uint32_t iterationCount, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 * @function vImageRichardsonLucyDeConvolve_PlanarF
 * @abstract Perform N iterations of a Lucy-Richardson deconvolution on PlanarF data
 * @discussion
 *  This routine iteratively uses the following formula:
 *      <pre>@textblock
 *		e[i+1] = e[i] x (psf0 * ( e[0] / (psf1 * e[i]) ) )
 *
 *		where:
 *              e[0] = the observed image (src parameter)
 *              e[n] = the result of the nth iteration
 *              psf  = point spread function (kernel for call to convolution)
 *				x    = multiply operator
 *              '*'  = convolution operator
 *      @/textblock </pre>
 *
 *  Does not work in place.
 * @param src           The input image
 *
 * @param dest          A preallocated buffer to receive the result image.
 *                      This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const float kernel[9] =   { 1./16, 2./16, 1./16,
 *                                                      2./16, 4./16, 2./16,
 *                                                      1./16, 2./16, 1./16 };
 *                          @/textblock </pre>
 *
 *                          This is psf0 in the formula given in the discussion.
 *
 *  @param kernel2          A pointer to a second 1D array of weights of dimension kernel_height2 x kernel_width2.
 *                          This is psf1 in the formula given in the discussion.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel1. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel1. It must be an odd number.
 *
 *  @param kernel_height2   The height of the 2D table of weights passed in as kernel2. It must be an odd number.
 *
 *  @param kernel_width2    The width of the 2D table of weights passed in as kernel2. It must be an odd number.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param iterationCount   The number of Richardson-Lucy iterations to perform on the data before returning.
 *                          If 0, the src buffer is coped to dest.
 *
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageRichardsonLucyDeConvolve_PlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, const float *kernel, const float *kernel2, uint32_t kernel_height, uint32_t kernel_width, uint32_t kernel_height2, uint32_t kernel_width2, Pixel_F backgroundColor,  uint32_t iterationCount, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 * @function vImageRichardsonLucyDeConvolve_ARGB8888
 * @abstract Perform N iterations of a Lucy-Richardson deconvolution on ARGB8888 data.
 * @discussion
 *  This routine iteratively uses the following formula:
 *      <pre>@textblock
 *		e[i+1] = e[i] x (psf0 * ( e[0] / (psf1 * e[i]) ) )
 *
 *		where:
 *              e[0] = the observed image (src parameter)
 *              e[n] = the result of the nth iteration
 *              psf  = point spread function (kernel for call to convolution)
 *				x    = multiply operator
 *              '*'  = convolution operator
 *      @/textblock </pre>
 *  The channels are operated on independently of one another. Consequently, this function will work on
 *  any 4-channel interleaved 8-bit per component format (e.g. RGBA, BGRA...), not just ARGB. 
 *
 *  The work in these functions is currently done internally with floating point precision. If you plan to call this function multiple times
 *  (rather than with iterationCount > 1) on 8-bit per channel images, you can save some computation by converting the 8-bit image data to
 *  single precision floating-point yourself using something like vImageConvert_Planar8toPlanarF and iterating on the appropriate
 *  floating-point Richardson Lucy variant. Convert back, when you are done.
 *
 *  Does not work in place.
 *
 * @param src           The input image
 *
 * @param dest          A preallocated buffer to receive the result image.
 *                      This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const int16_t kernel[9] = { 1, 2, 1,
 *                                                      2, 4, 2,
 *                                                      1, 2, 1 };
 *                          @/textblock </pre>
 *
 *                          This is psf0 in the formula given in the discussion.
 *
 *  @param kernel2          A pointer to a second 1D array of weights of dimension kernel_height2 x kernel_width2.
 *                          This is psf1 in the formula given in the discussion.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel1. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel1. It must be an odd number.
 *
 *  @param kernel_height2   The height of the 2D table of weights passed in as kernel2. It must be an odd number.
 *
 *  @param kernel_width2    The width of the 2D table of weights passed in as kernel2. It must be an odd number.
 *
 *  @param divisor          The divisor to use to correct for the volume under kernel.
 *
 *  @param divisor2         The divisor to use to correct for the volume under kernel2.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param iterationCount   The number of Richardson-Lucy iterations to perform on the data before returning.
 *                          If 0, the src buffer is coped to dest.
 *
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *              kvImageLeaveAlphaUnchanged  Operate only on the last 3 channels in memory. Leave the first channel
 *                                          unmodified.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageRichardsonLucyDeConvolve_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, const int16_t *kernel, const int16_t *kernel2, uint32_t kernel_height, uint32_t kernel_width, uint32_t kernel_height2, uint32_t kernel_width2, int32_t divisor, int32_t divisor2, const Pixel_8888 backgroundColor,  uint32_t iterationCount, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 * @function vImageRichardsonLucyDeConvolve_ARGBFFFF
 * @abstract Perform N iterations of a Lucy-Richardson deconvolution on ARGBFFFF data
 * @discussion
 *  This routine iteratively uses the following formula:
 *      <pre>@textblock
 *		e[i+1] = e[i] x (psf0 * ( e[0] / (psf1 * e[i]) ) )
 *
 *		where:
 *              e[0] = the observed image (src parameter)
 *              e[n] = the result of the nth iteration
 *              psf  = point spread function (kernel for call to convolution)
 *				x    = multiply operator
 *              '*'  = convolution operator
 *      @/textblock </pre>
 *
 *  The channels are operated on independently of one another. Consequently, this function will work on
 *  any 4-channel interleaved 8-bit per component format (e.g. RGBA, BGRA...), not just ARGB.
 *
 *  Does not work in place.
 * @param src           The input image
 *
 * @param dest          A preallocated buffer to receive the result image.
 *                      This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel           A pointer to a 1D array of weights of dimension kernel_height x kernel_width.
 *                          For example, for a simple 3x3 blur, it might be:
 *                          <pre>@textblock
 *                          const float kernel[9] =   { 1./16, 2./16, 1./16,
 *                                                      2./16, 4./16, 2./16,
 *                                                      1./16, 2./16, 1./16 };
 *                          @/textblock </pre>
 *
 *                          This is psf0 in the formula given in the discussion.
 *
 *  @param kernel2          A pointer to a second 1D array of weights of dimension kernel_height2 x kernel_width2.
 *                          This is psf1 in the formula given in the discussion.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel1. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel1. It must be an odd number.
 *
 *  @param kernel_height2   The height of the 2D table of weights passed in as kernel2. It must be an odd number.
 *
 *  @param kernel_width2    The width of the 2D table of weights passed in as kernel2. It must be an odd number.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param iterationCount   The number of Richardson-Lucy iterations to perform on the data before returning.
 *                          If 0, the src buffer is coped to dest.
 *
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *              kvImageLeaveAlphaUnchanged  Operate only on the last 3 channels in memory. Leave the first channel
 *                                          unmodified.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageNullPointerArgument  kernel may not be NULL
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageRichardsonLucyDeConvolve_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, const float *kernel, const float *kernel2, uint32_t kernel_height, uint32_t kernel_width, uint32_t kernel_height2, uint32_t kernel_width2, const Pixel_FFFF backgroundColor,  uint32_t iterationCount, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 *  @functiongroup Box Convolve
 *  @discussion  A box convolve is a special case of the standard convolution, which has a much faster algorithm.
 *               A box kernel is a kernel populated with all 1's. This returns the unweighted average of the pixels
 *               near the result pixel. Unlike general purpose convolution, the cost of a box convolve algorithm
 *               is theoretically constant regardless of kernel size, so it can be an inexpensive choice for very
 *               large blurs. The box convolve behavior may not be as desired, however, because the blur effect is
 *               rectangular in appearance, whereas most expect it to be gaussian or roughly circular. A tent blur has 
 *               similar rectangular character, but because the weighting is non uniform, it is less obvious. A
 *               tent blur is also constant cost per pixel, but larger constant cost.
 *
 *               Two box blur passes of the same kernel size results in a tent blur.  To see this we can take a 1-d starting image:
 *                <pre> @textblock
 *                      p0          p1          p2          p3          p4          p5          p6
 *                @/textblock </pre>
 *               and blur it once with a 3 wide box blur, ignoring for the moment what happens at the edges:
 *                <pre> @textblock
 *                     (edge)    p0+p1+p2    p1+p2+p3    p2+p3+p4    p3+p4+p5    p4+p5+p6    p5+p6+p7
 *                @/textblock </pre>
 *               and a second time:
 *                <pre> @textblock
 *                     (edge)           p0+2p1+3p2+2p3+p4       p2+2p3+3p4+2p5+p6       p4+2p5+3p6+2p7+p8 .....
 *                               (edge)             p1+2p2+3p3+2p4+p5       p3+2p4+3p5+2p6+p7
 *                @/textblock </pre>
 *
 *                If this process is continued, the shape converges towards a gaussian over multiple passes.
 *      <pre>@textblock
 *              =========================================================================
 *              ======    MOST VIMAGE CONVOLUTION FUNCTIONS DO NOT WORK IN PLACE    =====
 *              =========================================================================
 *      @/textblock </pre>
 */

/*!
 *  @function vImageBoxConvolve_Planar8
 *  @abstract Special purpose box convolution on a Planar8 image.
 *  @discussion This filter applies a box filter to a Planar8 image.  A box filter uses a much faster algorithm
 *              than a standard convolution, and may be a good solution for real time application of large blur
 *              radii against images.
 *              For each pixel:
 *      <pre>@textblock
 *          vImagePixelCount kernel_area = kernel_height * kernel_width;
 *          for each pixel[y][x] in image{
 *              int sum = 0;
 *
 *              // Calculate unweighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sum += pixel[y+i+srcOffsetToROI_Y-kernel_height/2]
 *                              [x+j+srcOffsetToROI_X- kernel_width/2];
 *              }
 *              // Correct for the scaling introduced by multiplying by the weights table
 *              sum = (sum + kernel_area/2) / kernel_area;
 *
 *              // write out result
 *              result[y][x] = CLAMP(sum, 0, 255);
 *          }
 *      @/textblock </pre>
 *
 *              This filter does not work in place.
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageBoxConvolve_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, uint32_t kernel_height, uint32_t kernel_width, Pixel_8 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
    
/*!
 *  @function vImageBoxConvolve_ARGB8888
 *  @abstract Special purpose box convolution on a 4-channel interleaved, 8-bit per channel image.
 *  @discussion This filter applies a box filter to a 4-channel interleaved, 8-bit per channel imagee.
 *              A box filter uses a much faster algorithm than a standard convolution, and may be a good
 *              solution for real time application of large blur radii against images.
 *              For each pixel:
 *      <pre>@textblock
 *          vImagePixelCount kernel_area = kernel_height * kernel_width;
 *          for each pixel[y][x] in image{
 *              int sumA = 0;
 *              int sumR = 0;
 *              int sumG = 0;
 *              int sumB = 0;
 *
 *              // Calculate unweighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sumA += pixel[y+i+srcOffsetToROI_Y-kernel_height/2]
 *                               [x+j+srcOffsetToROI_X- kernel_width/2][0];
 *                  sumR += pixel[y+i+srcOffsetToROI_Y-kernel_height/2]
 *                               [x+j+srcOffsetToROI_X- kernel_width/2][1];
 *                  sumG += pixel[y+i+srcOffsetToROI_Y-kernel_height/2]
 *                               [x+j+srcOffsetToROI_X- kernel_width/2][2];
 *                  sumB += pixel[y+i+srcOffsetToROI_Y-kernel_height/2]
 *                               [x+j+srcOffsetToROI_X- kernel_width/2][3];
 *              }
 *              // Correct for the scaling introduced by multiplying by the weights table
 *              sumA = (sumA + kernel_area/2) / kernel_area;
 *              sumR = (sumR + kernel_area/2) / kernel_area;
 *              sumG = (sumG + kernel_area/2) / kernel_area;
 *              sumB = (sumB + kernel_area/2) / kernel_area;
 *
 *              // write out result
 *              result[y][x][0] = CLAMP(sumA, 0, 255);
 *              result[y][x][1] = CLAMP(sumR, 0, 255);
 *              result[y][x][2] = CLAMP(sumG, 0, 255);
 *              result[y][x][3] = CLAMP(sumB, 0, 255);
 *          }
 *      @/textblock </pre>
 *
 *              This filter does not work in place.
 *
 *              This filter will work without modification for other byte orders such as RGBA, BGRA, AGBR, CMYK, etc. 
 *              The image should be non-premultiplied to avoid odd results in non-opaque regions.
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageLeaveAlphaUnchanged  Apply the convolution to the last three channels in memory, only.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageBoxConvolve_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, uint32_t kernel_height, uint32_t kernel_width, const Pixel_8888 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*!
 *  @functiongroup Tent Convolve
 *  @discussion  A tent convolve is a special case of the standard convolution, which has a much faster algorithm.
 *               A tent kernel is a kernel populated with slope of 1 rising towards the center. 2D kernels
 *               are calculated as the product of the appropriate 1D kernels. e.g.
 *               <pre> @textblock
 *                  {1,2,3,2,1}
 *               @/textblock </pre>
 *               or 
 *               <pre> @textblock
 *               |1|                { {1,2,1},
 *               |2| *  {1,2,1} =     {2,4,2},
 *               |1|                  {1,2,1}   }
 *               @/textblock </pre>
 *               This returns a blur that is more heavily weighted towards the center pixel than a box blur.
 *
 *               Unlike general purpose convolution, the cost of a tent convolve algorithm is theoretically constant 
 *               regardless of kernel size, so it can be an inexpensive choice for very large blurs. The tent convolve 
 *               behavior may not be as desired, however, because the blur effect is rectangular in appearance, whereas 
 *               most expect a blurring effect to be gaussian or roughly circular. The rectangularity of the tent blur
 *               is less obvious than the box blur.  A tent blur has somewhat larger constant cost than a box blur.
 *
 *      <pre>@textblock
 *              =========================================================================
 *              ======    MOST VIMAGE CONVOLUTION FUNCTIONS DO NOT WORK IN PLACE    =====
 *              =========================================================================
 *      @/textblock </pre>
 */

/*!
 *  @function vImageTentConvolve_Planar8
 *  @abstract Special purpose tent convolution on a Planar8 image.
 *  @discussion This filter applies a tent filter to a Planar8 image.  A tent filter uses a much faster algorithm
 *              than a standard convolution, and may be a good solution for real time application of large blur
 *              radii against images.
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              int sum = 0;
 *              int divisor = 0;
 *
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sum += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2]
 *                               [x+j+srcOffsetToROI_X- kernel_width/2];
 *                  divisor += kernel_element[i][j];
 *              }
 *
 *              // Correct for the scaling introduced by multiplying by the weights table
 *              sum = (sum + divisor/2) / divisor;
 *
 *              // write out result
 *              result[y][x] = CLAMP(sum, 0, 255);
 *          }
 *      @/textblock </pre>
 *
 *              This filter does not work in place.
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageTentConvolve_Planar8( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, uint32_t kernel_height, uint32_t kernel_width, Pixel_8 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

    
    

/*!
 *  @function vImageTentConvolve_ARGB8888
 *  @abstract Special purpose tent convolution on a 4-channel interleaved, 8-bit per channel image.
 *  @discussion This filter applies a tent filter to a 4-channel interleaved, 8-bit per channel imagee.
 *              A tent filter uses a much faster algorithm than a standard convolution, and may be a good
 *              solution for real time application of large blur radii against images.
 *              For each pixel:
 *      <pre>@textblock
 *          for each pixel[y][x] in image{
 *              int sumA = 0;
 *              int sumR = 0;
 *              int sumG = 0;
 *              int sumB = 0;
 *              int divisor = 0;
 *
 *              // Calculate weighted average over kernel area
 *              for each kernel_element[i][j] in kernel{
 *                  sumA += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][0];
 *                  sumR += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][1];
 *                  sumG += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][2];
 *                  sumB += kernel_element[i][j] *
 *                          pixel[y+i+srcOffsetToROI_Y-kernel_height/2][x+j+srcOffsetToROI_X- kernel_width/2][3];
 *                  divisor += kernel_element[i][j];
 *              }
 *              // Correct for the scaling introduced by multiplying by the weights table
 *              sumA = (sumA + divisor/2) / divisor;
 *              sumR = (sumR + divisor/2) / divisor;
 *              sumG = (sumG + divisor/2) / divisor;
 *              sumB = (sumB + divisor/2) / divisor;
 *
 *              // write out result
 *              result[y][x][0] = CLAMP(sumA, 0, 255);
 *              result[y][x][1] = CLAMP(sumR, 0, 255);
 *              result[y][x][2] = CLAMP(sumG, 0, 255);
 *              result[y][x][3] = CLAMP(sumB, 0, 255);
 *          }
 *      @/textblock </pre>
 *
 *              This filter does not work in place.
 *
 *              This filter will work without modification for other byte orders such as RGBA, BGRA, AGBR, CMYK, etc.
 *              The image should be non-premultiplied to avoid odd results in non-opaque regions.
 *
 *  @param src              The input image
 *
 *  @param dest             A pointer to a preallocated vImage_Buffer to receive the result image.
 *                          This may not alias the src image.
 *
 *  @param tempBuffer       An optional pointer to a region of memory to use as a working area during
 *                          computation.  The size of the tempBuffer is given by calling the function
 *                          with the same parameters and the kvImageGetTempBufferSize flag, in which case
 *                          the size is returned instead of an error code from the left hand side.
 *                          You may pass NULL here, in which case a region of memory of similar size
 *                          will be allocated by the function and freed before it returns.  Temp Buffers
 *                          are a way of avoiding lost time due to VM faults to initialize newly allocated
 *                          buffers. If you will be calling this function repeatedly with similar parameters
 *                          you should use a temp buffer. If the function is called from different threads
 *                          concurrently, a different temp buffer should be used for each.
 *
 *  @param srcOffsetToROI_X An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the left edge of the image.
 *
 *  @param srcOffsetToROI_Y An offset used in tiling to shift the position of the destination image
 *                          relative to the src image. Typically this is 0. Non-Zero values are needed
 *                          when the destination tile is not aligned with the top edge of the image.
 *
 *  @param kernel_height    The height of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param kernel_width     The width of the 2D table of weights passed in as kernel. It must be an odd number.
 *
 *  @param backgroundColor  When the kvImageBackgroundColorFill edging mode is active, the backgroundColor
 *                          parameter provides the background color to be used for missing pixels when the
 *                          kernel extends off the edge of the image.
 *
 *  @param flags            The following flags are allowed:
 *      <pre>@textblock
 *              kvImageCopyInPlace          If any pixels covered by the kernel do no not exist, simply
 *                                          copy the corresponding source pixel to the destination. This
 *                                          will result in a ring on unconvolved content at the edges
 *                                          and convolved content in the middle.
 *
 *              kvImageBackgroundColorFill  Substitute in the provided background color for missing pixels.
 *                                          For a blur filter this will look like the edges of the image
 *                                          have been blurred into a particular color. This is usually
 *                                          appropriate when the color of the surface onto which the image
 *                                          will be drawn is known.  You can also use {Alpha = 0, color = 0}
 *                                          as a background color, and let the downstream image compositor
 *                                          blend in the background color. In this case, the result image
 *                                          should be treated as a premultiplied image.
 *
 *              kvImageEdgeExtend           Substitute in the nearest defined pixel for missing pixels.
 *                                          This is better when the image is drawn into a frame or other
 *                                          context where the background is not expected to contribute to
 *                                          the final content.
 *
 *              kvImageTruncateKernel       This is similar to kvImageEdgeExtend, except that edge pixels are
 *                                          simply ignored, and the bias and divisor are adjusted accordingly.
 *                                          Because of the complication at the edges, this edging mode can
 *                                          be significantly slower than the others. It can be numerically
 *                                          unstable if the sum over any rectangular subsection of the kernel
 *                                          is zero, which can result in division by zero during the computation.
 *                                          The results for this edging mode are usually quite visually similar
 *                                          to kvImageEdgeExtend.
 *
 *              kvImageGetTempBufferSize    Instead of calculating the convolution of the image, return the
 *                                          size of the temp buffer needed for this set of parameters. Does
 *                                          not touch the src or dest image.
 *
 *              kvImageLeaveAlphaUnchanged  Apply the convolution to the last three channels in memory, only.
 *
 *              kvImageDoNotTile            Disable internal multithreading.
 *
 *      @/textblock </pre>
 *                          The first four flags listed are edging modes. One and only one edging mode must be
 *                          provided. If no edging mode is provided (e.g. kvImageNoFlags), then an error will
 *                          be returned.
 *
 *  @return One of the following error codes may be returned:
 *      <pre>@textblock
 *          kvImageNoError              Success.
 *              >= 0                    If kvImageGetTempBufferSize is passed, this is the size of
 *                                      the temp buffer to use with this function and this set of
 *                                      parameters.
 *
 *          kvImageInvalidEdgeStyle     One and only one of the following flags must be provided:
 *                                         { kvImageCopyInPlace, kvImageBackgroundColorFill,
 *                                           kvImageEdgeExtend,  kvImageTruncateKernel }
 *
 *          kvImageRoiLargerThanInputBuffer The dest->width and height must be less than or equal
 *                                          to corresponding dimensions of the source buffer.
 *
 *          kvImageInvalidOffset_X      The destination width + srcOffsetToROI_X > src->width
 *
 *          kvImageInvalidOffset_Y      The destination height + srcOffsetToROI_Y > src->height
 *
 *          kvImageMemoryAllocationError Could not allocate memory to serve as a temp buffer.
 *
 *          kvImageInvalidKernelSize    The kernel height and width must be odd numbers.
 *      @/textblock </pre>
 */
vImage_Error vImageTentConvolve_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, vImagePixelCount srcOffsetToROI_X, vImagePixelCount srcOffsetToROI_Y, uint32_t kernel_height, uint32_t kernel_width, const Pixel_8888 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );


#ifdef __cplusplus
}
#endif

#endif
