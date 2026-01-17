//
//  IOUSBHost.h
//  IOUSBHost
//
//  Copyright © 2019 Apple. All rights reserved.
//

extern double              IOUSBHostVersionNumber;
extern const unsigned char IOUSBHostVersionString[];

#import <Foundation/Foundation.h>
#import <IOUSBHost/AppleUSBDescriptorParsing.h>
#import <IOUSBHost/IOUSBHostDefinitions.h>
#import <IOUSBHost/IOUSBHostObject.h>
#import <IOUSBHost/IOUSBHostDevice.h>
#import <IOUSBHost/IOUSBHostInterface.h>
#import <IOUSBHost/IOUSBHostIOSource.h>
#import <IOUSBHost/IOUSBHostPipe.h>
#import <IOUSBHost/IOUSBHostStream.h>
#import <IOUSBHost/IOUSBHostControllerInterface.h>
#import <IOUSBHost/IOUSBHostCIControllerStateMachine.h>
#import <IOUSBHost/IOUSBHostCIPortStateMachine.h>
#import <IOUSBHost/IOUSBHostCIDeviceStateMachine.h>
#import <IOUSBHost/IOUSBHostCIEndpointStateMachine.h>
#import <IOUSBHost/IOUSBHostControllerInterfaceHelpers.h>
