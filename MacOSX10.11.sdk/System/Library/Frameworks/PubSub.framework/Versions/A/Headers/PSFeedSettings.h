/*
    PSFeedSettings.h
    PubSub

    Copyright 2006, Apple Computer, Inc.  All rights reserved.
*/


#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSArray;


#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

/*!
    @defined    PSFeedSettingsIntervalDefault
    @discussion Specifies that the per-client default interval should be used. 
*/
#define PSFeedSettingsIntervalDefault 0.0

/*!
    @defined    PSFeedSettingsIntervalNever
    @discussion Specifies that refreshing or expiring should never occur automatically.
                As a result, the application or user must force an update manually by calling the update method.
*/
#define PSFeedSettingsIntervalNever -1.0

/*!
    @defined    PSFeedSettingsUnlimitedSize
    @discussion Specifies no limit on enclosure sizes. 
*/
#define PSFeedSettingsUnlimitedSize 0

/*!
    @defined    PSFeedSettingsAllTypes
    @discussion Specifies all MIME types.
*/
#define PSFeedSettingsAllTypes nil


/*!
    @class      PSFeedSettings
    @discussion A <code>PSFeedSettings</code> object contains settings pertaining to retrieving subscribed feeds. 
                You can access and modify all feed settings, which include refresh and expiration intervals, and enclosure 
                download policies. Initially all the values are set to default settings, meaning that they inherit from 
                the PSClient's own feed settings object, but you can override those by putting explicit 
                values in the feed's feed settings object.

                Globally, there can be multiple feed subscriptions with different settings for the same URL. For example, 
                two clients may subscribe to the same feed URL but with different refresh intervals or enclosure policies. 
                In this case the PubSub Agent uses the most liberal policy: the minimum refresh interval, the maximum 
                enclosure size limit, and so on. It is not recommended that you subclass <code>PSFeedSettings</code>.
    @attribute 	Framework /System/Library/Frameworks/PubSub.framework
    @seealso 	//apple_ref/doc/uid/TP40004945 Publication Subscription Programming Guide
*/

NS_DEPRECATED(10_5, 10_9, NA, NA)
@interface PSFeedSettings : NSObject
{
    @private
    id _internal;
}


/*!
    @method     defaultFeedSettings
    @abstract   Returns a settings object initialized with the default values for a feed.
*/
+ (PSFeedSettings*) defaultFeedSettings;

/*!
    @method     defaultClientSettings
    @abstract   Returns a settings object initialized with the default values for a client.
    @discussion The returned object can be used to determine the actual default values of
                settings such as the refresh interval.
*/
+ (PSFeedSettings*) defaultClientSettings;


/*!
    @property   refreshInterval
    @abstract   The desired time interval that the PubSub Agent will poll for updates.
*/
@property NSTimeInterval refreshInterval;


/*!
    @property expirationInterval
    @abstract The amount of time before an entry is deleted.
*/
@property NSTimeInterval expirationInterval;


/*!
    @property     refreshesInBackground
    @abstract 	  A Boolean value that determines whether or not the PubSub Agent will refresh the feed when the client application is not running.
    @discussion   Returns YES if the PubSub Agent will refresh the feed in the background, NO if it will not.
*/
@property BOOL refreshesInBackground;


/*!
    @property     downloadsEnclosures
    @abstract     A Boolean value that indicates whether or not the PubSub Agent will automatically download enclosures associated with new entries.
    @discussion   Returns YES if the PubSub Agent will automatically download enclosures, NO if it will not. By default,
                  enclosures are not automatically downloaded.
*/
@property BOOL downloadsEnclosures;


/*!
    @property  maxEnclosureSize
    @abstract  The maximum size, in bytes, of an enclosure to be downloaded automatically.
*/
@property double maxEnclosureSize;


/*!
    @property   enclosureTypes
    @abstract   An array of string objects that contain the enclosure MIME types to be downloaded automatically.
    @discussion A wildcard can be used as a MIME subtype, for example, <code>image/ *</code>.
*/
@property (retain) NSArray* enclosureTypes;


@end

#endif
