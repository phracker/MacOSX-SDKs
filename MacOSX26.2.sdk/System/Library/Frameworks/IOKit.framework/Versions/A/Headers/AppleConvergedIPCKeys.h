//
//  AppleConvergedIPCKeys.h
//  AppleConvergedIPC
//
//  Created by Karan Sanghi on 12/16/13.
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#ifndef __AppleConvergedIPCKeys__
#define __AppleConvergedIPCKeys__

enum
{
	kACIPCUserClientOpen,
	kACIPCUserClientClose,
	kACIPCUserClientWrite,
	kACIPCUserClientRead,
	kACIPCUserClientSendImage,
	kACIPCUserClientRegisterRead,
	kACIPCUserClientAbortChannel,
	kACIPCUserClientStartChannel,
	kACIPCUserClientNumCommands
} AppleConvergedIPCUserClientCommands;

enum
{
	kACIPCControlUserClientOpen,
	kACIPCControlUserClientClose,
	kACIPCControlUserClientLogRead,
	kACIPCControlUserClientLoggerTune,
	kACIPCControlUserClientForceDoorbellFlush,
	kACIPCControlUserClientNumCommands
} AppleConvergedIPCControlUserClientCommands;

enum
{
	kACIPCLoggerKnobSubsystemInterface
} AppleConvergedIPCLoggerKnobSubsystems;

enum
{
	kACIPCLoggerKnobInterfaceFlavorLogBinary
} AppleConvergedIPCLoggerKnobInterfaceFlavors;

#endif	/* __AppleConvergedIPCKeys__ */
