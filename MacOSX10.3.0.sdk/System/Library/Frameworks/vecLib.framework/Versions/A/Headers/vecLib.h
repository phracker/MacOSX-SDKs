/*
     File:       vecLib/vecLib.h
 
     Contains:   Master include for vecLib framework
 
     Version:    vecLib-151~21
 
     Copyright:  © 2000-2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VECLIB__
#define __VECLIB__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#ifndef __VECLIBTYPES__
#include <vecLib/vecLibTypes.h>
#endif

#ifndef __VBASICOPS__
#include <vecLib/vBasicOps.h>
#endif

#ifndef __VBIGNUM__
#include <vecLib/vBigNum.h>
#endif

#ifndef __VECTOROPS__
#include <vecLib/vectorOps.h>
#endif

#ifndef __VFP__
#include <vecLib/vfp.h>
#endif

#ifndef __VDSP__
#include <vecLib/vDSP.h>
#endif

#ifndef __VBLAS__
#include <vecLib/vBLAS.h>
#endif


#ifndef __CLAPACK_H
#include <vecLib/clapack.h>
#endif

#endif /* __VECLIB__ */

