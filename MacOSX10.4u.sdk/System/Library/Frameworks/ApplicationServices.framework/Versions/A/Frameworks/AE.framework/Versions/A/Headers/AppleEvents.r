/*
     File:       AppleEvents.r
 
     Contains:   AppleEvent Package Interfaces.
 
     Version:    AppleEvents-316.2~623
 
     Copyright:  © 1989-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __APPLEEVENTS_R__
#define __APPLEEVENTS_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

															/*  Keywords for Apple event parameters  */
#define keyDirectObject 				'----'
#define keyErrorNumber 					'errn'
#define keyErrorString 					'errs'
#define keyProcessSerialNumber 			'psn '				/*  Keywords for special handlers  */
#define keyPreDispatch 					'phac'				/*  preHandler accessor call  */
#define keySelectProc 					'selh'				/*  more selector call  */
															/*  Keyword for recording  */
#define keyAERecorderCount 				'recr'				/*  available only in vers 1.0.1 and greater  */
															/*  Keyword for version information  */
#define keyAEVersion 					'vers'				/*  available only in vers 1.0.1 and greater  */

/* Event Class */
#define kCoreEventClass 				'aevt'
/* Event IDÕs */
#define kAEOpenApplication 				'oapp'
#define kAEOpenDocuments 				'odoc'
#define kAEPrintDocuments 				'pdoc'
#define kAEOpenContents 				'ocon'
#define kAEQuitApplication 				'quit'
#define kAEAnswer 						'ansr'
#define kAEApplicationDied 				'obit'
#define kAEShowPreferences 				'pref'				/*  sent by Mac OS X when the user chooses the Preferences item  */
#define kAEAutosaveNow 					'asav'				/*  sent by Mac OS X when it is advisable to autosave all the user's documents with uncommitted changes.  */

/* Constants for recording */
#define kAEStartRecording 				'reca'				/*  available only in vers 1.0.1 and greater  */
#define kAEStopRecording 				'recc'				/*  available only in vers 1.0.1 and greater  */
#define kAENotifyStartRecording 		'rec1'				/*  available only in vers 1.0.1 and greater  */
#define kAENotifyStopRecording 			'rec0'				/*  available only in vers 1.0.1 and greater  */
#define kAENotifyRecording 				'recr'				/*  available only in vers 1.0.1 and greater  */




/*--------------------------aedt ¥ Apple Events Template---------------------------------*/
/* Resource definition used for associating a value with an apple event */
/* This really only useful for general dispatching */

type 'aedt' {
    wide array {
    unsigned longint;   /* Event Class  */
    unsigned longint;   /* Event ID     */
    unsigned longint;   /* Value    */
    };
};

#endif /* __APPLEEVENTS_R__ */

