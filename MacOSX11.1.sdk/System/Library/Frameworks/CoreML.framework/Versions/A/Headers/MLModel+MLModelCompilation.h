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
 * You must move the compiled model to a permenant location if you wish to keep it
 *
 * @discussion the returned model can be loaded using:
 * @code
 * [MLModel modelWithContentsOfURL:error:]
 * @endcode
 *
 */
+ (nullable NSURL *)compileModelAtURL:(NSURL *)modelURL
                                error:(NSError **)error
                                API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) __WATCHOS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
