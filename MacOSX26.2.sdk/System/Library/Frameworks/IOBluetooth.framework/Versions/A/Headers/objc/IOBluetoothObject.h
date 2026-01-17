//
//  IOBluetoothObject.h
//  IOBluetoothFamily
//
//  Copyright (c) 2002-2012, 2023 Apple Inc. All rights reserved.
//

#if __OBJC__

#import <Foundation/Foundation.h>

#import <IOKit/IOKitLib.h>

API_UNAVAILABLE(ios, watchos, tvos)
@interface IOBluetoothObject : NSObject <NSCopying>
{
    io_service_t		mIOService;
    io_connect_t		mIOConnection;
    
    io_iterator_t		mIONotification;
}

@end

#define kBluetoothTargetDoesNotRespondToCallbackExceptionName	@"BluetoothTargetDoesNotRespondToCallbackException"

#endif // __OBJC__
