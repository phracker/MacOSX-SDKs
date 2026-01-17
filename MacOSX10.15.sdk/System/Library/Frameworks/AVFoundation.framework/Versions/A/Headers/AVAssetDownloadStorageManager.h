/*
	File:  AVAssetDownloadStorageManager.h
 
	Framework:  AVFoundation
 
	Copyright 2017 Apple Inc. All rights reserved.
 
 */

/*!
	@class		AVAssetDownloadStorageManager
 
	@abstract	An AVAssetDownloadStorageManager manages the policy for automatic purging of downloaded AVAssets. The policy is vended as  AVAssetDownloadStorageManagementPolicy object.

	@discussion	When a storage management policy needs to be set on an asset, sharedDownloadStorageManager singleton needs to be fetched. 
 				The new policy can then be set by using setStorageManagementPolicy and the location of the downloaded asset.
 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAssetDownloadStorageManagementPolicy;
/*!
	@group		AVAssetDownloadedAssetEvictionPriority string constants
	@brief		Used by AVAssetDownloadStorageManagementPolicy.
*/
typedef NSString *AVAssetDownloadedAssetEvictionPriority NS_STRING_ENUM API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@enum		AVAssetDownloadedAssetEvictionPriority
	@abstract	These constants represents the eviction priority of downloaded assets.

	@constant	AVAssetDownloadedAssetEvictionPriorityImportant
				Used to mark assets with the highest priority. They will be the last to be purged.
	@constant	AVAssetDownloadedAssetEvictionPriorityDefault
				Used to mark assets have the default priority. They will be the first to be purged.
*/
AVF_EXPORT AVAssetDownloadedAssetEvictionPriority const AVAssetDownloadedAssetEvictionPriorityImportant				API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos, watchos);
AVF_EXPORT AVAssetDownloadedAssetEvictionPriority const AVAssetDownloadedAssetEvictionPriorityDefault				API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos, watchos);

API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface AVAssetDownloadStorageManager : NSObject

/*!
	@method		sharedDownloadStorageManager
	@abstract	returns singleton instance.
*/
+ (AVAssetDownloadStorageManager *)sharedDownloadStorageManager;

/*!
	@method		setStorageManagementPolicy: forURL
	@abstract	Sets the policy for asset with disk backing at downloadStorageURL.
	@param		downloadStorageURL
 				The location of downloaded asset.
*/
- (void)setStorageManagementPolicy:(AVAssetDownloadStorageManagementPolicy *)storageManagementPolicy forURL:(NSURL *)downloadStorageURL;

/*!
	@method		storageManagementPolicyForURL:downloadStorageURL
	@abstract	Returns the storage management policy for asset downloaded at downloadStorageURL.
                This may be nil if a storageManagementPolicy was never set on the downloaded asset.
	@param		downloadStorageURL
				The location of downloaded asset.
*/
- (nullable AVAssetDownloadStorageManagementPolicy *)storageManagementPolicyForURL:(NSURL *)downloadStorageURL;

@end

/*!
	@class		AVAssetDownloadStorageManagementPolicy
 
	@abstract	A class to inform the system of a policy for automatic purging of downloaded AVAssets.
 
	@discussion	System will put in best-effort to evict all the assets based on expirationDate before evicting based on priority.
 */
@class AVAssetDownloadStorageManagementPolicyInternal;

API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface AVAssetDownloadStorageManagementPolicy : NSObject <NSCopying, NSMutableCopying> {
@private
	AVAssetDownloadStorageManagementPolicyInternal    *_storageManagementPolicy;
}

/*
 	@property	priority
 	@abstract	Indicates the eviction priority of downloaded asset.
 	@discussion	Assets with default priority will be purged first before assets with higher priorities.
				In case this is not set, default priority is used.
 */
@property (nonatomic, readonly, copy) AVAssetDownloadedAssetEvictionPriority priority;

/*
 	@property	expirationDate
 	@abstract	Returns the expiration date of asset.
 */
@property (nonatomic, readonly, copy) NSDate *expirationDate;

@end
/*!
	@class		AVMutableAssetDownloadStorageManagementPolicy
 
	@abstract	A mutable subclass of AVAssetDownloadStorageManagementPolicy.
 
	@discussion	System will put in best-effort to evict all the assets based on expirationDate before evicting based on priority.
 */
API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface AVMutableAssetDownloadStorageManagementPolicy : AVAssetDownloadStorageManagementPolicy

/*
	@property	priority
	@abstract	Indicates the eviction priority of downloaded asset.
	@discussion	Assets with default priority will be purged first before assets with higher priorities.
 				In case this is not set, default priority is used.
 */
@property (nonatomic, copy) AVAssetDownloadedAssetEvictionPriority priority;

/*
	@property	expirationDate
 	@abstract	Returns the expiration date of asset.
 */
@property (nonatomic, copy) NSDate *expirationDate;

@end

NS_ASSUME_NONNULL_END
