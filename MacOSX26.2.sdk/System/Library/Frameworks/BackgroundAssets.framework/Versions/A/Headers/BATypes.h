//
//  BATypes.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BackgroundAssets/BackgroundAssets.h>

NS_ASSUME_NONNULL_BEGIN

/// @abstract The content request type used in the BADownloaderExtension.
/// @constant BAContentRequestInstall  Content is being requested because the application was installed.
/// @constant BAContentRequestUpdate Content is being requested because the application was updated.
/// @constant BAContentRequestPeriodic Content is being requested because the system is asking for updated content for your application.
typedef NS_ENUM(NSInteger, BAContentRequest) {
    BAContentRequestInstall = 1,
    BAContentRequestUpdate,
    BAContentRequestPeriodic,
};

NS_ASSUME_NONNULL_END
