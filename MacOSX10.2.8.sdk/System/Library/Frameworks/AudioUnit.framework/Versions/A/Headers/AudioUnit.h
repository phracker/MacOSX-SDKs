/*
     File:      AudioUnit/AudioUnit.h
 
     Contains:  Umbrella include for AudioUnit definitions
 
     Version:   Technology: Mac OS X
 
     Copyright: (c) 2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __AUDIOUNIT__
#define __AUDIOUNIT__

// This is the main AudioUnit specification
#include <AudioUnit/AUComponent.h>
#include <AudioUnit/AudioOutputUnit.h>
#include <AudioUnit/MusicDevice.h>

#include <AudioUnit/AudioUnitProperties.h>
#include <AudioUnit/AudioUnitParameters.h>

#include <AudioUnit/AudioUnitCarbonView.h>

#include <AudioUnit/AudioCodec.h>

// This file relies on AUComponent.h
// and contains the differences of Version 1 API
#include <AudioUnit/AUNTComponent.h>

#endif /* __AUDIOUNIT__ */

