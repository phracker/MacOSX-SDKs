//
//  WCSessionFile.h
//  WatchConnectivity
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** Contains file information, such as the file's location and optional user info
 */
NS_CLASS_AVAILABLE_IOS(9.0)
@interface WCSessionFile : NSObject
@property (nonatomic, readonly) NSURL *fileURL;
@property (nonatomic, copy, readonly, nullable) NSDictionary<NSString *, id> *metadata;
@end

/** Used to track a file being transferred.
 */
NS_CLASS_AVAILABLE_IOS(9.0)
@interface WCSessionFileTransfer : NSObject
@property (nonatomic, readonly) WCSessionFile *file;
@property (nonatomic, readonly) NSProgress *progress API_AVAILABLE(ios(12.0), watchos(5.0));
@property (nonatomic, readonly, getter=isTransferring) BOOL transferring;
- (void)cancel;
@end

NS_ASSUME_NONNULL_END
