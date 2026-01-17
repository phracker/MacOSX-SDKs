/*
 	File:   	CoreMIDI/CoreMIDI.h
 
 	Contains:   Umbrella header for the CoreMIDI framework.
 
 	Copyright:  (c) 2000-2015 by Apple Inc., all rights reserved.
 
 	Bugs?:  	For bug reports, consult the following page on
 				the World Wide Web:
 
 					http://developer.apple.com/bugreporter/
 
*/

#ifndef __CoreMIDI_h__
#define __CoreMIDI_h__

#include <CoreMIDI/MIDIServices.h>
#include <CoreMIDI/MIDISetup.h>
#include <CoreMIDI/MIDIThruConnection.h>
#include <CoreMIDI/MIDIDriver.h>

#if TARGET_OS_IPHONE && __OBJC__
#import <CoreMIDI/MIDINetworkSession.h>
#endif

#endif
