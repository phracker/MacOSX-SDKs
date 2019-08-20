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
@class MTLFunctionConstantValues;


@protocol MTLArgumentEncoder;

typedef __autoreleasing MTLArgument *__nullable MTLAutoreleasedArgument;

typedef NS_ENUM(NSUInteger, MTLPatchType) {
    MTLPatchTypeNone = 0,
    MTLPatchTypeTriangle = 1,
    MTLPatchTypeQuad = 2,
} API_AVAILABLE(macos(10.12), ios(10.0));

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLVertexAttribute : NSObject

@property (readonly) NSString                    *name;
@property (readonly) NSUInteger                   attributeIndex;
@property (readonly) MTLDataType                  attributeType API_AVAILABLE(macos(10.11), ios(8.3));
@property (readonly, getter=isActive) BOOL        active;
@property (readonly, getter=isPatchData) BOOL              patchData API_AVAILABLE(macos(10.12), ios(10.0));
@property (readonly, getter=isPatchControlPointData) BOOL  patchControlPointData API_AVAILABLE(macos(10.12), ios(10.0));

@end

MTL_EXPORT API_AVAILABLE(macos(10.12), ios(10.0))
@interface MTLAttribute : NSObject

@property (readonly) NSString                    *name;
@property (readonly) NSUInteger                   attributeIndex;
@property (readonly) MTLDataType                  attributeType;
@property (readonly, getter=isActive) BOOL        active;
@property (readonly, getter=isPatchData) BOOL              patchData API_AVAILABLE(macos(10.12), ios(10.0));
@property (readonly, getter=isPatchControlPointData) BOOL  patchControlPointData API_AVAILABLE(macos(10.12), ios(10.0));

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
} API_AVAILABLE(macos(10.11), ios(8.0));


/*!
 @interface MTLFunctionConstant
 @abstract describe an uberShader constant used by the function
 */
MTL_EXPORT API_AVAILABLE(macos(10.12), ios(10.0))
@interface MTLFunctionConstant : NSObject

@property (readonly) NSString *name;
@property (readonly) MTLDataType type;
@property (readonly) NSUInteger index;
@property (readonly) BOOL required;

@end

/*!
 @protocol MTLFunction
 @abstract A handle to to intermediate code used as inputs for either a MTLComputePipelineState or a MTLRenderPipelineState.
 @discussion MTLFunction is a single vertex shader, fragment shader, or compute function.  A Function can only be used with the device that it was created against.
*/
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLFunction <NSObject>

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label  API_AVAILABLE(macos(10.12), ios(10.0));

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

/*!
 @property patchType
 @abstract Returns the patch type. MTLPatchTypeNone if it is not a post tessellation vertex shader.
 */
@property (readonly) MTLPatchType patchType API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @property patchControlPointCount
 @abstract Returns the number of patch control points if it was specified in the shader. Returns -1 if it
 was not specified.
 */
@property (readonly) NSInteger patchControlPointCount API_AVAILABLE(macos(10.12), ios(10.0));

@property (nullable, readonly) NSArray <MTLVertexAttribute *> *vertexAttributes;

/*!
 @property stageInputAttributes
 @abstract Returns an array describing the attributes
 */
@property (nullable, readonly) NSArray <MTLAttribute *> *stageInputAttributes API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @property name
 @abstract The name of the function in the shading language.
 */
@property (readonly) NSString *name;

/*!
 @property functionConstantsDictionary
 @abstract A dictionary containing information about all function contents, keyed by the constant names.
 */
@property (readonly) NSDictionary<NSString *, MTLFunctionConstant *> *functionConstantsDictionary API_AVAILABLE(macos(10.12), ios(10.0));


/*!
 * @method newArgumentEncoderWithBufferIndex:
 * @abstract Creates an argument encoder which will encode arguments matching the layout of the argument buffer at the given bind point index.
 */
- (id <MTLArgumentEncoder>)newArgumentEncoderWithBufferIndex:(NSUInteger)bufferIndex API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 * @method newArgumentEncoderWithBufferIndex:
 * @abstract Creates an argument encoder which will encode arguments matching the layout of the argument buffer at the given bind point index.
 */
- (id <MTLArgumentEncoder>)newArgumentEncoderWithBufferIndex:(NSUInteger)bufferIndex
                                                                  reflection:(MTLAutoreleasedArgument * __nullable)reflection API_AVAILABLE(macos(10.13), ios(11.0));


@end

typedef NS_ENUM(NSUInteger, MTLLanguageVersion) {

    MTLLanguageVersion1_0 API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos) = (1 << 16),
    MTLLanguageVersion1_1 API_AVAILABLE(macos(10.11), ios(9.0)) = (1 << 16) + 1,
    MTLLanguageVersion1_2 API_AVAILABLE(macos(10.12), ios(10.0)) = (1 << 16) + 2,
    MTLLanguageVersion2_0 API_AVAILABLE(macos(10.13), ios(11.0)) = (2 << 16),
    MTLLanguageVersion2_1 API_AVAILABLE(macos(10.14), ios(12.0)) = (2 << 16) + 1,
} API_AVAILABLE(macos(10.11), ios(9.0));

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
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
@property (readwrite, nonatomic) MTLLanguageVersion languageVersion API_AVAILABLE(macos(10.11), ios(9.0));

@end

/*!
 @constant MTLLibraryErrorDomain
 @abstract NSErrors raised when creating a library.
 */
API_AVAILABLE(macos(10.11), ios(8.0))
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
    MTLLibraryErrorFunctionNotFound API_AVAILABLE(macos(10.12), ios(10.0)) = 5,
    MTLLibraryErrorFileNotFound API_AVAILABLE(macos(10.12), ios(10.0)) = 6,
} API_AVAILABLE(macos(10.11), ios(8.0));

API_AVAILABLE(macos(10.11), ios(8.0))
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
 @method newFunctionWithName:constantValues:error:
 @abstract Returns a pointer to a function object obtained by applying the constant values to the named function.
 @discussion This method will call the compiler. Use newFunctionWithName:constantValues:completionHandler: to
 avoid waiting on the compiler.
 */
- (nullable id <MTLFunction>) newFunctionWithName:(NSString *)name constantValues:(MTLFunctionConstantValues *)constantValues
					error:(__autoreleasing NSError **)error API_AVAILABLE(macos(10.12), ios(10.0));


/*!
 @method newFunctionWithName:constantValues:completionHandler:
 @abstract Returns a pointer to a function object obtained by applying the constant values to the named function.
 @discussion This method is asynchronous since it is will call the compiler.
 */
- (void) newFunctionWithName:(NSString *)name constantValues:(MTLFunctionConstantValues *)constantValues
			completionHandler:(void (^)(id<MTLFunction> __nullable function, NSError* error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0));

/*!
 @property functionNames
 @abstract The array contains NSString objects, with the name of each function in library.
 */
@property (readonly) NSArray <NSString *> *functionNames;

@end
NS_ASSUME_NONNULL_END
