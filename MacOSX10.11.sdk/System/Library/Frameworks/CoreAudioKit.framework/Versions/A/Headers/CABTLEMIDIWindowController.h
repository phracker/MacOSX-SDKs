/*
	File:      CABTLEMIDIWindowController.h
 
	Contains:  Class definition for a window controller that displays nearby Bluetooth-based MIDI peripherals. The user can select one of those peripherals and pair it with their mac. Additionally, the user can advertise the mac as a Bluetooth-based MIDI peripheral.
 
	Copyright: (c) 2015 by Apple, Inc. All rights reserved.
 
	Bugs?:      For bug reports, consult the following page on the World Wide Web:
 
	http://developer.apple.com/bugreporter/
 */

#import <Cocoa/Cocoa.h>

@class CABTLEMIDIImpl;

/*!
 @class CABTLEMIDIWindowController
 @abstract  A window controller object that can present a window that displays nearby Bluetooth-based MIDI peripherals. The user can select one of those peripherals and pair it with their mac. Additionally, the user can advertise the mac as a Bluetooth-based MIDI peripheral.
 
 @discussion To use this class, create an instance of the CABTLEMIDIWindowController, initialize it, and call showWindow: to display the UI.
 */
@interface CABTLEMIDIWindowController : NSWindowController {
@private
    CABTLEMIDIImpl     *_impl;
}
@end
