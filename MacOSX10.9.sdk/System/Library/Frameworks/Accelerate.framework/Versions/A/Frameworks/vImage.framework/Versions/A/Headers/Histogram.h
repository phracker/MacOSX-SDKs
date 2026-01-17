/*
 *  Histogram.h
 *  vImage_Framework
 *
 *  Copyright (c) 2003 Apple Computer. All rights reserved.
 *
 */

#ifndef VIMAGE_HISTOGRAM_H
#define VIMAGE_HISTOGRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vImage/vImage_Types.h>

/*
 * vImageHistogramCalculation_Planar8
 *
 * Calculates a histogram for a Planar8 image.
 *
 *      For each pixel, do the following:
 *          histogram[src[x]]++;
 *
 *
 * Operands:
 * ---------
 *    src            A pointer to a vImage_Buffer that references the source pixels
 *
 *    histogram      A pointer to a histogram. On return, this array will 
 *                   contain the histogram for the source image.
 *                   The histogram will be an array with 256 elements.
 *
 *    flags          The following flags are allowed:
 *
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageNullPointerArgument      src or histogram pointer is NULL.
 *
 * This routine will not work in place
 *
 */
vImage_Error
vImageHistogramCalculation_Planar8( 
    const vImage_Buffer *src, 
    vImagePixelCount *histogram, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * vImageHistogramCalculation_PlanarF
 *
 * Calculates a histogram for a PlanarF image.
 *
 *      For each pixel, do the following:
 *          val = histogram_entries * (src[x] - minVal) / (maxVal - minVal);
 *          i = clip val between 0 and histogram_entries-1
 *          histogram[i]++;
 *
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    histogram         A pointer to a histogram. On return, this array will
 *                      contain the histogram for the source image.
 *                      The histogram will have histogram_entries elements.
 *
 *    histogram_entries The number of histogram entries, or “bins.”
 *                      The histogram will be an array with histogram_entries elements.
 *
 *    minVal            A minimum pixel value. Any pixel value less than this will be
 *                      clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the first histogram entry.
 *
 *    maxVal            A maximum pixel value. Any pixel value greater than this will
 *                      be clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the last histogram entry.
 *
 *    flags             The following flags are allowed:
 *
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or histogram pointer is NULL.
 *
 * This routine will not work in place
 *
 */
vImage_Error 
vImageHistogramCalculation_PlanarF( 
    const vImage_Buffer *src, 
    vImagePixelCount *histogram, 
    unsigned int histogram_entries, 
    Pixel_F minVal, 
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * vImageHistogramCalculation_ARGB8888
 *
 * Calculates histograms for each channel of an ARGB8888 image.
 *
 *      For each pixel and channel, do the following:
 *          val = src[x];
 *          histogram[ch][val[ch]]++;
 *
 *
 * Operands:
 * ---------
 *    src            A pointer to a vImage_Buffer that references the source pixels
 *
 *    histogram      A pointer to a histograms, one each for alpha, red, green, and blue (in that order). 
 *                   On return, this array will contain the four histograms for the corresponding channels.
 *                   Each of the four histograms will be an array with 256 elements.
 *
 *    flags          The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Do not calculate the histogram for the alpha channel
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageNullPointerArgument      src or histogram pointer is NULL.
 *
 * This routine will not work in place
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images) 
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF. 
 *    The ordering of the histogram will match the channel order of the image.
 */
vImage_Error 
vImageHistogramCalculation_ARGB8888( 
    const vImage_Buffer *src, 
    vImagePixelCount *histogram[4], 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * vImageHistogramCalculation_ARGBFFFF
 *
 * Calculates histograms for each channel of an ARGBFFFF image.
 *
 *      For each pixel, do the following:
 *          val = src[x];
 *          For each channel do:
 *              i = histogram_entries * (val[ch] - minVal) / (maxVal - minVal);
 *              i = clip i between 0 and histogram_entries-1
 *              histogram[ch][i]++;
 *
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    histogram         A pointer to an array of four histograms,
 *                      one each for alpha, red, green, and blue (in that order).
 *                      On return, this array will contain the four histograms for the corresponding channels.
 *                      Each of the four histograms will be an array with histogram_entries elements.
 *
 *    histogram_entries The number of histogram entries, or “bins.” Each of the four
 *                      calculated histograms will be an array with histogram_entries elements.
 *
 *    minVal            A minimum pixel value. Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *                      This minimum value is applied to each of the four channels separately.
 *
 *    maxVal            A maximum pixel value. Any pixel value greater than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry.
 *                      This maximum value is applied to each of the four channels separately.
 *
 *    flags             The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Do not calculate the histogram for the alpha channel
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or any of the histogram pointers is NULL.
 *
 * This routine will not work in place
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images) 
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF. 
 *    The ordering of the histogram will match the channel order of the image.
 */
vImage_Error 
vImageHistogramCalculation_ARGBFFFF( 
    const vImage_Buffer *src, 
    vImagePixelCount *histogram[4], 
    unsigned int histogram_entries, 
    Pixel_F minVal, 
    Pixel_F maxVal, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );




/*
 * vImageEqualization_Planar8
 *
 * Equalizes the histogram of a Planar8 source image.
 *
 *      Compute the histogram of the input image;
 *      Calculate normalized sum of histogram;
 *      For each pixel, do the following:
 *          dest[x] = equalized_histogram[src[x]];
 *
 *
 * Operands:
 * ---------
 *    src            A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest           A pointer to a vImage buffer that references the destination pixels
 *
 *    flags          The following flags are allowed:
 *
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 */
vImage_Error 
vImageEqualization_Planar8( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * vImageEqualization_PlanarF
 *
 * Equalizes the histogram of a PlanarF source image.
 *
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
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    tempBuffer        A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer, 
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself,
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information
 *                      on how to determine the minimum size that you must allocate.
 *
 *    histogram_entries The number of histogram entries, or “bins.”
 *                      The histogram will be an array with histogram_entries elements.
 *
 *    minVal            A minimum pixel value. Any pixel value less than this will be
 *                      clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the first histogram entry.
 *
 *    maxVal            A maximum pixel value. Any pixel value greater than this will
 *                      be clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the last histogram entry.
 *
 *    flags             The following flags are allowed:
 *
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
 * Return Value:
 * -------------
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or histogram pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
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

/*
 * vImageEqualization_ARGB8888
 *
 * Equalizes the histogram of an ARGB8888 source image.
 *
 *      Calculates histograms for each channel of the ARGB8888 source image;
 *      Calculate normalized sum of each histogram;
 *      For each pixel do the following:
 *          val = src[x];
 *          For each channel:
 *              val[ch] = equalized_histogram[ch][val[ch]];
 *              dest[x] = val;
 *
 * Operands:
 * ---------
 *    src            A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest           A pointer to a vImage buffer that references the destination pixels
 *
 *    flags          The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Copy the alpha channel to the destination image unchanged
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF. 
 */
vImage_Error 
vImageEqualization_ARGB8888( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * vImageEqualization_ARGBFFFF
 *
 * Equalizes the histogram of an ARGBFFFF source image.
 *
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
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    tempBuffer        A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer, 
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself,
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information
 *                      on how to determine the minimum size that you must allocate.
 *
 *    histogram_entries The number of histogram entries, or “bins,” to be used in histograms for this operation
 *
 *    minVal            A minimum pixel value. Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *                      This minimum value is applied to each of the four channels separately.
 *
 *    maxVal            A maximum pixel value. Any pixel value greater than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry.
 *                      This maximum value is applied to each of the four channels separately.
 *
 *    flags             The following flags are allowed:
 *
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
 *
 * Return Value:
 * -------------
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
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




/*
 * vImageHistogramSpecification_Planar8
 *
 * Performs a histogram specification operation on a Planar8 source image.
 *
 *      Compute the histogram of the input image;
 *      Calculate normalized sum of the input histogram and the desired_histogram
 *      Generate the inverse transform
 *      Transform final image using inv_hist as a LUT. For each pixel, do the following:
 *          dest[x] = inv_histogram[src[x]];
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    desired_histogram A pointer to the desired histogram for the transformed image.
 *                      The histogram should be an array with 256 elements.
 *
 *    flags             The following flags are allowed:
 *
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src, dest or desired_histogram pointer is NULL.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 */
vImage_Error
vImageHistogramSpecification_Planar8( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    const vImagePixelCount *desired_histogram, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * vImageHistogramSpecification_PlanarF
 *
 * Performs a histogram specification operation on a PlanarF source image.
 *
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
 *
 *
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    tempBuffer        A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer, 
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself,
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information
 *                      on how to determine the minimum size that you must allocate.
 *
 *    desired_histogram A pointer the desired histogram for the transformed image.
 *                      The histogram should be an array with histogram_entries elements.
 *
 *    histogram_entries The number of histogram entries, or “bins,” to be used in histograms for this operation
 *
 *    minVal            A minimum pixel value. Any pixel value less than this will be
 *                      clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the first histogram entry.
 *
 *    maxVal            A maximum pixel value. Any pixel value greater than this will
 *                      be clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the last histogram entry.
 *
 *    flags             The following flags are allowed:
 *
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
 * Return Value:
 * -------------
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src, dest or desired_histogram pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
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


/*
 * vImageHistogramSpecification_ARGB8888
 *
 * Performs a histogram specification operation on an ARGB8888 source image.
 *
 *      For each channel:
 *          Compute the histogram of the input image;
 *          Calculate normalized sum of the input histogram and the desired_histogram
 *          Generate the inverse transform
 *          Transform final image using inv_hist as a LUT. For each pixel, do the following:
 *              dest[x] = inv_histogram[src[x]];
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    desired_histogram A pointer to an array of four histograms, one each for
 *                      alpha, red, green, and blue (in that order).
 *                      These are the desired histograms for the transformed image.
 *                      Each histogram should be an array with 256 elements.
 *
 *    flags             The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Copy the alpha channel to the destination image unchanged
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src, dest or any of the desired_histogram pointers is NULL.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF. 
 *    The ordering of the desired_histogram must match the channel order of the image.
 */
vImage_Error 
vImageHistogramSpecification_ARGB8888( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    const vImagePixelCount *desired_histogram[4], 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*
 * vImageHistogramSpecification_ARGBFFFF
 *
 * Performs a histogram specification operation on an ARGBFFFF source image.
 *
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
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    tempBuffer        A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer, 
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself, 
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information 
 *                      on how to determine the minimum size that you must allocate.
 *
 *    desired_histogram A pointer to an array of four histograms, one each for
 *                      alpha, red, green, and blue (in that order).                
 *                      These are the desired histograms for the transformed image.
 *                      Each histogram should be an array with histogram_entries elements..
 *
 *    histogram_entries The number of histogram entries, or “bins,” to be used in histograms for this operation
 *
 *    minVal            A minimum pixel value. Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *                      This minimum value is applied to each of the four channels separately.
 *
 *    maxVal            A maximum pixel value. Any pixel value greater than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry. 
 *                      This maximum value is applied to each of the four channels separately.
 *
 *    flags             The following flags are allowed:
 *
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
 *
 * Return Value:
 * -------------
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src, dest or any of desired_histogram pointers is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF. 
 *    The ordering of the desired_histogram must match the channel order of the image.
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



/*
 * vImageContrastStretch_Planar8
 *
 * Stretches the contrast of a Planar8 source image.
 *
 *      Compute the histogram of the input image;
 *      Generate LookUp table based on the histogram
 *      Transform final image using the LUT. For each pixel, do the following:
 *          dest[x] = LUT[src[x]];
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    flags             The following flags are allowed:
 *
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * vImageEndsInContrastStretch_Planar8 or vImageTableLookUp_Planar8 may be used instead when more control
 * over the stretch is desired.
 */
vImage_Error 
vImageContrastStretch_Planar8( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * vImageContrastStretch_PlanarF
 *
 * Stretches the contrast of a PlanarF source image.
 *
 *      Find minimum and maximum value of the input image: loVal, hiVal;
 *      scale_factor = ( maxVal - minVal ) / (float) ( hiVal - loVal );
 *      Transfer the image. For each pixel do:
 *          dest[x] = (src[x] - loVal) * scale_factor + minVal;
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    tempBuffer        A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer, 
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself, 
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information 
 *                      on how to determine the minimum size that you must allocate.
 *
 *    histogram_entries The number of histogram entries, or “bins,” to be used in histograms for this operation
 *
 *    minVal            A minimum pixel value. Any pixel value less than this will be
 *                      clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the first histogram entry.
 *
 *    maxVal            A maximum pixel value. Any pixel value greater than this will
 *                      be clipped to this value (for the purposes of histogram calculation),
 *                      and assigned to the last histogram entry.
 *
 *    flags             The following flags are allowed:
 *
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
 * Return Value:
 * -------------
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * vImageEndsInContrastStretch_PlanarF or vImageInterpolatedLookupTable_PlanarF may be used instead when more control
 * over the stretch is desired.
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

/*
 * vImageContrastStretch_ARGB8888
 *
 * Stretches the contrast of an ARGB8888 source image.
 *
 *      For each channel:
 *          Compute the histogram of the input image;
 *          Generate LookUp table based on the histogram
 *          Transform final image using the LUT. For each pixel, do the following:
 *              dest[x] = LUT[src[x]];
 *
 * Operands:
 * ---------
 *    src           A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest          A pointer to a vImage buffer that references the destination pixels
 *
 *    flags         The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Copy the alpha channel to the destination image unchanged
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
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
 */
vImage_Error 
vImageContrastStretch_ARGB8888( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * vImageContrastStretch_ARGBFFFF
 *
 * Stretches the contrast of  an ARGBFFFF source image.
 *
 *        For each channel:
 *            Find minimum and maximum value of the input image: loVal, hiVal;
 *            scale_factor = ( maxVal - minVal ) / (float) ( hiVal - loVal );
 *            Transfer the image. For each pixel do:
 *                dest[x] = (src[x] - loVal) * scale_factor + minVal;
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    tempBuffer        A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer, 
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself, 
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information 
 *                      on how to determine the minimum size that you must allocate.
 *
 *    histogram_entries The number of histogram entries, or “bins,” to be used in histograms for this operation
 *
 *    minVal            A minimum pixel value. Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *                      This minimum value is applied to each of the four channels separately.
 *
 *    maxVal            A maximum pixel value. Any pixel value greater than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry. 
 *                      This maximum value is applied to each of the four channels separately.
 *
 *    flags             The following flags are allowed:
 *
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
 *
 * Return Value:
 * -------------
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal or histogram_entries is 0 
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF. 
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




/*
 * vImageEndsInContrastStretch_Planar8
 *
 * Performs an ends-in contrast stretch operation on a Planar8 source image.
 *
 *      Compute the histogram of the input image;
 *      Generate LookUp table based on the histogram and percentage parameters
 *      Transform final image using the LookUp table. For each pixel, do the following:
 *          dest[x] = LUT[src[x]];
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    percent_low       A percentage value.
 *                      The number of pixels that map to the lowest end of the histogram of the
 *                      transformed image should represent this percentage of the total pixels.
 *    
 *    percent_high      A percentage value.
 *                      The number of pixels that map to the highest end of the histogram of the 
 *                      transformed image should represent this percentage of the total pixels.
 *
 *    flags             The following flags are allowed:
 *
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *   kvImageInvalidParameter         percent_low + percent_high is greater than 100.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 */
vImage_Error 
vImageEndsInContrastStretch_Planar8( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    unsigned int percent_low, 
    unsigned int percent_high, 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );

/*
 * vImageEndsInContrastStretch_PlanarF
 *
 * Performs an ends-in contrast stretch operation on a PlanarF source image.
 *
 *      Compute the histogram of the input image;
 *      Generate LookUp table based on the histogram and percentage parameters
 *      Transform final image using the LookUp table. For each pixel, do the following:
 *          val = histogram_entries * (src[x] - minVal) / ( maxVal - minVal );
 *          i = clip val between 0 and histogram_entries-1
 *          dest[x] = LUT[i];
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    tempBuffer        A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer, 
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself, 
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information 
 *                      on how to determine the minimum size that you must allocate.
 *
 *    percent_low       A percentage value.
 *                      The number of pixels that map to the lowest end of the histogram of the
 *                      transformed image should represent this percentage of the total pixels.
 *    
 *    percent_high      A percentage value.
 *                      The number of pixels that map to the highest end of the histogram of the 
 *                      transformed image should represent this percentage of the total pixels.
 *
 *    histogram_entries The number of histogram entries, or “bins,” to be used in histograms for this operation
 *
 *    minVal            A minimum pixel value, the low end of the histogram.
 *                      Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *
 *    maxVal            A maximum pixel value, the high end of the histogram.
 *                      Any pixel value greater than this will be clipped to this value 
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry.
 *
 *    flags             The following flags are allowed:
 *
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
 * Return Value:
 * -------------
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal, histogram_entries is 0 or
 *                                   percent_low + percent_high is greater than 100.
 *   kvImageNullPointerArgument      src or dest pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
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

/*
 * vImageEndsInContrastStretch_ARGB8888
 *
 * Performs an ends-in contrast stretch operation on an ARGB8888 source image.
 *
 *      For each channel:
 *          Compute the histogram of the input image;
 *          Generate LookUp table based on the histogram and percentage parameters
 *          Transform final image using the LookUp table. For each pixel, do the following:
 *              dest[x] = LUT[src[x]];
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    percent_low       An array of four percentage values, one each for alpha, red, green, and blue.
 *                      The number of pixels that map to the lowest end of the histogram of the
 *                      transformed image should represent this percentage of the total pixels.
 *    
 *    percent_high      An array of four percentage values, one each for alpha, red, green, and blue.
 *                      The number of pixels that map to the highest end of the histogram of the 
 *                      transformed image should represent this percentage of the total pixels.
 *
 *    flags             The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageLeaveAlphaUnchanged  Copy the alpha channel to the destination image unchanged
 *
 * Return Value:
 * -------------
 *   kvImageNoError                  Success!
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *   kvImageNullPointerArgument      src, dest, percent_low or percent_high pointer is NULL.
 *   kvImageInvalidParameter         Some of percent_low[i]+percent_high[i] is greater than 100.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF. 
 *    The ordering of the percent_low and percent_high parameters match the order of the channels.
 */
vImage_Error 
vImageEndsInContrastStretch_ARGB8888( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    const unsigned int percent_low[4], 
    const unsigned int percent_high[4], 
    vImage_Flags flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_3, __IPHONE_5_0 );


/*
 * vImageEndsInContrastStretch_ARGBFFFF
 *
 * Performs a histogram specification operation on an ARGBFFFF source image.
 *
 *      For each channel do:
 *          Compute the histogram of the input image;
 *          Generate LookUp table based on the histogram and percentage parameters
 *          Transform final image using the LookUp table. For each pixel, do the following:
 *              val = histogram_entries * (src[x] - minVal) / ( maxVal - minVal );
 *              i = clip val between 0 and histogram_entries-1
 *              dest[x] = LUT[i];
 *
 * Operands:
 * ---------
 *    src               A pointer to a vImage_Buffer that references the source pixels
 *
 *    dest              A pointer to a vImage buffer that references the destination pixels
 *
 *    tempBuffer        A pointer to a temporary buffer. If you pass NULL, the function allocates the buffer, 
 *                      then deallocates it before returning. Alternatively, you can allocate the buffer yourself, 
 *                      in which case you are responsible for deallocating it when you is no longer need it.
 *                      If you want to allocate the buffer yourself, see the documentation for information 
 *                      on how to determine the minimum size that you must allocate.
 *
 *    percent_low       An array of four percentage values, one each for alpha, red, green, and blue.
 *                      The number of pixels that map to the lowest end of the histogram of the
 *                      transformed image should represent this percentage of the total pixels.
 *    
 *    percent_high      An array of four percentage values, one each for alpha, red, green, and blue.
 *                      The number of pixels that map to the highest end of the histogram of the 
 *                      transformed image should represent this percentage of the total pixels.
 *
 *    histogram_entries The number of histogram entries, or “bins,” to be used in histograms for this operation
 *
 *    minVal            A minimum pixel value. Any pixel value less than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the first histogram entry.
 *                      This minimum value is applied to each of the four channels separately.
 *
 *    maxVal            A maximum pixel value. Any pixel value greater than this will be clipped to this value
 *                      (for the purposes of histogram calculation), and assigned to the last histogram entry. 
 *                      This maximum value is applied to each of the four channels separately.
 *
 *    flags             The following flags are allowed:
 *
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
 *
 * Return Value:
 * -------------
 *   >= 0                            Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *   kvImageNoError                  Success!
 *   kvImageInvalidParameter         maxVal is less than minVal, histogram_entries is 0 or 
 *                                   some of percent_low[i]+percent_high[i] is greater than 100.
 *   kvImageNullPointerArgument      src, dest, percent_low or percent_high pointer is NULL.
 *   kvImageBufferSizeMismatch       Sizes of the src and dest images do not match.
 *   kvImageMemoryAllocationError    Can not allocate memory for the buffer.
 *
 * This routine will work in place provided that src.data == dest.data and src.rowBytes >= dest.rowBytes.
 *    if src.rowBytes > dest.rowBytes and src.data == dest.data, the function will only work if you pass
 *    kvImageDoNotTile
 *
 * All four channel histogram functions (i.e. those that support ARGB8888 or ARGBFFFF images)
 *    work equally well on four channel images with other channel orderings such as RGBA8888 or BGRAFFFF. 
 *    The ordering of the percent_low and percent_high parameters match the order of the channels.
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

/*
 * It is recommended that you use the kvImageGetTempBufferSize flag 
 * with the appropriate function, instead of using this API 
 * Simply pass the kvImageGetTempBufferSize flag in addition to all 
 * the regular parameters. The size will be returned in the  
 * vImage_Error result.  
 * kvImageGetTempBufferSize is for MacOS X.4 and later. 
 */
size_t 
vImageGetMinimumTempBufferSizeForHistogram( 
    const vImage_Buffer *src, 
    const vImage_Buffer *dest, 
    unsigned int histogram_entries, 
    vImage_Flags flags, 
    size_t bytesPerPixel ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_BUT_DEPRECATED( __MAC_10_3, __MAC_10_4, __IPHONE_NA, __IPHONE_NA );

#ifdef __cplusplus
}
#endif

#endif
