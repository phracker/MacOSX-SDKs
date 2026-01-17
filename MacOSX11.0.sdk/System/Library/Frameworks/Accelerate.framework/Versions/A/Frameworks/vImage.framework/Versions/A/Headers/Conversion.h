/*!
@header Conversion.h
vImage_Framework

See vImage/vImage.h for more on how to view the headerdoc documentation for functions declared herein.

@discussion  This header lists conversions between the many different image formats supported by vImage.  The core formats:
@code
Planar 8        Planar 16U      Planar 16S      Float
ARGB8888        ARGB16U         ARGB16S         ARGBFFFF        (also available in other channel orderings)
@endcode
are supported generally throughout vImage. Other formats may need to be converted to a core format before much can be
done with them. Many conversions between core formats as well as those between core formats and non-core formats are available here.
Please also see vImage_Utilities.h and vImage_CVUtilities.h for interfaces that allow for conversion between various CoreGraphics
and CoreVideo formats.  In many cases, those interfaces can serve as a simpler entrypoint into these APIs. They should be strongly
considered in cases where your code has to handle a variety of different image formats. These interfaces provide direct access to
the low-level workhorse functions for the case when you know exactly what image formats you are working with and want to just call
the right conversion directly.

Generally speaking, conversions are much faster than other image filters. When tiled correctly, they do not add a lot of extra cost
in cases where you find that your image format is not directly supported by other image filters. They are usually fast enough that
their performance is bottlenecked by throughput to L2, L3, etc. caches.  They benefit greatly from tiling, usually performing best
with wide tile sizes that are less than half the size of the L1 cache. Because of the L1 cache residency requirement for best performance,
they are often not internally multithreaded (it wouldn't help for out-of-cache performance and would cause slowdowns for in-cache)
and may need  to be used within the context of your tiling engine (or vImageConvert_AnyToAny) to reach peak performance. If you are calling
vImage functions within your own multithreaded tiling engine, it is recommended that you use the kvImageDoNotTile flag to make sure that
vImage does its work on the calling thread. This will help ensure that the data just produced on that thread by a previous pass
is resident in the correct L1 cache for the next pass.

@copyright Copyright (c) 2003-2016 by Apple Inc. All rights reserved.

@ignorefuncmacro VIMAGE_NON_NULL
*/


#ifndef VIMAGE_CONVERSION_H
#define VIMAGE_CONVERSION_H

#include <vImage/vImage_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 @function vImageClip_PlanarF
 
 @abstract Clips the pixel values of an image in PlanarF format, using the provided minimum and maximum values.
 
 @discussion For each pixel, do the following:
 @code
 if( pixel > maxFloat )
 pixel = maxFloat;
 if( pixel < minFloat )
 pixel = minFloat;
 @endcode
 
 This function can work in place provided the following are true:
 If src overlaps with dest, src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes
 If an overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param src
 A pointer to a vImage buffer structure that contains the source image whose data you want to clip.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a allocated buffer to receive the result pixels.
 
 @param maxFloat
 A maximum pixel value. The function clips larger values to this value in the destination image.
 
 @param minFloat
 A minimum pixel value. The function clips smaller values to this value in the destination image.
 
 @param flags
 \p kvImageNoFlags      Default operation.
 \p kvImageDoNotTile    Disable internal multithreading.
 
 @return kvImageNoError                      Success
 @return kvImageRoiLargerThanInputBuffer     The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @note This function may be used for multichannel image formats, such as ARGBFFFF.
 Scale the vImage_Buffer.width to compensate for the extra channels.
 */
VIMAGE_PF vImage_Error vImageClip_PlanarF(const vImage_Buffer* src, const vImage_Buffer* dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags)  VIMAGE_NON_NULL(1,2)   API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_Planar8toPlanarF
 
 @abstract Convert an array of 8 bit integer data to floating point data.
 
 @discussion For each pixel, do the following:
 @code
 float result = (maxFloat - minFloat) * (float) srcPixel / 255.0  + minFloat
 @endcode
 
 You can use this for ARGB8888 -> ARGBFFFF conversions by simply multiplying the width of the vImage_Buffer by 4 (for 4 channels)
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing the source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a allocated buffer to receive the result pixels.
 
 @param maxFloat
 A maximum float value.
 
 @param minFloat
 A minimum float value.
 
 @param flags
 \p kvImageNoFlags                      Default operation.
 \p kvImageDoNotTile                    Disable internal multithreading.
 \p kvImagePrintDiagnosticsToConsole    Directs the function to print diagnostic information to the console in the event of failure.
 
 @return kvImageNoError                     Success
 @return kvImageUnknownFlagsBit             Not all vImage flags are understood by this function. See description of flags parameter for supported flags.
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @note Does not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_Planar8toPlanarF(const vImage_Buffer *src, const vImage_Buffer *dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_PlanarFtoPlanar8
 
 @abstract Convert an array of floating point data to 8 bit integer data.
 
 @discussion For each pixel, do the following:
 @code
 uint8_t result = SATURATED_CLIP_0_to_255( 255.0f * ( srcPixel - minFloat ) / (maxFloat - minFloat) + 0.5f );
 @endcode
 
 You can use this for ARGBFFFF -> ARGB8888 conversions by simply multiplying the width of the vImage_Buffer by 4 (for 4 channels)
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing the source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a allocated buffer to receive the result pixels.
 
 @param maxFloat
 A maximum float value.
 
 @param minFloat
 A minimum float value.
 
 @param flags
 \p kvImageNoFlags      Default operation
 \p kvImageDoNotTile    Disable internal multithreading.  You should use this if you are doing your own threading / tiling.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageConvert_PlanarFtoPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, Pixel_F maxFloat, Pixel_F minFloat, vImage_Flags flags) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_PlanarFtoPlanar8_dithered
 
 @abstract Convert an array of floating point data to 8 bit integer data with dithering.
 
 @discussion For each pixel, do the following:
 @code
 uint8_t result = SATURATED_CLIP_0_to_255( 255.0f * ( srcPixel - minFloat ) / (maxFloat - minFloat) + random_float[0,1) );
 @endcode
 
 The \p dither parameter must be one of the following flags:
 \p kvImageConvert_DitherNone Same as vImageConvert_PlanarFtoPlanar8(). Rounds to nearest.
 
 \p kvImageConvert_DitherOrdered Pre-computed blue noise is added to the image before rounding to the values in
 the destination format.  The offset into this blue noise is randomized per-call to avoid visible artifacts
 if you do your own tiling or call the function on sequential frames of video.
 
 \p kvImageConvert_DitherOrderedReproducible Pre-computed blue noise is added to the image before rounding to the
 values in the destination format.  The offset into the blue noise is the same for every call to allow users
 to get reproducible results. Fine for still images. For video kvImageConvert_DitherOrdered is a better choice.
 
 The ordered dither methods may be further influenced by shaping the distribution of the noise using the gaussian and uniform options below.
 These options are OR-ed with kvImageConvert_DitherOrdered / kvImageConvert_DitherOrderedReproducible:
 
 \p kvImageConvert_OrderedGaussianBlue When using an ordered dither pattern, distribute the noise according to a gaussian
 distribution. This generally gives more pleasing images --  less noisy and perhaps a little more saturated -- but color
 fidelity can suffer. Its effect is between kvImageConvert_DitherNone and kvImageConvert_DitherOrdered | kvImageConvert_DitherUniform.
 This is the default for kvImageConvert_DitherOrdered and kvImageConvert_DitherOrderedReproducible.
 
 \p kvImageConvert_OrderedUniformBlue When using an ordered dither pattern, distribute the noise uniformly. This generally gives
 best color fidelity, but the resulting image is noisier and more obviously dithered. This is usually the best choice when low
 bitdepth content is drawn next to high bitdepth content and in other circumstances where subtle changes to color arising from the conversion
 could be easily noticed. It may be a poor choice when the image is likely to be enlarged -- this would cause the noise to become
 more evident-- and for very flat / synthetic content with little inherent noise. The enlargement problem may be avoided by enlarging
 first at high bitdepth, then convert to lower bitdepth.
 
 @note "Blue" noise does not look blue, nor does it operate solely on the blue color channel. Blue noise is monochrome noise that is added to all color
 channels equally. The name arises from blue light, which has a higher frequency than other colors of visible light. Thus, blue noise is noise which is
 weighted heavily towards high frequencies. Low frequency noise tends to have visible shapes in it that would become apparent in an image if it was added in,
 so it is excluded from the dither pattern.
 
 @warning Unlike vImageConvert_PlanarFtoPlanar8, vImageConvert_PlanarFtoPlanar8_dithered usually should not be used for
 multichannel data. Otherwise the dithering will occur in the chrominance dimensions and the noise will cause
 grain with varying hue.
 
 @note This function can work in place provided the following are true:
 If src overlaps with dest, src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes.
 If an overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags.
 
 @param src               A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing the source pixels.
 
 @param dest              A pointer to a valid and initialized vImage_Buffer struct, that points to a allocated buffer to receive the result pixels.
 
 @param maxFloat          The encoding for 1.0 in the src buffer, full intensity. Typically, this is 1.0 for floating-point data in the range[0,1] but if your data is [0,65535] then you would pass 65535.0f here.
 
 @param minFloat          The encoding for 0.0 in the src buffer, no light.  Typically this is 0.0 for floating-point data in the range [0,1], but if your data is [-.5,0.5] then you would pass -0.5f here.
 
 @param dither            The type of random noise to use for the dither. See discussion for more details.
 
 @param flags                   The following flags are honored:
 \p kvImageNoFlags              Default operation.
 \p kvImageDoNotTile            Disable internal multithreading, if any.
 \p kvImageGetTempBufferSize    Returns 0. Does no work. Does not touch data.
 
 @return \p kvImageNoError                      Success
 @return \p kvImageRoiLargerThanInputBuffer     The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 @return \p kvImageUnknownFlagsBit              Not all vImage flags are understood by this function. See description of flags parameter for supported flags.
 @return \p kvImageInvalidParameter             An unknown / unsupported dithering mode was requested.
 
 @seealso vImageConvert_PlanarFtoPlanar8
 */
VIMAGE_PF vImage_Error vImageConvert_PlanarFtoPlanar8_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, Pixel_F maxFloat, Pixel_F minFloat, int dither, vImage_Flags flags) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_RGBFFFtoRGB888_dithered
 
 @abstract Convert an array of floating point data to 8 bit integer data with dithering.
 
 @discussion For each pixel, do the following:
 @code
 // convert to uint8_t
 result[0] = SATURATED_CLIP_0_to_255( 255.0f * ( srcPixel[0] - minFloat[0] ) / (maxFloat[0] - minFloat[0]) + random_float[0,1) );
 result[1] = SATURATED_CLIP_0_to_255( 255.0f * ( srcPixel[1] - minFloat[1] ) / (maxFloat[1] - minFloat[1]) + random_float[0,1) );
 result[2] = SATURATED_CLIP_0_to_255( 255.0f * ( srcPixel[2] - minFloat[2] ) / (maxFloat[2] - minFloat[2]) + random_float[0,1) );
 @endcode
 
 This function will work for other channel orders, such as BGR, and other colorspaces such as L*a*b*.
 If you need to change channel orders, please see vImagePermuteChannels_RGB888().
 
 The \p dither parameter must be one of the following flags:
 \p kvImageConvert_DitherNone Same as vImageConvert_PlanarFtoPlanar8(). Rounds to nearest.
 
 \p kvImageConvert_DitherOrdered Pre-computed blue noise is added to the image before rounding to the values in
 the destination format.  The offset into this blue noise is randomized per-call to avoid visible artifacts
 if you do your own tiling or call the function on sequential frames of video.
 
 \p kvImageConvert_DitherOrderedReproducible Pre-computed blue noise is added to the image before rounding to the
 values in the destination format.  The offset into the blue noise is the same for every call to allow users
 to get reproducible results. Fine for still images. For video kvImageConvert_DitherOrdered is a better choice.
 
 The ordered dither methods may be further influenced by shaping the distribution of the noise using the gaussian and uniform options below.
 These options are OR-ed with kvImageConvert_DitherOrdered / kvImageConvert_DitherOrderedReproducible:
 
 \p kvImageConvert_OrderedGaussianBlue When using an ordered dither pattern, distribute the noise according to a gaussian
 distribution. This generally gives more pleasing images --  less noisy and perhaps a little more saturated -- but color
 fidelity can suffer. Its effect is between kvImageConvert_DitherNone and kvImageConvert_DitherOrdered | kvImageConvert_DitherUniform.
 This is the default for kvImageConvert_DitherOrdered and kvImageConvert_DitherOrderedReproducible.
 
 \p kvImageConvert_OrderedUniformBlue When using an ordered dither pattern, distribute the noise uniformly. This generally gives
 best color fidelity, but the resulting image is noisier and more obviously dithered. This is usually the best choice when low
 bitdepth content is drawn next to high bitdepth content and in other circumstances where subtle changes to color arising from the conversion
 could be easily noticed. It may be a poor choice when the image is likely to be enlarged -- this would cause the noise to become
 more evident-- and for very flat / synthetic content with little inherent noise. The enlargement problem may be avoided by enlarging
 first at high bitdepth, then convert to lower bitdepth.
 
 @note "Blue" noise does not look blue, nor does it operate solely on the blue color channel. Blue noise is monochrome noise that is added to all color
 channels equally. The name arises from blue light, which has a higher frequency than other colors of visible light. Thus, blue noise is noise which is
 weighted heavily towards high frequencies. Low frequency noise tends to have visible shapes in it that would become apparent in an image if it was added in,
 so it is excluded from the dither pattern.
 
 @note This function can work in place provided the following are true:
 If src overlaps with dest, src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes.
 If an overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param src               A pointer to a valid and initialized vImage_Buffer struct that points to a buffer containing the source pixels.
 
 @param dest              A pointer to a valid and initialized vImage_Buffer struct that points to a allocated buffer to receive the result pixels.
 
 @param maxFloat          The encoding for 1.0 in the src buffer, full intensity.
 Typically, this is 1.0 for floating-point data in the range[0,1]
 but if your data is [0,65535] then you would pass 65535.0f here.
 A separate value is provided for each of the three channels.
 
 @param minFloat          The encoding for 0.0 in the src buffer, no light.
 Typically this is 0.0 for floating-point data in the range [0,1],
 but if your data is [-.5,0.5] then you would pass -0.5f here.
 A separate value is provided for each of the three channels.
 
 @param dither            The type of random noise to use for the dither. See discussion for more details.
 
 @param flags                   The following flags are honored:
 \p kvImageNoFlags              Default operation.
 \p kvImageDoNotTile            Disable internal multithreading, if any.
 \p kvImageGetTempBufferSize    Returns 0. Does no work. Does not touch data.
 
 @return \p kvImageNoError                      Success
 @return \p kvImageRoiLargerThanInputBuffer     The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 @return \p kvImageUnknownFlagsBit              Not all vImage flags are understood by this function. See description of flags parameter for supported flags.
 @return \p kvImageInvalidParameter             An unknown / unsupported dithering mode was requested.
 
 @seealso vImageConvert_RGBFFFtoRGB888
 @seealso vImagePermuteChannels_RGB888
 */
VIMAGE_PF vImage_Error vImageConvert_RGBFFFtoRGB888_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_F maxFloat[3], const Pixel_F minFloat[3], int dither, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4)    API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGBFFFFtoARGB8888_dithered
 
 @abstract Convert an array of floating point data to 8 bit integer data with dithering.
 
 @discussion For each pixel, do the following:
 @code
 // convert to uint8_t
 Pixel_8888 temp;
 temp[0] = SATURATED_CLIP_0_to_255( 255.0f * ( srcPixel[0] - minFloat[0] ) / (maxFloat[0] - minFloat[0]) + random_float[0,1) );
 temp[1] = SATURATED_CLIP_0_to_255( 255.0f * ( srcPixel[1] - minFloat[1] ) / (maxFloat[1] - minFloat[1]) + random_float[0,1) );
 temp[2] = SATURATED_CLIP_0_to_255( 255.0f * ( srcPixel[2] - minFloat[2] ) / (maxFloat[2] - minFloat[2]) + random_float[0,1) );
 temp[3] = SATURATED_CLIP_0_to_255( 255.0f * ( srcPixel[3] - minFloat[3] ) / (maxFloat[3] - minFloat[3]) + random_float[0,1) );
 
 // place in requested output order
 Pixel_8888 result;
 result[0] = temp[permuteMap[0]];
 result[1] = temp[permuteMap[1]];
 result[2] = temp[permuteMap[2]];
 result[3] = temp[permuteMap[3]];
 @endcode
 
 The \p dither parameter must be one of the following flags:
 \p kvImageConvert_DitherNone Same as vImageConvert_PlanarFtoPlanar8(). Rounds to nearest.
 
 \p kvImageConvert_DitherOrdered Pre-computed blue noise is added to the image before rounding to the values in
 the destination format.  The offset into this blue noise is randomized per-call to avoid visible artifacts
 if you do your own tiling or call the function on sequential frames of video.
 
 \p kvImageConvert_DitherOrderedReproducible Pre-computed blue noise is added to the image before rounding to the
 values in the destination format.  The offset into the blue noise is the same for every call to allow users
 to get reproducible results. Fine for still images. For video kvImageConvert_DitherOrdered is a better choice.
 
 The ordered dither methods may be further influenced by shaping the distribution of the noise using the gaussian and uniform options below.
 These options are OR-ed with kvImageConvert_DitherOrdered / kvImageConvert_DitherOrderedReproducible:
 
 \p kvImageConvert_OrderedGaussianBlue When using an ordered dither pattern, distribute the noise according to a gaussian
 distribution. This generally gives more pleasing images --  less noisy and perhaps a little more saturated -- but color
 fidelity can suffer. Its effect is between kvImageConvert_DitherNone and kvImageConvert_DitherOrdered | kvImageConvert_DitherUniform.
 This is the default for kvImageConvert_DitherOrdered and kvImageConvert_DitherOrderedReproducible.
 
 \p kvImageConvert_OrderedUniformBlue When using an ordered dither pattern, distribute the noise uniformly. This generally gives
 best color fidelity, but the resulting image is noisier and more obviously dithered. This is usually the best choice when low
 bitdepth content is drawn next to high bitdepth content and in other circumstances where subtle changes to color arising from the conversion
 could be easily noticed. It may be a poor choice when the image is likely to be enlarged -- this would cause the noise to become
 more evident-- and for very flat / synthetic content with little inherent noise. The enlargement problem may be avoided by enlarging
 first at high bitdepth, then convert to lower bitdepth.
 
 @note "Blue" noise does not look blue, nor does it operate solely on the blue color channel. Blue noise is monochrome noise that is added to all color
 channels equally. The name arises from blue light, which has a higher frequency than other colors of visible light. Thus, blue noise is noise which is
 weighted heavily towards high frequencies. Low frequency noise tends to have visible shapes in it that would become apparent in an image if it was added in,
 so it is excluded from the dither pattern.
 
 @note This function will work for other channel orders, such as RGBA and BGRA.
 
 @note This function can work in place provided the following are true:
 If src overlaps with dest, src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes
 If an overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param src         A pointer to a valid and initialized vImage_Buffer struct that points to a buffer containing the source pixels.
 
 @param dest        A pointer to a valid and initialized vImage_Buffer struct that points to a allocated buffer to receive the result pixels.
 
 @param maxFloat    The encoding for 1.0 in the src buffer, full intensity.
 Typically, this is 1.0 for floating-point data in the range[0,1]
 but if your data is [0,65535] then you would pass 65535.0f here.
 A separate value is provided for each of the three channels.
 
 @param minFloat    The encoding for 0.0 in the src buffer, no light.
 Typically this is 0.0 for floating-point data in the range [0,1],
 but if your data is [-.5,0.5] then you would pass -0.5f here.
 A separate value is provided for each of the three channels.
 
 @param dither      The type of random noise to use for the dither. See discussion for more details.
 
 @param permuteMap  A 4 element array giving the order of the result channels.
 This allows you to convert a ARGB float buffer to a BGRA result
 buffer by providing the order {3,2,1,0}.
 
 @param flags                   The following flags are honored:
 \p kvImageNoFlags              Default operation.
 \p kvImageDoNotTile            Disable internal multithreading, if any.
 \p kvImageGetTempBufferSize    Returns 0. Does no work. Does not touch data.
 
 @return \p kvImageNoError                      Success
 @return \p kvImageRoiLargerThanInputBuffer     The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 @return \p kvImageUnknownFlagsBit              Not all vImage flags are understood by this function. See description of flags parameter for supported flags.
 @return \p kvImageInvalidParameter             An unknown / unsupported dithering mode was requested.
 
 @seealso vImageConvert_RGBFFFtoRGB888
 @seealso vImagePermuteChannels_RGB888
 */
VIMAGE_PF vImage_Error vImageConvert_ARGBFFFFtoARGB8888_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, int dither, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4)    API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_Planar8toARGB8888
 
 @abstract Interleave 4 planar 8 bit integer buffers to make an interleaved 4 channel ARGB8888 buffer.
 
 @discussion For each pixel in { srcA, srcR, srcG, srcB }, do the following:
 @code
 Pixel_88888 result = { pixelFromSrcA, pixelFromSrcR, pixelFromSrcG, pixelFromSrcB };
 @endcode
 
 This function may be used to create other channel orderings such as RGBA8888 by passing in the planar8 images in the alternate order.
 
 @param srcA
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing A source pixels.
 
 @param srcR
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing R source pixels.
 
 @param srcG
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing G source pixels.
 
 @param srcB
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing B source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a allocated buffer to receive the result pixels.
 
 @param flags
 \p kvImageNoFlags      Default operation
 \p kvImageDoNotTile    Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @note Does not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_Planar8toARGB8888(const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_PlanarFtoARGBFFFF
 
 @abstract Interleave 4 planar floating point buffers to make an interleaved 4 channel ARGBFFFF buffer.
 
 @discussion For each pixel in { srcA, srcR, srcG, srcB }, do the following:
 @code
 Pixel_FFFF result = { pixelFromSrcA, pixelFromSrcR, pixelFromSrcG, pixelFromSrcB };
 @endcode
 
 This function may be used to create other channel orderings such as RGBAFFFF by passing in the planar8 images in the alternate order.
 
 @param srcA
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing A source pixels.
 
 @param srcR
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing R source pixels.
 
 @param srcG
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing G source pixels.
 
 @param srcB
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing B source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a allocated buffer to receive the result pixels.
 
 @param flags
 \p kvImageNoFlags      Default operation
 \p kvImageDoNotTile    Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @note Does not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_PlanarFtoARGBFFFF(const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));

#define vImageConvert_PlanarFtoRGBAFFFF(_red, _green, _blue, _alpha, _dest, _flags) \
vImageConvert_PlanarFtoARGBFFFF((_red), (_green), (_blue), (_alpha), (_dest), (_flags))
#define vImageConvert_PlanarFtoBGRAFFFF(_blue, _green, _red, _alpha, _dest, _flags) \
vImageConvert_PlanarFtoARGBFFFF((_blue), (_green), (_red), (_alpha), (_dest), (_flags))

/*!
 @function vImageConvert_ARGB8888toPlanar8
 
 @abstract Deinterleave an ARGB8888 interleaved vImage_Buffer to form 4 planar 8-bit integer buffers.
 
 @discussion For each pixel in srcARGB, do the following:
 @code
 Pixel_8 destAResult = srcARGBPixel[0];
 Pixel_8 destRResult = srcARGBPixel[1];
 Pixel_8 destGResult = srcARGBPixel[2];
 Pixel_8 destBResult = srcARGBPixel[3];
 @endcode
 
 This function may be used to deinterleave other channel orderings such as RGBA8888 by passing in the planar8 images in the alternate order.
 
 @param srcARGB
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixels.
 
 @param destA
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing A destination pixels.
 
 @param destR
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing R destination pixels.
 
 @param destG
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing G destination pixels.
 
 @param destB
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing B destination pixels.
 
 @param flags
 \p kvImageNoFlags      Default operation
 \p kvImageDoNotTile    Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @note Does not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB8888toPlanar8(const vImage_Buffer *srcARGB, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5)   API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));
#define vImageConvert_RGBA8888toPlanar8(_src, _red, _green, _blue, _alpha, _flags) \
vImageConvert_ARGB8888toPlanar8((_src), (_red), (_green), (_blue), (_alpha), (_flags))
#define vImageConvert_BGRA8888toPlanar8(_src, _blue, _green, _red, _alpha, _flags) \
vImageConvert_ARGB8888toPlanar8((_src), (_blue), (_green), (_red), (_alpha), (_flags))

/*!
 @function vImageConvert_ARGBFFFFtoPlanarF
 
 @abstract Deinterleave an ARGBFFFF interleaved vImage_Buffer to form 4 planar floating point buffers.
 
 @discussion For each pixel in srcARGB, do the following:
 @code
 Pixel_F destAResult = srcARGBPixel[0];
 Pixel_F destRResult = srcARGBPixel[1];
 Pixel_F destGResult = srcARGBPixel[2];
 Pixel_F destBResult = srcARGBPixel[3];
 @endcode
 
 This function may be used to deinterleave other channel orderings such as RGBAFFFF by passing in the planar8 images in the alternate order.
 
 @param srcARGB
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixels.
 
 @param destA
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing A destination pixels.
 
 @param destR
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing R destination pixels.
 
 @param destG
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing G destination pixels.
 
 @param destB
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing B destination pixels.
 
 @param flags
 \p kvImageNoFlags      Default operation
 \p kvImageDoNotTile    Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @note Does not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_ARGBFFFFtoPlanarF(const vImage_Buffer *srcARGB, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));
#define vImageConvert_RGBAFFFFtoPlanarF(_src, _red, _green, _blue, _alpha, _flags) \
vImageConvert_ARGBFFFFtoPlanarF((_src), (_red), (_green), (_blue), (_alpha), (_flags))
#define vImageConvert_BGRAFFFFtoPlanarF(_src, _blue, _green, _red, _alpha, _flags) \
vImageConvert_ARGBFFFFtoPlanarF((_src), (_blue), (_green), (_red), (_alpha), (_flags))

/*
 vImageConvert_ChunkyToPlanar8
 vImageConvert_PlanarToChunky8
 vImageConvert_ChunkyToPlanarF
 vImageConvert_PlanarToChunkyF
 
 These functions convert between nearly arbitrary interleaved data formats that vImage
 doesn't support to/from planar data formats that it does support.
 N planar arrays are interleaved to make (or are made made by deinterleaving)
 a N channel packed interleaved buffer with pixels that are {srcStrideBytes, destStrideBytes}
 bytes in size. Valid data channels are assumed to be at the front of each interleaved pixel.
 
 Will not work in place
 
 Performance advisory:
 =====================
 These functions are too flexible to vectorize every case. When appropriate, it is suggested you use the other
 special purpose conversion functions. If you know what your data formats are ahead of time, it is
 likely you can write your own special purpose conversion function that is faster, even in scalar code.
 These functions are provided as a convenience.
 */
VIMAGE_PF vImage_Error vImageConvert_ChunkyToPlanar8( const void *srcChannels[], const vImage_Buffer *destPlanarBuffers[], unsigned int channelCount, size_t srcStrideBytes, vImagePixelCount srcWidth, vImagePixelCount srcHeight, size_t srcRowBytes, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error vImageConvert_PlanarToChunky8( const vImage_Buffer *srcPlanarBuffers[], void *destChannels[], unsigned int channelCount, size_t destStrideBytes, vImagePixelCount destWidth, vImagePixelCount destHeight, size_t destRowBytes, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error vImageConvert_ChunkyToPlanarF( const void *srcChannels[], const vImage_Buffer *destPlanarBuffers[], unsigned int channelCount, size_t srcStrideBytes, vImagePixelCount srcWidth, vImagePixelCount srcHeight, size_t srcRowBytes, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error vImageConvert_PlanarToChunkyF( const vImage_Buffer *srcPlanarBuffers[], void *destChannels[], unsigned int channelCount, size_t destStrideBytes, vImagePixelCount destWidth, vImagePixelCount destHeight, size_t destRowBytes, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_16SToF
 
 @abstract Convert a planar vImage_Buffer of 16 bit signed integers to a buffer containing floating point values.
 
 @discussion For each 16 bit pixel in src, do the following:
 @code
 float result = (float) srcPixel * scale + offset;
 @endcode
 
 To convert 4 channel interleaved signed 16 bit data to ARGBFFFF, simply multiply the vImage_Buffer.width by 4.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param scale
 A scale value in the conversion.
 
 @param offset
 A offset value in the conversion.
 
 @param flags
 \p kvImageNoFlags                     Default operation
 \p kvImageDoNotTile                   Disable internal multithreading.
 
 @return kvImageNoError                       Success
 @return kvImageRoiLargerThanInputBuffer      The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @note Does not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_16SToF( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_16UToF
 
 @abstract Convert a planar vImage_Buffer of 16 bit unsigned integers to a buffer containing floating point values.
 
 @discussion For each 16 bit pixel in src, do the following:
 @code
 float result = (float) srcPixel * scale + offset;
 @endcode
 
 To convert 4 channel interleaved signed 16 bit data to ARGBFFFF, simply multiply the vImage_Buffer.width by 4.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param scale
 A scale value in the conversion.
 
 @param offset
 A offset value in the conversion.
 
 @param flags
 \p kvImageNoFlags                     Default operation
 \p kvImageDoNotTile                   Disable internal multithreading.
 
 @return kvImageNoError                       Success
 @return kvImageRoiLargerThanInputBuffer      The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @note Does not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_16UToF( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_FTo16S
 
 @abstract Convert a planar vImage_Buffer of floating point values to a buffer of 16 bit signed integers.
 
 @discussion For each floating point pixel in src, do the following:
 @code
 int16_t result = SATURATED_CLIP_SHRT_MIN_to_SHRT_MAX( (srcPixel - offset) / scale  + 0.5f);
 @endcode
 
 Programmer's note:
 The scale and offset here are designed to be the same offset and scale used for the vImageConvert_16SToF conversion.
 For a lossless round trip (within the limits of floating point precision), use the same scale and offset values
 in both directions:
 
 vImageConvert_16SToF( int16_buffer, float_buffer, myOffset, myScale, kvImageNoFlags );   //Convert to float
 vImageConvert_FTo16S( float_buffer, int16_buffer, myOffset, myScale, kvImageNoFlags );   //Convert back to int16_t
 
 @note Works in place, as long as src->data == dest->data and src->rowBytes == dest->rowBytes.
 @note To convert multichannel interleaved floating point formats (e.g. ARGBFFFF) to a multichannel 16-bit image format with the same channel ordering, simply multiply the vImage_Buffer.width by the number of channels.
 
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param scale             A scale value in the conversion.
 
 @param offset            A offset value in the conversion.
 
 @param flags
 \p kvImageNoFlags                     Default operation
 \p kvImageDoNotTile                   Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageConvert_FTo16S( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_FTo16U
 
 @abstract Convert a planar vImage_Buffer of floating point values to a buffer of 16 bit unsigned integers.
 
 @discussion For each floating point pixel in src, do the following:
 @code
 uint16_t result = SATURATED_CLIP_0_to_USHRT_MAX( (srcPixel - offset) / scale  + 0.5f);
 @endcode
 
 Programmer's note:
 The scale and offset here are designed to be the same offset and scale used for the vImageConvert_16UToF conversion.
 For a lossless round trip (within the limits of floating point precision), use the same scale and offset values
 in both directions:
 
 vImageConvert_16UToF( int16_buffer, float_buffer, myOffset, myScale, kvImageNoFlags );   //Convert to float
 vImageConvert_FTo16U( float_buffer, int16_buffer, myOffset, myScale, kvImageNoFlags );   //Convert back to uint16_t
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param scale             A scale value in the conversion.
 
 @param offset            A offset value in the conversion.
 
 @param flags
 \p kvImageNoFlags                     Default operation.
 \p kvImageDoNotTile                   Disable internal multithreading.
 
 @return kvImageNoError                     Success.
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @note Works in place, as long as src->data == dest->data and src->rowBytes == dest->rowBytes.
 
 @note To convert multichannel interleaved floating point formats (e.g. ARGBFFFF) to a multichannel 16-bit image format with the same channel ordering, simply multiply the vImage_Buffer.width by the number of channels.
 */
VIMAGE_PF vImage_Error vImageConvert_FTo16U( const vImage_Buffer *src, const vImage_Buffer *dest, float offset, float scale, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));


/*!
 @function vImageConvert_16Uto16F
 
 @abstract Convert from 16 bit unsigned integer to 16 bit float format.
 
 @discussion For each floating point pixel in src, do the following:
 @code
 destPixel[x] = ConvertToPlanar16F(srcPixel[x]);
 @endcode
 
 The 16 bit floating point format is half-precision floating point
 (a.k.a.  IEEE-754 binary16, OpenCL half, GL_ARB_half_float_pixel, OpenEXR half).
 It has a layout as follows:
 
 16 bits:  seeeeemmmmmmmmmm
 
 1-bit sign | 5 bits of exponent, with a bias of 15 | 10 bits of significand
 (with 11 bits of significance due to the implicit 1 bit)
 
 NaNs, Infinities and denormals are supported.
 Per IEEE-754, all signaling NaNs are quieted during the conversion. (OpenEXR-1.2.1 converts SNaNs to SNaNs.)
 To set/inspect the current IEEE-754 rounding mode, please see appropriate utilities in fenv.h.
 
 @param src
 A pointer to a vImage_Buffer that references the source pixels.
 
 @param dest
 A pointer to a vImage_Buffer that references the destination pixels.
 
 @param flags
 \p kvImageDoNotTile    Turns off internal multithreading.
 
 @return \p kvImageNoError                      Success!
 @return \p kvImageRoiLargerThanInputBuffer     The source buffer must have a height and
 width at least as large as the destination buffer.
 @return \p kvImageNullPointerArgument          src or dest pointer is NULL.
 @return \p kvImageUnknownFlagsBit              Unknown flag was passed.
 
 @note This routine will work in place provided that src.data == dest.data
 and src.rowBytes >= dest.rowBytes. However, when src.rowBytes > dest.rowBytes
 in-place will only work if you pass kvImageDoNotTile.
 
 @note To use this with interleaved data, multiply vImage_Buffer.width by 4.
 */
VIMAGE_PF vImage_Error vImageConvert_16Uto16F( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )
VIMAGE_NON_NULL(1,2)  API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageConvert_16Fto16U
 
 @abstract Convert from 16 bit float to 16 bit unsigned integer format.
 
 @discussion For each floating point pixel in src, do the following:
 @code
 destPixel[x] = ConvertToPlanar16U(srcPixel[x]);
 @endcode
 
 The 16 bit floating point format is half-precision floating point
 (a.k.a.  IEEE-754 binary16, OpenCL half, GL_ARB_half_float_pixel, OpenEXR half).
 It has a layout as follows:
 
 16 bits:  seeeeemmmmmmmmmm
 
 1-bit sign | 5 bits of exponent, with a bias of 15 | 10 bits of significand
 (with 11 bits of significance due to the implicit 1 bit)
 
 NaNs, Infinities and denormals are supported.
 Per IEEE-754, all signaling NaNs are quieted during the conversion. (OpenEXR-1.2.1 converts SNaNs to SNaNs.)
 To set/inspect the current IEEE-754 rounding mode, please see appropriate utilities in fenv.h
 
 @param src
 A pointer to a vImage_Buffer that references the source pixels.
 
 @param dest
 A pointer to a vImage_Buffer that references the destination pixels.
 
 @param flags
 \p kvImageDoNotTile    Turns off internal multithreading.
 
 @return \p kvImageNoError              Success!
 @return \p kvImageRoiLargerThanInputBuffer   The source buffer must have a height and
 width at least as large as the destination buffer.
 @return \p kvImageNullPointerArgument  src or dest pointer is NULL.
 @return \p kvImageUnknownFlagsBit      Unknown flag was passed.
 
 @note This routine will work in place provided that src.data == dest.data
 and src.rowBytes >= dest.rowBytes. However, when src.rowBytes > dest.rowBytes
 in-place will only work if you pass kvImageDoNotTile.
 
 @note To use this with interleaved data, multiply vImage_Buffer.width by 4
 */
VIMAGE_PF vImage_Error vImageConvert_16Fto16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )
VIMAGE_NON_NULL(1,2)  API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


/*!
 @function vImageConvert_12UTo16U
 
 @abstract Converts 12U to 16U
 
 @discussion For each floating point pixel in src, do the following:
 @code
 uint8_t *srcRow = srcData;
 uint16_t *destRow = destData;
 
 //Load 2 12-bit values
 t0 = (srcRow[0] << 16) | (srcRow[1] << 8) | srcRow [2];
 srcRow += 3;
 
 //Separate each of 12-bit
 t1 = t0 & 0xfff;
 t0 >>= 12;
 
 //Convert and store
 destRow[0] = (t0 * 65535U + (t0 << 4) + 2055U) >> 12;
 destRow[1] = (t1 * 65535U + (t1 << 4) + 2055U) >> 12;
 destRow += 2;
 @endcode
 
 @param src
 A pointer to a vImage_Buffer that references 12-bit source pixels
 
 @param dest
 A pointer to a vImage_Buffer that references 16-bit destination pixels.
 
 @param flags
 \p kvImageDoNotTile    Turns off internal multithreading.
 
 @return \p kvImageNoError                      Success!
 @return \p kvImageRoiLargerThanInputBuffer     The source buffer must have a height and
 width at least as large as the destination buffer.
 @return \p kvImageNullPointerArgument          src, dest or table pointer is NULL.
 
 @note This routine will not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_12UTo16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageConvert_16UTo12U
 
 @abstract Converts 16U to 12U
 
 @discussion For each floating point pixel in src, do the following:
 @code
 uint16_t *srcRow = srcData;
 uint8_t *destRow = destData;
 
 // 2 16-bit in 4-bytes
 t0 = srcRow[0];
 t1 = srcRow[1];
 srcRow += 2;
 
 t0 = (t0 * 4095 + 32767 + (t0 >> 4)) >> 16;
 t1 = (t1 * 4095 + 32767 + (t1 >> 4)) >> 16;
 
 t0 <<= 12;
 t0 |= t1;
 
 // 2 12-bit in 3-bytes
 destRow[0] = t0 >> 16;
 destRow[1] = t0 >> 8;
 destRow[2] = t0;
 destRow += 3;
 @endcode
 
 @param src
 A pointer to a vImage_Buffer that references 12-bit source pixels
 
 @param dest
 A pointer to a vImage_Buffer that references 16-bit destination pixels.
 
 @param flags
 \p kvImageDoNotTile         Turns off internal multithreading.
 
 @return \p kvImageNoError                      Success!
 @return \p kvImageRoiLargerThanInputBuffer     The source buffer must have a height and
 width at least as large as the destination buffer.
 @return \p kvImageNullPointerArgument          src, dest or table pointer is NULL.
 
 @note This routine will not work in place.
 
 */
VIMAGE_PF vImage_Error vImageConvert_16UTo12U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageTableLookUp_ARGB8888
 
 @abstract Transforms an ARGB8888 image by substituting pixel values with pixel values provided by four lookup tables.
 
 @discussion For each pixel in src, do the following:
 Use a lookup table to remap 0...255 values in the source image to a different set of 0...255 values in the destination.
 A different lookup table is used for each channel in the ARGB image.
 
 This function can work in place provided the following are true:
 If src overlaps with dest, src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes
 If an overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @note This function may be used to do table lookups on other 4 channel 8-bit/channel formats (e.g. RGBA8888) by adjusting the order of the tables
 passed into the function accordingly.
 
 @note Performance Advisory:   For 8-bit monochrome -> ARGB8888  or 8-bit indexed -> ARGB8888 conversions,
 it is likely significantly faster to use vImageLookupTable_Planar8toPlanarF. Use the desired
 ARGB8888 (32 bits/pixel) pixels in place of the planar 32-bit floats in the lookup table.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param alphaTable
 A table to remap A values.
 
 @param redTable
 A table to remap R values.
 
 @param greenTable
 A table to remap G values.
 
 @param blueTable
 A table to remap B values.
 
 @param flags
 \p kvImageNoFlags                     Default operation
 \p kvImageDoNotTile                   Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageTableLookUp_ARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 alphaTable[256], const Pixel_8 redTable[256], const  Pixel_8 greenTable[256], const  Pixel_8 blueTable[256], vImage_Flags flags) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageTableLookUp_ARGB8888
 
 @abstract Transforms an Planar8 image by substituting pixel values with pixel values provided by four lookup tables.
 
 @discussion For each pixel in src, do the following:
 Use a lookup table to remap 0...255 values in the source image to a different set of 0...255 values in the destination.
 
 This function can work in place provided the following are true:
 If src overlaps with dest, src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes
 If an overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param table
 A table to remap the values in src.
 
 @param flags
 \p kvImageNoFlags                     Default operation
 \p kvImageDoNotTile                   Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageTableLookUp_Planar8(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 table[256], vImage_Flags flags)  VIMAGE_NON_NULL(1,2,3)   API_AVAILABLE(macos(10.3), ios(5.0), watchos(1.0), tvos(5.0));

/*
 Additional Lookup table functions are available in Transform.h :
 vImageLookupTable_Planar8toPlanar16,
 vImageLookupTable_Planar8toPlanarF,
 vImageLookupTable_8to64U,
 vImageLookupTable_PlanarFtoPlanar8
 */

/*!
 @function vImageOverwriteChannels_ARGB8888
 
 @abstract Overwrites one or more planes of an ARGB8888 image buffer with the provided planar buffer.
 
 @discussion For each pixel in src, do the following:
 @code
 // Set up a uint32_t mask - 0xFF where the pixels should be conserved
 // Load and splat the src pixel
 uint32_t srcPixel = newSrc->data[x];
 uint32_t result = origSrc->data[x];
 srcPixel |= srcPixel << 8;
 srcPixel |= srcPixel << 16;
 
 // Select for the channels based on the mask
 srcPixel &= ~mask;
 result &= mask;
 
 // combine the two and store
 dest->data[x] = srcPixel | result;
 @endcode
 
 origSrc and dest may overlap, if they share the same origin.
 origSrc should be at least as big as dest
 
 origSrc and dest can be the same buffer
 This function may be used with other channel orderings (e.g. origSrc -> a RGBA8888 buffer) by adjusting the order of the bits in the copyMask.
 
 This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data.
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags.
 
 @param newSrc
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing planar source pixel that we will overwrite with.
 
 @param origSrc
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixel that we will overwrite into.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageOverwriteChannels_ARGB8888(    const vImage_Buffer *newSrc,       /* A planar buffer */
                                                        const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                        const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                        uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                        vImage_Flags    flags ) VIMAGE_NON_NULL(1,2,3)        API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageOverwriteChannels_ARGBFFFF
 
 @abstract Overwrites one or more planes of an ARGBFFFF image buffer with the provided planar buffer.
 
 @discussion For each pixel in src, do the following:
 @code
 // Set up a uint32_t mask for which channels to use -1U where the pixels should not be conserved
 uint32_t    a = origSrc->data[0] & maskA;
 uint32_t    r = origSrc->data[1] & maskR;
 uint32_t    g = origSrc->data[2] & maskG;
 uint32_t    b = origSrc->data[3] & maskB;
 uint32_t    colorA = newSrc->data[0];
 uint32_t    colorR = colorA & ~maskR;
 uint32_t    colorG = colorA & ~maskG;
 uint32_t    colorB = colorA & ~maskB;
 colorA &= ~maskA;
 
 dest->data[0] = colorA | a;
 dest->data[1] = colorR | r;
 dest->data[2] = colorG | g;
 dest->data[3] = colorB | b;
 @endcode
 
 origSrc and dest may overlap, if they share the same origin.
 origSrc should be at least as big as dest
 
 origSrc and dest can be the same buffer
 This function may be used with other channel orderings (e.g. origSrc -> a RGBAFFFF buffer) by adjusting the order of the bits in the copyMask.
 
 This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data.
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags.
 
 @param newSrc
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing planar source pixel that we will overwrite with.
 
 @param origSrc
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixel that we will overwrite into.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageOverwriteChannels_ARGBFFFF(    const vImage_Buffer *newSrc,       /* A planar buffer */
                                                        const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                        const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                        uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                        vImage_Flags    flags ) VIMAGE_NON_NULL(1,2,3)        API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageOverwriteChannelsWithScalar_Planar8
 
 @abstract Fill the dest buffer with the scalar value.
 
 @param scalar
 A scalar value to fill the destination buffer.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageOverwriteChannelsWithScalar_Planar8(    Pixel_8     scalar,
                                                                 const vImage_Buffer *dest,      /* A planar buffer */
                                                                 vImage_Flags    flags ) VIMAGE_NON_NULL(2)        API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageOverwriteChannelsWithScalar_PlanarF
 
 @abstract Fill the dest buffer with the scalar value.
 
 @param scalar
 A scalar value to fill the destination buffer.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageOverwriteChannelsWithScalar_PlanarF( Pixel_F     scalar,
                                                                 const vImage_Buffer *dest,      /* A planar buffer */
                                                                 vImage_Flags    flags ) VIMAGE_NON_NULL(2)        API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageOverwriteChannelsWithScalar_Planar16S
 
 @abstract Fill the dest buffer with the scalar value.
 
 @param scalar
 A scalar value to fill the destination buffer.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageOverwriteChannelsWithScalar_Planar16S(    Pixel_16S     scalar,
                                                                   const vImage_Buffer *dest,      /* A planar buffer */
                                                                   vImage_Flags    flags ) VIMAGE_NON_NULL(2)        API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageOverwriteChannelsWithScalar_Planar16U
 
 @abstract Fill the dest buffer with the scalar value.
 
 @param scalar
 A scalar value to fill the destination buffer.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageOverwriteChannelsWithScalar_Planar16U(    Pixel_16U     scalar,
                                                                   const vImage_Buffer *dest,      /* A planar buffer */
                                                                   vImage_Flags    flags ) VIMAGE_NON_NULL(2)        API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*!
 @function vImageExtractChannel_ARGB8888
 
 @abstract Extract one channel from a 4-channel interleaved 8-bit per component buffer
 
 @discussion  This is the opposite operation from vImageOverwriteChannels_ARGB8888. It reads one component
 from the four channel 8-bit per component buffer and writes it into a Planar8 buffer.
 
 For each pixel i in src:
 @code
 Pixel_8888 *src_pixel;
 Pixel_8 *dest_pixel;
 
 dest_pixel[i] = src_pixel[i][channelIndex];
 @endcode
 
 @param src
 A valid pointer to a vImage_Buffer struct which describes a 8-bit per component, four channel buffer.
 It does not have to be ARGB8888. It can be BGRA, RGBA, CMYK, etc.
 
 @param dest
 A valid pointer to a vImage_Buffer struct which describes a 8-bit per component, one channel buffer.
 The buffer pointed to by dest should be allocated by you. It will be overwritten with one of the
 channels.  This function does work in place, so long as the rowBytes is the same for src and dest
 images and the start address also matches.
 
 @param channelIndex
 The index of the channel to extract. For alpha in a ARGB image, this is 0.  For alpha in a BGRA image, this is 3.
 
 @param flags
 \p kvImageDoNotTile
 \p kvImageGetTempBufferSize
 \p kvImagePrintDiagnosticsToConsole
 
 @return \p kvImageNoError                      Success. However, see also 0 below, if the kvImageGetTempBufferSize flag is passed.
 @return \p 0                                   If the kvImageGetTempBufferSize flag is passed, this function returns 0 and does no work.
 @return \p kvImageRoiLargerThanInputBuffer     The destination height or width is larger than the src height or width, respectively.
 @return \p kvImageUnknownFlagsBit              A flag was used which was not among the approved set of flags. See flags param description above.
 @return \p kvImageInvalidParameter             channelIndex must be in the range [0,3]
 */
VIMAGE_PF vImage_Error vImageExtractChannel_ARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, long channelIndex, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageExtractChannel_ARGB16U
 
 @abstract Extract one channel from a 4-channel interleaved 16-bit per component buffer.
 
 @discussion  vImageExtractChannel_ARGB16U reads one component from the four channel 16-bit per component buffer
 and writes it into a Planar16U buffer.  Since this just copies data around, the data may be any
 16-bit per component data type, including signed 16 bit integers and half-precision floating point,
 of any endianness. Likewise, the channel order does not need to be ARGB. RGBA, BGRA, CMYK, etc. all work.
 
 For each pixel i in src:
 @code
 Pixel_ARGB_16U *src_pixel;
 Pixel_16U *dest_pixel;
 
 dest_pixel[i] = src_pixel[i][channelIndex];
 @endcode
 
 @param src
 A valid pointer to a vImage_Buffer struct which describes a 16-bit per component, four channel buffer.
 It does not have to be ARGB16U. It can be BGRA, RGBA, CMYK, etc. The data can be any 16-bit per component
 type such as int16_t or half-precision floating-point. Data must be at least 2-byte aligned.
 
 @param dest
 A valid pointer to a vImage_Buffer struct which describes a 16-bit per component, one channel buffer.
 The buffer pointed to by dest should be allocated by you. It will be overwritten with one of the
 channels.  This function does work in place, so long as the rowBytes is the same for src and dest
 images and the start address also matches. The data returned will be in the same format (uint16_t,
 int16_t, half-float, etc.) as the data provided in the src format, except that only a single channel
 is present. Data must be at least 2-byte aligned.
 
 @param channelIndex
 The index of the channel to extract. For alpha in a ARGB image, this is 0.  For alpha in a BGRA image, this is 3.
 
 @param flags
 The following flags are allowed:  kvImageDoNotTile, kvImageGetTempBufferSize, kvImageNoFlags, kvImagePrintDiagnosticsToConsole
 
 @result kvImageNoError                     Success. However, see also 0 below, if the kvImageGetTempBufferSize flag is passed.
 @result 0                                  If the kvImageGetTempBufferSize flag is passed, this function returns 0 and does no work.
 @result kvImageRoiLargerThanInputBuffer    The destination height or width is larger than the src height or width, respectively.
 @result kvImageUnknownFlagsBit             A flag was used which was not among the approved set of flags. See flags param description above.
 @result kvImageInvalidParameter            channelIndex must be in the range [0,3]
 */
VIMAGE_PF vImage_Error vImageExtractChannel_ARGB16U( const vImage_Buffer *src, const vImage_Buffer *dest, long channelIndex, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageExtractChannel_ARGBFFFF
 
 @abstract Extract one channel from a 4-channel interleaved 32-bit per component buffer
 
 @discussion  This is the opposite operation from vImageOverwriteChannels_ARGBFFFF. It reads one component
 from the four channel 32-bit per component buffer and writes it into a PlanarF buffer. NaNs and
 and sNaNs are not modified. Sign of zero shall be preserved.
 
 For each pixel i in src:
 @code
 Pixel_FFFF *src_pixel;
 Pixel_F *dest_pixel;
 
 dest_pixel[i] = src_pixel[i][channelIndex];
 @endcode
 
 @param src
 A valid pointer to a vImage_Buffer struct which describes a 32-bit per component, four channel buffer.
 It does not have to be ARGBFFFF. It can be BGRA, RGBA, CMYK, etc. of any endianness. Data must be at
 least 4-byte aligned.
 
 @param dest
 A valid pointer to a vImage_Buffer struct which describes a 32-bit per component, one channel buffer.
 The buffer pointed to by dest should be allocated by you. It will be overwritten with one of the
 channels.  This function does work in place, so long as the rowBytes is the same for src and dest
 images and the start address also matches. Data must be at least 4 byte aligned.
 
 @param channelIndex
 The index of the channel to extract. For alpha in a ARGB image, this is 0.  For alpha in a BGRA image, this is 3.
 
 @param flags
 The following flags are allowed:  kvImageDoNotTile, kvImageGetTempBufferSize, kvImageNoFlags, kvImagePrintDiagnosticsToConsole
 
 @result kvImageNoError                     Success. However, see also 0 below, if the kvImageGetTempBufferSize flag is passed.
 @result 0                                  If the kvImageGetTempBufferSize flag is passed, this function returns 0 and does no work.
 @result kvImageRoiLargerThanInputBuffer    The destination height or width is larger than the src height or width, respectively.
 @result kvImageUnknownFlagsBit             A flag was used which was not among the approved set of flags. See flags param description above.
 @result kvImageInvalidParameter            channelIndex must be in the range [0,3]
 */
VIMAGE_PF vImage_Error vImageExtractChannel_ARGBFFFF( const vImage_Buffer *src, const vImage_Buffer *dest, long channelIndex, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*
 * Fill a buffer with a color. Use vImageOverwriteChannelsWithScalar_* to fill planar buffers with a color.
 * These functions work for any 2-channel, 4-channel 8-bit/channel, 16-bit/channel or floating-point format, such as RGBAFFFF or BGRA8888.
 */

/*!
 @function vImageBufferFill_ARGB8888
 
 @abstract Fill the dest buffer with the pixel value.
 
 @param color
 A pixel value to fill the destination buffer.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                    Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageBufferFill_ARGB8888( const vImage_Buffer *dest, const Pixel_8888 color, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageBufferFill_ARGB16U
 
 @abstract Fill the dest buffer with the pixel value.
 
 @param color
 A pixel value to fill the destination buffer.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageBufferFill_ARGB16U( const vImage_Buffer *dest, const Pixel_ARGB_16U color, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageBufferFill_ARGB16S
 
 @abstract Fill the dest buffer with the pixel value.
 
 @param color
 A pixel value to fill the destination buffer.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                    Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageBufferFill_ARGB16S( const vImage_Buffer *dest, const Pixel_ARGB_16S color, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageBufferFill_ARGBFFFF
 
 @abstract Fill the dest buffer with the pixel value.
 
 @param color
 A pixel value to fill the destination buffer.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                    Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageBufferFill_ARGBFFFF( const vImage_Buffer *dest, const Pixel_FFFF color, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageBufferFill_CbCr8
 
 @abstract Fill the dest buffer with the pixel value.
 
 @param color
 A pixel value to fill the destination buffer.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error
vImageBufferFill_CbCr8(
                       const vImage_Buffer *dest,
                       const Pixel_88 color,
                       vImage_Flags flags ) VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!
 @function vImageBufferFill_CbCr16U
 
 @abstract Fill the dest buffer with the pixel value.
 
 @param color
 A pixel value to fill the destination buffer.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error
vImageBufferFill_CbCr16U(
                         const vImage_Buffer *dest,
                         const Pixel_16U16U color,
                         vImage_Flags flags ) VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));


/*!
 @function vImageOverwriteChannelsWithScalar_ARGB8888
 
 @abstract Overwrites the pixels of one or more planes of an ARGB8888 image buffer with the provided scalar value.
 
 @discussion Fill the color channels (as indicated by copyMask) with the scalar value.
 
 For each pixel in src:
 @code
 Pixel_8888 srcPixel, destPixel;
 int mask;
 int i;
 
 mask = 0x8;
 for( i = 0; i < 4; i++ )
 {
 if( copyMask & mask )
 destPixel[i] = scalar;
 else
 destPixel[i] = srcPixel[i]
 
 mask = mask >> 1;
 }
 @endcode
 
 Bits 0-27 of copyMask must be 0.
 This function can work in place provided the following are true:
 src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes
 If overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @note These functions may be used for images with other channel orderings such as RGBA8888 by adjusting the ordering of the bits in copyMask.
 
 @param scalar
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing scalar value that we will overwrite with.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixel that we will overwrite into.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.  You should use this if you are doing your own threading / tiling.
 
 @return kvImageNoError                         Success
 @return kvImageInvalidParameter                When copyMask > 15 which is invalid.
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @seealso vImageOverwriteChannelsWithPixel_ARGB8888
 */
VIMAGE_PF vImage_Error vImageOverwriteChannelsWithScalar_ARGB8888(    Pixel_8     scalar,
                                                                  const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                                  const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                                  uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                                  vImage_Flags    flags ) VIMAGE_NON_NULL(2,3)        API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageOverwriteChannelsWithScalar_ARGBFFFF
 
 @abstract Overwrites the pixels of one or more planes of an ARGBFFFF image buffer with the provided scalar value.
 
 @discussion Fill the color channels (as indicated by copyMask) with the scalar value.
 
 For each pixel in src:
 @code
 Pixel_FFFF srcPixel, destPixel;
 int mask;
 int i;
 
 mask = 0x8;
 for( i = 0; i < 4; i++ )
 {
 if( copyMask & mask )
 destPixel[i] = scalar;
 else
 destPixel[i] = srcPixel[i]
 
 mask = mask >> 1;
 }
 @endcode
 
 Bits 0-27 of copyMask must be 0.
 This function can work in place provided the following are true:
 src->data must be equal to dest->data and src->rowBytes >= dest->rowBytes
 If overlapping src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @note These functions may be used for images with other channel orderings such as RGBAFFFF by adjusting the ordering of the bits in copyMask.
 
 @param scalar
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing scalar value that we will overwrite with.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixel that we will overwrite into.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.  You should use this if you are doing your own threading / tiling.
 
 @return kvImageNoError                         Success
 @return kvImageInvalidParameter                When copyMask > 15 which is invalid.
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @seealso vImageOverwriteChannelsWithPixel_ARGBFFFF
 */
VIMAGE_PF vImage_Error vImageOverwriteChannelsWithScalar_ARGBFFFF(    Pixel_F     scalar,
                                                                  const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                                  const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                                  uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                                  vImage_Flags    flags ) VIMAGE_NON_NULL(2,3)        API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImagePermuteChannels_ARGB8888
 
 @abstract Reorder color channels within the buffer according to the permute map.
 
 @discussion For each pixel in src, do the following:
 @code
 Pixel_8888 srcPixel, result;
 for( int i = 0; i < 4; i++ )
 result[i] = srcPixel[ permuteMap[i] ];
 @endcode
 
 The src buffer must be at least as large as the dest buffer in each dimension. (src.height >= dest.height && src.width >= dest.width)
 
 This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 This function may be used with any 4 channel 8-bit/channel format, such as RGBA8888, BGRA8888 or AYUV8888.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing the source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param permuteMap
 The map describing the permutation of the 4 color channels.
 Each value in the map must be 0,1,2, or 3.  A map of 0,1,2,3
 is a copy from src->dest while a map of 3,2,1,0 is permutes
 ARGB -> BGRA.  Providing a map value greater than 3 will
 result in the return of error kvImageInvalidParameter.
 
 @param flags
 \p kvImageNoFlags                     Default operation
 \p kvImageDoNotTile                   Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageInvalidParameter            When permuteMap > 3, which is invalid.
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImagePermuteChannels_ARGB8888(    const vImage_Buffer *src,
                                                      const vImage_Buffer *dest,
                                                      const uint8_t       permuteMap[4],
                                                      vImage_Flags        flags )    VIMAGE_NON_NULL(1,2,3)    API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImagePermuteChannels_ARGB16U
 
 @abstract Reorder color channels within the buffer according to the permute map.
 
 @discussion For each pixel in src, do the following:
 @code
 Pixel_ARGB_16U srcPixel, result;
 for( int i = 0; i < 4; i++ )
 result[i] = srcPixel[ permuteMap[i] ];
 @endcode
 
 The src buffer must be at least as large as the dest buffer in each dimension. (src.height >= dest.height && src.width >= dest.width)
 
 This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 This function may be used with any 4 channel 16-bit/channel format, such as RGBA16U, BGRA16U or AYUV16U.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing the source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param permuteMap
 The map describing the permutation of the 4 color channels.
 Each value in the map must be 0,1,2, or 3.  A map of 0,1,2,3
 is a copy from src->dest while a map of 3,2,1,0 is permutes
 ARGB -> BGRA.  Providing a map value greater than 3 will
 result in the return of error kvImageInvalidParameter.
 
 @param flags
 \p kvImageNoFlags                     Default operation
 \p kvImageDoNotTile                   Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageInvalidParameter            When permuteMap > 3, which is invalid.
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImagePermuteChannels_ARGB16U(     const vImage_Buffer *src,
                                                     const vImage_Buffer *dest,
                                                     const uint8_t       permuteMap[4],
                                                     vImage_Flags        flags )
VIMAGE_NON_NULL(1,2,3)
API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


/*!
 @function vImagePermuteChannels_ARGBFFFF
 
 @abstract Reorder color channels within the buffer according to the permute map.
 
 @discussion For each pixel in src, do the following:
 @code
 Pixel_FFFF srcPixel, result;
 for( int i = 0; i < 4; i++ )
 result[i] = srcPixel[ permuteMap[i] ];
 @endcode
 
 The src buffer must be at least as large as the dest buffer in each dimension. (src.height >= dest.height && src.width >= dest.width)
 
 This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 This function may be used with any 4 channel 32-bit/channel format, such as 16S and 16F.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing the source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param permuteMap
 The map describing the permutation of the 4 color channels.
 Each value in the map must be 0,1,2, or 3.  A map of 0,1,2,3
 is a copy from src->dest while a map of 3,2,1,0 is permutes
 ARGB -> BGRA.  Providing a map value greater than 3 will
 result in the return of error kvImageInvalidParameter.
 
 @param flags
 \p kvImageNoFlags                     Default operation
 \p kvImageDoNotTile                   Disable internal multithreading.
 
 @return kvImageNoError                     Success
 @return kvImageInvalidParameter            When permuteMap > 3, which is invalid.
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImagePermuteChannels_ARGBFFFF(    const vImage_Buffer *src,
                                                      const vImage_Buffer *dest,
                                                      const uint8_t       permuteMap[4],
                                                      vImage_Flags        flags )    VIMAGE_NON_NULL(1,2,3)
API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));



/*!
 @function vImagePermuteChannelsWithMaskedInsert_ARGB8888
 
 @discussion This is in principle vImagePermuteChannels_ARGB8888, followed by vImageOverwriteChannelsWithScalar_ARGB8888.  The fused operation is
 provided because it allows you to set different channels to different values (a weakness in vImageOverwriteChannelsWithScalar_ARGB8888)
 and because neither the Permute or Overwrite functions alone saturate the vector ALU on most architectures, so we think we can get
 the extra work done in the compound operation for free.
 
 For each pixel in src, do the following:
 @code
 Pixel_8888 srcPixel,  destPixel;
 uint8_t mask = 0x8;
 
 for( int i = 0; i < 4; i++ )
 {
 result[i] = srcPixel[ permuteMap[i] ];
 if( mask & copyMask )
 result[i] = backgroundColor[i];
 mask = mask >> 1;
 }
 @endcode
 
 If you intend to just set the entire image to just the backgroundColor, we will detect this case and reroute to vImageBufferFill_ARGB8888.
 If it isn't obvious, this will of course work with other non-ARGB channel orderings. You'll need to adjust copyMask accordingly. The
 backgroundColor should be in the output format.
 
 This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest,
 buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing the source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param permuteMap
 The map describing the permutation of the 4 color channels.
 Each value in the map must be 0,1,2, or 3.  A map of 0,1,2,3
 is a copy from src->dest while a map of 3,2,1,0 is permutes
 ARGB -> BGRA.  Providing a map value greater than 3 will
 result in the return of error kvImageInvalidParameter.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param   flags
 \p kvImageNoFlags                  Default operation
 \p kvImageDoNotTile                Disable internal multithreading.
 \p kvImageGetTempBufferSize        Does no work and returns zero, as this function does not use a temp buffer.
 
 @return kvImageNoError                     Success
 @return kvImageInvalidParameter            When permuteMap > 3 which is invalid.
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImagePermuteChannelsWithMaskedInsert_ARGB8888(    const vImage_Buffer *src,
                                                                      const vImage_Buffer *dest,
                                                                      const uint8_t permuteMap[4],
                                                                      uint8_t copyMask, /* Copy backgroundColor into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                                      const Pixel_8888 backgroundColor,
                                                                      vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImagePermuteChannelsWithMaskedInsert_ARGB16U
 
 @discussion This is in principle vImagePermuteChannels_ARGB16U, followed by vImageOverwriteChannelsWithScalar_ARGB16U.  The fused operation is
 provided because it allows you to set different channels to different values (a weakness in vImageOverwriteChannelsWithScalar_ARGB16U)
 and because neither the Permute or Overwrite functions alone saturate the vector ALU on most architectures, so we think we can get
 the extra work done in the compound operation for free.
 
 For each pixel in src, do the following:
 @code
 Pixel_ARGB_16U srcPixel,  destPixel;
 uint8_t mask = 0x8;
 
 for( int i = 0; i < 4; i++ )
 {
 result[i] = srcPixel[ permuteMap[i] ];
 if( mask & copyMask )
 result[i] = backgroundColor[i];
 mask = mask >> 1;
 }
 @endcode
 
 If you intend to just set the entire image to just the backgroundColor, we will detect this case and reroute to vImageBufferFill_ARGB16U.
 If it isn't obvious, this will of course work with other non-ARGB channel orderings. You'll need to adjust copyMask accordingly. The
 backgroundColor should be in the output format.
 
 This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest,
 buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing the source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param permuteMap
 The map describing the permutation of the 4 color channels.
 Each value in the map must be 0,1,2, or 3.  A map of 0,1,2,3
 is a copy from src->dest while a map of 3,2,1,0 is permutes
 ARGB -> BGRA.  Providing a map value greater than 3 will
 result in the return of error kvImageInvalidParameter.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param   flags
 \p kvImageNoFlags                  Default operation
 \p kvImageDoNotTile                Disable internal multithreading.
 \p kvImageGetTempBufferSize        Does no work and returns zero, as this function does not use a temp buffer.
 
 @return kvImageNoError                     Success
 @return kvImageInvalidParameter            When permuteMap > 3 which is invalid.
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImagePermuteChannelsWithMaskedInsert_ARGB16U(const vImage_Buffer *src,
                                                                     const vImage_Buffer *dest,
                                                                     const uint8_t permuteMap[4],
                                                                     uint8_t copyMask,
                                                                     const Pixel_ARGB_16U backgroundColor,
                                                                     vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImagePermuteChannelsWithMaskedInsert_ARGBFFFF
 
 @discussion This is in principle vImagePermuteChannels_ARGBFFFF, followed by vImageOverwriteChannelsWithScalar_ARGBFFFF.  The fused operation is
 provided because it allows you to set different channels to different values (a weakness in vImageOverwriteChannelsWithScalar_ARGBFFFF)
 and because neither the Permute or Overwrite functions alone saturate the vector ALU on most architectures, so we think we can get
 the extra work done in the compound operation for free.
 
 For each pixel in src, do the following:
 @code
 Pixel_FFFF srcPixel,  destPixel;
 uint8_t mask = 0x8;
 
 for( int i = 0; i < 4; i++ )
 {
 result[i] = srcPixel[ permuteMap[i] ];
 if( mask & copyMask )
 result[i] = backgroundColor[i];
 mask = mask >> 1;
 }
 @endcode
 
 If you intend to just set the entire image to just the backgroundColor, we will detect this case and reroute to vImageBufferFill_ARGBFFFF.
 If it isn't obvious, this will of course work with other non-ARGB channel orderings. You'll need to adjust copyMask accordingly. The
 backgroundColor should be in the output format.
 
 This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest,
 buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing the source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param permuteMap
 The map describing the permutation of the 4 color channels.
 Each value in the map must be 0,1,2, or 3.  A map of 0,1,2,3
 is a copy from src->dest while a map of 3,2,1,0 is permutes
 ARGB -> BGRA.  Providing a map value greater than 3 will
 result in the return of error kvImageInvalidParameter.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param   flags
 \p kvImageNoFlags                  Default operation
 \p kvImageDoNotTile                Disable internal multithreading.
 \p kvImageGetTempBufferSize        Does no work and returns zero, as this function does not use a temp buffer.
 
 @return kvImageNoError                     Success
 @return kvImageInvalidParameter            When permuteMap > 3 which is invalid.
 @return kvImageRoiLargerThanInputBuffer    The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImagePermuteChannelsWithMaskedInsert_ARGBFFFF(    const vImage_Buffer *src,
                                                                      const vImage_Buffer *dest,
                                                                      const uint8_t permuteMap[4],
                                                                      uint8_t copyMask, /* Copy backgroundColor into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                                      const Pixel_FFFF backgroundColor,
                                                                      vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


/*!
 @function vImageConvert_ARGB8888toPlanarF
 
 @abstract Convert a packed (interleaved) 4-channel 8-bit unsigned buffer to planar float buffers.
 
 @discussion For each pixel in src, do the following:
 @code
 float  alpha = (maxFloat[0] - minFloat[0]) * (float) src[0] / 255.0  + minFloat[0];
 float    red = (maxFloat[1] - minFloat[1]) * (float) src[1] / 255.0  + minFloat[1];
 float  green = (maxFloat[2] - minFloat[2]) * (float) src[2] / 255.0  + minFloat[2];
 float   blue = (maxFloat[3] - minFloat[3]) * (float) src[3] / 255.0  + minFloat[3];
 @endcode
 
 @note This routine will not work in place.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing source pixels.
 
 @param alpha
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing A destination pixels.
 
 @param red
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing R destination pixels.
 
 @param green
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing G destination pixels.
 
 @param blue
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing B destination pixels.
 
 @param maxFloat
 A maxFloat value in the above formula.
 
 @param minFloat
 A minFloat value in the above formula.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageBufferSizeMismatch              When the dimension of alpha / red / green / blue are not same.
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_ARGB8888toPlanarF(
                                                          const vImage_Buffer *src,
                                                          const vImage_Buffer *alpha,
                                                          const vImage_Buffer *red,
                                                          const vImage_Buffer *green,
                                                          const vImage_Buffer *blue,
                                                          const Pixel_FFFF maxFloat,
                                                          const Pixel_FFFF minFloat,
                                                          vImage_Flags flags ) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageConvert_ARGBFFFFtoPlanar8
 
 @abstract Convert a packed (interleaved) 4-channel floating point buffer to planar 8-bit unsigned integer buffers.
 
 @discussion For each pixel in src, do the following:
 @code
 uint8_t alpha = ROUND_TO_INTEGER( CLAMP(0, 255.0f * ( src[0] - minFloat[0], 255 ) / (maxFloat[0] - minFloat[0]) ));
 uint8_t   red = ROUND_TO_INTEGER( CLAMP(0, 255.0f * ( src[1] - minFloat[1], 255 ) / (maxFloat[1] - minFloat[1]) ));
 uint8_t green = ROUND_TO_INTEGER( CLAMP(0, 255.0f * ( src[2] - minFloat[2], 255 ) / (maxFloat[2] - minFloat[2]) ));
 uint8_t  blue = ROUND_TO_INTEGER( CLAMP(0, 255.0f * ( src[3] - minFloat[3], 255 ) / (maxFloat[3] - minFloat[3]) ));
 @endcode
 
 @note This routine will not work in place.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing source pixels.
 
 @param alpha
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing A destination pixels.
 
 @param red
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing R destination pixels.
 
 @param green
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing G destination pixels.
 
 @param blue
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing B destination pixels.
 
 @param maxFloat
 A maxFloat value in the above formula.
 
 @param minFloat
 A minFloat value in the above formula.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageBufferSizeMismatch              When the dimension of alpha / red / green / blue are not same.
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_ARGBFFFFtoPlanar8(
                                                          const vImage_Buffer *src,
                                                          const vImage_Buffer *alpha,
                                                          const vImage_Buffer *red,
                                                          const vImage_Buffer *green,
                                                          const vImage_Buffer *blue,
                                                          const Pixel_FFFF maxFloat,
                                                          const Pixel_FFFF minFloat,
                                                          vImage_Flags flags ) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageConvert_ARGBFFFFtoRGBFFF
 
 @abstract Convert 4-channel ARGB buffer to a 3-channel RGB one, by removing the alpha (1st) channel.
 @note This routine will work in place.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_ARGBFFFFtoRGBFFF(
                                                         const vImage_Buffer *src,
                                                         const vImage_Buffer *dest,
                                                         vImage_Flags flags ) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageConvert_RGBAFFFFtoRGBFFF
 
 @abstract Convert 4-channel RGBA buffer to a 3-channel RGB one, by removing the alpha (last) channel.
 @note This routine will work in place.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_RGBAFFFFtoRGBFFF(
                                                         const vImage_Buffer *src,
                                                         const vImage_Buffer *dest,
                                                         vImage_Flags flags ) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageConvert_BGRAFFFFtoRGBFFF
 
 @abstract Convert 4-channel BGRA buffer to a 3-channel RGB one, by removing the alpha (last) channel and reordering the remaining..
 @note This routine will work in place.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing source pixels.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_BGRAFFFFtoRGBFFF(
                                                         const vImage_Buffer *src,
                                                         const vImage_Buffer *dest,
                                                         vImage_Flags flags ) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));



/*!
 @function vImageConvert_RGBFFFtoARGBFFFF
 
 @abstract Convert/pack a float RGB buffer with a corresponding alpha channel buffer or an alpha factor into a ARGB buffer.
 
 @discussion
 a = a corresponding pixel from the alpha channel buffer, if it exists, or a fixed factor
 For each pixel (r,g,b) in src with alpha a, do the following:
 @code
 if (premultiply!=0) dest = (a,r*a,g*a,b*a);
 else dest = (a,r,g,b);
 @endcode
 
 @param rgbSrc
 A pointer to a vImage_Buffer that references the source RGB pixels.  Unchanged on exit.
 
 @param aSrc
 A pointer to a vImage_Buffer that references the source alpha channel. Unchanged on exit.
 
 @param alpha
 If aSrc is non-NULL, this parameter is ignored.
 If aSrc is NULL, the value is used for the alpha channel of every pixel.
 
 @param argbDest
 A pointer to a vImage_Buffer that references where to write the converted ARGB data.
 
 @param flags
 \p kvImageDoNotTile            Turns off internal multithreading.
 
 @return kvImageNoError                     Success!
 @return kvImageNullPointerArgument         rgbSrc or argbDest is NULL.
 @return kvImageUnknownFlagsBit             Unknown flag was passed to the function.
 @return kvImageRoiLargerThanInputBuffer    The source buffer must have a size (in both height and width)
 no less than the destination buffers.
 
 @note This routine will not work in place.
 */
VIMAGE_PF vImage_Error
vImageConvert_RGBFFFtoARGBFFFF(
                               const vImage_Buffer* /* rgbSrc      */,
                               const vImage_Buffer* /* aSrc        */,
                               Pixel_F              /* alpha       */,
                               const vImage_Buffer* /* argbDest    */,
                               bool                 /* premultiply */,  /* Boolean 1 or 0 */
                               vImage_Flags flags ) VIMAGE_NON_NULL(1,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageConvert_RGBFFFtoRGBAFFFF
 
 @abstract Convert/pack a float RGB buffer with a corresponding alpha channel buffer or an alpha factor into a RGBA buffer.
 
 @discussion
 a = a corresponding pixel from the alpha channel buffer, if it exists, or a fixed factor
 For each pixel (r,g,b) in src with alpha a, do the following:
 @code
 if (premultiply!=0) dest = (r*a,g*a,b*a,a);
 else dest = (r,g,b,a);
 @endcode
 
 @param rgbSrc
 A pointer to a vImage_Buffer that references the source RGB pixels.  Unchanged on exit.
 
 @param aSrc
 A pointer to a vImage_Buffer that references the source alpha channel. Unchanged on exit.
 
 @param alpha
 If aSrc is non-NULL, this parameter is ignored.
 If aSrc is NULL, the value is used for the alpha channel of every pixel.
 
 @param rgbaDest
 A pointer to a vImage_Buffer that references where to write the converted RGBA data.
 
 @param flags
 \p kvImageDoNotTile            Turns off internal multithreading.
 
 @return kvImageNoError                     Success!
 @return kvImageNullPointerArgument         rgbSrc or rgbaDest is NULL.
 @return kvImageUnknownFlagsBit             Unknown flag was passed to the function.
 @return kvImageRoiLargerThanInputBuffer    The source buffer must have a size (in both height and width)
 no less than the destination buffers.
 
 @note This routine will not work in place.
 */
VIMAGE_PF vImage_Error
vImageConvert_RGBFFFtoRGBAFFFF(
                               const vImage_Buffer* /* rgbSrc      */,
                               const vImage_Buffer* /* aSrc        */,
                               Pixel_F              /* alpha       */,
                               const vImage_Buffer* /* rgbaDest    */,
                               bool                 /* premultiply */,  /* Boolean 1 or 0 */
                               vImage_Flags flags ) VIMAGE_NON_NULL(1,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageConvert_RGBFFFtoBGRAFFFF
 
 @abstract Convert/pack a float RGB buffer with a corresponding alpha channel buffer or an alpha factor into a BGRA buffer.
 
 @discussion
 a = a corresponding pixel from the alpha channel buffer, if it exists, or a fixed factor
 For each pixel (r,g,b) in src with alpha a, do the following:
 @code
 if (premultiply!=0) dest = (b*a,g*a,r*a,a);
 else dest = (b,g,r,a);
 @endcode
 
 @param rgbSrc
 A pointer to a vImage_Buffer that references the source RGB pixels.  Unchanged on exit.
 
 @param aSrc
 A pointer to a vImage_Buffer that references the source alpha channel. Unchanged on exit.
 
 @param alpha
 If aSrc is non-NULL, this parameter is ignored.
 If aSrc is NULL, the value is used for the alpha channel of every pixel.
 
 @param bgraDest
 A pointer to a vImage_Buffer that references where to write the converted BGRA data.
 
 @param flags
 \p kvImageDoNotTile            Turns off internal multithreading.
 
 @return kvImageNoError                     Success!
 @return kvImageNullPointerArgument         rgbSrc or bgraDest is NULL.
 @return kvImageUnknownFlagsBit             Unknown flag was passed to the function.
 @return kvImageRoiLargerThanInputBuffer    The source buffer must have a size (in both height and width)
 no less than the destination buffers.
 
 @note This routine will not work in place.
 */
VIMAGE_PF vImage_Error
vImageConvert_RGBFFFtoBGRAFFFF(
                               const vImage_Buffer* /* rgbSrc      */,
                               const vImage_Buffer* /* aSrc        */,
                               Pixel_F              /* alpha       */,
                               const vImage_Buffer* /* bgraDest    */,
                               bool                 /* premultiply */,  /* Boolean 1 or 0 */
                               vImage_Flags flags ) VIMAGE_NON_NULL(1,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

#define vImageConvert_BGRFFFtoBGRAFFFF( _bgrSrc, _aSrc, _alpha, _bgraDest, _premultiply, _flags )   \
vImageConvert_RGBFFFtoRGBAFFFF((_bgrSrc), (_aSrc), (_alpha), (_bgraDest), (_premultiply), (_flags) )
#define vImageConvert_BGRFFFtoRGBAFFFF( _bgrSrc, _aSrc, _alpha, _rgbaDest, _premultiply, _flags )   \
vImageConvert_RGBFFFtoBGRAFFFF((_bgrSrc), (_aSrc), (_alpha), (_rgbaDest), (_premultiply), (_flags) )


/*!
 @function vImageConvert_ARGB1555toPlanar8
 
 @abstract Convert from 16 bit/pixel ARGB1555 to 8-bit/channel Planar8 format.
 
 @discussion
 For each pixel x in src->data:
 @code
 destA->data[x] =  1bitAlphaChannel * 255;
 destR->data[x] = (5bitRedChannel   * 255 + 15) / 31;
 destG->data[x] = (5bitGreenChannel * 255 + 15) / 31;
 destB->data[x] = (5bitBlueChannel  * 255 + 15) / 31;
 @endcode
 
 @note This function will not work in place.
 
 @param src
 A pointer to a vImage_Buffer that references the ARGB source channels.
 
 @param destA
 A pointer to a vImage_Buffer that references the destination planar 8-bit alpha channel.
 
 @param destR
 A pointer to a vImage_Buffer that references the destination planar 8-bit R channel.
 
 @param destG
 A pointer to a vImage_Buffer that references the destination planar 8-bit G channel.
 
 @param destB
 A pointer to a vImage_Buffer that references the destination planar 8-bit B channel.
 
 @param flags
 \p kvImageDoNotTile            Turns off internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageBufferSizeMismatch              When the dimension of alpha / red / green / blue are not same.
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_ARGB1555toPlanar8( const vImage_Buffer *src, const vImage_Buffer *destA, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags )    VIMAGE_NON_NULL(1,2,3,4,5)  API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_ARGB1555toARGB8888
 
 @abstract Convert from 16 bit/pixel ARGB1555 to 32 bit/pixel ARGB8888 format.
 
 @discussion
 For each pixel x in src:
 @code
 Pixel8 alpha =  1bitAlphaChannel * 255;
 Pixel8 red   = (5bitRedChannel   * 255 + 15) / 31;
 Pixel8 green = (5bitGreenChannel * 255 + 15) / 31;
 Pixel8 blue  = (5bitBlueChannel  * 255 + 15) / 31;
 dest->data[x] = {alpha, red, green, blue};
 @endcode
 
 @note This function will not work in place.
 
 @param src
 A pointer to a vImage_Buffer that references the ARGB source channels.
 
 @param dest
 A pointer to a vImage_Buffer that references the destination ARGB channels.
 
 @param flags
 \p kvImageDoNotTile            Turns off internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_ARGB1555toARGB8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_Planar8toARGB1555
 
 @abstract Convert from 8-bit/channel Planar8 to 16 bit/pixel ARGB1555 format.
 
 @discussion
 For each pixel x:
 @code
 uint32_t alpha = (srcA->data[x]      + 127) / 255;
 uint32_t red   = (srcR->data[x] * 31 + 127) / 255;
 uint32_t green = (srcG->data[x] * 31 + 127) / 255;
 uint32_t blue  = (srcB->data[x] * 31 + 127) / 255;
 dest->data[x] =  (alpha << 15) | (red << 10) | (green << 5) | blue;
 @endcode
 
 @note This function will not work in place.
 
 @param srcA
 A pointer to a vImage_Buffer that references the 8-bit alpha source channel.
 
 @param srcR
 A pointer to a vImage_Buffer that references the 8-bit R source channel.
 
 @param srcG
 A pointer to a vImage_Buffer that references the 8-bit G source channel.
 
 @param srcB
 A pointer to a vImage_Buffer that references the 8-bit B source channel.
 
 @param dest
 A pointer to a vImage_Buffer that references the ARGB destination channels.
 
 @param flags
 \p kvImageDoNotTile            Turns off internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageBufferSizeMismatch              When the dimension of alpha / red / green / blue are not same.
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_Planar8toARGB1555( const vImage_Buffer *srcA, const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags )    VIMAGE_NON_NULL(1,2,3,4,5)  API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_ARGB8888toARGB1555
 
 @abstract Convert between 32 bit/pixel ARGB8888 to 16 bit/pixel ARGB1555 format.
 
 @discussion
 For each pixel x in src:
 @code
 uint32_t alpha = (8bitAlphaChannel      + 127) / 255;
 uint32_t red   = (8bitRedChannel   * 31 + 127) / 255;
 uint32_t green = (8bitGreenChannel * 31 + 127) / 255;
 uint32_t blue  = (8bitBlueChannel  * 31 + 127) / 255;
 dest->data[x] =  (alpha << 15) | (red << 10) | (green << 5) | blue;
 @endcode
 
 @note This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes.
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags.
 
 @param src
 A pointer to a vImage_Buffer that references the source channels.
 
 @param dest
 A pointer to a vImage_Buffer that references the destination channels.
 
 @param flags
 \p kvImageDoNotTile            Turns off internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_ARGB8888toARGB1555( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_RGBA5551toRGBA8888
 
 @abstract Convert from 16 bit/pixel RGBA5551 to 32 bit/pixel RGBA8888 format.
 
 @discussion
 For each pixel x in src:
 @code
 Pixel8 red   = (5bitRedChannel   * 255 + 15) / 31;
 Pixel8 green = (5bitGreenChannel * 255 + 15) / 31;
 Pixel8 blue  = (5bitBlueChannel  * 255 + 15) / 31;
 Pixel8 alpha =  1bitAlphaChannel * 255;
 dest->data[x] = {red, green, blue, alpha};
 @endcode
 
 @note This function will not work in place.
 
 @param src
 A pointer to a vImage_Buffer that references the RGBA source channels.
 
 @param dest
 A pointer to a vImage_Buffer that references the destination RGBA channels.
 
 @param flags
 \p kvImageDoNotTile            Turns off internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_RGBA5551toRGBA8888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
#define         vImageConvert_BGRA5551toBGRA8888( _src, _dest, _flags)  vImageConvert_RGBA5551toRGBA8888( _src, _dest, _flags )

/*!
 @function vImageConvert_RGBA8888toRGBA5551
 
 @abstract Convert between 32 bit/pixel RGBA8888 to 16 bit/pixel RGBA5551 format.
 
 @discussion
 For each pixel x in src:
 @code
 uint32_t red   = (8bitRedChannel   * 31 + 127) / 255;
 uint32_t green = (8bitGreenChannel * 31 + 127) / 255;
 uint32_t blue  = (8bitBlueChannel  * 31 + 127) / 255;
 uint32_t alpha = (8bitAlphaChannel      + 127) / 255;
 dest->data[x] =  (red << 11) | (green << 6) | (blue << 1) | alpha;
 @endcode
 
 @note This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes.
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags.
 
 @param src
 A pointer to a vImage_Buffer that references the source channels.
 
 @param dest
 A pointer to a vImage_Buffer that references the destination channels.
 
 @param flags
 \p kvImageDoNotTile            Turns off internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_RGBA8888toRGBA5551( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
#define         vImageConvert_BGRA8888toBGRA5551( _src, _dest, _flags)  vImageConvert_RGBA8888toRGBA5551( _src, _dest, _flags )

/*!
 @function vImageConvert_ARGB8888toARGB1555_dithered
 
 @abstract Convert between 32 bit/pixel ARGB8888 to 16 bit/pixel ARGB1555 format with dithering.
 
 @discussion Similar to vImageConvert_ARGB8888toARGB1555, except the result is dithered instead of round to nearest.
 This method should provide more accurate (overall) color reproduction and less banding in low-frequency regions of the image.
 
 @note This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes.
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags.
 
 @param src
 A pointer to a vImage_Buffer that references the source channels.
 
 @param dest
 A pointer to a vImage_Buffer that references the destination channels.
 
 @param dither
 A dithering method which should be kvImageConvert_DitherOrdered or kvImageConvert_DitherOrderedReproducible.
 
 @param flags
 \p kvImageDoNotTile            Turns off internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 
 @seealso vImageConvert_ARGB8888toARGB1555
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB8888toARGB1555_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageConvert_RGBA8888toRGBA5551_dithered
 
 @abstract Convert between 32 bit/pixel RGBA8888 to 16 bit/pixel RGBA5551 format with dithering.
 
 @discussion Similar to vImageConvert_RGBA8888toRGBA5551, except the result is dithered instead of round to nearest.
 This method should provide more accurate (overall) color reproduction and less banding in low-frequency regions of the image.
 
 @note This function can work in place provided the following are true:
 For each buffer "buf" that overlaps with dest, buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes.
 If an overlapping buffer has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags.
 
 @param src
 A pointer to a vImage_Buffer that references the source channels.
 
 @param dest
 A pointer to a vImage_Buffer that references the destination channels.
 
 @param dither
 A dithering method which should be kvImageConvert_DitherOrdered or kvImageConvert_DitherOrderedReproducible.
 
 @param flags
 \p kvImageDoNotTile            Turns off internal multithreading.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageConvert_RGBA8888toRGBA5551_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
#define      vImageConvert_BGRA8888toBGRA5551_dithered( _src, _dest, _tempBuffer, _dither, _flags)  vImageConvert_RGBA8888toRGBA5551_dithered( _src, _dest, _tempBuffer, _dither, _flags )

/*  Convert from 16 bit/pixel RGB565 to 32 bit/pixel ARGB8888 or RGBA8888 or
 BGRA8888 formats.  For each pixel:
 
 Pixel8 alpha = alpha;
 Pixel8 red   = (5bitRedChannel   * 255 + 15) / 31;
 Pixel8 green = (6bitGreenChannel * 255 + 31) / 63;
 Pixel8 blue  = (5bitBlueChannel  * 255 + 15) / 31;
 
 The following flags are allowed:
 kvImageDoNotTile            Disables internal threading.  You may want
 to use this if you have your own threading
 scheme and need to avoid interference.
 
 kvImageGetTempBufferSize    Does no work and returns zero, as this
 function does not use a temp buffer.
 
 Return values:
 kvImageNoError              Success
 kvImageUnknownFlagsBit      No work was done because an unknown bit was
 set in the flags parameter.
 kvImageBufferSizeMismatch   No work was done because the source
 image isn't large enough to cover the
 destination image.
 
 
 These functions do not operate in place.
 */

VIMAGE_PF vImage_Error vImageConvert_RGB565toARGB8888(Pixel_8 alpha, const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(2,3) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error vImageConvert_RGB565toRGBA8888(Pixel_8 alpha, const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_RGB565toBGRA8888(Pixel_8 alpha, const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_RGB565toRGB888( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags )  VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*  Convert from 32 bit/pixel ARGB8888 or RGBA8888 or BGRA8888 formats
 to 16 bit/pixel RGB565. for each pixel:
 
 uint32_t red   = (8bitRedChannel   * 31 + 127) / 255;
 uint32_t green = (8bitGreenChannel * 63 + 127) / 255;
 uint32_t blue  = (8bitBlueChannel  * 31 + 127) / 255;
 uint16_t RGB565pixel =  (red << 11) | (green << 5) | blue;
 
 The following flags are allowed:
 kvImageDoNotTile            Disables internal threading.  You may want
 to use this if you have your own threading
 scheme and need to avoid interference.
 
 kvImageGetTempBufferSize    Does no work and returns zero, as this
 function does not use a temp buffer.
 
 Return values:
 kvImageNoError                     Success
 kvImageUnknownFlagsBit             No work was done because an unknown bit was
 set in the flags parameter.
 kvImageRoiLargerThanInputBuffer    No work was done because the source
 image isn't large enough to cover the
 destination image.
 
 These functions operate in place, provided that src->data == dest->data,
 src->rowBytes >= dest->rowBytes, and the kvImageDoNotTile flag is used
 if src->rowBytes > dest->rowBytes.
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888toRGB565(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error vImageConvert_RGBA8888toRGB565(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_BGRA8888toRGB565(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageConvert_RGB888toRGB565_dithered
 vImageConvert_ARGB8888toRGB565_dithered
 vImageConvert_RGBA8888toRGB565_dithered
 vImageConvert_BGRA8888toRGB565_dithered
 
 @param dither     A dithering method which should be kvImageConvert_DitherOrdered or kvImageConvert_DitherOrderedReproducible.
 
 Convert from RGB888 or ARGB8888 or RGBA8888 or BGRA8888 formats
 to 16 bit/pixel RGB565 with dithering. For each pixel:
 
 uint32_t red   = (8bitRedChannel   * (31 << 8) + 127) / 255;
 uint32_t green = (8bitGreenChannel * (63 << 8) + 127) / 255;
 uint32_t blue  = (8bitBlueChannel  * (31 << 8) + 127) / 255;
 red   += dither_noise + (1 << 7);
 green += dither_noise + (1 << 7);
 blue  += dither_noise + (1 << 7);
 red    = red >> 8;
 green  = green >> 8;
 blue   = blue >> 8;
 uint16_t RGB565pixel =  (red << 11) | (green << 5) | blue;
 
 The following flags are allowed:
 kvImageDoNotTile            Disables internal threading.  You may want
 to use this if you have your own threading
 scheme and need to avoid interference.
 
 kvImageGetTempBufferSize    Does no work and returns zero, as this
 function does not use a temp buffer.
 
 Return values:
 kvImageNoError                     Success
 kvImageUnknownFlagsBit             No work was done because an unknown bit was
 set in the flags parameter.
 kvImageRoiLargerThanInputBuffer    No work was done because the source
 image isn't large enough to cover the
 destination image.
 
 These functions operate in place, provided that src->data == dest->data,
 src->rowBytes >= dest->rowBytes, and the kvImageDoNotTile flag is used
 if src->rowBytes > dest->rowBytes.
 */

VIMAGE_PF vImage_Error vImageConvert_RGB888toRGB565_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_ARGB8888toRGB565_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_RGBA8888toRGB565_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_BGRA8888toRGB565_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*  Convert between 16 bit/pixel RGB565 and Planar8 formats.  For the forward
 conversion, for each pixel:
 
 Pixel8 red   = (5bitRedChannel   * 255 + 15) / 31;
 Pixel8 green = (6bitGreenChannel * 255 + 31) / 63;
 Pixel8 blue  = (5bitBlueChannel  * 255 + 15) / 31;
 
 For the reverse conversion, for each pixel:
 
 uint32_t red   = (8bitRedChannel   * 31 + 127) / 255;
 uint32_t green = (8bitGreenChannel * 63 + 127) / 255;
 uint32_t blue  = (8bitBlueChannel  * 31 + 127) / 255;
 uint16_t RGB565pixel =  (red << 11) | (green << 5) | blue;
 
 The following flags are allowed:
 kvImageDoNotTile            Disables internal threading.  You may want
 to use this if you have your own threading
 scheme and need to avoid interference.
 
 kvImageGetTempBufferSize    Does no work and returns zero, as this
 function does not use a temp buffer.
 
 Return values:
 kvImageNoError                     Success
 kvImageUnknownFlagsBit             No work was done because an unknown bit was
 set in the flags parameter.
 kvImageRoiLargerThanInputBuffer    No work was done because the source
 image isn't large enough to cover the
 destination image.
 
 These functions do not operate in place.
 */

VIMAGE_PF vImage_Error vImageConvert_RGB565toPlanar8(const vImage_Buffer *src, const vImage_Buffer *destR, const vImage_Buffer *destG, const vImage_Buffer *destB, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error vImageConvert_Planar8toRGB565(const vImage_Buffer *srcR, const vImage_Buffer *srcG, const vImage_Buffer *srcB, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageConvert_RGBA5551toRGB565
 @abstract Convert from RGBA5551 to RGB565 image format
 @discussion  Convert (with loss of alpha) from RGBA5551 to RGB565 format.
 If you need something fancier done with alpha first, such as unpremultiplication or flattening, convert to 8 bit per channel first.
 Both RGB565 and RGBA5551 are defined by vImage to be host-endian formats. On Intel and ARM and other little endian systems, these are
 little endian uint16_t's in memory. On a big endian system, these are big endian uint16_t's.
 
 @param src           A pointer to a vImage_Buffer struct which describes a memory region full of RGBA5551 pixels
 
 @param dest          A pointer to a vImage_Buffer struct which describes a preallocated memory region to be overwritten by RGB565 pixels
 
 @param flags           The following flags are understood by this function:
 
 <pre>
 @textblock
 kvImageNoFlags                      Default operation.
 
 kvImageDoNotTile                    Turn internal multithreading off. This may be helpful in cases where you already have
 many such operations going concurrently, and in cases where it is desirable to keep
 CPU utilization to a single core.
 
 kvImageGetTempBufferSize            Returns 0.  Reads and writes no pixels.
 @/textblock
 </pre>
 
 @return
 <pre>
 @textblock
 kvImageNoError                         Success
 
 kvImageRoiLargerThanInputBuffer        dest->height > src->height OR dest->width > src->width.  There are not enough pixels to fill the destination buffer.
 @/textblock
 </pre>
 */
VIMAGE_PF vImage_Error vImageConvert_RGBA5551toRGB565( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB1555toRGB565
 @abstract Convert from ARGB1555 to RGB565 image format
 @discussion  Convert (with loss of alpha) from ARGB1555 to RGB565 format.
 If you need something fancier done with alpha first, such as unpremultiplication or flattening, convert to 8 bit per channel first.
 Both RGB565 and ARGB1555 are defined by vImage to be host-endian formats. On Intel and ARM and other little endian systems, these are
 little endian uint16_t's in memory. On a big endian system, these are big endian uint16_t's.
 
 @param src           A pointer to a vImage_Buffer struct which describes a memory region full of ARGB1555 pixels
 
 @param dest          A pointer to a vImage_Buffer struct which describes a preallocated memory region to be overwritten by RGB565 pixels
 
 @param flags           The following flags are understood by this function:
 
 <pre>
 @textblock
 kvImageNoFlags                      Default operation.
 
 kvImageDoNotTile                    Turn internal multithreading off. This may be helpful in cases where you already have
 many such operations going concurrently, and in cases where it is desirable to keep
 CPU utilization to a single core.
 
 kvImageGetTempBufferSize            Returns 0.  Reads and writes no pixels.
 @/textblock
 </pre>
 
 @return
 <pre>
 @textblock
 kvImageNoError                         Success
 
 kvImageRoiLargerThanInputBuffer        dest->height > src->height OR dest->width > src->width.  There are not enough pixels to fill the destination buffer.
 @/textblock
 </pre>
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB1555toRGB565( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_RGB565toRGBA5551
 @abstract Convert from RGB565 to RGBA5551 image format
 @discussion  Convert from RGB565 to RGBA5551 format.  The new alpha is set to 1.
 Both RGB565 and RGBA5551 are defined by vImage to be host-endian formats. On Intel and ARM and other little endian systems, these are
 little endian uint16_t's in memory. On a big endian system, these are big endian uint16_t's.
 
 @param src           A pointer to a vImage_Buffer struct which describes a memory region full of RGB565 pixels
 
 @param dest          A pointer to a vImage_Buffer struct which describes a preallocated memory region to be overwritten by RGBA5551 pixels
 
 @param dither        A dithering method for the green channel.   Options:
 
 kvImageConvert_DitherNone - apply no dithering; input values
 are rounded to the nearest value representable in the
 destination format.
 kvImageConvert_DitherOrdered - pre-computed blue noise is
 added to the image before rounding to the values in
 the destination format.  The offset into this blue
 noise is randomized per-call to avoid visible artifacts
 if you do your own tiling or call the function on
 sequential frames of video.
 kvImageConvert_DitherOrderedReproducible - pre-computed
 blue noise is added to the image before rounding to the
 values in the destination format.  The offset into the
 blue noise is the same for every call to allow users
 to get reproducible results.
 
 The ordered dither methods may be further influenced by shaping the
 distribution of the noise using the gaussian and uniform options below.
 These options are OR-ed with kvImageConvert_DitherOrdered / kvImageCon-
 vert_DitherOrderedReproducible:
 
 kvImageConvert_OrderedGaussianBlue - when using an ordered dither
 pattern, distribute the noise according to a gaussian
 distribution. This generally gives more pleasing images --
 less noisy and perhaps a little more saturated -- but color
 fidelity can suffer. Its effect is between kvImageConvert_DitherNone
 and kvImageConvert_DitherOrdered | kvImageConvert_DitherUniform.
 This is the default for kvImageConvert_DitherOrdered and
 kvImageConvert_DitherOrderedReproducible.
 
 kvImageConvert_OrderedUniformBlue - when using an ordered dither
 pattern, distribute the noise uniformly. This generally gives
 best color fidelity, but the resulting image is noisier and more
 obviously dithered. This is usually the best choice when low
 bitdepth content is drawn next to high bitdepth content and in other
 circumstances where subtle changes to color arising from the conversion
 could be easily noticed. It may be a poor choice when the image
 is likely to be enlarged -- this would cause the noise to become
 more evident-- and for very flat / synthetic content with little
 inherent noise. The enlargement problem may be avoided by enlarging
 first at high bitdepth, then convert to lower bitdepth.
 
 To clarify: "Blue" noise is not blue, nor does it operate solely on the blue
 color channel. Blue noise is monochrome noise that is added to all color
 channels equally. The name arises from blue light, which has a higher frequency
 than other colors of visible light. Thus, blue noise is noise which is
 weighted heavily towards high frequencies. Low frequency noise tends to have
 visible shapes in it that would become apparent in an image if it was added in,
 so it is excluded from the dither pattern.
 
 @param flags           The following flags are understood by this function:
 
 <pre>
 @textblock
 kvImageNoFlags                      Default operation.
 
 kvImageDoNotTile                    Turn internal multithreading off. This may be helpful in cases where you already have
 many such operations going concurrently, and in cases where it is desirable to keep
 CPU utilization to a single core.
 
 kvImageGetTempBufferSize            Returns 0.  Reads and writes no pixels.
 @/textblock
 </pre>
 
 @return
 <pre>
 @textblock
 kvImageNoError                          Success
 
 kvImageRoiLargerThanInputBuffer         dest->height > src->height OR dest->width > src->width.  There are not enough pixels to fill the destination buffer.
 
 kvImageInvalidParameter                 Invalid / unknown dither value
 @/textblock
 </pre>
 */
VIMAGE_PF vImage_Error vImageConvert_RGB565toRGBA5551( const vImage_Buffer *src, const vImage_Buffer *dest, int dither, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_RGB565toARGB1555
 @abstract Convert from RGB565 to ARGB1555 image format
 @discussion  Convert from RGB565 to ARGB1555 format.  The new alpha is set to 1.
 Both RGB565 and ARGB1555 are defined by vImage to be host-endian formats. On Intel and ARM and other little endian systems, these are
 little endian uint16_t's in memory. On a big endian system, these are big endian uint16_t's.
 
 @param src           A pointer to a vImage_Buffer struct which describes a memory region full of RGB565 pixels
 
 @param dest          A pointer to a vImage_Buffer struct which describes a preallocated memory region to be overwritten by ARGB1555 pixels
 
 @param dither        A dithering method for the green channel.   Options:
 
 kvImageConvert_DitherNone - apply no dithering; input values
 are rounded to the nearest value representable in the
 destination format.
 kvImageConvert_DitherOrdered - pre-computed blue noise is
 added to the image before rounding to the values in
 the destination format.  The offset into this blue
 noise is randomized per-call to avoid visible artifacts
 if you do your own tiling or call the function on
 sequential frames of video.
 kvImageConvert_DitherOrderedReproducible - pre-computed
 blue noise is added to the image before rounding to the
 values in the destination format.  The offset into the
 blue noise is the same for every call to allow users
 to get reproducible results.
 
 The ordered dither methods may be further influenced by shaping the
 distribution of the noise using the gaussian and uniform options below.
 These options are OR-ed with kvImageConvert_DitherOrdered / kvImageCon-
 vert_DitherOrderedReproducible:
 
 kvImageConvert_OrderedGaussianBlue - when using an ordered dither
 pattern, distribute the noise according to a gaussian
 distribution. This generally gives more pleasing images --
 less noisy and perhaps a little more saturated -- but color
 fidelity can suffer. Its effect is between kvImageConvert_DitherNone
 and kvImageConvert_DitherOrdered | kvImageConvert_DitherUniform.
 This is the default for kvImageConvert_DitherOrdered and
 kvImageConvert_DitherOrderedReproducible.
 
 kvImageConvert_OrderedUniformBlue - when using an ordered dither
 pattern, distribute the noise uniformly. This generally gives
 best color fidelity, but the resulting image is noisier and more
 obviously dithered. This is usually the best choice when low
 bitdepth content is drawn next to high bitdepth content and in other
 circumstances where subtle changes to color arising from the conversion
 could be easily noticed. It may be a poor choice when the image
 is likely to be enlarged -- this would cause the noise to become
 more evident-- and for very flat / synthetic content with little
 inherent noise. The enlargement problem may be avoided by enlarging
 first at high bitdepth, then convert to lower bitdepth.
 
 To clarify: "Blue" noise is not blue, nor does it operate solely on the blue
 color channel. Blue noise is monochrome noise that is added to all color
 channels equally. The name arises from blue light, which has a higher frequency
 than other colors of visible light. Thus, blue noise is noise which is
 weighted heavily towards high frequencies. Low frequency noise tends to have
 visible shapes in it that would become apparent in an image if it was added in,
 so it is excluded from the dither pattern.
 
 @param flags           The following flags are understood by this function:
 
 <pre>
 @textblock
 kvImageNoFlags                      Default operation.
 
 kvImageDoNotTile                    Turn internal multithreading off. This may be helpful in cases where you already have
 many such operations going concurrently, and in cases where it is desirable to keep
 CPU utilization to a single core.
 
 kvImageGetTempBufferSize            Returns 0.  Reads and writes no pixels.
 @/textblock
 </pre>
 
 @return
 <pre>
 @textblock
 kvImageNoError                          Success
 
 kvImageRoiLargerThanInputBuffer               dest->height > src->height OR dest->width > src->width.  There are not enough pixels to fill the destination buffer.
 
 kvImageInvalidParameter                 Invalid / unknown dither value
 @/textblock
 </pre>
 */
VIMAGE_PF vImage_Error vImageConvert_RGB565toARGB1555( const vImage_Buffer *src, const vImage_Buffer *dest, int dither, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*
 Convert between 16 bit floats to 32 bit float format.
 The 16 bit floating point format is identical to OpenEXR. It has a layout as follows:
 
 16 bits:  seeeeemmmmmmmmmm
 
 1-bit sign | 5 bits of exponent, with a bias of 15 | 10 bits of significand (with 11 bits of significance due to the implicit 1 bit)
 
 NaNs, Infinities and denormals are supported.
 Per IEEE-754, all signaling NaNs are quieted during the conversion. (OpenEXR-1.2.1 converts SNaNs to SNaNs.)
 In the float->16 bit float direction, rounding occurs according to the IEEE-754 standard and current IEEE-754 rounding mode.
 To set/inspect the current IEEE-754 rounding mode, please see appropriate utilities in fenv.h
 
 vImageConvert_Planar16FtoPlanarF does not work in place.
 vImageConvert_PlanarFtoPlanar16F does work in place, though the contents of the unused half of the buffer are undefined
 In which case:
 src->data must be equal to dest->data  and src->rowBytes >= dest->rowBytes
 If src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 These functions may also be used with multichannel images formats, such as RGBAFFFF by scaling the width by the number of channels.
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_Planar16FtoPlanarF( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error    vImageConvert_PlanarFtoPlanar16F( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));


/*
 vImageConvert_Planar8toPlanar16F
 
 Convert from 8 bit integer to 16 bit float format.
 
 destPixel[x] = ConvertToPlanar16F(srcPixel[x]);
 
 The range for conversion is [0,255] -> (half) [0.0, 1.0]
 
 The 16 bit floating point format is half-precision floating point
 (a.k.a.  IEEE-754 binary16, OpenCL half, GL_ARB_half_float_pixel, OpenEXR half).
 It has a layout as follows:
 
 16 bits:  seeeeemmmmmmmmmm
 
 1-bit sign | 5 bits of exponent, with a bias of 15 | 10 bits of significand
 (with 11 bits of significance due to the implicit 1 bit)
 
 Operands:
 ---------
 src             A pointer to a vImage_Buffer that references the source pixels
 
 dest            A pointer to a vImage_Buffer that references the destination pixels
 
 flags           The following flags are allowed:
 
 kvImageDoNotTile            Turns off internal multithreading. You may
 wish to do this if you have your own
 multithreading scheme to avoid having the
 two interfere with one another.
 
 Return Value:
 -------------
 kvImageNoError                  Success!
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height.
 kvImageNullPointerArgument      src or dest pointer is NULL.
 kvImageUnknownFlagsBit            Unexpected flag was passed.
 
 This routine will work in place as long as the scan lines overlap exactly.
 
 You can use this for ARGB8888 -> ARGB16F conversions by simply multiplying
 the width of the vImage_Buffer by 4 (for 4 channels)
 */
VIMAGE_PF vImage_Error
vImageConvert_Planar8toPlanar16F(
                                 const vImage_Buffer *src,
                                 const vImage_Buffer *dest,
                                 vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageConvert_Planar16FtoPlanar8
 
 Convert from 16 bit float to 8 bit integer format.
 
 destPixel[x] = ROUND_TO_INTEGER( SATURATED_CLAMP_0_to_255( 255.0f * (srcPixel[x])));
 
 The ROUND_TO_INTEGER function is round to nearest integer (ties go to the even result).
 
 The 16 bit floating point format is half-precision floating point
 (a.k.a.  IEEE-754 binary16, OpenCL half, GL_ARB_half_float_pixel, OpenEXR half).
 It has a layout as follows:
 
 16 bits:  seeeeemmmmmmmmmm
 
 1-bit sign | 5 bits of exponent, with a bias of 15 | 10 bits of significand
 (with 11 bits of significance due to the implicit 1 bit)
 
 All NaNs are converted to 0.
 To set/inspect the current IEEE-754 rounding mode, please see appropriate utilities in fenv.h
 
 Operands:
 ---------
 src             A pointer to a vImage_Buffer that references the source pixels
 
 dest            A pointer to a vImage_Buffer that references the destination pixels
 
 flags           The following flags are allowed:
 
 kvImageDoNotTile            Turns off internal multithreading. You may
 wish to do this if you have your own
 multithreading scheme to avoid having the
 two interfere with one another.
 
 Return Value:
 -------------
 kvImageNoError                  Success!
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height.
 kvImageNullPointerArgument      src or dest pointer is NULL.
 kvImageUnknownFlagsBit            Unexpected flag was passed.
 
 This routine will work in place as long as the scan lines overlap exactly.
 
 You can use this for ARGB16F -> ARGB8888 conversions by simply multiplying
 the width of the vImage_Buffer by 4 (for 4 channels)
 */
VIMAGE_PF vImage_Error
vImageConvert_Planar16FtoPlanar8(
                                 const vImage_Buffer *src,
                                 const vImage_Buffer *dest,
                                 vImage_Flags flags ) VIMAGE_NON_NULL(1,2)  API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


/*
 vImageConvert_16UToPlanar8
 Convert a planar (or interleaved -- multiply vImage_Buffer.width by 4) vImage_Buffer of 16 bit unsigned shorts to a buffer containing 8 bit integer values.
 For each 16 bit pixel in src:
 
 uint8_t result = (srcPixel * 255 + 32767) / 65535;
 
 To convert 4 channel interleaved unsigned 16 bit data to ARGB_8888, simply multiply the vImage_Buffer.width by 4.
 
 This can work in place, though the contents of the unused half of the buffer are undefined
 In which case:
 src->data must be equal to dest->data  and src->rowBytes >= dest->rowBytes
 If src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 This function may also be used with multichannel images formats, such as RGBA16U -> RGBA8888 by scaling the width by the number of channels.
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageConvert_16UToPlanar8( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*
 vImageConvert_Planar8To16U:
 Convert a planar (or interleaved -- multiply vImage_Buffer.width by 4) vImage_Buffer of 8-bit integer values to a buffer of 16 bit unsigned ints.
 For each 8-bit pixel in src:
 
 uint16_t result = (srcPixel * 65535 + 127 ) / 255;
 
 will not work in place.
 This function may also be used with multichannel images formats, such as RGBA8888 -> RGBA16U  by scaling the width by the number of channels.
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageConvert_Planar8To16U( const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2)    API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*
 Convert RGB to ARGB
 
 If premultiply != 0, then
 
 r = (a * r + 127) / 255
 g = (a * g + 127) / 255
 b = (a * b + 127) / 255
 
 will not work in place.
 Pass NULL for aSrc to use alpha instead.
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageConvert_RGB888toARGB8888(   const vImage_Buffer* /* rgbSrc */,
                                                      const vImage_Buffer* /* aSrc */,
                                                      Pixel_8 /* alpha */,
                                                      const vImage_Buffer* /*argbDest*/,
                                                      bool /* premultiply */,  /* Boolean 1 or 0 */
                                                      vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,4) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error vImageConvert_RGB888toRGBA8888(    const vImage_Buffer * /* rgbSrc */,
                                                      const vImage_Buffer * /* aSrc */,
                                                      Pixel_8 /* alpha */,
                                                      const vImage_Buffer * /* rgbaDest */,
                                                      bool /* premultiply */,  /* Boolean 1 or 0 */
                                                      vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,4) API_AVAILABLE(macos(10.8), ios(6.0), watchos(1.0), tvos(6.0));
VIMAGE_PF vImage_Error vImageConvert_RGB888toBGRA8888(    const vImage_Buffer * /* rgbSrc, */,
                                                      const vImage_Buffer * /* aSrc */,
                                                      Pixel_8 /* alpha */,
                                                      const vImage_Buffer * /* bgraDest */,
                                                      bool /* premultiply */,  /* Boolean 1 or 0 */
                                                      vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,4) API_AVAILABLE(macos(10.8), ios(6.0), watchos(1.0), tvos(6.0));
#define vImageConvert_BGR888toBGRA8888( _bgrSrc, _aSrc, _alpha, _bgraDest, _premultiply, _flags )   vImageConvert_RGB888toRGBA8888((_bgrSrc), (_aSrc), (_alpha), (_bgraDest), (_premultiply), (_flags) )
#define vImageConvert_BGR888toRGBA8888( _bgrSrc, _aSrc, _alpha, _rgbaDest, _premultiply, _flags )   vImageConvert_RGB888toBGRA8888((_bgrSrc), (_aSrc), (_alpha), (_rgbaDest), (_premultiply), (_flags) )

/*
 Convert 4 channel buffer to a 3 channel one, by removing the 1st channel.
 The R,G and B channels are simply copied into the new buffer.
 
 This can work in place, though the contents of the unused half of the buffer are undefined
 In which case:
 src->data must be equal to dest->data  and src->rowBytes >= dest->rowBytes
 If src has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB8888toRGB888(    const vImage_Buffer * /*argbSrc*/,
                                                      const vImage_Buffer * /*rgbDest*/,
                                                      vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error vImageConvert_RGBA8888toRGB888(    const vImage_Buffer * /*rgbaSrc*/,
                                                      const vImage_Buffer * /*rgbDest*/,
                                                      vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(6.0), watchos(1.0), tvos(6.0));
VIMAGE_PF vImage_Error vImageConvert_BGRA8888toRGB888(    const vImage_Buffer * /* bgraSrc */,
                                                      const vImage_Buffer * /* rgbDest */,
                                                      vImage_Flags /* flags */ ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(6.0), watchos(1.0), tvos(6.0));
#define vImageConvert_RGBA8888toBGR888( _rgbaSrc, _bgrDest, _flags )    vImageConvert_BGRA8888toRGB888((_rgbaSrc), (_bgrDest), (_flags))
#define vImageConvert_BGRA8888toBGR888( _bgraSrc, _bgrDest, _flags )    vImageConvert_RGBA8888toRGB888((_bgraSrc), (_bgrDest), (_flags))

/*
 Flatten a ARGB8888 image to a RGB888 image against an opaque background of a certain color.
 The calculation for each {R,G,B} channel is done as:
 
 8-bit:
 if( isImagePremultiplied )
 color = (color * 255 + (255 - alpha) * backgroundColor + 127) / 255
 else
 color = (color * alpha + (255 - alpha) * backgroundColor + 127) / 255
 
 floating point:
 if( isImagePremultiplied )
 color = color + (1.0f - alpha) * backgroundColor
 else
 color = color * alpha + (1.0f - alpha) * backgroundColor
 
 backgroundColor.alpha is ignored.
 These functions will work in place provided that rowBytes and the position of row starts is the same between src and dest images.
 
 Note: that regardless of the value of isImagePremultiplied, the result image is premultiplied by alpha. If the backgroundColor
 was not opaque and you want a non-premultiplied image, you will still need to unpremultiply the result.
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageNullPointerArgument             If src or dest == NULL
 kvImageUnknownFlagsBit                 kvImageDoNotTile and kvImageNoFlags are only flags allowed for these function.
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error  vImageFlatten_ARGB8888ToRGB888(
                                                       const vImage_Buffer * /* argb8888Src */,
                                                       const vImage_Buffer * /* rgb888dest */,
                                                       const Pixel_8888   /* backgroundColor */,    /* background color is assumed to have a 255 alpha channel */
                                                       bool      /* isImagePremultiplied */,
                                                       vImage_Flags     /* flags */
) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error  vImageFlatten_ARGBFFFFToRGBFFF(
                                                       const vImage_Buffer * /* argbFFFFSrc */,
                                                       const vImage_Buffer * /* rgbFFFdest */,
                                                       const Pixel_FFFF   /* backgroundColor */,    /* background color is assumed to have a 1.0f alpha channel */
                                                       bool      /* isImagePremultiplied */,
                                                       vImage_Flags     /* flags */
) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error  vImageFlatten_RGBA8888ToRGB888(
                                                       const vImage_Buffer * /* rgba8888Src */,
                                                       const vImage_Buffer * /* rgb888dest */,
                                                       const Pixel_8888   /* backgroundColor */,    /* background color is assumed to have a 255 alpha channel */
                                                       bool      /* isImagePremultiplied */,
                                                       vImage_Flags     /* flags */
) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.8), ios(6.0), watchos(1.0), tvos(6.0));
VIMAGE_PF vImage_Error  vImageFlatten_RGBAFFFFToRGBFFF(
                                                       const vImage_Buffer * /* rgbaFFFFSrc */,
                                                       const vImage_Buffer * /* rgbFFFdest */,
                                                       const Pixel_FFFF   /* backgroundColor */,    /* background color is assumed to have a 1.0f alpha channel */
                                                       bool      /* isImagePremultiplied */,
                                                       vImage_Flags     /* flags */
) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.8), ios(6.0), watchos(1.0), tvos(6.0));
VIMAGE_PF vImage_Error  vImageFlatten_BGRA8888ToRGB888(
                                                       const vImage_Buffer * /* bgra8888Src */,
                                                       const vImage_Buffer * /* rgb888dest */,
                                                       const Pixel_8888   /* backgroundColor */,    /* background color is assumed to have a 255 alpha channel */
                                                       bool      /* isImagePremultiplied */,
                                                       vImage_Flags     /* flags */
) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.8), ios(6.0), watchos(1.0), tvos(6.0));
VIMAGE_PF vImage_Error  vImageFlatten_BGRAFFFFToRGBFFF(
                                                       const vImage_Buffer * /* bgraFFFFSrc */,
                                                       const vImage_Buffer * /* rgbFFFdest */,
                                                       const Pixel_FFFF   /* backgroundColor */,    /* background color is assumed to have a 1.0f alpha channel */
                                                       bool      /* isImagePremultiplied */,
                                                       vImage_Flags     /* flags */
) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.8), ios(6.0), watchos(1.0), tvos(6.0));
#define vImageFlatten_BGRA8888ToBGR888( _bgra8888Src, _bgr888Dest, _backgroundColor, _isImagePremultiplied, _flags )        \
vImageFlatten_RGBA8888ToRGB888( (_bgra8888Src), (_bgr888Dest), (_backgroundColor), (_isImagePremultiplied), (_flags) )
#define vImageFlatten_RGBA8888ToBGR888( _rgba8888Src, _bgr888Dest, _backgroundColor, _isImagePremultiplied, _flags )        \
vImageFlatten_BGRA8888ToRGB888( (_rgba8888Src), (_bgr888Dest), (_backgroundColor), (_isImagePremultiplied), (_flags) )
#define vImageFlatten_BGRAFFFFToBGRFFF( _bgraFFFFSrc, _bgrFFFDest, _backgroundColor, _isImagePremultiplied, _flags )        \
vImageFlatten_RGBAFFFFToRGBFFF( (_bgraFFFFSrc), (_bgrFFFDest), (_backgroundColor), (_isImagePremultiplied), (_flags) )
#define vImageFlatten_RGBAFFFFToBGRFFF( _rgbaFFFFSrc, _bgrFFFDest, _backgroundColor, _isImagePremultiplied, _flags )        \
vImageFlatten_BGRAFFFFToRGBFFF( (_rgbaFFFFSrc), (_bgrFFFDest), (_backgroundColor), (_isImagePremultiplied), (_flags) )


/*
 Convert 3 planar buffers to a 3 channel interleave buffer.
 
 Does not work in place
 This may be used to produce other channel orderings by changing the order of the planar buffers passed into the function.
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageConvert_Planar8toRGB888( const vImage_Buffer *planarRed, const vImage_Buffer *planarGreen, const vImage_Buffer *planarBlue, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error vImageConvert_PlanarFtoRGBFFF( const vImage_Buffer *planarRed, const vImage_Buffer *planarGreen, const vImage_Buffer *planarBlue, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));

/*
 Convert a 3 channel interleave buffer to 3 planar buffers.
 
 Does not work in place
 This may be used to consume other channel orderings by changing the order of the planar buffers passed into the function.
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageConvert_RGB888toPlanar8( const vImage_Buffer *rgbSrc, const vImage_Buffer *redDest, const vImage_Buffer *greenDest, const vImage_Buffer *blueDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error vImageConvert_RGBFFFtoPlanarF( const vImage_Buffer *rgbSrc, const vImage_Buffer *redDest, const vImage_Buffer *greenDest, const vImage_Buffer *blueDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.4), ios(5.0), watchos(1.0), tvos(5.0));


/*!
 @function vImageSelectChannels_ARGB8888
 
 @abstract Does the same thing as vImageOverwriteChannels_ARGB8888 except that the newSrc buffer is in ARGB8888.
 
 @discussion For each pixel in src, do the following:
 @code
 // Generate intMask to be 0xff for the channels that we want copy from newSrc to origSrc.
 uint32_t    t = *(uint32_t*)newSrc;
 uint32_t    b = *(uint32_t*)origSrc;
 
 t  = (t & intMask ) | (b & ~intMask );
 
 *(uint32_t*)dest = t;
 @endcode
 
 If the appropriate copyMask bit is set, then the color channel from newSrc is used. Otherwise the color channel from origSrc is used.
 We note that functions of this kind only exist for interleaved buffers. If you had been using planar data, this would just be a pointer swap.
 This will work for other channel orderings, such as RGBA8888.  You need to adjust the ordering of the bits in copyMask to compensate.
 This can work in place provided that for each buffer "buf" that overlaps with dest:
 buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If buf has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param newSrc
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixel that we will overwrite with.
 
 @param origSrc
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixel that we will overwrite into.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.  You should use this if you are doing your own threading / tiling.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageSelectChannels_ARGB8888( const vImage_Buffer *newSrc,       /* A ARGB interleaved buffer */
                                                        const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                        const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                        uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                        vImage_Flags    flags ) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.5), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageSelectChannels_ARGBFFFF
 
 @abstract Does the same thing as vImageOverwriteChannels_ARGBFFFF except that the newSrc buffer is in ARGBFFFF
 
 @discussion For each pixel in src, do the following:
 @code
 // Generate intMask to be 0xffffffff for the channels that we want copy from newSrc to origSrc.
 float    t = *(float*)newSrc;
 float    b = *(float*)origSrc;
 
 t  = (t & intMask ) | (b & ~intMask );
 
 *(float*)dest = t;
 @endcode
 
 If the appropriate copyMask bit is set, then the color channel from newSrc is used. Otherwise the color channel from origSrc is used.
 We note that functions of this kind only exist for interleaved buffers. If you had been using planar data, this would just be a pointer swap.
 This will work for other channel orderings, such as RGBAFFFF.  You need to adjust the ordering of the bits in copyMask to compensate.
 This can work in place provided that for each buffer "buf" that overlaps with dest:
 buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If buf has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param newSrc
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixel that we will overwrite with.
 
 @param origSrc
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixel that we will overwrite into.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing destination pixels.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.  You should use this if you are doing your own threading / tiling.
 
 @return kvImageNoError                         Success
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageSelectChannels_ARGBFFFF( const vImage_Buffer *newSrc,       /* A ARGB interleaved buffer */
                                                        const vImage_Buffer *origSrc,      /* A ARGB interleaved buffer */
                                                        const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                        uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                        vImage_Flags    flags ) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.5), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageOverwriteChannelsWithPixel_ARGB8888
 
 @abstract Like vImageOverwriteChannelsWithScalar_ARGB8888, with a ARGB input pixel, instead of a planar one.
 
 @discussion For each pixel in src, do the following:
 @code
 // Set up a uint32_t mask - 0xFF where the pixels should be conserved
 destRow[x] = (srcRow[x] & mask) | the_pixel;
 @endcode
 
 This will work for other channel orderings, such as RGBA8888. You will need to adjust the ordering of bits in copyMask to compensate.
 This can work in place provided that for each buffer "buf" that overlaps with dest:
 buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If buf has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param the_pixel
 A pointer to Pixel_8888 that references ARGB pixel.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixel.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB destination pixels.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.  You should use this if you are doing your own threading / tiling.
 
 @return kvImageNoError                         Success
 @return kvImageInvalidParameter                When copyMask > 0x0F
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageOverwriteChannelsWithPixel_ARGB8888( const Pixel_8888     the_pixel,
                                                                 const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                                 const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                                 uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                                 vImage_Flags    flags ) VIMAGE_NON_NULL(2,3) API_AVAILABLE(macos(10.5), ios(5.0), watchos(1.0), tvos(5.0));

/*!
 @function vImageOverwriteChannelsWithPixel_ARGB16U
 
 @abstract Like vImageOverwriteChannelsWithScalar_ARGB16U, with a ARGB input pixel, instead of a planar one.
 
 @discussion For each pixel in src, do the following:
 @code
 // Set up a uint32_t mask - 0xFFFF where the pixels should be conserved
 destRow[x] = (srcRow[x] & mask) | the_pixel;
 @endcode
 
 This will work for other channel orderings, such as RGBA16U. You will need to adjust the ordering of bits in copyMask to compensate.
 This can work in place provided that for each buffer "buf" that overlaps with dest:
 buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If buf has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param the_pixel
 A pointer to Pixel_ARGB_16U that references ARGB pixel.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixel.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB destination pixels.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.  You should use this if you are doing your own threading / tiling.
 
 @return kvImageNoError                         Success
 @return kvImageInvalidParameter                When copyMask > 0x0F
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageOverwriteChannelsWithPixel_ARGB16U( const Pixel_ARGB_16U     the_pixel,
                                                                const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                                const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                                uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                                vImage_Flags    flags ) VIMAGE_NON_NULL(2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*!
 @function vImageOverwriteChannelsWithPixel_ARGBFFFF
 
 @abstract Like vImageOverwriteChannelsWithScalar_ARGBFFFF, with a ARGB input pixel, instead of a planar one.
 
 @discussion For each pixel in src, do the following:
 @code
 // Set up a uint32_t mask - 0xFFFFFFFF where the pixels should be conserved
 destRow[x] = (srcRow[x] & mask) | the_pixel;
 @endcode
 
 This will work for other channel orderings, such as RGBAFFFF. You will need to adjust the ordering of bits in copyMask to compensate.
 This can work in place provided that for each buffer "buf" that overlaps with dest:
 buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If buf has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 @param the_pixel
 A pointer to Pixel_FFFF that references ARGB pixel.
 
 @param src
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB source pixel.
 
 @param dest
 A pointer to a valid and initialized vImage_Buffer struct, that points to a buffer containing ARGB destination pixels.
 
 @param copyMask
 A mask to copy plane : 0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue
 
 @param flags
 \p kvImageNoFlags          Default operation
 \p kvImageDoNotTile        Disable internal multithreading.  You should use this if you are doing your own threading / tiling.
 
 @return kvImageNoError                         Success
 @return kvImageInvalidParameter                When copyMask > 0x0F
 @return kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error vImageOverwriteChannelsWithPixel_ARGBFFFF( const Pixel_FFFF     the_pixel,
                                                                 const vImage_Buffer *src,      /* A ARGB interleaved buffer */
                                                                 const vImage_Buffer *dest,      /* A ARGB interleaved buffer */
                                                                 uint8_t copyMask,               /* Copy plane into  0x8  -- alpha, 0x4 -- red, 0x2 --- green, 0x1 --- blue */
                                                                 vImage_Flags    flags ) VIMAGE_NON_NULL(2,3) API_AVAILABLE(macos(10.5), ios(5.0), watchos(1.0), tvos(5.0));


/*
 The following functions interleave the planar buffers pointed to by red, green and blue, with the scalar value in alpha, to
 create a ARGB, BGRA or RGBA  four channel interleaved buffer.  These functions do not work in place.  Per all vImage functions
 channel order is defined as memory order.
 
 Flags:
 kvImageGetTempBufferSize    returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Other flags cause the function to return kvImageUnknownFlagsBit.
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_Planar8ToXRGB8888( Pixel_8 alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(2,3,4,5)    API_AVAILABLE(macos(10.6), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error    vImageConvert_Planar8ToBGRX8888( const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_8 alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5)    API_AVAILABLE(macos(10.6), ios(5.0), watchos(1.0), tvos(5.0));
#define         vImageConvert_Planar8ToRGBX8888( _red, _green, _blue, _alpha, _dest, _flags )   vImageConvert_Planar8ToBGRX8888((_red), (_green), (_blue), (_alpha), (_dest), (_flags))
VIMAGE_PF vImage_Error    vImageConvert_PlanarFToXRGBFFFF( Pixel_F alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(2,3,4,5)    API_AVAILABLE(macos(10.6), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error    vImageConvert_PlanarFToBGRXFFFF( const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_F alpha, const vImage_Buffer *dest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5)    API_AVAILABLE(macos(10.6), ios(5.0), watchos(1.0), tvos(5.0));
#define         vImageConvert_PlanarFToRGBXFFFF( _red, _green, _blue, _alpha, _dest, _flags )   vImageConvert_PlanarFToBGRXFFFF( (_red), (_green), (_blue), (_alpha), (_dest), (_flags))

/*
 The following functions de-interleave a XRGB, BGRX, or RGBX four-channel
 buffer to create three planar buffers red, green, and blue, discarding
 the fourth channel.  These functions do not work in place.  As with all
 vImage functions, channel order is memory order.
 
 Flags:
 kvImageGetTempBufferSize    Returns 0, does nothing.
 kvImageDoNotTile            Disables internal multithreading.
 
 Other flags cause the function to return kvImageUnknownFlagsBit.
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageBufferSizeMismatch              When the size of destination dimensions are different.
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */

VIMAGE_PF vImage_Error vImageConvert_XRGB8888ToPlanar8(const vImage_Buffer *src,
                                                       const vImage_Buffer *red,
                                                       const vImage_Buffer *green,
                                                       const vImage_Buffer *blue,
                                                       vImage_Flags flags)
VIMAGE_NON_NULL(1,2,3,4)
API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

VIMAGE_PF vImage_Error vImageConvert_BGRX8888ToPlanar8(const vImage_Buffer *src,
                                                       const vImage_Buffer *blue,
                                                       const vImage_Buffer *green,
                                                       const vImage_Buffer *red,
                                                       vImage_Flags flags)
VIMAGE_NON_NULL(1,2,3,4)
API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

#define vImageConvert_RGBX8888ToPlanar8(_src, _red, _green, _blue, _flags) \
vImageConvert_BGRX8888ToPlanar8((_src), (_red), (_green), (_blue), (_flags))

VIMAGE_PF vImage_Error vImageConvert_XRGBFFFFToPlanarF(const vImage_Buffer *src,
                                                       const vImage_Buffer *red,
                                                       const vImage_Buffer *green,
                                                       const vImage_Buffer *blue,
                                                       vImage_Flags flags)
VIMAGE_NON_NULL(1,2,3,4)
API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

VIMAGE_PF vImage_Error vImageConvert_BGRXFFFFToPlanarF(const vImage_Buffer *src,
                                                       const vImage_Buffer *blue,
                                                       const vImage_Buffer *green,
                                                       const vImage_Buffer *red,
                                                       vImage_Flags flags)
VIMAGE_NON_NULL(1,2,3,4)
API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

#define vImageConvert_RGBXFFFFToPlanarF(_src, _red, _green, _blue, _flags) \
vImageConvert_BGRXFFFFToPlanarF((_src), (_red), (_green), (_blue), (_flags))

/*
 vImageConvert_Planar8ToARGBFFFF
 
 Conversion routines to convert planar 8-bit buffers to packed (interleaved) 4 channel floating point format.
 
 The meaning of maxFloat and minFloat here is substatially the same as for vImageConvert_Planar8toPlanarF. The difference is that since this is a four channel
 image, we use four channel min and max values so that different mins and maxes can be used for each channel. The channels in minFloat and maxFloat are in the
 same order as the output pixels. MaxFloat is allowed to be less than MinFloat, in which case the image will come out looking like a photographic negative.
 (That is, you get a free contrast + brightness adjustment as part of this conversion.)
 
 The vImageConvert_Planar8ToARGBFFFF function is the workhorse of this family. The other three are provided as a convenience. You can actually substitute
 any of the channels with a constant by replacing the vImage_Buffer passed in for that channel with one from another color channel, and set
 maxFloat.color = minFloat.color = desired color for that channel. (In the particular case where you want all four channels to be constant, please call
 vImageBufferFill_ARGBFFFF instead.) Likewise, though these API names appear to correspond to particular color channel orders, vImage has no way of knowing what
 is actually red or green or cyan, so you can use them for other color spaces and other packing orders. Thus, vImageConvert_Planar8ToARGBFFFF should be
 properly considered a somewhat color space agnostic <=4 planar 8-bit channel to 4 channel packed float conversion function.
 
 Performance data on Intel Core2 and G5 suggest that like most simple conversion functions, these functions only perform well if the data is already in the cache.
 Optimum tile sizes are between ~200 pixels and somewhere in the 50000 to 200000 pixel range, depending on cache size. If the image is larger than that, this
 function is limited by the throughput of the machine's front side bus and will run anywhere from 3 to 10 times slower. For well sized images / times, we observe
 that the vector code is 3-12x faster than scalar code. For images that don't fit in cache or that are not in cache, the vector code is perhaps only 10% faster
 than scalar.
 
 Flags:
 kvImageGetTempBufferSize    returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Other flags cause the function to return kvImageUnknownFlagsBit.
 
 These routines do not work in place.
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_Planar8ToARGBFFFF( const vImage_Buffer *alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4,5) API_AVAILABLE(macos(10.6), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error    vImageConvert_Planar8ToXRGBFFFF( Pixel_F alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(2,3,4,5) API_AVAILABLE(macos(10.6), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error    vImageConvert_Planar8ToBGRXFFFF(const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_F alpha, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) API_AVAILABLE(macos(10.6), ios(5.0), watchos(1.0), tvos(5.0));
#define         vImageConvert_Planar8ToRGBXFFFF(_red, _green, _blue, _alpha, _dest, _maxFloat, _minFloat, _flags)  vImageConvert_Planar8ToBGRXFFFF((_red), (_green), (_blue), (_alpha), (_dest), (_maxFloat), (_minFloat), (_flags))

/*
 vImageConvert_PlanarFToARGB8888
 
 Conversion routines to convert planar float buffers to packed (interleaved) 4 channel 8-bit unsigned format.
 
 The meaning of maxFloat and minFloat here is similar to vImageConvert_PlanarFtoPlanar8. That is, the max and min define the pixel values for
 100% and 0% light saturation respectively. (Pixel values outside that range are clamped into that range before we do arithmetic.) Since this function works on
 multichannel data, we pass in multichannel maxes and mins. The channel order in maxFloat and minFloat is the same as for the desired result pixel. The calculation
 is as follows for each channel:
 
 uint8_t result = ROUND_TO_INTEGER( SATURATED_CLAMP_0_to_255( 255.0f * ( srcPixel[channel] - minFloat[channel] ) / (maxFloat[channel] - minFloat[channel]) ));
 
 The ROUND_TO_INTEGER function here behaves identically to the C99 lrintf() function. It rounds to integer using the prevailing floating point rounding mode.
 By default, that is round to nearest integer (ties go to the even result).  You can change the rounding mode using interfaces in fenv.h, specfically fesetround()
 and fegetround(), if you prefer that the calculation round up, or down.
 
 It is allowed that maxFloat[channel] < minFloat[channel], in which case you'll get an image that appears a bit like a photgraphic negative. The astute reader will
 note that these routines provide a free per-channel brightness and contrast adjustment.
 
 In the special case that maxFloat[channel] == minFloat[channel], then the calculation is instead as follows:
 
 uint8_t result = ROUND_TO_INTEGER( SATURATED_CLIP_0_to_255( 255.0f * maxFloat[channel] ) );
 
 This serves two purposes. It guarantees we can't get a division by zero. It also provides a way to set certain channels to a constant, rather than use
 a source buffer. You'll still need to pass in a source buffer for that channel, the data also needs to be valid, but it wont actually affect the result. It should
 be sufficient to substitute one of the other source buffers in for the color channel that you wish to be constant. If you intend to produce a buffer full of a
 solid color, please use vImageBufferFill_ARGB8888 instead. Two special purpose routines are provided for constant alpha in either the first or last position
 in the pixel, vImageConvert_PlanarFToXRGB8888, vImageConvert_PlanarFToBGRX8888. On some platforms, these may be a little bit faster.
 
 Numerics note: We don't actually do the full caculation described above. The constant terms are precalculated. We are really doing the following:
 
 float a = 255.0f / (maxFloat[channel] - minFloat[channel]);
 float b = minFloat[channel] * -a;
 
 uint8_t result = ROUND_TO_INTEGER( SATURATED_CLAMP( srcPixel[channel], minFloat[channel], maxFloat[channel]) * a  + b ));
 
 This may cause slightly different rounding when scaling the pixel to the 0..255 range. In very rare cases, that may produce a result pixel that differs from the
 true calculation by 1. NaNs produce 0.
 
 Flags:
 kvImageGetTempBufferSize    returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Other flags cause the function to return kvImageUnknownFlagsBit.
 
 These can work in place provided that for each buffer "buf" that overlaps with dest:
 buf->data must be equal to dest->data and buf->rowBytes >= dest->rowBytes
 If buf has a different rowBytes from dest, kvImageDoNotTile must be also passed in the flags
 
 Return Value:
 -------------
 kvImageNoError                         Success
 kvImageRoiLargerThanInputBuffer        The height and width of the destination must be less than or equal to the height and width of the src buffer, respectively.
 */
VIMAGE_PF vImage_Error    vImageConvert_PlanarFToARGB8888( const vImage_Buffer *alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4,5,6,7) API_AVAILABLE(macos(10.6), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error    vImageConvert_PlanarFToXRGB8888( Pixel_8 alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(2,3,4,5,6,7) API_AVAILABLE(macos(10.6), ios(5.0), watchos(1.0), tvos(5.0));
VIMAGE_PF vImage_Error    vImageConvert_PlanarFToBGRX8888( const vImage_Buffer *blue, const vImage_Buffer *green, const vImage_Buffer *red, Pixel_8 alpha, const vImage_Buffer *dest, const Pixel_FFFF maxFloat, const Pixel_FFFF minFloat, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5,6,7) API_AVAILABLE(macos(10.6), ios(5.0), watchos(1.0), tvos(5.0));
#define         vImageConvert_PlanarFToRGBX8888( _red, _green, _blue, _alpha, _dest, _maxFloat, _minFloat, _flags )     vImageConvert_PlanarFToBGRX8888((_red), (_green), (_blue), (_alpha), (_dest), (_maxFloat), (_minFloat), (_flags))

/*
 vImageConvert_RGB16UtoARGB16U
 
 Convert RGB16U -> ARGB16U
 
 
 vImageConvert_RGB16UtoRGBA16U
 
 Convert RGB16U -> RGBA16U
 
 
 vImageConvert_RGB16UtoBGRA16U
 
 Convert RGB16U -> BGRA16U
 
 
 Each channel is 16 bit unsigned.
 3-channel interleaved pixel buffers that contains RGB and 1 planar pixel buffer for A or
 'alpha' value are combined to create 4-channel interleaved pixel buffer.
 'premultiply' determines if this function will premultiply alpha value(s) to RGB values.
 
 if (aSrc != NULL)
 {
 if (premultiply)
 {
 r = (aSrc[i] * rgb[i*3+0] + 32767) / 65535
 g = (aSrc[i] * rgb[i*3+1] + 32767) / 65535
 b = (aSrc[i] * rgb[i*3+2] + 32767) / 65535
 
 argbDest[i*4+0] = aSrc[i];
 argbDest[i*4+1] = r;
 argbDest[i*4+2] = g;
 argbDest[i*4+3] = b;
 }
 else
 {
 argbDest[i*4+0] = aSrc[i];
 argbDest[i*4+1] = rgb[i*3+0];
 argbDest[i*4+2] = rgb[i*3+1];
 argbDest[i*4+3] = rgb[i*3+2];
 }
 }
 else
 {
 if (premultiply)
 {
 r = (alpha * rgb[i*3+0] + 32767) / 65535
 g = (alpha * rgb[i*3+1] + 32767) / 65535
 b = (alpha * rgb[i*3+2] + 32767) / 65535
 
 argbDest[i*4+0] = alpha;
 argbDest[i*4+1] = r;
 argbDest[i*4+2] = g;
 argbDest[i*4+3] = b;
 }
 else
 {
 argbDest[i*4+0] = alpha;
 argbDest[i*4+1] = rgb[i*3+0];
 argbDest[i*4+2] = rgb[i*3+1];
 argbDest[i*4+3] = rgb[i*3+2];
 }
 }
 
 Operands:
 ---------
 rgbSrc : A pointer to vImage_Buffer that references RGB interleaved source pixels
 
 aSrc : A pointer to vImage_Buffer that references A planar source pixels
 
 alpha : A single alpha value
 
 argbDest / rgbaDest / bgraDest : A pointer to vImage_Buffer that references ARGB / RGBA / BGRA interleaved destination pixels
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when src.width < dest.width || src.height < dest.height.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 
 This function will not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_RGB16UtoARGB16U( const vImage_Buffer *rgbSrc, const vImage_Buffer *aSrc, Pixel_16U alpha, const vImage_Buffer *argbDest, bool premultiply, vImage_Flags flags ) VIMAGE_NON_NULL(1,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_RGB16UtoRGBA16U( const vImage_Buffer *rgbSrc, const vImage_Buffer *aSrc, Pixel_16U alpha, const vImage_Buffer *rgbaDest, bool premultiply, vImage_Flags flags ) VIMAGE_NON_NULL(1,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_RGB16UtoBGRA16U( const vImage_Buffer *rgbSrc, const vImage_Buffer *aSrc, Pixel_16U alpha, const vImage_Buffer *bgraDest, bool premultiply, vImage_Flags flags ) VIMAGE_NON_NULL(1,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageConvert_ARGB16UtoRGB16U
 
 Convert ARGB16U -> RGB16U
 
 
 vImageConvert_RGBA16UtoRGB16U
 
 Convert RGBA16U -> RGB16U
 
 
 vImageConvert_BGRA16UtoRGB16U
 
 Convert BGRA16U -> RGB16U
 
 
 Each channel is 16-bit unsigned
 4-channel interleaved pixel buffer becomes 3-channel interleaved pixel buffer by skipping to copy
 the first channel in 4-channel interleaved pixel buffer.
 
 rgbDest[i*3+0] = argbSrc[i*4+1];
 rgbDest[i*3+1] = argbSrc[i*4+2];
 rgbDest[i*3+2] = argbSrc[i*4+3];
 
 Operands:
 ---------
 argbSrc / rgbaSrc / bgraSrc : A pointer to vImage_Buffer that references ARGB / RGBA / BGRA interleaved source pixels
 
 rgbDest : A pointer to vImage_Buffer that references RGB interleaved destination pixels
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when src.width < dest.width || src.height < dest.height.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 
 vImageConvert_RGBA16UtoRGB16U() can work in place if (argbSrc.data == rgbDest.data) && (argbSrc.rowBytes == rgbDest.rowBytes)
 Rest of cases in these 3 functions will not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB16UtoRGB16U( const vImage_Buffer *argbSrc, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_RGBA16UtoRGB16U( const vImage_Buffer *rgbaSrc, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_BGRA16UtoRGB16U( const vImage_Buffer *bgraSrc, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageConvert_Planar16UtoARGB16U
 
 Convert Planar16U -> ARGB16U
 
 
 Each channel is 16-bit unsigned
 4 planar pixel buffers are combined to create 4-channel interleaved pixel buffers.
 
 argbDest[i*4+0] = aSrc[i];
 argbDest[i*4+1] = rSrc[i];
 argbDest[i*4+2] = gSrc[i];
 argbDest[i*4+3] = bSrc[i];
 
 This function can be used to create any channel order from 4 planar pixel buffers to interleaved
 pixel buffers.
 
 Operands:
 ---------
 aSrc : A pointer to vImage_Buffer that references A planar source pixels
 
 rSrc : A pointer to vImage_Buffer that references R planar source pixels
 
 gSrc : A pointer to vImage_Buffer that references G planar source pixels
 
 bSrc : A pointer to vImage_Buffer that references B planar source pixels
 
 argbDest : A pointer to vImage_Buffer that references ARGB interleaved destination pixels
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when src.width < dest.width || src.height < dest.height.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 
 This function will not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_Planar16UtoARGB16U(const vImage_Buffer *aSrc, const vImage_Buffer *rSrc, const vImage_Buffer *gSrc, const vImage_Buffer *bSrc, const vImage_Buffer *argbDest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageConvert_ARGB16UtoPlanar16U
 
 Convert ARGB16U -> Planar16U
 
 
 Each channel is 16-bit unsigned
 Each channel of 4-channel interleaved pixel buffer are copied into its planar pixel buffer.
 
 aDest[i] = argbSrc[i*4+0];
 rDest[i] = argbSrc[i*4+1];
 gDest[i] = argbSrc[i*4+2];
 bDest[i] = argbSrc[i*4+3];
 
 This function can be used to create any channel order from interleaved pixel buffers to 4 planar
 pixel buffers.
 
 Operands:
 ---------
 argbSrc : A pointer to vImage_Buffer that references ARGB interleaved source pixels
 
 aDest : A pointer to vImage_Buffer that references A planar destination pixels
 
 rDest : A pointer to vImage_Buffer that references R planar destination pixels
 
 gDest : A pointer to vImage_Buffer that references G planar destination pixels
 
 bDest : A pointer to vImage_Buffer that references B planar destination pixels
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 vImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when src.width < dest.width || src.height < dest.height.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 
 This function will not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB16UtoPlanar16U(const vImage_Buffer *argbSrc, const vImage_Buffer *aDest, const vImage_Buffer *rDest, const vImage_Buffer *gDest, const vImage_Buffer *bDest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


/*
 vImageConvert_Planar16UtoRGB16U
 
 Planar16U -> RGB16U
 
 
 Each channel is 16-bit unsigned
 3 planar pixel buffers are combined to create 3-channel interleaved pixel buffer.
 
 rgbDest[i*3+0] = rSrc[i];
 rgbDest[i*3+1] = gSrc[i];
 rgbDest[i*3+2] = bSrc[i];
 
 This function can be used to create any channel order from 3 planar pixel buffers to interleaved
 pixel buffers.
 
 Operands:
 ---------
 rSrc : A pointer to vImage_Buffer that references R planar source pixels
 
 gSrc : A pointer to vImage_Buffer that references G planar source pixels
 
 bSrc : A pointer to vImage_Buffer that references B planar source pixels
 
 rgbDest : A pointer to vImage_Buffer that references RGB interleaved destination pixels
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when src.width < dest.width || src.height < dest.height.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 
 This function will not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_Planar16UtoRGB16U( const vImage_Buffer *rSrc, const vImage_Buffer *gSrc, const vImage_Buffer *bSrc, const vImage_Buffer *rgbDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageConvert_RGB16UtoPlanar16U
 
 Planar16U <- RGB16U
 
 Each channel is 16-bit unsigned
 Each channel of 3-channel interleaved pixel buffer are copied into its planar pixel buffer.
 
 rDest[i] = rgbSrc[i*3+0];
 gDest[i] = rgbSrc[i*3+1];
 bDest[i] = rgbSrc[i*3+2];
 
 This function can be used to create any channel order from interleaved pixel buffers to 3 planar
 pixel buffers.
 
 Operands:
 ---------
 rgbSrc : A pointer to vImage_Buffer that references RGB interleaved source pixels
 
 rDest : A pointer to vImage_Buffer that references R planar destination pixels
 
 gDest : A pointer to vImage_Buffer that references G planar destination pixels
 
 bDest : A pointer to vImage_Buffer that references B planar destination pixels
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 
 This function will not work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_RGB16UtoPlanar16U( const vImage_Buffer *rgbSrc, const vImage_Buffer *rDest, const vImage_Buffer *gDest, const vImage_Buffer *bDest, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


VIMAGE_PF vImage_Error vImageConvert_Planar16UtoPlanar8_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, int dither, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));
VIMAGE_PF vImage_Error vImageConvert_RGB16UtoRGB888_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, int dither, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));
VIMAGE_PF vImage_Error vImageConvert_ARGB16UtoARGB8888_dithered(const vImage_Buffer *src, const vImage_Buffer *dest, int dither, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*
 vImageConvert_ARGB16UToARGB8888
 
 This function does 3 things.
 1. Converts 16-bit unsigned ARGB interleaved pixels into 8-bit unsigned ARGB interleaved pixels.
 2. Changes the order of channels according to permuteMap
 3. Selects between the result pixel and the backgroundColor according to the bits in copyMask.
 
 permuteMap[i] = 0, 1, 2, or 3 to specify how we permute each channel.
 
 permuteMap[0] tells which channel in ARGB16U will be used as the 1st channel (A) in the result ARGB8888.
 permuteMap[1] tells which channel in ARGB16U will be used as the 2nd channel (R) in the result ARGB8888.
 permuteMap[2] tells which channel in ARGB16U will be used as the 3rd channel (G) in the result ARGB8888.
 permuteMap[3] tells which channel in ARGB16U will be used as the 4th channel (B) in the result ARGB8888.
 
 copyMask = _ _ _ _  ; 4 digit binary
 1000 tells if we want to use 1st channel in backgroundColor as the value of channel A in the result.
 0100 tells if we want to use 2nd channel in backgroundColor as the value of channel R in the result.
 0010 tells if we want to use 3rd channel in backgroundColor as the value of channel G in the result.
 0001 tells if we want to use 4th channel in backgroundColor as the value of channel B in the result.
 
 The per-pixel operation is:
 
 Pixel_16U *srcPixel;
 Pixel_8888 *destPixel;
 uint16_t result16;
 uint8_t result[4];
 uint8_t mask = 0x8;
 
 for( int i = 0; i < 4; i++ )
 {
 result16 = srcPixel[ permuteMap[i] ];
 result[i] = (result16 * 255U + 32767U) / 65535U;
 if( mask & copyMask )
 result[i] = backgroundColor[i];
 mask = mask >> 1;
 }
 srcPixel += 4;
 
 destPixel[0] = result[0];
 destPixel[1] = result[1];
 destPixel[2] = result[2];
 destPixel[3] = result[3];
 destPixel += 4;
 
 Operands:
 ---------
 src : A pointer to vImage_Buffer that references 16-bit ARGB interleaved source pixels.
 dest : A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 permuteMap : Values that can be used to switch the channel order as the above example.
 copyMask : A mask to choose between the result and backgroundColor.
 backgroudColor : A pointer to Pixel_8888 that references 8-bit ARGB values which can replace the result pixels with. Pixel_8888 backgroundColor = {alpha, red, green, blue};
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 kvImageInvalidParameter            Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 kvImageNullPointerArgument         Is returned when backgroundColorPtr is NULL.
 
 This function can work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB16UToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const uint8_t permuteMap[4], uint8_t copyMask, const Pixel_8888 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


/*
 vImageConvert_ARGB8888ToARGB16U
 
 This function does 3 things.
 1. Converts 8-bit unsigned ARGB interleaved pixels into 16-bit unsigned ARGB interleaved pixels.
 2. Changes the order of channels according to permuteMap
 3. Selects between the result pixel and the backgroundColor according to the bits in copyMask.
 
 permuteMap[i] = 0, 1, 2, or 3 to specify how we permute each channel.
 
 permuteMap[0] tells which channel in ARGB8888 will be used as the 1st channel (A) in the result ARGB16U.
 permuteMap[1] tells which channel in ARGB8888 will be used as the 2nd channel (R) in the result ARGB16U.
 permuteMap[2] tells which channel in ARGB8888 will be used as the 3rd channel (G) in the result ARGB16U.
 permuteMap[3] tells which channel in ARGB8888 will be used as the 4th channel (B) in the result ARGB16U.
 
 copyMask = _ _ _ _  ; 4 digit binary
 1000 tells if we want to use 1st channel in backgroundColor as the value of channel A in the result.
 0100 tells if we want to use 2nd channel in backgroundColor as the value of channel R in the result.
 0010 tells if we want to use 3rd channel in backgroundColor as the value of channel G in the result.
 0001 tells if we want to use 4th channel in backgroundColor as the value of channel B in the result.
 
 The per-pixel operation is:
 
 Pixel_8888 *srcPixel;
 Pixel_16U *destPixel;
 uint8_t result8;
 uint16_t result[4];
 uint8_t mask = 0x8;
 
 for( int i = 0; i < 4; i++ )
 {
 result8 = srcPixel[ permuteMap[i] ];
 result[i] = (result8 * 65535U + 127U) / 255U;
 if( mask & copyMask )
 result[i] = backgroundColor[i];
 mask = mask >> 1;
 }
 srcPixel += 4;
 
 destPixel[0] = result[0];
 destPixel[1] = result[1];
 destPixel[2] = result[2];
 destPixel[3] = result[3];
 destPixel += 4;
 
 Operands:
 ---------
 src : A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 dest : A pointer to vImage_Buffer that references 16-bit ARGB interleaved destination pixels.
 permuteMap : Values that can be used to switch the channel order as the above example.
 copyMask : A mask to choose between the result and backgroundColor.
 backgroundColor : A pointer to Pixel_ARGB_16U that references 16-bit ARGB values which can replace the result pixels with. Pixel_ARGB_16U backgroundColor = {alpha, red, green, blue};
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 kvImageInvalidParameter            Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 kvImageNullPointerArgument         Is returned when backgroundColorPtr is NULL.
 
 This function doesn't work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB8888ToARGB16U(const vImage_Buffer *src, const vImage_Buffer *dest, const uint8_t permuteMap[4], uint8_t copyMask, const Pixel_ARGB_16U backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


/*
 vImageConvert_RGB16UToARGB8888
 
 This function does 3 things.
 1. Converts 16-bit unsigned RGB interleaved pixels into 8-bit unsigned ARGB interleaved pixels. (255 or A from backgroundColor will be used as A.)
 2. Changes the order of channels according to permuteMap.
 3. Selects between the result pixel and the backgroundColor according to the bits in copyMask.
 
 permuteMap[x] = 0, 1, or 2 to specify how we permute each channel.
 
 255 will be used as a default alpha value.
 permuteMap[0] tells which channel in 255RGB16U will be used as the 1st channel (A) in the result ARGB8888.
 permuteMap[1] tells which channel in 255RGB16U will be used as the 2nd channel (R) in the result ARGB8888.
 permuteMap[2] tells which channel in 255RGB16U will be used as the 3rd channel (G) in the result ARGB8888.
 permuteMap[3] tells which channel in 255RGB16U will be used as the 4th channel (B) in the result ARGB8888.
 
 copyMask = _ _ _ _  ; 4 digit binary
 1000 tells if we want to use 1st channel in backgroundColor which can be A in this function.
 0100 tells if we want to use 2nd channel in backgroundColor which can be R in this function.
 0010 tells if we want to use 3rd channel in backgroundColor which can be G in this function.
 0001 tells if we want to use 4th channel in backgroundColor which can be B in this function.
 
 The per-pixel operation is:
 
 Pixel_16U  *srcPixel;
 Pixel_8888 *destPixel;
 uint16_t   r16, g16, b16;
 uint8_t    result[4], a, r, g, b;
 uint8_t    mask = 0x8;
 
 r16 = srcPixel[0];
 g16 = srcPixel[1];
 b16 = srcPixel[2];
 srcPixel += 3;
 
 //Convert
 result[0] = 255;
 result[1] = (r16 * 255U + 32767U) / 65535U;
 result[2] = (g16 * 255U + 32767U) / 65535U;
 result[3] = (b16 * 255U + 32767U) / 65535U;
 
 //Permute
 a = result[permuteMap[0]];
 r = result[permuteMap[1]];
 g = result[permuteMap[2]];
 b = result[permuteMap[3]];
 
 //Select
 if( mask & copyMask )
 a = backgroundColor[0];
 mask = mask >> 1;
 if( mask & copyMask )
 r = backgroundColor[1];
 mask = mask >> 1;
 if( mask & copyMask )
 g = backgroundColor[2];
 mask = mask >> 1;
 if( mask & copyMask )
 b = backgroundColor[3];
 
 destPixel[0] = a;
 destPixel[1] = r;
 destPixel[2] = g;
 destPixel[3] = b;
 destPixel += 4;
 
 Operands:
 ---------
 src : A pointer to vImage_Buffer that references 16-bit RGB interleaved source pixels.
 dest : A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 permuteMap : Values that can be used to switch the channel order as the above example. permuteMap[0] is for A in the dest ARGB8888, permuteMap[1] is for R in the dest ARGB8888,  permuteMap[2] is for G in the dest ARGB8888, and  permuteMap[3] is for B in the dest ARGB8888.
 copyMask : A mask to choose between the result and backgroundColor.
 backgroudColor : A pointer to Pixel_8888 that references 8-bit ARGB values which can replace the result pixels with. Pixel_8888 backgroundColor = {alpha, red, green, blue};
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 kvImageInvalidParameter            Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 kvImageNullPointerArgument         Is returned when backgroundColorPtr is NULL.
 
 This function can work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_RGB16UToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const uint8_t permuteMap[4], uint8_t copyMask, const Pixel_8888 backgroundColor, vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


/*
 vImageConvert_ARGB8888ToRGB16U
 
 This function does 3 things.
 1. Converts 8-bit unsigned ARGB interleaved pixels into 16-bit unsigned RGB interleaved pixels.
 2. Changes the order of channels according to permuteMap.
 3. Selects between the result pixel and the backgroundColor according to the bits in copyMask.
 
 permuteMap[i] = 0, 1, 2, or 3 to specify how we permute each channel.
 
 permuteMap[0] tells which channel in ARGB8888 will be used as the 1st channel (R) in the result RGB16U.
 permuteMap[1] tells which channel in ARGB8888 will be used as the 2nd channel (G) in the result RGB16U.
 permuteMap[2] tells which channel in ARGB8888 will be used as the 3rd channel (B) in the result RGB16U.
 
 copyMask = _ _ _ _  ; 3 digit binary
 100 tells if we want to use 1st channel in backgroundColor as the value of channel R in the result.
 010 tells if we want to use 2nd channel in backgroundColor as the value of channel G in the result.
 001 tells if we want to use 3rd channel in backgroundColor as the value of channel B in the result.
 
 The per-pixel operation is:
 
 Pixel_8888 *srcPixel;
 Pixel_16U *destPixel;
 uint8_t result8, r8, g8, b8;
 uint16_t result[3];
 uint8_t mask = 0x4;
 
 //Permute
 r8 = srcPixel[permuteMap[0]];
 g8 = srcPixel[permuteMap[1]];
 b8 = srcPixel[permuteMap[2]];
 srcPixel += 4;
 
 //Convert
 result[0] = (r8 * 65535U + 127U) / 255U;
 result[1] = (g8 * 65535U + 127U) / 255U;
 result[2] = (b8 * 65535U + 127U) / 255U;
 
 //Select
 if( mask & copyMask )
 result[0] = backgroundColor[0];
 mask = mask >> 1;
 if( mask & copyMask )
 result[1] = backgroundColor[1];
 mask = mask >> 1;
 if( mask & copyMask )
 result[2] = backgroundColor[2];
 
 destPixel[0] = result[0];
 destPixel[1] = result[1];
 destPixel[2] = result[2];
 destPixel += 3;
 
 Operands:
 ---------
 src : A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 dest : A pointer to vImage_Buffer that references 16-bit RGB interleaved destination pixels.
 permuteMap : Values that can be used to switch the channel order as the above example. permuteMap[0] is for R in the dest ARGB8888,  permuteMap[1] is for G in the dest ARGB8888, and  permuteMap[2] is for B in the dest ARGB8888.
 copyMask : A mask to choose between the result and backgroundColor.
 backgroudColor : A pointer to Pixel_16U that references 16-bit ARGB values which can replace the result pixels with. Pixel_16U backgroundColor[3] = {red, green, blue};
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 kvImageInvalidParameter            Is returned when the values in permuteMap[i] is not one of 0, 1, 2, or 3.
 kvImageNullPointerArgument         Is returned when backgroundColorPtr is NULL.
 
 This function doesn't work in place.
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB8888ToRGB16U(const vImage_Buffer *src, const vImage_Buffer *dest, const uint8_t permuteMap[3], uint8_t copyMask, const Pixel_16U backgroundColor[3], vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,5) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


/*
 vImageByteSwap_Planar16U
 
 This function does byteswap 16-bit pixel.
 
 Operands:
 ---------
 src  : A pointer to vImage_Buffer that references 16-bit source pixels.
 dest : A pointer to vImage_Buffer that references 16-bit destination pixels.
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 
 This function can work in place.
 */

VIMAGE_PF vImage_Error vImageByteSwap_Planar16U(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));



/*
 vImageFlatten_ARGB8888
 
 This function does a flattening operation on ARGB8888.
 A flattening operation is an alpha composite against a solid background color.
 
 The per-pixel operation is:
 
 resultAlpha = (pixelAlpha * 255 + (255 - pixelAlpha) * backgroundAlpha + 127) / 255
 if(isImagePremultiplied)
 {
 resultColor = (pixelColor * 255 + (255 - pixelAlpha) * backgroundColor + 127) / 255
 }
 else
 {
 resultColor = (pixelColor * pixelAlpha + (255 - pixelAlpha) * backgroundColor + 127) / 255
 }
 
 Operands:
 ---------
 src  : A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 dest : A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 backgroudColorPtr : A pointer to Pixel_8888 that references 8-bit premultiplied ARGB background color.
 isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 kvImageNullPointerArgument         Is returned when argbBackgroundColorPtr is NULL.
 
 This function can work in place.
 */

VIMAGE_PF vImage_Error  vImageFlatten_ARGB8888(const vImage_Buffer *argbSrc, const vImage_Buffer *argbDst, const Pixel_8888 argbBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageFlatten_RGBA8888
 
 This function does flattening operation on RGBA8888.
 A flattening operation is an alpha composite against a solid background color.
 
 The per-pixel operation is:
 
 resultAlpha = (pixelAlpha * 255 + (255 - pixelAlpha) * backgroundAlpha + 127) / 255
 if(isImagePremultiplied)
 {
 resultColor = (pixelColor * 255 + (255 - pixelAlpha) * backgroundColor + 127) / 255
 }
 else
 {
 resultColor = (pixelColor * pixelAlpha + (255 - pixelAlpha) * backgroundColor + 127) / 255
 }
 
 Operands:
 ---------
 src  : A pointer to vImage_Buffer that references 8-bit RGBA interleaved source pixels.
 dest : A pointer to vImage_Buffer that references 8-bit RGBA interleaved destination pixels.
 backgroudColorPtr : A pointer to Pixel_8888 that references 8-bit premultiplied RGBA background color.
 isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 kvImageNullPointerArgument         Is returned when rgbaBackgroundColorPtr is NULL.
 
 This function can work in place.
 BGRA format can be used as well.
 */

VIMAGE_PF vImage_Error  vImageFlatten_RGBA8888(const vImage_Buffer *rgbaSrc, const vImage_Buffer *rgbaDst, const Pixel_8888 rgbaBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageFlatten_ARGB16U
 
 This function does flattening operation on ARGB16U.
 A flattening operation is an alpha composite against a solid background color.
 
 The per-pixel operation is:
 
 resultAlpha = (pixelAlpha * 65535 + (65535 - pixelAlpha) * backgroundAlpha + 32767) / 65535
 if(isImagePremultiplied)
 {
 resultColor = (pixelColor * 65535 + (65535 - pixelAlpha) * backgroundColor + 32767) / 65535
 }
 else
 {
 resultColor = (pixelColor * pixelAlpha + (65535 - pixelAlpha) * backgroundColor + 32767) / 65535
 }
 
 Operands:
 ---------
 src  : A pointer to vImage_Buffer that references 16-bit ARGB interleaved source pixels.
 dest : A pointer to vImage_Buffer that references 16-bit ARGB interleaved destination pixels.
 backgroudColorPtr : A pointer to Pixel_ARGB_16U that references 16-bit ARGB premultiplied background color.
 isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 kvImageNullPointerArgument         Is returned when argbBackgroundColorPtr is NULL.
 
 This function can work in place.
 */

VIMAGE_PF vImage_Error  vImageFlatten_ARGB16U(const vImage_Buffer *argbSrc, const vImage_Buffer *argbDst, const Pixel_ARGB_16U argbBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageFlatten_RGBA16U
 
 This function does flattening operation on RGBA16U.
 A flattening operation is an alpha composite against a solid background color.
 
 The per-pixel operation is:
 
 resultAlpha = (pixelAlpha * 65535 + (65535 - pixelAlpha) * backgroundAlpha + 32767) / 65535
 if(isImagePremultiplied)
 {
 resultColor = (pixelColor * 65535 + (65535 - pixelAlpha) * backgroundColor + 32767) / 65535
 }
 else
 {
 resultColor = (pixelColor * pixelAlpha + (65535 - pixelAlpha) * backgroundColor + 32767) / 65535
 }
 
 Operands:
 ---------
 src  : A pointer to vImage_Buffer that references 16-bit RGBA interleaved source pixels.
 dest : A pointer to vImage_Buffer that references 16-bit RGBA interleaved destination pixels.
 backgroudColorPtr : A pointer to Pixel_ARGB_16U that references 16-bit RGBA premultiplied background color.
 isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 kvImageNullPointerArgument         Is returned when rgbaBackgroundColorPtr is NULL.
 
 This function can work in place.
 BGRA format can be used as well.
 */

VIMAGE_PF vImage_Error  vImageFlatten_RGBA16U(const vImage_Buffer *rgbaSrc, const vImage_Buffer *rgbaDst, const Pixel_ARGB_16U rgbaBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));



/*
 vImageFlatten_ARGB16Q12
 
 This function does flattening operation on ARGB16Q12.
 A flattening operation is an alpha composite against a solid background color.
 
 The per-pixel operation is:
 
 pixelAlpha = CLAMP( 0, pixelAlpha, 4096);
 resultAlpha = (pixelAlpha * 4096 + (4096 - pixelAlpha) * backgroundAlpha + 2048) >> 12;
 if(isImagePremultiplied)
 {
 resultColor = (pixelColor * 4096 + (4096 - pixelAlpha) * backgroundColor + 2048) >> 12
 }
 else
 {
 resultColor = (pixelColor * pixelAlpha + (4096 - pixelAlpha) * backgroundColor + 2048) >> 12
 }
 
 Whether the function attempts to clamp the case when the |resultColor| >= 8.0 is undefined.
 
 Operands:
 ---------
 src  : A pointer to vImage_Buffer that references 16Q12 ARGB interleaved source pixels.
 dest : A pointer to vImage_Buffer that references 16Q12 ARGB interleaved destination pixels.
 backgroudColorPtr : A pointer to Pixel_ARGB_16S that references 16-bit ARGB16Q12 premultiplied background color.
 isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 kvImageNullPointerArgument         Is returned when argbBackgroundColorPtr is NULL.
 
 This function can work in place. Pixels are assumed to be in native-endian byte order.
 */
VIMAGE_PF vImage_Error  vImageFlatten_ARGB16Q12(const vImage_Buffer *argbSrc, const vImage_Buffer *argbDst, const Pixel_ARGB_16S argbBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error  vImageFlatten_RGBA16Q12(const vImage_Buffer *argbSrc, const vImage_Buffer *argbDst, const Pixel_ARGB_16S argbBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));



/*
 vImageFlatten_ARGBFFFF
 
 This function does flattening operation on ARGBFFFF.
 A flattening operation is an alpha composite against a solid background color.
 
 The per-pixel operation is:
 
 resultAlpha = pixelAlpha + (1 - pixelAlpha) * backgroundAlpha
 if(isImagePremultiplied)
 {
 resultColor = pixelColor + (1 - pixelAlpha) * backgroundColor
 }
 else
 {
 resultColor = pixelColor * pixelAlpha + (1 - pixelAlpha) * backgroundColor
 }
 
 Operands:
 ---------
 src  : A pointer to vImage_Buffer that references float ARGB interleaved source pixels.
 dest : A pointer to vImage_Buffer that references float ARGB interleaved destination pixels.
 backgroudColorPtr : A pointer to Pixel_FFFF that references float premultiplied ARGB background color.
 isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 kvImageNullPointerArgument         Is returned when argbBackgroundColorPtr is NULL.
 
 This function can work in place.
 */

VIMAGE_PF vImage_Error  vImageFlatten_ARGBFFFF(const vImage_Buffer *argbSrc, const vImage_Buffer *argbDst, const Pixel_FFFF argbBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageFlatten_RGBAFFFF
 
 This function does flattening operation on RGBAFFFF.
 A flattening operation is an alpha composite against a solid background color.
 
 The per-pixel operation is:
 
 resultAlpha = pixelAlpha + (1 - pixelAlpha) * backgroundAlpha
 if(isImagePremultiplied)
 {
 resultColor = pixelColor + (1 - pixelAlpha) * backgroundColor
 }
 else
 {
 resultColor = pixelColor * pixelAlpha + (1 - pixelAlpha) * backgroundColor
 }
 
 Operands:
 ---------
 src  : A pointer to vImage_Buffer that references float RGBA interleaved source pixels.
 dest : A pointer to vImage_Buffer that references float RGBA interleaved destination pixels.
 backgroudColorPtr : A pointer to Pixel_FFFF that references float RGBA premultiplied background color.
 isImagePremultiplied : True means input colors are premultiplied. False means input colors are not premultiplied.
 
 Flags:
 ------
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 Return Value:
 -------------
 kvImageNoError                     Is returned when there was no error.
 kvImageRoiLargerThanInputBuffer    Is returned when the height and width of the source are less than the height and width of the destination buffer, respectively.
 kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 kvImageNullPointerArgument         Is returned when rgbaBackgroundColorPtr is NULL.
 
 This function can work in place.
 BGRA format can be used as well.
 */

VIMAGE_PF vImage_Error  vImageFlatten_RGBAFFFF(const vImage_Buffer *rgbaSrc, const vImage_Buffer *rgbaDst, const Pixel_FFFF rgbaBackgroundColorPtr, bool isImagePremultiplied, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageConvert_Planar1toPlanar8
 vImageConvert_Planar2toPlanar8
 vImageConvert_Planar4toPlanar8
 
 These functions convert from 1-, 2-, or 4-bit per pixel to 8-bit per pixel
 planar formats.
 
 Function Arguments:
 -------------------
 src         Pointer to the source vImage_Buffer object.  Because the
 source pixel format is smaller than a byte, there are
 multiple pixels in each byte of the data buffer.  These
 pixels are interpreted as being in big endian order (i.e.
 the low-indexed pixel is in the high-order bits of the
 byte).
 
 Sub-byte indexing of scanlines is unsupported, because the
 data and rowBytes fields of the buffer are specified in
 whole bytes.
 
 Widths, however, are measured in pixels, so a scanline may
 end in the middle of a byte.  If this occurs, the contents
 of any unused bits of the final byte are ignored.
 
 dest        Pointer to the destination vImage_Buffer object.
 
 flags       The following flags are allowed:
 
 kvImageDoNotTile - disables internal threading.  You may
 want to specify this if you have your own threading
 scheme and need to avoid interference.
 
 kvImageGetTempBufferSize - does no work and returns zero,
 as these functions do not use temp buffers.
 
 Operation:
 ----------
 For each pixel in the destination image, the resulting value is the
 corresponding pixel value from the source image multiplied by 255, 85,
 or 17 (for Planar1, Planar2, or Planar4, respectively).
 
 
 Return values:
 --------------
 kvImageNoError                     Success
 kvImageUnknownFlagsBit             No work was done because an unknown bit was
 set in the flags parameter.
 kvImageRoiLargerThanInputBuffer    No work was done because the source
 image isn't large enough to cover the
 destination image.
 
 These functions do not work in place.
 */

VIMAGE_PF vImage_Error vImageConvert_Planar1toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_Planar2toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_Planar4toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageConvert_Indexed1toPlanar8
 vImageConvert_Indexed2toPlanar8
 vImageConvert_Indexed4toPlanar8
 
 These functions convert from 1-, 2-, or 4-bit per pixel indexed to 8-bit
 per pixel planar format.
 
 Function Arguments:
 -------------------
 src         Pointer to the source vImage_Buffer object.  Because the
 source pixel format is smaller than a byte, there are
 multiple pixels in each byte of the data buffer.  These
 pixels are interpreted as being in big endian order (i.e.
 the low-indexed pixel is in the high-order bits of the
 byte).
 
 Sub-byte indexing of scanlines is unsupported, because the
 data and rowBytes fields of the buffer are specified in
 whole bytes.
 
 Widths, however, are measured in pixels, so a scanline may
 end in the middle of a byte.  If this occurs, the contents
 of any unused bits of the final byte are ignored.
 
 dest        Pointer to the destination vImage_Buffer object.
 
 colors      Color table in which to lookup pixel values for destination
 image.
 
 flags       The following flags are allowed:
 
 kvImageDoNotTile - disables internal threading.  You may
 want to specify this if you have your own threading
 scheme and need to avoid interference.
 
 kvImageGetTempBufferSize - does no work and returns zero,
 as these functions do not use temp buffers.
 
 Operation:
 ----------
 For each pixel in the destination image, the value is looked up in the
 color table using the corresponding pixel value from the source image
 as an index.
 
 Return values:
 --------------
 kvImageNoError                     Success
 kvImageUnknownFlagsBit             No work was done because an unknown bit was
 set in the flags parameter.
 kvImageRoiLargerThanInputBuffer    No work was done because the source
 image isn't large enough to cover the
 destination image.
 
 These functions do not work in place.
 */


VIMAGE_PF vImage_Error vImageConvert_Indexed1toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 colors[2], const vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_Indexed2toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 colors[4], const vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_Indexed4toPlanar8(const vImage_Buffer *src, const vImage_Buffer *dest, const Pixel_8 colors[16], const vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageConvert_Planar8toPlanar1
 vImageConvert_Planar8toPlanar2
 vImageConvert_Planar8toPlanar4
 
 These functions convert from 8-bit per pixel to 1-, 2-, or 4-bit per pixel
 planar formats.
 
 Function Arguments:
 -------------------
 src         Pointer to the source vImage_Buffer object
 
 dest        Pointer to the destination vImage_Buffer object.  Because
 the destination pixel format is smaller than a byte, there
 are multiple pixels in each byte of the data buffer.  These
 pixels are interpreted as being in big endian order (i.e.
 the low-indexed pixel is in the high-order bits of the
 byte).
 
 Sub-byte indexing of scanlines is unsupported, because the
 data and rowBytes fields of the buffer are specified in
 whole bytes.
 
 Widths, however, are measured in pixels, so a scanline may
 end in the middle of a byte.  If this occurs, the contents
 of any unused bits of the final byte are unspecified.
 
 tempBuffer  Pointer to temporary buffer for the routine to use for
 scratch space.  If non-NULL, the buffer must be at least
 as large as the value returned by calling this function
 with the kvImageGetTempBufferSize flag.  If NULL, this
 function will still work, but may allocate and free a
 scratch buffer internally.
 
 dither      Type of dithering to apply to the image, if any.  Options:
 
 kvImageConvert_DitherNone - apply no dithering; input values
 are rounded to the nearest value representable in the
 destination format.
 kvImageConvert_DitherOrdered - pre-computed blue noise is
 added to the image before rounding to the values in
 the destination format.  The offset into this blue
 noise is randomized per-call to avoid visible artifacts
 if you do your own tiling or call the function on
 sequential frames of video.
 kvImageConvert_DitherOrderedReproducible - pre-computed
 blue noise is added to the image before rounding to the
 values in the destination format.  The offset into the
 blue noise is the same for every call to allow users
 to get reproducible results.
 kvImageConvert_DitherFloydSteinberg - Floyd-Steinberg
 dithering is applied to the image.
 kvImageConvert_DitherAtkinson - Atkinson dithering is
 applied to the image, for the old timers.
 
 The ordered dither methods may be further influenced by shaping the
 distribution of the noise using the gaussian and uniform options below.
 These options are OR-ed with kvImageConvert_DitherOrdered / kvImageCon-
 vert_DitherOrderedReproducible:
 
 kvImageConvert_OrderedGaussianBlue - when using an ordered dither
 pattern, distribute the noise according to a gaussian
 distribution. This generally gives more pleasing images --
 less noisy and perhaps a little more saturated -- but color
 fidelity can suffer. Its effect is between kvImageConvert_DitherNone
 and kvImageConvert_DitherOrdered | kvImageConvert_DitherUniform.
 This is the default for kvImageConvert_DitherOrdered and
 kvImageConvert_DitherOrderedReproducible.
 
 kvImageConvert_OrderedUniformBlue - when using an ordered dither
 pattern, distribute the noise uniformly. This generally gives
 best color fidelity, but the resulting image is noisier and more
 obviously dithered. This is usually the best choice when low
 bitdepth content is drawn next to high bitdepth content and in other
 circumstances where subtle changes to color arising from the conversion
 could be easily noticed. It may be a poor choice when the image
 is likely to be enlarged -- this would cause the noise to become
 more evident-- and for very flat / synthetic content with little
 inherent noise. The enlargement problem may be avoided by enlarging
 first at high bitdepth, then convert to lower bitdepth.
 
 To clarify: "Blue" noise is not blue, nor does it operate solely on the blue
 color channel. Blue noise is monochrome noise that is added to all color
 channels equally. The name arises from blue light, which has a higher frequency
 than other colors of visible light. Thus, blue noise is noise which is
 weighted heavily towards high frequencies. Low frequency noise tends to have
 visible shapes in it that would become apparent in an image if it was added in,
 so it is excluded from the dither pattern.
 
 flags       The following flags are allowed:
 
 kvImageDoNotTile - disables internal threading.  You may
 want to specify this if you have your own threading
 scheme and need to avoid interference.
 
 kvImageGetTempBufferSize - does no work, but returns the
 required size of tempBuffer for this routine.
 
 Operation:
 ----------
 For a brief description of each dither method, see dither above.
 
 Notes:
 The results for Floyd-Steinberg and Atkinson dithering methods depend on the results
 of pixels around each result pixel. Consequently, these methods do not tile well. (Tiling
 can cause visible artifacts at tile boundaries because residuals are not propagated to the
 next tile in a manner consistent with how it is propagated within a tile.) You should pass
 the entire image in a single call for good results with Atkinson and Floyd-Steinberg.
 
 The ordered dithering method is suitable for tiled / multithreaded / scanline-at-a-time
 execution. In addition to being spatially random, the ordered dithering pattern is also
 temporally random. This is necessary to prevent stripes when it is invoked scanline-at-a-time.
 Temporal randomness also prevents visible walking of the dither pattern across the image
 when used for video. Because it is temporally random, results from this filter are not
 reproducible.
 
 To get reproducible results with ordered dithering, use the OrderedReproducible
 dithering attribute.
 
 The dither none option will produce reproducible results in all calling contexts, but
 is prone to obvious banding in images, especially in regions of an image with a smooth
 gradient.
 
 Return values:
 --------------
 kvImageNoError                     Success
 kvImageUnknownFlagsBit             No work was done because an unknown bit was
 set in the flags parameter.
 kvImageRoiLargerThanInputBuffer    No work was done because the source
 image isn't large enough to cover the
 destination image.
 kvImageInvalidParameter            An unrecognized or unsupported value was
 specified for dither.
 
 These functions do not work in place.
 */

/* See description above for the meaning of these contants */
enum {
    kvImageConvert_DitherNone                   = 0,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_DitherOrdered                = 1,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_DitherOrderedReproducible    = 2,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_DitherFloydSteinberg         = 3,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_DitherAtkinson               = 4,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    
    /* Gaussian vs. uniform distribution for ordered dithering patterns. By default ordered dithering uses gaussian blue noise. */
    kvImageConvert_OrderedGaussianBlue          = 0,         /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_OrderedUniformBlue           = (1<<28),   /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
    kvImageConvert_OrderedNoiseShapeMask        = (0xfU<<28) /* __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0) */
};

VIMAGE_PF vImage_Error vImageConvert_Planar8toPlanar1(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_Planar8toPlanar2(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_Planar8toPlanar4(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageConvert_Planar8toIndexed1
 vImageConvert_Planar8toIndexed2
 vImageConvert_Planar8toIndexed4
 
 These functions convert from 8-bit per pixel planar to 1-, 2-, or 4-bit
 per pixel indexed formats.
 
 Function Arguments:
 -------------------
 src         Pointer to the source vImage_Buffer object
 
 dest        Pointer to the destination vImage_Buffer object.  Because
 the destination pixel format is smaller than a byte, there
 are multiple pixels in each byte of the data buffer.  These
 pixels are interpreted as being in big endian order (i.e.
 the low-indexed pixel is in the high-order bits of the
 byte).
 
 Sub-byte indexing of scanlines is unsupported, because the
 data and rowBytes fields of the buffer are specified in
 whole bytes.
 
 Widths, however, are measured in pixels, so a scanline may
 end in the middle of a byte.  If this occurs, the contents
 of any unused bits of the final byte are unspecified.
 
 tempBuffer  Pointer to temporary buffer for the routine to use for
 scratch space.  If non-NULL, the buffer must be at least
 as large as the value returned by calling this function
 with the kvImageGetTempBufferSize flag.  If NULL, this
 function will still work, but may allocate and free a
 scratch buffer internally.
 
 colors      Color table to use for the destination.
 
 If you want us to compute a color table for you, initialize
 the table to all zeros:
 
 Pixel_8 colors[4] = { 0 };
 vImageConvert_Planar8toIndexed2(src, dest, colors, dither, flags);
 
 We will then compute an appropriate color table for the
 image before performing the conversion.
 
 dither      Type of dithering to apply to the image, if any.  See the
 discussion for vImageConvert_Planar8toPlanar1 for more
 details.
 
 flags       The following flags are allowed:
 
 kvImageDoNotTile - disables internal threading.  You may
 want to specify this if you have your own threading
 scheme and need to avoid interference.
 
 kvImageGetTempBufferSize - does no work, but returns the
 required size of tempBuffer for this routine.
 
 Operation:
 ----------
 See dither above.
 
 Return values:
 --------------
 kvImageNoError                     Success
 kvImageUnknownFlagsBit             No work was done because an unknown bit was
 set in the flags parameter.
 kvImageRoiLargerThanInputBuffer    No work was done because the source
 image isn't large enough to cover the
 destination image.
 kvImageInvalidParameter            A non-zero color table was not ordered
 correctly, or an unrecognized or
 unsupported value was specified for dither.
 
 These functions do not work in place.
 */

VIMAGE_PF vImage_Error vImageConvert_Planar8toIndexed1(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, Pixel_8 colors[2], int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_Planar8toIndexed2(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, Pixel_8 colors[4], int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_Planar8toIndexed4(const vImage_Buffer *src, const vImage_Buffer *dest, void *tempBuffer, Pixel_8 colors[16], int dither, const vImage_Flags flags) VIMAGE_NON_NULL(1,2,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*  vImageConvert_8to16Q12
 vImageConvert_RGB888toPlanar16Q12
 vImageConvert_ARGB8888toPlanar16Q12
 
 All three functions convert 8-bit pixel format to 16-bit format with 12
 fractional bits.  The conversion is performed as follows:
 
 uint16_t dest = ((src << 12) + 127)/255;
 
 Source pixel values of 0 are mapped to 0, and source pixel values of 255
 are mapped to 0x1000 (4096).  No larger values are produced by this
 conversion, which provides some headroom to help subsequent operations
 avoid overflow or clipping.
 
 vImageConvert_8to16Q12 takes a single source buffer and a single
 destination buffer and simply does the conversion.
 
 vImageConvert_RGB888toPlanar16Q12 has three destination buffers, and
 de-interleaves while it converts.
 
 vImageConvert_ARGB8888toPlanar16Q12 takes four destination buffers, and
 also de-interleaves.  Any channel order may be handled by the latter two
 functions by permuting the order in which the destination buffers are
 passed as arguments.
 
 
 
 The only supported flags are:
 
 kvImageDoNotTile            Turns off internal multithreading. You may
 wish to do this if you have your own
 multithreading scheme to avoid having the
 two interfere with one another.
 
 kvImageGetTempBufferSize    Returns zero, as the routine does not use
 a temp buffer.
 
 Passing any other flag will result in no work being done and an error
 code being returned.
 
 Return Value:
 -------------
 kvImageNoError                  is returned when there was no error.
 kvImageBufferSizeMismatch       the destination buffers do not have the
 same size as each other
 kvImageRoiLargerThanInputBuffer The destination buffers are larger than the
 source buffer.
 kvImageUnknownFlagsBit          is returned when there is a unknown flag.
 
 This function will not operate in place.
 */

VIMAGE_PF vImage_Error vImageConvert_8to16Q12(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_RGB888toPlanar16Q12(const vImage_Buffer *src, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_ARGB8888toPlanar16Q12(const vImage_Buffer *src, const vImage_Buffer *alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*  vImageConvert_16Q12to8
 vImageConvert_Planar16Q12toRGB888
 vImageConvert_Planar16Q12toARGB8888
 
 All three functions convert 16-bit format with 12 fractional bits to 8-bit.
 The conversion is performed as follows:
 
 uint8_t dest = clamp(src, 0, 4096)*255 + 2048 >> 12
 
 Source pixel values of 0 are mapped to 0, and source pixel values of 4088
 or greater are mapped to 255.
 
 vImageConvert_Planar16Q12toRGB888 and vImageConvert_Planar16Q12toARGB8888
 interleave data from three or four buffers respectively while performing
 the conversion.
 
 The only supported flags are:
 
 kvImageDoNotTile            Turns off internal multithreading. You may
 wish to do this if you have your own
 multithreading scheme to avoid having the
 two interfere with one another.
 
 kvImageGetTempBufferSize    Returns zero, as the routine does not use
 a temp buffer.
 
 Passing any other flag will result in no work being done and an error
 code being returned.
 
 Return Value:
 -------------
 kvImageNoError                  is returned when there was no error.
 kvImageBufferSizeMismatch       the destination buffers do not have the
 same size as each other
 kvImageRoiLargerThanInputBuffer The destination buffers are larger than the
 source buffer.
 kvImageUnknownFlagsBit          is returned when there is a unknown flag.
 
 This function will not operate in place.
 */

VIMAGE_PF vImage_Error vImageConvert_16Q12to8(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_Planar16Q12toRGB888(const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_Planar16Q12toARGB8888(const vImage_Buffer *alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


/*!
 @function vImageConvert_16Q12to16F
 @abstract Convert 16Q12 (16-bit format with 12 fractional bits) to half-precision floating-point.
 
 @discussion Source pixel values of 0 are mapped to 0, and source pixel values of (Pixel_16Q12) 4096
 are mapped to (Pixel_16F) 1.0f.
 @note Works in place provided that src->data == dest->data && src->rowBytes == dest->rowBytes.
 
 @param src              The input image.
 @param dest             A pointer to a preallocated vImage_Buffer to receive the resulting image.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 \p kvImageGetTempBufferSize    Returns zero, as the routine does not use a temp buffer.
 
 @return kvImageNoError                      There was no error.
 @return kvImageBufferSizeMismatch           The destination buffers do not have the
 same size as each other
 @return kvImageRoiLargerThanInputBuffer     The destination buffers are larger than the
 source buffer.
 @return kvImageUnknownFlagsBit              Unknown flag(s) provided.
 */
VIMAGE_PF vImage_Error vImageConvert_16Q12to16F(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!
 @function vImageConvert_16Q12toRGB16F
 @abstract Convert 16Q12 and interleave (16-bit format with 12 fractional bits) to half-precision floating-point.
 
 @discussion Interleaves data from three source buffers while performing the format conversion.
 Source pixel values of 0 are mapped to 0, and source pixel values of (Pixel_16Q12) 4096
 are mapped to (Pixel_16F) 1.0f.
 @note Does not work in place.
 
 @param red              The red channel of the input image.
 @param green            The green channel of the input image.
 @param blue             The blue channel of the input image.
 @param dest             A pointer to a preallocated vImage_Buffer to receive the resulting chunky image.
 
 @param flags
 \p kvImageDoNotTile             Disables internal multithreading, if any.
 \p kvImageGetTempBufferSize     Returns zero, as the routine does not use a temp buffer.
 
 @return kvImageNoError                      There was no error.
 @return kvImageBufferSizeMismatch           The destination buffers do not have the
 same size as each other
 @return kvImageRoiLargerThanInputBuffer     The destination buffers are larger than the
 source buffer.
 @return kvImageUnknownFlagsBit              Unknown flag(s) provided.
 */
VIMAGE_PF vImage_Error vImageConvert_Planar16Q12toRGB16F(const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!
 @function vImageConvert_Planar16Q12toARGB16F
 @abstract Convert and interleave 16Q12 (16-bit format with 12 fractional bits) to half-precision floating-point.
 
 @discussion Interleaves data from four source buffers while performing the format conversion.
 Source pixel values of 0 are mapped to 0, and source pixel values of (Pixel_16Q12) 4096
 are mapped to (Pixel_16F) 1.0f.
 @note Does not work in place.
 
 @param alpha            The alpha channel of the input image.
 @param red              The red channel of the input image.
 @param green            The green channel of the input image.
 @param blue             The blue channel of the input image.
 @param dest             A pointer to a preallocated vImage_Buffer to receive the resulting chunky image.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 \p kvImageGetTempBufferSize    Returns zero, as the routine does not use a temp buffer.
 
 @return kvImageNoError                      There was no error.
 @return kvImageBufferSizeMismatch           The destination buffers do not have the
 same size as each other
 @return kvImageRoiLargerThanInputBuffer     The destination buffers are larger than the
 source buffer.
 @return kvImageUnknownFlagsBit              Unknown flag(s) provided.
 */
VIMAGE_PF vImage_Error vImageConvert_Planar16Q12toARGB16F(const vImage_Buffer *alpha, const vImage_Buffer *red, const vImage_Buffer *green, const vImage_Buffer *blue, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!
 @function vImageConvert_16Fto16Q12
 @abstract Convert half-precision floating-point to 16Q12 (16-bit format with 12 fractional bits).
 
 @discussion Source pixel values of 0 are mapped to 0, and source pixel values of (Pixel_16F) 1.0f
 are mapped to (Pixel_16Q12) 4096.
 @note Works in place provided that src->data == dest->data && src->rowBytes == dest->rowBytes.
 
 @param src              The input image.
 @param dest             A pointer to a preallocated vImage_Buffer to receive the resulting image.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 \p kvImageGetTempBufferSize    Returns zero, as the routine does not use a temp buffer.
 
 @return kvImageNoError                      There was no error.
 @return kvImageBufferSizeMismatch           The destination buffers do not have the
 same size as each other
 @return kvImageRoiLargerThanInputBuffer     The destination buffers are larger than the
 source buffer.
 @return kvImageUnknownFlagsBit              Unknown flag(s) provided.
 */
VIMAGE_PF vImage_Error vImageConvert_16Fto16Q12(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));


/*
 vImageConvert_16Q12toF
 vImageConvert_Fto16Q12
 
 Convert 16-bit format with 12 fractional bits to floating-point.
 The conversion is performed as follows:
 
 float vImageConvert_16Q12toF_result = sample_16Q12 / 4096.0f
 Pixel_16Q12 vImageConvert_Fto16Q12_result = CLAMP( -32768, lrintf(sample_float * 4096.0f), 32767)
 
 Source pixel values of 0 are mapped to 0, and source pixel values of (Pixel_16Q12) 4096
 is mapped to (Pixel_F) 1.0f.
 
 The only supported flags are:
 
 kvImageDoNotTile            Turns off internal multithreading. You may
 wish to do this if you have your own
 multithreading scheme to avoid having the
 two interfere with one another.
 
 kvImageGetTempBufferSize    Returns zero, as the routine does not use
 a temp buffer. Does no work
 
 Passing any other flag will result in no work being done and an error
 code being returned.
 
 Return Value:
 -------------
 kvImageNoError                  is returned when there was no error.
 kvImageRoiLargerThanInputBuffer one or more source buffers is smaller than the destination buffer.
 kvImageUnknownFlagsBit          is returned when there is a unknown flag.
 
 These functions will operate in place provided that src->data == dest->data && src->rowBytes == dest->rowBytes.
 
 */

VIMAGE_PF vImage_Error vImageConvert_16Q12toF(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_Fto16Q12(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));

/*
 vImageConvert_16Q12to16U
 vImageConvert_16Uto16Q12
 
 Convert 16-bit format with 12 fractional bits to floating-point.
 The conversion is performed as follows:
 
 Pixel_16U vImageConvert_16Q12to16U_result = CLAMP( 0, (sample_16Q12 * 65535 + 2048) >> 12, 65535 )
 Pixel_16Q12 vImageConvert_16Uto16Q12_result = (sample_16U * 4096 + 32767) / 65535;
 
 Source pixel values of 0 are mapped to 0, and source pixel values of (Pixel_16Q12) 4096
 is mapped to (Pixel_16U) 65535.
 
 The only supported flags are:
 
 kvImageDoNotTile            Turns off internal multithreading. You may
 wish to do this if you have your own
 multithreading scheme to avoid having the
 two interfere with one another.
 
 kvImageGetTempBufferSize    Returns zero, as the routine does not use
 a temp buffer. Does no work
 
 Passing any other flag will result in no work being done and an error
 code being returned.
 
 Return Value:
 -------------
 kvImageNoError                  is returned when there was no error.
 kvImageRoiLargerThanInputBuffer one or more source buffers is smaller than the destination buffer.
 kvImageUnknownFlagsBit          is returned when there is a unknown flag.
 
 These functions will operate in place provided that src->data == dest->data && src->rowBytes == dest->rowBytes.
 
 */

VIMAGE_PF vImage_Error vImageConvert_16Q12to16U(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));
VIMAGE_PF vImage_Error vImageConvert_16Uto16Q12(const vImage_Buffer *src, const vImage_Buffer *dest, vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.9), ios(7.0), watchos(1.0), tvos(7.0));


/*
 
 YpCbCr image formats:
 =====================
 Some details about video formats are provided below to provide some context for interpreting parameters passed to YpCbCr conversion functions.
 
 Luminance and Chrominance
 -------------------------
 Luminance is the brightness in an image. An example might be the image visible on a black and white television. Luminance (Y, Y' or Yp)
 is defined as a weighted sum of the color components, usually weighted according to the relative ability of red, green and blue to cause
 perceived brightness changes in an image. For example for ITU-Recommendation BT.709 images, the Y component is given as:
 
 Y = 0.2126*R + 0.7152*G + 0.0722*B
 
 Chrominance (Cb and Cr) is the correction applied to the luminance to add color information. For ITU-R BT.709 they would be:
 
 Cb  = 0.5389*(B-Y)
 Cr  = 0.6350*(R-Y)
 
 Together, these can be written as an invertible 3x3 color matrix that converts {R,G,B} to {Yp, Cb, Cr}.
 
 Since chrominance is calculated as the difference between two unsigned values, it itself is signed. Typically, a large bias is added to
 the chrominance value when it is encoded as an unsigned integer to make negative values representable. For example, 8-bit chrominance
 values typically have an implicit +128 in them. To convert a full range 8-bit chroma value to an unbiased floating point representation,
 it would be:
 
 Pb = (Cb - 128) / 127
 
 and so a full range chrominance value actually varies in the range [1,255] indicating [-1.0, 1.0]. See also Video Range.
 
 YpCbCr video color representations are typically specified in terms of a RGB colorspace and a typically 3x3 matrix to convert RGB to YpCbCr.
 The RGB colorspace itself is also defined relative to an absolute XYZ colorspace.  This is typically done using some x,y,z (little xyz!)
 primaries defining the size of the color cube and a transfer function that describes the conversion from linear color to non-linear RGB. The
 transfer function is usually of a form that can be evaluated with vImagePiecewiseGamma_<fmt> (see vImage/Transform.h). It should be noted that
 both of these are customarily defined in the opposite direction from an ICC profile. Whereas an ICC profile is conversion from display colorspace
 to linear XYZ, video formats are from XYZ to YpCbCr. Thus, the matrices and the gamma are inverted.
 
 Chroma subsampling
 ------------------
 Since the human eye is better at getting positional information from luminance changes than chrominance changes, the chrominance signal is
 often subsampled relative to luminance. (For each chrominance sample, there may be 2 or 4 luminance ones.) This saves memory. See
 [sampling ratio] below.
 
 Chroma Siting
 -------------
 Chroma subsampling also brings with it the possibility of differences in how the chroma samples are positioned relative to the luminance samples.
 For example for 422, they may overlap the left one, or the right one, or be positioned between them. This is called chroma siting. Many video
 formats are available for a diversity of siting options. However, for OS X.10 and iOS 8, vImage does only the centered variant
 (kCVImageBufferChromaLocation_Center). Please file a bug report to request other siting modes where they are found to be necessary.
 
 Video Range
 -----------
 Video formats commonly do not use the entire representable range available to them to encode video data. A 8-bit video range signal may use
 the range [16,235] instead of [0,255] to represent the range of signal strengths [0,1.0] for luminance, and [16,240] for chroma. A video signal
 that uses the full [0,255] ([1,255] for chroma) is said to be full range.
 
 Pixel Blocks
 -------------
 Since some channels are sampled at a higher rate than other channels, it is common to group multiple pixels together in a block which is
 encoded or decoded as a unit. Blocks are useful because they are an integer multiple of a byte in size and describe a particular
 repeating component order that can be serviced in a loop. See [sampling ratio] below for common ways in which multiple YpCbCr pixels fit
 together in a block. An example might be a 2vuy image (422CbYpCrYp8 to vImage) which has luminance and chrominance for two pixels packed
 together in a block as {Cb, Yp, Cr, Yp}.  The chrominance is shared between the two pixels, but each has its own luminance.
 
 In all cases, the beginning of a scanline must also be the beginning of a block, and must be at least byte aligned.  We do not support cases where
 a block spans multiple block rows. If the width of an image is not a multiple of the block width (or height is not a multiple of a block height)
 and you are writing to a YpCbCr format, then the edge pixels are in effect duplicated (see kvImageEdgeExtend) until the image is a multiple of
 the block size and the larger image is encoded to YpCbCr. If you are converting from a subsampled YpCbCr image to a non-subsampled format, then
 we only write out the pixels that fit in the vImage_Buffer.height and vImage_Buffer.width provided. You should be careful to keep the original
 height and width, since edges of the wider images may look like image artifacts if they appear onscreen.
 
 Nomenclature used in vImage
 ---------------------------
 To cover the many different packing orders, chroma subsamplings and separate image planes, we adopt the following naming convention here
 as an extension of that commonly used here for RGB images:
 
 [sampling ratio][order of appearance of components in block][bitdepth](_[sampling ratio][order of appearance of components in block] for plane 2)...
 
 Examples:
 
 444YpCbCrA8        Each chunk is one pixel. Channels are 8-bit interleaved in the order A, Yp, Cb, Cr.  kCVPixelFormatType_4444YpCbCrA8
 422CbYpCrYp8        Each chunk is two horizontally adjacent pixels. Channels are 8-bit interleaved in the order Cb, Yp0, Cr, Yp0. (2vuy)
 422CbYpCrYp8_AA8   Like 422CbYpCrYp8 but with a separate alpha channel added. (kCVPixelFormatType_422YpCbCr_4A_8BiPlanar)
 
 The fields and behavior details of such formats are described below:
 
 [sampling ratio]
 ----------------
 The format begins with a three digit code commonly used for video formats that describes the relative frequencies with which luminance
 (Yp) and chrominance (Cb, Cr) are sampled, to enable rapid indexing of the formats for experienced professionals. For the rest of us,
 these are:
 
 444  Luminance and chrominance are sampled at the same rate
 422  Luminance is sampled at twice the rate of chrominance components in the horizontal dimension
 420  Luminance is sampled at twice the rate of chrominance components in both dimensions.
 ...
 
 If there is an alpha channel, it is assumed to be sampled at the same rate as luminance.
 
 [order of appearance of components in block]:
 --------------------------------------------
 For a 444 block, each component appears once and the block holds one pixel, so you
 just see the order of the components such as AYpCbCr much like we write ARGB. For a 422 block, there are two luminance for each Cb or Cr, so
 you will see a block order like YpCbYpCr and the block represents two pixels in a fully decoded image. Noticed that Yp is repeated twice.
 The pixels have different luminance but share the same chrominance values. In the case of 420 and 411, there is also vertical subsampling.
 In this case, the vImage_Buffer.rowBytes describes the stride from one block row to the next. (Each block row is two pixels tall.)
 
 In extreme cases with blocks that span more than two pixels, the block packing can become complicated, resulting in an exceptionally long name.
 This can happen for bit depths that are not a multiple of a byte, where the block size not only accommodates subsampling, but also byte alignment.
 Such cases may be abbreviated with the 'P' character, indicating Packed. An example is 422PCbYpCrYp10, which would otherwise have to be named
 422CrYpCbYpCbYpCbYpCrYpCrYp10. In such cases, the actual layout is given in the comments.
 
 
 [bitdepth]
 ----------
 This is the number of bits per component. Typically, all the channels have the same bit depth so it just appears at the end of the plane name.
 If there is a heterogeneous format, the bit depths are inserted between the channels where they change (e.g. 444Yp12CbCr10) for 12 bit Yp and
 10 bit CbCr in a 32-bit 444 block.
 
 [additional planes]
 -------------------
 Some YpCbCr formats have multiple planes. (That is, multiple vImage_Buffers.) It is common to have the Y data in one plane and CbCr packed in
 another plane, or perhaps alpha stored  separately. An underbar '_' shall separate the planes and the new plane will be named according to order
 of appearance of the block components. Subsampling may cause components in a plane to appear multiple times.  For example: 411YpYpCbYpYpCr8_AAAA8
 is a 411 format with alpha in a separate plane.  We see AAAA instead of A because each block holds 4 pixels and so the block contains alpha four
 times in that plane. Blocks in all planes have the same height and width for a particular format.
 
 
 Conversion to RGB and other colorspaces
 ----------------------------------------
 
 Unfortunately, the RGB colorspaces that commonly underlie YpCbCr formats are generally not the same as ones commonly used for RGB imaging in
 CoreGraphics. For example, ITU-R BT.709 is similar to sRGB but not the same. Consequently, simple conversion from YpCbCr data to RGB using
 the matrix functions provided here may not be the only step required for good color fidelity. A RGB -> RGB colorspace conversion may be
 required too.  Typically, this involves converting to linear color, applying a RGB->RGB conversion matrix, and then applying the new gamma.
 This can be done using vImagePiecewiseGamma_<fmt> and vImageMatrixMultiply_<fmt>. (We recommend planar 16Q12 for 8- and 10-bpc formats and
 floating point for higher bit depths.) However, some may find it simpler to use the interfaces on vImage_CVUtilities.h instead, which handle
 such details for you.
 
 */


/*!
 @function vImageConvert_YpCbCrToARGB_GenerateConversion
 
 @abstract Generates the conversion from a YpCbCr to a ARGB pixel format.
 
 @param matrix
 A pointer to vImage_YpCbCrToARGBMatrix that contains the matrix coefficients for the conversion
 from a YpCbCr to a ARGB pixel format.
 
 @param pixelRange
 A pointer to vImage_YpCbCrPixelRange that contains the pixel range information for the conversion
 from a YpCbCr to a ARGB pixel format.
 
 @param outInfo
 A pointer to vImage_YpCbCrToRGB will be initialized with the information for the conversion function
 will use later.
 
 @param inYpCbCrType
 A YpCbCrType to specify the input YpCbCr format.
 
 @param outARGBType
 A ARGBType to specify the output ARGB format.
 
 @param flags
 kvImagePrintDiagnosticsToConsole   Directs the function to print diagnostic information to the console in the event of failure.
 
 @discussion This function is used to create the vImage_YpCbCrToARGB conversion information necessary for all
 of YUV -> RGB conversion functions.
 
 For example, if we want to prepare for the conversion from 'yuvs' with ITU 601 video range to ARGB8888, then we
 need to do the following:
 
 <pre> @textblock
 VIMAGE_PF vImage_Error err = kvImageNoError;
 vImage_Flags flags = kvImageNoFlags;
 vImage_YpCbCrPixelRange pixelRange;
 vImage_YpCbCrToARGB outInfo;
 
 pixelRange.Yp_bias         =   16;     // encoding for Y' = 0.0
 pixelRange.CbCr_bias       =  128;     // encoding for CbCr = 0.0
 pixelRange.YpRangeMax      =  235;     // encoding for Y'= 1.0
 pixelRange.CbCrRangeMax    =  240;     // encoding for CbCr = 0.5
 pixelRange.YpMax           =  255;     // a clamping limit above which the value is not allowed to go. 255 is fastest. Use pixelRange.YpRangeMax if you don't want Y' > 1.
 pixelRange.YpMin           =    0;     // a clamping limit below which the value is not allowed to go. 0 is fastest. Use pixelRange.Yp_bias if you don't want Y' < 0.
 pixelRange.CbCrMax         =  255;     // a clamping limit above which the value is not allowed to go. 255 is fastest.  Use pixelRange.CbCrRangeMax, if you don't want CbCr > 0.5
 pixelRange.CbCrMin         =    0;     // a clamping limit above which the value is not allowed to go. 0 is fastest.  Use (2*pixelRange.CbCr_bias - pixelRange.CbCrRangeMax), if you don't want CbCr < -0.5
 //                ( pixelRange.CbCr_bias - (pixelRange.CbCrRangeMax - pixelRange.CbCr_bias) = 2*pixelRange.CbCr_bias - pixelRange.CbCrRangeMax )
 
 err = vImageConvert_YpCbCrToARGB_GenerateConversion(kvImageITU601_YpCbCrToARGBMatrix, &pixelRange, &outInfo, kvImage422YpCbYpCr8, kvImageARGB8888, flags);
 @/textblock </pre>
 
 If we want to define our own conversion coefficents, then we can do
 
 <pre> @textblock
 vImage_YpCbCrToARGBMatrix matrix;
 vImage_YpCbCrPixelRange pixelRange;
 
 matrix.Yp                  =  1.0f;
 matrix.Cb_G                = -0.3441f;
 matrix.Cb_B                =  1.772f;
 matrix.Cr_R                =  1.402f;
 matrix.Cr_G                = -0.7141f;
 
 pixelRange.Yp_bias         =   16;     // encoding for Y' = 0.0
 pixelRange.CbCr_bias       =  128;     // encoding for CbCr = 0.0
 pixelRange.YpRangeMax      =  235;     // encoding for Y'= 1.0
 pixelRange.CbCrRangeMax    =  240;     // encoding for CbCr = 0.5
 pixelRange.YpMax           =  255;     // a clamping limit above which the value is not allowed to go. 255 is fastest. Use pixelRange.YpRangeMax if you don't want Y' > 1.
 pixelRange.YpMin           =    0;     // a clamping limit below which the value is not allowed to go. 0 is fastest. Use pixelRange.Yp_bias if you don't want Y' < 0.
 pixelRange.CbCrMax         =  255;     // a clamping limit above which the value is not allowed to go. 255 is fastest.  Use pixelRange.CbCrRangeMax, if you don't want CbCr > 0.5
 pixelRange.CbCrMin         =    0;     // a clamping limit above which the value is not allowed to go. 0 is fastest.  Use (2*pixelRange.CbCr_bias - pixelRange.CbCrRangeMax), if you don't want CbCr < -0.5
 //                ( pixelRange.CbCr_bias - (pixelRange.CbCrRangeMax - pixelRange.CbCr_bias) = 2*pixelRange.CbCr_bias - pixelRange.CbCrRangeMax )
 
 err = vImageConvert_YpCbCrToARGB_GenerateConversion(&matrix, &pixelRange, &outInfo, kvImage422YpCbYpCr8, kvImageARGB8888, flags).
 @/textblock </pre>
 
 
 vImage_YpCbCrToARGB created may be reused multiple times from multiple threads concurrently.
 
 Here are the conversions available currently.
 
 <pre>
 @textblock
 RGB8   RGB16Q12    RGB16
 YUV8     Y        N          N
 YUV10    Y        Y          N
 YUV12    Y        Y          N
 YUV14    Y        N          Y
 YUV16    Y        N          Y
 @/textblock
 </pre>
 
 @return  The following return codes may occur:
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageUnsupportedConversion    Is returned when there is no conversion in vImage for inYpCbCrType & outARGBType.
 @/textblock  </pre>
 
 */

VIMAGE_PF vImage_Error vImageConvert_YpCbCrToARGB_GenerateConversion(const vImage_YpCbCrToARGBMatrix *matrix, const vImage_YpCbCrPixelRange *pixelRange, vImage_YpCbCrToARGB *outInfo, vImageYpCbCrType inYpCbCrType, vImageARGBType outARGBType, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGBToYpCbCr_GenerateConversion
 
 @abstract Generates the conversion from a ARGB to a YpCbCr pixel format.
 
 @param matrix
 A pointer to vImage_ARGBToYpCbCrMatrix that contains the matrix coefficients for the conversion
 from a ARGB to a YpCbCr pixel format.
 
 @param pixelRange
 A pointer to vImage_YpCbCrPixelRange that contains the pixel range information for the conversion
 from a ARGB to a YpCbCr pixel format.
 
 @param outInfo
 A pointer to vImage_ARGBToYpCbCr will be initialized with the information for the conversion function
 will use later.
 
 @param inARGBType
 A ARGBType to specify the output ARGB format.
 
 @param outYpCbCrType
 A YpCbCrType to specify the input YpCbCr format.
 
 @param flags
 kvImagePrintDiagnosticsToConsole   Directs the function to print diagnostic information to the console in the event of failure.
 
 @discussion This function is used to create the vImage_ARGBToYpCbCr conversion information necessary for all
 of RGB -> YUV conversion functions.
 
 For example, if we want to prepare for the conversion from ARGB8888 'yuvs' with ITU 601 video range, then we
 need to do the following:
 
 <pre> @textblock
 VIMAGE_PF vImage_Error err = kvImageNoError;
 vImage_Flags flags = kvImageNoFlags;
 vImage_YpCbCrPixelRange pixelRange;
 vImage_ARGBToYpCbCr outInfo;
 
 pixelRange.Yp_bias         =   16;     // encoding for Y' = 0.0
 pixelRange.CbCr_bias       =  128;     // encoding for CbCr = 0.0
 pixelRange.YpRangeMax      =  235;     // encoding for Y'= 1.0
 pixelRange.CbCrRangeMax    =  240;     // encoding for CbCr = 0.5
 pixelRange.YpMax           =  255;     // a clamping limit above which the value is not allowed to go. 255 is fastest. Use pixelRange.YpRangeMax if you don't want Y' > 1.
 pixelRange.YpMin           =    0;     // a clamping limit below which the value is not allowed to go. 0 is fastest. Use pixelRange.Yp_bias if you don't want Y' < 0.
 pixelRange.CbCrMax         =  255;     // a clamping limit above which the value is not allowed to go. 255 is fastest.  Use pixelRange.CbCrRangeMax, if you don't want CbCr > 0.5
 pixelRange.CbCrMin         =    0;     // a clamping limit above which the value is not allowed to go. 0 is fastest.  Use (2*pixelRange.CbCr_bias - pixelRange.CbCrRangeMax), if you don't want CbCr < -0.5
 
 err = vImageConvert_ARGBToYpCbCr_GenerateConversion(kvImage_ARGBToYpCbCrMatrix_ITU_R_601_4, &pixelRange, &outInfo, kvImageARGB8888, kvImage422YpCbYpCr8, flags);
 
 
 If we want to define our own conversion coefficents, then we can do
 
 vImage_ARGBToYpCbCrMatrix matrix;;
 vImage_YpCbCrPixelRange pixelRange;
 
 matrix.R_Yp          =  0.2989f;
 matrix.G_Yp          =  0.5866f;
 matrix.B_Yp          =  0.1144f;
 matrix.R_Cb          = -0.1688f;
 matrix.G_Cb          = -0.3312f;
 matrix.B_Cb_R_Cr     =  0.5f;
 matrix.G_Cr          = -0.4183f;
 matrix.B_Cr          = -0.0816f;
 pixelRange.Yp_bias         =   16;     // encoding for Y' = 0.0
 pixelRange.CbCr_bias       =  128;     // encoding for CbCr = 0.0
 pixelRange.YpRangeMax      =  235;     // encoding for Y'= 1.0
 pixelRange.CbCrRangeMax    =  240;     // encoding for CbCr = 0.5
 pixelRange.YpMax           =  255;     // a clamping limit above which the value is not allowed to go. 255 is fastest. Use pixelRange.YpRangeMax if you don't want Y' > 1.
 pixelRange.YpMin           =    0;     // a clamping limit below which the value is not allowed to go. 0 is fastest. Use pixelRange.Yp_bias if you don't want Y' < 0.
 pixelRange.CbCrMax         =  255;     // a clamping limit above which the value is not allowed to go. 255 is fastest.  Use pixelRange.CbCrRangeMax, if you don't want CbCr > 0.5
 pixelRange.CbCrMin         =    0;     // a clamping limit above which the value is not allowed to go. 0 is fastest.  Use (2*pixelRange.CbCr_bias - pixelRange.CbCrRangeMax), if you don't want CbCr < -0.5
 
 err = vImageConvert_ARGBToYpCbCr_GenerateConversion(&matrix, &pixelRange, &outInfo, kvImageARGB8888, kvImage422YpCbYpCr8, flags);
 
 
 vImage_ARGBToYpCbCr created may be reused multiple times from multiple threads concurrently.
 
 Here are the conversions available currently.
 
 RGB8   RGB16Q12    RGB16
 YUV8     Y        N          N
 YUV10    Y        Y          N
 YUV12    Y        Y          N
 YUV14    Y        N          Y
 YUV16    Y        N          Y
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageUnsupportedConversion    Is returned when there is no conversion in vImage for inARGBType & outYpCbCrType.
 @/textblock </pre>
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGBToYpCbCr_GenerateConversion(const vImage_ARGBToYpCbCrMatrix *matrix, const vImage_YpCbCrPixelRange *pixelRange, vImage_ARGBToYpCbCr *outInfo, vImageARGBType inARGBType, vImageYpCbCrType outYpCbCrType, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*! @functiongroup 422YpCbYpCr8 ('yuvs' and 'yuvf') */

/*!
 @function vImageConvert_422YpCbYpCr8ToARGB8888
 
 @abstract Convert YUV 422YpCbYpCr8 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 422YpCbYpCr8 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param alpha
 A value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 
 @discussion Convert YUV 422YpCbYpCr8 format to ARGB8888
 
 
 Yp0 Cb0 Yp1 Cr0  =>  A0 R0 G0 B0  A1 R1 G1 B1
 
 
 YUV 422YpCbYpCr8 can be used for 'yuvs' and 'yuvf' that are defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 'yuvs' with ITU 601 video range, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion().
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 
 <pre>
 @textblock
 uint8_t *srcPixel = src.data;
 Yp0 = srcPixel[0];
 Cb0 = srcPixel[1];
 Yp1 = srcPixel[2];
 Cr0 = srcPixel[3];
 srcPixel += 4;
 
 A0 = alpha
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                              ), 255 )
 A1 = alpha
 R1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                              ), 255 )
 
 uint8_t ARGB[8];
 ARGB[0] = A0;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 ARGB[4] = A1;
 ARGB[5] = R1;
 ARGB[6] = G1;
 ARGB[7] = B1;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel[4] = ARGB[permuteMap[0]+4];
 destPixel[5] = ARGB[permuteMap[1]+4];
 destPixel[6] = ARGB[permuteMap[2]+4];
 destPixel[7] = ARGB[permuteMap[3]+4];
 destPixel += 8;
 @/textblock
 </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_422YpCbYpCr8ToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], const uint8_t alpha, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888To422YpCbYpCr8
 
 @abstract Convert ARGB8888 to YUV 422YpCbYpCr8 format.
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 422YpCbYpCr8 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as each channel appears only once.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB8888 to YUV 422YpCbYpCr8 format
 
 A0 R0 G0 B0  A1 R1 G1 B1 => Yp0 Cb0 Yp1 Cr0
 
 
 YUV 422YpCbYpCr8 can be used for 'yuvs' and 'yuvf' that are defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 'yuvs' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 The per-pixel operation is:
 
 <pre>
 @textblock
 uint8_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A1 = srcPixel[permuteMap[0]];
 R1 = srcPixel[permuteMap[1]];
 G1 = srcPixel[permuteMap[2]];
 B1 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Yp1 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R1 * R_Yp      + G1 * G_Yp + B1 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr
 +   R1 * R_Cb      + G1 * G_Cb + B1 * B_Cb_R_Cr) / 2 )
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr
 +   R1 * B_Cb_R_Cr + G1 * G_Cr + B1 * B_Cr     ) / 2 )
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = Yp0;
 destPixel[1] = Cb0;
 destPixel[2] = Yp1;
 destPixel[3] = Cr0;
 destPixel += 4;
 @/textblock
 </pre>
 
 @return
 <pre>
 @textblock
 
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 </pre>
 
 Results are guaranteed to be faithfully rounded.
 Chroma is sampled at center by default.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888To422YpCbYpCr8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*! @functiongroup 422CbYpCrYp8 ('2vuy' and '2vuf') */

/*!
 @function vImageConvert_422CbYpCrYp8ToARGB8888
 
 @abstract Convert YUV 422CbYpCrYp8 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 422CbYpCrYp8 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param alpha
 A value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 422CbYpCrYp8 format to ARGB8888
 
 
 Cb0 Yp0 Cr0 Yp1  =>  A0 R0 G0 B0  A1 R1 G1 B1
 
 
 YUV 422CbYpCrYp8 can be used for '2vuy' and '2vuf' that are defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert '2vuy' with ITU 601 video range to ARGB8888, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 
 <pre>
 @textblock
 uint8_t *srcPixel = src.data;
 Cb0 = srcPixel[0];
 Yp0 = srcPixel[1];
 Cr0 = srcPixel[2];
 Yp1 = srcPixel[3];
 srcPixel += 4;
 
 A0 = alpha
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 A1 = alpha
 R1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                            ), 255 )
 
 uint8_t ARGB[8];
 ARGB[0] = A0;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 ARGB[4] = A1;
 ARGB[5] = R1;
 ARGB[6] = G1;
 ARGB[7] = B1;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel[4] = ARGB[permuteMap[0]+4];
 destPixel[5] = ARGB[permuteMap[1]+4];
 destPixel[6] = ARGB[permuteMap[2]+4];
 destPixel[7] = ARGB[permuteMap[3]+4];
 destPixel += 8;
 @/textblock
 </pre>
 
 @return
 <pre>
 @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 </pre>
 
 Note: Results are guaranteed to be faithfully rounded.
 
 
 */
VIMAGE_PF vImage_Error vImageConvert_422CbYpCrYp8ToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], const uint8_t alpha, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*!
 @function vImageConvert_ARGB8888To422CbYpCrYp8
 
 @abstract Convert ARGB8888 to YUV 422CbYpCrYp8 format
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 422CbYpCrYp8 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as each channel appears only once in the ordering.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB8888 to YUV 422CbYpCrYp8 format. Can be used for 2vuy.
 
 
 A0 R0 G0 B0  A1 R1 G1 B1 => Cb0 Yp0 Cr0 Yp1
 
 
 YUV 422CbYpCrYp8 can be used for '2vuy' and '2vuf' that are defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to '2vuy' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 
 The per-pixel operation is:
 
 <pre>
 @textblock
 uint8_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A1 = srcPixel[permuteMap[0]];
 R1 = srcPixel[permuteMap[1]];
 G1 = srcPixel[permuteMap[2]];
 B1 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Yp1 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R1 * R_Yp      + G1 * G_Yp + B1 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr
 +   R1 * R_Cb      + G1 * G_Cb + B1 * B_Cb_R_Cr) / 2 )
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr
 +   R1 * B_Cb_R_Cr + G1 * G_Cr + B1 * B_Cr     ) / 2 )
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = Cb0;
 destPixel[1] = Yp0;
 destPixel[2] = Cr0;
 destPixel[3] = Yp1;
 destPixel += 4;
 @/textblock
 </pre>
 
 @return
 <pre>
 @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 </pre>
 
 Results are guaranteed to be faithfully rounded.
 Chroma is sampled at center by default.
 
 
 */


VIMAGE_PF vImage_Error vImageConvert_ARGB8888To422CbYpCrYp8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*! @functiongroup 422CbYpCrYp8_AA8 ('a2vy') */

/*!
 @function vImageConvert_422CbYpCrYp8_AA8ToARGB8888
 
 @abstract Convert YUV 422CbYpCrYp8_AA8 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 422CbYpCrYp8_AA8 source pixels.
 
 @param srcA
 A pointer to vImage_Buffer that references 8-bit alpha source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param alpha
 A value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 422CbYpCrYp8_AA8 format to ARGB8888
 
 
 Cb0 Yp0 Cr0 Yp1  =>  A0 R0 G0 B0  A1 R1 G1 B1
 
 A0 A1
 
 
 YUV 422CbYpCrYp8_AA8 can be used for 'a2vy' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert 'a2vy' with ITU 601 video range to ARGB8888, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 
 <pre>
 @textblock
 uint8_t *srcPixel = src.data;
 Cb0 = srcPixel[0];
 Yp0 = srcPixel[1];
 Cr0 = srcPixel[2];
 Yp1 = srcPixel[3];
 srcPixel += 4;
 
 uint8_t *alpha = srcA.data;
 A0 = alpha[0];
 A1 = alpha[1];
 alpha += 2;
 
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 R1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 
 uint8_t ARGB[8];
 ARGB[0] = A0;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 ARGB[4] = A1;
 ARGB[5] = R1;
 ARGB[6] = G1;
 ARGB[7] = B1;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel[4] = ARGB[permuteMap[0]+4];
 destPixel[5] = ARGB[permuteMap[1]+4];
 destPixel[6] = ARGB[permuteMap[2]+4];
 destPixel[7] = ARGB[permuteMap[3]+4];
 destPixel += 8;
 @/textblock
 </pre>
 
 @return
 <pre>
 @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_422CbYpCrYp8_AA8ToARGB8888(const vImage_Buffer *src, const vImage_Buffer *srcA, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888To422CbYpCrYp8_AA8
 
 @abstract Convert ARGB8888 to YUV 422CbYpCrYp8_AA8 format
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 422CbYpCrYp8_AA8 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as each channel appears exactly once.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB8888 to YUV 422CbYpCrYp8_AA8 format
 
 
 A0 R0 G0 B0  A1 R1 G1 B1 => Cb0 Yp0 Cr0 Yp1
 
 A0 A1
 
 
 For example, if we want to use this function to convert ARGB8888 to 'a2vy' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 The per-pixel operation is:
 
 <pre>
 @textblock
 
 uint8_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A1 = srcPixel[permuteMap[0]];
 R1 = srcPixel[permuteMap[1]];
 G1 = srcPixel[permuteMap[2]];
 B1 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Yp1 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R1 * R_Yp      + G1 * G_Yp + B1 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr
 +   R1 * R_Cb      + G1 * G_Cb + B1 * B_Cb_R_Cr) / 2 )
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr
 +   R1 * B_Cb_R_Cr + G1 * G_Cr + B1 * B_Cr     ) / 2 )
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = Cb0;
 destPixel[1] = Yp0;
 destPixel[2] = Cr0;
 destPixel[3] = Yp1;
 destPixel += 4;
 
 uint8_t *alpha = destA.data;
 alpha[0] = A0;
 alpha[1] = A1;
 alpha += 2;
 
 @/textblock
 </pre>
 
 @return
 <pre>
 @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 <pre>
 
 Results are guaranteed to be faithfully rounded.
 Chroma is sampled at center by default.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888To422CbYpCrYp8_AA8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_Buffer *destA, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*! @functiongroup 444AYpCbCr8 ('r408' and 'y408') */

/*!
 @function vImageConvert_444AYpCbCr8ToARGB8888
 
 @abstract Convert YUV 444AYpCbCr8 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 444AYpCbCr8 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 444AYpCbCr8 format to ARGB8888
 
 
 A0 Yp0 Cb0 Cr0  =>  A0 R0 G0 B0
 
 
 YUV 444AYpCbCr8 can be used for 'r408' and 'y408' that are defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert 'y408' with ITU 601 video range to ARGB8888, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 
 <pre>
 @textblock
 
 uint8_t *srcPixel = src.data;
 A0  = srcPixel[0];
 Yp0 = srcPixel[1];
 Cb0 = srcPixel[2];
 Cr0 = srcPixel[3];
 srcPixel += 4;
 
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 
 uint8_t ARGB[4];
 ARGB[0] = A0;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 
 @/textblock
 <pre>
 
 @return
 <pre>
 @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 </pre>
 
 Results are guaranteed to be faithfully rounded.
 This function can work in place.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_444AYpCbCr8ToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888To444AYpCbCr8
 
 @abstract Convert ARGB8888 to YUV 444AYpCbCr8 format
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 444AYpCbCr8 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as each channel appears exactly once.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB8888 to YUV 444AYpCbCr8 format
 
 
 A0 R0 G0 B0  =>  A0 Yp0 Cb0 Cr0
 
 
 YUV 444AYpCbCr8 can be used for 'r408' and 'y408' that are defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 'y408' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 The per-pixel operation is:
 
 <pre>
 @textblock
 uint8_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   + R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr)
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr     )
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = A0;
 destPixel[1] = Yp0;
 destPixel[2] = Cb0;
 destPixel[3] = Cr0;
 destPixel += 4;
 @/textblock
 </pre>
 
 
 @return
 <pre>
 @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 <pre>
 
 Results are guaranteed to be faithfully rounded.
 This function can work in place.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888To444AYpCbCr8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*! @functiongroup 444CbYpCrA8 ('v408') */
/*!
 @function vImageConvert_444CbYpCrA8ToARGB8888
 
 @abstract Convert YUV 444CbYpCrA8 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 444CbYpCrA8 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 444CbYpCrA8 format to ARGB8888
 
 
 Cb0 Yp0 Cr0 A0  =>  A0 R0 G0 B0
 
 
 YUV 444CbYpCrA8 can be used for 'v408' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert 'v408' with ITU 601 video range to ARGB8888, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 
 <pre> @textblock
 uint8_t *srcPixel = src.data;
 Cb0 = srcPixel[0];
 Yp0 = srcPixel[1];
 Cr0 = srcPixel[2];
 A0  = srcPixel[3];
 srcPixel += 4;
 
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 
 uint8_t ARGB[4];
 ARGB[0] = A0;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @/textblock    </pre>
 
 
 @return
 <pre>
 @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 </pre>
 
 Results are guaranteed to be faithfully rounded.
 This function can work in place.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_444CbYpCrA8ToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888To444CbYpCrA8
 
 @abstract Convert ARGB8888 to YUV 444CbYpCrA8 format
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 444CbYpCrA8 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, provided that each channel appears only once.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB8888 to YUV 444CbYpCrA8 format
 
 
 A0 R0 G0 B0  =>  Cb0 Yp0 Cr0 A0
 
 
 YUV 444CbYpCrA8 can be used for 'v408' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 'v408' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 The per-pixel operation is:
 
 <pre> @textblock
 uint8_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   + R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr)
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr     )
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = Cb0;
 destPixel[1] = Yp0;
 destPixel[2] = Cr0;
 destPixel[3] = A0;
 destPixel += 4;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 This function can work in place.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888To444CbYpCrA8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*! @functiongroup 444CrYpCb8 ('v308')  */

/*!
 @function vImageConvert_444CrYpCb8ToARGB8888
 
 @abstract Convert YUV 444CrYpCb8 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 444CrYpCb8 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param alpha
 A value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 444CrYpCb8 format to ARGB8888
 
 
 Cr0 Yp0 Cb0  =>  A0 R0 G0 B0
 
 
 YUV 444CrYpCb8 can be used for 'v308' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert 'v308' with ITU 601 video range to ARGB8888, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 <pre>
 @textblock
 
 uint8_t *srcPixel = src.data;
 Cr0 = srcPixel[0];
 Yp0 = srcPixel[1];
 Cb0 = srcPixel[2];
 srcPixel += 3;
 
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 
 uint8_t ARGB[4];
 ARGB[0] = alpha;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @/textblock
 </pre>
 
 
 @return
 <pre>
 @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_444CrYpCb8ToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], const uint8_t alpha, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888To444CrYpCb8
 
 @abstract Convert ARGB8888 to YUV 444CrYpCb8 format
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 444CrYpCb8 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, provided that each channel appears only once.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB8888 to YUV 444CrYpCb8 format
 
 
 A0 R0 G0 B0  =>  Cr0 Yp0 Cb0
 
 
 YUV 444CrYpCb8 can be used for 'v308' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 'v308' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 
 The per-pixel operation is:
 
 <pre>
 @textblock
 uint8_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   + R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr)
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr     )
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = Cr0;
 destPixel[1] = Yp0;
 destPixel[2] = Cb0;
 destPixel += 3;
 @/textblock
 </pre>
 
 @return
 <pre>
 @textblock
 
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 </pre>
 
 Note: Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888To444CrYpCb8(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*! @functiongroup 420Yp8_Cb8_Cr8 ('y420' and 'f420') */

/*!
 @function vImageConvert_420Yp8_Cb8_Cr8ToARGB8888
 
 @abstract Convert YUV 420Yp8_Cb8_Cr8 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 420Yp8_Cb8_Cr8 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param alpha
 A value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 420Yp8_Cb8_Cr8 format to ARGB8888
 
 
 Ypt0 Ypt1  =>  At0 Rt0 Gt0 Bt0  At1 Rt1 Gt1 Bt1
 
 Ypb0 Ypb1      Ab0 Rb0 Gb0 Bb0  Ab1 Rb1 Gb1 Bb1
 
 Cb0
 
 Cr0
 
 
 YUV 420Yp8_Cb8_Cr8 can be used for 'y420' and 'f420' that are defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert 'y420' with ITU 601 video range to ARGB8888, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 <pre>
 @textblock
 
 uint8_t *srcYtPixel = srcY.data;
 uint8_t *srcYbPixel = srcY.data + srcY.rowBytes;
 Ypt0 = srcYtPixel[0];
 Ypt1 = srcYtPixel[1];
 srcYtPixel += 2;
 Ypb0 = srcYbPixel[0];
 Ypb1 = srcYbPixel[1];
 srcYbPixel += 2;
 
 uint8_t *srcCbPixel = srcCb.data;
 uint8_t *srcCrPixel = srcCr.data;
 Cb0 = srcCbPixel[0];
 srcCbPixel += 1;
 Cr0 = srcCrPixel[0];
 srcCrPixel += 1;
 
 At0 = alpha
 Rt0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt0 + Yp_bias) * Yp                               + (Cr0 + CbCr_bias) * Cr_R), 255 )
 Gt0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt0 + Yp_bias) * Yp + (Cb0 + CbCr_bias) * Cb_G + (Cr0 + CbCr_bias) * Cr_G), 255 )
 Bt0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt0 + Yp_bias) * Yp + (Cb0 + CbCr_bias) * Cb_B                              ), 255 )
 At1 = alpha
 Rt1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt1 + Yp_bias) * Yp                               + (Cr0 + CbCr_bias) * Cr_R), 255 )
 Gt1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt1 + Yp_bias) * Yp + (Cb0 + CbCr_bias) * Cb_G + (Cr0 + CbCr_bias) * Cr_G), 255 )
 Bt1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt1 + Yp_bias) * Yp + (Cb0 + CbCr_bias) * Cb_B                              ), 255 )
 Ab0 = alpha
 Rb0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb0 + Yp_bias) * Yp                               + (Cr0 + CbCr_bias) * Cr_R), 255 )
 Gb0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb0 + Yp_bias) * Yp + (Cb0 + CbCr_bias) * Cb_G + (Cr0 + CbCr_bias) * Cr_G), 255 )
 Bb0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb0 + Yp_bias) * Yp + (Cb0 + CbCr_bias) * Cb_B                              ), 255 )
 Ab1 = alpha
 Rb1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb1 + Yp_bias) * Yp                               + (Cr0 + CbCr_bias) * Cr_R), 255 )
 Gb1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb1 + Yp_bias) * Yp + (Cb0 + CbCr_bias) * Cb_G + (Cr0 + CbCr_bias) * Cr_G), 255 )
 Bb1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb1 + Yp_bias) * Yp + (Cb0 + CbCr_bias) * Cb_B                              ), 255 )
 
 uint8_t ARGB[16];
 ARGB[0]  = At0;
 ARGB[1]  = Rt0;
 ARGB[2]  = Gt0;
 ARGB[3]  = Bt0;
 ARGB[4]  = At1;
 ARGB[5]  = Rt1;
 ARGB[6]  = Gt1;
 ARGB[7]  = Bt1;
 ARGB[8]  = Ab0;
 ARGB[9]  = Rb0;
 ARGB[10] = Gb0;
 ARGB[11] = Bb0;
 ARGB[12] = Ab1;
 ARGB[13] = Rb1;
 ARGB[14] = Gb1;
 ARGB[15] = Bb1;
 
 uint8_t *destTPixel = dest.data;
 destTPixel[0]  = ARGB[permuteMap[0]];
 destTPixel[1]  = ARGB[permuteMap[1]];
 destTPixel[2]  = ARGB[permuteMap[2]];
 destTPixel[3]  = ARGB[permuteMap[3]];
 destTPixel[4]  = ARGB[permuteMap[0]+4];
 destTPixel[5]  = ARGB[permuteMap[1]+4];
 destTPixel[6]  = ARGB[permuteMap[2]+4];
 destTPixel[7]  = ARGB[permuteMap[3]+4];
 destTPixel += 8;
 uint8_t *destBPixel = dest.data + dest.rowBytes;
 destBPixel[0]  = ARGB[permuteMap[0]+8];
 destBPixel[1]  = ARGB[permuteMap[1]+8];
 destBPixel[2]  = ARGB[permuteMap[2]+8];
 destBPixel[3]  = ARGB[permuteMap[3]+8];
 destBPixel[4]  = ARGB[permuteMap[0]+12];
 destBPixel[5]  = ARGB[permuteMap[1]+12];
 destBPixel[6]  = ARGB[permuteMap[2]+12];
 destBPixel[7]  = ARGB[permuteMap[3]+12];
 destBPixel += 8;
 
 @/textblock
 </pre>
 
 @return
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 
 Note: Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_420Yp8_Cb8_Cr8ToARGB8888(const vImage_Buffer *srcYp, const vImage_Buffer *srcCb, const vImage_Buffer *srcCr, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], const uint8_t alpha, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888To420Yp8_Cb8_Cr8
 
 @abstract Convert ARGB8888 to YUV 420Yp8_Cb8_Cr8 format.
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 420Yp8_Cb8_Cr8 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, provided that each channel appears only once.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB8888 to YUV 420Yp8_Cb8_Cr8 format
 
 
 <pre> @textblock
 At0 Rt0 Gt0 Bt0  At1 Rt1 Gt1 Bt1  =>  Ypt0 Ypt1
 
 Ab0 Rb0 Gb0 Bb0  Ab1 Rb1 Gb1 Bb1      Ypb0 Ypb1
 
 Cb0
 
 Cr0
 
 @/textblock </pre>
 
 YUV 420Yp8_Cb8_Cr8 can be used for 'y420' and 'f420' that are defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 'y420' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 The per-pixel operation is:
 <pre>
 @textblock
 uint8_t *srcTPixel = src.data;
 At0 = srcTPixel[permuteMap[0]];
 Rt0 = srcTPixel[permuteMap[1]];
 Gt0 = srcTPixel[permuteMap[2]];
 Bt0 = srcTPixel[permuteMap[3]];
 srcTPixel += 4;
 At1 = srcTPixel[permuteMap[0]];
 Rt1 = srcTPixel[permuteMap[1]];
 Gt1 = srcTPixel[permuteMap[2]];
 Bt1 = srcTPixel[permuteMap[3]];
 srcTPixel += 4;
 uint8_t *srcBPixel = src.data + src.rowBytes;
 Ab0 = srcBPixel[permuteMap[0]];
 Rb0 = srcBPixel[permuteMap[1]];
 Gb0 = srcBPixel[permuteMap[2]];
 Bb0 = srcBPixel[permuteMap[3]];
 srcBPixel += 4;
 Ab1 = srcBPixel[permuteMap[0]];
 Rb1 = srcBPixel[permuteMap[1]];
 Gb1 = srcBPixel[permuteMap[2]];
 Bb1 = srcBPixel[permuteMap[3]];
 srcBPixel += 4;
 
 Ypt0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   Rt0 * R_Yp      + Gt0 * G_Yp + Bt0 * B_Yp     )
 Ypt1 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   Rt1 * R_Yp      + Gt1 * G_Yp + Bt1 * B_Yp     )
 Ypb0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   Rb0 * R_Yp      + Gb0 * G_Yp + Bb0 * B_Yp     )
 Ypb1 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   Rb1 * R_Yp      + Gb1 * G_Yp + Bb1 * B_Yp     )
 Cb0  = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( Rt0 * R_Cb      + Gt0 * G_Cb + Bt0 * B_Cb_R_Cr
 +   Rt1 * R_Cb      + Gt1 * G_Cb + Bt1 * B_Cb_R_Cr
 +   Rb0 * R_Cb      + Gb0 * G_Cb + Bb0 * B_Cb_R_Cr
 +   Rb1 * R_Cb      + Gb1 * G_Cb + Bb1 * B_Cb_R_Cr) / 4 )
 Cr0  = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( Rt0 * B_Cb_R_Cr + Gt0 * G_Cr + Bt0 * B_Cr
 +   Rt1 * B_Cb_R_Cr + Gt1 * G_Cr + Bt1 * B_Cr
 +   Rb0 * B_Cb_R_Cr + Gb0 * G_Cr + Bb0 * B_Cr
 +   Rb1 * B_Cb_R_Cr + Gb1 * G_Cr + Bb1 * B_Cr     ) / 4 )
 
 uint8_t *destYptPixel = destYp.data;
 uint8_t *destYpbPixel = destYp.data + destYp.rowBytes;
 destYptPixel[0] = Ypt0;
 destYptPixel[1] = Ypt1;
 destYpbPixel[0] = Ypb0;
 destYpbPixel[1] = Ypb1;
 destYptPixel += 2;
 destYpbPixel += 2;
 
 uint8_t *destCbPixel = destCb.data;
 uint8_t *destCrPixel = destCr.data;
 destCbPixel[0] = Cb0;
 destCrPixel[0] = Cr0;
 destCbPixel += 1;
 destCrPixel += 1;
 @/textblock
 </pre>
 
 @return
 <pre>
 @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 </pre>
 
 Results are guaranteed to be faithfully rounded.
 Chroma is sampled at center by default.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888To420Yp8_Cb8_Cr8(const vImage_Buffer *src, const vImage_Buffer *destYp, const vImage_Buffer *destCb, const vImage_Buffer *destCr, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4,5) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*! @functiongroup 420Yp8_CbCr8 ('420v' and '420f') */

/*!
 @function vImageConvert_420Yp8_CbCr8ToARGB8888
 
 @abstract Convert YUV 420Yp8_CbCr8 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 420Yp8_CbCr8 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param alpha
 A value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 420Yp8_CbCr8 format to ARGB8888
 
 
 Ypt0 Ypt1  =>  At0 Rt0 Gt0 Bt0  At1 Rt1 Gt1 Bt1
 
 Ypb0 Ypb1      Ab0 Rb0 Gb0 Bb0  Ab1 Rb1 Gb1 Bb1
 
 Cb0 Cr0
 
 
 YUV 420Yp8_CbCr8 can be used for '420v' and '420f' that are defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert '420v' with ITU 601 video range to ARGB8888, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 <pre>
 @textblock
 
 uint8_t *srcYtPixel = srcY.data;
 uint8_t *srcYbPixel = srcY.data + srcY.rowBytes;
 Ypt0 = srcYtPixel[0];
 Ypt1 = srcYtPixel[1];
 srcYtPixel += 2;
 Ypb0 = srcYbPixel[0];
 Ypb1 = srcYbPixel[1];
 srcYbPixel += 2;
 
 uint8_t *srcCbCrPixel = srcCbCr.data;
 Cb0 = srcCbCrPixel[0];
 Cr0 = srcCbCrPixel[1];
 srcCrPixel += 2;
 
 At0 = alpha
 Rt0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 Gt0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 Bt0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                              ), 255 )
 At1 = alpha
 Rt1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt1 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 Gt1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 Bt1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypt1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                              ), 255 )
 Ab0 = alpha
 Rb0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 Gb0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 Bb0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                              ), 255 )
 Ab1 = alpha
 Rb1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb1 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 Gb1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 Bb1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Ypb1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                              ), 255 )
 
 uint8_t ARGB[16];
 ARGB[0]  = At0;
 ARGB[1]  = Rt0;
 ARGB[2]  = Gt0;
 ARGB[3]  = Bt0;
 ARGB[4]  = At1;
 ARGB[5]  = Rt1;
 ARGB[6]  = Gt1;
 ARGB[7]  = Bt1;
 ARGB[8]  = Ab0;
 ARGB[9]  = Rb0;
 ARGB[10] = Gb0;
 ARGB[11] = Bb0;
 ARGB[12] = Ab1;
 ARGB[13] = Rb1;
 ARGB[14] = Gb1;
 ARGB[15] = Bb1;
 
 uint8_t *destTPixel = dest.data;
 destTPixel[0]  = ARGB[permuteMap[0]];
 destTPixel[1]  = ARGB[permuteMap[1]];
 destTPixel[2]  = ARGB[permuteMap[2]];
 destTPixel[3]  = ARGB[permuteMap[3]];
 destTPixel[4]  = ARGB[permuteMap[0]+4];
 destTPixel[5]  = ARGB[permuteMap[1]+4];
 destTPixel[6]  = ARGB[permuteMap[2]+4];
 destTPixel[7]  = ARGB[permuteMap[3]+4];
 destTPixel += 8;
 uint8_t *destBPixel = dest.data + dest.rowBytes;
 destBPixel[0]  = ARGB[permuteMap[0]+8];
 destBPixel[1]  = ARGB[permuteMap[1]+8];
 destBPixel[2]  = ARGB[permuteMap[2]+8];
 destBPixel[3]  = ARGB[permuteMap[3]+8];
 destBPixel[4]  = ARGB[permuteMap[0]+12];
 destBPixel[5]  = ARGB[permuteMap[1]+12];
 destBPixel[6]  = ARGB[permuteMap[2]+12];
 destBPixel[7]  = ARGB[permuteMap[3]+12];
 destBPixel += 8;
 
 @/textblock
 </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_420Yp8_CbCr8ToARGB8888(const vImage_Buffer *srcYp, const vImage_Buffer *srcCbCr, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], const uint8_t alpha, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888To420Yp8_CbCr8
 
 @abstract Convert ARGB8888 to YUV 420Yp8_CbCr8 format.
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 420Yp8_CbCr8 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as the channels don't repeat. For example, the pirate colorspace {0,1,1,1} (ARRR) is not supported, because the red channel appears more than once. (Pirates see red.)
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB8888 to YUV 420Yp8_CbCr8 format
 
 
 <pre> @textblock
 At0 Rt0 Gt0 Bt0  At1 Rt1 Gt1 Bt1  =>  Ypt0 Ypt1
 
 Ab0 Rb0 Gb0 Bb0  Ab1 Rb1 Gb1 Bb1      Ypb0 Ypb1
 
 Cb0 Cr0
 @/textblock </pre>
 
 
 YUV 420Yp8_CbCr8 can be used for '420v' and '420f' that are defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to '420v' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 The per-pixel operation is:
 <pre> @textblock
 uint8_t *srcTPixel = src.data;
 At0 = srcTPixel[permuteMap[0]];
 Rt0 = srcTPixel[permuteMap[1]];
 Gt0 = srcTPixel[permuteMap[2]];
 Bt0 = srcTPixel[permuteMap[3]];
 srcTPixel += 4;
 At1 = srcTPixel[permuteMap[0]];
 Rt1 = srcTPixel[permuteMap[1]];
 Gt1 = srcTPixel[permuteMap[2]];
 Bt1 = srcTPixel[permuteMap[3]];
 srcTPixel += 4;
 uint8_t *srcBPixel = src.data + src.rowBytes;
 Ab0 = srcBPixel[permuteMap[0]];
 Rb0 = srcBPixel[permuteMap[1]];
 Gb0 = srcBPixel[permuteMap[2]];
 Bb0 = srcBPixel[permuteMap[3]];
 srcBPixel += 4;
 Ab1 = srcBPixel[permuteMap[0]];
 Rb1 = srcBPixel[permuteMap[1]];
 Gb1 = srcBPixel[permuteMap[2]];
 Bb1 = srcBPixel[permuteMap[3]];
 srcBPixel += 4;
 
 Ypt0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   Rt0 * R_Yp      + Gt0 * G_Yp + Bt0 * B_Yp     )
 Ypt1 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   Rt1 * R_Yp      + Gt1 * G_Yp + Bt1 * B_Yp     )
 Ypb0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   Rb0 * R_Yp      + Gb0 * G_Yp + Bb0 * B_Yp     )
 Ypb1 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   Rb1 * R_Yp      + Gb1 * G_Yp + Bb1 * B_Yp     )
 Cb0  = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( Rt0 * R_Cb      + Gt0 * G_Cb + Bt0 * B_Cb_R_Cr
 +   Rt1 * R_Cb      + Gt1 * G_Cb + Bt1 * B_Cb_R_Cr
 +   Rb0 * R_Cb      + Gb0 * G_Cb + Bb0 * B_Cb_R_Cr
 +   Rb1 * R_Cb      + Gb1 * G_Cb + Bb1 * B_Cb_R_Cr) / 4 )
 Cr0  = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( Rt0 * B_Cb_R_Cr + Gt0 * G_Cr + Bt0 * B_Cr
 +   Rt1 * B_Cb_R_Cr + Gt1 * G_Cr + Bt1 * B_Cr
 +   Rb0 * B_Cb_R_Cr + Gb0 * G_Cr + Bb0 * B_Cr
 +   Rb1 * B_Cb_R_Cr + Gb1 * G_Cr + Bb1 * B_Cr     ) / 4 )
 
 uint8_t *destYptPixel = destYp.data;
 uint8_t *destYpbPixel = destYp.data + destYp.rowBytes;
 destYptPixel[0] = Ypt0;
 destYptPixel[1] = Ypt1;
 destYpbPixel[0] = Ypb0;
 destYpbPixel[1] = Ypb1;
 destYptPixel += 2;
 destYpbPixel += 2;
 
 uint8_t *destCbCrPixel = destCbCr.data;
 destCbCrPixel[0] = Cb0;
 destCbCrPixel[1] = Cr0;
 destCbCrPixel += 2;
 @/textblock </pre>
 
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock
 </pre>
 
 
 Results are guaranteed to be faithfully rounded.
 Chroma is sampled at center by default.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888To420Yp8_CbCr8(const vImage_Buffer *src, const vImage_Buffer *destYp, const vImage_Buffer *destCbCr, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3,4) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*! @functiongroup 444AYpCbCr16 ('y416') */

/*!
 @function vImageConvert_444AYpCbCr16ToARGB8888
 
 @abstract Convert YUV 444AYpCbCr16 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 444AYpCbCr16 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 444AYpCbCr16 format to ARGB8888
 
 
 A0 Yp0 Cb0 Cr0  =>  A0 R0 G0 B0
 
 
 YUV 444AYpCbCr8 can be used for 'y416' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert 'y416' with ITU 601 video range to ARGB8888, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 <pre> @textblock
 uint16_t *srcPixel = src.data;
 A0  = srcPixel[0];
 Yp0 = srcPixel[1];
 Cb0 = srcPixel[2];
 Cr0 = srcPixel[3];
 srcPixel += 4;
 
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 
 uint8_t ARGB[4];
 ARGB[0] = A0;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @/textblock </pre>
 
 @result
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_444AYpCbCr16ToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888To444AYpCbCr16
 
 @abstract Convert ARGB8888 to YUV 444AYpCbCr16 format
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 444AYpCbCr16 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as the values are unique.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB8888 to YUV 444AYpCbCr16 format
 
 
 A0 R0 G0 B0  =>  A0 Yp0 Cb0 Cr0
 
 
 YUV 444AYpCbCr8 can be used for 'y416' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 'y416' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 
 The per-pixel operation is:
 <pre> @textblock
 uint8_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   + R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr)
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr     )
 
 uint16_t *destPixel = dest.data;
 destPixel[0] = A0;
 destPixel[1] = Yp0;
 destPixel[2] = Cb0;
 destPixel[3] = Cr0;
 destPixel += 4;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888To444AYpCbCr16(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_444AYpCbCr16ToARGB16U
 
 @abstract Convert YUV 444AYpCbCr16 format to ARGB16U
 
 @param src
 A pointer to vImage_Buffer that references YUV 444AYpCbCr16 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 16-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16U.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16U.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 444AYpCbCr16 format to ARGB16U
 
 
 A0 Yp0 Cb0 Cr0  =>  A0 R0 G0 B0
 
 
 YUV 444AYpCbCr8 can be used for 'y416' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert 'y416' with ITU 601 video range to ARGB16U, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 <pre> @textblock
 uint16_t *srcPixel = src.data;
 A0  = srcPixel[0];
 Yp0 = srcPixel[1];
 Cb0 = srcPixel[2];
 Cr0 = srcPixel[3];
 srcPixel += 4;
 
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 65535 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 65535 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 65535 )
 
 uint16_t ARGB[4];
 ARGB[0] = A0;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 
 uint16_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 This function can work in place.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_444AYpCbCr16ToARGB16U(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB16UTo444AYpCbCr16
 
 @abstract Convert ARGB8888 to YUV 444AYpCbCr16 format
 
 @param src
 A pointer to vImage_Buffer that references 16-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 444AYpCbCr16 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16U.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16U.
 Any ordering of channels is supported as long as each channel appears only once.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB16U to YUV 444AYpCbCr16 format
 
 
 A0 R0 G0 B0  =>  A0 Yp0 Cb0 Cr0
 
 
 YUV 444AYpCbCr8 can be used for 'y416' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB16U to 'y416' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 
 The per-pixel operation is:
 <pre> @textblock
 uint16_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   + R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr)
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr     )
 
 uint16_t *destPixel = dest.data;
 destPixel[0] = A0;
 destPixel[1] = Yp0;
 destPixel[2] = Cb0;
 destPixel[3] = Cr0;
 destPixel += 4;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 This function can work in place.
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB16UTo444AYpCbCr16(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*! @functiongroup 444CrYpCb10 ('v410') */

/*!
 @function vImageConvert_444CrYpCb10ToARGB8888
 
 @abstract Convert YUV 444CrYpCb10 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 444CrYpCb10 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param alpha
 A value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 444CrYpCb10 format to ARGB8888
 
 
 3 10-bit unsigned components are packed into a 32-bit little-endian word.
 
 <pre> @textblock
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Cr            10-bit Yp            10-bit Cb                   =>  A0 R0 G0 B0
 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  X X
 @/textblock </pre>
 
 
 YUV 444CrYpCb10 can be used for 'v410' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert 'v410' with ITU 601 video range to ARGB8888, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 <pre> @textblock
 uint32_t *srcPixel = src.data;
 uint32_t pixel = *srcPixel;
 srcPixel += 1;
 
 Yp0 = getYpFromv410(pixel);
 Cb0 = getCbFromv410(pixel);
 Cr0 = getCrFromv410(pixel);
 
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 
 uint8_t ARGB[4];
 ARGB[0] = alpha;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 
 Results are guaranteed to be faithfully rounded.
 This function can work in place.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_444CrYpCb10ToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], const uint8_t alpha, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888To444CrYpCb10
 
 @abstract Convert ARGB8888 to YUV 444CrYpCb10 format
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 444CrYpCb10 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as each channel appears only once.
 
 @param flags
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 
 @discussion Convert ARGB8888 to YUV 444CrYpCb10 format
 
 
 3 10-bit unsigned components are packed into a 32-bit little-endian word.
 
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 A0 R0 G0 B0  =>  10-bit Cr            10-bit Yp            10-bit Cb
 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  X X
 
 
 YUV 444CrYpCb10 can be used for 'v410' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 'v410' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 
 The per-pixel operation is:
 <pre> @textblock
 uint8_t *srcPixel = src.data;
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   + R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr)
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr     )
 
 pixel = makev410(Yp0, Cb0, Cr0);
 
 uint32_t *destPixel = dest.data;
 *destPixel = pixel;
 destPixel += 1;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 
 Results are guaranteed to be faithfully rounded.
 This function can work in place.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888To444CrYpCb10(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_444CrYpCb10ToARGB16Q12
 
 @abstract Convert YUV 444CrYpCb10 format to ARGB16Q12
 
 @param src
 A pointer to vImage_Buffer that references YUV 444CrYpCb10 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 16Q12 ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16Q12.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16Q12.
 
 @param alpha
 A 16Q12 value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 444CrYpCb10 format to ARGB16Q12
 
 
 3 10-bit unsigned components are packed into a 32-bit little-endian word.
 
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Cr            10-bit Yp            10-bit Cb                   =>  A0 R0 G0 B0
 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  X X
 
 
 YUV 444CrYpCb10 can be used for 'v410' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert 'v410' with ITU 601 video range to ARGB16Q12, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 <pre> @textblock
 uint32_t *srcPixel = src.data;
 uint32_t pixel = *srcPixel;
 srcPixel += 1;
 
 Yp0 = getYpFromv410(pixel);
 Cb0 = getCbFromv410(pixel);
 Cr0 = getCrFromv410(pixel);
 
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 4096 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 4096 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                            ), 4096 )
 
 uint16_t ARGB[4];
 ARGB[0] = alpha;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 
 uint16_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_444CrYpCb10ToARGB16Q12(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], const Pixel_16Q12 alpha, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB16Q12To444CrYpCb10
 
 @abstract Convert ARGB16Q12 to YUV 444CrYpCb10 format
 
 @param src
 A pointer to vImage_Buffer that references 16Q12 ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 444CrYpCb10 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16Q12.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16Q12.
 Any ordering of channels is supported as long as each channel appears only once.
 
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB16Q12 to YUV 444CrYpCb10 format
 
 
 3 10-bit unsigned components are packed into a 32-bit little-endian word.
 <pre> @textblock
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 A0 R0 G0 B0  =>  10-bit Cr            10-bit Yp            10-bit Cb
 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  X X
 @/textblock </pre>
 
 
 YUV 444CrYpCb10 can be used for 'v410' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB16Q12 to 'v410' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 
 The per-pixel operation is:
 <pre> @textblock
 uint16_t *srcPixel = src.data;
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   + R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr)
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr     )
 
 pixel = makev410(Yp0, Cb0, Cr0);
 
 uint32_t *destPixel = dest.data;
 destPixel[0] = pixel;
 destPixel += 1;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB16Q12To444CrYpCb10(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*! @functiongroup 422CrYpCbYpCbYpCbYpCrYpCrYp10 ('v210')   */

/*!
 @function vImageConvert_422CrYpCbYpCbYpCbYpCrYpCrYp10ToARGB8888
 
 @abstract Convert YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param alpha
 A value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 format to ARGB8888
 
 
 6 packed YUV pixels are getting mapped into 6 ARGB8888 pixels.
 
 12 10-bit unsigned components are packed into 4 32-bit little-endian words.
 <pre> @textblock
 
 Word0
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Cr0           10-bit Y0            10-bit Cb0
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word1
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Y2            10-bit Cb1           10-bit Y1
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word2
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Cb2           10-bit Y3            10-bit Cr1
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word3
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Y5            10-bit Cr2           10-bit Y4
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 
 =>  A0 R0 G0 B0  A1 R1 G1 B1  A2 R2 G2 B2  A3 R3 G3 B3  A4 R4 G4 B4  A5 R5 G5 B5
 @/textblock </pre>
 
 YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 can be used for 'v210' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 'v210' with ITU 601 video range, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 <pre> @textblock
 uint32_t *srcPixel = src.data;
 pixel0 = srcPixel[0];
 pixel1 = srcPixel[1];
 pixel2 = srcPixel[2];
 pixel3 = srcPixel[3];
 srcPixel += 4;
 
 Yp0 = getYp0Fromv210(pixel0, pixel1, pixel2, pixel3);
 Yp1 = getYp1Fromv210(pixel0, pixel1, pixel2, pixel3);
 Yp2 = getYp2Fromv210(pixel0, pixel1, pixel2, pixel3);
 Yp3 = getYp3Fromv210(pixel0, pixel1, pixel2, pixel3);
 Yp4 = getYp4Fromv210(pixel0, pixel1, pixel2, pixel3);
 Yp5 = getYp5Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cb0 = getCb0Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cb1 = getCb1Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cb2 = getCb2Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cr0 = getCr0Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cr1 = getCr1Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cr2 = getCr2Fromv210(pixel0, pixel1, pixel2, pixel3);
 
 A0 = alpha
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 A1 = alpha
 R1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 A2 = alpha
 R2 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp2 - Yp_bias) * Yp                            + (Cr1 - CbCr_bias) * Cr_R), 255 )
 G2 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp2 - Yp_bias) * Yp + (Cb1 - CbCr_bias) * Cb_G + (Cr1 - CbCr_bias) * Cr_G), 255 )
 B2 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp2 - Yp_bias) * Yp + (Cb1 - CbCr_bias) * Cb_B                           ), 255 )
 A3 = alpha
 R3 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp3 - Yp_bias) * Yp                            + (Cr1 - CbCr_bias) * Cr_R), 255 )
 G3 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp3 - Yp_bias) * Yp + (Cb1 - CbCr_bias) * Cb_G + (Cr1 - CbCr_bias) * Cr_G), 255 )
 B3 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp3 - Yp_bias) * Yp + (Cb1 - CbCr_bias) * Cb_B                           ), 255 )
 A4 = alpha
 R4 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp4 - Yp_bias) * Yp                            + (Cr2 - CbCr_bias) * Cr_R), 255 )
 G4 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp4 - Yp_bias) * Yp + (Cb2 - CbCr_bias) * Cb_G + (Cr2 - CbCr_bias) * Cr_G), 255 )
 B4 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp4 - Yp_bias) * Yp + (Cb2 - CbCr_bias) * Cb_B                           ), 255 )
 A5 = alpha
 R5 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp5 - Yp_bias) * Yp                            + (Cr2 - CbCr_bias) * Cr_R), 255 )
 G5 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp5 - Yp_bias) * Yp + (Cb2 - CbCr_bias) * Cb_G + (Cr2 - CbCr_bias) * Cr_G), 255 )
 B5 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp5 - Yp_bias) * Yp + (Cb2 - CbCr_bias) * Cb_B                           ), 255 )
 
 uint8_t ARGB[24];
 ARGB[0] = A0;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 ARGB[4] = A1;
 ARGB[5] = R1;
 ARGB[6] = G1;
 ARGB[7] = B1;
 ARGB[8] = A2;
 ARGB[9] = R2;
 ARGB[10] = G2;
 ARGB[11] = B2;
 ARGB[12] = A3;
 ARGB[13] = R3;
 ARGB[14] = G3;
 ARGB[15] = B3;
 ARGB[16] = A4;
 ARGB[17] = R4;
 ARGB[18] = G4;
 ARGB[19] = B4;
 ARGB[20] = A5;
 ARGB[21] = R5;
 ARGB[22] = G5;
 ARGB[23] = B5;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel[4] = ARGB[permuteMap[0]+4];
 destPixel[5] = ARGB[permuteMap[1]+4];
 destPixel[6] = ARGB[permuteMap[2]+4];
 destPixel[7] = ARGB[permuteMap[3]+4];
 destPixel[8] = ARGB[permuteMap[0]+8];
 destPixel[9] = ARGB[permuteMap[1]+8];
 destPixel[10] = ARGB[permuteMap[2]+8];
 destPixel[11] = ARGB[permuteMap[3]+8];
 destPixel[12] = ARGB[permuteMap[0]+12];
 destPixel[13] = ARGB[permuteMap[1]+12];
 destPixel[14] = ARGB[permuteMap[2]+12];
 destPixel[15] = ARGB[permuteMap[3]+12];
 destPixel[16] = ARGB[permuteMap[0]+16];
 destPixel[17] = ARGB[permuteMap[1]+16];
 destPixel[18] = ARGB[permuteMap[2]+16];
 destPixel[19] = ARGB[permuteMap[3]+16];
 destPixel[20] = ARGB[permuteMap[0]+20];
 destPixel[21] = ARGB[permuteMap[1]+20];
 destPixel[22] = ARGB[permuteMap[2]+20];
 destPixel[23] = ARGB[permuteMap[3]+20];
 destPixel += 24;
 @/textblock </pre>
 
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_422CrYpCbYpCbYpCbYpCrYpCrYp10ToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], const uint8_t alpha, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888To422CrYpCbYpCbYpCbYpCrYpCrYp10
 
 @abstract Convert ARGB8888 to YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 format.
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as each channel appears only once.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB8888 to YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 format
 
 
 6 ARGB8888 pixels are getting mapped into 6 packed YUV pixels.
 
 A0 R0 G0 B0  A1 R1 G1 B1  A2 R2 G2 B2  A3 R3 G3 B3  A4 R4 G4 B4  A5 R5 G5 B5  =>
 
 12 10-bit unsigned components are packed into 4 32-bit little-endian words.
 
 <pre> @textblock
 Word0
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Cr0           10-bit Y0            10-bit Cb0
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word1
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Y2            10-bit Cb1           10-bit Y1
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word2
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Cb2           10-bit Y3            10-bit Cr1
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word3
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Y5            10-bit Cr2           10-bit Y4
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 @/textblock </pre>
 
 YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 can be used for 'v210' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 'v210' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 The per-pixel operation is:
 <pre> @textblock
 uint8_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A1 = srcPixel[permuteMap[0]];
 R1 = srcPixel[permuteMap[1]];
 G1 = srcPixel[permuteMap[2]];
 B1 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A2 = srcPixel[permuteMap[0]];
 R2 = srcPixel[permuteMap[1]];
 G2 = srcPixel[permuteMap[2]];
 B2 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A3 = srcPixel[permuteMap[0]];
 R3 = srcPixel[permuteMap[1]];
 G3 = srcPixel[permuteMap[2]];
 B3 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A4 = srcPixel[permuteMap[0]];
 R4 = srcPixel[permuteMap[1]];
 G4 = srcPixel[permuteMap[2]];
 B4 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A5 = srcPixel[permuteMap[0]];
 R5 = srcPixel[permuteMap[1]];
 G5 = srcPixel[permuteMap[2]];
 B5 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Yp1 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R1 * R_Yp      + G1 * G_Yp + B1 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr
 +   R1 * R_Cb      + G1 * G_Cb + B1 * B_Cb_R_Cr) / 2 )
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr
 +   R1 * B_Cb_R_Cr + G1 * G_Cr + B1 * B_Cr     ) / 2 )
 Yp2 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R2 * R_Yp      + G2 * G_Yp + B2 * B_Yp     )
 Yp3 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R3 * R_Yp      + G3 * G_Yp + B3 * B_Yp     )
 Cb1 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R2 * R_Cb      + G2 * G_Cb + B2 * B_Cb_R_Cr
 +   R3 * R_Cb      + G3 * G_Cb + B3 * B_Cb_R_Cr) / 2 )
 Cr1 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R2 * B_Cb_R_Cr + G2 * G_Cr + B2 * B_Cr
 +   R3 * B_Cb_R_Cr + G3 * G_Cr + B3 * B_Cr     ) / 2 )
 Yp4 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R4 * R_Yp      + G4 * G_Yp + B4 * B_Yp     )
 Yp5 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R5 * R_Yp      + G5 * G_Yp + B5 * B_Yp     )
 Cb2 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R4 * R_Cb      + G4 * G_Cb + B4 * B_Cb_R_Cr
 +   R5 * R_Cb      + G5 * G_Cb + B5 * B_Cb_R_Cr) / 2 )
 Cr2 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R4 * B_Cb_R_Cr + G4 * G_Cr + B4 * B_Cr
 +   R5 * B_Cb_R_Cr + G5 * G_Cr + B5 * B_Cr     ) / 2 )
 
 uint32_t *destPixel = dest.data;
 packv210AndStore(destPixel, Yp0, Yp1, Yp2, Yp3, Yp4, Yp5, Cb0, Cb1, Cb2, Cr0, Cr1, Cr2);
 destPixel += 4;
 @/textblock </pre>
 
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 Chroma is sampled at center by default.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888To422CrYpCbYpCbYpCbYpCrYpCrYp10(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_422CrYpCbYpCbYpCbYpCrYpCrYp10ToARGB16Q12
 
 @abstract Convert YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 format to ARGB16Q12
 
 @param src
 A pointer to vImage_Buffer that references YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 16Q12 ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16Q12.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16Q12.
 
 @param alpha
 A value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 format to ARGB16Q12
 
 
 6 packed YUV pixels are getting mapped into 6 ARGB16Q12 pixels.
 
 12 10-bit unsigned components are packed into 4 32-bit little-endian words.
 <pre> @textblock
 Word0
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Cr0           10-bit Y0            10-bit Cb0
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word1
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Y2            10-bit Cb1           10-bit Y1
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word2
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Cb2           10-bit Y3            10-bit Cr1
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word3
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Y5            10-bit Cr2           10-bit Y4
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 
 =>  A0 R0 G0 B0  A1 R1 G1 B1  A2 R2 G2 B2  A3 R3 G3 B3  A4 R4 G4 B4  A5 R5 G5 B5
 @/textblock </pre>
 
 YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 can be used for 'v210' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB16Q12 to 'v210' with ITU 601 video range, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 <pre> @textblock
 
 uint32_t *srcPixel = src.data;
 pixel0 = srcPixel[0];
 pixel1 = srcPixel[1];
 pixel2 = srcPixel[2];
 pixel3 = srcPixel[3];
 srcPixel += 4;
 
 Yp0 = getYp0Fromv210(pixel0, pixel1, pixel2, pixel3);
 Yp1 = getYp1Fromv210(pixel0, pixel1, pixel2, pixel3);
 Yp2 = getYp2Fromv210(pixel0, pixel1, pixel2, pixel3);
 Yp3 = getYp3Fromv210(pixel0, pixel1, pixel2, pixel3);
 Yp4 = getYp4Fromv210(pixel0, pixel1, pixel2, pixel3);
 Yp5 = getYp5Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cb0 = getCb0Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cb1 = getCb1Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cb2 = getCb2Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cr0 = getCr0Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cr1 = getCr1Fromv210(pixel0, pixel1, pixel2, pixel3);
 Cr2 = getCr2Fromv210(pixel0, pixel1, pixel2, pixel3);
 
 A0 = alpha
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 4096 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 4096 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 4096 )
 A1 = alpha
 R1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 4096 )
 G1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 4096 )
 B1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 4096 )
 A2 = alpha
 R2 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp2 - Yp_bias) * Yp                            + (Cr1 - CbCr_bias) * Cr_R), 4096 )
 G2 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp2 - Yp_bias) * Yp + (Cb1 - CbCr_bias) * Cb_G + (Cr1 - CbCr_bias) * Cr_G), 4096 )
 B2 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp2 - Yp_bias) * Yp + (Cb1 - CbCr_bias) * Cb_B                           ), 4096 )
 A3 = alpha
 R3 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp3 - Yp_bias) * Yp                            + (Cr1 - CbCr_bias) * Cr_R), 4096 )
 G3 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp3 - Yp_bias) * Yp + (Cb1 - CbCr_bias) * Cb_G + (Cr1 - CbCr_bias) * Cr_G), 4096 )
 B3 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp3 - Yp_bias) * Yp + (Cb1 - CbCr_bias) * Cb_B                           ), 4096 )
 A4 = alpha
 R4 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp4 - Yp_bias) * Yp                            + (Cr2 - CbCr_bias) * Cr_R), 4096 )
 G4 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp4 - Yp_bias) * Yp + (Cb2 - CbCr_bias) * Cb_G + (Cr2 - CbCr_bias) * Cr_G), 4096 )
 B4 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp4 - Yp_bias) * Yp + (Cb2 - CbCr_bias) * Cb_B                           ), 4096 )
 A5 = alpha
 R5 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp5 - Yp_bias) * Yp                            + (Cr2 - CbCr_bias) * Cr_R), 4096 )
 G5 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp5 - Yp_bias) * Yp + (Cb2 - CbCr_bias) * Cb_G + (Cr2 - CbCr_bias) * Cr_G), 4096 )
 B5 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp5 - Yp_bias) * Yp + (Cb2 - CbCr_bias) * Cb_B                           ), 4096 )
 
 uint16_t ARGB[24];
 ARGB[0] = A0;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 ARGB[4] = A1;
 ARGB[5] = R1;
 ARGB[6] = G1;
 ARGB[7] = B1;
 ARGB[8] = A2;
 ARGB[9] = R2;
 ARGB[10] = G2;
 ARGB[11] = B2;
 ARGB[12] = A3;
 ARGB[13] = R3;
 ARGB[14] = G3;
 ARGB[15] = B3;
 ARGB[16] = A4;
 ARGB[17] = R4;
 ARGB[18] = G4;
 ARGB[19] = B4;
 ARGB[20] = A5;
 ARGB[21] = R5;
 ARGB[22] = G5;
 ARGB[23] = B5;
 
 uint16_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel[4] = ARGB[permuteMap[0]+4];
 destPixel[5] = ARGB[permuteMap[1]+4];
 destPixel[6] = ARGB[permuteMap[2]+4];
 destPixel[7] = ARGB[permuteMap[3]+4];
 destPixel[8] = ARGB[permuteMap[0]+8];
 destPixel[9] = ARGB[permuteMap[1]+8];
 destPixel[10] = ARGB[permuteMap[2]+8];
 destPixel[11] = ARGB[permuteMap[3]+8];
 destPixel[12] = ARGB[permuteMap[0]+12];
 destPixel[13] = ARGB[permuteMap[1]+12];
 destPixel[14] = ARGB[permuteMap[2]+12];
 destPixel[15] = ARGB[permuteMap[3]+12];
 destPixel[16] = ARGB[permuteMap[0]+16];
 destPixel[17] = ARGB[permuteMap[1]+16];
 destPixel[18] = ARGB[permuteMap[2]+16];
 destPixel[19] = ARGB[permuteMap[3]+16];
 destPixel[20] = ARGB[permuteMap[0]+20];
 destPixel[21] = ARGB[permuteMap[1]+20];
 destPixel[22] = ARGB[permuteMap[2]+20];
 destPixel[23] = ARGB[permuteMap[3]+20];
 destPixel += 24;
 @/textblock </pre>
 
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Note: Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_422CrYpCbYpCbYpCbYpCrYpCrYp10ToARGB16Q12(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], const Pixel_16Q12 alpha, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB16Q12To422CrYpCbYpCbYpCbYpCrYpCrYp10
 
 @abstract Convert ARGB16Q12 to YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 format.
 
 @param src
 A pointer to vImage_Buffer that references 16Q12 ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16Q12.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16Q12.
 Any ordering of channels is supported as long as each channel appears only once.
 
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB16Q12 to YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 format
 
 
 6 ARGB16Q12 pixels are getting mapped into 6 packed YUV pixels.
 <pre> @textblock
 
 A0 R0 G0 B0  A1 R1 G1 B1  A2 R2 G2 B2  A3 R3 G3 B3  A4 R4 G4 B4  A5 R5 G5 B5  =>
 
 12 10-bit unsigned components are packed into 4 32-bit little-endian words.
 
 Word0
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Cr0           10-bit Y0            10-bit Cb0
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word1
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Y2            10-bit Cb1           10-bit Y1
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word2
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Cb2           10-bit Y3            10-bit Cr1
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 
 Word3
 Decreasing Address order (32-bit little-endian)
 byte3           byte2            byte1            byte0
 10-bit Y5            10-bit Cr2           10-bit Y4
 X X 9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1 0
 @/textblock </pre>
 
 YUV 422CrYpCbYpCbYpCbYpCrYpCrYp10 can be used for 'v210' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB16Q12 to 'v210' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 The per-pixel operation is:
 
 <pre> @textblock
 
 uint16_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A1 = srcPixel[permuteMap[0]];
 R1 = srcPixel[permuteMap[1]];
 G1 = srcPixel[permuteMap[2]];
 B1 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A2 = srcPixel[permuteMap[0]];
 R2 = srcPixel[permuteMap[1]];
 G2 = srcPixel[permuteMap[2]];
 B2 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A3 = srcPixel[permuteMap[0]];
 R3 = srcPixel[permuteMap[1]];
 G3 = srcPixel[permuteMap[2]];
 B3 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A4 = srcPixel[permuteMap[0]];
 R4 = srcPixel[permuteMap[1]];
 G4 = srcPixel[permuteMap[2]];
 B4 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A5 = srcPixel[permuteMap[0]];
 R5 = srcPixel[permuteMap[1]];
 G5 = srcPixel[permuteMap[2]];
 B5 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Yp1 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R1 * R_Yp      + G1 * G_Yp + B1 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr
 +   R1 * R_Cb      + G1 * G_Cb + B1 * B_Cb_R_Cr) / 2 )
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr
 +   R1 * B_Cb_R_Cr + G1 * G_Cr + B1 * B_Cr     ) / 2 )
 Yp2 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R2 * R_Yp      + G2 * G_Yp + B2 * B_Yp     )
 Yp3 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R3 * R_Yp      + G3 * G_Yp + B3 * B_Yp     )
 Cb1 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R2 * R_Cb      + G2 * G_Cb + B2 * B_Cb_R_Cr
 +   R3 * R_Cb      + G3 * G_Cb + B3 * B_Cb_R_Cr) / 2 )
 Cr1 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R2 * B_Cb_R_Cr + G2 * G_Cr + B2 * B_Cr
 +   R3 * B_Cb_R_Cr + G3 * G_Cr + B3 * B_Cr     ) / 2 )
 Yp4 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R4 * R_Yp      + G4 * G_Yp + B4 * B_Yp     )
 Yp5 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R5 * R_Yp      + G5 * G_Yp + B5 * B_Yp     )
 Cb2 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R4 * R_Cb      + G4 * G_Cb + B4 * B_Cb_R_Cr
 +   R5 * R_Cb      + G5 * G_Cb + B5 * B_Cb_R_Cr) / 2 )
 Cr2 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R4 * B_Cb_R_Cr + G4 * G_Cr + B4 * B_Cr
 +   R5 * B_Cb_R_Cr + G5 * G_Cr + B5 * B_Cr     ) / 2 )
 
 uint32_t *destPixel = dest.data;
 packv210AndStore(destPixel, Yp0, Yp1, Yp2, Yp3, Yp4, Yp5, Cb0, Cb1, Cb2, Cr0, Cr1, Cr2);
 destPixel += 4;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 Chroma is sampled at center by default.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB16Q12To422CrYpCbYpCbYpCbYpCrYpCrYp10(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*! @functiongroup 422CbYpCrYp16(bitdepth) ('v216')    */

/*!
 @function vImageConvert_422CbYpCrYp16ToARGB8888
 
 @abstract Convert YUV 422CbYpCrYp16 format to ARGB8888
 
 @param src
 A pointer to vImage_Buffer that references YUV 422CbYpCrYp16 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param alpha
 A value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 
 @discussion Convert YUV 422CbYpCrYp16 format to ARGB8888
 <pre> @textblock
 
 pixel0-1
 byte0 byte1   byte2 byte3   byte4 byte5   byte6 byte7
 LE-16-bit-Cb  LE-16-bit-Y0  LE-16-bit-Cr  LE-16-bit-Y1  =>  A0 R0 G0 B0  A1 R1 G1 B1
 
 (LE and left-justified 16-bit-per-component)
 @/textblock </pre>
 
 YUV 422CbYpCrYp16 can be used for 16-bit 'v216' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 16-bit 'v216' with ITU 601 video range, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 <pre> @textblock
 
 uint64_t *srcPixel = src.data;
 uint64_t pixel = *srcPixel;
 Yp0 = getYp0From16bitv216(pixel);
 Cb0 = getCb0From16bitv216(pixel);
 Yp1 = getYp1From16bitv216(pixel);
 Cr0 = getCr0From16bitv216(pixel);
 srcPixel += 1;
 
 A0 = alpha
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 A1 = alpha
 R1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 255 )
 G1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 255 )
 B1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 255 )
 
 uint8_t ARGB[8];
 ARGB[0] = A0;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 ARGB[4] = A1;
 ARGB[5] = R1;
 ARGB[6] = G1;
 ARGB[7] = B1;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel[4] = ARGB[permuteMap[0]+4];
 destPixel[5] = ARGB[permuteMap[1]+4];
 destPixel[6] = ARGB[permuteMap[2]+4];
 destPixel[7] = ARGB[permuteMap[3]+4];
 destPixel += 8;
 @/textblock </pre>
 
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock <pre>
 
 Results are guaranteed to be faithfully rounded.
 This function can work in place.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_422CbYpCrYp16ToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], const uint8_t alpha, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888To422CbYpCrYp16
 
 @abstract Convert ARGB8888 to YUV 422CbYpCrYp16 format.
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 422CbYpCrYp16 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as each channel appears only once.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB8888 to YUV 422CbYpCrYp16 format
 <pre> @textblock
 
 pixel0-1
 byte0 byte1   byte2 byte3   byte4 byte5   byte6 byte7
 A0 R0 G0 B0  A1 R1 G1 B1  =>  LE-16-bit-Cb  LE-16-bit-Y0  LE-16-bit-Cr  LE-16-bit-Y1
 
 (LE and left-justified 16-bit-per-component)
 @/textblock </pre>
 
 YUV 422CbYpCrYp16 can be used for 16-bit 'v216' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB8888 to 16-bit 'v216' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 The per-pixel operation is:
 <pre> @textblock
 
 uint8_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A1 = srcPixel[permuteMap[0]];
 R1 = srcPixel[permuteMap[1]];
 G1 = srcPixel[permuteMap[2]];
 B1 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R0 * R_Yp      + G0 * G_Yp + B0 * B_Yp     )
 Yp1 = ROUND_TO_NEAREST_INTEGER( Yp_bias   +   R1 * R_Yp      + G1 * G_Yp + B1 * B_Yp     )
 Cb0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * R_Cb      + G0 * G_Cb + B0 * B_Cb_R_Cr
 +   R1 * R_Cb      + G1 * G_Cb + B1 * B_Cb_R_Cr) / 2 )
 Cr0 = ROUND_TO_NEAREST_INTEGER( CbCr_bias + ( R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr
 +   R1 * B_Cb_R_Cr + G1 * G_Cr + B1 * B_Cr     ) / 2 )
 
 uint64_t *destPixel = dest.data;
 pack16bitv216AndStore(destPixel, Yp0, Yp1, Cb0, Cr0);
 destPixel += 1;
 
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 Chroma is sampled at center by default.
 This function can work in place.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB8888To422CbYpCrYp16(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_422CbYpCrYp16ToARGB16U
 
 @abstract Convert YUV 422CbYpCrYp16 format to ARGB16U
 
 @param src
 A pointer to vImage_Buffer that references YUV 422CbYpCrYp16 source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 16-bit ARGB interleaved destination pixels.
 
 @param info
 A pointer to vImage_YpCbCrToARGB which contains info coeffcient and preBias values.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16U.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16U.
 
 @param alpha
 A 16-bit value for alpha channel in dest.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 
 @discussion Convert YUV 422CbYpCrYp16 format to ARGB16U
 <pre> @textblock
 
 pixel0-1
 byte0 byte1   byte2 byte3   byte4 byte5   byte6 byte7
 LE-16-bit-Cb  LE-16-bit-Y0  LE-16-bit-Cr  LE-16-bit-Y1  =>  A0 R0 G0 B0  A1 R1 G1 B1
 
 (LE and left-justified 16-bit-per-component)
 @/textblock </pre>
 
 YUV 422CbYpCrYp16 can be used for 16-bit 'v216' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB16U to 16-bit 'v216' with ITU 601 video range, then we need
 generate vImage_YpCbCrToARGB by vImageConvert_YpCbCrToARGB_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, Yp, Cr_R, Cb_G, Cr_G, and Cb_B are calculated and converted into the right
 format by vImageConvert_YpCbCrToARGB_GenerateConversion() inside of vImage_YpCbCrToARGB.
 
 
 The per-pixel operation is:
 <pre> @textblock
 
 uint64_t *srcPixel = src.data;
 uint64_t pixel = *srcPixel;
 Yp0 = getYp0From16bitv216(pixel);
 Cb0 = getCb0From16bitv216(pixel);
 Yp1 = getYp1From16bitv216(pixel);
 Cr0 = getCr0From16bitv216(pixel);
 srcPixel += 1;
 
 A0 = alpha
 R0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 65535 )
 G0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 65535 )
 B0 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp0 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 65535 )
 A1 = alpha
 R1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp                            + (Cr0 - CbCr_bias) * Cr_R), 65535 )
 G1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_G + (Cr0 - CbCr_bias) * Cr_G), 65535 )
 B1 = CLAMP(0, ROUND_TO_NEAREST_INTEGER((Yp1 - Yp_bias) * Yp + (Cb0 - CbCr_bias) * Cb_B                           ), 65535 )
 
 uint16_t ARGB[8];
 ARGB[0] = A0;
 ARGB[1] = R0;
 ARGB[2] = G0;
 ARGB[3] = B0;
 ARGB[4] = A1;
 ARGB[5] = R1;
 ARGB[6] = G1;
 ARGB[7] = B1;
 
 uint16_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel[4] = ARGB[permuteMap[0]+4];
 destPixel[5] = ARGB[permuteMap[1]+4];
 destPixel[6] = ARGB[permuteMap[2]+4];
 destPixel[7] = ARGB[permuteMap[3]+4];
 destPixel += 8;
 
 @/textblock </pre>
 
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_422CbYpCrYp16ToARGB16U(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_YpCbCrToARGB *info, const uint8_t permuteMap[4], const uint16_t alpha, vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB16UTo422CbYpCrYp16
 
 @abstract Convert ARGB16U to YUV 422CbYpCrYp16 format.
 
 @param src
 A pointer to vImage_Buffer that references 16-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references YUV 422CbYpCrYp16 destination pixels.
 
 @param info
 A pointer to vImage_ARGBToYpCbCr which contains info coeffcient and postBias values.
 This is generated by vImageConvert_ARGBToYpCbCr_GenerateConversion().
 
 @param permuteMap
 Values that can be used to switch the channel order of src.
 permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16U.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16U.
 
 @param flags
 <pre> @textblock
 kvImageGetTempBufferSize    Returns 0. Does no work.
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 
 
 @discussion Convert ARGB16U to YUV 422CbYpCrYp16 format
 <pre> @textblock
 
 pixel0-1
 byte0 byte1   byte2 byte3   byte4 byte5   byte6 byte7
 A0 R0 G0 B0  A1 R1 G1 B1  =>  LE-16-bit-Cb  LE-16-bit-Y0  LE-16-bit-Cr  LE-16-bit-Y1
 
 (LE and left-justified 16-bit-per-component)
 @/textblock </pre>
 
 YUV 422CbYpCrYp16 can be used for 16-bit 'v216' that is defined in CVPixelBuffer.h.
 
 For example, if we want to use this function to convert ARGB16U to 16-bit 'v216' with ITU 601 video range, then we need
 generate vImage_ARGBToYpCbCr by vImageConvert_ARGBToYpCbCr_GenerateConversion() and call this function.
 
 Yp_bias, CbCr_bias, CbCr_bias, R_Yp, G_Yp, B_Yp, R_Cb, G_Cb, B_Cb_R_Cr, G_Cr and B_Cr are calculated and
 converted into the right format by vImageConvert_ARGBToYpCbCr_GenerateConversion() inside of vImage_ARGBToYpCbCr.
 
 The per-pixel operation is:
 <pre> @textblock
 
 uint16_t *srcPixel = src.data;
 A0 = srcPixel[permuteMap[0]];
 R0 = srcPixel[permuteMap[1]];
 G0 = srcPixel[permuteMap[2]];
 B0 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 A1 = srcPixel[permuteMap[0]];
 R1 = srcPixel[permuteMap[1]];
 G1 = srcPixel[permuteMap[2]];
 B1 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 Yp0 = Yp_bias + ROUND_TO_NEAREST_INTEGER( R0 * R_Yp + G0 * G_Yp + B0 * B_Yp )
 Yp1 = Yp_bias + ROUND_TO_NEAREST_INTEGER( R1 * R_Yp + G1 * G_Yp + B1 * B_Yp )
 R0 += R1;  G0 += G1;   B0 += B1;
 Cb0 = CbCr_bias + ROUND_TO_NEAREST_INTEGER( ( R0 * R_Cb + G0 * G_Cb + B0 * B_Cb_R_Cr) / 2 )
 Cr0 = CbCr_bias + ROUND_TO_NEAREST_INTEGER( ( R0 * B_Cb_R_Cr + G0 * G_Cr + B0 * B_Cr) / 2 )
 
 uint64_t *destPixel = dest.data;
 pack16bitv216AndStore(destPixel, Yp0, Yp1, Cb0, Cr0);
 destPixel += 1;
 
 @/textblock </pre>
 
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 Chroma is sampled at center by default.
 
 Note: vImage doesn't do anything with the alpha here. It is just thrown away. The operation is therefore best suited for kCGImageAlphaNoneSkip<First/Last>
 images.  If it has alpha, you may wish to composite against an opaque background first, before the transparency information is lost.
 If it is premultiplied by alpha, you at minimum should unpremultiply it first, or composite it against an opaque background. See
 vImageUnpremultiplyData_ARGB16U() and vImageFlatten_ARGB16U().
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB16UTo422CbYpCrYp16(const vImage_Buffer *src, const vImage_Buffer *dest, const vImage_ARGBToYpCbCr *info, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2,3) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*! @functiongroup RGBA1010102    */

/*!
 @function vImageConvert_RGBA1010102ToARGB8888
 
 @abstract Convert RGBA1010102 to ARGB8888 format.
 
 @param src
 A pointer to vImage_Buffer that references 10-bit RGB interleaved source pixels. Source pixels must be at least 4 byte aligned.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels. Destination pixels may have any alignment.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param flags
 \p kvImageDoNotTile        Disables internal multithreading, if any.
 
 @discussion
 RGBA1010102 is almost the same format that is defined in CVPixelBuffer.h as 'kCVPixelFormatType_30RGB'
 except that this format uses the least significant 2 bits for alpha channel.
 
 This format is 10-bit big endian 32-bit pixels.
 
 RGB101010RangeMax & RGB101010RangeMin are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 @code
 RGB101010RangeMax  = 1023;
 RGB101010RangeMin  = 0;
 @endcode
 
 The per-pixel operation is:
 @code
 uint32_t *srcPixel = src.data;
 uint32_t pixel = ntohl(srcPixel[0]);
 srcPixel += 1;
 
 int32_t A2  = pixel & 0x3;
 int32_t R10 = (pixel >> 22) & 0x3ff;
 int32_t G10 = (pixel >> 12) & 0x3ff;
 int32_t B10 = (pixel >>  2) & 0x3ff;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 
 A2  = (A2 * UCHAR_MAX + 1) / 3;
 R10 = ((R10 - RGB101010RangeMin) * UCHAR_MAX + (range10 >> 1)) / range10;
 G10 = ((G10 - RGB101010RangeMin) * UCHAR_MAX + (range10 >> 1)) / range10;
 B10 = ((B10 - RGB101010RangeMin) * UCHAR_MAX + (range10 >> 1)) / range10;
 
 uint8_t R8, G8, B8;
 R8 = CLAMP(0, R10, UCHAR_MAX);
 G8 = CLAMP(0, G10, UCHAR_MAX);
 B8 = CLAMP(0, B10, UCHAR_MAX);
 
 uint8_t ARGB[4];
 ARGB[0] = A2;
 ARGB[1] = R8;
 ARGB[2] = G8;
 ARGB[3] = B8;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @endcode
 
 @return kvImageNoError                     Is returned when there was no error.
 @return kvImageUnknownFlagsBit             Is returned when there is a unknown flag.
 @return kvImageRoiLargerThanInputBuffer    Is returned when src.width < dest.width || src.height < dest.height
 @return kvImageInvalidParameter            Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax.
 
 @note Results are guaranteed to be faithfully rounded.
 */
VIMAGE_PF vImage_Error vImageConvert_RGBA1010102ToARGB8888(const vImage_Buffer *src, const vImage_Buffer *dest, int32_t RGB101010RangeMin, int32_t RGB101010RangeMax, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB8888ToRGBA1010102
 
 @abstract Convert ARGB8888 to RGBA1010102 format.
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels. Source pixels may have any alignment.
 
 @param dest
 A pointer to vImage_Buffer that references 10-bit RGB interleaved destination pixels.  Destination pixels must be at least 4 byte aligned.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of src.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param flags
 \p kvImageDoNotTile    Disables internal multithreading, if any.
 
 @discussion
 RGBA1010102 is almost the same format that is defined in CVPixelBuffer.h as 'kCVPixelFormatType_30RGB'
 except that this format uses the least significant 2 bits for alpha channel.
 
 This format is 10-bit big endian 32-bit pixels.
 
 RGB101010RangeMax & RGB101010RangeMin are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 @code
 RGB101010RangeMax  = 1023;
 RGB101010RangeMin  = 0;
 @endcode
 
 The per-pixel operation is:
 @code
 uint8_t *srcPixel = src.data;
 A8 = srcPixel[permuteMap[0]];
 R8 = srcPixel[permuteMap[1]];
 G8 = srcPixel[permuteMap[2]];
 B8 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 int32_t R10, G10, B10;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 int32_t rounding = UCHAR_MAX >> 1;
 R10 = ((R8 * range10 + rounding) / UCHAR_MAX) + RGB101010RangeMin;
 G10 = ((G8 * range10 + rounding) / UCHAR_MAX) + RGB101010RangeMin;
 B10 = ((B8 * range10 + rounding) / UCHAR_MAX) + RGB101010RangeMin;
 A10 = ((A10 * 3 + rounding) / UCHAR_MAX);
 
 uint32_t *destPixel = dest.data;
 destPixel[0] = htonl((R10 << 22) | (G10 << 12) | (B10 << 2) | A10);
 destPixel += 1;
 @endcode
 
 @return kvImageNoError                  Is returned when there was no error.
 @return kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 @return kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @return kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax.
 
 @note Results are guaranteed to be faithfully rounded.
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB8888ToRGBA1010102(const vImage_Buffer *src, const vImage_Buffer *dest, int32_t RGB101010RangeMin, int32_t RGB101010RangeMax, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_RGBA1010102ToARGB16Q12
 
 @abstract Convert RGBA1010102 to ARGB16Q12 format.
 
 @param src
 A pointer to vImage_Buffer that references 10-bit RGB interleaved source pixels.  Samples must be at least 4 byte aligned.
 
 @param dest
 A pointer to vImage_Buffer that references 16Q12 ARGB interleaved destination pixels.  Samples must be at least 2 byte aligned.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16Q12.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16Q12.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as each channel is unique.  That is, ARRG is not an allowed order
 because R is repeated.
 
 @param flags
 <pre> @textblock
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 
 @discussion Convert RGBA1010102 to ARGB16Q12 format
 
 RGBA1010102 is almost the same format that is defined in CVPixelBuffer.h as 'kCVPixelFormatType_30RGB'
 except that this format uses the least significant 2 bits for alpha channel.
 
 This format is 10-bit big endian 32-bit pixels.
 
 RGB101010RangeMax & RGB101010RangeMin are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 
 <pre> @textblock
 RGB101010RangeMax  = 1023;
 RGB101010RangeMin  = 0;
 @/textblock </pre>
 
 The per-pixel operation is:
 
 <pre> @textblock
 uint32_t *srcPixel = src.data;
 uint32_t pixel = ntohl(srcPixel[0]);
 srcPixel += 1;
 
 int32_t A2  = pixel & 0x3;
 int32_t R10 = (pixel >> 22) & 0x3ff;
 int32_t G10 = (pixel >> 12) & 0x3ff;
 int32_t B10 = (pixel >>  2) & 0x3ff;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 
 int16_t R16, G16, B16;
 A2  = (A2 * 4096 + 1) / 3;
 R16 = ((R10 - RGB101010RangeMin) * 4096 + (range10 >> 1)) / range10;
 G16 = ((G10 - RGB101010RangeMin) * 4096 + (range10 >> 1)) / range10;
 B16 = ((B10 - RGB101010RangeMin) * 4096 + (range10 >> 1)) / range10;
 
 R16 = CLAMP(INT16_MIN, R16, INT16_MAX);
 G16 = CLAMP(INT16_MIN, G16, INT16_MAX);
 B16 = CLAMP(INT16_MIN, B16, INT16_MAX);
 
 int16_t ARGB[4];
 ARGB[0] = A2;
 ARGB[1] = R16;
 ARGB[2] = G16;
 ARGB[3] = B16;
 
 int16_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax.
 @/textblock </pre>
 
 Note: Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_RGBA1010102ToARGB16Q12(const vImage_Buffer *src, const vImage_Buffer *dest, int32_t RGB101010RangeMin, int32_t RGB101010RangeMax, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB16Q12ToRGBA1010102
 
 @abstract Convert ARGB16Q12 to RGBA1010102 format.
 
 @param src
 A pointer to vImage_Buffer that references 16Q12 ARGB interleaved source pixels.   ARGB16Q12 pixels must be at least 2 byte aligned.
 
 @param dest
 A pointer to vImage_Buffer that references 10-bit RGB interleaved destination pixels.  RGBA1010102 pixels must be at least 4 byte aligned.
 
 @param RGB101010RangeMax
 A maximum value for the range of 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for the range of 10-bit RGB pixel.
 
 @param RGB101010Max
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010Min
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16Q12.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16Q12.
 
 @param flags
 <pre> @textblock
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB16Q12 to RGBA1010102 format.
 
 RGBA1010102 is almost the same format that is defined in CVPixelBuffer.h as 'kCVPixelFormatType_30RGB'
 except that this format uses the least significant 2 bits for alpha channel.
 
 This format is 10-bit big endian 32-bit pixels.
 
 RGB101010RangeMax & RGB101010RangeMin are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 
 <pre> @textblock
 RGB101010RangeMax  = 1023;
 RGB101010RangeMin  = 0;
 @/textblock </pre>
 
 RGB101010Max & RGB101010Min are available to specify the min / max of the representation.
 This will be used as clipping the results.
 
 <pre> @textblock
 RGB101010Max  = 1023;
 RGB101010Min  = 0;
 @/textblock </pre>
 
 This is needed because 16Q12 has a chance to be outside of [0.0, 1.0] range and we are converting those
 values into video-range. Then, there will be some numbers outside of 10-bit video-range and we want those
 values to be representable as much as possible.
 
 The per-pixel operation is:
 <pre> @textblock
 
 int16_t *srcPixel = src.data;
 A16 = srcPixel[permuteMap[0]];
 R16 = srcPixel[permuteMap[1]];
 G16 = srcPixel[permuteMap[2]];
 B16 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 int32_t R10, G10, B10;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 R10 = CLAMP(RGB101010Min, ((R16 * range10 + 2048) >> 12) + RGB101010RangeMin, RGB101010Max);
 G10 = CLAMP(RGB101010Min, ((G16 * range10 + 2048) >> 12) + RGB101010RangeMin, RGB101010Max);
 B10 = CLAMP(RGB101010Min, ((B16 * range10 + 2048) >> 12) + RGB101010RangeMin, RGB101010Max);
 A10 = CLAMP( 0, (A16 * 3 + 2048) >> 12), 3);
 
 uint32_t *destPixel = dest.data;
 destPixel[0] = htonl((R10 << 22) | (G10 << 12) | (B10 << 2) | A10);
 destPixel += 1;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 kvImageInvalidParameter         Is returned when RGB101010Min > RGB101010Max || RGB101010RangeMin > RGB101010RangeMax
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB16Q12ToRGBA1010102(const vImage_Buffer *src, const vImage_Buffer *dest, int32_t RGB101010RangeMin, int32_t RGB101010RangeMax, int32_t RGB101010Min, int32_t RGB101010Max, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*!
 @function vImageConvert_RGBA1010102ToARGB16U
 
 @abstract Convert RGBA1010102 to ARGB16U format.
 
 @param src
 A pointer to vImage_Buffer that references 10-bit RGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 16-bit ARGB interleaved destination pixels.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16U.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16U.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3.
 
 @param flags
 <pre> @textblock
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert RGBA1010102 to ARGB16U format
 
 RGBA1010102 is almost the same format that is defined in CVPixelBuffer.h as 'kCVPixelFormatType_30RGB'
 except that this format uses the least significant 2 bits for alpha channel.
 
 This format is 10-bit big endian 32-bit pixels.
 
 RGB101010RangeMax & RGB101010RangeMin are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 
 <pre> @textblock
 RGB101010RangeMax  = 1023;
 RGB101010RangeMin  = 0;
 @/textblock </pre>
 
 The per-pixel operation is:
 <pre> @textblock
 
 uint32_t *srcPixel = src.data;
 uint32_t pixel = ntohl(srcPixel[0]);
 srcPixel += 1;
 
 int32_t A2  = pixel & 0x3;
 int32_t R10 = (pixel >> 22) & 0x3ff;
 int32_t G10 = (pixel >> 12) & 0x3ff;
 int32_t B10 = (pixel >>  2) & 0x3ff;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 
 A2  = (A2 * USHRT_MAX + 1) / 3;
 R10 = ((R10 - RGB101010RangeMin) * USHRT_MAX + (range10 >> 1)) / range10;
 G10 = ((G10 - RGB101010RangeMin) * USHRT_MAX + (range10 >> 1)) / range10;
 B10 = ((B10 - RGB101010RangeMin) * USHRT_MAX + (range10 >> 1)) / range10;
 
 uint16_t R16, G16, B16;
 R16 = CLAMP(0, R10, USHRT_MAX);
 G16 = CLAMP(0, G10, USHRT_MAX);
 B16 = CLAMP(0, B10, USHRT_MAX);
 
 uint16_t ARGB[4];
 ARGB[0] = A2;
 ARGB[1] = R16;
 ARGB[2] = G16;
 ARGB[3] = B16;
 
 uint16_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @/textblock </pre>
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax.
 @/textblock </pre>
 
 Note: Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_RGBA1010102ToARGB16U(const vImage_Buffer *src, const vImage_Buffer *dest, int32_t RGB101010RangeMin, int32_t RGB101010RangeMax, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*!
 @function vImageConvert_ARGB16UToRGBA1010102
 
 @abstract Convert ARGB16U to RGBA1010102 format.
 
 @param src
 A pointer to vImage_Buffer that references 16-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 10-bit RGB interleaved destination pixels.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16U.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16U.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as each channel appears only once.
 
 @param flags
 <pre> @textblock
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock </pre>
 @discussion Convert ARGB16U to RGB101010 format.
 
 RGB101010 is almost the same format that is defined in CVPixelBuffer.h as 'kCVPixelFormatType_30RGB'
 except that this format uses the least significant 2 bits for alpha channel.
 
 This format is 10-bit big endian 32-bit pixels.
 
 RGB101010RangeMax & RGB101010RangeMin are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 
 RGB101010RangeMax  = 1023;
 RGB101010RangeMin  = 0;
 
 The per-pixel operation is:
 
 uint16_t *srcPixel = src.data;
 A16 = srcPixel[permuteMap[0]];
 R16 = srcPixel[permuteMap[1]];
 G16 = srcPixel[permuteMap[2]];
 B16 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 int32_t R10, G10, B10;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 R10 = ((R16 * range10 + (USHRT_MAX >> 1)) / USHRT_MAX) + RGB101010RangeMin;
 G10 = ((G16 * range10 + (USHRT_MAX >> 1)) / USHRT_MAX) + RGB101010RangeMin;
 B10 = ((B16 * range10 + (USHRT_MAX >> 1)) / USHRT_MAX) + RGB101010RangeMin;
 A10 = ((A16 * 3 + (USHRT_MAX >> 1)) / USHRT_MAX);
 
 uint32_t *destPixel = dest.data;
 destPixel[0] = htonl((R10 << 22) | (G10 << 12) | (B10 << 2) | A10);
 destPixel += 1;
 
 @return
 <pre> @textblock
 kvImageNoError                  Is returned when there was no error.
 kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax.
 @/textblock </pre>
 
 Results are guaranteed to be faithfully rounded.
 
 
 */

VIMAGE_PF vImage_Error vImageConvert_ARGB16UToRGBA1010102(const vImage_Buffer *src, const vImage_Buffer *dest, int32_t RGB101010RangeMin, int32_t RGB101010RangeMax, const uint8_t permuteMap[4], vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));

/*! @functiongroup RGB888 */

/*!
 @function vImagePermuteChannels_RGB888
 
 @abstract Reorder 3 color channels within the buffer according to the permute map.
 
 @param src
 A pointer to vImage_Buffer that references 8-bit 3-channel interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit 3-channel interleaved destination pixels.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For exmaple, permuteMap[3] = {0, 1, 2} or NULL will produce the same dest pixels as the src.
 permuteMap[3] = {2, 1, 0} is the reverse ordered dest pixels from the dest.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, or 2.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 
 @discussion This function can be used to reorder 3 color channel buffer.
 
 The per-pixel operation is:
 
 @code
 uint8_t *srcRow = src.data;
 uint8_t *destRow = dest.data;
 
 R = srcRow[permuteMap[0]];
 G = srcRow[permuteMap[1]];
 B = srcRow[permuteMap[2]];
 srcRow += 3;
 
 destRow[0] = R;
 destRow[1] = G;
 destRow[2] = B;
 destRow += 3;
 @endcode
 
 @return kvImageNoError                  Is returned when there was no error.
 @return kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 @return kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 
 @note Works in place.
 */

VIMAGE_PF vImage_Error vImagePermuteChannels_RGB888(const vImage_Buffer *src, const vImage_Buffer *dest, const uint8_t permuteMap[3], vImage_Flags flags) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*!
 @functiongroup Format agnostic
 */

/*!
 @function vImageCopyBuffer
 
 @abstract Copy vImage buffer from src to dest.
 
 @param src
 A pointer to source vImage_Buffer.
 
 @param dest
 A pointer to destination vImage_Buffer.
 
 @param pixelSize
 Number of bytes for one pixel.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 \p kvImageGetTempBufferSize    Returns 0. Does no work.
 
 @return \p kvImageNoError                      Is returned when there was no error.
 @return \p kvImageRoiLargerThanInputBuffer     Is returned when src.width < dest.width || src.height < dest.height
 
 @seealso vImage_Buffer
 */

VIMAGE_PF vImage_Error vImageCopyBuffer(const vImage_Buffer *src, const vImage_Buffer *dest, size_t pixelSize, vImage_Flags flags ) VIMAGE_NON_NULL(1,2) API_AVAILABLE(macos(10.10), ios(8.0), watchos(1.0), tvos(8.0));


/*!  @functiongroup XRGB2101010  */
/*!
 @function vImageConvert_XRGB2101010ToARGB8888
 
 @abstract Convert XRGB2101010 to ARGB8888 format.
 
 @param src
 A pointer to vImage_Buffer that references 10-bit RGB interleaved source pixels.
 XRGB2101010 pixels must be at least 4 byte aligned.
 
 @param dest
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved destination pixels.
 ARGB8888 pixels may have any alignment.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For example, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3, as long as each channel appears only once.
 
 @param flags
 <pre> @textblock
 kvImageDoNotTile            Disables internal multithreading, if any.
 @/textblock <pre>
 
 @discussion
 This format is 10-bit little endian 32-bit pixels. The 2 MSB are zero.
 
 RGB101010RangeMin & RGB101010RangeMax are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 @code
 RGB101010RangeMin  = 0;
 RGB101010RangeMax  = 1023;
 @endcode
 
 The per-pixel operation is:
 
 @code
 uint32_t *srcPixel = src.data;
 uint32_t pixel = srcPixel[0];
 srcPixel += 1;
 
 int32_t R10 = (pixel >> 20) & 0x3ff;
 int32_t G10 = (pixel >> 10) & 0x3ff;
 int32_t B10 = (pixel >>  0) & 0x3ff;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 
 R10 = ((R10 - RGB101010RangeMin) * UCHAR_MAX + (range10 >> 1)) / range10;
 G10 = ((G10 - RGB101010RangeMin) * UCHAR_MAX + (range10 >> 1)) / range10;
 B10 = ((B10 - RGB101010RangeMin) * UCHAR_MAX + (range10 >> 1)) / range10;
 
 uint8_t R8, G8, B8;
 R8 = CLAMP(0, R10, UCHAR_MAX);
 G8 = CLAMP(0, G10, UCHAR_MAX);
 B8 = CLAMP(0, B10, UCHAR_MAX);
 
 uint8_t ARGB[4];
 ARGB[0] = alpha;
 ARGB[1] = R8;
 ARGB[2] = G8;
 ARGB[3] = B8;
 
 uint8_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @endcode
 
 @return \p kvImageNoError                  Is returned when there was no error.
 @return \p kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 @return \p kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @return \p kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax
 or when RGB101010RangeMin < 0 || RGB101010RangeMax > 1023.
 
 @note Results are guaranteed to be faithfully rounded.
 
 @seealso vImageConvert_ARGB2101010ToARGB8888
 */
VIMAGE_PF vImage_Error vImageConvert_XRGB2101010ToARGB8888(const vImage_Buffer *src, Pixel_8 alpha,
                                                           const vImage_Buffer *dest,
                                                           int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                           const uint8_t permuteMap[4],
                                                           vImage_Flags flags)
VIMAGE_NON_NULL(1,3)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));
VIMAGE_PF vImage_Error vImageConvert_ARGB2101010ToARGB8888(const vImage_Buffer *src,
                                                           const vImage_Buffer *dest,
                                                           int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                           const uint8_t permuteMap[4],
                                                           vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));


/*!
 @function vImageConvert_ARGB8888ToXRGB2101010
 
 @abstract Convert ARGB8888 to XRGB2101010 format.
 
 @param src
 A pointer to vImage_Buffer that references 8-bit ARGB interleaved source pixels.
 ARGB8888 pixels may have any alignment.
 
 @param dest
 A pointer to vImage_Buffer that references 10-bit RGB interleaved destination pixels.
 XRGB2101010 pixels must be at least 4 byte aligned.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of src.
 For example, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB8888.
 permuteMap[4] = {3, 2, 1, 0} is BGRA8888.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3,
 as long as each channel appears only once.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 
 @discussion
 This format is 10-bit little endian 32-bit pixels. The 2 MSB are zero.
 
 RGB101010RangeMin & RGB101010RangeMax are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 @code
 RGB101010RangeMin  = 0;
 RGB101010RangeMax  = 1023;
 @endcode
 
 The per-pixel operation is:
 
 @code
 uint8_t *srcPixel = src.data;
 R8 = srcPixel[permuteMap[1]];
 G8 = srcPixel[permuteMap[2]];
 B8 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 int32_t R10, G10, B10;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 int32_t rounding = UCHAR_MAX >> 1;
 R10 = ((R8 * range10 + rounding) / UCHAR_MAX) + RGB101010RangeMin;
 G10 = ((G8 * range10 + rounding) / UCHAR_MAX) + RGB101010RangeMin;
 B10 = ((B8 * range10 + rounding) / UCHAR_MAX) + RGB101010RangeMin;
 
 uint32_t *destPixel = dest.data;
 destPixel[0] = (R10 << 20) | (G10 << 10) | (B10 << 0);
 destPixel += 1;
 @endcode
 
 @return \p kvImageNoError                  Is returned when there was no error.
 @return \p kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 @return \p kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @return \p kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax
 or when RGB101010RangeMin < 0 || RGB101010RangeMax > 1023.
 
 @note Results are guaranteed to be faithfully rounded.
 
 @seealso vImageConvert_ARGB8888ToARGB2101010
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB8888ToXRGB2101010(const vImage_Buffer *src,
                                                           const vImage_Buffer *dest,
                                                           int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                           const uint8_t permuteMap[4],
                                                           vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));
VIMAGE_PF vImage_Error vImageConvert_ARGB8888ToARGB2101010(const vImage_Buffer *src,
                                                           const vImage_Buffer *dest,
                                                           int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                           const uint8_t permuteMap[4],
                                                           vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));


/*!
 @function vImageConvert_XRGB2101010ToARGB16Q12
 
 @abstract Convert XRGB2101010 to ARGB16Q12 format.
 
 @param src
 A pointer to vImage_Buffer that references 10-bit RGB interleaved source pixels.
 XRGB2101010 pixels must be at least 4 byte aligned.
 
 @param dest
 A pointer to vImage_Buffer that references 16Q12 ARGB interleaved destination pixels.
 ARGB16Q12 ixels must be at least 2 byte aligned.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For example, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16Q12.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16Q12.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3,
 as long as each channel appears only once.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 
 @discussion
 This format is 10-bit little endian 32-bit pixels. The 2 MSB are zero.
 
 RGB101010RangeMin & RGB101010RangeMax are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 @code
 RGB101010RangeMin  = 0;
 RGB101010RangeMax  = 1023;
 @endcode
 
 The per-pixel operation is:
 
 @code
 uint32_t *srcPixel = src.data;
 srcPixel += 1;
 
 int32_t R10 = (pixel >> 20) & 0x3ff;
 int32_t G10 = (pixel >> 10) & 0x3ff;
 int32_t B10 = (pixel >>  0) & 0x3ff;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 
 int16_t R16, G16, B16;
 R16 = ((R10 - RGB101010RangeMin) * 4096 + (range10 >> 1)) / range10;
 G16 = ((G10 - RGB101010RangeMin) * 4096 + (range10 >> 1)) / range10;
 B16 = ((B10 - RGB101010RangeMin) * 4096 + (range10 >> 1)) / range10;
 
 R16 = CLAMP(INT16_MIN, R16, INT16_MAX);
 G16 = CLAMP(INT16_MIN, G16, INT16_MAX);
 B16 = CLAMP(INT16_MIN, B16, INT16_MAX);
 
 int16_t ARGB[4];
 ARGB[0] = alpha;
 ARGB[1] = R16;
 ARGB[2] = G16;
 ARGB[3] = B16;
 
 int16_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @endcode
 
 @return \p kvImageNoError                  Is returned when there was no error.
 @return \p kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 @return \p kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @return \p kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax
 or when RGB101010RangeMin < 0 || RGB101010RangeMax > 1023.
 
 @note Results are guaranteed to be faithfully rounded.
 
 @seealso vImageConvert_ARGB2101010ToARGB16Q12
 */
VIMAGE_PF vImage_Error vImageConvert_XRGB2101010ToARGB16Q12(const vImage_Buffer *src, Pixel_16Q12 alpha,
                                                            const vImage_Buffer *dest,
                                                            int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                            const uint8_t permuteMap[4],
                                                            vImage_Flags flags)
VIMAGE_NON_NULL(1,3)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));
VIMAGE_PF vImage_Error vImageConvert_ARGB2101010ToARGB16Q12(const vImage_Buffer *src,
                                                            const vImage_Buffer *dest,
                                                            int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                            const uint8_t permuteMap[4],
                                                            vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));


/*!
 @function vImageConvert_ARGB16Q12ToXRGB2101010
 
 @abstract Convert ARGB16Q12 to XRGB2101010 format.
 
 @param src
 A pointer to vImage_Buffer that references 16Q12 ARGB interleaved source pixels.
 ARGB16Q12 pixels must be at least 2 byte aligned.
 
 @param dest
 A pointer to vImage_Buffer that references 10-bit RGB interleaved destination pixels.
 XRGB2101010 pixels must be at least 4 byte aligned.
 
 @param RGB101010RangeMax
 A maximum value for the range of 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for the range of 10-bit RGB pixel.
 
 @param RGB101010Max
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010Min
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For example, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16Q12.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16Q12.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3,
 as long as each channel appears only once.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 
 @discussion
 This format is 10-bit little endian 32-bit pixels. The 2 MSB are zero.
 
 RGB101010RangeMin & RGB101010RangeMax are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 @code
 RGB101010RangeMin  = 0;
 RGB101010RangeMax  = 1023;
 @endcode
 
 This is needed because 16Q12 has a chance to be outside of [0.0, 1.0] range and we are converting those
 values into video-range. In that case, there will be some numbers outside of 10-bit video-range and we
 want those values to be representable as much as possible.
 
 The per-pixel operation is:
 @code
 
 int16_t *srcPixel = src.data;
 R16 = srcPixel[permuteMap[1]];
 G16 = srcPixel[permuteMap[2]];
 B16 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 int32_t R10, G10, B10;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 R10 = CLAMP(RGB101010Min, ((R16 * range10 + 2048) >> 12) + RGB101010RangeMin, RGB101010Max);
 G10 = CLAMP(RGB101010Min, ((G16 * range10 + 2048) >> 12) + RGB101010RangeMin, RGB101010Max);
 B10 = CLAMP(RGB101010Min, ((B16 * range10 + 2048) >> 12) + RGB101010RangeMin, RGB101010Max);
 A10 = CLAMP( 0, (A16 * 3 + 2048) >> 12), 3);
 
 uint32_t *destPixel = dest.data;
 destPixel[0] = (R10 << 20) | (G10 << 10) | (B10 << 0);
 destPixel += 1;
 @endcode
 
 @return \p kvImageNoError                  Is returned when there was no error.
 @return \p kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 @return \p kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @return \p kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax
 or when RGB101010RangeMin < 0 || RGB101010RangeMax > 1023.
 
 @note Results are guaranteed to be faithfully rounded.
 
 @seealso vImageConvert_ARGB16Q12ToARGB2101010
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB16Q12ToXRGB2101010(const vImage_Buffer *src,
                                                            const vImage_Buffer *dest,
                                                            int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                            int32_t RGB101010Min, int32_t RGB101010Max,
                                                            const uint8_t permuteMap[4],
                                                            vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));
VIMAGE_PF vImage_Error vImageConvert_ARGB16Q12ToARGB2101010(const vImage_Buffer *src,
                                                            const vImage_Buffer *dest,
                                                            int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                            int32_t RGB101010Min, int32_t RGB101010Max,
                                                            const uint8_t permuteMap[4],
                                                            vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));


/*!
 @function vImageConvert_XRGB2101010ToARGB16U
 
 @abstract Convert XRGB2101010 to ARGB16U format.
 
 @param src
 A pointer to vImage_Buffer that references 10-bit RGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 16-bit ARGB interleaved destination pixels.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For example, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16U.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16U.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3,
 as long as each channel appears only once.
 
 @param flags
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 
 @discussion
 This format is 10-bit little endian 32-bit pixels. The 2 MSB are zero.
 
 RGB101010RangeMin & RGB101010RangeMax are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 @code
 RGB101010RangeMin  = 0;
 RGB101010RangeMax  = 1023;
 @endcode
 
 The per-pixel operation is:
 @code
 uint32_t *srcPixel = src.data;
 uint32_t pixel = ntohl(srcPixel[0]);
 srcPixel += 1;
 
 int32_t R10 = (pixel >> 20) & 0x3ff;
 int32_t G10 = (pixel >> 10) & 0x3ff;
 int32_t B10 = (pixel >>  0) & 0x3ff;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 
 R10 = ((R10 - RGB101010RangeMin) * USHRT_MAX + (range10 >> 1)) / range10;
 G10 = ((G10 - RGB101010RangeMin) * USHRT_MAX + (range10 >> 1)) / range10;
 B10 = ((B10 - RGB101010RangeMin) * USHRT_MAX + (range10 >> 1)) / range10;
 
 uint16_t R16, G16, B16;
 R16 = CLAMP(0, R10, USHRT_MAX);
 G16 = CLAMP(0, G10, USHRT_MAX);
 B16 = CLAMP(0, B10, USHRT_MAX);
 
 uint16_t ARGB[4];
 ARGB[0] = alpha;
 ARGB[1] = R16;
 ARGB[2] = G16;
 ARGB[3] = B16;
 
 uint16_t *destPixel = dest.data;
 destPixel[0] = ARGB[permuteMap[0]];
 destPixel[1] = ARGB[permuteMap[1]];
 destPixel[2] = ARGB[permuteMap[2]];
 destPixel[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @endcode
 
 @return \p kvImageNoError                  Is returned when there was no error.
 @return \p kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 @return \p kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @return \p kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax
 or when RGB101010RangeMin < 0 || RGB101010RangeMax > 1023.
 
 @note Results are guaranteed to be faithfully rounded.
 
 @seealso vImageConvert_ARGB2101010ToARGB16U
 */
VIMAGE_PF vImage_Error vImageConvert_XRGB2101010ToARGB16U(const vImage_Buffer *src, uint16_t alpha,
                                                          const vImage_Buffer *dest,
                                                          int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                          const uint8_t permuteMap[4],
                                                          vImage_Flags flags)
VIMAGE_NON_NULL(1,3)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));
VIMAGE_PF vImage_Error vImageConvert_ARGB2101010ToARGB16U(const vImage_Buffer *src,
                                                          const vImage_Buffer *dest,
                                                          int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                          const uint8_t permuteMap[4],
                                                          vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));

/*!
 @function vImageConvert_ARGB16UToXRGB2101010
 
 @abstract Convert ARGB16U to XRGB2101010 format.
 
 @param src
 A pointer to vImage_Buffer that references 16-bit ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 10-bit RGB interleaved destination pixels.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For example, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16U.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16U.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3,
 as long as each channel appears only once.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 
 @discussion
 This format is 10-bit big endian 32-bit pixels.
 
 RGB101010RangeMin & RGB101010RangeMax are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 
 @code
 RGB101010RangeMin  = 0;
 RGB101010RangeMax  = 1023;
 @endcode
 
 The per-pixel operation is:
 @code
 
 uint16_t *srcPixel = src.data;
 R16 = srcPixel[permuteMap[1]];
 G16 = srcPixel[permuteMap[2]];
 B16 = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 int32_t R10, G10, B10;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 R10 = ((R16 * range10 + (USHRT_MAX >> 1)) / USHRT_MAX) + RGB101010RangeMin;
 G10 = ((G16 * range10 + (USHRT_MAX >> 1)) / USHRT_MAX) + RGB101010RangeMin;
 B10 = ((B16 * range10 + (USHRT_MAX >> 1)) / USHRT_MAX) + RGB101010RangeMin;
 
 uint32_t *destPixel = dest.data;
 destPixel[0] = (R10 << 20) | (G10 << 10) | (B10 << 0);
 destPixel += 1;
 @endcode
 
 @return \p kvImageNoError                  Is returned when there was no error.
 @return \p kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 @return \p kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @return \p kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax
 or when RGB101010RangeMin < 0 || RGB101010RangeMax > 1023.
 
 @note Results are guaranteed to be faithfully rounded.
 
 @seealso vImageConvert_ARGB16UToARGB2101010
 */
VIMAGE_PF vImage_Error vImageConvert_ARGB16UToXRGB2101010(const vImage_Buffer *src,
                                                          const vImage_Buffer *dest,
                                                          int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                          const uint8_t permuteMap[4],
                                                          vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));
VIMAGE_PF vImage_Error vImageConvert_ARGB16UToARGB2101010(const vImage_Buffer *src,
                                                          const vImage_Buffer *dest,
                                                          int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                          const uint8_t permuteMap[4],
                                                          vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));


/*!
 @function vImageConvert_XRGB2101010ToARGBFFFF
 
 @abstract Convert XRGB2101010 to ARGBFFFF format.
 
 @param src
 A pointer to vImage_Buffer that references 10-bit RGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 32-bit float ARGB interleaved destination pixels.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For example, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGBFFFF.
 permuteMap[4] = {3, 2, 1, 0} is BGRAFFFF.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3,
 as long as each channel appears only once.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 \p kvImageDoNotClamp           Disables clamping floating point values to [0, 1].
 
 @discussion
 This format is 10-bit little endian 32-bit pixels. The 2 MSB are zero.
 
 RGB101010RangeMin & RGB101010RangeMax are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 @code
 RGB101010RangeMin  = 0;
 RGB101010RangeMax  = 1023;
 @endcode
 
 The per-pixel operation is:
 @code
 uint32_t *srcPixel = src.data;
 uint32_t pixel = ntohl(srcPixel[0]);
 srcPixel += 1;
 
 int32_t R10 = (pixel >> 20) & 0x3ff;
 int32_t G10 = (pixel >> 10) & 0x3ff;
 int32_t B10 = (pixel >>  0) & 0x3ff;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 
 float RF, GF, BF;
 RF = (R10 - RGB101010RangeMin) / (float)range10;
 GF = (G10 - RGB101010RangeMin) / (float)range10;
 BF = (B10 - RGB101010RangeMin) / (float)range10;
 
 if (!(flags & kvImageDoNotClamp)) {
 RF = CLAMP(RF, 0.0f, 1.0f);
 GF = CLAMP(GF, 0.0f, 1.0f);
 BF = CLAMP(BF, 0.0f, 1.0f);
 }
 
 float ARGB[4];
 ARGB[0] = alpha;
 ARGB[1] = RF;
 ARGB[2] = GF;
 ARGB[3] = BF;
 
 float *destPixel = dest.data;
 destRow[0] = ARGB[permuteMap[0]];
 destRow[1] = ARGB[permuteMap[1]];
 destRow[2] = ARGB[permuteMap[2]];
 destRow[3] = ARGB[permuteMap[3]];
 destPixel += 4;
 @endcode
 
 @return \p kvImageNoError                  Is returned when there was no error.
 @return \p kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 @return \p kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @return \p kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax
 or when RGB101010RangeMin < 0 || RGB101010RangeMax > 1023.
 
 @note Results are guaranteed to be faithfully rounded.
 
 @seealso vImageConvert_ARGB2101010ToARGBFFFF
 */
VIMAGE_PF vImage_Error vImageConvert_XRGB2101010ToARGBFFFF(const vImage_Buffer *src, Pixel_F alpha,
                                                           const vImage_Buffer *dest,
                                                           int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                           const uint8_t permuteMap[4],
                                                           vImage_Flags flags)
VIMAGE_NON_NULL(1,3)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));
VIMAGE_PF vImage_Error vImageConvert_ARGB2101010ToARGBFFFF(const vImage_Buffer *src,
                                                           const vImage_Buffer *dest,
                                                           int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                           const uint8_t permuteMap[4],
                                                           vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));


/*!
 @function vImageConvert_ARGBFFFFToXRGB2101010
 
 @abstract Convert ARGBFFFF to XRGB2101010 format.
 
 @param src
 A pointer to vImage_Buffer that references 32-bit float ARGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 10-bit RGB interleaved destination pixels.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of source.
 For exmaple, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGBFFFF.
 permuteMap[4] = {3, 2, 1, 0} is BGRAFFFF.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3,
 as long as each channel appears only once.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 \p kvImageDoNotClamp           Disables clamping floating point values to [0, 1].
 
 @discussion
 This format is 10-bit little endian 32-bit pixels. The 2 MSB are zero.
 
 RGB101010RangeMin & RGB101010RangeMax are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 @code
 RGB101010RangeMin  = 0;
 RGB101010RangeMax  = 1023;
 @endcode
 
 The per-pixel operation is:
 @code
 float *srcPixel = src.data;
 float AF, RF, GF, BF;
 AF = srcPixel[permuteMap[0]];
 RF = srcPixel[permuteMap[1]];
 GF = srcPixel[permuteMap[2]];
 BF = srcPixel[permuteMap[3]];
 srcPixel += 4;
 
 if (!(flags & kvImageDoNotClamp)) {
 RF = CLAMP(RF, 0.0f, 1.0f);
 GF = CLAMP(GF, 0.0f, 1.0f);
 BF = CLAMP(BF, 0.0f, 1.0f);
 }
 
 int32_t A2, R10, G10, B10;
 int32_t range10  = RGB101010RangeMax - RGB101010RangeMin;
 A2  = (int)(AF * 3.0f + 0.5f);
 R10 = (int)(RF * range10 + 0.5f) + RGB101010RangeMin;
 G10 = (int)(GF * range10 + 0.5f) + RGB101010RangeMin;
 B10 = (int)(BF * range10 + 0.5f) + RGB101010RangeMin;
 
 uint32_t *destPixel = dest.data;
 destPixel[0] = (A2 << 30) | (R10 << 20) | (G10 << 10) | (B10 << 0);
 destPixel += 1;
 @endcode
 
 @return \p kvImageNoError                  Is returned when there was no error.
 @return \p kvImageUnknownFlagsBit          Is returned when there is a unknown flag.
 @return \p kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height
 @return \p kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax
 or when RGB101010RangeMin < 0 || RGB101010RangeMax > 1023.
 
 @note Results are guaranteed to be faithfully rounded.
 
 @seealso vImageConvert_ARGBFFFFToARGB2101010
 */
VIMAGE_PF vImage_Error vImageConvert_ARGBFFFFToXRGB2101010(const vImage_Buffer *src,
                                                           const vImage_Buffer *dest,
                                                           int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                           const uint8_t permuteMap[4],
                                                           vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));
VIMAGE_PF vImage_Error vImageConvert_ARGBFFFFToARGB2101010(const vImage_Buffer *src,
                                                           const vImage_Buffer *dest,
                                                           int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                           const uint8_t permuteMap[4],
                                                           vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!
 @function vImageConvert_XRGB2101010ToARGB16F
 
 @abstract Convert XRGB2101010 to ARGB16F format.
 
 @param src
 A pointer to vImage_Buffer that references 10-bit RGB interleaved source pixels.
 
 @param dest
 A pointer to vImage_Buffer that references 16-bit float ARGB interleaved destination pixels.
 
 @param RGB101010RangeMax
 A maximum value for 10-bit RGB pixel.
 
 @param RGB101010RangeMin
 A minimum value for 10-bit RGB pixel.
 
 @param permuteMap
 Values that can be used to switch the channel order of dest.
 For example, permuteMap[4] = {0, 1, 2, 3} or NULL are ARGB16F.
 permuteMap[4] = {3, 2, 1, 0} is BGRA16F.
 Any order of permuteMap is allowed when each permuteMap value is 0, 1, 2, or 3,
 as long as each channel appears only once.
 
 @param flags
 \p kvImageDoNotTile            Disables internal multithreading, if any.
 \p kvImageDoNotClamp           Disables clamping floating point values to [0, 1].
 
 @discussion
 XRGB2101010 is the same format that is defined in CVPixelBuffer.h as
 'kCVPixelFormatType_30RGBLEPackedWideGamut' or 'w30r'.
 
 This format is 10-bit little endian 32-bit pixels. The 2 MSB are zero.
 
 RGB101010RangeMin & RGB101010RangeMax are available for non-full-range pixel values.
 For full-range pixel values, the user can set these as
 @code
 RGB101010RangeMin  = 0;
 RGB101010RangeMax  = 1023;
 @endcode
 
 The per-pixel operation is:
 @code
 uint32_t *srcPixel = src.data;
 uint32_t pixel = ntohl(srcPixel[0]);
 srcPixel += 1;
 
 int32_t R10 = (pixel >> 20) & 0x3ff;
 int32_t G10 = (pixel >> 10) & 0x3ff;
 int32_t B10 = (pixel >>  0) & 0x3ff;
 int32_t range10 = RGB101010RangeMax - RGB101010RangeMin;
 
 float RF, GF, BF;
 RF = (R10 - RGB101010RangeMin) / (float)range10;
 GF = (G10 - RGB101010RangeMin) / (float)range10;
 BF = (B10 - RGB101010RangeMin) / (float)range10;
 
 if (!(flags & kvImageDoNotClamp)) {
 RF = CLAMP(RF, 0.0f, 1.0f);
 GF = CLAMP(GF, 0.0f, 1.0f);
 BF = CLAMP(BF, 0.0f, 1.0f);
 }
 
 float ARGB[4];
 ARGB[0] = alpha;
 ARGB[1] = RF;
 ARGB[2] = GF;
 ARGB[3] = BF;
 
 uint16_t *destPixel = dest.data;
 destPixel[0] = ConvertFloatToHalf(ARGB[permA]);
 destPixel[1] = ConvertFloatToHalf(ARGB[permR]);
 destPixel[2] = ConvertFloatToHalf(ARGB[permG]);
 destPixel[3] = ConvertFloatToHalf(ARGB[permB]);
 destPixel += 4;
 @endcode
 
 @return \p kvImageNoError                  Is returned when there was no error.
 @return \p kvImageUnknownFlagsBit          Is returned when there is an unknown flag.
 @return \p kvImageRoiLargerThanInputBuffer Is returned when src.width < dest.width || src.height < dest.height.
 @return \p kvImageInvalidParameter         Is returned when RGB101010RangeMin is bigger than RGB101010RangeMax
 or when RGB101010RangeMin < 0 || RGB101010RangeMax > 1023.
 
 @note Results are guaranteed to be faithfully rounded.
 
 @seealso vImageConvert_ARGB2101010ToARGB16F
 */
VIMAGE_PF vImage_Error vImageConvert_XRGB2101010ToARGB16F(const vImage_Buffer *src, Pixel_F alpha,
                                                          const vImage_Buffer *dest,
                                                          int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                          const uint8_t permuteMap[4],
                                                          vImage_Flags flags)
VIMAGE_NON_NULL(1,3)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));
VIMAGE_PF vImage_Error vImageConvert_ARGB2101010ToARGB16F(const vImage_Buffer *src,
                                                          const vImage_Buffer *dest,
                                                          int32_t RGB101010RangeMin, int32_t RGB101010RangeMax,
                                                          const uint8_t permuteMap[4],
                                                          vImage_Flags flags)
VIMAGE_NON_NULL(1,2)
API_AVAILABLE(macos(10.12), ios(9.3), watchos(3.0), tvos(10.0));

#ifdef __cplusplus
}
#endif

#endif


