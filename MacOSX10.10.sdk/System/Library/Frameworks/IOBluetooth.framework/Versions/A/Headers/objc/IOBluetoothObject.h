//
//  IOBluetoothObject.h
//  IOBluetoothFamily
//
//  Copyright (c) 2002-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <IOKit/IOKitLib.h>

@interface IOBluetoothObject : NSObject <NSCopying>
{
    io_service_t		mIOService;
    io_connect_t		mIOConnection;
    
    io_iterator_t		mIONotification;
}

@end

#define kBluetoothTargetDoesNotRespondToCallbackExceptionName	@"BluetoothTargetDoesNotRespondToCallbackException"
