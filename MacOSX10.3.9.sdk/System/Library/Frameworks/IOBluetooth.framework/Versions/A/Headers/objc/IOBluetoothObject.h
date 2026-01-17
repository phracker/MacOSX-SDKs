//
//  IOBluetoothObject.h
//  IOBluetoothFamily
//
//  Created by Eric Brown on Tue Jun 11 2002.
//  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <IOKit/IOKitLib.h>

@interface IOBluetoothObject : NSObject
{
    io_service_t		mIOService;
    io_connect_t		mIOConnection;
    
    io_iterator_t		mIONotification;
}

@end

#define kBluetoothTargetDoesNotRespondToCallbackExceptionName	@"BluetoothTargetDoesNotRespondToCallbackException"
