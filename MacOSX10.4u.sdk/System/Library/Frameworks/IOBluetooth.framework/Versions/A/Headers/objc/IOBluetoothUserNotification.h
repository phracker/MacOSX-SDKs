#import <Foundation/NSObject.h>

/*!
    @class IOBluetoothUserNotification
    @abstract Represents a registered notification.
    @discussion When registering for various notifications in the system, an IOBluetoothUserNotification
				object is returned.  To unregister from the notification, call -unregister on the
				IOBluetoothUserNotification object.  Once -unregister is called, the object will no
				longer be valid.
*/

@interface IOBluetoothUserNotification : NSObject
{
}

/*!
    @method unregister
    @abstract Called to unregister the target notification.
    @discussion Once this method has completed, the target IOBluetoothUserNotification will
				no longer be valid.
*/

- (void)unregister;

@end

