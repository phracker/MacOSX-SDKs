//
//  VZDirectoryShare.h
//  Virtualization
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a directory share.
 @discussion
    A directory share defines how host directories get exposed to a virtual machine guest.

    VZDirectoryShare should not be instantiated directly.
    One of its subclasses like VZSingleDirectoryShare or VZMultipleDirectoryShare should be used instead.

 @see VZSingleDirectoryShare
 @see VZMultipleDirectoryShare
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZDirectoryShare : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
