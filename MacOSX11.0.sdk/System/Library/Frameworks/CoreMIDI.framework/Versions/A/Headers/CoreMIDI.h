/*
 	File:   	CoreMIDI/CoreMIDI.h
 
 	Contains:   Umbrella header for the CoreMIDI framework.
 
 	Copyright:  (c) 2000-2020 by Apple Inc., all rights reserved.
 
 	Bugs?:  	For bug reports, consult the following page on
 				the World Wide Web:
 
 					http://feedbackassistant.apple.com/
 
*/

#ifndef __CoreMIDI_h__
#define __CoreMIDI_h__

#include <CoreMIDI/MIDIServices.h>
#include <CoreMIDI/MIDISetup.h>
#include <CoreMIDI/MIDIThruConnection.h>
#include <CoreMIDI/MIDIDriver.h>
#include <CoreMIDI/MIDIMessages.h>

#if __OBJC__
#import <CoreMIDI/MIDINetworkSession.h>
#endif

#if __OBJC2__
#import <CoreMIDI/MIDICapabilityInquiry.h>
#endif

#endif
