// Basic Neural Network Subroutines (BNNS)

#ifndef __BNNS_HEADER__
#define __BNNS_HEADER__

#include <stddef.h>
#include <stdint.h>

// Availability
#if __has_include( <Availability.h> )
#include <Availability.h>
#else
#define __API_AVAILABLE(...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Nullability
#if __has_feature(assume_nonnull)
  _Pragma("clang assume_nonnull begin")
#else
#define _Null_unspecified
#define _Nullable
#define _Nonnull
#endif

/*

  Logging

  When a parameter is invalid or an internal error occurs, an error message will be logged.
  Some combinations of parameters may not be supported. In that case, an info message will be logged.

*/

/*!

@abstract Type for user-provided memory allocation function

@discussion Should conform to posix_memalign(), and must be compatible with the memory deallocation function.

@param memptr Pointer to a <tt>(void *)</tt> receiving the address of the allocated memory.
@param alignment Requested alignment, must be a power of 2, and at least <tt>sizeof(void *)</tt>.
@param size Number of bytes to allocate.

@return 0 on success, or an error value on failure.

*/
typedef int (*BNNSAlloc)(void * _Nullable * _Nullable memptr, size_t alignment, size_t size);

/*!

@abstract Type for user-provided memory deallocation function

@discussion Should conform to free(), and must be compatible with the memory allocation function.

@param ptr Address of the block to release.

*/
typedef void (*BNNSFree)(void * _Null_unspecified ptr);

#pragma mark - Constants

/*!
 
@abstract Storage data type

@constant BNNSDataTypeFloatBit
Common bit to floating point types, this constant is not a valid type

@constant BNNSDataTypeFloat16
16-bit half precision floating point

@constant BNNSDataTypeFloat32
32-bit single precision floating point

@constant BNNSDataTypeIntBit
Common bit to signed integer types, this constant is not a valid type

@constant BNNSDataTypeInt8
8-bit signed integer

@constant BNNSDataTypeInt16
16-bit signed integer

@constant BNNSDataTypeIn32
32-bit signed integer

@constant BNNSDataTypeUIntBit
Common bit to unsigned integer types, this constant is not a valid type (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

@constant BNNSDataTypeUInt8
8-bit unsigned integer (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

@constant BNNSDataTypeUInt16
16-bit unsigned integer (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

@constant BNNSDataTypeUIn32
32-bit unsigned integer (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

@constant BNNSDataTypeIndexedBit
Common bit to indexed floating point types, this constant is not a valid type

@constant BNNSDataTypeIndexed8
8-bit unsigned indices into a floating point conversion table (256 values)

*/
typedef enum {

  BNNSDataTypeFloatBit            = 0x10000,
  BNNSDataTypeFloat16             = BNNSDataTypeFloatBit | 16,
  BNNSDataTypeFloat32             = BNNSDataTypeFloatBit | 32,

  BNNSDataTypeIntBit              = 0x20000,
  BNNSDataTypeInt8                = BNNSDataTypeIntBit | 8,
  BNNSDataTypeInt16               = BNNSDataTypeIntBit | 16,
  BNNSDataTypeInt32               = BNNSDataTypeIntBit | 32,

  // The UInt fields are available in macOS 10.13, iOS 11, tvOS 11, watchOS 4
  BNNSDataTypeUIntBit             = 0x40000,
  BNNSDataTypeUInt8               = BNNSDataTypeUIntBit | 8,
  BNNSDataTypeUInt16              = BNNSDataTypeUIntBit | 16,
  BNNSDataTypeUInt32              = BNNSDataTypeUIntBit | 32,

  BNNSDataTypeIndexedBit          = 0x80000,
  BNNSDataTypeIndexed8            = BNNSDataTypeIndexedBit | 8,

} BNNSDataType;

/*!

@abstract Pooling layer function

@discussion
In the definitions below, the input sample is <tt>X<sub>i</sub></tt> and has <tt>N</tt> elements.

@constant BNNSPoolingFunctionMax
max(X<sub>i</sub>)

@constant BNNSPoolingFunctionAverage
&sum;<sub>i</sub> X<sub>i</sub> / N

*/
typedef enum {

  BNNSPoolingFunctionMax          = 0,
  BNNSPoolingFunctionAverage      = 1,

} BNNSPoolingFunction;

/*!

@abstract Activation layer function

@constant BNNSActivationFunctionIdentity
x

@constant BNNSActivationFunctionRectifiedLinear
0 if x<0, and x if x>=0

@constant BNNSActivationFunctionLeakyRectifiedLinear
alpha*x if x<0, and x if x>=0

@constant BNNSActivationFunctionSigmoid
sigmoid(x)

@constant BNNSActivationFunctionTanh
tanh(x)

@constant BNNSActivationFunctionScaledTanh
alpha*tanh(x*beta)

@constant BNNSActivationFunctionAbs
abs(x) (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

@constant BNNSActivationFunctionLinear
alpha*x (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

@constant BNNSActivationFunctionClamp
min(max(x, alpha), beta) (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

@constant BNNSActivationFunctionIntegerLinearSaturate
Saturate<output_type>((iscale * x + ioffset) >> ishift)
This is an arithmetic shift, preserving sign. (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

@constant BNNSActivationFunctionIntegerLinearSaturatePerChannel
Saturate<output_type>((iscale_per_channel[channel] * x + ioffset_per_channel[channel]) >> ishift_per_channel[channel]) for each channel
This is an arithmetic shift, preserving sign. (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

@constant BNNSActivationFunctionSoftmax
softmax(x)_i = exp(x_i) / ( sum_i exp(x_i) )
(macOS 10.13, iOS 11, tvOS 11, watchOS 4)
 
*/
typedef enum {

  BNNSActivationFunctionIdentity                        =  0,
  BNNSActivationFunctionRectifiedLinear                 =  1,
  BNNSActivationFunctionLeakyRectifiedLinear            =  2,
  BNNSActivationFunctionSigmoid                         =  3,
  BNNSActivationFunctionTanh                            =  4,
  BNNSActivationFunctionScaledTanh                      =  5,
  BNNSActivationFunctionAbs                             =  6,

  // The following fields are available in macOS 10.13, iOS 11, tvOS 11, watchOS 4

  BNNSActivationFunctionLinear                          =  7,
  BNNSActivationFunctionClamp                           =  8,
  BNNSActivationFunctionIntegerLinearSaturate           =  9,
  BNNSActivationFunctionIntegerLinearSaturatePerChannel = 10,
  BNNSActivationFunctionSoftmax                         = 11,

} BNNSActivationFunction;

/*!

@abstract Filter creation flags

@constant BNNSFlagsUseClientPtr

Instructs the filter to keep the pointers provided by the client at creation time (weights, bias), and work directly from this data. In that
case, the client must ensure these pointers remain valid through the entire lifetime of the filter.

If not set, the filter creation function must allocate buffers, and keep an internal copy of the data. In that case, the client doesn't have
to keep the pointers valid after the filter is created.

*/
typedef enum {

  BNNSFlagsUseClientPtr                         = 0x0001,

} BNNSFlags;

#pragma mark - Data formats

/*!

@abstract Image stack descriptor

@discussion
An image stack is a sequence of images with the same width and height. Each image in the sequence is called a channel.
For example, a RGB image will be stored as three separate channels. A pixel has only one scalar value, stored using the type
described by <tt>data_type</tt>.

Pixel <tt>P(c,x,y)</tt> at position <tt>(x,y)</tt> in channel <tt>c</tt> is stored in
<tt>data[x + row_stride * y + image_stride * c]</tt>, with
<tt>x=0..width-1</tt>,
<tt>y=0..height-1</tt>,
<tt>c=0..channels-1</tt>. <tt>row_stride &geq; width</tt>, <tt>image_stride &geq; row_stride * height</tt>.

Int<n> types are converted to floating point using float Y = DATA_SCALE * (float)X + DATA_BIAS, and back to integer using Int<n> X = convert_and_saturate(Y / DATA_SCALE - DATA_BIAS)

@field width Image width
@field height Image height
@field channels Number of images in stack
@field row_stride Increment (in values) between image rows
@field image_stride Increment (in values) between image channels
@field data_type Storage data type for image values. INDEXED data types are not allowed here.
@field data_scale Conversion scale for image values, used for INT,UINT data types only
@field data_bias Conversion bias for image values, used for INT,UINT data types only

*/
typedef struct {

  size_t width;
  size_t height;
  size_t channels;
  size_t row_stride;
  size_t image_stride;
  
  BNNSDataType data_type;
  float        data_scale;
  float        data_bias;

} BNNSImageStackDescriptor;

/*!

@abstract Vector format descriptor

@discussion
Represents a vector of dimension <tt>size</tt>.
Each vector element is a scalar value, stored using the type specified in <tt>data_type</tt>.

Component <tt>V(i)</tt> at index <tt>i</tt> is stored in <tt>data[i]</tt>, with <tt>i=0..size-1</tt>.

Int<n> types are converted to floating point using float Y = DATA_SCALE * (float)X + DATA_BIAS, and back to integer using Int<n> X = convert_and_saturate(Y / DATA_SCALE - DATA_BIAS)

@field size Vector dimension
@field data_type Storage data type for vector values. INDEXED data types are not allowed here.
@field data_scale Conversion scale for vector values, used for INT,UINT data types only
@field data_bias Conversion bias for vector values, used for INT,UINT data types only

*/
typedef struct {

  size_t size;
  
  BNNSDataType data_type;
  float        data_scale;
  float        data_bias;

} BNNSVectorDescriptor;

#pragma mark - Layer parameters

/*!

@abstract Common layer parameters

@discussion Int<n> types are converted to floating point using float Y = DATA_SCALE * (float)X + DATA_BIAS, and back to integer using Int<n> X = convert_and_saturate(Y / DATA_SCALE - DATA_BIAS)

@field data Pointer to layer values (weights, bias), layout and size are specific to each layer
@field data_type Storage data type for the values stored in <tt>data</tt>
@field data_scale Conversion scale for values, used for INT data types only, ignored for INDEXED and FLOAT data types
@field data_bias Conversion bias for values, used for INT data types only, ignored for INDEXED and FLOAT data types
@field data_table Conversion table (256 values) for indexed floating point data, used for INDEXED data types only

*/
typedef struct {

  const void * _Nullable  data;
  BNNSDataType            data_type;
  float                   data_scale;
  float                   data_bias;
  const float * _Nullable data_table;

} BNNSLayerData;

/*!

@abstract Common activation function parameters

@field function Activation function
@field alpha Parameter to the activation function
@field beta Parameter to the activation function

@field iscale Scale for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)
@field ioffset Offset for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)
@field ishift Shift for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

@field iscale_per_channel Scale per channel for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)
@field ioffset_per_channel Offset per channel for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)
@field ishift_per_channel Shift per channel for integer functions (macOS 10.13, iOS 11, tvOS 11, watchOS 4)

*/
typedef struct {

  BNNSActivationFunction function;
  float alpha;
  float beta;

  // The following fields are available in macOS 10.13, iOS 11, tvOS 11, watchOS 4

  int32_t iscale;
  int32_t ioffset;
  int32_t ishift;

  const int32_t * _Nullable iscale_per_channel;
  const int32_t * _Nullable ioffset_per_channel;
  const int32_t * _Nullable ishift_per_channel;

} BNNSActivation;

/*!

@abstract Convolution parameters

@discussion
The convolution product Output = Weights &times; Input is defined as follows.  Pixel <tt>Output(o,x,y)</tt> of the output image stack receives:
<br><tt>Output(o,x,y) = &sum;<sub>i,kx,ky</sub> Weight(o,i,kx,ky) * Input(i,x_stride * x + kx,y_stride * y + ky)</tt> with
<tt>kx=0..k_width-1</tt>, <tt>ky=0..k_height-1</tt>,
<tt>i=0..in_channels-1</tt>, <tt>o=0..out_channels-1</tt>,
<tt>x=0..out_width-1</tt>, <tt>y=0..out_height-1</tt>.

After the convolution is applied, the output is updated with bias and/or activation function as follows:
<br><tt>Output(o,x,y) = ActivationFunction( Bias(o) + Output(o,x,y) )</tt>.

Dimensions must satisfy:
<br><tt>in_width + 2 * x_padding = x_stride * ( out_width - 1 ) + k_width</tt>, and <tt>in_height + 2 * y_padding = y_stride * ( out_height - 1 ) + k_height</tt>.
<br>A common use case is <tt>x_stride=y_stride=1</tt>, and <tt>x_padding=y_padding=0</tt>. In that case, <tt>in_width = out_width + k_width - 1</tt>, and <tt>in_height = out_height + k_height - 1</tt>.

Padding is a border of 0 values virtually added to the input image.

Coefficient <tt>Weight(o,i,kx,ky)</tt> for output image <tt>o=0..out_channels-1</tt>, input image <tt>i=0..in_channels-1</tt>, and kernel point (kx,ky) is
stored in <tt>weights[kx + k_width * (ky + k_height * (i + in_channels * o))]</tt>, where
the convolution kernel dimensions are <tt>k_width,k_height</tt>.

@field x_stride X increment in the input image
@field y_stride Y increment in the input image
@field x_padding X padding, virtual 0 values added to the left and right of each channel of the input stack
@field y_padding Y padding, virtual 0 values added to the top and bottom of each channel of the input stack
@field k_width Width of the convolution kernel
@field k_height Height of the convolution kernel
@field in_channels Number of input channels
@field out_channels Number of output channels

@field weights Convolution weights, <tt>k_width * k_height * in_channels * out_channels</tt> values, with the layout described in the discussion
@field bias Layer bias, <tt>out_channels</tt> values, one for each output channel
@field activation Layer activation function

*/
typedef struct {

  size_t x_stride;
  size_t y_stride;
  size_t x_padding;
  size_t y_padding;
  size_t k_width;
  size_t k_height;
  size_t in_channels;
  size_t out_channels;

  BNNSLayerData weights;
  BNNSLayerData bias;
  BNNSActivation activation;
  
} BNNSConvolutionLayerParameters;

/*!

@abstract Fully connected layer parameters

@discussion
The output of a fully connected layer is the result of a matrix-vector product.
The output vector is defined by <tt>Output(o) = &sum;<sub>i</sub> Weight(o,i) * Input(i)</tt> for <tt>i=0..in_size-1</tt>, <tt>o=0..out_size-1</tt>.

Coefficient <tt>Weight(o,i)</tt> is stored in <tt>weights[i + o * in_size]</tt>.

After the matrix product, the output is updated with bias and/or activation function as follows:
<br><tt>Output(o) = ActivationFunction( Bias(o) + Output(o) )</tt>.

@field in_size Size of input vector
@field out_size Size of output vector

@field weights Matrix coefficients, <tt>in_size * out_size</tt> values, with the layout described in the discussion
@field bias Layer bias, <tt>out_size</tt> values, one for each output component
@field activation Layer activation function

*/
typedef struct {

  size_t in_size;
  size_t out_size;

  BNNSLayerData weights;
  BNNSLayerData bias;
  BNNSActivation activation;
  
} BNNSFullyConnectedLayerParameters;

/*!

@abstract Pooling layer parameters

@discussion
The pooling is defined as follows.  Pixel <tt>Output(o,x,y)</tt> of the output image stack receives:
<br><tt>Output(o,x,y) = PoolingFunction( Input(o,x_stride * x + kx,y_stride * y + ky) )</tt> with <tt>kx=0..k_width-1</tt>, <tt>ky=0..k_height-1</tt>,
<tt>o=0..out_channels-1</tt>, <tt>x=0..out_width-1</tt>, <tt>y=0..out_height-1</tt>.

After the pooling is applied, the output is updated with bias and/or activation function as follows:
<br><tt>Output(o,x,y) = ActivationFunction( Bias(o) + Output(o,x,y) )</tt>.

Dimensions must satisfy:
<br><tt>in_width + 2 * x_padding >= x_stride * (out_width - 1) + 1</tt>,
<br><tt>iin_height + 2 * y_padding >= p->y_stride * (o->height - 1) + 1</tt>.

Padding is a border of 0 values virtually added to the input image.

@field x_stride X increment in the input image
@field y_stride Y increment in the input image
@field x_padding X padding, virtual 0 values added to the left and right of each channel of the input stack
@field y_padding Y padding, virtual 0 values added to the top and bottom of each channel of the input stack
@field k_width Width of the pooling kernel
@field k_height Height of the pooling kernel
@field in_channels Number of input channels
@field out_channels Number of output channels

@field pooling_function Selects the pooling function to apply to each sample
@field bias Layer bias, <tt>out_channels</tt> values
@field activation Layer activation function

*/
typedef struct {

  size_t x_stride;
  size_t y_stride;
  size_t x_padding;
  size_t y_padding;
  size_t k_width;
  size_t k_height;
  size_t in_channels;
  size_t out_channels;
  
  BNNSPoolingFunction pooling_function;
  BNNSLayerData bias;
  BNNSActivation activation;

} BNNSPoolingLayerParameters;

#pragma mark - Filter parameters

/*!

@abstract Common filter parameters

@field flags
A logical OR of zero or more values from BNNSFlags.

@field n_threads
If 0, use the best number of threads for the current machine.
Otherwise, specifies the number of worker threads to execute.

@field alloc_memory
If not NULL, will be called to allocate memory. Otherwise, posix_memalign() will be called.
Must be compatible with the free_memory function.

@field free_memory
If not NULL, will be called to deallocate memory. Otherwise, free() will be called.
Must be compatible with the alloc_memory function.

*/
typedef struct {

  uint32_t flags;
  size_t n_threads;
  BNNSAlloc _Nullable alloc_memory;
  BNNSFree _Nullable free_memory;

} BNNSFilterParameters;

#pragma mark - Filter creation

/*!

@abstract Filter object

*/
typedef void * _Nullable BNNSFilter;

/*!

@abstract Create a convolution layer filter

@discussion
Creates a filter applying the convolution described in <tt>layer_params</tt>.
Some combinations of the parameters may not be supported, in which case the call will fail.

@param in_desc Input image stack descriptor
@param out_desc Output image stack descriptor
@param layer_params Layer parameters and weights
@param filter_params Filter runtime parameters, may be NULL for default parameters

@return A new non-NULL filter on success, and NULL on failure.

*/
BNNSFilter BNNSFilterCreateConvolutionLayer(const BNNSImageStackDescriptor * in_desc,
                                            const BNNSImageStackDescriptor * out_desc,
                                            const BNNSConvolutionLayerParameters * layer_params,
                                            const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!

@abstract Create a fully connected layer filter

@discussion
Creates a filter applying the fully connected layer described in <tt>layer_params</tt>.
Some combinations of the parameters may not be supported, in which case the call will fail.

@param in_desc Input vector descriptor
@param out_desc Output vector descriptor
@param layer_params Layer parameters and weights
@param filter_params Filter runtime parameters, may be NULL for default parameters

@return A new non-NULL filter on success, and NULL on failure.

*/
BNNSFilter BNNSFilterCreateFullyConnectedLayer(const BNNSVectorDescriptor * in_desc,
                                               const BNNSVectorDescriptor * out_desc,
                                               const BNNSFullyConnectedLayerParameters * layer_params,
                                               const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!

@abstract Create a pooling layer filter

@discussion
Creates a filter applying the pooling layer described in <tt>layer_params</tt>

Some combinations of the parameters may not be supported, in which case the call will fail.

@param in_desc Input image stack descriptor
@param out_desc Output image stack descriptor
@param layer_params Layer parameters and weights
@param filter_params Filter runtime parameters, may be NULL for default parameters

@return A new non-NULL filter on success, and NULL on failure.

*/
BNNSFilter BNNSFilterCreatePoolingLayer(const BNNSImageStackDescriptor * in_desc,
                                        const BNNSImageStackDescriptor * out_desc,
                                        const BNNSPoolingLayerParameters * layer_params,
                                        const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!

@abstract Create a vector conversion/activation layer filter

@discussion
Creates a filter applying the given activation function and conversions to vectors. Input and output vectors must have the same size.

@param in_desc Input vector descriptor
@param out_desc Output vector descriptor
@param activation Activation function to apply and its parameters
@param filter_params Filter runtime parameters, may be NULL for default parameters

@return A new non-NULL filter on success, and NULL on failure.

*/
BNNSFilter BNNSFilterCreateVectorActivationLayer(const BNNSVectorDescriptor * in_desc,
                                                 const BNNSVectorDescriptor * out_desc,
                                                 const BNNSActivation * activation,
                                                 const BNNSFilterParameters * _Nullable filter_params)
__API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!

@abstract Apply a filter

@param filter Filter to apply
@param in Pointer to the input data
@param out Pointer to the output data

@return 0 on success, and -1 on failure.
*/
int BNNSFilterApply(BNNSFilter filter,const void * in,void * out)
__API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!

@abstract Apply a filter to a several pairs of (input, output) data

@discussion
The filter is applied for each of the <tt>batch_size</tt> inputs, and produces <tt>batch_size</tt> outputs.
<tt>in</tt> (resp. <tt>out</tt>) is expected to point to <tt>batch_size</tt> times the input (resp. output) object size defined when the filter was created.

@param filter Filter to apply
@param batch_size Number of (input, output) pairs to process
@param in Pointer to the input data
@param in_stride Increment (in values) between inputs
@param out Pointer to the output data
@param out_stride Increment (in values) between outputs

@return 0 on success, and -1 on failure.
*/

int BNNSFilterApplyBatch(BNNSFilter filter,size_t batch_size,const void * in,size_t in_stride,void * out,size_t out_stride)
__API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!

@abstract Destroy filter

@discussion Releases all resources allocated for this filter.

@param filter Filter to destroy
*/
void BNNSFilterDestroy(BNNSFilter filter)
__API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

// Availability
#if !__has_include( <Availability.h> )
#undef __API_AVAILABLE
#endif

// Nullability
#if __has_feature(assume_nonnull)
  _Pragma("clang assume_nonnull end")
#else
#undef _Nullable
#undef _Null_unspecified
#undef _Nonnull
#endif

#ifdef __cplusplus
}
#endif

#endif // __BNNS_HEADER__
