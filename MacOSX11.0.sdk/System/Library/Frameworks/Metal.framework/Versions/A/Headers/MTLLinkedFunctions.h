//
//  MTLLinkedFunctions.h
//  Metal
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>


#import <Foundation/Foundation.h>


@protocol MTLFunction;

MTL_EXTERN API_AVAILABLE(macos(11.0), ios(14.0))
@interface MTLLinkedFunctions : NSObject <NSCopying>

/*!
 @method linkedFunctions
 @abstract Create an autoreleased MTLLinkedFunctions object.
 */
+ (nonnull MTLLinkedFunctions *)linkedFunctions;

/*!
* @property functions
* @abstract The array of functions to be AIR linked.
*/
@property (readwrite, nonatomic, copy, nullable) NSArray<id<MTLFunction>> *functions;


/*!
* @property binaryFunctions
* @abstract The array of functions compiled to binary to be linked.
*/
@property (readwrite, nonatomic, copy, nullable) NSArray<id<MTLFunction>> *binaryFunctions;

/*!
* @property groups
* @abstract Groups of functions, grouped to match callsites in the shader code.
*/
@property (readwrite, nonatomic, copy, nullable) NSDictionary<NSString*, NSArray<id<MTLFunction>>*> *groups;

@end

