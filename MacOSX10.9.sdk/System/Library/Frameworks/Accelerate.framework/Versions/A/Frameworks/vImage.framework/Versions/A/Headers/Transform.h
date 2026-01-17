/*
 *  Transform.h
 *  vImage Framework
 *
 *  Copyright (c) 2003 Apple Computer. All rights reserved.
 *
 */

#ifndef VIMAGE_TRANSFORM_H
#define VIMAGE_TRANSFORM_H	

#include <vImage/vImage_Types.h>

#ifdef __cplusplus
extern "C" {
#endif



/*
 * vImageMatrixMultiply_Planar16S
 *
 * Transform M source planes to N destination planes by multiplying the
 * M x N transformation matrix by the source planes.  A pre-bias may
 * optionally be added to the source planes before the transformation.  A 
 * post-bias may optionally be added to the resulting destination planes. As 
 * a final step the destination planes are divided by a given divisor. 
 *
 * if (pre_bias)
 *   { bA, bR, bG, ... } = { A + pre_bias[0], R + pre_bias[1],
 *                           G + pre_bias[2], ... }
 * else 
 *   { bA, bR, bG, ... } = { A, R, G, ... }
 *
 *
 *                                            { a00  a01  a02  ... }
 * { A', R', G', ...} = { bA, bR, bG, ... } * { a10  a11  a12  ... }
 *                                            { a20  a21  a22  ... }
 *                                            { ...  ...  ...  ... }
 *
 * if (post_bias)
 *    { A', R', G', ... } += { post_bias[0], post_bias[1], post_bias[2], ... }
 * else // correct value for normal rounding: divisor/2
 *    { A', R', G', ... } += { divisor/2, divisor/2, divisor/2, ... }
 *
 * { A', R', G', ... } /= divisor
 *
 * where the values are:
 * { A', R', ... }	Resulting destination planes (dests).  For a concrete 
 *					example of the multiply step for one plane:
 *					A' = bA * a00 + bR * a10 + bG * a20 + ... * ...
 *
 * { A, R, ... }    Source planes (srcs).
 *
 * { bA, bR, ... }	Pre-biased source planes. (for demonstration only, never
 *					actually exists)
 *
 * a00, a01, ...    Elements in the transformation matrix (matrix).
 *
 * pre_bias         Pre-bias values corresponding to the source channels.
 *					Value is zero when NULL.
 *
 * post_bias 		Post-bias values corresponding to the destination channels.
 *					When NULL, the correct value for normal rounding if used,
 *					which is divisor/2.
 *
 * divisor			Divisor to normalize the destination planes.	
 *
 * Operands:
 * ---------
 * srcs				A pointer to an array of vImage_Buffer pointers that
 *					reference the source planes. This array must contain
 *					src_planes number of vImage_Buffer pointers.
 *
 * dests			A pointer to an array of vImage_Buffer pointers that 
 *					reference where to write the destination planes. Only 
 *					the image data pointed to by each vImage_Buffer is modified
 *					(i.e. dests[0]->data), everything else remains unchanged.
 *					This array must contain dest_planes number of vImage_Buffer
 *					pointers.
 *
 * src_planes		The number of source planes.  Must be less than 256.
 *
 * dest_planes		The number of destination planes.  Must be less than 256.
 *                         
 * matrix			The row major transformation matrix with dest_planes number 
 *					of columns and src_planes number of rows.  Be aware that if
 *					any column of this matrix sums to a value larger than 
 *					+-65538 this function may silently overflow.
 *
 * divisor			Division by this value occurs as the last step, in effect
 *					normalizing the output planes.
 *
 * pre_bias			An optional array of length src_planes consisting of int16_t
 *					values. Each value will be added to the corresponding
 *					source plane in srcs.  Pass NULL for no pre_bias.
 *
 * post_bias		An optional array of length dest_planes consisting of 
 *					int16_t values.  Each value will be added to the 
 *					corresponding destination planes in dests.  The post_bias
 *					is added before any clipping, rounding or division.  Pass 
 *					NULL the correct value for for normal rounding (divisor/2).
 *
 * flags			The following flags are allowed:
 *
 *		kvImageDoNotTile			Turns off internal multithreading. You may
 * 									wish to do this if you have your own
 *									multithreading scheme to avoid having the
 *									two interfere with one another.
 *
 * Return Value:
 * -------------
 * kvImageInvalidKernelSize			Either src_planes or dest_planes is 0.
 * kvImageBufferSizeMismatch		All buffers in dests must have the same
 *									width and height.
 * kvImageROILargerThanSourceBuffer The destination buffer size (width, or
 *									height) is larger than the source buffer.
 * kvImageUnknownFlagsBit			Unexpected flag was passed.		
 * kvImageNoError					Success!
 *
 *
 * Comments:
 * ---------
 * Be aware that 32-bit signed accumulators are used in this operation with no
 * overflow protection. To avoid the possibility of overflow, limit the sum
 * of any column in the transformation matrix to values less than +-65536.
 * 
 * The 32-bit accumulated results out of 16-bit range (+-32767) will be subject  
 * clipping before writing to the destination buffer.
 *
 * This routine will work in place provided all of the following are true:
 * src.data == dest.data
 * src.rowBytes == dest.rowBytes
 * kvImageDoNotTile is passed
 *
 *  Some matrix based color transforms, such as that obtained using kColorSyncConversionMatrix are defined differently.
 *
 *      ColorSync:      p' = M1 * p                  M1 = colorsync matrix,  p = input pixel as column vector, p' = output pixel as column vector
 *         vImage:      p'T = pT * M2                M2 = vImage matrix,T indicates transpose -- vImage pixels are row vectors
 *
 *  Given that (A*B)T = BT*AT, it can be shown that M2 = M1T. So, to use the alternative definition here, you need to transpose the matrix.
 *
 * Example:
 * --------
 * To convert RGB to YUV, one might use the following formula:
 *
 *          Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16
 *          U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128
 *          V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128
 *
 *      This translates to a matrix that looks like this:
 *
 *               66     -38     112
 *              129     -74     -94
 *               25     112     -18
 *
 *		Pass 256 as the divisor to handle the >> 8 operation.  The post_bias
 *		argument can handle the addition of { 16, 128, 128 }, however because
 *		this function performs the division last, this array must be scaled by
 *		the divisor, yielding a post_bias of:
 *			post_bias = { 16*divisor + divisor/2, 128*divisor + divisor/2, 
 *									128*divisor + divisor/2}
 *			post bias = { 4224, 32896, 32896 }
 */
    
vImage_Error vImageMatrixMultiply_Planar16S( const vImage_Buffer *srcs[],
                                             const vImage_Buffer *dests[],	
                                             uint32_t    	      src_planes,
                                             uint32_t    	      dest_planes,
                                             const int16_t    	  matrix[],
                                             int32_t              divisor,
                                             const int16_t	     *pre_bias,	
                                             const int32_t	     *post_bias,
                                             vImage_Flags 	      flags )
    										 VIMAGE_NON_NULL(1,2,5)
    										 __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
/*
 * vImageMatrixMultiply_*
 *
 *	Multiply the M channels in the src buffers (A,R,G...) by a NxM matrix (a##) to yield N channels in the dest buffer(s)
 *	For ARGB interleaved functions, both M and N must be 4. The pre_bias (ca, cr, cg...) is added to the M input channels
 *	before the matrix is applied. The post_bias (ka, kr, kg...)  is added afterward. 
 *
 *                                                             { a00  a10  a20  ... }
 *		{ A', R', G' ...} = { A + ca, R + cr, G + cg, ... } *  { a01  a11  a21  ... } + { ka, kr, kg, ....}
 *                                                             { a02  a12  a22  ... }
 *                                                             { ...  ...  ...  ... }
 *
 *		A', R', G', ... = result channels stored into dests
 *		A, R, G, ... = input channels from srcs
 *		ca, cr, cg, ... = pre_bias elements corresponding to the input src channels, or zero if pre_bias is NULL
 *		a00, a11, a12, ... = elmenets from the matrix[]
 *		ka, kr, kg, ... = post_bias elements corresponding to the destination dest channels, or zero if post_bias is NULL
 *
 *  For integer code, there is an additional division operation that happens at the end, in effect normalizing integer matrices. 
 *  The post-bias is added before any clipping, rounding or division. If you pass NULL for the post-bias, the correct value for 
 *  normal rounding will be used:
 *
 *      integer:            divisor/2
 *      floating point:     0.0f 
 *
 *  Be aware that 32 bit signed accumulators are used for integer code. If the sum over any matrix column is larger 
 *  than +- 2**23, then overflow may occur. Generally speaking this will not happen because the matrix elements are 
 *  16 bit integers, so one would need more than 256 source buffers before it is possible to encounter trouble.
 *
 *  As an example, to convert RGB to YUV, one might use the following formula:
 *
 *          Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16
 *          U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128
 *          V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128
 *
 *  This translates to a matrix that looks like this:
 *
 *               66     -38     112
 *              129     -74     -94
 *               25     112     -18
 *
 *  There is also the >>8 operation and the extra terms to be dealt with. For integer data, you would use a divisor of 
 *  256 to account for the >>8 operation. The divisor is applied last after all other multiplications and additions. 
 *  (For floating point, there is no divisor. Just divide the whole matrix by the divisor if one is needed.) Use the
 *  post bias to handle the +128 and {+16, +128, +128} terms. Since the second set happen after the divisor in the 
 *  formula above, but our post_bias is applied before the divide, you'll need to multiply those biases by the divisor.  
 *  This will give a post_bias of:
 *
 *              {  16 * 256 + 128, 128 * 256 + 128, 128 * 256 + 128 } = { 4224, 32896, 32896 }
 *
 *  Finally, if there is an alpha component, such that you wish to convert ARGB to AYUV, leaving the alpha component
 *  unchanged then add another row and column:
 *
 *      matrix =    divisor      0       0       0
 *                      0        66     -38     112 
 *                      0       129     -74     -94 
 *                      0        25     112     -18 
 *
 *      post_bias =     { divisor/2, 4224, 32896, 32896 }
 *      divisor =       256
 *
 *  Integer results out of range of 0...255 will be subject to saturated clipping before writing to the destination buffer.
 *
 *
 *	Programming Note:
 *		The pre-bias is provided as a convenience. The pre-bias can be converted to a post bias by 
 *	multiplying it by the matrix, which is what we do behind the scenes. Pass NULL for the pre-bias if
 *	you don't want a prebias added in.
 *	
 *	These functions work in place as long as overlapping buffers overlap exactly. Buffers that partially overlap
 *	will yield undefined results. Destination buffers will be stored to in the order they appear in the dests array.
 *	The buffers all need to be the same size. They can have different rowBytes. 	
 *
 *  In cases where the number of src and dest buffers match, these functions will work in place. 
 *  The source and destination buffers may all be different sizes and have different sized rowbytes. The source buffers must 
 *  be at least as large as the dest buffers. In cases where the source buffer is larger than a dest buffer, the portion of the 
 *  source buffer that overlaps the destination buffer when their top left corners are aligned will be used.  
 *
 *  Some matrix based color transforms, such as that obtained using kColorSyncConversionMatrix are defined differently.
 *
 *      ColorSync:      p' = M1 * p                  M1 = colorsync matrix,  p = input pixel as column vector, p' = output pixel as column vector
 *         vImage:      p'T = pT * M2                M2 = vImage matrix, T indicates transpose -- vImage pixels are row vectors
 *
 *  Given that (A*B)T = BT*AT, we find that M2 = M1T. So, to use the alternatively defined matrix here, you need to transpose the matrix 
 *  before passing it to vImage.
 */

vImage_Error vImageMatrixMultiply_Planar8(          const vImage_Buffer *srcs[],	//A set of src_planes as a const array of pointers to vImage_Buffer structs that reference vImage_Buffers.
                                                    const vImage_Buffer *dests[],	//A set of src_planes as a const array of pointers to vImage_Buffer structs that reference vImage_Buffers.
                                                    uint32_t    	src_planes,
                                                    uint32_t    	dest_planes,
                                                    const int16_t    	matrix[],
                                                    int32_t             divisor,
                                                    const int16_t	*pre_bias,	//A packed array of src_plane int16_t values. NULL is okay
                                                    const int32_t	*post_bias,	//A packed array of dest_plane int32_t values. NULL is okay
                                                    vImage_Flags 	flags ) VIMAGE_NON_NULL(1,2,5) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

vImage_Error vImageMatrixMultiply_PlanarF(          const vImage_Buffer *srcs[],        //A set of src_planes as a const array of pointers to vImage_Buffer structs that reference vImage_Buffers.
                                                    const vImage_Buffer *dests[],       //A set of src_planes as a const array of pointers to vImage_Buffer structs that reference vImage_Buffers.
                                                    uint32_t    	src_planes,
                                                    uint32_t    	dest_planes,
                                                    const float		matrix[],		
                                                    const float 	*pre_bias,	//A packed array of float values. NULL is okay
                                                    const float 	*post_bias,	//A packed array of float values. NULL is okay
                                                    vImage_Flags flags ) VIMAGE_NON_NULL(1,2,5) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 * vImageMatrixMultiply_ARGB8888 will also work for other channel orders such as RGBA8888.  The ordering of terms in the matrix, pre_bias and 
 * post_bias should be adjusted to compensate.
 */
vImage_Error vImageMatrixMultiply_ARGB8888(         const vImage_Buffer *src,
                                                    const vImage_Buffer *dest,
                                                    const int16_t	matrix[4*4],
                                                    int32_t             divisor,
                                                    const int16_t	*pre_bias,	//Must be an array of 4 int16_t's. NULL is okay. 
                                                    const int32_t 	*post_bias,	//Must be an array of 4 int32_t's. NULL is okay. 
                                                    vImage_Flags 	flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 * vImageMatrixMultiply_ARGBFFFF will also work for other channel orders such as RGBAFFFF.  The ordering of terms in the matrix, pre_bias and 
 * post_bias should be adjusted to compensate.
 */
vImage_Error vImageMatrixMultiply_ARGBFFFF(         const vImage_Buffer *src,
                                                    const vImage_Buffer *dest,
                                                    const float		matrix[4*4],
                                                    const float		*pre_bias,	//Must be an array of 4 floats. NULL is okay. 
                                                    const float		*post_bias,	//Must be an array of 4 floats. NULL is okay. 
                                                    vImage_Flags 	flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 * The gamma calculation is at the simplest level:
 *
 *      if( value < 0) 
 *          sign = -1.0f;
 *      else
 *          sign = 1.0f;
 *
 *      result = pow( fabs( value ), gamma ) * sign;
 *
 *  i.e. negative values are treated as if they are positive, and the sign restored at the end.
 *
 * This provides for symmetric gamma curves about 0, and also solves the problem of NaN results from
 * pow( negative number, non-integer). 
 *
 * The results are available in two varieties, full and half precision. The full precision version covers
 * all pixel values and all exponents and delivers a result within a few ULPs of the IEEE-754 correct powf().
 *       
 * The half precision variant provides a precision of ±1/4096: 
 *
 *          fabs((correct result - result provided)) < 1/4096
 *
 * Half-precision is intended to be used with data that will ultimately be converted to 8-bit integer data. 
 * As such, the faster half precision variants only work for floating point pixel values in the range 0.0 ... 1.0.
 * Out of range pixel values will clamp appropriately to 0.0 or 1.0 before the calculation is performed. 
 *
 * In addition, there are restrictions on range on the exponent. In general, for best performance, it should be near 1.0,
 * though a faster path exists out to +-12. If the exponent is outside the prescribed range the code will return a full 
 * precision gamma instead. (In MacOS X.4.3 and earlier, all exponents fall back on the full precision version. )  
 *
 * Half precision calculations that conform to these restrictions are likely to be much faster 
 * than the full precision gamma. Use kvImageGamma_UseGammaValue and kvImageGamma_UseGammaValue_half_precision 
 * to control whether you get a full or half precision result. kvImageGamma_UseGammaValue will never use a 
 * half-precision calculation.
 *
 * There are some additional gamma types for specific gamma curves. These are precise to ±1/4096, share the same
 * restrictions as above for the half precision gamma, but execute in less time. (These fixed exponent gamma curves
 * are present in MacOS X.4, unless otherwise noted below.)
 *
 * vImageGamma_PlanarF and vImageGamma_PlanarFToPlanar8 will work in place, provided that the following are true:
 *      src->data == dest->data
 *      src->rowBytes >= dest->rowBytes
 *      if( src->rowBytes > dest->rowBytes ) kvImageDoNotTile must be passed in the flags parameter
 *
 * vImageGamma_Planar8ToPlanarF will NOT work in place. 
 *
 *  For the func
 *
 * These functions will also work for multichannel data, such as RGBAFFFF buffers by adjusting the width of the buffer to 
 * reflect the additional channels. Note that this will cause the alpha channel if there is one to become gamma corrected.
 */

/*
 * constants for use in the gamma_type
 */
enum
{
    kvImageGamma_UseGammaValue                  =   0,          /* __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
    kvImageGamma_UseGammaValue_half_precision   =   1,          /* __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
    kvImageGamma_5_over_9_half_precision        =   2,          /* gamma = 5/9. (Gamma 1/1.8) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
    kvImageGamma_9_over_5_half_precision        =   3,          /* gamma = 9/5. (Gamma 1.8)  __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
    kvImageGamma_5_over_11_half_precision       =   4,          /* gamma = 5/11. (Gamma 1/2.2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
    kvImageGamma_11_over_5_half_precision       =   5,          /* gamma = 11/5. (Gamma 2.2) On exit, gamma = 5/11. __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
    kvImageGamma_sRGB_forward_half_precision    =   6,          /* gamma = sRGB standard 2.2. (like 2.2 but offset a bit and with a linear segment: x<0.03928?x/12.92:pow((x+0.055)/1.055,2.4) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
    kvImageGamma_sRGB_reverse_half_precision    =   7,          /* gamma = sRGB standard 1/2.2. (like 2.2 but offset a bit and with a linear segment: x<0.00304?12.92*x:1.055pow(x,1/2.4)-0.055) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
    kvImageGamma_11_over_9_half_precision       =   8,          /* gamma = 11/9 (Gamma (11/5)/(9/5)) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
    kvImageGamma_9_over_11_half_precision       =   9,          /* gamma = 9/11 (Gamma (9/5)/(11/5)) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
	kvImageGamma_BT709_forward_half_precision	=	10,			/* gamma = ITU-R BT.709 standard (like sRGB above but without the 1.125 viewing gamma for computer graphics: x<0.081?x/4.5:pow((x+0.099)/1.099, 1/0.45) ) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
	kvImageGamma_BT709_reverse_half_precision	=	11			/* gamma = ITU-R BT.709 standard *reverse* (like sRGB 1/2.2 above but without the 1.125 viewing gamma for computer graphics: x<0.018?4.5*x:1.099*pow(x,0.45)-0.099) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 ) */
};

GammaFunction   vImageCreateGammaFunction(          float           gamma,
                                                    int             gamma_type,
                                                    vImage_Flags    flags )             __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

void            vImageDestroyGammaFunction( GammaFunction f )                           __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/* There is a 8 bit lookup table in Conversion.h, if you are looking for a 8bit to 8bit gamma function. */
vImage_Error    vImageGamma_Planar8toPlanarF(       const vImage_Buffer *src,
                                                    const vImage_Buffer *dest,           
                                                    const GammaFunction gamma,
                                                    vImage_Flags        flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
                                                    
vImage_Error    vImageGamma_PlanarFtoPlanar8(       const vImage_Buffer *src,           
                                                    const vImage_Buffer *dest,          
                                                    const GammaFunction gamma,
                                                    vImage_Flags        flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
                                                    
vImage_Error    vImageGamma_PlanarF(                const vImage_Buffer *src,           
                                                    const vImage_Buffer *dest,          
                                                    const GammaFunction gamma,
                                                    vImage_Flags        flags ) VIMAGE_NON_NULL(1,2) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
                                        
/* vImagePiecewiseGamma_Planar8
 * vImagePiecewiseGamma_Planar8toPlanar16Q12
 * vImagePiecewiseGamma_Planar8toPlanarF
 * vImagePiecewiseGamma_Planar16Q12
 * vImagePiecewiseGamma_Planar16Q12toPlanar8
 * vImagePiecewiseGamma_PlanarF
 * vImagePiecewiseGamma_PlanarFtoPlanar8
 *
 * The piecewise gamma calculation combines a linear and an exponential (gamma)
 * curve on two regions of the input interval, separated by a user-supplied
 * boundary value.  When the input is greater or equal to the boundary value,
 * the gamma curve is used to generate the output. Otherwise, the linear curve
 * is used.
 *
 * The operation can be described as follows:
 *
 *  For each source pixel value x:
 *    sign = x < 0 ? -1 : 1
 *    absx = x < 0 ? -x : x
 *    if absx < cutoff:
 *      output pixel value = sign * (linearCoeffs[0]*absx + linearCoeffs[1])
 *    else:
 *      y = exponentialCoeffs[0]*absx + exponentialCoeffs[1]
 *      output pixel value = sign * (pow(y, gamma) + exponentialCoeffs[2])
 *
 * If y is negative, the result is undefined.
 *
 * If the source format is Planar8, we multiply by 1/255.0 to get the "input"
 * value used in the expression above; if the destination format is Planar8,
 * we clamp the output value to [0, 1.0], multiply by 255.0 and round to
 * nearest to get the value stored to the destination buffer.
 *
 * If the source format is Planar16Q12, we multiply by 1/4096.0 to get the
 * input value; we clamp to [-8, 8), multiply by 4096.0, and round to nearest
 * to get the stored to the destination buffer.
 *
 * Regardless of the input or output pixel type, the parameters describing the
 * piecewise gamma function are 32-bit floats, with the single exception of the
 * boundary parameter.
 *
 *  Operands:
 *  ---------
 *      src                 A pointer to a vImage_Buffer that references the source pixels
 *
 *      dest                A pointer to a vImage_Buffer that references the destination pixels
 *
 *      exponentialCoeffs   An array of three floating point coefficients for the gamma curve
 *
 *      gamma               The exponent of a power function for calculating gamma correction
 *
 *      linearCoeffs        An array of two floating point coefficients for the linear curve
 *
 *      boundary            The boundary value for switching from linear to gamma curve
 *
 *      flags               The following flags are allowed:
 *
 *          kvImageDoNotTile            Turns off internal multithreading. You may
 *                                      wish to do this if you have your own
 *                                      multithreading scheme to avoid having the
 *                                      two interfere with one another.
 *
 *          kvImageGetTempBufferSize    Does no work and returns zero.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError                  Success!
 *      kvImageNullPointerArgument      src, dest, exponentialCoeffs, or linearCoeffs pointer is NULL.
 *      kvImageBufferSizeMismatch       The destination buffer size (width or
 *                                      height) is larger than the source buffer.
 *      kvImageUnknownFlagsBit          An unknown or invalid flag was passed. See flags above.
 *
 *  The variants of this routine that have source and dest pixel types of the
 *  same size (Planar8, Planar16Q12, and PlanarF) operate in place so long as
 *  the source and dest image scanlines overlap exactly.  The other variants
 *  (Planar8toPlanar16Q12, Planar8toPlanarF, etc) do not support in-place
 *  operation.
 */

vImage_Error vImagePiecewiseGamma_Planar8(const vImage_Buffer *src,
                                          const vImage_Buffer *dest,
                                          const float         exponentialCoeffs[3],
                                          const float         gamma,
                                          const float         linearCoeffs[2],
                                          const Pixel_8       boundary,
                                          vImage_Flags        flags) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
vImage_Error vImagePiecewiseGamma_Planar8toPlanar16Q12(const vImage_Buffer *src,
                                                       const vImage_Buffer *dest,
                                                       const float         exponentialCoeffs[3],
                                                       const float         gamma,
                                                       const float         linearCoeffs[2],
                                                       const Pixel_8       boundary,
                                                       vImage_Flags        flags) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
vImage_Error vImagePiecewiseGamma_Planar16Q12(const vImage_Buffer *src,
                                              const vImage_Buffer *dest,
                                              const float         exponentialCoeffs[3],
                                              const float         gamma,
                                              const float         linearCoeffs[2],
                                              const Pixel_16S     boundary,
                                              vImage_Flags        flags) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
vImage_Error vImagePiecewiseGamma_Planar16Q12toPlanar8(const vImage_Buffer *src,
                                                       const vImage_Buffer *dest,
                                                       const float         exponentialCoeffs[3],
                                                       const float         gamma,
                                                       const float         linearCoeffs[2],
                                                       const Pixel_16S     boundary,
                                                       vImage_Flags        flags) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
vImage_Error vImagePiecewiseGamma_Planar8toPlanarF(const vImage_Buffer *src,
                                                   const vImage_Buffer *dest,
                                                   const float         exponentialCoeffs[3],
                                                   const float         gamma,
                                                   const float         linearCoeffs[2],
                                                   const Pixel_8       boundary,
                                                   vImage_Flags        flags) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

vImage_Error vImagePiecewiseGamma_PlanarF(const vImage_Buffer *src,
                                          const vImage_Buffer *dest,
                                          const float         exponentialCoeffs[3],
                                          const float         gamma,
                                          const float         linearCoeffs[2],
                                          const float         boundary,
                                          vImage_Flags        flags) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
vImage_Error vImagePiecewiseGamma_PlanarFtoPlanar8(const vImage_Buffer *src,
                                                   const vImage_Buffer *dest,
                                                   const float         exponentialCoeffs[3],
                                                   const float         gamma,
                                                   const float         linearCoeffs[2],
                                                   const float         boundary,
                                                   vImage_Flags        flags) VIMAGE_NON_NULL(1,2,3,5) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *  vImagePiecewisePolynomial*
 *
 *  Apply one or more polynomials to the input image to give the output image.  
 *
 *  vImagePiecewisePolynomial_Planar8toPlanarF uses 8 bit data on input and produces floating point data.
 *  vImagePiecewisePolynomial_PlanarFtoPlanar8 uses floating point data on input and produces 8-bit data with saturated clamping at 0 and 255 to prevent modulo overflow.
 *  vImagePiecewisePolynomial_PlanarF floating point data on both input and output.
 *  vImageTableLookUp_Planar8 uses 8 bit data and produces 8 bit data. In certain cases, the matrix multiply function may also be appropriate.
 *
 *  No other arithmetic is done. If you wish a /255 or *255 operation to be done as part of the calculation, you must incorporate that into your polynomial.
 *
 *  The arrangement of the polynomials is defined as follows:
 *      Let there be N polynomials that each cover part of the single precision floating point range that are arranged in order of area of influence from -Infinity to Infinity.
 *      The ith polynomial shall operate on the set of input pixel values that fall in the range:  
 *
 *          boundary[i] <= pixel_value < boundary[i+1]. 
 *
 *     for which:
 *
 *          boundary[0] = smallest value fit by the polynomial. Input pixels smaller than this will be clamped to this value before the calculation is done. Use -Inf for no lower limit.
 *          boundary[N] = largest value fit by the polynomial. Input pixels larger than this will be clamped to this value before the calculation is done. Use +Inf for no upper limit.
 *          boundary[1....N-1] = the boundaries separating the input ranges covered by the various polynomials provided (see below)
 *
 *     NaNs will return NaNs. The last polynomial also operates on Inf.  N must be an integer power of 2.
 *     Values found in the distination array are undefined until after the function returns.
 *	   The behavior is undefined if boundaries are NaN.
 *
 *  These functions will also work for multichannel data, such as RGBAFFFF buffers by adjusting the width of the buffer to 
 *  reflect the additional channels. Note that this will cause the alpha channel, if there is one, to become modified like the other channels.
 *  These will work in place, provided that the following are true:
 *      src->data == dest->data
 *      src->rowBytes >= dest->rowBytes
 *      if( src->rowBytes > dest->rowBytes ) kvImageDoNotTile must be passed in the flags parameter

 *
 *  The input parameters are as follows:
 *
 *      src = a pointer to a vImage_Buffer containing the input data for the function
 *      dest = a pointer to a vImage_Buffer structure that describes where to write the results
 *
 *      coefficients = a packed array of pointers to packed arrays of (order+1) polynomial coefficients ( i.e. coefficients[ N ][ order + 1 ] ). 
 *                      The polynomials must appear in order from least to greatest sorted by area of influence.
 *                      The polynomials must all be of the same order. 
 *                      The polynomial coefficients are sorted from 0th order term to highest order term 
 *
 *      boundaries = a packed array of (N+1) floating point values that mark the dividing line between one polynomial and the next. These must be sorted from most negative to most positive. 
 *						Input pixel values less than boundaries[0] will be clamped to be equal to boundaries[0] before the calculation is done
 *						Input pixel values greater than boundaries[N] will be clamped to be equal to boundaries[N] before the calculation is done
 *
 *      order = the number of coefficients minus one used for each polynomial -- all the polynomials must be of the same order
 *                  A polynomial with _two_ coefficients (y = c0 + c1 * x) is a _first_ order polynomial. Pass 1 for a first order polynomial. Pass 2 for a second order polynomial, etc. 
 *
 *      log2segments = log2(N)  
 *
 *      flags = no flags are currently honored. You must pass zero here.
 *
 *      vImagePiecewisePolynomial_PlanarF will work in place.
 *      vImagePiecewisePolynomial_Planar8toPlanarF will work in place.
 *      vImagePiecewisePolynomial_PlanarFtoPlanar8 will NOT work in place.
 *
 *  Performance advisory: 
 *      It costs much more to resolve additional polynomials than to work with higher order polynomials. 
 *      For performance, you are typically better off with one 9th order polynomial that spans the range you are 
 *      interested in than many first order polynomials that cover the area in a  piecewise fashion. 
 *      Vector code execution time is roughly proportional to:
 *
 *              time = (base cost to touch all the data) + polynomial order + 4 * log2segments
 *
 *      The vector code for a unsplit 13th order polynomial should be about as fast as vImageLookupTable_Planar8toPlanarF() 
 *          on a G4.
 *
 *      With data not in cache, the time may be significantly different. For sufficiently small polynomials, the 
 *      cost may be a fixed cost, dependent only on how much data is touched, and not on polynomial order.
 *
 *        This performance behavior is provided to help developers evaluate speed tradeoffs. It is not a guaranteed. 
 *        It is subject to change in future operating system revisions, and may be different on different hardware
 *        within the same or different operating system revisions. 
 *
 *      Vector code is not invoked for log2segments > 3.
 *
 *  Accuracy advisory:
 *      Single precision floating point arithmetic is used. While some polynomials may fit a desired curve 
 *      within prescribed error limits when using infinite precision math, limited floating point precision 
 *      may in practice cause significant error to accumulate for some sets of polynomial coefficients. It is 
 *      recommended that you test all reasonable floating point pixel values to make sure that they do indeed
 *      give results that conform to prescribed error limits. 
 *      
 *
 *  Usage Example:
 *  --------------
 *      Lets say you want to mimic the sRGB gamma curve using vImagePiecewisePolynomial_PlanarF. The sRGB gamma curve is defined as follows:
 *
 *              if( {R,G,B} < 0.00304 )
 *                  result = 12.92 * {R,G,B}
 *              else
 *                  result = -0.055 + 1.055 * Pow( {R,G,B}, 2.4 )
 *
 *      Since the power function isn't a polynomial and we need a polynomial, we will approximate it with a second order polynomial:
 *
 *              if( {R,G,B} < 0.00304 )
 *                  result = 12.92 * {R,G,B}
 *              else
 *                  result = c0 + c1 * {R,G,B} + c2 * {R,G,B}^2
 *
 *      (Finding the best values for c0, c1, c2 to approximate -0.055 + 1.055 * Pow( {R,G,B}, 2.4 ) over the range [0.00304, 1.0] is 
 *          left as an exercise for the reader.) 
 *
 *      We have two polynomials -- one for the region below 0.00304 and one for the region above, so N = 2.
 *      The highest order polynomial is a second order polynomial, so order = 2.
 *
 *              const int N = 2;        // two polynomials 
 *              const int order = 2;    // the polynomials are second order (have three terms, including zero terms)
 *
 *      The two polynomials are:
 *
 *              float linearPart[ order + 1 ] = { 0, 12.92, 0 }; //result = 0 + 12.92 * {R,G,B} + 0 * {R,G,B} * {R,G,B} 
 *              float nonLinearPart[ order + 1 ] = { c0, c1, c2 };  //result = c0 + c1 * {R,G,B} + c2 * {R,G,B} * {R,G,B}
 *
 *      Here we assemble the rest of the information:
 *      
 *              float *coefficients[ N ] = { linearPart, nonLinearPart };   //sorted in order of area of influence from least to greatest. ( x < 0.00304, x >= 0.00304 )
 *              float boundaries[ N+1 ] = { 0.0f, 0.00304, 1.0f };      //sorted in order from least to greatest. 0.0f and 1.0f define the range over which the polynomials are valid. 0.00304 is the single value separating the two polynomials
 *              int log2segments = 1;  //log2(N) 
 *              int flags = 0;          //you must pass 0 for the flags
 *
 *              vImage_Error error = vImagePiecewisePolynomial_PlanarF( &mySourceBuffer, &myDestinationBuffer, coefficients, boundaries, order, log2segments, flags );
 */										
vImage_Error    vImagePiecewisePolynomial_PlanarF(  const vImage_Buffer *src,       //floating point data
                                                    const vImage_Buffer *dest,       //floating point data
                                                    const float         **coefficients,
                                                    const float         *boundaries,
                                                    uint32_t            order,
                                                    uint32_t            log2segments,
                                                    vImage_Flags        flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );



vImage_Error    vImagePiecewisePolynomial_Planar8toPlanarF( const vImage_Buffer *src,        //8-bit data
                                                            const vImage_Buffer *dest,       //floating point data
                                                            const float         **coefficients,
                                                            const float         *boundaries,
                                                            uint32_t            order,
                                                            uint32_t            log2segments,
                                                            vImage_Flags        flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

vImage_Error    vImagePiecewisePolynomial_PlanarFtoPlanar8( const vImage_Buffer *src,       //floating point data
                                                            const vImage_Buffer *dest,      //8-bit data
                                                            const float         **coefficients,
                                                            const float         *boundaries,	/*The 0th and Nth terms in the boundaries array are typically 0.0f and 255.0f respectively. Other values may incur additional computational cost. */
                                                            uint32_t            order,
                                                            uint32_t            log2segments,
                                                            vImage_Flags        flags ) VIMAGE_NON_NULL(1,2,3,4) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

/*
 *      vImagePiecewiseRational_PlanarF is similar to vImagePiecewisePolynomial_PlanarF
 *      Except that it evaluates a piecewise rational expression in the form of:
 *
 *                      c0 + c1*x + c2*x^2 + c3*x^3...
 *          result = -----------------------------------
 *                      d0 + d1*x + d2*x^2 + d3*x^3...
 *
 *      The function is behaves nearly exactly like vImagePiecewisePolynomial_PlanarF, except that
 *      there are now two polynomials, for top and bottom of the divide shown above. Each
 *      polynomial has its own set of coefficients and its own polynomial order. The two 
 *      polynomials share the same set of segment boundaries. If the polynomials are split then 
 *      all the top polynomials must be of the same order, and all the bottom polynomials must 
 *      be of the same order. However, regardless of whether the polynomial is split or not,
 *      the top polynomials do not need to be the same order as the bottom polynomials.
 *
 *      This function does not deliver IEEE-754 correct division. The divide does not round per
 *      the IEEE-754 current rounding mode. It incurs up to 2 ulps of error. Edge cases involving 
 *      denormals, infinities, NaNs and division by zero return undefined results. (They will not 
 *      crash, but NaN is a likely result in such cases.) Denormals can be rescued on AltiVec enabled 
 *      machines by turning off the Non-Java bit in the VSCR, at the expense of taking a many-thousand 
 *      cycle kernel exception every time a denormal number is encountered. Since you can predict ahead 
 *      of time whether a given set of bounded polynomials is going to encounter these conditions, 
 *      this problem should be avoidable by wise choice of polynomials. Developers who require IEEE-754 
 *      correct results should call the polynomial evaluator above twice and do the division themselves. 
 *
 *      These functions will also work for multichannel data, such as RGBAFFFF buffers by adjusting the 
 *      width of the buffer to reflect the additional channels. Note that this will cause the alpha channel, 
 *      if there is one, to become modified like the other channels.
 *
 *      These will work in place, provided that the following are true:
 *          src->data == dest->data
 *          src->rowBytes >= dest->rowBytes
 *          if( src->rowBytes > dest->rowBytes ) kvImageDoNotTile must be passed in the flags parameter

 *      Performance Advisory:
 *        Approximate cost of evaluating a rational (in the same units as polynomial above) is:
 *
 *              time = (base cost to touch all the data) 
 *                          + top polynomial order 
 *                          + bottom polynomial order 
 *                          + 4 
 *                          + 4 * log2segments
 *
 *        With data not in cache, the time may be significantly different. For sufficiently small polynomials, the 
 *        cost may be a fixed cost, dependent only on how much data is touched, and not on polynomial order.
 *
 *        This performance behavior is provided to help developers evaluate speed tradeoffs. It is not a guaranteed. 
 *        It is subject to change in future operating system revisions, and may be different on different hardware
 *        within the same or different operating system revisions. 
 *
 */
vImage_Error    vImagePiecewiseRational_PlanarF(  const vImage_Buffer *src,         //floating point data
                                                    const vImage_Buffer *dest,       //floating point data
                                                    const float         **topCoefficients,
                                                    const float         **bottomCoefficients,
                                                    const float         *boundaries,
                                                    uint32_t            topOrder,
                                                    uint32_t            bottomOrder,
                                                    uint32_t            log2segments,
                                                    vImage_Flags        flags ) VIMAGE_NON_NULL(1,2,3,4,5) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );
    
/*  A simple lookup table:
 *
 *          Pixel_16U table[256];
 *          Pixel_16U result_pixel = table[input_8_bit_pixel];
 *
 *  The input is a buffer of 8-bit pixels. The output is a buffer of 16-bit pixels.
 *
 *	Note: It is okay to use this to convert Planar8 data to other 16 bit types as well, such as 16S or 16F,
 *  or ARGB1555 or RGB565 pixels.  Simply use an array of the appropriate type for the lookup table.
 *
 *  This function can also work for multichannel data by scaling the width of the image to compensate for the
 *  additional channels. All channels will use the same table.
 *
 *  vImageLookupTable_Planar8ToPlanar16 will not work in place.
 */
    
vImage_Error vImageLookupTable_Planar8toPlanar16(const vImage_Buffer *src,
                                                 const vImage_Buffer *dest,
                                                 const Pixel_16U      table[256],
                                                 vImage_Flags         flags)
    VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
    
/*
 *  A simple lookup table:
 *
 *          float table[256];
 *          float result_pixel = table[ input_8_bit_pixel ];
 *
 *  The input is a buffer of 8-bit pixels. The output is a buffer of floating point pixels. 
 *
 *	Note: It is okay to use this to convert Planar8 data to other 32 bit types as well, such as a ARGB8888 pixel. 
 *			Simply pass a Pixel_8888[256] array instead of a Pixel_F[256] array.
 *
 *  This function can also work for multichannel data by scaling the width of the image to compensate for the 
 *  additional channels. All channels will use the same table.
 *  
 *  vImageLookupTable_Planar8ToPlanarF will not work in place.
 */
    
vImage_Error vImageLookupTable_Planar8toPlanarF(const vImage_Buffer *src,
                                                const vImage_Buffer *dest,
                                                const Pixel_F        table[256],
                                                vImage_Flags         flags)
    VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_5_0);


/*
 *  A simple lookup table with floating point inputs:
 *
 *          uint8_t table[4096];
 *          uint32_t index =  (uint32_t) MIN( MAX( input_float_pixel * 4096.0f, 0.0f), 4095.0f);
 *          uint8_t result_pixel = table[ index ];
 *
 *  The input is a buffer of floating-point pixels. The output is a buffer of 8-bit pixels. 
 *  This function can also work for multichannel data by scaling the width of the image to compensate for the 
 *  additional channels. All channels will use the same table.
 *
 *  vImageLookupTable_PlanarFToPlanar8 will work in place, provided that the following are true:
 *      src->data == dest->data
 *      src->rowBytes >= dest->rowBytes
 *      if( src->rowBytes > dest->rowBytes ) kvImageDoNotTile must be passed in the flags parameter
 */
vImage_Error
vImageLookupTable_PlanarFtoPlanar8(
    const vImage_Buffer *src,          /* floating point pixels */
    const vImage_Buffer *dest,         /* 8-bit pixels */
    const Pixel_8       table[4096],
    vImage_Flags        flags )
    VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );


/*
 *  vImageLookupTable_8to64U
 *
 *  Use a lookup table to remap 0..255 values in the source image to a
 *  different set of 64-bit unsigned integer values in the destination.
 *
 *          uint64_t table[256];
 *          uint64_t result_pixel = table[ input_8_bit_pixel ];
 *
 *      src         A pointer to a vImage_Buffer that references the source pixels
 *
 *      dest        A pointer to a vImage_Buffer that references the destination pixels
 *
 *      table       A pointer to the lookup table. The table should be an array with 256 elements.
 *
 *      flags       The following flags are allowed:
 *
 *          kvImageDoNotTile         Turns off internal multithreading. You may
 *                                   wish to do this if you have your own
 *                                   multithreading scheme to avoid having the
 *                                   two interfere with one another.
 *
 *  Return Value:
 *  -------------
 *      kvImageNoError                  Success!
 *      kvImageBufferSizeMismatch       Sizes of the src and dest images do not match
 *      kvImageNullPointerArgument      src, dest or table pointer is NULL.
 *
 *  This routine will not work in place.
 *
 */
vImage_Error
vImageLookupTable_8to64U(
    const vImage_Buffer *src,
    const vImage_Buffer *dest,
    const uint64_t      LUT[256],
    vImage_Flags flags)
    VIMAGE_NON_NULL(1,2,3)   __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );


/*
 *  vImageInterpolatedLookupTable_PlanarF
 *
 *  Results are calculated as follows:
 *
 *	float clippedPixel = MAX( MIN( src_pixel, maxFloat ), minFloat );	//clip src_pixel to be in range
 *	float fIndex = (float) (tableEntries - 1) * (clippedPixel - minFloat ) / (maxFloat - minFloat);
 *	float fract = fIndex - floor( fIndex );
 *	unsigned long index =  fIndex;
 *	float result = table[ index ] * ( 1.0f - fract ) + table[ index + 1] * fract;
 *
 *  In English, this translates to a lookup table that contains tableEntries values, that span
 *  the input range of minFloat...maxFloat, inclusive, in an evenly spaced fashion.
 *
 *                      tableEntries
 *               <--------------------->
 *      |
 *    r |          ****
 *    e |        *      *              *
 *    s |                 *          *
 *    u |                  *       *
 *    l |                    *****  
 *    t +--------+---------------------+--------
 *            minFloat              maxFloat
 *
 *	IMPORTANT: For correct operation, the table must be allocated to contain tableEntries+1 entries. 
 *				If the table is too small or the value of table[ tableEntries ] is infinite or NaN, 
 *				behavior is undefined.
 *
 *  The function will work in place, provided that the following are true:
 *      src->data == dest->data
 *      src->rowBytes >= dest->rowBytes
 *      if( src->rowBytes > dest->rowBytes ) kvImageDoNotTile must be passed in the flags parameter
 * 
 *  This function may be used on multichannel images by scaling the width by the number of channels.
 *  The same table will be used for all the channels, including alpha, if there is an alpha channel.
 */
vImage_Error    vImageInterpolatedLookupTable_PlanarF(  const vImage_Buffer *src,
                                                        const vImage_Buffer *dest,
                                                        const Pixel_F       *table,
                                                        vImagePixelCount    tableEntries,
                                                        float               maxFloat,
                                                        float               minFloat,
                                                        vImage_Flags        flags ) VIMAGE_NON_NULL(1,2,3) __OSX_AVAILABLE_STARTING( __MAC_10_4, __IPHONE_5_0 );

    
/*
 *  vImageMultidimensionalTable_Create
 *
 *  Creates a vImage_MultidimensionalTable for use with vImageMultiDimensionalInterpolatedLookupTable_<fmt>(). The
 *  input data is a contiguous array of N dimensional samples which define the lookup table grid points.
 *  The samples have range [0,65535] interpreted as [0, 1.0f]. (Samples have an implict divide by 65535
 *  in them, like the Planar16U format.)  
 *
 *  The vImage_MultidimensionalTable is not a CFType.
 *
 *  Example: 
 *      Suppose the multidimensional table is intended to convert RGB (3 channel) data to CMYK (4 channel).
 *      In each of the {R, G, B} dimensions, we have 17 samples. The table is then comprised of
 *      17x17x17=4913 uint16_t[4]'s, each of which contains {C,M,Y,K} for that position. The dimensions
 *      are iterated in standard C order (row major). In this case, they would be:
 * 
 *      {CMYK for  R0G0B0, CMYK for R0G0B1,  CMYK for  R0G0B2, ...  CMYK for  R0G0B16,
 *       CMYK for  R0G1B0, CMYK for R0G1B1,  CMYK for  R0G1B2, ...  CMYK for  R0G1B16,
 *       ...
 *       CMYK for R0G16B0, CMYK for R0G16B1, CMYK for R0G16B2, ...  CMYK for R0G16B16,
 *       CMYK for  R1G0B0, CMYK for R1G0B1,  CMYK for R1G0B2,  ...  CMYK for R1G0B16,
 *       ...
 *       CMYK for R1G16B0, CMYK for R1G16B1, CMYK for R1G16B2,  ...  CMYK for R1G16B16,
 *       ...
 *       CMYK for R16G16B0, CMYK for R16G16B1, CMYK for R16G16B2,  ...  CMYK for R16G16B16 }
 *
 *  Parameters:
 *      tableData                   A non-NULL pointer to the data used to build the table
 *      numSrcChannels              The number of channels in an input pixel
 *      numDestChannels             The number of channels in an output pixel
 *      table_entries_per_dimension An array containing the number of table entries for each dimension in numSrcChannels
 *                                      The entries are in the same order as the channels in the src pixel.
 *      hint                        An indication of how the table would be used.  Pass either kvImageMDTableHint_16Q12
 *                                      or kvImageMDTableHint_Float or both. If only one is passed, we will save memory
 *                                      and time skipping work to set up the table for unused formats.
 *      flags						The following flags are allowed:
 *
 *				kvImageDoNotTile	Turns off internal multithreading. You may
 * 									wish to do this if you have your own
 *									multithreading scheme to avoid having the
 *									two interfere with one another.
 *      err                         A pointer to a vImage_Error. If err != NULL, on return, the memory pointed to by error
 *                                      will be overwritten with an appropriate error or kvImageNoError. It is sufficient to 
 *                                      simply check the LHS return value against NULL to determine whether the function succeeeded.
 *
 *  Return value:
 *      On return a valid vImage_MultidimensionalTable for use with vImageMultiDimensionalInterpolatedLookupTable_<fmt>
 *      if err is not NULL, the memory it points to will be overwritten with an appropriate error code. The 
 *      vImage_MultidimensionalTable will contain a copy of the data provided in tableData. It is safe to deallocate
 *      the input tableData immediately after this call returns.
 *
 *       
 *
 *  Errors:
 *      kvImageNoError                Success
 *      kvImageInvalidParameter       hint must be kvImageMDTableHint_16Q12 or kvImageMDTableHint_Float or both
 *		kvImageInvalidParameter       numSrcChannels and numDestChannels must be non-zero.
 *      kvImageNullPointerArgument    tableData and table_entries_per_dimension must not be NULL.
 *      kvImageUnknownFlagsBit        An illegal or unknown flag was passed to the function.
 *      kvImageMemoryAllocationError  Can not allocate memory for buffer.
 *      
 *  Use vImageMultidimensionalTable_Release to destroy the vImage_MultidimensionalTable when you are done with it. 
 *  The vImage_MultidimensionalTable may be reused. The table is immutable, thread-safe and may be used by many 
 *  vImageMultiDimensionalInterpolatedLookupTable_<fmt> calls concurrently so long as care is taken that it is not 
 *  freed while it is being used. To support multithreaded concurrent access, the table follows standard retain/release 
 *  semantics. On creation the table has a retain count of 1. When the reference count drops to 0, the table is destroyed.
 *
 */

typedef struct vImage_MultidimensionalTableData * vImage_MultidimensionalTable;
    
/* Hints to describe use of vImage_MultidimensionalTableData look up table. */
typedef enum
{
    kvImageMDTableHint_16Q12 = 1,           
    kvImageMDTableHint_Float = 2,
}vImageMDTableUsageHint;
    
vImage_MultidimensionalTable vImageMultidimensionalTable_Create( const uint16_t *tableData,
                                                                 uint32_t numSrcChannels,
                                                                 uint32_t numDestChannels,
                                                                 uint8_t table_entries_per_dimension[],   /* uint8_t[numSrcChannels] */
                                                                 vImageMDTableUsageHint hint,
                                                                 vImage_Flags flags,
                                                                 vImage_Error *err )
                                                                 VIMAGE_NON_NULL(1,4)
                                                                 __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
/*
 *  vImageMultidimensionalTable_Retain
 *  vImageMultidimensionalTable_Release
 *
 *  A vImage_MultidimensionalTable follows Retain/Release semantics. On creation, the table has  a retain count of 1. 
 *  If you call vImageMultidimensionalTable_Retain on it, the retain count is incremented. If you call 
 *  vImageMultidimensionalTable_Release on it, the retain count is decremented. When the retain count reaches 0,
 *  the object is destroyed. If any vImage function is called on an object whose reference count has already reached 
 *  0, behavior is undefined.
 *
 *  Parameters:
 *      table       A pointer to vImage_MultidimensionalTableData. If NULL, then nothing happens.
 *
 *  Errors:
 *      kvImageNoError                  Success
 */
vImage_Error vImageMultidimensionalTable_Retain( vImage_MultidimensionalTable table ) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
vImage_Error vImageMultidimensionalTable_Release( vImage_MultidimensionalTable table ) __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
/*
 *  vImageMultiDimensionalLookupTable_PlanarF
 *
 *  vImageMultiDimensionalLookupTable_<fmt> uses the input color channel values (treated as a N-dimensional coordinate)
 *  to index a N-dimensional lookup table to find a new color value, possibly in a new color space. The number of color channels
 *  in the destination image does not need to match the number of color channels in the source image. The table is created using
 *  vImageMultidimensionalTable_Create. 
 *
 *  In each dimension, the table must be of size (2**K[dimension])+1. The first entry corresponds to 0 and the last to 1.0. The rest
 *  correspond to steps at 2**-K[dimension]. (K[] is the table_entries_per_dimension[] array in vImageMultidimensionalTable_Create.)
 *  Thus a 17x17x17 3D lookup table defines the vertices that delineate a grid of 16x16x16 cubes, just as a ruler marked in 16ths of an
 *  inch has 17 marks between 0 and 1 inch, inclusive. (SI units are usually awkwardly subdivided by powers of 10, rather than powers of 2
 *  so we avoid them in this example. :-)    The most significant portion of the color channel values are used to index the multidimensional 
 *  grid. Usually there will be some fractional precision left over.  That is used to do a linear interpolation between nearby gridpoints 
 *  to find the value at that position. If the vImage_InterpolationMethod is kvImageFullInterpolation, then all 2**N (for N dimensions) 
 *  nearby gridpoints are considered. If the vImage_InterpolationMethod is kvImageHalfInterpolation, then the {0,0,0...}, {1,1,1...} verticies 
 *  along the gray axis are considered along with N-1 nearest other vertices. 
 *
 *      <insert formula here>
 *
 *  Parameters:
 *
 *      srcs                    An array of vImage_Buffers that reference the source image planes. The number of
 *                              such buffers is given by the numSrcChannels parameter passed to vImageMultidimensionalTable_Create.
 *
 *      dests                   An array of vImage_Buffers that reference the destination image planes. The number of
 *                              such buffers is given by the numDestChannels parameter passed to vImageMultidimensionalTable_Create.
 *
 *      tempBuffer              May be NULL. If non-NULL, this is a pointer to a region of memory that vImage can use as a 
 *                              scratch space for storing temporary data. The minimum size of the scratch space is obtained  
 *                              by calling the function with identical parameters and the kvImageGetTempBufferSize flag.
 *                              If vImageMultiDimensionalInterpolatedLookupTable_<fmt> can be called from multiple threads
 *                              simultaneously, the temp buffer must be different (or NULL) for each thread. 
 *
 *      table                   A valid table created by vImageMultidimensionalTable_Create
 *
 *      method                  either kvImageFullInterpolation or kvImageHalfInterpolation. See description above.
 *
 *      flags                   Must be kvImageNoFlags or one or more from this list:
 *                              
 *                                  kvImageDoNotTile            turn off internal multithreading. 
 *                                  kvImageGetTempBufferSize    Return the size of temp buffer. It may return 0. Do nothing.
 *
 *  Error Values:
 *		>= 0                        Minimum temp buffer size, if kvImageGetTempBufferSize was specified.
 *      kvImageNoError              Success
 *      kvImageNullPointerArgument  srcs, dests and table may not be NULL
 *      kvImageUnknownFlagsBit      An illegal or unknown flag was passed to the function.
 *      kvImageInvalidParameter     An unknown or illegal interpolation method was indicated
 *      kvImageInvalidParameter     The interpolation method doesn't have a table for the requested data type. 
 *                                      This happened because an incorrect vImageMDTableUsageHint was passed to
 *                                      vImageMultidimensionalTable_Create
 *      kvImageBufferSizeMismatch   Within srcs, all vImage_Buffers must have the same height and width.
 *									Similarly, within dests, all vImage_Buffers must have the same height and width.
 *									Otherwise this error is returned.
 *      kvImageBufferSizeMismatch   The src height and width must be greater than or equal to the destination height
 *									and width.
 *
 */

/* interpolation method for vImageMultiDimensionalInterpolatedLookupTable_<fmt>*/
typedef enum
{
    kvImageNoInterpolation = 0,             /* nearest neighbor. Fast but probably causes banding and will certainly quantize the histogram. */
    kvImageFullInterpolation = 1,           /* full linear interpolation */
    kvImageHalfInterpolation = 2            /* partial linear interpolation between vertices on gray axis and N-1 nearest vertices */
}vImage_InterpolationMethod;
    
vImage_Error vImageMultiDimensionalInterpolatedLookupTable_PlanarF( const vImage_Buffer srcs[],
                                                                    const vImage_Buffer dests[],
                                                                    void *tempBuffer,
                                                                    vImage_MultidimensionalTable table,
                                                                    vImage_InterpolationMethod method,
                                                                    vImage_Flags flags )
                                                                    VIMAGE_NON_NULL(1,2,4)
                                                                    __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );

/*
 *  vImageMultiDimensionalInterpolatedLookupTable_Planar16Q12
 *
 *  vImageMultiDimensionalInterpolatedLookupTable_Planar16Q12 is like vImageMultiDimensionalInterpolatedLookupTable_PlanarF
 *  except that it operates on signed fixed-point data. The 16Q12 format is a signed 16-bit fixed-point value with 12 fractional 
 *  bits, 3 non-fractional bits and one sign bit. It can represent values in the range (-8,8). However the table always describes 
 *  a region between [0,1] in each dimension. Values outside this range are clamped to the nearest in-range value by Manhattan 
 *  distance before indexing the table. See vImageConvert_Planar8to16Q12 and vImageConvert_16Q12toPlanar8 for more on the format.
 */
vImage_Error vImageMultiDimensionalInterpolatedLookupTable_Planar16Q12( const vImage_Buffer srcs[],
                                                                        const vImage_Buffer dests[],
                                                                        void *tempBuffer,
                                                                        vImage_MultidimensionalTable table,
                                                                        vImage_InterpolationMethod method, 
                                                                        vImage_Flags flags )
                                                                        VIMAGE_NON_NULL(1,2,4)
                                                                        __OSX_AVAILABLE_STARTING( __MAC_10_9, __IPHONE_7_0 );
    
    
    

#ifdef __cplusplus
}
#endif

#endif /* vImage_TRANSFORM_H */
