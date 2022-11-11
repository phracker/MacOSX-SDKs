//
//  HMHomeManager.h
//  HomeKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAddAccessoryRequest;
@class HMHome;

@protocol HMHomeManagerDelegate;

/*!
 *  @abstract   The home data authorization status of the client process.
 *
 *  @constant   HMHomeManagerAuthorizationStatusDetermined  Indicates the user has not yet made a choice regarding the access of the application.
 *  @constant   HMHomeManagerAuthorizationStatusRestricted      Access to home data is currently restricted by the system.
 *  @constant   HMHomeManagerAuthorizationStatusAuthorized      The application is authorized to access home data.
 */
typedef NS_OPTIONS( NSUInteger, HMHomeManagerAuthorizationStatus )
{
    HMHomeManagerAuthorizationStatusDetermined  = (1 << 0),
    HMHomeManagerAuthorizationStatusRestricted  = (1 << 1),
    HMHomeManagerAuthorizationStatusAuthorized  = (1 << 2),
} API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

/*!
 *  @abstract   Manages collection of one or more homes.
 *
 *  @discussion This class is responsible for managing a collection of homes.
 */
HM_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMHomeManager : NSObject

/*!
 *  @abstract   Delegate that receives updates on the collection of homes.
 */
@property (weak, nonatomic, nullable) id<HMHomeManagerDelegate> delegate;

/*!
 *  @abstract   The current authorization status of the application.
 *  @discussion The authorization is managed by the system, there is no need to explicitly request authorization.
 */
@property (readonly) HMHomeManagerAuthorizationStatus authorizationStatus API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0)) API_UNAVAILABLE(macos);

/*!
 *  @abstract   The primary home for this collection.
 */
@property (readonly, strong, nonatomic, nullable) HMHome *primaryHome;

/*!
 *  @abstract   Array of HMHome objects that represents the homes associated with the home manager.
 *
 *  @discussion When a new home manager is created, this array is initialized as an empty array. It is
 *              not guaranteed to be filled with the list of homes, represented as HMHome objects,
 *              until the homeManagerDidUpdateHomes: delegate method has been invoked.
 */
@property (readonly, copy, nonatomic) NSArray<HMHome *> *homes;

/*!
 *  @abstract   This method is used to change the primary home.
 *
 *  @param      home        New primary home.
 *
 *  @param      completion  Block that is invoked once the request is processed.
 *                          The NSError provides more information on the status of the request, error
 *                          will be nil on success.
 */
- (void)updatePrimaryHome:(HMHome *)home completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

/*!
 *  @abstract   Adds a new home to the collection.
 *
 *  @param      homeName    Name of the  home to create and add to the collection.
 *
 *  @param      completion  Block that is invoked once the request is processed.
 *                          The NSError provides more information on the status of the request, error
 *                          will be nil on success.
 *
 */
- (void)addHomeWithName:(NSString *)homeName completionHandler:(void (^)(HMHome * __nullable home, NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos) NS_SWIFT_ASYNC_NAME(addHome(named:));

/*!
 *  @abstract   Removes an existing home from the collection.
 *
 *  @param      home        Home object that needs to be removed from the collection.
 *
 *  @param      completion  Block that is invoked once the request is processed.
 *                          The NSError provides more information on the status of the request, error
 *                          will be nil on success.
 */
- (void)removeHome:(HMHome *)home completionHandler:(void (^)(NSError * __nullable error))completion API_UNAVAILABLE(watchos, tvos);

@end

/*!
 *  @abstract   This delegate receives updates on homes being managed via the home manager.
 */
API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@protocol HMHomeManagerDelegate <NSObject>

@optional

/*!
 *  @abstract   Informs the delegate a change in authorization status has occurred.
 *
 *  @param      manager     Sender of this message.
 *  @param      status      The updated authorization status.
 */
- (void)homeManager:(HMHomeManager *)manager didUpdateAuthorizationStatus:(HMHomeManagerAuthorizationStatus)status API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0)) API_UNAVAILABLE(macos);

/*!
 *  @abstract   Informs the delegate when homes configured by the user have been detected by the system.
 *
 *  @discussion This delegate method is also invoked to inform an application of significant changes
 *              to the home configuration. Applications should use this as a cue to invalidate their
 *              current references to HomeKit objects and refresh their views with the new list of homes.
 *
 *  @param      manager     Sender of this message.
 */
- (void)homeManagerDidUpdateHomes:(HMHomeManager *)manager;

/*!
 *  @abstract   Informs the delegate when the primary home is modified.
 *
 *  @param      manager     Sender of this message.
 */
- (void)homeManagerDidUpdatePrimaryHome:(HMHomeManager *)manager;

/*!
 *  @abstract   Informs the delegate when a new home is added.
 *
 *  @param      manager     Sender of this message.
 *
 *  @param      home        New home that was added.
 */
- (void)homeManager:(HMHomeManager *)manager didAddHome:(HMHome *)home;

/*!
 *  @abstract   Informs the delegate when an existing home is removed.
 *
 *  @param      manager     Sender of this message.
 *
 *  @param      home        Home that was removed.
 */
- (void)homeManager:(HMHomeManager *)manager didRemoveHome:(HMHome *)home;

/*!
 *  @abstract   Informs the delegate an accessory needs to be added to the home by using one of the
 *        HMAccessorySetupPayload factory methods on the request parameter.
 *
 *  @param      manager     Sender of this message.
 *
 *  @param      request     Information for the add accessory request.
 */
- (void)homeManager:(HMHomeManager *)manager didReceiveAddAccessoryRequest:(HMAddAccessoryRequest *)request API_DEPRECATED("No longer supported", ios(13.0, 15.0)) API_UNAVAILABLE(ios, macos, watchos, tvos, macCatalyst) NS_SWIFT_NAME(homeManager(_:didReceiveAddAccessoryRequest:));

@end

NS_ASSUME_NONNULL_END
