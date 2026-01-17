//
//  MLModel+MLModelCompilation.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <CoreML/MLModel.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLModel (MLModelCompilation)
 *
 * Class with utilties for performing .mlmodel compilation
 */
@interface MLModel (MLModelCompilation)

/*!
 * Compile a .mlmodel for this device
 *
 * @param modelURL URL file path to .mlmodel file you wish to compile
 * @param error Any errors are surfaced here
 *
 * @returns a URL to the compiled .mlmodelc directory if successful
 * The model is compiled to a temporary location on disk
 * You must move the compiled model to a permanent location if you wish to keep it
 *
 * @discussion The returned model can be loaded using:
 * @code
 * [MLModel modelWithContentsOfURL:error:]
 * @endcode
 *
 */
+ (nullable NSURL *)compileModelAtURL:(NSURL *)modelURL
                                error:(NSError **)error
                                API_UNAVAILABLE(watchos)
                                API_DEPRECATED("Use the asynchronous interface compileModelAtURL:completionHandler:error: instead.",
                                macos(10.13, API_TO_BE_DEPRECATED), ios(11.0, API_TO_BE_DEPRECATED), tvos(11.0, API_TO_BE_DEPRECATED));

/*!
 * Compile a .mlmodel or .mlpackage for this device. Perform the compilation asynchronously.
 *
 * @param modelURL URL file path to .mlmodel file you wish to compile
 * @param handler When the model compilation completes successfully  the completion handler is invoked with a valid URL to the compiled .mlmodelc directory.
 * On failure, signified by nil  compiledModelURL, the NSError object is populated.
 *
 * @discussion The model is compiled to a temporary location in the file system. You must move the compiled model to a permanent location if you wish to keep it. Then the model can be loaded using the returned URL:
 * @code
 * [MLModel modelWithContentsOfURL:error:]
 * @endcode
 *
 */

+ (void)compileModelAtURL:(NSURL *)modelURL
        completionHandler:(void (^)(NSURL * _Nullable compiledModelURL, NSError * _Nullable error))handler
        API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
        NS_REFINED_FOR_SWIFT NS_SWIFT_ASYNC_NAME(compileModel(at:));

@end

NS_ASSUME_NONNULL_END
