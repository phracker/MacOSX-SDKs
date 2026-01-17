//
//  MXCallStackTree.h
//  MetricKit
//
//  Copyright (c) 2019 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@class         MXCallStackTree
@abstract      A data class that encapsulates call stack trees vended by MetricKit.
@discussion    You should use the JSONRepresentation API to generate human readable call stack trees for symbolication off device.
*/
API_AVAILABLE(ios(14.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXCallStackTree : NSObject <NSSecureCoding>

/*!
 @method        JSONRepresentation
 @abstract      Convenience method to return a JSON representation of this callstack tree.
 @discussion    The JSON structure of MXCallStackTree is organized into individual groups of call stacks. Individual call stacks contain stack frames, which consist of information needed to symbolicate the frame off device. This includes binary image name, binary UUID, offset in binary text segment, address, and sample count (for stack trees that contain temporally sampled data.)
 @discussion    MXCallStackTrees can be organized into a single callstack for the entire application, or broken up into callstacks associated with individual threads.
 @result        An NSData object containing the JSON representation
 */
- (NSData *)JSONRepresentation;

@end

NS_ASSUME_NONNULL_END
