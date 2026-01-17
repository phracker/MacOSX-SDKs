/*
    File:       CoreMIDI/MIDIBluetoothConnection.h
 
    Contains:   Routines for connecting MIDI over Bluetooth LE.
 
    Copyright:  (c) 2022 by Apple Inc., all rights reserved.
 
    Bugs?:      For bug reports, consult the following page on
                the World Wide Web:
 
                    http://feedbackassistant.apple.com/
 
*/

#pragma once
#include <CoreFoundation/CoreFoundation.h>
#include <CoreMIDI/MIDIServices.h>

CF_ASSUME_NONNULL_BEGIN

//  -----------------------------------------------------------------------------
/*!
    @header MIDIBluetoothConnection.h

    The following methods are used to register connected Bluetooth Low Energy
    MIDI peripherals with CoreMIDI so that MIDI I/O becomes possible and to
	programmatically disconnect a BLE MIDI peripheral from CoreMIDI.
        
*/
//  -----------------------------------------------------------------------------


#ifdef __cplusplus
extern "C" {
#endif

// =================================================================================================

/*!
	@function       MIDIBluetoothDriverActivateAllConnections

	@abstract       Promotes all active CoreBluetooth connections to peripherals' Bluetooth LE MIDI
					service into online MIDI devices capable of I/O.
	 
	@result         An OSStatus result code.

	@discussion
		To programmatically establish a Bluetooth MIDI driver connection to a LE MIDI peripheral,
		the following steps must be completed in order.
		
		1. Using CoreBluetooth API, scan for the peripheral's advertised LE MIDI service.
		2. Using CoreBluetooth API, connect to the desired advertised peripheral.
		3. Upon successful connection, call MIDIBluetoothDriverActivateAllConnections.
		4. Using CoreMIDI API, confirm the peripheral's registration by locating its MIDIDeviceRef.
		5. If present, CoreMIDI now owns a connection the peripheral.
		6. Using CoreBluetooth API, disconnect from the peripheral now managed by CoreMIDI.
*/
extern OSStatus
MIDIBluetoothDriverActivateAllConnections(void) API_AVAILABLE(macos(13.0), ios(16.0));

/*!
	@function       MIDIBluetoothDriverDisconnect

	@abstract       Disconnects the Bluetooth MIDI driver from a BLE MIDI peripheral.
	
	@param          uuid
						A string representation of the CoreBluetooth UUI for a connected peripheral.
 
	@result         An OSStatus result code.

	@discussion
		If a CoreMIDI is connected to a BLE MIDI peripheral with the supplied UUID, it will disconnect.
*/
extern OSStatus
MIDIBluetoothDriverDisconnect(__nonnull CFStringRef uuid) API_AVAILABLE(macos(13.0), ios(16.0));

#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

