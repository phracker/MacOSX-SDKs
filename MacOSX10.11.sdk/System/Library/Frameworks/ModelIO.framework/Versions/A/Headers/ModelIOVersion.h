//
//  ModelIOVersion.h
// @framework ModelIO
//
// @copyright (c) 2015 Apple. All rights reserved.
//

#ifndef ModelIO_ModelIOVersion_h
#define ModelIO_ModelIOVersion_h

// MMRRNNNP
// Major, Revision, miNor, Point
#define __MODELIO_1_4_0 1040000
#define __MODELIO_1_4_1 1040010
#define __MODELIO_1_4_2 1040020
#define __MODELIO_1_4_3 1040030
#define __MODELIO_1_4_4 1040040
#define __MODELIO_1_4_5 1040050
#define __MODELIO_1_4_6 1040060
#define __MODELIO_1_4_7 1040070
#define __MODELIO_1_4_8 1040080
#define __MODELIO_1_4_9 1040090
#define __MODELIO_1_4_10 1040100
#define __MODELIO_1_5_0 1050000
#define __MODELIO_1_5_1 1050010

#import <ModelIO/ModelIOExports.h>

#define MODELIO_VERSION_NUMBER __MODELIO_1_4_10
#define MODELIO_VERSION_STRING "1.4.10"

//! Project version number for ModelIO.
MDL_EXPORT double ModelIOVersionNumber;

//! Project version string for ModelIO.
MDL_EXPORT const unsigned char ModelIOVersionString[];

#endif
