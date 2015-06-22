//
//  MTLLibrary.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLResource.h>
#import <Metal/MTLArgument.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;
@protocol MTLFunction;
@protocol MTLLibrary;
@class MTLCompileOptions;

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLVertexAttribute : NSObject
 
@property (nullable, readonly) NSString *name;
@property (readonly) NSUInteger                   attributeIndex;
@property (readonly) MTLDataType                  attributeType NS_AVAILABLE(10_11, 8_3);
@property (readonly, getter=isActive) BOOL        active;
@end

/*!
 @enum MTLFunctionType
 @abstract An identifier for a top-level Metal function.
 @discussion Each location in the API where a program is used requires a function written for that specific usage.
 
 @constant MTLFunctionTypeVertex
 A vertex shader, usable for a MTLRenderPipelineState.
 
 @constant MTLFunctionTypeFragment
 A fragment shader, usable for a MTLRenderPipelineState.
 
 @constant MTLFunctionTypeKernel
 A compute kernel, usable to create a MTLComputePipelineState.
 */
typedef NS_ENUM(NSUInteger, MTLFunctionType) {
    MTLFunctionTypeVertex = 1,
    MTLFunctionTypeFragment = 2,
    MTLFunctionTypeKernel = 3,
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 @protocol MTLFunction
 @abstract A handle to to intermediate code used as inputs for either a MTLComputePipelineState or a MTLRenderPipelineState.
 @discussion MTLFunction is a single vertex shader, fragment shader, or compute function.  A Function can only be used with the device that it was created against.
*/
NS_AVAILABLE(10_11, 8_0)
@protocol MTLFunction <NSObject>

/*!
 @property device
 @abstract The device this resource was created against.  This resource can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property functionType
 @abstract The overall kind of entry point: compute, vertex, or fragment.
 */
@property (readonly) MTLFunctionType functionType;

@property (nullable, readonly) NSArray <MTLVertexAttribute *> *vertexAttributes;

/*!
 @property name
 @abstract The name of the function in the shading language.
 */
@property (readonly) NSString *name;

@end

typedef NS_ENUM(NSUInteger, MTLLanguageVersion) {

    MTLLanguageVersion1_0 NS_ENUM_AVAILABLE(NA, 9_0) = (1 << 16),
    MTLLanguageVersion1_1 = (1 << 16) + 1,
} NS_ENUM_AVAILABLE(10_11, 9_0);


NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLCompileOptions : NSObject <NSCopying>

// Pre-processor options

/*!
 @property preprocessorNames
 @abstract List of preprocessor macros to consider to when compiling this program. Specified as key value pairs, using a NSDictionary. The keys must be NSString objects and values can be either NSString or NSNumber objects.
 @discussion The default value is nil.
 */
@property (nullable, readwrite, copy, nonatomic) NSDictionary <NSString *, NSObject *> *preprocessorMacros;

// Math intrinsics options

/*!
 @property fastMathEnabled
 @abstract If YES, enables the compiler to perform optimizations for floating-point arithmetic that may violate the IEEE 754 standard. It also enables the high precision variant of math functions for single precision floating-point scalar and vector types. fastMathEnabled defaults to YES.
 */
@property (readwrite, nonatomic) BOOL fastMathEnabled;

/*!
 @property languageVersion
 @abstract set the metal language version used to interpret the source.
 */
@property (readwrite, nonatomic) MTLLanguageVersion languageVersion NS_AVAILABLE(10_11, 9_0);

@end

/*!
 @constant MTLLibraryErrorDomain
 @abstract NSErrors raised when creating a library.
 */
NS_AVAILABLE(10_11, 8_0)
MTL_EXTERN NSString *const MTLLibraryErrorDomain;

/*!
 @enum MTLLibraryError
 @abstract NSErrors raised when creating a library.
 */
typedef NS_ENUM(NSUInteger, MTLLibraryError) {
    MTLLibraryErrorUnsupported      = 1,
    MTLLibraryErrorInternal         = 2,
    MTLLibraryErrorCompileFailure   = 3,
    MTLLibraryErrorCompileWarning   = 4,
} NS_ENUM_AVAILABLE(10_11, 8_0);

MTL_EXTERN NSString *const MTLRenderPipelineErrorDomain;

/*!
 @enum MTLRenderPipelineError
 @abstract NSErrors raised when creating a pipeline or kernel.
 */
typedef NS_ENUM(NSUInteger, MTLRenderPipelineError) {
    MTLRenderPipelineErrorInternal          = 1,    
    MTLRenderPipelineErrorUnsupported       = 2,
    MTLRenderPipelineErrorInvalidInput      = 3,
} NS_ENUM_AVAILABLE(10_11, 8_0);


NS_AVAILABLE(10_11, 8_0)
@protocol MTLLibrary <NSObject>

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;

/*!
 @property device
 @abstract The device this resource was created against.  This resource can only be used with this device.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @method newFunctionWithName
 @abstract Returns a pointer to a function object, return nil if the function is not found in the library.
 */
- (nullable id <MTLFunction>) newFunctionWithName:(NSString *)functionName;

/*!
 @property functionNames
 @abstract The array contains NSString objects, with the name of each function in library.
 */
@property (readonly) NSArray <NSString *> *functionNames;

@end
NS_ASSUME_NONNULL_END
