//
//  MLWritable.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CoreML/CoreML.h>

NS_ASSUME_NONNULL_BEGIN

ML_EXPORT
API_AVAILABLE(macos(10.15), ios(13.0))
@protocol MLWritable <NSObject>

// Writes the model to disk and returns YES if the write is successful.
- (BOOL)writeToURL:(NSURL *)url error:(NSError * _Nullable * _Nullable)error;

@end

NS_ASSUME_NONNULL_END

