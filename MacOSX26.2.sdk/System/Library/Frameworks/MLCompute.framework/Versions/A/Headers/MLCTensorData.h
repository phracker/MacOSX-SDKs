//
//  MLCTensorData.h
//  MLCompute
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MLCompute/MLCDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCTensorData
    @discussion An object to encapsulate memory to be used as tensor data
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCTensorData : NSObject

/*! @property   bytes
    @abstract   Pointer to memory that contains or will be used for tensor data
 */
@property (readonly, nonatomic) void *bytes;

/*! @property   length
    @abstract   The size in bytes of the tensor data
 */
@property (readonly, nonatomic) NSUInteger length;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @abstract   Creates a data object that holds a given number of bytes from a given buffer.
    @note       The returned object will not take ownership of the \p bytes pointer and thus will not free it on deallocation.
    @param      bytes   A buffer containing data for the new object.
    @param      length  The number of bytes to hold from \p bytes. This value must not exceed the length of \p bytes.
    @return     A new \p MLCTensorData object.
 */
+ (instancetype)dataWithBytesNoCopy:(void *)bytes
                             length:(NSUInteger)length;

/*! @abstract   Creates a data object that holds a given number of bytes from a given buffer.
    @note       The returned object will not take ownership of the \p bytes pointer and thus will not free it on deallocation. The underlying bytes in the return object should not be mutated.
    @param      bytes   A buffer containing data for the new object.
    @param      length  The number of bytes to hold from \p bytes. This value must not exceed the length of \p bytes.
    @return     A new \p MLCTensorData object.
 */
+ (instancetype)dataWithImmutableBytesNoCopy:(const void *)bytes
                                      length:(NSUInteger)length;

/*! @absract          Creates a data object that holds a given number of bytes from a given buffer. with a custom deallocator block.
    @param     bytes   A buffer containing data for the new object.
    @param     length  The number of bytes to hold from \p bytes. This value must not exceed the length of \p bytes.
    @param     deallocator A block to invoke when the resulting object is deallocated.
    @return    A new  \p MLCTensorData object.
 */
+ (instancetype)dataWithBytesNoCopy:(void *)bytes
                             length:(NSUInteger)length
                        deallocator:(void (^)(void *bytes, NSUInteger length))deallocator
    MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5));

@end

NS_ASSUME_NONNULL_END
