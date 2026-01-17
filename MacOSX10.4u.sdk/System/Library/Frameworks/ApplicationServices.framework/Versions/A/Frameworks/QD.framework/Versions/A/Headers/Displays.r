/*
     File:       Displays.r
 
     Contains:   Display Manager Interfaces.
 
     Version:    Quickdraw-192.24~58
 
     Copyright:  © 1993-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __DISPLAYS_R__
#define __DISPLAYS_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#define kDisplayGestaltDisplayCommunicationAttr  'comm'
#define kDisplayGestaltForbidI2CMask 	0x01				/*  Some displays have firmware problems if they get I2C communication.  If this bit is set, then I2C communication is forbidden */
#define kDisplayGestaltUseI2CPowerMask 	0x02				/*  Some displays require I2C power settings (most use DPMS). */
#define kDisplayGestaltCalibratorAttr 	'cali'
#define kDisplayGestaltBrightnessAffectsGammaMask  0x01		/*  Used by default calibrator (should we show brightness panel)  */
#define kDisplayGestaltViewAngleAffectsGammaMask  0x02		/*  Currently not used by color sync */


#endif /* __DISPLAYS_R__ */

