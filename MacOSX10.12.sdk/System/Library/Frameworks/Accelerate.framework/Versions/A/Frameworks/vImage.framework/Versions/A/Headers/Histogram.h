/*!
 *  @header Histogram.h
 *  vImage_Framework
 *
 *  See vImage/vImage.h for more on how to view the headerdoc documentation for functions declared herein.
 *
 *  @copyright Copyright (c) 2003-2016 by Apple Inc. All rights reserved.
 *
 *  @discussion Exports interfaces for collecting histograms of images, and causing images to conform to histograms.
 *
 *  @ignorefuncmacro VIMAGE_NON_NULL
 */

#ifndef VIMAGE_HISTOGRAM_H
#define VIMAGE_HISTOGRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vImage/vImage_Types.h>

/*!
 * @functiongroup Histogram Calculation
 * @discussion  These functions build a histogram of the frequency of occurence of 
 *              each channel value in the provided image.
 */
    
/*!
 * @function vImageHistogramCalculation_Planar8
 *
 * @abstract Calculates a histogram for a Planar8 image.
 *
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      For each pixel, do the following:
 *          histogram[src[x]]++;
 * @/textblock</pre>
 *
 * This routine will not work in place
 *
 * @param   src            A pointer to a vImage_Buffer that references the source pixels
 *
 * @param   histogram      A pointer to a histogram. On return, this array will
 *                   contain the histogram for the source image.
 *                   The histogram will be an array with 256 elements.
 *
 * @param   flags          The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 * @/textblock</pre>
 *
 * @return The following error codes may be returned
 * <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageNullPointerArgument      src or histogram pointer is NULL.
 * @/textblock</pre>
 */
vImage_Error
vImageHistogramCalculation_Planar8( 
    const vImage_Buffer *src, 
    vImagePixelCount *histogram, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageHistogramCalculation_PlanarF
 *
 * @abstract Calculates a histogram for a PlanarF image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      For each pixel, do the following:
 *          val = histogram_entries * (src[x] - minVal) / (maxVal - minVal);
 *          i = clip val between 0 and histogram_entries-1
 *          histogram[i]++;
 * @/textblock</pre>
 *
 * This routine will not work in place
 *
 * @param   src         A pointer to a vImage_Buffer that references the source pixels
 *
 * @param   histogram   A pointer to a histogram. On return, this array will
 *                      contain the histogram for the source image.
 *                      The histogram will have histogram_entries elements.
 *
 * @param   histogram_entries The number of histogram entries, or bins.
 *                      The histogram will be an array with histogram_entries elements.
 *
 * @param   minVal      A minimum pixel value. Any pixel value less than this will be
 *                      clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the first histogram entry. src is not modified.
 *
 * @param   maxVal      A maximum pixel value. Any pixel value greater than this will
 *                      be clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the last histogram entry.  src is not modified.
 *
 * @param   flags       The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 * @/textblock</pre>
 *
 * @return  The following error codes may occur:
 * <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or histogram pointer is NULL.
 * @/textblock</pre>
 */
vImage_Error 
vImageHistogramCalculation_PlanarF( 
    const vImage_Buffer *src, 
    vImagePixelCount *histogram, 
    unsigned int histogram_entries, 
    Pixel_F minVal, 
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageHistogramCalculation_ARGB8888
 *
 * @abstract Calculates histograms for each channel of an ARGB8888 image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *
 *      For each pixel and channel, do the following:
 *          val = src[x];
 *          histogram[ch][val[ch]]++;
 *
 * @/textblock</pre>
 *
 * This routine will not work in place
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF.
 *    The ordering of the histogram will match the channel order of the image.
 *
 * @param   src         A pointer to a vImage_Buffer that references the source pixels
 *
 * @param   histogram   A pointer to a histograms, one each for alpha, red, green, and blue (in that order).
 *                      On return, this array will contain the four histograms for the corresponding channels.
 *                      Each of the four histograms will be an array with 256 elements.
 *                      This function does not allocate storage for the histograms. You must allocate
 *                      storage for each of the four histograms, create an array and populate it with
 *                      pointers to the histograms before calling the function.
 *
 * @param   flags       The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Do not calculate the histogram for the alpha channel
 * @/textblock</pre>
 *
 * @return  The following error codes may occur
 * <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageNullPointerArgument      src or histogram pointer is NULL.
 * @/textblock</pre>
 */
vImage_Error 
vImageHistogramCalculation_ARGB8888( 
    const vImage_Buffer *src, 
    vImagePixelCount *histogram[4], 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageHistogramCalculation_ARGBFFFF
 *
 * @abstract Calculates histograms for each channel of an ARGBFFFF image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      For each pixel, do the following:
 *          val = src[x];
 *          For each channel do:
 *              i = histogram_entries * (val[ch] - minVal) / (maxVal - minVal);
 *              i = clip i between 0 and histogram_entries-1
 *              histogram[ch][i]++;
 * @/textblock</pre>
 *
 * This routine will not work in place
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF.
 *    The ordering of the histogram will match the channel order of the image.
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param histogram     A pointer to an array of four histograms,
 *                      one each for alpha, red, green, and blue (in that order).
 *                      On return, this array will contain the four histograms for the corresponding channels.
 *                      Each of the four histograms will be an array with histogram_entries elements.
 *                      This function does not allocate storage for the histograms. You must allocate
 *                      storage for each of the four histograms, create an array and populate it with
 *                      pointers to the histograms before calling the function.
 *
 * @param histogram_entries The number of histogram entries, or bins. Each of the four
 *                      calculated histograms will be an array with histogram_entries elements.
 *
 * @param minVal        A minimum pixel value. Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *                      This minimum value is applied to each of the four channels separately.
 *
 * @param maxVal        A maximum pixel value. Any pixel value greater than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry.
 *                      This maximum value is applied to each of the four channels separately.
 *
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Do not calculate the histogram for the alpha channel
 * @/textblock</pre>
 *
 * @return The following error codes may be returned:
 * <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or any of the histogram pointers is NULL.
 * @/textblock</pre>
 *
 */
vImage_Error 
vImageHistogramCalculation_ARGBFFFF( 
    const vImage_Buffer *src, 
    vImagePixelCount *histogram[4], 
    unsigned int histogram_entries, 
    Pixel_F minVal, 
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*!
 * @functiongroup Histogram Equalization
 * @discussion These functions attempt to change an image such that its histogram
 *              contains an even distribution of values.
 */

/*!
 * @function vImageEqualization_Planar8
 *
 * @abstract Equalizes the histogram of a Planar8 source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      Compute the histogram of the input image;
 *      Calculate normalized sum of histogram;
 *      For each pixel, do the following:
 *          dest[x] = equalized_histogram[src[x]];
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * @param src       A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest      A pointer to a vImage buffer that references the destination pixels
 *
 * @param flags     The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 * @/textblock</pre>
 *
 * @return The following error codes may be returned:
 * <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 * @/textblock</pre>
 */
vImage_Error 
vImageEqualization_Planar8( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageEqualization_PlanarF
 *
 * @abstract Equalizes the histogram of a PlanarF source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      Compute the histogram of the input image:
 *          For each pixel, do the following:
 *              val = histogram_entries * (src[x] - minVal) / (maxVal - minVal);
 *              i = clip val between 0 and histogram_entries-1
 *              histogram[i]++;
 *      Calculate normalized sum of histogram;
 *      For each pixel, do the following:
 *          val = histogram_entries * (src[x] - minVal) / (maxVal - minVal);
 *          i = clip val between 0 and histogram_entries-1
 *          dest[x] = equalized_histogram[i];
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param tempBuffer    A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer,
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself,
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information
 *                      on how to determine the minimum size that you must allocate.
 *
 * @param histogram_entries The number of histogram entries, or bins.
 *                      The histogram will be an array with histogram_entries elements.
 *
 * @param minVal        A minimum pixel value. Any pixel value less than this will be
 *                      clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the first histogram entry.
 *
 * @param maxVal        A maximum pixel value. Any pixel value greater than this will
 *                      be clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the last histogram entry.
 *
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageGetTempBufferSize    If this is passed, then the size of a temp
 *                                      buffer is returned from the left hand side
 *                                      of the function and no other work is done.
 *                                      An error may still be returned in this case.
 *                                      All vImage errors are < 0.  0 may also be
 *                                      returned, indicating that the temp buffer
 *                                      size is 0 for this set of parameters on
 *                                      this device with this operating system at
 *                                      this time of day.
 * @/textblock</pre>
 *
 * @return The following values may be returned:
 * <pre>@textblock
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or histogram pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 * @/textblock</pre>
 */
vImage_Error
vImageEqualization_PlanarF( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    void *tempBuffer, 
    unsigned int histogram_entries, 
    Pixel_F minVal,
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageEqualization_ARGB8888
 *
 * @abstract Equalizes the histogram of an ARGB8888 source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      Calculates histograms for each channel of the ARGB8888 source image;
 *      Calculate normalized sum of each histogram;
 *      For each pixel do the following:
 *          val = src[x];
 *          For each channel:
 *              val[ch] = equalized_histogram[ch][val[ch]];
 *              dest[x] = val;
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF.
 *
 * @param src       A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest      A pointer to a vImage buffer that references the destination pixels
 *
 * @param flags     The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Copy the alpha channel to the destination image unchanged
 * @/textblock</pre>
 *
 * @return The following error codes may be returned
 * <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 * @/textblock</pre>
 */
vImage_Error 
vImageEqualization_ARGB8888( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageEqualization_ARGBFFFF
 *
 * @abstract Equalizes the histogram of an ARGBFFFF source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      Compute the histogram of the input image:
 *          For each pixel, do the following:
 *              val = src[x];
 *              For each channel do:
 *                  i = histogram_entries * (val[ch] - minVal) / (maxVal - minVal);
 *                  i = clip i between 0 and histogram_entries-1
 *                  histogram[ch][i]++;
 *
 *      Calculate normalized sum of each histogram;
 *
 *      For each pixel, do the following:
 *          val = src[x];
 *          For each channel do:
 *              i = histogram_entries * (val[ch] - minVal) / (maxVal - minVal);
 *              i = clip i between 0 and histogram_entries-1
 *              val[ch] = equalized_histogram[ch][i];
 *          dest[x] = val;
 * @/textblock</pre>
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param tempBuffer    A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer,
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself,
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information
 *                      on how to determine the minimum size that you must allocate.
 *
 * @param histogram_entries The number of histogram entries, or bins, to be used in histograms for this operation
 *
 * @param minVal        A minimum pixel value. Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *                      This minimum value is applied to each of the four channels separately.
 *
 * @param maxVal        A maximum pixel value. Any pixel value greater than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry.
 *                      This maximum value is applied to each of the four channels separately.
 *
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageGetTempBufferSize    If this is passed, then the size of a temp
 *                                      buffer is returned from the left hand side
 *                                      of the function and no other work is done.
 *                                      An error may still be returned in this case.
 *                                      All vImage errors are < 0.  0 may also be
 *                                      returned, indicating that the temp buffer
 *                                      size is 0 for this set of parameters on
 *                                      this device with this operating system at
 *                                      this time of day. 
 *
 *          kvImageLeaveAlphaUnchanged    Copy the alpha channel to the destination image unchanged
 * @/textblock</pre>
 *
 * @return The following error codes may be returned
 * <pre>@textblock
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF. 
 */
vImage_Error
vImageEqualization_ARGBFFFF( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    void *tempBuffer, 
    unsigned int histogram_entries,  
    Pixel_F minVal, 
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*!
 * @functiongroup Histogram Specification
 * @discussion These functions cause the source image pixel distribution to conform to the
 *             desired histogram.
 */
    
/*!
 * @function vImageHistogramSpecification_Planar8
 *
 * @abstract Performs a histogram specification operation on a Planar8 source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      Compute the histogram of the input image;
 *      Calculate normalized sum of the input histogram and the desired_histogram
 *      Generate the inverse transform
 *      Transform final image using inv_hist as a LUT. For each pixel, do the following:
 *          dest[x] = inv_histogram[src[x]];
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * @param src               A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest              A pointer to a vImage buffer that references the destination pixels
 *
 * @param desired_histogram A pointer to the desired histogram for the transformed image.
 *                          The histogram should be an array with 256 elements.
 *
 * @param flags             The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 * @/textblock</pre>
 *
 * @return  The following error codes may occur:
 * <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src, dest or desired_histogram pointer is NULL.
 * @/textblock</pre>
 */
vImage_Error
vImageHistogramSpecification_Planar8( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    const vImagePixelCount *desired_histogram, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageHistogramSpecification_PlanarF
 *
 * @abstract Performs a histogram specification operation on a PlanarF source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      Compute the histogram of the input image:
 *          For each pixel, do the following:
 *              val = histogram_entries * (src[x] - minVal) / (maxVal - minVal);
 *              i = clip val between 0 and histogram_entries-1
 *              histogram[i]++;
 *      Calculate normalized sum of the input histogram and the desired_histogram
 *      Generate the inverse transform
 *      Transform final image using inverse transform as a LUT. For each pixel, do the following:
 *          val = histogram_entries * (src[x] - minVal) / (maxVal - minVal);
 *          i = clip val between 0 and histogram_entries-1
 *          dest[x] = inv_histogram[i];
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param tempBuffer    A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer,
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself,
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information
 *                      on how to determine the minimum size that you must allocate.
 *
 * @param desired_histogram A pointer the desired histogram for the transformed image.
 *                      The histogram should be an array with histogram_entries elements.
 *
 * @param histogram_entries The number of histogram entries, or bins, to be used in histograms for this operation
 *
 * @param minVal        A minimum pixel value. Any pixel value less than this will be
 *                      clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the first histogram entry.
 *
 * @param maxVal        A maximum pixel value. Any pixel value greater than this will
 *                      be clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the last histogram entry.
 *
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageGetTempBufferSize    If this is passed, then the size of a temp
 *                                      buffer is returned from the left hand side
 *                                      of the function and no other work is done.
 *                                      An error may still be returned in this case.
 *                                      All vImage errors are < 0.  0 may also be
 *                                      returned, indicating that the temp buffer
 *                                      size is 0 for this set of parameters on
 *                                      this device with this operating system at
 *                                      this time of day. 
 * @/textblock</pre>
 *
 * @return The following error codes may be returned:
 * <pre>@textblock
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src, dest or desired_histogram pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 * @/textblock</pre>
 */
vImage_Error 
vImageHistogramSpecification_PlanarF( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    void *tempBuffer, 
    const vImagePixelCount *desired_histogram, 
    unsigned int histogram_entries, 
    Pixel_F minVal, 
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*!
 * @function vImageHistogramSpecification_ARGB8888
 *
 * @abstract Performs a histogram specification operation on an ARGB8888 source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      For each channel:
 *          Compute the histogram of the input image;
 *          Calculate normalized sum of the input histogram and the desired_histogram
 *          Generate the inverse transform
 *          Transform final image using inv_hist as a LUT. For each pixel, do the following:
 *              dest[x] = inv_histogram[src[x]];
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF.
 *    The ordering of the desired_histogram must match the channel order of the image.
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param desired_histogram A pointer to an array of four histograms, one each for
 *                      alpha, red, green, and blue (in that order).
 *                      These are the desired histograms for the transformed image.
 *                      Each histogram should be an array with 256 elements.
 *                      This function does not allocate storage for the histograms. You must allocate
 *                      storage for each of the four histograms, create an array and populate it with
 *                      pointers to the histograms before calling the function. The contents of the 
 *                      histograms are generally obtained from vImageHistogramCalculation_<fmt> from
 *                      another image, but need not be so.
 *
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Copy the alpha channel to the destination image unchanged
 * @/textblock</pre>
 *
 * @return The following values may be returned:
 * <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src, dest or any of the desired_histogram pointers is NULL.
 * @/textblock</pre>
 */
vImage_Error 
vImageHistogramSpecification_ARGB8888( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    const vImagePixelCount *desired_histogram[4], 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*!
 * @function vImageHistogramSpecification_ARGBFFFF
 *
 * @abstract Performs a histogram specification operation on an ARGBFFFF source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      For each channel do:
 *          Compute the histogram of the input image:
 *              For each pixel, do the following:
 *                  val = histogram_entries * (src[x] - minVal) / (maxVal - minVal);
 *                  i = clip val between 0 and histogram_entries-1
 *                  histogram[ch][i]++;
 *          Calculate normalized sum of the input histogram and the desired_histogram
 *          Generate the inverse transform
 *          Transform final image using inverse transform as a LUT. For each pixel, do the following:
 *              val = histogram_entries * (src[ch][x] - minVal) / (maxVal - minVal);
 *              i = clip val between 0 and histogram_entries-1
 *              dest[ch][x] = inv_histogram[ch][i];
 * @/textblock </pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF.
 *    The ordering of the desired_histogram must match the channel order of the image.
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param tempBuffer    A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer,
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself, 
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information 
 *                      on how to determine the minimum size that you must allocate.
 *
 * @param desired_histogram A pointer to an array of four histograms, one each for
 *                      alpha, red, green, and blue (in that order).                
 *                      These are the desired histograms for the transformed image.
 *                      Each histogram should be an array with histogram_entries elements..
 *                      This function does not allocate storage for the histograms. You must allocate
 *                      storage for each of the four histograms, create an array and populate it with
 *                      pointers to the histograms before calling the function. The contents of the
 *                      histograms are generally obtained from vImageHistogramCalculation_<fmt> from
 *                      another image, but need not be so.
 *
 * @param histogram_entries The number of histogram entries, or bins, to be used in histograms for this operation
 *
 * @param minVal        A minimum pixel value. Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *                      This minimum value is applied to each of the four channels separately.
 *
 * @param maxVal        A maximum pixel value. Any pixel value greater than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry. 
 *                      This maximum value is applied to each of the four channels separately.
 *
 * @param flags The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageGetTempBufferSize    If this is passed, then the size of a temp
 *                                      buffer is returned from the left hand side
 *                                      of the function and no other work is done.
 *                                      An error may still be returned in this case.
 *                                      All vImage errors are < 0.  0 may also be
 *                                      returned, indicating that the temp buffer
 *                                      size is 0 for this set of parameters on
 *                                      this device with this operating system at
 *                                      this time of day. 
 *
 *          kvImageLeaveAlphaUnchanged  Copy the alpha channel to the destination image unchanged
 * @/textblock</pre>
 *
 * @return  The following error codes may be returned:
 * <pre>@textblock
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src, dest or any of desired_histogram pointers is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 * @/textblock</pre>
 */
vImage_Error
vImageHistogramSpecification_ARGBFFFF( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    void *tempBuffer, 
    const vImagePixelCount *desired_histogram[4], 
    unsigned int histogram_entries, 
    Pixel_F minVal, 
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @functiongroup Contrast Stretch
 * @discussion Some images do not make enough use of the light and dark ends of the spectrum.
 *             vImageContrastStretch functions widen the pixel value distribution to use a wider
 *             range of values.
 */

/*!
 * @function vImageContrastStretch_Planar8
 *
 * @abstract Stretches the contrast of a Planar8 source image.
 * @discussion This function performs the following operation:
 *   <pre>@textblock
 *      Compute the histogram of the input image;
 *      Generate LookUp table based on the histogram
 *      Transform final image using the LUT. For each pixel, do the following:
 *          dest[x] = LUT[src[x]];
 *   @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * vImageEndsInContrastStretch_Planar8 or vImageTableLookUp_Planar8 may be used instead when more control
 * over the stretch is desired.
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param flags         The following flags are allowed:
 *   <pre>@textblock
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 *   @/textblock</pre>
 *
 * @return The following error codes may be returned:
 *   <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *   @/textblock</pre>
 */
vImage_Error 
vImageContrastStretch_Planar8( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageContrastStretch_PlanarF
 *
 * @abstract Stretches the contrast of a PlanarF source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      Find minimum and maximum value of the input image: loVal, hiVal;
 *      scale_factor = ( maxVal - minVal ) / (float) ( hiVal - loVal );
 *      Transfer the image. For each pixel do:
 *          dest[x] = (src[x] - loVal) * scale_factor + minVal;
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * vImageEndsInContrastStretch_PlanarF or vImageInterpolatedLookupTable_PlanarF may be used instead when more control
 * over the stretch is desired.
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param tempBuffer    A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer,
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself, 
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information 
 *                      on how to determine the minimum size that you must allocate.
 *
 * @param histogram_entries The number of histogram entries, or bins to be used in histograms for this operation
 *
 * @param minVal        A minimum pixel value. Any pixel value less than this will be
 *                      clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the first histogram entry.
 *
 * @param maxVal        A maximum pixel value. Any pixel value greater than this will
 *                      be clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the last histogram entry.
 *
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageGetTempBufferSize    If this is passed, then the size of a temp
 *                                      buffer is returned from the left hand side
 *                                      of the function and no other work is done.
 *                                      An error may still be returned in this case.
 *                                      All vImage errors are < 0.  0 may also be
 *                                      returned, indicating that the temp buffer
 *                                      size is 0 for this set of parameters on
 *                                      this device with this operating system at
 *                                      this time of day. 
 * @/textblock</pre>
 *
 * @return The following error codes may be returned
 * <pre>@textblock
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 * @/textblock</pre>
 */
vImage_Error 
vImageContrastStretch_PlanarF( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    void *tempBuffer, 
    unsigned int histogram_entries, 
    Pixel_F minVal, 
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageContrastStretch_ARGB8888
 * @abstract Stretches the contrast of an ARGB8888 source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      For each channel:
 *          Compute the histogram of the input image;
 *          Generate LookUp table based on the histogram
 *          Transform final image using the LUT. For each pixel, do the following:
 *              dest[x] = LUT[src[x]];
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF.
 *
 * vImageEndsInContrastStretch_ARGB8888 or vImageTableLookUp_ARGB8888 may be used instead when more control
 * over the stretch is desired.
 *
 * @param src       A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest      A pointer to a vImage buffer that references the destination pixels
 *
 * @param flags     The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Copy the alpha channel to the destination image unchanged
 * @/textblock</pre>
 *
 * @return The following error codes may be returned:
 * <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 * @/textblock</pre>
 */
vImage_Error 
vImageContrastStretch_ARGB8888( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageContrastStretch_ARGBFFFF
 *
 * @abstract Stretches the contrast of  an ARGBFFFF source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *        For each channel:
 *            Find minimum and maximum value of the input image: loVal, hiVal;
 *            scale_factor = ( maxVal - minVal ) / (float) ( hiVal - loVal );
 *            Transfer the image. For each pixel do:
 *                dest[x] = (src[x] - loVal) * scale_factor + minVal;
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF.
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param tempBuffer    A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer,
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself, 
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information 
 *                      on how to determine the minimum size that you must allocate.
 *
 * @param histogram_entries The number of histogram entries, or bins, to be used in histograms for this operation
 *
 * @param minVal        A minimum pixel value. Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *                      This minimum value is applied to each of the four channels separately.
 *
 * @param maxVal        A maximum pixel value. Any pixel value greater than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry. 
 *                      This maximum value is applied to each of the four channels separately.
 *
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageGetTempBufferSize    If this is passed, then the size of a temp
 *                                      buffer is returned from the left hand side
 *                                      of the function and no other work is done.
 *                                      An error may still be returned in this case.
 *                                      All vImage errors are < 0.  0 may also be
 *                                      returned, indicating that the temp buffer
 *                                      size is 0 for this set of parameters on
 *                                      this device with this operating system at
 *                                      this time of day. 
 *
 *          kvImageLeaveAlphaUnchanged  Copy the alpha channel to the destination image unchanged
 * @/textblock</pre>
 *
 * @return The following error codes may be returned:
 * <pre>@textblock
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 * @/textblock<pre>
 */
vImage_Error 
vImageContrastStretch_ARGBFFFF( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    void *tempBuffer, 
    unsigned int histogram_entries, 
    Pixel_F minVal, 
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*!
 *  @functiongroup Ends-In Contrast Stretch
 *  @discussion Readjust the image pixel value distribution to use only some of the range of available intensities.
 */

/*!
 * @function vImageEndsInContrastStretch_Planar8
 *
 * @abstract Performs an ends-in contrast stretch operation on a Planar8 source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      Compute the histogram of the input image;
 *      Generate LookUp table based on the histogram and percentage parameters
 *      Transform final image using the LookUp table. For each pixel, do the following:
 *          dest[x] = LUT[src[x]];
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param percent_low   A percentage value.
 *                      The number of pixels that map to the lowest end of the histogram of the
 *                      transformed image should represent this percentage of the total pixels.
 *    
 * @param percent_high  A percentage value.
 *                      The number of pixels that map to the highest end of the histogram of the 
 *                      transformed image should represent this percentage of the total pixels.
 *
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 * @/textblock</pre>
 *
 * @return The following error codes may be returned:
 * <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *   kvImageInvalidParameter         percent_low + percent_high is greater than 100.
 * @/textblock</pre>
 */
vImage_Error 
vImageEndsInContrastStretch_Planar8( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    unsigned int percent_low, 
    unsigned int percent_high, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageEndsInContrastStretch_PlanarF
 *
 * @abstract Performs an ends-in contrast stretch operation on a PlanarF source image.
 * @discussion 
 * <pre>@textblock
 *      Compute the histogram of the input image;
 *      Generate LookUp table based on the histogram and percentage parameters
 *      Transform final image using the LookUp table. For each pixel, do the following:
 *          val = histogram_entries * (src[x] - minVal) / ( maxVal - minVal );
 *          i = clip val between 0 and histogram_entries-1
 *          dest[x] = LUT[i];
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param tempBuffer    A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer,
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself, 
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information 
 *                      on how to determine the minimum size that you must allocate.
 *
 * @param percent_low   A percentage value.
 *                      The number of pixels that map to the lowest end of the histogram of the
 *                      transformed image should represent this percentage of the total pixels.
 *    
 * @param percent_high  A percentage value.
 *                      The number of pixels that map to the highest end of the histogram of the 
 *                      transformed image should represent this percentage of the total pixels.
 *
 * @param histogram_entries The number of histogram entries, or bins, to be used in histograms for this operation
 *
 * @param minVal        A minimum pixel value, the low end of the histogram.
 *                      Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *
 * @param maxVal        A maximum pixel value, the high end of the histogram.
 *                      Any pixel value greater than this will be clipped to this value 
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry.
 *
 * @param    flags      The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageGetTempBufferSize    If this is passed, then the size of a temp
 *                                      buffer is returned from the left hand side
 *                                      of the function and no other work is done.
 *                                      An error may still be returned in this case.
 *                                      All vImage errors are < 0.  0 may also be
 *                                      returned, indicating that the temp buffer
 *                                      size is 0 for this set of parameters on
 *                                      this device with this operating system at
 *                                      this time of day. 
 * @/textblock</pre>
 *
 * @return The following error codes may be returned:
 * <pre>@textblock
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal, histogram_entries is 0 or
 *                                   percent_low + percent_high is greater than 100.
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 * @/textblock </pre>
 */
vImage_Error
vImageEndsInContrastStretch_PlanarF( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    void *tempBuffer, 
    unsigned int percent_low, 
    unsigned int percent_high, 
    unsigned int histogram_entries, 
    Pixel_F minVal, 
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*!
 * @function vImageEndsInContrastStretch_ARGB8888
 *
 * @abstract Performs an ends-in contrast stretch operation on an ARGB8888 source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      For each channel:
 *          Compute the histogram of the input image;
 *          Generate LookUp table based on the histogram and percentage parameters
 *          Transform final image using the LookUp table. For each pixel, do the following:
 *              dest[x] = LUT[src[x]];
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF.
 *    The ordering of the percent_low and percent_high parameters match the order of the channels.
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param percent_low   An array of four percentage values, one each for alpha, red, green, and blue.
 *                      The number of pixels that map to the lowest end of the histogram of the
 *                      transformed image should represent this percentage of the total pixels.
 *    
 * @param percent_high  An array of four percentage values, one each for alpha, red, green, and blue.
 *                      The number of pixels that map to the highest end of the histogram of the 
 *                      transformed image should represent this percentage of the total pixels.
 *
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Copy the alpha channel to the destination image unchanged
 * @/textblock</pre>
 *
 * @return The following error codes may be returned:
 * <pre>@textblock
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src, dest, percent_low or percent_high pointer is NULL.
 *   kvImageInvalidParameter         Some of percent_low[i]+percent_high[i] is greater than 100.
 * @/textblock</pre>
 */
vImage_Error 
vImageEndsInContrastStretch_ARGB8888( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    const unsigned int percent_low[4], 
    const unsigned int percent_high[4], 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*!
 * @function vImageEndsInContrastStretch_ARGBFFFF
 *
 * @abstract Performs a histogram specification operation on an ARGBFFFF source image.
 * @discussion This function performs the following operation:
 * <pre>@textblock
 *      For each channel do:
 *          Compute the histogram of the input image;
 *          Generate LookUp table based on the histogram and percentage parameters
 *          Transform final image using the LookUp table. For each pixel, do the following:
 *              val = histogram_entries * (src[x] - minVal) / ( maxVal - minVal );
 *              i = clip val between 0 and histogram_entries-1
 *              dest[x] = LUT[i];
 * @/textblock</pre>
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF.
 *    The ordering of the percent_low and percent_high parameters match the order of the channels.
 *
 * @param src           A pointer to a vImage_Buffer that references the source pixels
 *
 * @param dest          A pointer to a vImage buffer that references the destination pixels
 *
 * @param tempBuffer    A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer,
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself, 
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information 
 *                      on how to determine the minimum size that you must allocate.
 *
 * @param percent_low   An array of four percentage values, one each for alpha, red, green, and blue.
 *                      The number of pixels that map to the lowest end of the histogram of the
 *                      transformed image should represent this percentage of the total pixels.
 *    
 * @param percent_high  An array of four percentage values, one each for alpha, red, green, and blue.
 *                      The number of pixels that map to the highest end of the histogram of the 
 *                      transformed image should represent this percentage of the total pixels.
 *
 * @param histogram_entries The number of histogram entries, or bins, to be used in histograms for this operation
 *
 * @param minVal        A minimum pixel value. Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *                      This minimum value is applied to each of the four channels separately.
 *
 * @param maxVal        A maximum pixel value. Any pixel value greater than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry. 
 *                      This maximum value is applied to each of the four channels separately.
 *
 * @param flags         The following flags are allowed:
 * <pre>@textblock
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageGetTempBufferSize    If this is passed, then the size of a temp
 *                                      buffer is returned from the left hand side
 *                                      of the function and no other work is done.
 *                                      An error may still be returned in this case.
 *                                      All vImage errors are < 0.  0 may also be
 *                                      returned, indicating that the temp buffer
 *                                      size is 0 for this set of parameters on
 *                                      this device with this operating system at
 *                                      this time of day. 
 *
 *          kvImageLeaveAlphaUnchanged  Copy the alpha channel to the destination image unchanged
 * @/textblock</pre>
 * @return The following error codes may be returned:
 * <pre>@textblock
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal, histogram_entries is 0 or 
 *                                   some of percent_low[i]+percent_high[i] is greater than 100.
 *   kvImageNullPointerArgument      src, dest, percent_low or percent_high pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 * @/textblock</pre>
 */
vImage_Error 
vImageEndsInContrastStretch_ARGBFFFF( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    void *tempBuffer, 
    const unsigned int percent_low[4], 
    const unsigned int percent_high[4], 
    unsigned int histogram_entries, 
    Pixel_F minVal, 
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2,4,5) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


#ifdef __cplusplus
}
#endif

#endif

